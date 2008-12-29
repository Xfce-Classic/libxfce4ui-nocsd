/* $Id$ */
/*-
 * Copyright (c) 2008 The Xfce Development Team
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

#include <gtk/gtk.h>
#include <gladeui/glade.h>
#include <libxfce4ui/libxfce4ui.h>



void       glade_xfce_titled_dialog_post_create        (GladeWidgetAdaptor *adaptor,
                                                        GObject            *object,
                                                        GladeCreateReason   reason);
GtkWidget *glade_xfce_titled_dialog_get_internal_child (GladeWidgetAdaptor *adaptor,
                                                        GtkDialog          *dialog,
                                                        const gchar        *name);
GList     *glade_xfce_titled_dialog_get_children       (GladeWidgetAdaptor *adaptor,
                                                        GtkDialog          *dialog);



void
glade_xfce_titled_dialog_post_create (GladeWidgetAdaptor *adaptor,
                                      GObject            *object,
                                      GladeCreateReason   reason)
{
  GtkDialog   *dialog = GTK_DIALOG (object);
  GladeWidget *widget, *vbox, *action_area;

  g_return_if_fail (XFCE_IS_TITLED_DIALOG (dialog));

  widget = glade_widget_get_from_gobject (GTK_WIDGET (dialog));
  if (G_UNLIKELY (widget == NULL))
    return;

  if (XFCE_IS_TITLED_DIALOG (dialog))
    {
      /* create the dialog vbxo */
      vbox = glade_widget_adaptor_create_internal (widget, G_OBJECT (dialog->vbox), "vbox", "dialog", FALSE, reason);
      glade_widget_remove_property (vbox, "border-width");

      /* create the action area */
      action_area = glade_widget_adaptor_create_internal (vbox, G_OBJECT (dialog->action_area), "action_area", "dialog", FALSE, reason);
      glade_widget_remove_property (action_area, "border-width");
      glade_widget_remove_property (action_area, "spacing");

      /* set properties on initial creation */
      if (reason == GLADE_CREATE_USER)
        {
          glade_widget_property_set (vbox, "spacing", 2);
          glade_widget_property_set (vbox, "size", 2);

          glade_widget_property_set (action_area, "size", 2);
          glade_widget_property_set (action_area, "layout-style", GTK_BUTTONBOX_END);
        }
    }
}



GtkWidget *
glade_xfce_titled_dialog_get_internal_child (GladeWidgetAdaptor *adaptor,
                                             GtkDialog          *dialog,
                                             const gchar        *name)
{
  GtkWidget *child = NULL;

  g_return_val_if_fail (XFCE_IS_TITLED_DIALOG (dialog), NULL);

  if (strcmp ("vbox", name) == 0)
    child = dialog->vbox;
  else if (strcmp ("action_area", name) == 0)
    child = dialog->action_area;

  return child;
}



GList *
glade_xfce_titled_dialog_get_children (GladeWidgetAdaptor *adaptor,
                                       GtkDialog          *dialog)
{
  g_return_val_if_fail (XFCE_IS_TITLED_DIALOG (dialog), NULL);

  return g_list_prepend (NULL, dialog->vbox);
}
