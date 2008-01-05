/* $Id$ */
/*-
 * Copyright (c) 2006 Benedikt Meurer <benny@xfce.org>
 * Copyright (c) 2007 The Xfce Development Team.
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

#ifndef __XFCE_SESSION_CLIENT_H__
#define __XFCE_SESSION_CLIENT_H__

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _XfceSessionClientPrivate XfceSessionClientPrivate;
typedef struct _XfceSessionClientClass   XfceSessionClientClass;
typedef struct _XfceSessionClient        XfceSessionClient;

#define XFCE_TYPE_SESSION_CLIENT             (xfce_session_client_get_type ())
#define XFCE_SESSION_CLIENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), XFCE_TYPE_SESSION_CLIENT, XfceSessionClient))
#define XFCE_SESSION_CLIENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), XFCE_TYPE_SESSION_CLIENT, XfceSessionClientClass))
#define XFCE_IS_SESSION_CLIENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), XFCE_TYPE_SESSION_CLIENT))
#define XFCE_IS_SESSION_CLIENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), XFCE_TYPE_SESSION_CLIENT))
#define XFCE_SESSION_CLIENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), XFCE_TYPE_SESSION_CLIENT, XfceSessionClientClass))

struct _XfceSessionClientClass
{
  /*< private >*/
  GObjectClass __parent__;
};

struct _XfceSessionClient
{
  /*< private >*/
  GObject __parent__;
  XfceSessionClientPrivate *priv;
};

GType              xfce_session_client_get_type (void) G_GNUC_CONST;

XfceSessionClient *xfce_session_client_new      (const gchar *session_id) G_GNUC_MALLOC;

G_END_DECLS

#endif /* !__XFCE_SESSION_CLIENT_H__ */
