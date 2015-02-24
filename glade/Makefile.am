AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libxfce4ui-glade\" \
	$(PLATFORM_CPPFLAGS)

SUBDIRS = \
	icons

if HAVE_GLADEUI
##
## Glade module
##
glademoduledir = \
	$(GLADEUI_MODULEDIR)

glademodule_LTLIBRARIES = \
	libxfce4uiglade.la

libxfce4uiglade_la_SOURCES  = \
	libxfce4ui-glade.c

libxfce4uiglade_la_CFLAGS = \
	$(GLADEUI_CFLAGS) \
	$(LIBXFCE4UTIL_CFLAGS) \
	$(PLATFORM_CFLAGS)

libxfce4uiglade_la_LDFLAGS = \
	-no-undefined \
	-avoid-version \
	-module \
	$(PLATFORM_LDFLAGS)

libxfce4uiglade_la_LIBADD = \
	$(top_builddir)/libxfce4ui/libxfce4ui-1.la \
	$(LIBXFCE4UTIL_LIBS) \
	$(GLADEUI_LIBS)

##
## Glade catalog xml file
##
gladecatalogdir = \
	$(GLADEUI_CATALOGDIR)
gladecatalog_DATA = \
	libxfce4ui.xml \
	libxfce4ui.xml.in
@INTLTOOL_XML_NOMERGE_RULE@
endif

CLEANFILES = \
	libxfce4ui.xml

EXTRA_DIST = \
	libxfce4ui.xml.in

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
