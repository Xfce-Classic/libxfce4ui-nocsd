/*
 * Copyright (c) 2007 The Xfce Development Team
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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#if !defined (LIBXFCE4UI_INSIDE_LIBXFCE4UI_H) && !defined (LIBXFCE4UI_COMPILATION)
#error "Only <libxfce4ui/libxfce4ui.h> can be included directly, this file is not part of the public API."
#endif

#ifndef __XFCE_GTK_EXTENSIONS_H__
#define __XFCE_GTK_EXTENSIONS_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

/*
 * List of item types which are supported by the XfceGtkActionEntry
 * To be extended if required
*/
typedef enum
{
  XFCE_GTK_MENU_ITEM,
  XFCE_GTK_IMAGE_MENU_ITEM,
  XFCE_GTK_CHECK_MENU_ITEM,
  XFCE_GTK_RADIO_MENU_ITEM,
} XfceGtkMenuItem;

/*
 * Replacement for the deprecated GtkActionEntry
 * The idea is to provide a fixed list of XfceGtkActionEntrys
 * - use 'xfce_gtk_translate_action_entries' once to translate the list
 * - use 'xfce_gtk_accel_group_append' once to register the provided accelerators
 * - use 'xfce_gtk_get_action_entry_by_id' to find a single entry, e.g. by using a enumeration
 * - use 'xfce_gtk_***_new_from_action_entry' to create the specific menu- or tool-items from the entry
*/
typedef struct
{
  guint            id;                     /* unique identifier for instances of this structure (you might want to use a enum) */
  const gchar     *accel_path;             /* The unique path, used to identify the accelerator */
  const gchar     *default_accelerator;    /* The default key and modifier to trigger the callback linked to the entry */

  /* menu_item data is optional, only relevant if there exists a menu_item for that accelerator */
  XfceGtkMenuItem  menu_item_type;         /* The type of the item which should be used for creation */
  gchar           *menu_item_label_text;   /* text which should be shown in the menu */
  gchar           *menu_item_tooltip_text; /* optional tooltip of the item */
  const gchar     *menu_item_icon_name;    /* optional icon name which will be used to find a image for the item */

  GCallback        callback;               /* The callback which will be triggered on activation */

} XfceGtkActionEntry;



GtkWidget                *xfce_gtk_menu_item_new                          (const gchar              *label_text,
                                                                           const gchar              *tooltip_text,
                                                                           const gchar              *accel_path,
                                                                           GCallback                 callback,
                                                                           GObject                  *callback_param,
                                                                           GtkMenuShell             *menu_to_append_item);
GtkWidget                *xfce_gtk_image_menu_item_new                    (const gchar              *label_text,
                                                                           const gchar              *tooltip_text,
                                                                           const gchar              *accel_path,
                                                                           GCallback                 callback,
                                                                           GObject                  *callback_param,
                                                                           GtkWidget                *image,
                                                                           GtkMenuShell             *menu_to_append_item);
GtkWidget                *xfce_gtk_image_menu_item_new_from_icon_name     (const gchar              *label_text,
                                                                           const gchar              *tooltip_text,
                                                                           const gchar              *accel_path,
                                                                           GCallback                 callback,
                                                                           GObject                  *callback_param,
                                                                           const gchar              *icon_name,
                                                                           GtkMenuShell             *menu_to_append_item);
GtkWidget                *xfce_gtk_check_menu_item_new                    (const gchar              *label_text,
                                                                           const gchar              *tooltip_text,
                                                                           const gchar              *accel_path,
                                                                           GCallback                 callback,
                                                                           GObject                  *callback_param,
                                                                           gboolean                  active,
                                                                           GtkMenuShell             *menu_to_append_item);
GtkWidget                *xfce_gtk_radio_menu_item_new                    (const gchar              *label_text,
                                                                           const gchar              *tooltip_text,
                                                                           const gchar              *accel_path,
                                                                           GCallback                 callback,
                                                                           GObject                  *callback_param,
                                                                           gboolean                  active,
                                                                           GtkMenuShell             *menu_to_append_item);
GtkWidget                *xfce_gtk_menu_item_new_from_action_entry        (const XfceGtkActionEntry *action_entry,
                                                                           GObject                  *callback_param,
                                                                           GtkMenuShell             *menu_to_append_item);
GtkWidget                *xfce_gtk_toggle_menu_item_new_from_action_entry (const XfceGtkActionEntry *action_entry,
                                                                           GObject                  *callback_param,
                                                                           gboolean                  active,
                                                                           GtkMenuShell             *menu_to_append_item);
GtkWidget                *xfce_gtk_tool_button_new_from_action_entry      (const XfceGtkActionEntry *action_entry,
                                                                           GObject                  *callback_param,
                                                                           GtkToolbar               *toolbar_to_append_item);
GtkAccelGroup            *xfce_gtk_accel_group_append                     (GtkAccelGroup            *accel_group,
                                                                           const XfceGtkActionEntry *action_entries,
                                                                           guint                     n_action_entries,
                                                                           gpointer                  callback_data);
const XfceGtkActionEntry *xfce_gtk_get_action_entry_by_id                 (const XfceGtkActionEntry *action_entries,
                                                                           guint                     n_action_entries,
                                                                           guint                     id);
void                      xfce_gtk_translate_action_entries               (XfceGtkActionEntry       *action_entries,
                                                                           guint                     n_action_entries);
void                      xfce_gtk_menu_append_seperator                  (GtkMenuShell             *menu);

GtkWidget                *xfce_gtk_button_new_mixed                       (const gchar              *stock_id,
                                                                           const gchar              *label) G_GNUC_MALLOC;

GtkWidget                *xfce_gtk_frame_box_new                          (const gchar              *label,
                                                                           GtkWidget               **container_return) G_GNUC_MALLOC;

GtkWidget                *xfce_gtk_frame_box_new_with_content             (const gchar               *label,
                                                                           GtkWidget                 *content) G_GNUC_MALLOC;

void                      xfce_gtk_window_center_on_active_screen         (GtkWindow                 *window);

gboolean                  xfce_gtk_menu_popup_until_mapped                (GtkMenu                   *menu,
                                                                           GtkWidget                 *parent_menu_shell,
                                                                           GtkWidget                 *parent_menu_item,
                                                                           GtkMenuPositionFunc        func,
                                                                           gpointer                   data,
                                                                           guint                      button,
                                                                           guint32                    activate_time);

gboolean                  xfce_widget_reparent                            (GtkWidget                 *widget,
                                                                           GtkWidget                 *new_parent);

const gchar              *xfce_icon_name_from_desktop_id                  (const gchar               *desktop_id);

GIcon                    *xfce_gicon_from_name                            (const gchar               *name);

G_END_DECLS

#endif /* !__XFCE_GTK_EXTENSIONS_H__ */
