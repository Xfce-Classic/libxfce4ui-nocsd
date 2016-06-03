/*-
 * vi:set et ai sts=2 sw=2 cindent:
 *
 * Copyright (c) 2016 Eric Koegel <eric@xfce.org>
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
 * You should have received a copy of the GNU Library General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>

#include <gtk/gtk.h>
#include <glib.h>
#include <libxfce4ui/libxfce4ui.h>


static const gchar *APP_NAME = "libxfce4ui: Test";

static void
main_window_destroy (GtkWidget *window)
{
  gtk_main_quit ();
}

static void
show_xfce_message_dialog (GtkButton *button,
                          gpointer unused)
{
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size ("../icons/48x48/xfce4-logo.png", 24, 24, NULL);

#if GTK_CHECK_VERSION (3, 0, 0)
  xfce_message_dialog (NULL, "Question - Gtk3 version with no deprecated symbols",
                       "dialog-question",
                       "There are unsaved modifications",
                       "The menu has been modified, do you want to save it before quitting?",
                       XFCE_BUTTON_TYPE_MIXED, "document-save", "Save", GTK_RESPONSE_YES,
                       XFCE_BUTTON_TYPE_MIXED, "edit-delete", "Forget modifications", GTK_RESPONSE_APPLY,
                       XFCE_BUTTON_TYPE_PIXBUF, pixbuf, "Quit", GTK_RESPONSE_NO,
                       XFCE_BUTTON_TYPE_MIXED, "process-stop", "Cancel", GTK_RESPONSE_CANCEL,
                       NULL);
#endif

/* ignore those warnings so it's easy to see what the default Gtk2 version
 * looks like in Gtk3 with the stock icons */
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  xfce_message_dialog (NULL, "Question - Gtk2 version",
                       GTK_STOCK_DIALOG_QUESTION,
                       "There are unsaved modifications",
                       "The menu has been modified, do you want to save it before quitting?",
                       GTK_STOCK_SAVE, GTK_RESPONSE_YES,
                       XFCE_BUTTON_TYPE_MIXED, GTK_STOCK_DELETE, "Forget modifications", GTK_RESPONSE_APPLY,
                       XFCE_BUTTON_TYPE_PIXBUF, pixbuf, "Quit", GTK_RESPONSE_NO,
                       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                       NULL);
G_GNUC_END_IGNORE_DEPRECATIONS

  if (pixbuf != NULL)
    {
      g_object_unref (G_OBJECT (pixbuf));
    }
}

static void
show_xfce_dialog_show_help (GtkButton *button,
                            gpointer unused)
{
  xfce_dialog_show_help (NULL, "xfce4-session", "preferences", NULL);
}

static void
show_xfce_dialog_show_help_with_version (GtkButton *button,
                                         gpointer unused)
{
  xfce_dialog_show_help_with_version (NULL, "xfce4-power-manager", "start", NULL, "4.12");
}

static void
show_xfce_dialog_show_info (GtkButton *button,
                            gpointer unused)
{
  xfce_dialog_show_info(NULL, NULL, "%s", "xfburn_transcoder_get_description (priv->trans)");
}

static void
show_xfce_dialog_show_warning (GtkButton *button,
                               gpointer unused)
{
  xfce_dialog_show_warning(NULL, NULL, _("A file named \"%s\" already exists in this directory, the file hasn't been added."), "name");
}

static void
show_xfce_dialog_show_error (GtkButton *button,
                             gpointer unused)
{
  GError *error = NULL;

  g_set_error (&error, G_FILE_ERROR, G_FILE_ERROR_NOENT, "This isn't a real error");

  xfce_dialog_show_error (NULL, error, _("Failed to migrate the old panel configuration"));

  g_clear_error (&error);
}

static void
show_xfce_dialog_confirm (GtkButton *button,
                          gpointer unused)
{
#if GTK_CHECK_VERSION (3, 0, 0)
  xfce_dialog_confirm (NULL, "system-run", "Execute",
                       "Do you want to start the panel? If you do, make sure "
                       "you save the session on logout, so the panel is "
                       "automatically started the next time you login.",
                       "No running instance of %s was found", G_LOG_DOMAIN);
#endif

/* ignore those warnings so it's easy to see what the default Gtk2 version
 * looks like in Gtk3 with the stock icons */
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  xfce_dialog_confirm (NULL, GTK_STOCK_EXECUTE, "Execute",
                       "Do you want to start the panel? If you do, make sure "
                       "you save the session on logout, so the panel is "
                       "automatically started the next time you login.",
                       "No running instance of %s was found", G_LOG_DOMAIN);
G_GNUC_END_IGNORE_DEPRECATIONS
}

static void
create_main_window (void)
{
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *button;

  /* Create main window */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), APP_NAME);
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (window), 12);
  gtk_widget_show (window);

  /* Exit main loop when when the window is closed */
  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (main_window_destroy), NULL);

  /* Create the box to hold all the stuff */
#if GTK_CHECK_VERSION (3, 0, 0)
  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
#else
  box = gtk_vbox_new (FALSE, 0);
#endif
  gtk_container_add (GTK_CONTAINER (window), box);
  gtk_widget_show (box);

  /* Create buttons */

  /* xfce_message_dialog */
  button = gtk_button_new_with_label ("show xfce_message_dialog");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_message_dialog), NULL);

  /* xfce_dialog_show_help */
  button = gtk_button_new_with_label ("show xfce_dialog_show_help");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_help), NULL);

  /* xfce_dialog_show_help_with_version */
  button = gtk_button_new_with_label ("show xfce_dialog_show_help_with_version");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_help_with_version), NULL);

  /* xfce_dialog_show_info */
  button = gtk_button_new_with_label ("show xfce_dialog_show_info");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_info), NULL);

  /* xfce_dialog_show_warning */
  button = gtk_button_new_with_label ("show xfce_dialog_show_warning");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_warning), NULL);

  /* xfce_dialog_show_error */
  button = gtk_button_new_with_label ("show xfce_dialog_show_error");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_show_error), NULL);

  /* xfce_dialog_confirm */
  button = gtk_button_new_with_label ("show xfce_dialog_confirm");
  gtk_container_add (GTK_CONTAINER (box), button);
  gtk_widget_show (button);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (show_xfce_dialog_confirm), NULL);
}



gint
main (gint    argc,
      gchar **argv)
{
  gint    exit_code = EXIT_SUCCESS;

  /* Initialize GTK+ */
  gtk_init (&argc, &argv);

  /* create the main window */
  create_main_window ();

  /* Enter main loop */
  gtk_main ();

  return exit_code;
}
