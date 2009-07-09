/* eggsmclient-private.h
 * Copyright (C) 2007 Novell, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __EGG_SM_CLIENT_PRIVATE_H__
#define __EGG_SM_CLIENT_PRIVATE_H__

#include <gdkconfig.h>
#include "eggsmclient.h"

G_BEGIN_DECLS

GKeyFile    *egg_sm_client_save_state     (EggSMClient *client);
void         egg_sm_client_quit_requested (EggSMClient *client);
void         egg_sm_client_quit_cancelled (EggSMClient *client);
void         egg_sm_client_quit           (EggSMClient *client);

#ifdef PLATFORM_OSX
GType        egg_sm_client_osx_get_type (void);
EggSMClient *egg_sm_client_osx_new      (void);
#else
GType        egg_sm_client_xsmp_get_type (void);
EggSMClient *egg_sm_client_xsmp_new      (void);
#endif
G_END_DECLS

#endif /* __EGG_SM_CLIENT_PRIVATE_H__ */
