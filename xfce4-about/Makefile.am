
INCLUDES = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"xfce4-about\" \
	-DDATADIR=\"$(datadir)/xfce4\" \
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\" \
	$(PLATFORM_CPPFLAGS)

bin_PROGRAMS = \
	xfce4-about

xfce4_about_built_sources = \
	about-dialog-ui.h

xfce4_about_SOURCES = \
	$(xfce4_about_built_sources) \
	contributors.h \
	translators.h \
	main.c

xfce4_about_CFLAGS = \
	$(LIBXFCE4UTIL_CFLAGS) \
	$(GTK2_CFLAGS) \
	$(PLATFORM_CFLAGS)

xfce4_about_LDADD = \
	$(top_builddir)/libxfce4ui/libxfce4ui-$(LIBXFCE4UI_VERSION_API).la \
	$(LIBXFCE4UTIL_LIBS) \
	$(GTK2_LIBS)

xfce4_about_DEPENDENCIES = \
	$(top_builddir)/libxfce4ui/libxfce4ui-$(LIBXFCE4UI_VERSION_API).la

desktopdir = $(datadir)/applications
desktop_in_files = xfce4-about.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

if MAINTAINER_MODE

about-dialog-ui.h: $(srcdir)/xfce4-about-dialog.glade Makefile
	$(AM_V_GEN) xdt-csource --static --strip-comments --strip-content --name=xfce_about_dialog_ui $< >$@

BUILT_SOURCES = \
	$(xfce4_about_built_sources)

endif

EXTRA_DIST = \
	$(desktop_in_files) \
	xfce4-about-dialog.glade

DISTCLEANFILES = \
	$(xfce4_about_built_sources) \
	$(desktop_DATA)

