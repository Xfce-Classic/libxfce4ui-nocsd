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

/**
 * SECTION:xfce-gtk-extensions
 * @title: Gtk Extensions
 * @short_description: various extensions to Gtk+
 * @stability: Stable
 * @include: libxfce4ui/libxfce4ui.h
 *
 * Common used functions for GtkWidget's that are not provided by the Gtk+ library
 **/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <gtk/gtk.h>
#include <pango/pango.h>

#include <libxfce4ui/xfce-gtk-extensions.h>
#include <libxfce4ui/xfce-gdk-extensions.h>
#include <libxfce4ui/libxfce4ui-private.h>
#include <libxfce4ui/libxfce4ui-alias.h>
#include <libxfce4util/libxfce4util.h>

/* Xfce frame padding */
#define PADDING (6)



/**
 * xfce_gtk_menu_item_fill_base:
 * @item : #GtkMenuItem which should be filled
 * @tooltip_text : Tooltip to add on the passed item, or NULL
 * @accel_path : Unique path, used to identify the accelerator, or NULL
 * @callback: (scope notified): #GCallback which will be triggered on activation, or NULL
 * @callback_param : optional callback parameter, or NULL.
 * @menu_to_append_item : #GtkMenuShell on which the item should be appended, or NULL
 *
 * internal Convenience method to fill a menu item.
 *
 **/
static void
xfce_gtk_menu_item_fill_base (GtkWidget    *item,
                              const gchar  *tooltip_text,
                              const gchar  *accel_path,
                              GCallback     callback,
                              GObject      *callback_param,
                              GtkMenuShell *menu_to_append_item)
{
  g_return_if_fail (GTK_IS_MENU_ITEM (item));

  if (tooltip_text != NULL)
    gtk_widget_set_tooltip_text (item, tooltip_text);

  /* Explicitly dont use 'gtk_menu_item_set_accel_path'
   * in order to give more control over accelerator management for non-permanent menu items */
  xfce_gtk_menu_item_set_accel_label (GTK_MENU_ITEM (item), accel_path);
  if (callback != NULL)
    g_signal_connect_swapped (G_OBJECT (item), "activate", callback, callback_param);
  if (menu_to_append_item != NULL)
    gtk_menu_shell_append (menu_to_append_item, item);
}



/**
 * xfce_gtk_menu_item_new:
 * @label_text : Label to use for the #GtkMenuItem
 * @tooltip_text : Tooltip to add on the passed item, or NULL
 * @accel_path : Unique path, used to identify the accelerator, or NULL
 * @callback: (scope notified): #GCallback which will be triggered on activation, or NULL
 * @callback_param : optional callback parameter, or NULL.
 * @menu_to_append_item : #GtkMenuShell on which the item should be appended, or NULL
 *
 * Convenience method to create a #GtkMenuItem and preconfigure it with the passed parameters.
 *
 * Return value: (transfer full): A new #GtkMenuItem.
 *
 * Since: 4.16
 **/
GtkWidget*
xfce_gtk_menu_item_new (const gchar  *label_text,
                        const gchar  *tooltip_text,
                        const gchar  *accel_path,
                        GCallback     callback,
                        GObject      *callback_param,
                        GtkMenuShell  *menu_to_append_item)
{
  GtkWidget *item;

  item = gtk_menu_item_new_with_mnemonic (label_text);
  xfce_gtk_menu_item_fill_base (item, tooltip_text, accel_path, callback, callback_param, menu_to_append_item);
  return item;
}



/**
 * xfce_gtk_image_menu_item_new_from_icon_name:
 * @label_text : Label to use for the #GtkImageMenuItem
 * @tooltip_text : Tooltip to add on the passed item, or NULL
 * @accel_path : Unique path, used to identify the accelerator, or NULL
 * @callback: (scope notified): #GCallback which will be triggered on activation, or NULL
 * @callback_param : optional callback parameter, or NULL.
 * @icon_name : name of the icon to use for the #GtkImageMenuItem, or NULL
 * @menu_to_append_item : #GtkMenuShell on which the item should be appended, or NULL
 *
 * Convenience method to create a #GtkImageMenuItem and preconfigure it with the passed parameters.
 *
 * Return value: (transfer full): A new #GtkImageMenuItem.
 *
 * Since: 4.16
 **/
GtkWidget*
xfce_gtk_image_menu_item_new_from_icon_name (const gchar  *label_text,
                                             const gchar  *tooltip_text,
                                             const gchar  *accel_path,
                                             GCallback     callback,
                                             GObject      *callback_param,
                                             const gchar  *icon_name,
                                             GtkMenuShell *menu_to_append_item)
{
  GtkWidget *image = NULL;

  image = gtk_image_new_from_icon_name (icon_name, GTK_ICON_SIZE_MENU);
  return xfce_gtk_image_menu_item_new (label_text, tooltip_text, accel_path,
                                       callback, callback_param, image, menu_to_append_item);
}



/**
 * xfce_gtk_image_menu_item_new:
 * @label_text : Label to use for the #GtkImageMenuItem
 * @tooltip_text : Tooltip to add on the passed item, or NULL
 * @accel_path : Unique path, used to identify the accelerator, or NULL
 * @callback: (scope notified): #GCallback which will be triggered on activation, or NULL
 * @callback_param : optional callback parameter, or NULL.
 * @image : a widget to set as the image for the menu item, or NULL
 * @menu_to_append_item : #GtkMenuShell on which the item should be appended, or NULL
 *
 * Convenience method to create a deprecated #GtkImageMenuItem and preconfigure it with the passed parameters.
 * In order to prevent G_GNUC_BEGIN_IGNORE_DEPRECATIONS in all xfce projects, this method can be used
 *
 * Return value: (transfer full): A new #GtkImageMenuItem.
 *
 * Since: 4.16
 **/
GtkWidget*
xfce_gtk_image_menu_item_new (const gchar  *label_text,
                              const gchar  *tooltip_text,
                              const gchar  *accel_path,
                              GCallback     callback,
                              GObject      *callback_param,
                              GtkWidget    *image,
                              GtkMenuShell *menu_to_append_item)
{
  GtkWidget *item;

  G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  item = gtk_image_menu_item_new_with_mnemonic (label_text);
  G_GNUC_END_IGNORE_DEPRECATIONS
  xfce_gtk_menu_item_fill_base (item, tooltip_text, accel_path, callback, callback_param, menu_to_append_item);
  if (image != NULL)
    {
      G_GNUC_BEGIN_IGNORE_DEPRECATIONS
      gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
      G_GNUC_END_IGNORE_DEPRECATIONS
    }
  return item;
}



/**
 * xfce_gtk_check_menu_item_new:
 * @label_text : Label to use for the #GtkCheckMenuItem
 * @tooltip_text : Tooltip to add on the passed item, or NULL
 * @accel_path : Unique path, used to identify the accelerator, or NULL
 * @callback: (scope notified): #GCallback which will be triggered on activation, or NULL
 * @callback_param : optional callback parameter, or NULL.
 * @active : boolean value indicating whether the check box is active.
 * @menu_to_append_item : #GtkMenuShell on which the item should be appended, or NULL
 *
 * Convenience method to create a #GtkCheckMenuItem and preconfigure it with the passed parameters.
 *
 * Return value: (transfer full): A new #GtkCheckMenuItem.
 *
 * Since: 4.16
 **/
GtkWidget*
xfce_gtk_check_menu_item_new (const gchar  *label_text,
                              const gchar  *tooltip_text,
                              const gchar  *accel_path,
                              GCallback     callback,
                              GObject      *callback_param,
                              gboolean      active,
                              GtkMenuShell *menu_to_append_item)
{
  GtkWidget *item;

  item = gtk_check_menu_item_new_with_mnemonic (label_text);
  xfce_gtk_menu_item_fill_base (item, tooltip_text, accel_path, NULL, NULL, menu_to_append_item);

  /* 'gtk_check_menu_item_set_active' has to be done before 'g_signal_connect_swapped', to don't trigger the callback */
  gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (item), active);
  if (callback != NULL)
    g_signal_connect_swapped (G_OBJECT (item), "toggled", callback, callback_param);

  return item;
}



/**
 * xfce_gtk_radio_menu_item_new:
 * @label_text : Label to use for the #GtkCheckMenuItem
 * @tooltip_text : Tooltip to add on the passed item, or NULL
 * @accel_path : Unique path, used to identify the accelerator, or NULL
 * @callback: (scope notified): #GCallback which will be triggered on activation, or NULL
 * @callback_param : optional callback parameter, or NULL.
 * @active : boolean value indicating whether the check box is active.
 * @menu_to_append_item : #GtkMenuShell on which the item should be appended, or NULL
 *
 * Convenience method to create a #GtkCheckMenuItem and preconfigure it with the passed parameters.
 * In order to simplify usage, a #GtkCheckMenuItem is created and drawn as radio-item
 *
 * Return value: (transfer full): A new #GtkCheckMenuItem.
 *
 * Since: 4.16
 **/
GtkWidget*
xfce_gtk_radio_menu_item_new (const gchar  *label_text,
                              const gchar  *tooltip_text,
                              const gchar  *accel_path,
                              GCallback     callback,
                              GObject      *callback_param,
                              gboolean      active,
                              GtkMenuShell *menu_to_append_item)
{
  GtkWidget *item;

  /* It's simpler to just use a gtk_check_menu_item and display it with a radio button */
  item = xfce_gtk_check_menu_item_new (label_text, tooltip_text, accel_path, callback, callback_param, active, menu_to_append_item);
  gtk_check_menu_item_set_draw_as_radio (GTK_CHECK_MENU_ITEM (item), TRUE);

  return item;
}



/**
 * xfce_gtk_menu_item_new_from_action_entry:
 * @action_entry : Label to use for the #GtkCheckMenuItem
 * @callback_param : optional callback parameter, or NULL.
 * @menu_to_append_item : #GtkMenuShell on which the item should be appended, or NULL
 *
 * Method to create a menu item from the passed action entry
 *
 * Return value: (transfer full): A new #GtkMenuItem or NULL
 *
 * Since: 4.16
 **/
GtkWidget*
xfce_gtk_menu_item_new_from_action_entry (const XfceGtkActionEntry *action_entry,
                                          GObject                  *callback_param,
                                          GtkMenuShell             *menu_to_append_item)
{
  g_return_val_if_fail (action_entry != NULL, NULL);

  if (action_entry->menu_item_type == XFCE_GTK_IMAGE_MENU_ITEM)
    {
      return xfce_gtk_image_menu_item_new_from_icon_name (action_entry->menu_item_label_text, action_entry->menu_item_tooltip_text,
                                                          action_entry->accel_path, action_entry->callback,
                                                          callback_param, action_entry->menu_item_icon_name, menu_to_append_item);
    }
  if (action_entry->menu_item_type == XFCE_GTK_MENU_ITEM)
    {
      return xfce_gtk_menu_item_new (action_entry->menu_item_label_text, action_entry->menu_item_tooltip_text,
                                     action_entry->accel_path, action_entry->callback,
                                     callback_param, menu_to_append_item);
    }
  g_warning ("xfce_gtk_menu_item_new_from_action_entry: Unknown item_type");
  return NULL;
}



/**
 * xfce_gtk_toggle_menu_item_new_from_action_entry:
 * @action_entry : Label to use for the #GtkCheckMenuItem
 * @callback_param : optional callback parameter, or NULL.
 * @menu_to_append_item : #GtkMenuShell on which the item should be appended, or NULL
 *
 * Method to create a toggle menu item from the passed action entry
 *
 * Return value: (transfer full): A new #GtkMenuItem or NULL
 *
 * Since: 4.16
 **/
GtkWidget*
xfce_gtk_toggle_menu_item_new_from_action_entry (const XfceGtkActionEntry *action_entry,
                                                 GObject                  *callback_param,
                                                 gboolean                  active,
                                                 GtkMenuShell             *menu_to_append_item)
{
  g_return_val_if_fail (action_entry != NULL, NULL);

  if (action_entry->menu_item_type == XFCE_GTK_CHECK_MENU_ITEM)
    {
      return xfce_gtk_check_menu_item_new (action_entry->menu_item_label_text, action_entry->menu_item_tooltip_text,
                                           action_entry->accel_path, action_entry->callback,
                                           callback_param, active, menu_to_append_item);
    }
  if (action_entry->menu_item_type == XFCE_GTK_RADIO_MENU_ITEM)
    {
      return xfce_gtk_radio_menu_item_new (action_entry->menu_item_label_text, action_entry->menu_item_tooltip_text,
                                           action_entry->accel_path, action_entry->callback,
                                           callback_param, active, menu_to_append_item);
    }
  g_warning ("xfce_gtk_toggle_menu_item_new_from_action_entry: Unknown item_type");
  return NULL;
}



/**
 * xfce_gtk_tool_button_new_from_action_entry:
 * @action_entry : Label to use for the #GtkTolButton
 * @callback_param : optional callback parameter, or NULL.
 * @toolbar_to_append_item : #GtkToolBar on which the item should be appended
 *
 * Method to create a toolbar button from the passed action entry
 *
 * Return value: (transfer full): A new #GtkTolButton
 *
 * Since: 4.16
 **/
GtkWidget*
xfce_gtk_tool_button_new_from_action_entry (const XfceGtkActionEntry *action_entry,
                                            GObject                  *callback_param,
                                            GtkToolbar               *toolbar_to_append_item)
{
  GtkToolItem *tool_item;
  GtkWidget   *image;

  g_return_val_if_fail (action_entry != NULL, NULL);

  image = gtk_image_new_from_icon_name (action_entry->menu_item_icon_name, GTK_ICON_SIZE_LARGE_TOOLBAR);
  tool_item = gtk_tool_button_new (image, action_entry->menu_item_label_text);
  g_signal_connect_swapped (G_OBJECT (tool_item), "clicked", action_entry->callback, callback_param);
  gtk_widget_set_tooltip_text (GTK_WIDGET (tool_item), action_entry->menu_item_tooltip_text);
  gtk_toolbar_insert (toolbar_to_append_item, tool_item, -1);
  return GTK_WIDGET (tool_item);
}



/**
 * xfce_gtk_menu_append_seperator:
 * @menu : #GtkMenuShell on which the separator should be appended
 *
 * Convenience method do add separators, used to prevent code duplication
 *
 * Since: 4.16
 **/
void
xfce_gtk_menu_append_seperator (GtkMenuShell *menu)
{
  GtkWidget *item;

  g_return_if_fail (GTK_IS_MENU_SHELL (menu));

  item = gtk_separator_menu_item_new ();
  gtk_menu_shell_append (menu, item);
}



/**
 * xfce_gtk_accel_map_add_entries:
 * @action_entries : array of action_entries to be added
 * @n_action_entries : size of the action_entries array
 *
 * Adds the default key of each ActionEntry to the accel_map, if no key was defined for the related accel_path so far.
 *
 * Since: 4.16
 **/
void
xfce_gtk_accel_map_add_entries (const XfceGtkActionEntry *action_entries,
                                guint                     n_action_entries)
{
  GtkAccelKey key;

  for (size_t i = 0; i < n_action_entries; i++)
    {
      if (action_entries[i].accel_path == NULL || g_strcmp0 (action_entries[i].accel_path, "") == 0)
        continue;

      /* If the accel path was not loaded to the acel_map via file, we add the default key for it to the accel_map */
      if (gtk_accel_map_lookup_entry (action_entries[i].accel_path, &key) == FALSE)
        {
          gtk_accelerator_parse (action_entries[i].default_accelerator, &key.accel_key, &key.accel_mods);
          gtk_accel_map_add_entry (action_entries[i].accel_path, key.accel_key, key.accel_mods);
        }
    }
}



/**
 * xfce_gtk_accel_group_connect_action_entries:
 * @accel_group   : the #GtkAccelGroup to connect to
 * @action_entries : array of action_entries to be added
 * @n_action_entries : size of the action_entries array
 * @callback_data : data which should be passed to the callback of each #XfceGtkActionEntry
 *
 * This method will connect each accel_path from the #XfceGtkActionEntry in action_entries
 * to its related callback. If the accelerator is pressed, the related callback will be called.
 *
 * Since: 4.16
 **/
void
xfce_gtk_accel_group_connect_action_entries (GtkAccelGroup            *accel_group,
                                             const XfceGtkActionEntry *action_entries,
                                             guint                     n_action_entries,
                                             gpointer                  callback_data)
{
  GClosure   *closure = NULL;

  g_return_if_fail (GTK_IS_ACCEL_GROUP (accel_group));

  for (size_t i = 0; i < n_action_entries; i++)
    {
      if (action_entries[i].accel_path == NULL || g_strcmp0 (action_entries[i].accel_path, "") == 0)
        continue;

      if (action_entries[i].callback != NULL)
        {
          closure = g_cclosure_new_swap (action_entries[i].callback, callback_data, NULL);
          gtk_accel_group_connect_by_path (accel_group, action_entries[i].accel_path, closure);
        }
    }
 }



/**
 * xfce_gtk_accel_group_disconnect_action_entries:
 * @accel_group   : the #GtkAccelGroup to connect to
 * @action_entries : array of action_entries to be added
 * @n_action_entries : size of the action_entries array
 *
 * This method will disconnect each accel_path from the #XfceGtkActionEntry in action_entries.
 *
 * Since: 4.16
 **/
void
xfce_gtk_accel_group_disconnect_action_entries (GtkAccelGroup            *accel_group,
                                                const XfceGtkActionEntry *action_entries,
                                                guint                     n_action_entries)
{
  GtkAccelKey key;

  g_return_if_fail (GTK_IS_ACCEL_GROUP (accel_group));

  for (size_t i = 0; i < n_action_entries; i++)
    {
      if (action_entries[i].accel_path == NULL || g_strcmp0 (action_entries[i].accel_path, "") == 0)
        continue;
      if (action_entries[i].callback != NULL)
        {
          if (gtk_accel_map_lookup_entry (action_entries[i].accel_path, &key) == TRUE)
            gtk_accel_group_disconnect_key (accel_group, key.accel_key, key.accel_mods);
        }
    }
 }



/**
 * xfce_gtk_get_action_entry_by_id:
 * @action_entries : array of action_entries to be searched
 * @n_action_entries : size of the action_entries array
 * @id : id of the action entry (usually enum values are used)
 *
 * Convenience method to find a specific action_entry from an array of action_entries
 *
 * Return value: (transfer none): The matching #XfceGtkActionEntry or NULL if not found
 *
 * Since: 4.16
 **/
const XfceGtkActionEntry*
xfce_gtk_get_action_entry_by_id (const XfceGtkActionEntry *action_entries,
                                 guint                     n_action_entries,
                                 guint                     id)
{
  for (size_t i = 0; i <  n_action_entries; i++)
    {
      if( action_entries[i].id == id )
          return &(action_entries[i]);
    }
  g_warning ("There is no action with the id '%i'.", id);
  return NULL;
}



/**
 * xfce_gtk_translate_action_entries:
 * @action_entries : array of action_entries to be translated
 * @n_action_entries : size of the action_entries array
 *
 * Convenience method to translate the label text and tooltip text of an array of action_entries
 *
 * Since: 4.16
 **/
void
xfce_gtk_translate_action_entries (XfceGtkActionEntry *action_entries,
                                   guint               n_action_entries)
{
  for (size_t i = 0; i <  n_action_entries; i++)
    {
      action_entries[i].menu_item_label_text = g_strdup( g_dgettext (NULL, action_entries[i].menu_item_label_text));
      action_entries[i].menu_item_tooltip_text = g_strdup( g_dgettext (NULL, action_entries[i].menu_item_tooltip_text));
    }
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
 * Return value: (transfer full): the newly created #GtkButton widget.
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

      if (stock_id != NULL && strlen(stock_id) > 0)
        {
          /* create image widget */
          image = gtk_image_new_from_icon_name (stock_id, GTK_ICON_SIZE_BUTTON);
          gtk_button_set_image (GTK_BUTTON (button), image);
        }
    }
  else
    {
      button = gtk_button_new_with_label (label);
    }

  return button;
}



/**
 * xfce_gtk_frame_box_new:
 * @label            : the text to use as the label of the frame.
 * @container_return : (out) (allow-none): return location for the frame's container.
 *
 * Creates an Xfce-styled frame. The frame is a #GtkFrame, without
 * outline and an optional bolded text label.  The contents of the
 * frame are indented on the left.
 * The return value is the #GtkFrame itself.  The @container_return is
 * a #GtkAlignment widget to which children of the frame should be added.
 *
 * See also: xfce_gtk_frame_box_new_with_content().
 *
 * Return value: (transfer full): the newly created #GtkFrame widget.
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
      gtk_label_set_yalign (GTK_LABEL (frame_label), 0.5);
      gtk_frame_set_label_widget (GTK_FRAME (frame), frame_label);
      gtk_widget_show (frame_label);
    }

/* We're ignoring this for now because we directly return the alignment
 * and who knows if our consumers want to poke at it. */
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  container = gtk_alignment_new (0.0, 0.0, 1.0, 1.0);
  gtk_alignment_set_padding (GTK_ALIGNMENT (container), PADDING, PADDING, PADDING * 3, PADDING);
  gtk_container_add (GTK_CONTAINER (frame), container);
  gtk_widget_show (container);
G_GNUC_END_IGNORE_DEPRECATIONS

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
 * Return value: (transfer full): the newly created #GtkFrame widget.
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
 * @parent_menu_shell: (allow-none): the menu shell containing the triggering menu item, or %NULL.
 * @parent_menu_item: (allow-none): the menu item whose activation triggered the popup, or %NULL.
 * @func: (scope call) (allow-none): a user supplied function used to position the menu, or %NULL.
 * @data: (allow-none): user supplied data to be passed to func.
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
 *
 * Since: 4.14
 *
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
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
        gtk_menu_popup (GTK_MENU (menu),
                        parent_menu_shell,
                        parent_menu_item,
                        func,
                        data,
                        button,
                        activate_time);
G_GNUC_END_IGNORE_DEPRECATIONS

        g_usleep (100);
    }

  return gtk_widget_get_mapped (GTK_WIDGET (menu));
}



/**
 * xfce_widget_reparent:
 * @widget: a #GtkWidget.
 * @new_parent: a #GtkContainer to move the widget into
 *
 * Moves a widget from one GtkContainer to another, handling reference
 * count issues to avoid destroying the widget.
 *
 * Return value: %TRUE if the widget could be moved, %FALSE otherwise.
 *
 * Since: 4.14
 */
gboolean
xfce_widget_reparent (GtkWidget *widget,
                      GtkWidget *new_parent)
{
  GtkWidget *parent;

  g_return_val_if_fail (GTK_IS_WIDGET (widget), FALSE);
  g_return_val_if_fail (GTK_IS_WIDGET (new_parent), FALSE);

  if (!GTK_IS_CONTAINER (new_parent))
    return FALSE;

  parent = gtk_widget_get_parent(widget);
  if (parent)
    {
      g_object_ref (widget);
      gtk_container_remove (GTK_CONTAINER(parent), widget);
      gtk_container_add (GTK_CONTAINER(new_parent), widget);
      g_object_unref (widget);

      return TRUE;
    }

  return FALSE;
}



/**
 * xfce_icon_name_from_desktop_id:
 * @desktop_id : Name of the desktop file.
 *
 * Return value: %NULL on error, else the string, which should be freed using
 *               g_free() when no longer needed.
 *
 * Since: 4.16
 **/
const gchar *
xfce_icon_name_from_desktop_id (const gchar *desktop_id)
{
    const gchar *icon_file;
    gchar *resource;
    XfceRc *rcfile;

    resource = g_strdup_printf ("applications%c%s.desktop",
                                G_DIR_SEPARATOR,
                                desktop_id);
    rcfile = xfce_rc_config_open (XFCE_RESOURCE_DATA,
                                  resource, TRUE);
    g_free (resource);

    if (rcfile && xfce_rc_has_group (rcfile, "Desktop Entry")) {
        xfce_rc_set_group (rcfile, "Desktop Entry");
        icon_file = xfce_rc_read_entry (rcfile, "Icon", NULL);
        xfce_rc_close (rcfile);
        return icon_file;
    }
    else
        return NULL;
}



/**
 * xfce_gicon_from_name:
 * @name : Name of the application.
 *
 * This function will first look for a desktop file of @name and if successful
 * use the value of the "Icon" property to return a #GIcon.
 * If no desktop file of @name is found it will fallback to returning a #GIcon
 * based on #g_themed_icon_new_with_default_fallbacks and
 * #gtk_icon_theme_lookup_by_gicon.
 *
 * Return value: a new #GThemedIcon.
 *
 * Since: 4.16
 **/
GIcon *
xfce_gicon_from_name (const gchar *name)
{
    const gchar *icon_name;
    GIcon *gicon;
    GtkIconInfo *icon_info;

    /* Check if there is a desktop file of 'name' */
    icon_name = xfce_icon_name_from_desktop_id (name);
    if (icon_name) {
        gicon = g_themed_icon_new_with_default_fallbacks (icon_name);
    }
    else {
        gicon = g_themed_icon_new_with_default_fallbacks (name);
    }

    /* As g_themed_icon_new_with_default_fallbacks always returns 'something'
       check if there's anything that matches in the icon theme */
    icon_info = gtk_icon_theme_lookup_by_gicon (gtk_icon_theme_get_default (),
                                                gicon,
                                                GTK_ICON_SIZE_BUTTON,
                                                GTK_ICON_LOOKUP_FORCE_REGULAR);

    if (icon_info)
        return gicon;
    else
        return NULL;
}



/**
 * xfce_gtk_menu_item_set_accel_label:
 * @menu_item : #GtkMenuItem on which the accel label is to set
 * @accel_path : Unique path, used to identify the accelerator, or NULL to show no accelerator
*
 * Use the passed accel_path show the related #GtkAccelLabel with the correct accelerator on the item.
 *
 * Since: 4.16
 **/
void
xfce_gtk_menu_item_set_accel_label (GtkMenuItem *menu_item,
                                    const gchar *accel_path)
{
  GtkAccelKey key;
  gboolean    found = FALSE;

  g_return_if_fail (GTK_IS_MENU_ITEM (menu_item));

  if (accel_path != NULL)
    found = gtk_accel_map_lookup_entry (accel_path, &key);

  /* Only show the relevant accelerator, do not automatically connect to the callback */
  for (GList* lp = gtk_container_get_children (GTK_CONTAINER (menu_item)); lp != NULL; lp = lp->next)
    {
      if (GTK_IS_ACCEL_LABEL (lp->data))
        {
          if (found)
            gtk_accel_label_set_accel (lp->data, key.accel_key, key.accel_mods);
          else
            gtk_accel_label_set_accel (lp->data, 0, 0);
        }

    }
}



#define __XFCE_GTK_EXTENSIONS_C__
#include <libxfce4ui/libxfce4ui-aliasdef.c>
