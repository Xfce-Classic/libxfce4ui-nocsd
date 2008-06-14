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



static void
xfce_pango_attr_list_insert (PangoAttrList  *attr_list,
                             PangoAttribute *attribute)
{
  /* set the attribute index and insert it into the list */
  attribute->start_index = 0;
  attribute->end_index = -1;
  pango_attr_list_insert (attr_list, attribute);
}



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
 * xfce_gtk_label_new_with_style:
 * @label        : the text of the label.
 * @scale_factor : the font size of the label, for example #PANGO_SCALE_LARGE.
 * @style        : the style (ie. italic) of the label.
 * @weight       : the weight of the label.
 * @underline    : whether the label should be underlined.
 *
 * Creates a new label with the given text inside it. The markup of the
 * text will be set to the style attributes passed to the function.
 * Normally you would use the convience macros like xfce_gtk_label_new_small_italic()
 * or xfce_gtk_label_new_bold().
 *
 * For more information see the <link linkend="pango-Text-Attributes">Pango
 * text attributes manual</link>.
 *
 * Return value: the newly created #GtkLabel widget.
 **/
GtkWidget *
xfce_gtk_label_new_with_style (const gchar    *label,
                               gdouble         scale_factor,
                               PangoStyle      style,
                               PangoWeight     weight,
                               PangoUnderline  underline)
{
  GtkWidget     *widget;
  PangoAttrList *attr_list;

  /* create the label */
  widget = gtk_label_new (label);

  /* create attribules list */
  attr_list = pango_attr_list_new ();
  
  /* insert the user attributes if they differ from normal */
  if (scale_factor != PANGO_SCALE_MEDIUM)
    xfce_pango_attr_list_insert (attr_list, pango_attr_scale_new (scale_factor));

  if (style != PANGO_STYLE_NORMAL)
    xfce_pango_attr_list_insert (attr_list, pango_attr_style_new (style));

  if (weight != PANGO_WEIGHT_NORMAL)
    xfce_pango_attr_list_insert (attr_list, pango_attr_weight_new (weight));

  if (underline != PANGO_UNDERLINE_NONE)
    xfce_pango_attr_list_insert (attr_list, pango_attr_underline_new (underline));

  /* set attributes list */
  gtk_label_set_attributes (GTK_LABEL (widget), attr_list);

  /* decrease our refcount */
  pango_attr_list_unref (attr_list);

  return widget;
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

  g_return_val_if_fail (container_return != NULL, NULL);

  /* create frame */
  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);
  gtk_frame_set_label_align (GTK_FRAME (frame), 0.0, 1.0);

  if (G_LIKELY (label != NULL))
    {
      /* create bold label */
      frame_label = xfce_gtk_label_new_bold (label);
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
 * xfce_gtk_dialog_parse_parent:
 * @parent        : a #GtkWidget, a #GdkScreen or %NULL.
 * @window_return : return location for the toplevel #GtkWindow or %NULL.
 *
 * Determines the screen for the @parent and returns that #GdkScreen.
 * If @window_return is not %NULL, the pointer to the #GtkWindow is
 * placed into it, or %NULL if the window could not be determined.
 *
 * If @parent is %NULL, the active #GdkScreen is set, see
 * xfce_gdk_screen_get_active() for more information.
 *
 * Return value: the #GdkScreen for the @parent.
 **/
GdkScreen *
xfce_gtk_dialog_parse_parent (gpointer    parent,
                              GtkWindow **window_return)
{
  GdkScreen *screen = NULL;
  GtkWidget *window = NULL;

  g_return_val_if_fail (parent == NULL || GDK_IS_SCREEN (parent) || GTK_IS_WIDGET (parent), NULL);

  /* determine the proper parent if one was set */
  if (parent != NULL)
    {
      if (GDK_IS_SCREEN (parent))
        {
          /* yep, that's a screen */
          screen = GDK_SCREEN (parent);
        }
      else if (GTK_IS_WIDGET (parent))
        {
          /* parent is a widget, so let's determine the toplevel window */
          window = gtk_widget_get_toplevel (GTK_WIDGET (parent));
          if (GTK_WIDGET_TOPLEVEL (window))
            {
              /* make sure the toplevel window is shown */
              gtk_widget_show_now (window);
            }
          else
            {
              /* no toplevel, not usable then */
              window = NULL;
            }

          /* determine the screen for the widget */
          screen = gtk_widget_get_screen (GTK_WIDGET (parent));
        }
    }

  /* use the active screen */
  if (screen == NULL)
    screen = xfce_gdk_screen_get_active (NULL);

  /* return the window */
  if (G_LIKELY (window_return != NULL))
    *window_return = GTK_WINDOW (window);

  return screen;
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
