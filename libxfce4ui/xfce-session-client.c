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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_MEMORY_H
#include <memory.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_LIBSM
#include <X11/SM/SMlib.h>
#include <X11/ICE/ICElib.h>
#endif

#include <libxfce4ui/xfce-session-client.h>
#include <libxfce4ui/libxfce4ui-private.h>
#include <libxfce4ui/libxfce4ui-alias.h>



#define XFCE_SESSION_CLIENT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), XFCE_TYPE_SESSION_CLIENT, XfceSessionClientPrivate))



enum
{
  SAVE_YOURSELF,  /* whether the clien should save its state */
  DIE,            /* if the session manager want to client to shut down */
  LAST_SIGNAL
};



static void     xfce_session_client_class_init          (XfceSessionClientClass *klass);
static void     xfce_session_client_init                (XfceSessionClient      *session_client);
static void     xfce_session_client_finalize            (GObject                *object);


static void     xfce_session_client_ice_error_handler    (IceConn       connection);
static gboolean xfce_session_client_ice_process_messages (GIOChannel   *channel,
                                                          GIOCondition  condition,
                                                          gpointer      client_data);
static void     xfce_session_client_ice_connection_watch (IceConn       connection,
                                                          IcePointer    client_data,
                                                          Bool          opening,
                                                          IcePointer   *watch_data);
static void     xfce_session_client_ice_init             (void);



struct _XfceSessionClientPrivate
{
  gchar *id;
};



G_DEFINE_TYPE (XfceSessionClient, xfce_session_client, G_TYPE_OBJECT);



static void
xfce_session_client_class_init (XfceSessionClientClass *klass)
{
  GObjectClass   *gobject_class;

  /* add our private data to the class */
  g_type_class_add_private (klass, sizeof (XfceSessionClientPrivate));

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = xfce_session_client_finalize;


}



static void
xfce_session_client_init (XfceSessionClientClass *session_client)
{
  /* setup the private data */
  session_client->priv = XFCE_SESSION_CLIENT_GET_PRIVATE (session_client);

  /* initialize the ice layer */
  xfce_session_client_ice_init ();
}



static void
xfce_session_client_finalize (GObject *object)
{
  XfceSessionClient *session_client = XFCE_SESSION_CLIENT (object);

  (*G_OBJECT_CLASS (xfce_session_client_parent_class)->finalize) (object);
}



static void
xfce_session_client_ice_error_handler (IceConn connection)
{
  /*
   * The I/O error handler does whatever is necessary to respond
   * to the I/O error and then returns, but it does not call
   * IceCloseConnection. The ICE connection is given a "bad IO"
   * status, and all future reads and writes to the connection
   * are ignored. The next time IceProcessMessages is called it
   * will return a status of IceProcessMessagesIOError. At that
   * time, the application should call IceCloseConnection.
   */
}



static gboolean
xfce_session_client_ice_process_messages (GIOChannel  *channel,
                                          GIOCondition condition,
                                          gpointer     client_data)
{
  IceProcessMessagesStatus status;
  IceConn                  connection = client_data;

  /* try to process pending messages */
  status = IceProcessMessages (connection, NULL, NULL);
  if (G_UNLIKELY (status == IceProcessMessagesIOError))
    {
      /* we were disconnected from the session manager */
      IceSetShutdownNegotiation (connection, False);
      IceCloseConnection (connection);
    }

  return TRUE;
}



static void
xfce_session_client_ice_connection_watch (IceConn     connection,
                                          IcePointer  client_data,
                                          Bool        opening,
                                          IcePointer *watch_data)
{
  GIOChannel *channel;
  guint       watch_id;
  gint        fd;

  if (G_LIKELY (opening))
    {
      /* determine the file descriptor */
      fd = IceConnectionNumber (connection);

      /* Make sure we don't pass on these file descriptors to an exec'd child process */
      fcntl (fd, F_SETFD, fcntl (fd, F_GETFD, 0) | FD_CLOEXEC);

      /* allocate an I/O channel to watch the connection */
      channel = g_io_channel_unix_new (fd);
      watch_id = g_io_add_watch (channel, G_IO_ERR | G_IO_HUP | G_IO_IN, xfce_session_client_ice_process_messages, connection);
      g_io_channel_unref (channel);

      /* remember the watch id */
      *watch_data = GUINT_TO_POINTER (watch_id);
    }
  else
    {
      /* remove the watch */
      watch_id = GPOINTER_TO_UINT (*watch_data);
      g_source_remove (watch_id);
    }
}



static void
xfce_session_client_ice_init (void)
{
  static gboolean initialized = FALSE;

  if (G_LIKELY (!initialized))
    {
      /* setup our custom I/O error handler */
      IceSetIOErrorHandler (xfce_session_client_ice_error_handler);

      /* add the connection watch */
      IceAddConnectionWatch (xfce_session_client_ice_connection_watch, NULL);

      initialized = TRUE;
    }
}



XfceSessionClient *
xfce_session_client_new (const gchar *session_id)
{
  XfceSessionClient *session_client;

  /* create new session client */
  session_client = g_object_new (XFCE_TYPE_SESSION_CLIENT, NULL);

  return session_client;
}

