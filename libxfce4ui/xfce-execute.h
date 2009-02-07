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

#ifndef __XFCE_EXECUTE_H__
#define __XFCE_EXECUTE_H__

#include <gdk/gdk.h>

G_BEGIN_DECLS

gboolean xfce_execute_argv_on_screen (GdkScreen    *screen,
                                      const gchar  *working_directory,
                                      gchar       **argv,
                                      gchar       **envp,
                                      GSpawnFlags   flags,
                                      gboolean      startup_notify,
                                      guint32       startup_timestamp,
                                      const gchar  *icon_name,
                                      GError      **error);

gboolean xfce_execute_on_screen      (GdkScreen    *screen,
                                      const gchar  *command_line,
                                      gboolean      in_terminal,
                                      gboolean      startup_notify,
                                      GError      **error);

G_END_DECLS

#endif /* !__XFCE_EXECUTE_H__ */
