/*
 * Copyright (c) 2006 Benedikt Meurer <benny@xfce.org>.
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

#ifdef HAVE_MEMORY_H
#include <memory.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <libxfce4ui/xfce-heading.h>
#include <libxfce4ui/libxfce4ui-private.h>
#include <libxfce4ui/libxfce4ui-alias.h>



#define XFCE_HEADING_BORDER      6
#define XFCE_HEADING_SPACING    12
#define XFCE_HEADING_ICON_SIZE  48


static void         _xfce_heading_finalize             (GObject          *object);
static void         _xfce_heading_realize              (GtkWidget        *widget);
static void         _xfce_heading_size_request         (GtkWidget        *widget,
                                                        GtkRequisition   *requisition);
#if GTK_CHECK_VERSION (3, 0, 0)
static void         _xfce_heading_get_preferred_width  (GtkWidget        *widget,
                                                        gint             *min,
                                                        gint             *natural);
static void         _xfce_heading_get_preferred_height (GtkWidget        *widget,
                                                        gint             *min,
                                                        gint             *natural);
static gboolean     _xfce_heading_draw                 (GtkWidget        *widget,
                                                        cairo_t          *ctx);
#else
static void         _xfce_heading_style_set            (GtkWidget        *widget,
                                                        GtkStyle         *previous_style);
static gboolean     _xfce_heading_expose_event         (GtkWidget        *widget,
                                                        GdkEventExpose   *event);
#endif
static AtkObject   *_xfce_heading_get_accessible       (GtkWidget        *widget);
static PangoLayout *_xfce_heading_make_layout          (XfceHeading      *heading);
static GdkPixbuf   *_xfce_heading_make_pixbuf          (XfceHeading      *heading);




struct _XfceHeadingClass
{
  /*< private >*/
  GtkWidgetClass __parent__;
};

struct _XfceHeading
{
  /*< private >*/
  GtkWidget       __parent__;

  GdkPixbuf       *icon;
  gchar           *icon_name;
  gchar           *subtitle;
  gchar           *title;
};



G_DEFINE_TYPE (XfceHeading, _xfce_heading, GTK_TYPE_WIDGET)



static void
_xfce_heading_class_init (XfceHeadingClass *klass)
{
  GtkWidgetClass *gtkwidget_class;
  GObjectClass   *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = _xfce_heading_finalize;

  gtkwidget_class = GTK_WIDGET_CLASS (klass);
  gtkwidget_class->realize = _xfce_heading_realize;
  gtkwidget_class->get_accessible = _xfce_heading_get_accessible;
#if GTK_CHECK_VERSION (3, 0, 0)
  gtkwidget_class->get_preferred_width = _xfce_heading_get_preferred_width;
  gtkwidget_class->get_preferred_height = _xfce_heading_get_preferred_height;
  gtkwidget_class->draw = _xfce_heading_draw;
#else
  gtkwidget_class->size_request = _xfce_heading_size_request;
  gtkwidget_class->style_set = _xfce_heading_style_set;
  gtkwidget_class->expose_event = _xfce_heading_expose_event;
#endif
}



static void
_xfce_heading_init (XfceHeading *heading)
{
  /* setup the widget parameters */
  gtk_widget_set_has_window (GTK_WIDGET (heading), TRUE);
}



static void
_xfce_heading_finalize (GObject *object)
{
  XfceHeading *heading = XFCE_HEADING (object);

  /* release the private data */
  if (G_UNLIKELY (heading->icon != NULL))
    g_object_unref (G_OBJECT (heading->icon));

  g_free (heading->icon_name);
  g_free (heading->subtitle);
  g_free (heading->title);

  (*G_OBJECT_CLASS (_xfce_heading_parent_class)->finalize) (object);
}



static void
_xfce_heading_realize (GtkWidget *widget)
{
  GdkWindowAttr  attributes;
  GtkAllocation  allocation;
  GdkWindow     *window;

  /* mark the widget as realized */
  gtk_widget_set_realized (widget, TRUE);
  gtk_widget_get_allocation (widget, &allocation);

  /* setup the window attributes */
  attributes.x = allocation.x;
  attributes.y = allocation.y;
  attributes.width = allocation.width;
  attributes.height = allocation.height;
#if !GTK_CHECK_VERSION (3, 0, 0)
  attributes.colormap = gtk_widget_get_colormap (widget);
#endif
  attributes.wclass = GDK_INPUT_OUTPUT;
  attributes.window_type = GDK_WINDOW_CHILD;
  attributes.visual = gtk_widget_get_visual (widget);
  attributes.event_mask = gtk_widget_get_events (widget)
                        | GDK_EXPOSURE_MASK;

#if GTK_CHECK_VERSION (3, 0, 0)
  /* allocate the widget window */
  window = gdk_window_new (gtk_widget_get_parent_window (widget), &attributes,
                           GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL);
  gtk_widget_set_window (widget, window);
  gdk_window_set_user_data (window, widget);
#else
  /* allocate the widget window */
  window = gdk_window_new (gtk_widget_get_parent_window (widget), &attributes,
                           GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP);
  gtk_widget_set_window (widget, window);
  gdk_window_set_user_data (window, widget);

  /* connect the style to the window */
  gtk_widget_style_attach (widget);

  /* set background color (using the base color) */
  gdk_window_set_background (gtk_widget_get_window (widget),
                             &gtk_widget_get_style (widget)->base[GTK_STATE_NORMAL]);
#endif
}



#if GTK_CHECK_VERSION (3, 0, 0)
static void
_xfce_heading_get_preferred_width (GtkWidget *widget,
                                   gint      *min,
                                   gint      *natural)
{
  GtkRequisition requisition;

  _xfce_heading_size_request (widget, &requisition);

  *min = *natural = requisition.width;
}



static void
_xfce_heading_get_preferred_height (GtkWidget *widget,
                                    gint      *min,
                                    gint      *natural)
{

  GtkRequisition requisition;

  _xfce_heading_size_request (widget, &requisition);

  *min = *natural = requisition.height;
}



static gboolean
_xfce_heading_draw (GtkWidget *widget,
                    cairo_t   *ctx)
{
  XfceHeading     *heading = XFCE_HEADING (widget);
  PangoLayout     *layout;
  GdkPixbuf       *pixbuf;
  gboolean         rtl;
  gint             width;
  gint             height;
  gint             x;
  gint             y;
  GtkAllocation    allocation;
  GtkStyleContext *context;

  gtk_widget_get_allocation (widget, &allocation);

  context = gtk_widget_get_style_context (widget);

  gtk_style_context_save (context);
  gtk_style_context_add_class (context, GTK_STYLE_CLASS_HIGHLIGHT);

  /* check if we should render from right to left */
  rtl = (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL);

  /* determine the initial horizontal position */
  x = (rtl ? allocation.width - XFCE_HEADING_BORDER : XFCE_HEADING_BORDER);

  gtk_render_background (context, ctx,
                         allocation.x, allocation.y,
                         allocation.x + allocation.width,
                         allocation.y + allocation.height);

  /* check if we have a pixbuf to render */
  pixbuf = _xfce_heading_make_pixbuf (heading);
  if (G_LIKELY (pixbuf != NULL))
    {
      /* determine the pixbuf dimensions */
      width = gdk_pixbuf_get_width (pixbuf);
      height = gdk_pixbuf_get_height (pixbuf);

      /* determine the vertical position */
      y = (allocation.height - height) / 2;

      gtk_render_icon (context, ctx,
                       pixbuf,
                       rtl ? x - width : x,
                       y);

      /* release the pixbuf */
      g_object_unref (G_OBJECT (pixbuf));

      /* advance the horizontal position */
      x += (rtl ? -1 : 1) * (width + XFCE_HEADING_SPACING);
    }

  /* generate the title layout */
  layout = _xfce_heading_make_layout (heading);
  pango_layout_get_pixel_size (layout, &width, &height);

  /* determine the vertical position */
  y = (allocation.height - height) / 2;

  gtk_render_layout (context, ctx,
                     rtl ? x - width : x, y,
                     layout);

  /* release the layout */
  g_object_unref (G_OBJECT (layout));

  gtk_style_context_restore (context);

  return FALSE;
}
#endif



static void
_xfce_heading_size_request (GtkWidget      *widget,
                            GtkRequisition *requisition)
{
  XfceHeading *heading = XFCE_HEADING (widget);
  PangoLayout *layout;
  GdkPixbuf   *pixbuf;
  gint         layout_width;
  gint         layout_height;
  gint         pixbuf_width = 0;
  gint         pixbuf_height = 0;

  /* determine the dimensions of the title text */
  layout = _xfce_heading_make_layout (heading);
  pango_layout_get_pixel_size (layout, &layout_width, &layout_height);
  g_object_unref (G_OBJECT (layout));

  /* determine the dimensions of the pixbuf */
  pixbuf = _xfce_heading_make_pixbuf (heading);
  if (G_LIKELY (pixbuf != NULL))
    {
      pixbuf_width = gdk_pixbuf_get_width (pixbuf);
      pixbuf_height = gdk_pixbuf_get_height (pixbuf);
      g_object_unref (G_OBJECT (pixbuf));
    }

  /* determine the base dimensions */
  requisition->width = layout_width + pixbuf_width + ((pixbuf_width > 0) ? XFCE_HEADING_SPACING : 0);
  requisition->height = MAX (XFCE_HEADING_ICON_SIZE, MAX (pixbuf_height, layout_height));

  /* add border size */
  requisition->width += 2 * XFCE_HEADING_BORDER;
  requisition->height += 2 * XFCE_HEADING_BORDER;
}



#if !GTK_CHECK_VERSION (3, 0, 0)
static void
_xfce_heading_style_set (GtkWidget *widget,
                         GtkStyle  *previous_style)
{
  /* check if we're already realized */
  if (gtk_widget_get_realized (widget))
    {
      /* set background color (using the base color) */
      gdk_window_set_background (gtk_widget_get_window (widget),
                                 &gtk_widget_get_style (widget)->base[GTK_STATE_NORMAL]);
    }
}



static gboolean
_xfce_heading_expose_event (GtkWidget      *widget,
                            GdkEventExpose *event)
{
  XfceHeading   *heading = XFCE_HEADING (widget);
  PangoLayout   *layout;
  GdkPixbuf     *pixbuf;
  gboolean       rtl;
  gint           width;
  gint           height;
  gint           x;
  gint           y;
  cairo_t       *cr;
  GtkAllocation  allocation;

  gtk_widget_get_allocation (widget, &allocation);

  /* check if we should render from right to left */
  rtl = (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL);

  /* determine the initial horizontal position */
  x = (rtl ? allocation.width - XFCE_HEADING_BORDER : XFCE_HEADING_BORDER);

  /* check if we have a pixbuf to render */
  pixbuf = _xfce_heading_make_pixbuf (heading);
  if (G_LIKELY (pixbuf != NULL))
    {
      /* determine the pixbuf dimensions */
      width = gdk_pixbuf_get_width (pixbuf);
      height = gdk_pixbuf_get_height (pixbuf);

      /* determine the vertical position */
      y = (allocation.height - height) / 2;

      /* render the pixbuf */
      cr = gdk_cairo_create (GDK_DRAWABLE (gtk_widget_get_window (widget)));
      gdk_cairo_set_source_pixbuf (cr, pixbuf, (rtl ? x - width : x), y);
      cairo_paint (cr);
      cairo_destroy (cr);

      /* release the pixbuf */
      g_object_unref (G_OBJECT (pixbuf));

      /* advance the horizontal position */
      x += (rtl ? -1 : 1) * (width + XFCE_HEADING_SPACING);
    }

  /* generate the title layout */
  layout = _xfce_heading_make_layout (heading);
  pango_layout_get_pixel_size (layout, &width, &height);

  /* determine the vertical position */
  y = (allocation.height - height) / 2;

  /* render the title */
  gtk_paint_layout (gtk_widget_get_style (widget),
                    gtk_widget_get_window (widget),
                    gtk_widget_get_state (widget),
                    TRUE, &event->area, widget,
                    "heading", (rtl ? x - width : x), y, layout);

  /* release the layout */
  g_object_unref (G_OBJECT (layout));

  return FALSE;
}
#endif



static AtkObject*
_xfce_heading_get_accessible (GtkWidget *widget)
{
  AtkObject *object;

  object = (*GTK_WIDGET_CLASS (_xfce_heading_parent_class)->get_accessible) (widget);
  atk_object_set_role (object, ATK_ROLE_HEADER);

  return object;
}



static PangoLayout*
_xfce_heading_make_layout (XfceHeading *heading)
{
  PangoAttribute *attribute;
  PangoAttrList  *attr_list;
  PangoLayout    *layout;
  GString        *text;
  gint            title_length = 0;

  /* generate the full text */
  text = g_string_sized_new (128);
  if (G_LIKELY (heading->title != NULL))
    {
      /* add the main title */
      title_length = strlen (heading->title);
      g_string_append (text, heading->title);
    }
  if (heading->subtitle != NULL && *heading->subtitle != '\0')
    {
      /* add an empty line between the title and the subtitle */
      if (G_LIKELY (heading->title != NULL))
        g_string_append (text, "\n");

      /* add the subtitle */
      g_string_append (text, heading->subtitle);
    }

  /* allocate and setup a new layout from the widget's context */
  layout = gtk_widget_create_pango_layout (GTK_WIDGET (heading), text->str);


  /* allocate an attribute list (large bold title) */
  attr_list = pango_attr_list_new ();
  attribute = pango_attr_scale_new (PANGO_SCALE_LARGE); /* large title */
  attribute->start_index = 0;
  attribute->end_index = title_length;
  pango_attr_list_insert (attr_list, attribute);
  attribute = pango_attr_weight_new (PANGO_WEIGHT_BOLD); /* bold title */
  attribute->start_index = 0;
  attribute->end_index = title_length;
  pango_attr_list_insert (attr_list, attribute);
  pango_layout_set_attributes (layout, attr_list);
  pango_attr_list_unref (attr_list);

  /* cleanup */
  g_string_free (text, TRUE);

  return layout;
}



static GdkPixbuf*
_xfce_heading_make_pixbuf (XfceHeading *heading)
{
  GtkIconTheme *icon_theme;
  GdkPixbuf    *pixbuf = NULL;
  GdkScreen    *screen;
  GdkPixbuf    *scaled;

  if (G_UNLIKELY (heading->icon != NULL))
    {
      /* just use the specified icon */
      pixbuf = g_object_ref (G_OBJECT (heading->icon));
    }
  else if (G_LIKELY (heading->icon_name != NULL))
    {
      /* determine the icon theme for the current screen */
      screen = gtk_widget_get_screen (GTK_WIDGET (heading));
      icon_theme = gtk_icon_theme_get_for_screen (screen);

      /* try to load the icon from the icon theme */
      pixbuf = gtk_icon_theme_load_icon (icon_theme, heading->icon_name,
                                         XFCE_HEADING_ICON_SIZE,
                                         GTK_ICON_LOOKUP_USE_BUILTIN, NULL);

      if (pixbuf != NULL
          && (gdk_pixbuf_get_height (pixbuf) > XFCE_HEADING_ICON_SIZE
              || gdk_pixbuf_get_width (pixbuf) > XFCE_HEADING_ICON_SIZE))
        {
          /* this doesn't happen often, so be stupid
           * and assume icons are always squared */
          scaled = gdk_pixbuf_scale_simple (pixbuf,
                                            XFCE_HEADING_ICON_SIZE,
                                            XFCE_HEADING_ICON_SIZE,
                                            GDK_INTERP_BILINEAR);
          g_object_unref (pixbuf);
          pixbuf = scaled;
        }

      /* cache the icon, this does not take theme changes in account,
       * but because of the only use in the titled dialog, this works
       * fine, since the window properties are emitted on icon changes */
      if (heading->icon == NULL
          && pixbuf != NULL)
        heading->icon = g_object_ref (pixbuf);
    }

  return pixbuf;
}



/**
 * _xfce_heading_set_icon:
 * @heading : a #XfceHeading.
 * @icon    : the new icon or %NULL.
 *
 * If @icon is not %NULL, @heading will display the new @icon
 * aside the title. Else, if @icon is %NULL no icon is displayed
 * unless an icon name was set with _xfce_heading_set_icon_name().
 **/
void
_xfce_heading_set_icon (XfceHeading *heading,
                        GdkPixbuf   *icon)
{
  _libxfce4ui_return_if_fail (XFCE_IS_HEADING (heading));
  _libxfce4ui_return_if_fail (icon == NULL || GDK_IS_PIXBUF (icon));

  /* check if we have a new icon */
  if (G_LIKELY (heading->icon != icon))
    {
      /* disconnect from the previous icon */
      if (G_LIKELY (heading->icon != NULL))
        g_object_unref (G_OBJECT (heading->icon));

      if (icon != NULL)
        {
          if (gdk_pixbuf_get_height (icon) > XFCE_HEADING_ICON_SIZE
              || gdk_pixbuf_get_width (icon) > XFCE_HEADING_ICON_SIZE)
            {
              /* this doesn't happen often, so be stupid
               * and assume icons are always squared */
              heading->icon = gdk_pixbuf_scale_simple (icon,
                                                       XFCE_HEADING_ICON_SIZE,
                                                       XFCE_HEADING_ICON_SIZE,
                                                       GDK_INTERP_BILINEAR);
            }
          else
            {
              heading->icon = g_object_ref (icon);
            }
        }
      else
        {
          heading->icon = NULL;
        }

      gtk_widget_queue_resize (GTK_WIDGET (heading));
    }
}



/**
 * _xfce_heading_set_icon_name:
 * @heading   : a #XfceHeading.
 * @icon_name : the new icon name, or %NULL.
 *
 * If @icon_name is not %NULL and the "icon" property is set to
 * %NULL, see _xfce_heading_set_icon(), the @heading will display
 * the name icon identified by the @icon_name.
 **/
void
_xfce_heading_set_icon_name (XfceHeading *heading,
                             const gchar *icon_name)
{
  _libxfce4ui_return_if_fail (XFCE_IS_HEADING (heading));

  /* activate the new icon name */
  g_free (heading->icon_name);
  heading->icon_name = g_strdup (icon_name);

  gtk_widget_queue_resize (GTK_WIDGET (heading));
}



/**
 * _xfce_heading_set_subtitle:
 * @heading  : a #XfceHeading.
 * @subtitle : the new subtitle for @heading, or %NULL.
 *
 * If @subtitle is not %NULL and not the empty string, it
 * will be displayed by @heading below the main title.
 **/
void
_xfce_heading_set_subtitle (XfceHeading *heading,
                            const gchar *subtitle)
{
  _libxfce4ui_return_if_fail (XFCE_IS_HEADING (heading));
  _libxfce4ui_return_if_fail (subtitle == NULL || g_utf8_validate (subtitle, -1, NULL));

  /* activate the new subtitle */
  g_free (heading->subtitle);
  heading->subtitle = g_strdup (subtitle);

  gtk_widget_queue_resize (GTK_WIDGET (heading));
}



/**
 * _xfce_heading_set_title:
 * @heading : a #XfceHeading.
 * @title   : the new title for the @heading.
 *
 * Sets the title displayed by the @heading to the
 * specified @title.
 **/
void
_xfce_heading_set_title (XfceHeading *heading,
                         const gchar *title)
{
  _libxfce4ui_return_if_fail (XFCE_IS_HEADING (heading));
  _libxfce4ui_return_if_fail (title == NULL || g_utf8_validate (title, -1, NULL));

  /* activate the new title */
  g_free (heading->title);
  heading->title = g_strdup (title);

  gtk_widget_queue_resize (GTK_WIDGET (heading));
}



#define __XFCE_HEADING_C__
#include <libxfce4ui/libxfce4ui-aliasdef.c>
