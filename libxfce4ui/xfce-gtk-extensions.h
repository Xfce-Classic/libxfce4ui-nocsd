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

#ifndef __XFCE_GTK_EXTENSIONS_H__
#define __XFCE_GTK_EXTENSIONS_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

/* convienent marcos for xfce_gtk_label_new_with_style */
#define xfce_gtk_label_new_italic(label)           (xfce_gtk_label_new_with_style ((label),    \
                                                    PANGO_SCALE_MEDIUM, PANGO_STYLE_ITALIC,    \
                                                    PANGO_WEIGHT_NORMAL, PANGO_UNDERLINE_NONE))
#define xfce_gtk_label_new_small_italic(label)     (xfce_gtk_label_new_with_style ((label),    \
                                                    PANGO_SCALE_SMALL, PANGO_STYLE_ITALIC,     \
                                                    PANGO_WEIGHT_NORMAL, PANGO_UNDERLINE_NONE))
#define xfce_gtk_label_new_bold(label)             (xfce_gtk_label_new_with_style ((label),    \
                                                    PANGO_SCALE_MEDIUM, PANGO_STYLE_NORMAL,    \
                                                    PANGO_WEIGHT_BOLD, PANGO_UNDERLINE_NONE))
#define xfce_gtk_label_new_big_bold(label)         (xfce_gtk_label_new_with_style ((label),    \
                                                    PANGO_SCALE_LARGE, PANGO_STYLE_NORMAL,     \
                                                    PANGO_WEIGHT_BOLD, PANGO_UNDERLINE_NONE))

GtkWidget *xfce_gtk_button_new_mixed               (const gchar     *stock_id,
                                                    const gchar     *label) G_GNUC_MALLOC;

GtkWidget *xfce_gtk_label_new_with_style           (const gchar     *label,
                                                    gdouble          scale_factor,
                                                    PangoStyle       style,
                                                    PangoWeight      weight,
                                                    PangoUnderline   underline) G_GNUC_MALLOC;

GtkWidget *xfce_gtk_frame_box_new                  (const gchar     *label,
                                                    GtkWidget      **container_return) G_GNUC_MALLOC;

GtkWidget *xfce_gtk_frame_box_new_with_content     (const gchar     *label,
                                                    GtkWidget       *content) G_GNUC_MALLOC;

GdkScreen *xfce_gtk_dialog_parse_parent            (gpointer         parent,
                                                    GtkWindow      **window_return);

void       xfce_gtk_window_center_on_active_screen (GtkWindow       *window);

G_END_DECLS

#endif /* !__XFCE_GTK_EXTENSIONS_H__ */
