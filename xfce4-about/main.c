/*
 * Copyright (C) 2019 Xfce Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <gtk/gtk.h>
#include <libxfce4util/libxfce4util.h>
#include <libxfce4ui/libxfce4ui.h>

#include "contributors.h"
#include "translators.h"
#include "about-dialog-ui.h"

#ifdef HAVE_GLIBTOP
#include "system-info.h"
#endif

#define MARGIN 20



typedef struct
{
  const gchar *name;
  const gchar *display_name;
  const gchar *description;
}
AboutModules;



static gboolean     opt_version = FALSE;
static GOptionEntry opt_entries[] =
{
  { "version", 'V', G_OPTION_FLAG_IN_MAIN, G_OPTION_ARG_NONE, &opt_version, N_("Version information"), NULL },
  { NULL }
};


#ifdef HAVE_GLIBTOP
static void
xfce_about_system (GtkBuilder *builder)
{
  GObject *label;
  GObject *vendor_info;
  glibtop_mem mem;
  const glibtop_sysinfo *info;
  g_autofree char *device_text = NULL;
  g_autofree char *cpu_text = NULL;
  g_autofree char *memory_text = NULL;
  g_autofree char *os_name_text = NULL;
  g_autofree char *os_type_text = NULL;

  label = gtk_builder_get_object (builder, "device");
  device_text = get_system_info (DEVICE_NAME);
  gtk_label_set_text (GTK_LABEL (label), device_text ? device_text : "");

  label = gtk_builder_get_object (builder, "osname");
  os_name_text = get_os_name ();
  gtk_label_set_text (GTK_LABEL (label), os_name_text ? os_name_text : "");

  label = gtk_builder_get_object (builder, "ostype");
  os_type_text = get_system_info (ARCH);
  gtk_label_set_text (GTK_LABEL (label), os_type_text ? os_type_text : "");

  label = gtk_builder_get_object (builder, "xfce-version");
  gtk_label_set_text (GTK_LABEL (label), xfce_version_string ());

  label = gtk_builder_get_object (builder, "vendor-info");
  vendor_info = gtk_builder_get_object (builder, "vendor-info-label");
#ifdef VENDOR_INFO
  gtk_label_set_text (GTK_LABEL (label), VENDOR_INFO);
#else
  gtk_widget_hide (GTK_WIDGET (vendor_info));
  gtk_widget_hide (GTK_WIDGET (label));
#endif

  label = gtk_builder_get_object (builder, "cpu");
  info = glibtop_get_sysinfo ();
  cpu_text = get_cpu_info (info);
  gtk_label_set_markup (GTK_LABEL (label), cpu_text ? cpu_text : "");

  label = gtk_builder_get_object (builder, "memory");
  glibtop_get_mem (&mem);
  memory_text = g_format_size_full (mem.total, G_FORMAT_SIZE_IEC_UNITS);
  gtk_label_set_text (GTK_LABEL (label), memory_text ? memory_text : "");
}
#endif



static void
xfce_about_about (GtkTextBuffer *buffer)
{
  guint                i;
  AboutModules        *info;
  GtkTextTag          *bold;
  GtkTextTag          *indent;
  GtkTextIter          end;
  gchar               *str;
  static AboutModules  xfce_about_info[] =
    {
      { "xfwm4",
        N_("Window Manager"),
        N_("Handles the placement of windows on the screen.")
      },
      { "xfce4-panel",
        N_("Panel"),
        N_("Program launchers, window buttons, applications menu, "
           "workspace switcher and more.")
      },
      { "xfdesktop",
        N_("Desktop Manager"),
        N_("Sets the background color or image with optional application menu "
           "or icons for minimized applications or launchers, devices and folders.")
      },
      { "thunar",
        N_("File Manager"),
        N_("A modern file manager for the Unix/Linux desktop, aiming to "
           "be easy-to-use and fast.")
      },
      { "thunar-volman",
        N_("Volume manager"),
        N_("Automatic management of removable drives and media for Thunar.")
      },
      { "xfce4-session",
        N_("Session Manager"),
        N_("Restores your session on startup and allows you to shutdown "
           "the computer from Xfce.")
      },
      { "xfce4-settings",
        N_("Setting System"),
        N_("Configuration system to control various aspects of the desktop "
           "like appearance, display, keyboard and mouse settings.")
      },
      { "xfce4-appfinder",
        N_("Application Finder"),
        N_("Shows the applications installed on your system in categories, "
           "so you can quickly find and launch them.")
      },
      { "xfconf",
        N_("Settings Daemon"),
        N_("D-Bus-based configuration storage system.")
      },
      { "garcon",
        N_("A menu library"),
        N_("A freedesktop.org compliant menu implementation based "
           "on GLib and GIO.")
      },
      { "tumbler",
        N_("Thumbnails service"),
        N_("Thumbnail service implementing the thumbnail management D-Bus specification.")
      }
    };

  g_return_if_fail (GTK_IS_TEXT_BUFFER (buffer));

  gtk_text_buffer_insert_at_cursor (buffer,
      _("Xfce is a collection of programs that together provide a "
        "full-featured desktop environment. The following programs "
        "are part of the Xfce core:"), -1);
  gtk_text_buffer_get_end_iter (buffer, &end);

  bold = gtk_text_buffer_create_tag (buffer, "bold",
                                     "weight", PANGO_WEIGHT_BOLD, NULL);

  indent = gtk_text_buffer_create_tag (buffer, "indent",
                                       "left-margin", MARGIN, NULL);

  for (i = 0; i < G_N_ELEMENTS (xfce_about_info); i++)
    {
      info = xfce_about_info + i;

      str = g_strdup_printf ("\n\n%s (%s)\n", _(info->display_name), info->name);
      gtk_text_buffer_insert_with_tags (buffer, &end, str, -1, bold, NULL);
      g_free (str);

      gtk_text_buffer_insert_with_tags (buffer, &end, _(info->description), -1, indent, NULL);
    }

  gtk_text_buffer_insert (buffer, &end, "\n\n", -1);
  gtk_text_buffer_insert (buffer, &end,
      _("Xfce is also a development platform providing several libraries, "
        "that help programmers create applications that fit in well "
        "with the desktop environment."), -1);

  gtk_text_buffer_insert (buffer, &end, "\n\n", -1);
  gtk_text_buffer_insert (buffer, &end,
      _("Xfce components are licensed under free or open source "
        "licences; GPL or BSDL for applications and LGPL or BSDL for "
        "libraries. Look at the documentation, the source code or the "
        "Xfce website (https://www.xfce.org) for more information."), -1);

  gtk_text_buffer_insert (buffer, &end, "\n\n", -1);
  gtk_text_buffer_insert (buffer, &end,
      _("Thank you for your interest in Xfce."), -1);

  gtk_text_buffer_insert (buffer, &end, "\n\n\t- ", -1);
  gtk_text_buffer_insert (buffer, &end,
      _("The Xfce Development Team"), -1);

  gtk_text_buffer_insert (buffer, &end, "\n", -1);
}



static void
xfce_about_credits_translators (GtkTextBuffer *buffer,
                                GtkTextIter   *end)
{
  guint                 i;
  GtkTextTag           *italic;
  GtkTextTag           *language;
  const TranslatorInfo *member;
  const TranslatorTeam *team;
  gchar                *str;
  GtkTextTag           *coordinator;

  language = gtk_text_buffer_create_tag (buffer, "language",
                                         "weight", PANGO_WEIGHT_BOLD,
                                         "left-margin", MARGIN,
                                         "indent", -MARGIN, NULL);

  coordinator = gtk_text_buffer_create_tag (buffer, "italic",
                                            "style", PANGO_STYLE_ITALIC, NULL);

  for (i = 0; i < G_N_ELEMENTS (xfce_translators); i++)
    {
      team = xfce_translators + i;

      str = g_strdup_printf ("%s [%s]:\n", team->name, team->code);
      gtk_text_buffer_insert_with_tags (buffer, end, str, -1, language, NULL);
      g_free (str);

      for (member = team->members; member->name != NULL; member++)
        {
          italic = member->is_coordinator ? coordinator : NULL;

          gtk_text_buffer_insert_with_tags (buffer, end, "\t", -1, italic, NULL);
          gtk_text_buffer_insert_with_tags (buffer, end, member->name, -1, italic, NULL);
          gtk_text_buffer_insert_with_tags (buffer, end, " <", -1, italic, NULL);
          gtk_text_buffer_insert_with_tags (buffer, end, member->email, -1, italic, NULL);
          gtk_text_buffer_insert_with_tags (buffer, end, ">\n", -1, italic, NULL);

        }

      gtk_text_buffer_insert (buffer, end, "\n", -1);
    }
}



static void
xfce_about_credits (GtkTextBuffer *buffer)
{
  guint                   i;
  GtkTextTag             *title;
  GtkTextTag             *indent;
  GtkTextIter             end;
  const ContributorGroup *group;
  const ContributorInfo  *user;

  g_return_if_fail (GTK_IS_TEXT_BUFFER (buffer));

  title = gtk_text_buffer_create_tag (buffer, "title",
                                      "scale", 1.1,
                                      "weight", PANGO_WEIGHT_BOLD, NULL);

  indent = gtk_text_buffer_create_tag (buffer, "indent",
                                       "left-margin", MARGIN,
                                       "indent", -MARGIN, NULL);

  gtk_text_buffer_get_end_iter (buffer, &end);

  for (i = 0; i < G_N_ELEMENTS (xfce_contributors); i++)
    {
      group = xfce_contributors + i;

      gtk_text_buffer_insert_with_tags (buffer, &end, _(group->name), -1, title, NULL);
      gtk_text_buffer_insert (buffer, &end, "\n", -1);

      if (group->contributors != NULL)
        {
          for (user = group->contributors; user->name != NULL; user++)
            {
              gtk_text_buffer_insert_with_tags (buffer, &end, user->name, -1, indent, NULL);
              gtk_text_buffer_insert (buffer, &end, " <", -1);
              gtk_text_buffer_insert (buffer, &end, user->email, -1);
              gtk_text_buffer_insert (buffer, &end, ">\n", -1);
            }
        }
      else
        {
          /* add the translators */
          xfce_about_credits_translators (buffer, &end);
        }

      gtk_text_buffer_insert (buffer, &end, "\n", -1);
    }

  gtk_text_buffer_insert (buffer, &end,
      _("If you know of anyone missing from this list; don't hesitate and "
        "file a bug on <https://bugzilla.xfce.org> ."), -1);
  gtk_text_buffer_insert (buffer, &end, "\n\n", -1);
  gtk_text_buffer_insert_with_tags (buffer, &end,
      _("Thanks to all who helped making this software available!"), -1, title, NULL);

  gtk_text_buffer_insert (buffer, &end, "\n", -1);
}



static void
xfce_about_copyright (GtkTextBuffer *buffer)
{
  GtkTextIter end;

  g_return_if_fail (GTK_IS_TEXT_BUFFER (buffer));

  gtk_text_buffer_get_end_iter (buffer, &end);

  gtk_text_buffer_insert (buffer, &end,
      _("Xfce 4 is copyright Olivier Fourdan (fourdan@xfce.org). The different "
        "components are copyrighted by their respective authors."), -1);

  gtk_text_buffer_insert (buffer, &end, "\n\n", -1);
  gtk_text_buffer_insert (buffer, &end,
      _("The libxfce4ui, libxfce4util and exo packages are "
        "distributed under the terms of the GNU Library General Public License as "
        "published by the Free Software Foundation; either version 2 of the License, or "
        "(at your option) any later version."), -1);

  gtk_text_buffer_insert (buffer, &end, "\n\n", -1);
  gtk_text_buffer_insert (buffer, &end,
      _("The packages thunar, xfce4-appfinder, xfce4-panel, xfce4-session, "
        "xfce4-settings, xfconf, xfdesktop and xfwm4 are "
        "distributed under the terms of the GNU General Public License as "
        "published by the Free Software Foundation; either version 2 of the "
        "License, or (at your option) any later version."), -1);

  gtk_text_buffer_insert (buffer, &end, "\n", -1);
}



#ifdef VENDOR_INFO
static void
xfce_about_vendor (GtkBuilder *builder)
{
  gchar   *contents;
  gchar   *filename;
  GObject *object;
  gsize    length;

  g_return_if_fail (GTK_IS_BUILDER (builder));

  filename = g_build_filename (DATADIR, "vendorinfo", NULL);
  if (g_file_get_contents (filename, &contents, &length, NULL))
    {
      if (length > 0)
        {
          if (g_utf8_validate(contents, length, NULL))
            {
              object = gtk_builder_get_object (builder, "vendor-buffer");
              gtk_text_buffer_set_text (GTK_TEXT_BUFFER (object), contents, length);

              object = gtk_builder_get_object (builder, "vendor-label");
              gtk_label_set_text (GTK_LABEL (object), VENDOR_INFO);

              object = gtk_builder_get_object (builder, "vendor-tab");
              gtk_widget_show (GTK_WIDGET (object));
            }
          else
            {
              g_critical ("\"%s\" is not UTF-8 valid", filename);
            }
        }

      g_free (contents);
    }
  else
    {
      g_message ("No vendor information found in \"%s\".", filename);
    }

  g_free (filename);
}
#endif



static void
xfce_about_license (GtkBuilder *builder,
                    GObject    *buffer)
{
  GObject         *dialog;
  GObject         *object;
  static gboolean  initial = TRUE;

  g_return_if_fail (GTK_IS_BUILDER (builder));
  g_return_if_fail (GTK_IS_TEXT_BUFFER (buffer));

  object = gtk_builder_get_object (builder, "license-textview");
  gtk_text_view_set_buffer (GTK_TEXT_VIEW (object), GTK_TEXT_BUFFER (buffer));

  dialog = gtk_builder_get_object (builder, "license-dialog");
  if (initial)
    {
      g_signal_connect (G_OBJECT (dialog), "delete-event",
           G_CALLBACK (gtk_widget_hide_on_delete), NULL);

      object = gtk_builder_get_object (builder, "license-close-button");
      g_signal_connect_swapped (G_OBJECT (object), "clicked",
          G_CALLBACK (gtk_widget_hide), dialog);

      object = gtk_builder_get_object (builder, "window");
      gtk_window_set_transient_for (GTK_WINDOW (dialog), GTK_WINDOW (object));

      initial = FALSE;
    }

  gtk_widget_show (GTK_WIDGET (dialog));
}



static void
xfce_about_license_gpl (GtkBuilder *builder)
{
  xfce_about_license (builder,
      gtk_builder_get_object (builder, "gpl-buffer"));
}



static void
xfce_about_license_lgpl (GtkBuilder *builder)
{
  xfce_about_license (builder,
      gtk_builder_get_object (builder, "lgpl-buffer"));
}



static void
xfce_about_license_bsd (GtkBuilder *builder)
{
  xfce_about_license (builder,
      gtk_builder_get_object (builder, "bsd-buffer"));
}



static void
xfce_about_help (GtkWidget *button,
                 GtkWidget *dialog)
{
  g_return_if_fail (GTK_IS_BUTTON (button));
  xfce_dialog_show_help (GTK_WINDOW (dialog),
                         NULL, NULL, NULL);
}



gint
main (gint    argc,
      gchar **argv)
{
  GtkBuilder *builder;
  GError     *error = NULL;
  GObject    *dialog;
  GObject    *object;
  gchar      *version;

  xfce_textdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR, "UTF-8");

  if (G_UNLIKELY (!gtk_init_with_args (&argc, &argv, NULL, opt_entries, PACKAGE, &error)))
    {
      if (G_LIKELY (error != NULL))
        {
          g_print ("%s: %s.\n", G_LOG_DOMAIN, error->message);
          g_print (_("Type '%s --help' for usage information."), G_LOG_DOMAIN);
          g_print ("\n");

          g_error_free (error);
        }
      else
        g_error (_("Unable to initialize GTK+."));

      return EXIT_FAILURE;
    }

  if (G_UNLIKELY (opt_version))
    {
      g_print ("%s %s (Xfce %s)\n\n", G_LOG_DOMAIN, PACKAGE_VERSION, xfce_version_string ());
      g_print ("%s\n", "Copyright (c) 2008-2019");
      g_print ("\t%s\n\n", _("The Xfce development team. All rights reserved."));
      g_print (_("Please report bugs to <%s>."), PACKAGE_BUGREPORT);
      g_print ("\n");

      return EXIT_SUCCESS;
    }

  builder = gtk_builder_new ();
  if (!gtk_builder_add_from_string (builder, xfce_about_dialog_ui,
                                    xfce_about_dialog_ui_length, &error))
    {
      xfce_dialog_show_error (NULL, error, _("Failed to load interface"));
      g_error_free (error);
      g_object_unref (G_OBJECT (builder));

      return EXIT_FAILURE;
    }

  dialog = gtk_builder_get_object (builder, "window");
  g_signal_connect_swapped (G_OBJECT (dialog), "delete-event",
      G_CALLBACK (gtk_main_quit), NULL);

#ifdef VENDOR_INFO
  /* I18N: first %s will be replaced by the version, second by
   * the name of the distribution (--with-vendor-info=NAME) */
  version = g_strdup_printf (_("Version %s, distributed by %s"),
                             xfce_version_string (), VENDOR_INFO);
#else
  /* I18N: %s will be replaced by the Xfce version number */
  version = g_strdup_printf (_("Version %s"), xfce_version_string ());
#endif
  xfce_titled_dialog_set_subtitle (XFCE_TITLED_DIALOG (dialog), version);
  g_free (version);

#ifdef HAVE_GLIBTOP
  xfce_about_system (builder);
#else
  // Hide system tab
  gtk_notebook_remove_page (GTK_NOTEBOOK (gtk_builder_get_object (builder, "notebook")), 0);
#endif

  object = gtk_builder_get_object (builder, "about-buffer");
  xfce_about_about (GTK_TEXT_BUFFER (object));

  object = gtk_builder_get_object (builder, "credits-buffer");
  xfce_about_credits (GTK_TEXT_BUFFER (object));

  object = gtk_builder_get_object (builder, "copyright-buffer");
  xfce_about_copyright (GTK_TEXT_BUFFER (object));

#ifdef VENDOR_INFO
  xfce_about_vendor (builder);
#endif

  object = gtk_builder_get_object (builder, "gpl-button");
  g_signal_connect_swapped (G_OBJECT (object), "clicked",
      G_CALLBACK (xfce_about_license_gpl), builder);

  object = gtk_builder_get_object (builder, "lgpl-button");
  g_signal_connect_swapped (G_OBJECT (object), "clicked",
      G_CALLBACK (xfce_about_license_lgpl), builder);

  object = gtk_builder_get_object (builder, "bsd-button");
  g_signal_connect_swapped (G_OBJECT (object), "clicked",
      G_CALLBACK (xfce_about_license_bsd), builder);

  object = gtk_builder_get_object (builder, "help-button");
  g_signal_connect (G_OBJECT (object), "clicked",
      G_CALLBACK (xfce_about_help), dialog);

  object = gtk_builder_get_object (builder, "close-button");
  g_signal_connect_swapped (G_OBJECT (object), "clicked",
      G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_show (GTK_WIDGET (dialog));

  gtk_main ();

  g_object_unref (G_OBJECT (builder));

  return EXIT_SUCCESS;
}
