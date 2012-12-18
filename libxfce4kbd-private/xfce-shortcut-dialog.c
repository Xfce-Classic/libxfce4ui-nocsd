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

#include <gdk/gdkkeysyms.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>

#include <libxfce4util/libxfce4util.h>
#include <libxfce4ui/libxfce4ui.h>

#include <libxfce4kbd-private/xfce-shortcuts.h>
#include <libxfce4kbd-private/xfce-shortcut-dialog.h>



static void     xfce_shortcut_dialog_finalize         (GObject                 *object);
static void     xfce_shortcut_dialog_create_contents  (XfceShortcutDialog      *dialog,
                                                       const gchar             *provider,
                                                       const gchar             *action_name,
                                                       const gchar             *action);
static gboolean xfce_shortcut_dialog_key_pressed      (XfceShortcutDialog      *dialog,
                                                       GdkEventKey             *event);
static gboolean xfce_shortcut_dialog_key_released     (XfceShortcutDialog      *dialog,
                                                       GdkEventKey             *event);



struct _XfceShortcutDialogClass
{
  XfceTitledDialogClass __parent__;

  gboolean (*validate_shortcut) (XfceShortcutDialog *dialog,
                                 const gchar        *shortcut,
                                 gpointer            user_data);

  gint validate_shortcut_signal;
};

struct _XfceShortcutDialog
{
  XfceTitledDialog __parent__;

  GtkWidget *shortcut_label;

  gchar     *action_name;
  gchar     *action;
  gchar     *shortcut;
};



G_DEFINE_TYPE (XfceShortcutDialog, xfce_shortcut_dialog, XFCE_TYPE_TITLED_DIALOG)



/**
 * Taken from GTK+ (_gtk_marshal_BOOLEAN__SRING). Credits go out to the
 * GTK+ devs for this.
 */
static void
marshal_BOOLEAN__STRING (GClosure     *closure,
                         GValue       *return_value G_GNUC_UNUSED,
                         guint         n_param_values,
                         const GValue *param_values,
                         gpointer      invocation_hint G_GNUC_UNUSED,
                         gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__STRING) (gpointer data1,
                                                    gpointer arg_1,
                                                    gpointer data2);
  register GMarshalFunc_BOOLEAN__STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 2);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }

  callback = (GMarshalFunc_BOOLEAN__STRING) (marshal_data ? marshal_data : cc->callback);

  #define g_marshal_value_peek_string(v) (char*) g_value_get_string (v)
  v_return = callback (data1, g_marshal_value_peek_string (param_values + 1), data2);

  g_value_set_boolean (return_value, v_return);
}




static void
xfce_shortcut_dialog_class_init (XfceShortcutDialogClass *klass)
{
  GObjectClass *gobject_class;

  /* Make sure to use the translations from libxfce4ui */
  xfce_textdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR, "UTF-8");

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = xfce_shortcut_dialog_finalize;

  klass->validate_shortcut = NULL;

  /* Create 'validate-shortcut' signal */
  klass->validate_shortcut_signal = g_signal_new ("validate-shortcut",
                                                  G_TYPE_FROM_CLASS (klass),
                                                  G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                                                  G_STRUCT_OFFSET (XfceShortcutDialogClass, validate_shortcut),
                                                  NULL,
                                                  NULL,
                                                  marshal_BOOLEAN__STRING,
                                                  G_TYPE_BOOLEAN,
                                                  1,
                                                  G_TYPE_STRING);
}



static void
xfce_shortcut_dialog_init (XfceShortcutDialog *dialog)
{
  dialog->shortcut = NULL;
}



static void
xfce_shortcut_dialog_finalize (GObject *object)
{
  XfceShortcutDialog *dialog = XFCE_SHORTCUT_DIALOG (object);

  g_free (dialog->action_name);
  g_free (dialog->action);
  g_free (dialog->shortcut);

  (*G_OBJECT_CLASS (xfce_shortcut_dialog_parent_class)->finalize) (object);
}



GtkWidget*
xfce_shortcut_dialog_new (const gchar *provider,
                          const gchar *action_name,
                          const gchar *action)
{
  XfceShortcutDialog *dialog;

  dialog = g_object_new (XFCE_TYPE_SHORTCUT_DIALOG, NULL);
  dialog->action_name = g_strdup (action_name);
  dialog->action = g_strdup (action);

  xfce_shortcut_dialog_create_contents (dialog, provider, action_name, action);

  return GTK_WIDGET (dialog);
}



static void
xfce_shortcut_dialog_create_contents (XfceShortcutDialog *dialog,
                                      const gchar        *provider,
                                      const gchar        *action_name,
                                      const gchar        *action)
{
  GtkWidget   *button;
  GtkWidget   *table;
  GtkWidget   *label;
  const gchar *title;
  const gchar *action_label;

  if (g_utf8_collate (provider, "xfwm4") == 0)
    {
      title = _("Window Manager Action Shortcut");
      action_label = _("Action:");
    }
  else if (g_utf8_collate (provider, "commands") == 0)
    {
      title = _("Command Shortcut");
      action_label = _("Command:");
    }
  else
    {
      title = _("Shortcut");
      action_label = _("Action:");
    }

  /* Set dialog title */
  gtk_window_set_title (GTK_WINDOW (dialog), title);
  gtk_window_set_icon_name (GTK_WINDOW (dialog), "input-keyboard");

  /* Create clear button for xfwm4 */
  if (g_utf8_collate (provider, "xfwm4") == 0)
    {
      button = gtk_button_new_from_stock (GTK_STOCK_CLEAR);
      gtk_dialog_add_action_widget (GTK_DIALOG (dialog), button, GTK_RESPONSE_REJECT);
      gtk_widget_show (button);
    }

  /* Create cancel button */
  button = gtk_button_new_from_stock (GTK_STOCK_CANCEL);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog), button, GTK_RESPONSE_CANCEL);
  gtk_widget_show (button);

  table = gtk_table_new (2, 2, FALSE);
  gtk_table_set_row_spacings (GTK_TABLE (table), 6);
  gtk_table_set_col_spacings (GTK_TABLE (table), 12);
  gtk_container_set_border_width (GTK_CONTAINER (table), 12);
  gtk_container_add (GTK_CONTAINER (gtk_dialog_get_content_area (GTK_DIALOG (dialog))), table);
  gtk_widget_show (table);

  label = gtk_label_new (action_label);
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  gtk_table_attach (GTK_TABLE (table), label, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
  gtk_widget_show (label);

  label = gtk_label_new (action_name);
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  gtk_table_attach_defaults (GTK_TABLE (table), label, 1, 2, 0, 1);
  gtk_widget_show (label);

  label = gtk_label_new (_("Shortcut:"));
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  gtk_table_attach (GTK_TABLE (table), label, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
  gtk_widget_show (label);

  dialog->shortcut_label = gtk_label_new (NULL);
  gtk_misc_set_alignment (GTK_MISC (dialog->shortcut_label), 0.0, 0.5);
  gtk_table_attach_defaults (GTK_TABLE (table), dialog->shortcut_label, 1, 2, 1, 2);
  gtk_widget_show (dialog->shortcut_label);

  /* Connect to key release signal for determining the new shortcut */
  g_signal_connect_swapped (dialog, "key-press-event", G_CALLBACK (xfce_shortcut_dialog_key_pressed), dialog);
  g_signal_connect_swapped (dialog, "key-release-event", G_CALLBACK (xfce_shortcut_dialog_key_released), dialog);
}



gint
xfce_shortcut_dialog_run (XfceShortcutDialog *dialog,
                          GtkWidget          *parent)
{
#if GTK_CHECK_VERSION (3, 0, 0)
  GdkDisplay       *display;
  GdkDevice        *device;
  GdkDeviceManager *device_manager;
  GList            *devices, *li;
  gboolean          succeed = FALSE;
#endif
  gint              response = GTK_RESPONSE_CANCEL;

  g_return_val_if_fail (XFCE_IS_SHORTCUT_DIALOG (dialog), GTK_RESPONSE_CANCEL);

  gtk_window_set_transient_for (GTK_WINDOW (dialog), GTK_WINDOW (parent));
  gtk_window_set_destroy_with_parent (GTK_WINDOW (dialog), TRUE);

#if GTK_CHECK_VERSION (3, 0, 0)
  display = gtk_widget_get_display (GTK_WIDGET (dialog));
  device_manager = gdk_display_get_device_manager (display);
  devices = gdk_device_manager_list_devices (device_manager, GDK_DEVICE_TYPE_MASTER);

  for (li = devices; li != NULL; li =li->next)
    {
      device = li->data;
      if (gdk_device_get_source (device) != GDK_SOURCE_KEYBOARD)
        continue;

      if (gdk_device_grab (device, gtk_widget_get_root_window (GTK_WIDGET (dialog)),
                           GDK_OWNERSHIP_WINDOW, TRUE,
                           GDK_KEY_PRESS_MASK | GDK_KEY_RELEASE_MASK,
                           NULL, GDK_CURRENT_TIME) == GDK_GRAB_SUCCESS)
        {
          succeed = TRUE;
        }
    }

  /* Take control on the keyboard */
  if (succeed)
#else
  /* Take control on the keyboard */
  if (G_LIKELY (gdk_keyboard_grab (gtk_widget_get_root_window (GTK_WIDGET (dialog)), TRUE, GDK_CURRENT_TIME) == GDK_GRAB_SUCCESS))
#endif
    {
      /* Run the dialog and wait for the user to enter a valid shortcut */
      response = gtk_dialog_run (GTK_DIALOG (dialog));

      /* Clear shortcut if requested by the user */
      if (G_UNLIKELY (response == GTK_RESPONSE_NO))
        {
          g_free (dialog->shortcut);
          dialog->shortcut = g_strdup ("");
        }

#if GTK_CHECK_VERSION (3, 0, 0)
      /* Release keyboard */
      for (li = devices; li != NULL; li =li->next)
        {
          device = li->data;
          if (gdk_device_get_source (device) == GDK_SOURCE_KEYBOARD)
            gdk_device_ungrab (device, GDK_CURRENT_TIME);
        }
#else
      /* Release keyboard */
      gdk_keyboard_ungrab (GDK_CURRENT_TIME);
#endif
    }
  else
    {
      g_warning (_("Could not grab the keyboard."));
    }

#if GTK_CHECK_VERSION (3, 0, 0)
  g_list_free (devices);
#endif

  /* Return the response ID */
  return response;
}



static gboolean
xfce_shortcut_dialog_key_pressed (XfceShortcutDialog *dialog,
                                  GdkEventKey        *event)
{
  GdkKeymap       *keymap;
  GdkModifierType  consumed, modifiers;
  guint            keyval, mod_mask;
  gchar           *text;
  gchar           *shortcut;

  g_free (dialog->shortcut);

  /* Get the keyboard state */
  mod_mask = gtk_accelerator_get_default_mod_mask ();
  keymap = gdk_keymap_get_default ();
  modifiers = event->state;

  gdk_keymap_translate_keyboard_state (keymap, event->hardware_keycode,
                                       modifiers, event->group,
                                       &keyval, NULL, NULL, &consumed);

  /* Get the modifiers */

  /* If Shift was used when translating the keyboard state, we remove it
   * from the consumed bit because gtk_accelerator_{name,parse} fail to
   * handle this correctly. This allows us to have shortcuts with Shift
   * as a modifier key (see bug #8744). */
  if ((modifiers & GDK_SHIFT_MASK) && (consumed & GDK_SHIFT_MASK))
    consumed &= ~GDK_SHIFT_MASK;

  modifiers &= ~consumed;
  modifiers &= mod_mask;

  /* Get and store the pressed shortcut */
  dialog->shortcut = gtk_accelerator_name (keyval, modifiers);

  shortcut = g_markup_escape_text (dialog->shortcut, -1);
  text = g_strdup_printf ("<span size='large'><b>%s</b></span>", shortcut);

  gtk_label_set_markup (GTK_LABEL (dialog->shortcut_label), text);

  g_free (text);
  g_free (shortcut);

  return FALSE;
}



static gboolean
xfce_shortcut_dialog_key_released (XfceShortcutDialog *dialog,
                                   GdkEventKey        *event)
{
  gboolean shortcut_accepted = FALSE;

  /* Let 'validate-shortcut' listeners decide whether this shortcut is ok or not */
  g_signal_emit_by_name (dialog, "validate-shortcut", dialog->shortcut, &shortcut_accepted);

  /* Check if the shortcut was accepted */
  if (G_LIKELY (shortcut_accepted))
    {
#if !GTK_CHECK_VERSION (3, 0, 0)
      /* Release keyboard */
      gdk_keyboard_ungrab (GDK_CURRENT_TIME);
#endif

      /* Exit dialog with positive response */
      gtk_dialog_response (GTK_DIALOG (dialog), GTK_RESPONSE_OK);
    }
  else
    {
      /* Clear label */
      gtk_label_set_markup (GTK_LABEL (dialog->shortcut_label), "");
    }

  return FALSE;
}



const gchar*
xfce_shortcut_dialog_get_shortcut (XfceShortcutDialog *dialog)
{
  g_return_val_if_fail (XFCE_IS_SHORTCUT_DIALOG (dialog), NULL);
  return dialog->shortcut;
}



const gchar *
xfce_shortcut_dialog_get_action (XfceShortcutDialog *dialog)
{
  g_return_val_if_fail (XFCE_IS_SHORTCUT_DIALOG (dialog), NULL);
  return dialog->action;
}



const gchar *
xfce_shortcut_dialog_get_action_name (XfceShortcutDialog *dialog)
{
  g_return_val_if_fail (XFCE_IS_SHORTCUT_DIALOG (dialog), NULL);
  return dialog->action_name;
}
