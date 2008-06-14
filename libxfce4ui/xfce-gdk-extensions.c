/* $Id$ */
/*-
 * Copyright (c) 2003-2007 Benedikt Meurer <benny@xfce.org>
 * Copyright (c) 2007      The Xfce Development Team
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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <libxfce4ui/xfce-gdk-extensions.h>
#include <libxfce4ui/libxfce4ui-private.h>
#include <libxfce4ui/libxfce4ui-alias.h>

#ifdef GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#endif



/**
 * xfce_gdk_pixbuf_new_from_inline_at_size:
 * @data   : byte data containing a serialized #GdkPixdata structure.
 * @width  : the width of the returned pixbuf or -1 to not constrain the width.
 * @height : the height of the returned pixbuf or -1 to not constrain the height.
 *
 * Creates a #GdkPixbuf from a flat representation that is suitable
 * for storing as inline data in a program. The image will be scaled
 * to fit in the requested size, preserving the image's aspect ratio.
 *
 * See also: gdk_pixbuf_new_from_inline(), gdk_pixbuf_scale_simple().
 *
 * Return value: a newly-created pixbuf with a reference count of 1,
 *               or %NULL on failure.  This data must be freed with
 *               g_object_unref() after use.
 **/
GdkPixbuf *
xfce_gdk_pixbuf_new_from_inline_at_size (const guint8 *data,
                                         gint          width,
                                         gint          height)
{
  GdkPixbuf *pixbuf, *scaled;

  /*create a pixbuf from the inline data */
  pixbuf = gdk_pixbuf_new_from_inline (-1, data, FALSE, NULL);

  if (G_LIKELY (pixbuf != NULL))
    {
      /* check pixbuf size */
      if ((width > 0 && gdk_pixbuf_get_width (pixbuf) != width)
          || (height > 0 && gdk_pixbuf_get_height (pixbuf) != height))
        {
          /* scale pixbuf */
          scaled = gdk_pixbuf_scale_simple (pixbuf,
                                            width > 0 ? width : gdk_pixbuf_get_width (pixbuf),
                                            height > 0 ? height : gdk_pixbuf_get_height (pixbuf),
                                            GDK_INTERP_BILINEAR);

          /* release the old pixbuf */
          g_object_unref (G_OBJECT (pixbuf));

          /* set */
          pixbuf = scaled;
        }
    }

  return pixbuf;
}



/**
 * xfce_gdk_screen_get_active:
 * @monitor_return : Address to store the monitor number to or %NULL.
 *
 * Returns the currently active #GdkScreen, that is, the screen which
 * currently contains the pointer. If no active screen was found, the
 * default #GdkScreen is returned.
 *
 * Return value: the currently active #GdkScreen.
 **/
GdkScreen *
xfce_gdk_screen_get_active (gint *monitor_return)
{
#ifdef GDK_WINDOWING_X11
  GdkScreen *screen;
  Window     child;
	Window     root;
  GSList    *displays;
  GSList    *lp;
	guint      xmask;
	gint       rootx, rooty;
	gint       winx, winy;
  gint       n;

  /* determine the list of active displays */
  displays = gdk_display_manager_list_displays (gdk_display_manager_get ());
  for (lp = displays; lp != NULL; lp = lp->next)
    {
      /* check all screens on this display */
      for (n = 0; n < gdk_display_get_n_screens (lp->data); ++n)
        {
          /* check if this screen contains the pointer */
          screen = gdk_display_get_screen (lp->data, n);
          if (XQueryPointer (GDK_SCREEN_XDISPLAY (screen),
                             GDK_DRAWABLE_XID (gdk_screen_get_root_window (screen)),
                             &root, &child, &rootx, &rooty, &winx, &winy, &xmask))
            {
              /* return the monitor number */
              if (monitor_return)
                *monitor_return = gdk_screen_get_monitor_at_point (screen, rootx, rooty);
              
              /* yap, this screen contains the pointer, hence it's the active screen */
              goto out;
            }
        }
    }

  /* fallback to the default screen */
  screen = gdk_screen_get_default ();
  
  /* no monitor was found */
  if (monitor_return)
    *monitor_return = 0;

out:
  /* release the displays */
  g_slist_free (displays);

  return screen;
#else
  /* dunno what to do on non-X11 window systems */
  return gdk_screen_get_default ();
#endif
}



#define __XFCE_GDK_EXTENSIONS_C__
#include <libxfce4ui/libxfce4ui-aliasdef.c>
