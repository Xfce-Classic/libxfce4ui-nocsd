/* $Id$ */
/*-
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
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#if !defined (LIBXFCE4UI_INSIDE_LIBXFCE4UI_H) && !defined (LIBXFCE4UI_COMPILATION)
#error "Only <libxfce4ui/libxfce4ui.h> can be included directly, this file is not part of the public API."
#endif

#ifndef __XFCE_DIALOGS_H__
#define __XFCE_DIALOGS_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define XFCE_BUTTON_TYPE_MIXED  "button-mixed"
#define XFCE_BUTTON_TYPE_PIXBUF "button-pixbuf"

void       xfce_dialog_show_info          (GtkWindow    *parent,
                                           const gchar  *secondary_text,
                                           const gchar  *primary_format,
                                           ...) G_GNUC_PRINTF (3, 4);

void       xfce_dialog_show_warning       (GtkWindow    *parent,
                                           const gchar  *secondary_text,
                                           const gchar  *primary_format,
                                           ...) G_GNUC_PRINTF (3, 4);

void       xfce_dialog_show_error         (GtkWindow    *parent,
                                           const GError *error,
                                           const gchar  *primary_format,
                                           ...) G_GNUC_PRINTF (3, 4);

gboolean   xfce_dialog_confirm            (GtkWindow    *parent,
                                           const gchar  *stock_id,
                                           const gchar  *confirm_label,
                                           const gchar  *secondary_text,
                                           const gchar  *primary_format,
                                           ...) G_GNUC_PRINTF (5, 6);
                                     
GtkWidget *xfce_message_dialog_new_valist (GtkWindow   *parent,
                                           const gchar *title,
                                           const gchar *icon_stock_id,
                                           const gchar *primary_text,
                                           const gchar *secondary_text,
                                           const gchar *first_button_text,
                                           va_list      args) G_GNUC_MALLOC;

GtkWidget *xfce_message_dialog_new        (GtkWindow    *parent,
                                           const gchar  *title,
                                           const gchar  *stock_id,
                                           const gchar  *primary_text,
                                           const gchar  *secondary_text,
                                           const gchar  *first_button_text,
                                           ...) G_GNUC_NULL_TERMINATED G_GNUC_MALLOC;

gint       xfce_message_dialog            (GtkWindow    *parent,
                                           const gchar  *title,
                                           const gchar  *stock_id,
                                           const gchar  *primary_text,
                                           const gchar  *secondary_text,
                                           const gchar  *first_button_text,
                                           ...) G_GNUC_NULL_TERMINATED;

G_END_DECLS

#endif /* !__XFCE_DIALOGS_H__ */
