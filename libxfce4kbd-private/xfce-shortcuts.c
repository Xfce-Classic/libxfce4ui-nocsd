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

#include <X11/Xlib.h>

#include <gtk/gtk.h>

#include <libxfce4util/libxfce4util.h>
#include <libxfce4ui/libxfce4ui.h>
#include <xfconf/xfconf.h>

#include <libxfce4kbd-private/xfce-shortcuts.h>
#include <libxfce4kbd-private/xfwm4-shortcut-values.h>



typedef struct
{
  const gchar *owner_name;
  const gchar *other_name;
  const gchar *message;
  const gchar *owner_button_text;
  const gchar *other_button_text;
} XfceShortcutConflictMessage;



static XfceShortcutConflictMessage conflict_messages[] = {
  { "xfwm4", "xfwm4",
    N_("This shortcut is already being used for the action '%s'. Which action do you want to use?"),
    N_("Use '%s'"), N_("Keep '%s'") },
  { "xfwm4", "commands",
    N_("This shortcut is already being used for the command '%s'. Which action do you want to use?"),
    N_("Use '%s'"), N_("Keep '%s'") },
  { "commands","commands",
    N_("This shortcut is already being used for the command '%s'. Which action do you want to use?"),
    N_("Use '%s'"), N_("Keep '%s'") },
  { "commands", "xfwm4",
    N_("This shortcut is already being used by the action '%s'. Which action do you want to use?"),
    N_("Use '%s'"), N_("Keep '%s'") },
  { 0, 0, NULL, NULL, NULL },
};



gint
xfce_shortcut_conflict_dialog (GtkWindow   *parent,
                               const gchar *owner,
                               const gchar *other,
                               const gchar *shortcut,
                               const gchar *owner_action,
                               const gchar *other_action,
                               gboolean     ignore_same_provider)
{
  gchar   *title;
  gchar   *secondary_text;
  gchar   *owner_action_name;
  gchar   *other_action_name;
  gchar   *owner_button_text;
  gchar   *other_button_text;
  gboolean handled = FALSE;
  gint     response = GTK_RESPONSE_ACCEPT;
  gint     i;

  /* Make sure to use the translations from libxfce4ui */
  xfce_textdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR, "UTF-8");

  if (g_utf8_collate (owner, other) == 0 && ignore_same_provider)
    return GTK_RESPONSE_ACCEPT;

  if (g_utf8_collate (owner, other) == 0 && g_utf8_collate (owner_action, other_action) == 0)
    {
      /* This shortcut already exists in the provider, we don't want it twice */

      /* Warn the user */
      xfce_dialog_show_warning (NULL, _("Please use another key combination."),
                                _("%s already triggers this action."), shortcut);

      return GTK_RESPONSE_REJECT;
    }

  title = g_strdup_printf (_("Conflicting actions for %s"), shortcut);

  for (i = 0; conflict_messages[i].message != NULL; ++i)
    if (g_utf8_collate (conflict_messages[i].owner_name, owner) == 0 &&
        g_utf8_collate (conflict_messages[i].other_name, other) == 0)
      {
        if (owner_action == NULL)
          owner_action_name = NULL;
        else if (g_utf8_collate (owner, "xfwm4") == 0)
          {
            gint j;

            /* We need to get the human readable string of the action name */
            for (j = 0; xfwm4_shortcut_values[j].name != NULL; ++j)
            if (G_UNLIKELY (g_str_equal (xfwm4_shortcut_values[j].feature,
                                         owner_action)))
              {
                owner_action_name =
                  g_markup_escape_text (xfwm4_shortcut_values[j].name, -1);
                break;
              }
          }
        else
          owner_action_name = g_markup_escape_text (owner_action, -1);

        if (other_action == NULL)
          other_action_name = NULL;
        else if (g_utf8_collate (other, "xfwm4") == 0)
          {
            gint j;

            /* We need to get the human readable string of the action name */
            for (j = 0; xfwm4_shortcut_values[j].name != NULL; ++j)
            if (G_UNLIKELY (g_str_equal (xfwm4_shortcut_values[j].feature,
                                         other_action)))
              {
                other_action_name =
                  g_markup_escape_text (xfwm4_shortcut_values[j].name, -1);
                break;
              }
          }
        else
          other_action_name = g_markup_escape_text (other_action, -1);

        secondary_text = g_strdup_printf (_(conflict_messages[i].message), other_action_name);

        owner_button_text = g_markup_printf_escaped (_(conflict_messages[i].owner_button_text), owner_action_name);
        other_button_text = g_markup_printf_escaped (_(conflict_messages[i].other_button_text), other_action_name);

        response = xfce_message_dialog (parent, title, GTK_STOCK_DIALOG_QUESTION,
                                        title, secondary_text,
                                        XFCE_BUTTON_TYPE_MIXED, NULL, owner_button_text, GTK_RESPONSE_ACCEPT,
                                        XFCE_BUTTON_TYPE_MIXED, NULL, other_button_text, GTK_RESPONSE_REJECT,
                                        NULL);

        g_free (other_button_text);
        g_free (owner_button_text);
        g_free (secondary_text);
        g_free (other_action_name);
        g_free (owner_action_name);

        handled = TRUE;
        break;
      }

  if (G_UNLIKELY (!handled))
    {
      xfce_message_dialog (parent, title, GTK_STOCK_DIALOG_ERROR,
                           title, _("This shortcut is already being used for something else."),
                           GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);
      response = GTK_RESPONSE_REJECT;
    }

  g_free (title);

  return response;
}
