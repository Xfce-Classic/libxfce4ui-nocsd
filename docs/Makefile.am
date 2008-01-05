# $Id$

AUTOMAKE_OPTIONS = 1.8

# The name of the module.
DOC_MODULE=libxfce4ui

# The top-level SGML file.
DOC_MAIN_SGML_FILE=$(DOC_MODULE)-docs.sgml

# Extra options to supply to gtkdoc-scan
SCAN_OPTIONS=--deprecated-guards="XFCE_DISABLE_DEPRECATED"

# Extra options to pass to gtkdoc-scangobj
SCANGOBJ_OPTIONS=

# The directory containing the source code. Relative to $(srcdir)
DOC_SOURCE_DIR=../libxfce4ui

# Extra options to supply to gtkdoc-mkdb
MKDB_OPTIONS=--sgml-mode --output-format=xml

# Extra options to supply to gtkdoc-fixref
FIXXREF_OPTIONS=

# Used for dependencies
HFILE_GLOB=$(top_srcdir)/libxfce4ui/*.h
CFILE_GLOB=$(top_srcdir)/libxfce4ui/*.c

# Header files to ignore when scanning
IGNORE_HFILES=								\
	libxfce4ui.h							\
	libxfce4ui-alias.h						\
	libxfce4ui-private.h						\
	xfce-heading.h

# Extra files to add when scanning (relative to $srcdir)
EXTRA_HFILES=

# Images to copy into HTML directory
HTML_IMAGES =

# Extra SGML files that are included by DOC_MAIN_SGML_FILE
content_files = 							\
	version.xml

# CFLAGS and LDFLAGS for compiling scan program. Only needed
# if $(DOC_MODULE).types is non-empty.
INCLUDES =	 							\
	-I$(top_srcdir) 						\
	-I$(top_builddir) 						\
	$(LIBXFCE4UTIL_CFLAGS)						\
	$(GTK_CFLAGS)

GTKDOC_LIBS =  								\
	$(LIBXFCE4UTIL_LIBS)						\
	$(GTK_LIBS)							\
	$(top_builddir)/libxfce4ui/libxfce4ui-$(LIBXFCE4UI_VERSION_API).la

include $(top_srcdir)/gtk-doc.make

# Other files to distribute
EXTRA_DIST +=								\
	version.xml.in

# required for gtk-doc
dist-hook: all

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
