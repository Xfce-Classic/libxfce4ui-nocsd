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

GtkWidget *xfce_gtk_button_new_mixed               (const gchar        *stock_id,
                                                    const gchar        *label) G_GNUC_MALLOC;

GtkWidget *xfce_gtk_frame_box_new                  (const gchar        *label,
                                                    GtkWidget         **container_return) G_GNUC_MALLOC;

GtkWidget *xfce_gtk_frame_box_new_with_content     (const gchar         *label,
                                                    GtkWidget           *content) G_GNUC_MALLOC;

void       xfce_gtk_window_center_on_active_screen (GtkWindow           *window);

gboolean   xfce_gtk_menu_popup_until_mapped        (GtkMenu             *menu,
                                                    GtkWidget           *parent_menu_shell,
                                                    GtkWidget           *parent_menu_item,
                                                    GtkMenuPositionFunc  func,
                                                    gpointer             data,
                                                    guint                button,
                                                    guint32              activate_time);

gboolean   xfce_widget_reparent                    (GtkWidget           *widget,
                                                    GtkWidget           *new_parent);

gchar     *xfce_icon_name_from_desktop_id          (const gchar         *desktop_id);

GIcon     *xfce_gicon_from_name                    (const gchar         *name);

G_END_DECLS

#endif /* !__XFCE_GTK_EXTENSIONS_H__ */
