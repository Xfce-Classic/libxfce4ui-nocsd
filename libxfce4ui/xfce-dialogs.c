/* $Id$ */
/*-
 * Copyright (c) 2006-2007 Benedikt Meurer <benny@xfce.org>
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

#ifdef HAVE_STDARG_H
#include <stdarg.h>
#endif

#include <gtk/gtk.h>
#include <libxfce4util/libxfce4util.h>

#include <libxfce4ui/xfce-dialogs.h>
#include <libxfce4ui/xfce-gtk-extensions.h>
#include <libxfce4ui/xfce-gdk-extensions.h>
#include <libxfce4ui/libxfce4ui-private.h>
#include <libxfce4ui/libxfce4ui-alias.h>



static GtkWidget *
xfce_message_dialog_vnew (gpointer     parent,
                          const gchar *title,
                          const gchar *icon_stock_id,
                          const gchar *primary_text,
                          const gchar *secondary_text,
                          const gchar *first_button_text,
                          va_list      args)
{
  GtkWidget   *dialog;
  GtkWindow   *window;
  GdkScreen   *screen;
  gchar       *markup;
  GtkWidget   *image;
  GtkWidget   *button;
  const gchar *text = first_button_text;
  const gchar *label;
  const gchar *stock_id;
  gint         response;
  GdkPixbuf   *pixbuf, *scaled;
  gint         w, h;

  g_return_val_if_fail (primary_text != NULL || secondary_text != NULL, NULL);

  /* parse the parent pointer */
  screen = xfce_gtk_dialog_parse_parent (parent, &window);

  /* make the primary text large and bold */
  if (G_LIKELY (primary_text != NULL))
    markup = g_strdup_printf ("<span weight='bold' size='large'>%s</span>", primary_text);
  else
    markup = NULL;

  /* create the dialog */
  dialog = gtk_message_dialog_new_with_markup (window,
                                               GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_OTHER, GTK_BUTTONS_NONE,
                                               markup ? markup : secondary_text);

  /* cleanup */
  g_free (markup);

  /* move the dialog to the appropriate screen and center it */
  if (G_UNLIKELY (window == NULL && screen != NULL))
    {
      gtk_window_set_screen (GTK_WINDOW (dialog), screen);
      gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    }

  /* set the secondary text */
  if (primary_text != NULL && secondary_text != NULL)
    gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), secondary_text);

  /* set title */
  if (title != NULL)
    gtk_window_set_title (GTK_WINDOW (dialog), title);

  if (icon_stock_id != NULL)
    {
      /* set dialog and window icon */
      image = gtk_image_new_from_stock (icon_stock_id, GTK_ICON_SIZE_DIALOG);
      gtk_message_dialog_set_image (GTK_MESSAGE_DIALOG (dialog), image);
      gtk_widget_show (image);
      gtk_window_set_icon_name (GTK_WINDOW (dialog), icon_stock_id);
    }

  /* add buttons */
  while (text != NULL)
    {
      if (strcmp (text, XFCE_BUTTON_TYPE_MIXED) == 0)
        {
          /* get arguments */
          stock_id = va_arg (args, const gchar *);
          label = va_arg (args, const gchar *);
          response = va_arg (args, gint);

          /* add a mixed button to the dialog */
          button = xfce_gtk_button_new_mixed (stock_id, label);
          gtk_dialog_add_action_widget (GTK_DIALOG (dialog), button, response);
          gtk_widget_show (button);
        }
      else if (strcmp (text, XFCE_BUTTON_TYPE_PIXBUF) == 0)
        {
          /* get arguments */
          pixbuf = va_arg (args, GdkPixbuf *);
          label = va_arg (args, const gchar *);
          response = va_arg (args, gint);

          /* lookup real icons size for button icons */
          gtk_icon_size_lookup (GTK_ICON_SIZE_BUTTON, &w, &h);

          /* scale the pixbuf if needed */
          if (gdk_pixbuf_get_width (pixbuf) != w || gdk_pixbuf_get_height (pixbuf) != h)
            scaled = gdk_pixbuf_scale_simple (pixbuf, w, h, GDK_INTERP_BILINEAR);
          else
            scaled = NULL;

          /* create image */
          image = gtk_image_new_from_pixbuf (scaled ? scaled : pixbuf);

          /* release scaled image */
          if (scaled != NULL)
            g_object_unref (G_OBJECT (scaled));

          /* create button and add it to the dialog */
          button = gtk_button_new_with_label (label);
          gtk_button_set_image (GTK_BUTTON (button), image);
          gtk_dialog_add_action_widget (GTK_DIALOG (dialog), button, response);
          gtk_widget_show (button);
        }
      else /* stock button */
        {
          /* get arguments */
          stock_id = text;
          response = va_arg (args, gint);

          /* add a stock button to the dialog */
          gtk_dialog_add_button (GTK_DIALOG (dialog), stock_id, response);
        }

      /* get the next argument */
      text = va_arg (args, const gchar *);
    }

  return dialog;
}



/**
 * xfce_dialog_show_info:
 * @parent : a #GtkWidget, a #GdkScreen or %NULL, see xfce_gtk_dialog_parse_parent() for more information.
 * @format : the printf()-style format for the primary problem description.
 * @...    : argument list for the @format.
 *
 * Displays an information dialog on @parent using the @format as message.
 *
 * If @widget is not %NULL and @widget is part of a #GtkWindow, the function makes sure
 * that the toplevel window is visible prior to displaying the information dialog.
 */
void
xfce_dialog_show_info (gpointer     parent,
                       const gchar *format,
                       ...)
{
  va_list  args;
  gchar   *primary_text;

  /* create primary text */
  va_start (args, format);
  primary_text = g_strdup_vprintf (format, args);
  va_end (args);

  /* run dialog */
  xfce_message_dialog_run (parent, _("Information"), GTK_STOCK_DIALOG_INFO,
                           primary_text, NULL,
                           GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);

  /* cleanup */
  g_free (primary_text);
}



/**
 * xfce_dialog_show_warning:
 * @parent : a #GtkWidget, a #GdkScreen or %NULL, see xfce_gtk_dialog_parse_parent() for more information.
 * @format : the printf()-style format for the primary problem description.
 * @...    : argument list for the @format.
 *
 * Displays a warning dialog on @parent using the @format as message.
 *
 * If @widget is not %NULL and @widget is part of a #GtkWindow, the function makes sure
 * that the toplevel window is visible prior to displaying the message dialog.
 */
void
xfce_dialog_show_warning (gpointer     parent,
                          const gchar *format,
                          ...)
{
  va_list  args;
  gchar   *primary_text;

  /* create primary text */
  va_start (args, format);
  primary_text = g_strdup_vprintf (format, args);
  va_end (args);

  /* run dialog */
  xfce_message_dialog_run (parent, _("Warning"), GTK_STOCK_DIALOG_WARNING,
                           primary_text, NULL,
                           GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);

  /* cleanup */
  g_free (primary_text);
}



/**
 * xfce_dialog_show_error:
 * @parent : a #GtkWidget, a #GdkScreen or %NULL, see xfce_gtk_dialog_parse_parent() for more information.
 * @error  : a #GError, which gives a more precise description of the problem or %NULL.
 * @format : the printf()-style format for the primary problem description.
 * @...    : argument list for the @format.
 *
 * Displays an error dialog on @parent using the @format as primary message and optionally
 * displaying @error as secondary error text.
 *
 * If @parent is not %NULL and @parent is part of a #GtkWindow, the function makes sure
 * that the toplevel window is visible prior to displaying the error dialog.
 */
void
xfce_dialog_show_error (gpointer      parent,
                        const GError *error,
                        const gchar  *format,
                        ...)
{
  va_list  args;
  gchar   *primary_text;

  /* create primary text */
  va_start (args, format);
  primary_text = g_strdup_vprintf (format, args);
  va_end (args);

  /* run dialog */
  xfce_message_dialog_run (parent, _("Error"), GTK_STOCK_DIALOG_ERROR,
                           primary_text, error ? error->message : NULL,
                           GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);

  /* cleanup */
  g_free (primary_text);
}



/**
 * xfce_dialog_confirm:
 * @parent        : a #GtkWidget, a #GdkScreen or %NULL, see xfce_gtk_dialog_parse_parent() for more information.
 * @stock_id      : the stock name of the confirm button, for example #GTK_STOCK_YES or #GTK_STOCK_CLEAR.
 * @confirm_label : if non-%NULL, this text is used on the confirm button together with the @stock_id icon.
 * @format        : the printf()-style format for the dialog question.
 * @...           : argument list for the @format.
 *
 * Runs a questions dialog, that has a 'Cancel' and a 'Confirm' button. The 'Confirm'
 * button text can be set by @action if given.
 *
 * If @stock_id is equal to #GTK_STOCK_YES, the 'Cancel' button becomes a 'No' button.
 *
 * Return value: TRUE if the user confirms, else FALSE.
 */
gboolean
xfce_dialog_confirm (gpointer     parent,
                     const gchar *stock_id,
                     const gchar *confirm_label,
                     const gchar *format,
                     ...)
{
  va_list      args;
  gchar       *primary_text;
  const gchar *no_stock_id;
  gint         response_id;

  g_return_val_if_fail (stock_id != NULL || confirm_label != NULL, FALSE);

  /* create primary text */
  va_start (args, format);
  primary_text = g_strdup_vprintf (format, args);
  va_end (args);

  /* whether this will be a yes/no dialog */
  if (stock_id != NULL && strcmp (stock_id, GTK_STOCK_YES) == 0)
    no_stock_id = GTK_STOCK_NO;
  else
    no_stock_id = GTK_STOCK_CANCEL;

  /* run dialog */
  response_id = xfce_message_dialog_run (parent, _("Question"), GTK_STOCK_DIALOG_QUESTION,
                                         primary_text, NULL,
                                         no_stock_id, GTK_RESPONSE_NO,
                                         XFCE_BUTTON_TYPE_MIXED, stock_id, confirm_label, GTK_RESPONSE_YES, NULL);

  /* cleanup */
  g_free (primary_text);

  return (response_id == GTK_RESPONSE_YES);
}



/**
 * xfce_message_dialog_new:
 * @parent            : a #GtkWidget, a #GdkScreen or %NULL, see xfce_gtk_dialog_parse_parent() for more information.
 * @title             : title of the dialog, or %NULL.
 * @stock_id          : gtk stock icon name to show in the dialog.
 * @primary_text      : primary text shown in large bold font.
 * @secondary_text    : secondary text shown in normal font.
 * @first_button_text : text for the first button.
 * @...               : %NULL ended list of parameters.
 *
 * xfce_message_dialog_new() allows you to easily create Gtk+ message dialogs.
 * It accepts GTK+ stock buttons, mixed buttons (using XFCE_BUTTON_TYPE_MIXED)
 * or buttons with a #GdkPixbuf (using XFCE_BUTTON_TYPE_PIXBUF).
 *
 * The buttons are defined by @first_button_text and the next arguments in the
 * following format @type, @param1[, @param2, @param3].
 *
 * <variablelist>
 *   <varlistentry>
 *     <term><varname>XFCE_BUTTON_TYPE_MIXED</varname></term>
 *     <listitem>
 *       <para>
 *         This allows you to easily create mixed buttons in a dialog.
 *         @param1 is used for the stock_id, @param2 for the label and
 *         @param3 for the response_id. See also xfce_gtk_button_new_mixed().
 *       </para>
 *     </listitem>
 *   </varlistentry>
 *   <varlistentry>
 *     <term><varname>XFCE_BUTTON_TYPE_PIXBUF</varname></term>
 *     <listitem>
 *       <para>
 *         Creates a button with the #GdkPixbuf as button icon.
 *         @param1 is the #GdkPixuf, @param2 for the label and
 *         @param3 for the response_id.
 *       </para>
 *     </listitem>
 *   </varlistentry>
 *   <varlistentry>
 *     <term>Stock Buttons</term>
 *     <listitem>
 *       <para>
 *         When the variables above were not matched, the button type
 *         will be a stock button. @type will be the stock id, @param1
 *         is used for the response_id.
 *       </para>
 *     </listitem>
 *   </varlistentry>
 * </variablelist>
 *
 * To clarify this behaviour see the example below. We create a dialog with
 * two stock buttons, a #GdkPixbuf button and a mixed button.
 *
 * <example>
 * <title>Creating a Xfce Message Dialog</title>
 * <programlisting>
 * GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_size (filename, 24, 24);
 *
 * GtkWidget *dialog = xfce_message_dialog (parent, "Question",
 *                                          GTK_STOCK_DIALOG_QUESTION,
 *                                          "There are unsaved modifications",
 *                                          "The menu has been modified, do you want to save it before quitting?",
 *                                          GTK_STOCK_SAVE, GTK_RESPONSE_YES,
 *                                          XFCE_BUTTON_TYPE_MIXED, GTK_STOCK_DELETE, "Forget modifications", GTK_RESPONSE_APPLY,
 *                                          XFCE_BUTTON_TYPE_PIXBUF, pixbuf, "Quit", GTK_RESPONSE_NO,
 *                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
 *                                          NULL);
 *
 * g_object_unref (G_OBJECT (pixbuf));
 * </programlisting>
 * </example>
 *
 * Return value: A new #GtkMessageDialog.
 **/
GtkWidget *
xfce_message_dialog_new (gpointer     parent,
                         const gchar *title,
                         const gchar *stock_id,
                         const gchar *primary_text,
                         const gchar *secondary_text,
                         const gchar *first_button_text,
                         ...)
{
  va_list    args;
  GtkWidget *dialog;

  /* create dialog */
  va_start (args, first_button_text);
  dialog = xfce_message_dialog_vnew (parent, title, stock_id, primary_text, secondary_text, first_button_text, args);
  va_end (args);

  return dialog;
}



/**
 * xfce_message_dialog_run:
 * @parent            : a #GtkWidget, a #GdkScreen or %NULL, see xfce_gtk_dialog_parse_parent() for more information.
 * @title             : title of the dialog, or %NULL.
 * @stock_id          : gtk stock icon name to show in the dialog.
 * @primary_text      : primary text shown in large bold font.
 * @secondary_text    : secondary text shown in normal font.
 * @first_button_text : text for the first button.
 * @...               : %NULL ended list of parameters.
 *
 * Create a new dialog as in xfce_message_dialog_new(), then runs the
 * dialog and return the response id selected by the user.
 *
 * See xfce_message_dialog_new() for more information.
 *
 * Returns: the selected response id.
 **/
gint
xfce_message_dialog_run (gpointer     parent,
                         const gchar *title,
                         const gchar *stock_id,
                         const gchar *primary_text,
                         const gchar *secondary_text,
                         const gchar *first_button_text,
                         ...)
{
  va_list    args;
  GtkWidget *dialog;
  gint       response_id;

  /* create dialog */
  va_start (args, first_button_text);
  dialog = xfce_message_dialog_vnew (parent, title, stock_id, primary_text, secondary_text, first_button_text, args);
  va_end (args);

  /* run the dialog */
  response_id = gtk_dialog_run (GTK_DIALOG (dialog));

  /* hide */
  gtk_widget_hide (dialog);

  /* destroy */
  gtk_widget_destroy (dialog);

  return response_id;
}



#define __XFCE_DIALOGS_C__
#include <libxfce4ui/libxfce4ui-aliasdef.c>
