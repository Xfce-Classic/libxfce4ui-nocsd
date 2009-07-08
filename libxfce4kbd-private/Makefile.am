# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:

if ENABLE_KEYBOARD_LIBRARY

INCLUDES = \
	-I$(top_builddir) \
	-I$(top_srcdir) \
	-DDATADIR=\"$(datadir)\" \
	-DG_LOG_DOMAIN=\"libxfce4kbd-private\" \
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\" \
	-DPREFIX=\"$(prefix)\" \
	$(PLATFORM_CPPFLAGS)

lib_LTLIBRARIES = libxfce4kbd-private-2.la

libxfce4kbd_headers = \
	xfce-shortcuts-provider.h \
	xfce-shortcuts-grabber.h \
	xfce-shortcut-dialog.h \
	xfce-shortcuts.h

libxfce4kbd_private_includedir = \
	$(includedir)/xfce4/libxfce4kbd-private-$(LIBXFCE4KBD_PRIVATE_VERSION_API)/libxfce4kbd-private

libxfce4kbd_private_include_HEADERS = \
	$(libxfce4kbd_headers)

libxfce4kbd_private_2_la_SOURCES = \
	$(libxfce4kbd_headers) \
  xfce-shortcuts-provider.c \
	xfce-shortcuts-grabber.c \
	xfce-shortcut-dialog.c \
	xfce-shortcuts.c

libxfce4kbd_private_2_la_CFLAGS = \
	$(PLATFORM_CFLAGS) \
	$(GLIB_CFLAGS)  \
	$(GTK_CFLAGS) \
	$(LIBX11_CFLAGS) \
	$(LIBXFCE4UTIL_CFLAGS) \
	$(XFCONF_CFLAGS)

libxfce4kbd_private_2_la_LDFLAGS = \
	-export-dynamic \
	-version-info $(LIBXFCE4KBD_PRIVATE_VERINFO) \
	-export-symbols-regex "^[^_].*" \
	-no-undefined \
	$(LIBX11_LDFLAGS)

libxfce4kbd_private_2_la_LIBADD = \
	$(top_builddir)/libxfce4ui/libxfce4ui-$(LIBXFCE4UI_VERSION_API).la \
	$(PLATFORM_LDFLAGS) \
	$(GLIB_LIBS) \
	$(GTK_LIBS) \
	$(LIBX11_LIBS) \
	$(LIBXFCE4UTIL_LIBS) \
	$(XFCONF_LIBS)

settingsdir = $(sysconfdir)/xdg/xfce4/xfconf/xfce-perchannel-xml
settings_DATA = xfce4-keyboard-shortcuts.xml

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libxfce4kbd-private-2.pc

EXTRA_DIST = \
	$(settings_DATA)

# required for gtk-doc
dist-hook: all

endif # ENABLE_KEYBOARD_LIBRARY
