/* vi:set expandtab sw=2 sts=2: */
/*
 * Copyright (c) 2008 Jannis Pohlmann <jannis@xfce.org>
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
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>
#include <glib-object.h>

#include <X11/Xlib.h>
#include <X11/XKBlib.h>

#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gdk/gdkkeysyms.h>

#include <gtk/gtk.h>

#include <libxfce4util/libxfce4util.h>

#include <libxfce4kbd-private/xfce-shortcuts-grabber.h>
#include <libxfce4kbd-private/xfce-shortcuts-marshal.h>



#define XFCE_SHORTCUTS_GRABBER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), XFCE_TYPE_SHORTCUTS_GRABBER, XfceShortcutsGrabberPrivate))
#define MODIFIERS_ERROR ((GdkModifierType)(-1))
#define MODIFIERS_NONE 0


typedef struct _XfceKey XfceKey;



static void            xfce_shortcuts_grabber_constructed      (GObject                   *object);
static void            xfce_shortcuts_grabber_finalize         (GObject                   *object);
static void            xfce_shortcuts_grabber_keys_changed     (GdkKeymap                 *keymap,
                                                                XfceShortcutsGrabber      *grabber);
static void            xfce_shortcuts_grabber_grab_all         (XfceShortcutsGrabber      *grabber);
static void            xfce_shortcuts_grabber_ungrab_all       (XfceShortcutsGrabber      *grabber);
static void            xfce_shortcuts_grabber_grab             (XfceShortcutsGrabber      *grabber,
                                                                XfceKey                   *key,
                                                                gboolean                   grab);
static GdkFilterReturn xfce_shortcuts_grabber_event_filter     (GdkXEvent                 *gdk_xevent,
                                                                GdkEvent                  *event,
                                                                XfceShortcutsGrabber      *grabber);



struct _XfceShortcutsGrabberPrivate
{
  GHashTable *keys;
};

struct _XfceKey
{
  guint keyval;
  guint modifiers;
};



G_DEFINE_TYPE (XfceShortcutsGrabber, xfce_shortcuts_grabber, G_TYPE_OBJECT)



static void
xfce_shortcuts_grabber_class_init (XfceShortcutsGrabberClass *klass)
{
  GObjectClass *gobject_class;

  g_type_class_add_private (klass, sizeof (XfceShortcutsGrabberPrivate));

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->constructed = xfce_shortcuts_grabber_constructed;
  gobject_class->finalize = xfce_shortcuts_grabber_finalize;

  g_signal_new ("shortcut-activated",
                XFCE_TYPE_SHORTCUTS_GRABBER,
                G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                0,
                NULL,
                NULL,
                _xfce_shortcuts_marshal_VOID__STRING_INT,
                G_TYPE_NONE,
                2,
                G_TYPE_STRING, G_TYPE_INT);
}



static void
xfce_shortcuts_grabber_init (XfceShortcutsGrabber *grabber)
{
  grabber->priv = XFCE_SHORTCUTS_GRABBER_GET_PRIVATE (grabber);
  grabber->priv->keys = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

  /* Workaround: Make sure modmap is up to date
   * There is possibly a bug in GTK+ where virtual modifiers are not
   * mapped because the modmap is not updated. The following function
   * updates it.
   */
  (void) gdk_keymap_have_bidi_layouts (gdk_keymap_get_default ());
}



static void
xfce_shortcuts_grabber_constructed (GObject *object)
{
  GdkDisplay *display;
  GdkKeymap  *keymap;

  XfceShortcutsGrabber *grabber = XFCE_SHORTCUTS_GRABBER (object);

  keymap = gdk_keymap_get_default ();
  g_signal_connect (keymap, "keys-changed", G_CALLBACK (xfce_shortcuts_grabber_keys_changed),
                    grabber);

  display = gdk_display_get_default ();

  /* Flush events before adding the event filter */
  XAllowEvents (GDK_DISPLAY_XDISPLAY (display), AsyncBoth, CurrentTime);

  /* Add event filter */
  gdk_window_add_filter (NULL, (GdkFilterFunc) xfce_shortcuts_grabber_event_filter, grabber);
}



static void
xfce_shortcuts_grabber_finalize (GObject *object)
{
  XfceShortcutsGrabber *grabber = XFCE_SHORTCUTS_GRABBER (object);

  xfce_shortcuts_grabber_ungrab_all (grabber);
  g_hash_table_unref (grabber->priv->keys);

  (*G_OBJECT_CLASS (xfce_shortcuts_grabber_parent_class)->finalize) (object);
}



static void
xfce_shortcuts_grabber_keys_changed (GdkKeymap            *keymap,
                                     XfceShortcutsGrabber *grabber)
{
  g_return_if_fail (XFCE_IS_SHORTCUTS_GRABBER (grabber));

  TRACE ("Keys changed, regrabbing");

  xfce_shortcuts_grabber_ungrab_all (grabber);
  xfce_shortcuts_grabber_grab_all (grabber);
}



static gboolean
grab_key (const gchar          *shortcut,
          XfceKey              *key,
          XfceShortcutsGrabber *grabber)
{
  xfce_shortcuts_grabber_grab (grabber, key, TRUE);
  return FALSE;
}



static void
xfce_shortcuts_grabber_grab_all (XfceShortcutsGrabber *grabber)
{
  g_return_if_fail (XFCE_IS_SHORTCUTS_GRABBER (grabber));
  g_hash_table_foreach (grabber->priv->keys,
                        (GHFunc) (void (*)(void)) grab_key,
                        grabber);
}



static gboolean
ungrab_key (const gchar          *shortcut,
            XfceKey              *key,
            XfceShortcutsGrabber *grabber)
{
  xfce_shortcuts_grabber_grab (grabber, key, FALSE);
  return FALSE;
}



static void
xfce_shortcuts_grabber_ungrab_all (XfceShortcutsGrabber *grabber)
{
  g_return_if_fail (XFCE_IS_SHORTCUTS_GRABBER (grabber));
  g_hash_table_foreach (grabber->priv->keys,
                        (GHFunc) (void (*)(void)) ungrab_key,
                        grabber);
}



static void
xfce_shortcuts_grabber_grab (XfceShortcutsGrabber *grabber,
                             XfceKey              *key,
                             gboolean              grab)
{
  GdkModifierType  numlock_modifier;
  GdkKeymapKey    *keys;
  GdkDisplay      *display;
  GdkKeymap       *keymap;
  gchar           *shortcut_name;
  guint            modifiers;
  guint            k;
  gint             i, j;
  gint             n_keys;
  gint             screens;

  g_return_if_fail (XFCE_IS_SHORTCUTS_GRABBER (grabber));
  g_return_if_fail (key != NULL);

  display = gdk_display_get_default ();
#if GTK_CHECK_VERSION (3, 10, 0)
  screens = 1;
#else
  screens = gdk_display_get_n_screens (display);
#endif
  keymap = gdk_keymap_get_default ();

  /* Map virtual modifiers to non-virtual modifiers */
  modifiers = key->modifiers;
  gdk_keymap_map_virtual_modifiers (keymap, &modifiers);

  /* Debugging information */
  shortcut_name = gtk_accelerator_name (key->keyval, modifiers);

  if (grab)
    TRACE ("Grabbing %s", shortcut_name);
  else
    TRACE ("Ungrabbing %s", shortcut_name);

  TRACE ("Keyval: %d", key->keyval);
  TRACE ("Modifiers: 0x%x", modifiers);

  g_free (shortcut_name);

  if (modifiers == key->modifiers &&
      (GDK_SUPER_MASK | GDK_HYPER_MASK | GDK_META_MASK) & modifiers)
    {
      TRACE ("Failed to map virtual modifiers");
      return;
    }

  /* Get all keys generating keyval */
  if (!gdk_keymap_get_entries_for_keyval (keymap,key->keyval,
                                          &keys, &n_keys))
    {
      TRACE ("Got no keys for keyval");
      return;
    }

  if (n_keys == 0)
    {
      g_free (keys);

      TRACE ("Got 0 keys for keyval");
      return;
    }

  numlock_modifier =
    XkbKeysymToModifiers (GDK_DISPLAY_XDISPLAY (display), GDK_KEY_Num_Lock);

  for (i = 0; i < n_keys; i ++)
    {
      /* Grab all hardware keys generating keyval */

      TRACE ("Keycode: %d", keys[i].keycode);

      for (j = 0; j < screens; j++)
        {
          /* Do the grab on all screens */
          Window root_window;

          /* Ignorable modifiers */
          guint mod_masks [] = {
            0,
            GDK_MOD2_MASK,
            numlock_modifier | GDK_MOD2_MASK,
            GDK_LOCK_MASK,
            numlock_modifier | GDK_LOCK_MASK,
            GDK_MOD5_MASK,
            numlock_modifier | GDK_MOD5_MASK,
            GDK_MOD2_MASK | GDK_LOCK_MASK,
            numlock_modifier | GDK_MOD2_MASK | GDK_LOCK_MASK,
            GDK_MOD2_MASK | GDK_MOD5_MASK,
            numlock_modifier | GDK_MOD2_MASK | GDK_MOD5_MASK,
            GDK_LOCK_MASK | GDK_MOD5_MASK,
            numlock_modifier | GDK_LOCK_MASK | GDK_MOD5_MASK,
            GDK_MOD2_MASK | GDK_LOCK_MASK | GDK_MOD5_MASK,
            numlock_modifier | GDK_MOD2_MASK | GDK_LOCK_MASK | GDK_MOD5_MASK,
          };

#if GTK_CHECK_VERSION (3, 0, 0)
          /* Retrieve the root window of the screen */
          root_window = GDK_WINDOW_XID (gdk_screen_get_root_window (gdk_display_get_screen (display, j)));
          gdk_x11_display_error_trap_push (display);
#else
          /* Retrieve the root window of the screen */
          root_window = GDK_WINDOW_XWINDOW (gdk_screen_get_root_window (gdk_display_get_screen (display, j)));
          gdk_error_trap_push ();
#endif

          for (k = 0; k < G_N_ELEMENTS (mod_masks); k++)
            {
              /* Take ignorable modifiers into account when grabbing */
              if (grab)
                XGrabKey (GDK_DISPLAY_XDISPLAY (display),
                          keys[i].keycode,
                          modifiers | mod_masks [k],
                          root_window,
                          False,
                          GrabModeAsync,
                          GrabModeAsync);
              else
                XUngrabKey (GDK_DISPLAY_XDISPLAY (display),
                            keys[i].keycode,
                            modifiers | mod_masks [k],
                            root_window);
            }

#if GTK_CHECK_VERSION (3, 0, 0)
          gdk_display_flush (display);

          if (gdk_x11_display_error_trap_pop (display))
#else
          gdk_flush ();

          if (gdk_error_trap_pop ())
#endif
            {
              if (grab)
                TRACE ("Failed to grab");
              else
                TRACE ("Failed to ungrab");
            }
        }
    }

  g_free (keys);
}



struct EventKeyFindContext
{
  XfceShortcutsGrabber *grabber;
  GdkModifierType       modifiers;
  guint                 keyval;
  const gchar          *result;
};



static gboolean
find_event_key (const gchar                *shortcut,
                XfceKey                    *key,
                struct EventKeyFindContext *context)
{
  g_return_val_if_fail (context != NULL, FALSE);

  TRACE ("Comparing to %s", shortcut);

  if ((key->modifiers & (GDK_CONTROL_MASK | GDK_SHIFT_MASK | GDK_MOD1_MASK | GDK_SUPER_MASK))
      == (context->modifiers)
      && (key->keyval == context->keyval))
    {
      context->result = shortcut;

      TRACE ("Positive match for %s", context->result);
      return TRUE;
    }

  return FALSE;
}



static GdkFilterReturn
xfce_shortcuts_grabber_event_filter (GdkXEvent            *gdk_xevent,
                                     GdkEvent             *event,
                                     XfceShortcutsGrabber *grabber)
{
  struct EventKeyFindContext  context;
  GdkKeymap                  *keymap;
  GdkModifierType             consumed, modifiers;
  GdkDisplay                 *display;
  XEvent                     *xevent;
  guint                       keyval, mod_mask;
  gchar                      *raw_shortcut_name;
  gint                        timestamp;

  g_return_val_if_fail (XFCE_IS_SHORTCUTS_GRABBER (grabber), GDK_FILTER_CONTINUE);

  xevent = (XEvent *) gdk_xevent;

  if (xevent->type != KeyPress)
    return GDK_FILTER_CONTINUE;

  context.grabber = grabber;
  context.result = NULL;
  timestamp = xevent->xkey.time;

  /* Get the keyboard state */
  display = gdk_display_get_default ();
#if GTK_CHECK_VERSION (3, 0, 0)
  gdk_x11_display_error_trap_push (display);
#else
  gdk_error_trap_push ();
#endif
  keymap = gdk_keymap_get_default ();
  mod_mask = gtk_accelerator_get_default_mod_mask ();
  modifiers = xevent->xkey.state;

  gdk_keymap_translate_keyboard_state (keymap, xevent->xkey.keycode,
                                       modifiers,
                                       XkbGroupForCoreState (xevent->xkey.state),
                                       &keyval, NULL, NULL, &consumed);

  /* We want Alt + Print to be Alt + Print not SysReq. See bug #7897 */
  if (keyval == GDK_KEY_Sys_Req && (modifiers & GDK_MOD1_MASK) != 0)
    {
      consumed = 0;
      keyval = GDK_KEY_Print;
    }

  /* Get the modifiers */

  /* If Shift was used when translating the keyboard state, we remove it
   * from the consumed bit because gtk_accelerator_{name,parse} fail to
   * handle this correctly. This allows us to have shortcuts with Shift
   * as a modifier key (see bug #8744). */
  if ((modifiers & GDK_SHIFT_MASK) && (consumed & GDK_SHIFT_MASK))
    consumed &= ~GDK_SHIFT_MASK;

  /*
   * !!! FIX ME !!!
   * Turn MOD4 into SUPER key press events. Although it is not clear if
   * this is a proper solution, it fixes bug #10373 which some people
   * experience without breaking functionality for other users.
   */
  if (modifiers & GDK_MOD4_MASK)
    {
      modifiers &= ~GDK_MOD4_MASK;
      modifiers |= GDK_SUPER_MASK;
      consumed &= ~GDK_MOD4_MASK;
      consumed &= ~GDK_SUPER_MASK;
    }

  modifiers &= ~consumed;
  modifiers &= mod_mask;

  /* Use the keyval and modifiers values of gtk_accelerator_parse. We
   * will compare them with values we also get from this function and as
   * it has its own logic, it's easier and safer to do so.
   * See bug #8744 for a "live" example. */
  raw_shortcut_name = gtk_accelerator_name (keyval, modifiers);
  gtk_accelerator_parse (raw_shortcut_name, &context.keyval, &context.modifiers);

  TRACE ("Looking for %s", raw_shortcut_name);
  g_free (raw_shortcut_name);

  g_hash_table_foreach (grabber->priv->keys,
                        (GHFunc) (void (*)(void)) find_event_key,
                        &context);

  if (G_LIKELY (context.result != NULL))
    /* We had a positive match */
    g_signal_emit_by_name (grabber, "shortcut-activated",
                           context.result, timestamp);

#if GTK_CHECK_VERSION (3, 0, 0)
  gdk_display_flush (display);
  gdk_x11_display_error_trap_pop_ignored (display);
#else
  gdk_flush ();
  gdk_error_trap_pop ();
#endif

  return GDK_FILTER_CONTINUE;
}



XfceShortcutsGrabber *
xfce_shortcuts_grabber_new (void)
{
  return g_object_new (XFCE_TYPE_SHORTCUTS_GRABBER, NULL);
}



void
xfce_shortcuts_grabber_add (XfceShortcutsGrabber *grabber,
                            const gchar          *shortcut)
{
  XfceKey *key;

  g_return_if_fail (XFCE_IS_SHORTCUTS_GRABBER (grabber));
  g_return_if_fail (shortcut != NULL);

  key = g_new0 (XfceKey, 1);

  gtk_accelerator_parse (shortcut, &key->keyval, &key->modifiers);

  if (G_LIKELY (key->keyval != 0))
    {
      xfce_shortcuts_grabber_grab (grabber, key, TRUE);
      g_hash_table_insert (grabber->priv->keys, g_strdup (shortcut), key);
    }
  else
    g_free (key);
}



void
xfce_shortcuts_grabber_remove (XfceShortcutsGrabber *grabber,
                               const gchar          *shortcut)
{
  XfceKey *key;

  g_return_if_fail (XFCE_IS_SHORTCUTS_GRABBER (grabber));
  g_return_if_fail (shortcut != NULL);

  key = g_hash_table_lookup (grabber->priv->keys, shortcut);

  if (G_LIKELY (key != NULL))
    {
      xfce_shortcuts_grabber_grab (grabber, key, FALSE);
      g_hash_table_remove (grabber->priv->keys, shortcut);
    }
}
