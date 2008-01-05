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

#if !defined (LIBXFCE4UI_COMPILATION)
#error "Only <libxfce4ui/libxfce4ui.h> can be included directly, this file is not part of the public API."
#endif

#ifndef __LIBXFCE4UI_PRIVATE_H__
#define __LIBXFCE4UI_PRIVATE_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

/* avoid copying name, nick and blurb */
#define LIBXFCE4UI_PARAM_READABLE  (G_PARAM_READABLE \
                                    | G_PARAM_STATIC_NAME \
                                    | G_PARAM_STATIC_NICK \
                                    | G_PARAM_STATIC_BLURB)
#define LIBXFCE4UI_PARAM_WRITABLE  (G_PARAM_WRITABLE \
                                    | G_PARAM_STATIC_NAME \
                                    | G_PARAM_STATIC_NICK \
                                    | G_PARAM_STATIC_BLURB)
#define LIBXFCE4UI_PARAM_READWRITE (G_PARAM_READWRITE \
                                    | G_PARAM_STATIC_NAME \
                                    | G_PARAM_STATIC_NICK \
                                    | G_PARAM_STATIC_BLURB)

/* support for canonical representations of strings */
#define I_(string) (g_intern_static_string ((string)))

/* avoid trivial g_value_get_*() function calls */
#ifdef NDEBUG
#define g_value_get_boolean(v)  (((const GValue *) (v))->data[0].v_int)
#define g_value_get_char(v)     (((const GValue *) (v))->data[0].v_int)
#define g_value_get_uchar(v)    (((const GValue *) (v))->data[0].v_uint)
#define g_value_get_int(v)      (((const GValue *) (v))->data[0].v_int)
#define g_value_get_uint(v)     (((const GValue *) (v))->data[0].v_uint)
#define g_value_get_long(v)     (((const GValue *) (v))->data[0].v_long)
#define g_value_get_ulong(v)    (((const GValue *) (v))->data[0].v_ulong)
#define g_value_get_int64(v)    (((const GValue *) (v))->data[0].v_int64)
#define g_value_get_uint64(v)   (((const GValue *) (v))->data[0].v_uint64)
#define g_value_get_enum(v)     (((const GValue *) (v))->data[0].v_long)
#define g_value_get_flags(v)    (((const GValue *) (v))->data[0].v_ulong)
#define g_value_get_float(v)    (((const GValue *) (v))->data[0].v_float)
#define g_value_get_double(v)   (((const GValue *) (v))->data[0].v_double)
#define g_value_get_string(v)   (((const GValue *) (v))->data[0].v_pointer)
#define g_value_get_param(v)    (((const GValue *) (v))->data[0].v_pointer)
#define g_value_get_boxed(v)    (((const GValue *) (v))->data[0].v_pointer)
#define g_value_get_pointer(v)  (((const GValue *) (v))->data[0].v_pointer)
#define g_value_get_object(v)   (((const GValue *) (v))->data[0].v_pointer)
#endif

G_END_DECLS

#endif /* !__LIBXFCE4UI_PRIVATE_H__ */
