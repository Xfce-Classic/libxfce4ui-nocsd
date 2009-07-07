/* $Id$ */
/*-
 * Copyright (c) 2005-2007 Benedikt Meurer <benny@xfce.org>
 * Copyright (c) 2007      The Xfce Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <gdk/gdk.h>

#ifdef GDK_WINDOWING_X11
#include <X11/Xatom.h>
#include <gdk/gdkx.h>
#endif

#ifdef HAVE_LIBSTARTUP_NOTIFICATION
#include <libsn/sn.h>
#endif

#include <libxfce4ui/xfce-spawn.h>
#include <libxfce4ui/xfce-gdk-extensions.h>
#include <libxfce4ui/libxfce4ui-private.h>
#include <libxfce4ui/libxfce4ui-alias.h>

/* the maximum time for an application to startup */
#define XFCE_SPAWN_STARTUP_TIMEOUT (30 * 1000)



#ifdef HAVE_LIBSTARTUP_NOTIFICATION
typedef struct
{
  SnLauncherContext *sn_launcher;
  guint              timeout_id;
  guint              watch_id;
  GPid               pid;
} XfceSpawnData;




static gboolean
xfce_spawn_startup_timeout (gpointer user_data)
{
  XfceSpawnData *spawn_data = user_data;
  GTimeVal       now;
  gdouble        elapsed;
  glong          tv_sec;
  glong          tv_usec;

  GDK_THREADS_ENTER ();

  /* determine the amount of elapsed time */
  g_get_current_time (&now);
  sn_launcher_context_get_last_active_time (spawn_data->sn_launcher, &tv_sec, &tv_usec);
  elapsed = (((gdouble) now.tv_sec - tv_sec) * G_USEC_PER_SEC + (now.tv_usec - tv_usec)) / 1000.0;

  /* check if the timeout was reached */
  if (elapsed >= XFCE_SPAWN_STARTUP_TIMEOUT)
    {
      /* abort the startup notification */
      sn_launcher_context_complete (spawn_data->sn_launcher);
      sn_launcher_context_unref (spawn_data->sn_launcher);
      spawn_data->sn_launcher = NULL;
    }

  GDK_THREADS_LEAVE ();

  /* keep the startup timeout if not elapsed */
  return (elapsed < XFCE_SPAWN_STARTUP_TIMEOUT);
}



static void
xfce_spawn_startup_timeout_destroy (gpointer user_data)
{
  XfceSpawnData *spawn_data = user_data;

  g_return_if_fail (spawn_data->sn_launcher == NULL);

  /* cancel the watch (if any) */
  if (spawn_data->watch_id != 0)
    g_source_remove (spawn_data->watch_id);

  /* make sure we don't leave zombies */
  g_child_watch_add_full (G_PRIORITY_LOW, spawn_data->pid,
                          (GChildWatchFunc) g_spawn_close_pid,
                          NULL, NULL);

  /* release the startup data */
  g_slice_free (XfceSpawnData, spawn_data);
}



static void
xfce_spawn_startup_watch (GPid     pid,
                          gint     status,
                          gpointer user_data)
{
  XfceSpawnData *spawn_data = user_data;

  g_return_if_fail (spawn_data->sn_launcher != NULL);
  g_return_if_fail (spawn_data->watch_id != 0);
  g_return_if_fail (spawn_data->pid == pid);

  /* abort the startup notification (application exited) */
  sn_launcher_context_complete (spawn_data->sn_launcher);
  sn_launcher_context_unref (spawn_data->sn_launcher);
  spawn_data->sn_launcher = NULL;

  /* cancel the startup notification timeout */
  g_source_remove (spawn_data->timeout_id);
}



static gint
xfce_spawn_get_active_workspace_number (GdkScreen *screen)
{
  GdkWindow *root;
  gulong     bytes_after_ret = 0;
  gulong     nitems_ret = 0;
  guint     *prop_ret = NULL;
  Atom       _NET_CURRENT_DESKTOP;
  Atom       _WIN_WORKSPACE;
  Atom       type_ret = None;
  gint       format_ret;
  gint       ws_num = 0;

  gdk_error_trap_push ();

  root = gdk_screen_get_root_window (screen);

  /* determine the X atom values */
  _NET_CURRENT_DESKTOP = XInternAtom (GDK_WINDOW_XDISPLAY (root), "_NET_CURRENT_DESKTOP", False);
  _WIN_WORKSPACE = XInternAtom (GDK_WINDOW_XDISPLAY (root), "_WIN_WORKSPACE", False);

  if (XGetWindowProperty (GDK_WINDOW_XDISPLAY (root), GDK_WINDOW_XWINDOW (root),
                          _NET_CURRENT_DESKTOP, 0, 32, False, XA_CARDINAL,
                          &type_ret, &format_ret, &nitems_ret, &bytes_after_ret,
                          (gpointer) &prop_ret) != Success)
    {
      if (XGetWindowProperty (GDK_WINDOW_XDISPLAY (root), GDK_WINDOW_XWINDOW (root),
                              _WIN_WORKSPACE, 0, 32, False, XA_CARDINAL,
                              &type_ret, &format_ret, &nitems_ret, &bytes_after_ret,
                              (gpointer) &prop_ret) != Success)
        {
          if (G_UNLIKELY (prop_ret != NULL))
            {
              XFree (prop_ret);
              prop_ret = NULL;
            }
        }
    }

  if (G_LIKELY (prop_ret != NULL))
    {
      if (G_LIKELY (type_ret != None && format_ret != 0))
        ws_num = *prop_ret;
      XFree (prop_ret);
    }

  gdk_error_trap_pop ();

  return ws_num;
}
#endif



/**
 * xfce_spawn_on_screen:
 * @screen            : a #GdkScreen or %NULL to use the active screen,
 *                      see xfce_gdk_screen_get_active().
 * @working_directory : child's current working directory or %NULL to
 *                      inherit parent's.
 * @argv              : child's argument vector.
 * @envp              : child's environment vector or %NULL to inherit
 *                      parent's.
 * @flags             : flags from #GSpawnFlags.
 * @startup_notify    : whether to use startup notification.
 * @startup_timestamp : the timestamp to pass to startup notification, use
 *                      the event time here if possible to make focus
 *                      stealing prevention work property. If you don't
 *                      have direct access to the event time you could use
 *                      gtk_get_current_event_time() or if nothing is
 *                      available 0 is valid too.
 * @icon_name         : application icon or %NULL.
 * @error             : return location for errors or %NULL.
 *
 * Like gdk_spawn_on_screen(), but also supports startup notification
 * (if Libxfce4ui was built with startup notification support).
 *
 * Return value: %TRUE on success, %FALSE if @error is set.
 **/
gboolean
xfce_spawn_on_screen (GdkScreen    *screen,
                      const gchar  *working_directory,
                      gchar       **argv,
                      gchar       **envp,
                      GSpawnFlags   flags,
                      gboolean      startup_notify,
                      guint32       startup_timestamp,
                      const gchar  *icon_name,
                      GError      **error)
{
  gboolean           succeed;
  gchar            **cenvp;
  gint               n;
  gint               n_cenvp;
  gchar             *display_name;
  GPid               pid;
#ifdef HAVE_LIBSTARTUP_NOTIFICATION
  SnLauncherContext *sn_launcher = NULL;
  XfceSpawnData     *spawn_data;
  SnDisplay         *sn_display = NULL;
  gint               sn_workspace;
#endif

  g_return_val_if_fail (screen == NULL || GDK_IS_SCREEN (screen), FALSE);
  g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

  /* lookup the screen with the pointer */
  if (screen == NULL)
    screen = xfce_gdk_screen_get_active (NULL);

  /* setup the child environment, without startup id and display */
  if (G_LIKELY (envp == NULL))
    {
      /* use the portable g_listenv, but note that this function only returns the
       * variable names, not with values, therefore the call to g_getenv */
      envp = g_listenv ();
      cenvp = g_new0 (gchar *, g_strv_length (envp) + 3);
      for (n = n_cenvp = 0; envp[n] != NULL; n++)
        if (strcmp (envp[n], "DESKTOP_STARTUP_ID") != 0
            && strcmp (envp[n], "DISPLAY") != 0)
          cenvp[n_cenvp++] = g_strconcat (envp[n], "=", g_getenv (envp[n]), NULL);

      /* cleanup */
      g_strfreev (envp);
      envp = NULL;
    }
  else
    {
      cenvp = g_new0 (gchar *, g_strv_length (envp) + 3);
      for (n = n_cenvp = 0; envp[n] != NULL; n++)
        if (strncmp (envp[n], "DESKTOP_STARTUP_ID", 18) != 0
            && strncmp (envp[n], "DISPLAY", 7) != 0)
          cenvp[n_cenvp++] = g_strdup (envp[n]);
    }

  /* add the real display name */
  display_name = gdk_screen_make_display_name (screen);
  cenvp[n_cenvp++] = g_strconcat ("DISPLAY=", display_name, NULL);
  g_free (display_name);

#ifdef HAVE_LIBSTARTUP_NOTIFICATION
  /* initialize the sn launcher context */
  if (G_LIKELY (startup_notify))
    {
      sn_display = sn_display_new (GDK_SCREEN_XDISPLAY (screen),
                                   (SnDisplayErrorTrapPush) gdk_error_trap_push,
                                   (SnDisplayErrorTrapPop) gdk_error_trap_pop);

      if (G_LIKELY (sn_display != NULL))
        {
          sn_launcher = sn_launcher_context_new (sn_display, GDK_SCREEN_XNUMBER (screen));

          if (G_LIKELY (sn_launcher != NULL && !sn_launcher_context_get_initiated (sn_launcher)))
            {
              /* initiate the sn launcher context */
              sn_workspace = xfce_spawn_get_active_workspace_number (screen);
              sn_launcher_context_set_binary_name (sn_launcher, argv[0]);
              sn_launcher_context_set_workspace (sn_launcher, sn_workspace);
              sn_launcher_context_set_icon_name (sn_launcher, (icon_name != NULL) ? icon_name : "applications-other");
              sn_launcher_context_initiate (sn_launcher, g_get_prgname (), argv[0], startup_timestamp);

              /* add the real startup id to the child environment */
              cenvp[n_cenvp++] = g_strconcat ("DESKTOP_STARTUP_ID=", sn_launcher_context_get_startup_id (sn_launcher), NULL);

              /* we want to watch the child process */
              flags |= G_SPAWN_DO_NOT_REAP_CHILD;
            }
        }
    }
#endif

  /* try to spawn the new process */
  succeed = g_spawn_async (working_directory, argv, cenvp, flags, NULL, NULL, &pid, error);

#ifdef HAVE_LIBSTARTUP_NOTIFICATION
  if (G_LIKELY (sn_launcher != NULL))
    {
      if (G_UNLIKELY (!succeed))
        {
          /* abort the startup notification sequence */
          sn_launcher_context_complete (sn_launcher);
          sn_launcher_context_unref (sn_launcher);
        }
      else
        {
          /* schedule a startup notification timeout */
          spawn_data = g_slice_new0 (XfceSpawnData);
          spawn_data->sn_launcher = sn_launcher;
          spawn_data->timeout_id = g_timeout_add_full (G_PRIORITY_LOW, XFCE_SPAWN_STARTUP_TIMEOUT, xfce_spawn_startup_timeout,
                                                         spawn_data, xfce_spawn_startup_timeout_destroy);
          spawn_data->watch_id = g_child_watch_add_full (G_PRIORITY_LOW, pid, xfce_spawn_startup_watch, spawn_data, NULL);
          spawn_data->pid = pid;
        }
    }
  else if (G_LIKELY (succeed))
    {
      /* make sure we don't leave zombies */
      g_child_watch_add_full (G_PRIORITY_LOW, pid, (GChildWatchFunc) g_spawn_close_pid, NULL, NULL);
    }

  /* release the sn display */
  if (G_LIKELY (sn_display != NULL))
    sn_display_unref (sn_display);
#endif

  /* cleanup */
  g_strfreev (cenvp);

  return succeed;
}



/**
 * xfce_spawn_command_line_on_screen:
 * @screen            : a #GdkScreen or %NULL to use the active screen, see xfce_gdk_screen_get_active().
 * @command_line      : command line to run.
 * @in_terminal       : whether to run @command_line in a terminal.
 * @startup_notify    : whether to use startup notification.
 * @error             : location for a #GError or %NULL.
 *
 * Executes the given @command_line and returns %TRUE if the
 * command terminated successfully. Else, the @error is set
 * to the standard error output.
 *
 * Returns: %TRUE if the @command_line was executed
 *          successfully, %FALSE if @error is set.
 */
gboolean
xfce_spawn_command_line_on_screen (GdkScreen    *screen,
                                   const gchar  *command_line,
                                   gboolean      in_terminal,
                                   gboolean      startup_notify,
                                   GError      **error)
{
  gchar    **argv;
  gboolean   succeed;

  g_return_val_if_fail (screen == NULL || GDK_IS_SCREEN (screen), FALSE);
  g_return_val_if_fail (error == NULL || *error == NULL, FALSE);
  g_return_val_if_fail (command_line != NULL, FALSE);

  /* parse the command */
  if (in_terminal == FALSE)
    {
      /* parse the command, retrun false with error when this fails */
      if (G_UNLIKELY (!g_shell_parse_argv (command_line, NULL, &argv, error)))
        return FALSE;
    }
  else
    {
      /* create an argv to run the command in a terminal */
      argv = g_new0 (gchar *, 5);
      argv[0] = g_strdup ("exo-open");
      argv[1] = g_strdup ("--launch");
      argv[2] = g_strdup ("TerminalEmulator");
      argv[3] = g_strdup (command_line);
      argv[4] = NULL;
    }

  /* execute the function */
  succeed = xfce_spawn_on_screen (screen, NULL, argv, NULL,
                                       G_SPAWN_SEARCH_PATH, startup_notify,
                                       gtk_get_current_event_time (), NULL, error);

  /* cleanup */
  g_strfreev (argv);

  return succeed;
}



#define __XFCE_SPAWN_C__
#include <libxfce4ui/libxfce4ui-aliasdef.c>
