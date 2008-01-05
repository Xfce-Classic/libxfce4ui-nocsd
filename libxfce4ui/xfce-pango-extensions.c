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

#include <pango/pango.h>

#include <libxfce4ui/xfce-pango-extensions.h>
#include <libxfce4ui/libxfce4ui-private.h>
#include <libxfce4ui/libxfce4ui-alias.h>



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
 * xfce_pango_attr_list_new:
 * @scale_factor : the font size of the label, for example #PANGO_SCALE_LARGE.
 * @style        : the style (ie. italic) of the label.
 * @weight       : the weight of the label.
 * @underline    : whether the label should be underlined.
 *
 * Creates a new pango attributes list. The attributes passed to the function
 * will be added to the list when they differ from normal.
 * The list is returned with a refcount of 1, so you need to release it
 * with pango_attr_list_unref().
 *
 * For more information see the <link linkend="pango-Text-Attributes">Pango
 * text attributes manual</link>.
 *
 * Return value: the newly created #PangoAttrList.
 **/
PangoAttrList *
xfce_pango_attr_list_new (gdouble        scale_factor,
                          PangoStyle     style,
                          PangoWeight    weight,
                          PangoUnderline underline)
{
  PangoAttrList *attr_list;

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

  return attr_list;
}



#define __XFCE_PANGO_EXTENSIONS_C__
#include <libxfce4ui/libxfce4ui-aliasdef.c>
