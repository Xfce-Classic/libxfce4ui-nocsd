/*
 * Copyright (c) 2006 Benedikt Meurer <benny@xfce.org>.
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

#ifndef __XFCE_HEADING_H__
#define __XFCE_HEADING_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _XfceHeadingClass   XfceHeadingClass;
typedef struct _XfceHeading        XfceHeading;

#define XFCE_TYPE_HEADING             (_xfce_heading_get_type ())
#define XFCE_HEADING(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), XFCE_TYPE_HEADING, XfceHeading))
#define XFCE_HEADING_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), XFCE_TYPE_HEADING, XfceHeadingClass))
#define XFCE_IS_HEADING(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), XFCE_TYPE_HEADING))
#define XFCE_IS_HEADING_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), XFCE_TYPE_HEADING))
#define XFCE_HEADING_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), XFCE_TYPE_HEADING, XfceHeadingClass))

GType      _xfce_heading_get_type      (void) G_GNUC_CONST;

void       _xfce_heading_set_icon      (XfceHeading *heading,
                                        GdkPixbuf   *icon);

void       _xfce_heading_set_icon_name (XfceHeading *heading,
                                        const gchar *icon_name);

void       _xfce_heading_set_subtitle  (XfceHeading *heading,
                                        const gchar *subtitle);

void       _xfce_heading_set_title     (XfceHeading *heading,
                                        const gchar *title);

G_END_DECLS

#endif /* !__XFCE_HEADING_H__ */
