/*
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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
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
      button = gtk_button_new_with_mnemonic (label);

      if (stock_id != NULL)
        {
          /* create image widget */
#if !GTK_CHECK_VERSION (3, 10, 0)
          if (g_str_has_prefix (stock_id, "gtk-"))
            image = gtk_image_new_from_stock (stock_id, GTK_ICON_SIZE_BUTTON);
          else
#endif
            image = gtk_image_new_from_icon_name (stock_id, GTK_ICON_SIZE_BUTTON);
          gtk_button_set_image (GTK_BUTTON (button), image);
        }
    }
  else
    {
#if !GTK_CHECK_VERSION (3, 10, 0)
      /* fall back to a stock button */
      button = gtk_button_new_from_stock (stock_id);
#else
      button = gtk_button_new_with_label (label);
#endif
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

  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);
  gtk_frame_set_label_align (GTK_FRAME (frame), 0.0, 1.0);

  if (G_LIKELY (label != NULL))
    {
      /* create bold label */
      markup_label = g_markup_printf_escaped ("<b>%s</b>", label);
      frame_label = gtk_label_new (markup_label);
      gtk_label_set_use_markup (GTK_LABEL (frame_label), TRUE);
      g_free (markup_label);
      gtk_misc_set_alignment (GTK_MISC (frame_label), 0.0, 0.5);
      gtk_frame_set_label_widget (GTK_FRAME (frame), frame_label);
      gtk_widget_show (frame_label);
    }

  container = gtk_alignment_new (0.0, 0.0, 1.0, 1.0);
  gtk_alignment_set_padding (GTK_ALIGNMENT (container), PADDING, PADDING, PADDING * 3, PADDING);
  gtk_container_add (GTK_CONTAINER (frame), container);
  gtk_widget_show (container);

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

  frame = xfce_gtk_frame_box_new (label, &container);
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

  gtk_window_set_screen (window, screen);

  /* gtk+ handles the centering of the window properly after resize */
  gtk_window_set_position (window, GTK_WIN_POS_CENTER);
}



/**
 * xfce_gtk_menu_popup_until_mapped:
 * @menu: a #GtkMenu.
 * @parent_menu_shell: the menu shell containing the triggering menu item, or %NULL.
 * @parent_menu_item: the menu item whose activation triggered the popup, or %NULL.
 * @func: a user supplied function used to position the menu, or %NULL.
 * @data: user supplied data to be passed to func.
 * @button: the mouse button which was pressed to initiate the event.
 * @activate_time: the time at which the activation event occurred.
 *
 * Attempts to pop up a #GtkMenu for a short duration. Unlike the original
 * gtk_menu_popup(), this function will verify that the menu has been mapped
 * or will keep trying for up to 250ms. It will also return a value indicating
 * whether the menu was eventually mapped or not. Following is an excerpt from
 * the GTK+ Documentation on #GtkMenu.
 * 
 * Displays a menu and makes it available for selection.
 *
 * Applications can use this function to display context-sensitive menus, and will
 * typically supply %NULL for the @parent_menu_shell, @parent_menu_item, @func and
 * @data parameters. The default menu positioning function will position the menu
 * at the current mouse cursor position.
 *
 * The @button parameter should be the mouse button pressed to initiate the menu
 * popup. If the menu popup was initiated by something other than a mouse button
 * press, such as a mouse button release or a keypress, button should be 0.
 *
 * The @activate_time parameter is used to conflict-resolve initiation of concurrent
 * requests for mouse/keyboard grab requests. To function properly, this needs to
 * be the timestamp of the user event (such as a mouse click or key press) that
 * caused the initiation of the popup. Only if no such event is available,
 * gtk_get_current_event_time() can be used instead.
 *
 * Return value: %TRUE if the menu could be mapped, %FALSE otherwise.
 */
gboolean
xfce_gtk_menu_popup_until_mapped (GtkMenu *menu,
                                  GtkWidget *parent_menu_shell,
                                  GtkWidget *parent_menu_item,
                                  GtkMenuPositionFunc func,
                                  gpointer data,
                                  guint button,
                                  guint32 activate_time)
{
  gint i = 0;

  g_return_val_if_fail (GTK_IS_MENU (menu), FALSE);

  while ((i++ < 2500) && (!gtk_widget_get_mapped (GTK_WIDGET (menu))))
    {
        gtk_menu_popup (GTK_MENU (menu),
                        parent_menu_shell,
                        parent_menu_item,
                        func,
                        data,
                        button,
                        activate_time);

        g_usleep (100);
    }

  return gtk_widget_get_mapped (GTK_WIDGET (menu));
}

#define __XFCE_GTK_EXTENSIONS_C__
#include <libxfce4ui/libxfce4ui-aliasdef.c>
