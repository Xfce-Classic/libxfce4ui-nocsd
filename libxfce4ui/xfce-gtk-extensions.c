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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#include <pango/pango.h>

#include <libxfce4ui/xfce-gtk-extensions.h>
#include <libxfce4ui/xfce-gdk-extensions.h>
#include <libxfce4ui/libxfce4ui-private.h>
#include <libxfce4ui/libxfce4ui-alias.h>

/* Xfce frame padding */
#define PADDING (6)



/**
 * xfce_gtk_button_new_mixed:
 * @stock_id : the name of the stock item.
 * @label    : the text of the button, with an underscore in front of
 *             the mnemonic character.
 *
 * Creates a new #GtkButton containing a mnemonic label and a stock icon.
 * The @stock_id could be something like #GTK_STOCK_OK or #GTK_STOCK_APPLY.
 *
 * When the @stock_id is %NULL a normal mnemonic button will be created,
 * when @label is %NULL a stock button will be created. This behaviour
 * is added for xfce_message_dialog_new().
 *
 * Return value: the newly created #GtkButton widget.
 **/
GtkWidget *
xfce_gtk_button_new_mixed (const gchar *stock_id,
                           const gchar *label)
{
  GtkWidget *button;
  GtkWidget *image;

  g_return_val_if_fail (stock_id != NULL || label != NULL, NULL);

  if (label != NULL)
    {
      /* create button */
      button = gtk_button_new_with_mnemonic (label);

      if (stock_id != NULL)
        {
          /* create image widget */
          image = gtk_image_new_from_stock (stock_id, GTK_ICON_SIZE_BUTTON);
          gtk_button_set_image (GTK_BUTTON (button), image);
        }
    }
  else
    {
      /* fall back to a stock button */
      button = gtk_button_new_from_stock (stock_id);
    }

  return button;
}



/**
 * xfce_gtk_frame_box_new:
 * @label            : the text to use as the label of the frame.
 * @container_return : return location for the frame's container.
 *
 * Creates an Xfce-styled frame. The frame is a #GtkFrame, without
 * outline and an optional bolded text label.  The contents of the
 * frame are indented on the left.
 * The return value is the #GtkFrame itself.  The @container_return is
 * a #GtkAlignment widget to which children of the frame should be added.
 *
 * See also: xfce_gtk_frame_box_new_with_content().
 *
 * Return value: the newly created #GtkFrame widget.
 **/
GtkWidget *
xfce_gtk_frame_box_new (const gchar  *label,
                        GtkWidget   **container_return)
{
  GtkWidget *frame;
  GtkWidget *frame_label;
  GtkWidget *container;
  gchar     *markup_label;

  g_return_val_if_fail (container_return != NULL, NULL);

  /* create frame */
  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);
  gtk_frame_set_label_align (GTK_FRAME (frame), 0.0, 1.0);

  if (G_LIKELY (label != NULL))
    {
      /* create bold label */
      markup_label = g_strdup_printf ("<b>%s</b>", label);
      frame_label = gtk_label_new (markup_label);
      g_free (markup_label);
      gtk_misc_set_alignment (GTK_MISC (frame_label), 0.0, 0.5);
      gtk_frame_set_label_widget (GTK_FRAME (frame), frame_label);
      gtk_widget_show (frame_label);
    }

  /* create the container */
  container = gtk_alignment_new (0.0, 0.0, 1.0, 1.0);
  gtk_alignment_set_padding (GTK_ALIGNMENT (container), PADDING, PADDING, PADDING * 3, PADDING);
  gtk_container_add (GTK_CONTAINER (frame), container);
  gtk_widget_show (container);

  /* return container */
  if (G_LIKELY (container_return != NULL))
    *container_return = container;

  return frame;
}



/**
 * xfce_gtk_frame_box_new_with_content:
 * @label   : the text to use as the label of the frame.
 * @content : the #GtkWidget to put inside the frame.
 *
 * Creates a widget with xfce_gtk_frame_box_new() and adds the
 * @content #GtkWidget to the frame.
 *
 * Return value: the newly created #GtkFrame widget.
 **/
GtkWidget *
xfce_gtk_frame_box_new_with_content (const gchar *label,
                                     GtkWidget   *content)
{
  GtkWidget *frame;
  GtkWidget *container;

  /* create frame */
  frame = xfce_gtk_frame_box_new (label, &container);

  /* add content */
  gtk_container_add (GTK_CONTAINER (container), content);

  return frame;
}



/**
 * xfce_gtk_window_center_on_active_screen:
 * @window: the #GtkWindow to center.
 *
 * Determines the screen that contains the pointer and centers the
 * @window on it. If it failes to determine the current pointer position,
 * @window is centered on the default screen.
 *
 * This function only works properly if you call it before realizing the
 * window and you haven't set a fixed window position using gtk_window_move().
 *
 * See also: xfce_gdk_screen_get_active().
 */
void
xfce_gtk_window_center_on_active_screen (GtkWindow *window)
{
  GdkScreen *screen;

  g_return_if_fail (GTK_IS_WINDOW (window));

  /* get the screen with the pointer */
  screen = xfce_gdk_screen_get_active (NULL);

  /* set the window screen */
  gtk_window_set_screen (window, screen);

  /* gtk+ handles the centering of the window properly after resize */
  gtk_window_set_position (window, GTK_WIN_POS_CENTER);
}



#define __XFCE_GTK_EXTENSIONS_C__
#include <libxfce4ui/libxfce4ui-aliasdef.c>
