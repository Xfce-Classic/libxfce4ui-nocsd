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

#include <libxfce4util/libxfce4util.h>
#include <libxfce4ui/libxfce4ui.h>

#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <glibtop/mem.h>
#include <glibtop/sysinfo.h>
#include <sys/utsname.h>

#include "system-info.h"



typedef struct
{
  char *regex;
  char *replacement;
} ReplaceStrings;



static char *
prettify_info (const char *info)
{
  g_autofree char *escaped = NULL;
  g_autofree gchar *pretty = NULL;
  guint   i;
  static const ReplaceStrings rs[] = {
    { "Mesa DRI ", ""},
    { "Intel[(]R[)]", "Intel<sup>\302\256</sup>"},
    { "Core[(]TM[)]", "Core<sup>\342\204\242</sup>"},
    { "Atom[(]TM[)]", "Atom<sup>\342\204\242</sup>"},
    { "Gallium .* on (AMD .*)", "\\1"},
    { "(AMD .*) [(].*", "\\1"},
    { "(AMD [A-Z])(.*)", "\\1\\L\\2\\E"},
    { "AMD", "AMD<sup>\302\256</sup>"},
    { "Graphics Controller", "Graphics"},
  };

  if (*info == '\0')
    return NULL;

  escaped = g_markup_escape_text (info, -1);
  pretty = g_strdup (g_strstrip (escaped));

  for (i = 0; i < G_N_ELEMENTS (rs); i++)
    {
      g_autoptr(GError) error = NULL;
      g_autoptr(GRegex) re = NULL;
      g_autofree gchar *new = NULL;

      re = g_regex_new (rs[i].regex, 0, 0, &error);
      if (re == NULL)
        {
          g_warning ("Error building regex: %s", error->message);
          continue;
        }

      new = g_regex_replace (re,
                             pretty,
                             -1,
                             0,
                             rs[i].replacement,
                             0,
                             &error);

      if (error != NULL)
        {
          g_warning ("Error replacing %s: %s", rs[i].regex, error->message);
          continue;
        }

      g_free (pretty);
      pretty = g_steal_pointer (&new);
    }

  return g_steal_pointer (&pretty);
}



static char *
remove_duplicate_whitespace (const char *old)
{
  g_autofree gchar *new = NULL;
  g_autoptr(GRegex) re = NULL;
  g_autoptr(GError) error = NULL;

  if (old == NULL)
    return NULL;

  re = g_regex_new ("[ \t\n\r]+", G_REGEX_MULTILINE, 0, &error);
  if (re == NULL)
    {
      g_warning ("Error building regex: %s", error->message);
      return g_strdup (old);
    }
  new = g_regex_replace (re,
                         old,
                         -1,
                         0,
                         " ",
                         0,
                         &error);
  if (new == NULL)
    {
      g_warning ("Error replacing string: %s", error->message);
      return g_strdup (old);
    }

  return g_steal_pointer (&new);
}



static char *
info_cleanup (const char *input)
{
  g_autofree char *pretty;

  pretty = prettify_info (input);
  return remove_duplicate_whitespace (pretty);
}



char *
get_cpu_info (const glibtop_sysinfo *info)
{
  g_autoptr(GHashTable) counts = NULL;
  g_autoptr(GString) cpu = NULL;
  GHashTableIter iter;
  gpointer       key, value;
  guint          i;
  int            j;

  counts = g_hash_table_new (g_str_hash, g_str_equal);

  /* count duplicates */
  for (i = 0; i != info->ncpu; ++i)
    {
      const char * const keys[] = { "model name", "cpu", "Processor" };
      char *model;
      int  *count;

      model = NULL;

      for (j = 0; model == NULL && j != G_N_ELEMENTS (keys); ++j)
        {
          model = g_hash_table_lookup (info->cpuinfo[i].values,
                                       keys[j]);
        }

      if (model == NULL)
          continue;

      count = g_hash_table_lookup (counts, model);
      if (count == NULL)
        g_hash_table_insert (counts, model, GINT_TO_POINTER (1));
      else
        g_hash_table_replace (counts, model, GINT_TO_POINTER (GPOINTER_TO_INT (count) + 1));
    }

  cpu = g_string_new (NULL);
  g_hash_table_iter_init (&iter, counts);
  while (g_hash_table_iter_next (&iter, &key, &value))
    {
      g_autofree char *cleanedup = NULL;
      int count;

      count = GPOINTER_TO_INT (value);
      cleanedup = info_cleanup ((const char *) key);
      if (count > 1)
        g_string_append_printf (cpu, "%s \303\227 %d ", cleanedup, count);
      else
        g_string_append_printf (cpu, "%s ", cleanedup);
    }

  return g_strdup (cpu->str);
}



static GHashTable*
get_os_info (void)
{
  GHashTable *hashtable;
  g_autofree gchar *buffer = NULL;

  hashtable = NULL;

  if (g_file_get_contents ("/etc/os-release", &buffer, NULL, NULL))
    {
      g_auto(GStrv) lines = NULL;
      gint i;

      lines = g_strsplit (buffer, "\n", -1);

      for (i = 0; lines[i] != NULL; i++)
        {
          gchar *delimiter;

          /* Initialize the hash table if needed */
          if (!hashtable)
            hashtable = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

          delimiter = strstr (lines[i], "=");

          if (delimiter != NULL)
            {
              gint size;
              gchar *key, *value;

              key = g_strndup (lines[i], delimiter - lines[i]);

              /* Jump the '=' */
              delimiter += strlen ("=");

              /* Eventually jump the ' " ' character */
              if (g_str_has_prefix (delimiter, "\""))
                delimiter += strlen ("\"");

              size = strlen (delimiter);

              /* Don't consider the last ' " ' too */
              if (g_str_has_suffix (delimiter, "\""))
                size -= strlen ("\"");

              value = g_strndup (delimiter, size);

              g_hash_table_insert (hashtable, key, value);
            }
        }
    }

  return hashtable;
}



char *
get_os_type (void)
{
  if (GLIB_SIZEOF_VOID_P == 8)
    /* translators: This is the type of architecture for the OS */
    return g_strdup_printf (_("64-bit"));
  else
    /* translators: This is the type of architecture for the OS */
    return g_strdup_printf (_("32-bit"));
}



char *
get_system_info (guint infotype)
{
  gchar *result = NULL;
  struct utsname buffer;

  if (uname (&buffer) != 0) {
    result = g_strdup (_("Unknown"));
    return result;
  }

  switch (infotype)
    {
      case OS_NAME:
        result = g_strdup_printf ("%s %s", buffer.sysname, buffer.release);
        break;
      case DEVICE_NAME:
        result = g_strdup (buffer.nodename);
        break;
    }

  return result;
}



char *
get_os_name (void)
{
  GHashTable *os_info;
  gchar *name, *version_id, *pretty_name, *build_id;
  gchar *result = NULL;
  g_autofree gchar *name_version = NULL;

  os_info = get_os_info ();

  /* If we're not on Linux we return the OS info from uname */
  if (!os_info) {
    result = get_system_info (OS_NAME);
    return result;
  }

  name = g_hash_table_lookup (os_info, "NAME");
  version_id = g_hash_table_lookup (os_info, "VERSION_ID");
  pretty_name = g_hash_table_lookup (os_info, "PRETTY_NAME");
  build_id = g_hash_table_lookup (os_info, "BUILD_ID");

  if (pretty_name)
    name_version = g_strdup (pretty_name);
  else if (name && version_id)
    name_version = g_strdup_printf ("%s %s", name, version_id);
  else
    name_version = g_strdup (_("Unknown"));

  if (build_id)
    {
      /* translators: This is the name of the OS, followed by the build ID, for
       * example:
       * "Fedora 25 (Workstation Edition); Build ID: xyz" or
       * "Ubuntu 16.04 LTS; Build ID: jki" */
      result = g_strdup_printf (_("%s; Build ID: %s"), name_version, build_id);
    }
  else
    {
      result = g_strdup (name_version);
    }

  g_clear_pointer (&os_info, g_hash_table_destroy);

  return result;
}
