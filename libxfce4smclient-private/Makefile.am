# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:

if ENABLE_SMCLIENT_LIBRARY

INCLUDES = \
	-I$(top_builddir) \
	-I$(top_srcdir) \
	-DDATADIR=\"$(datadir)\" \
	-DG_LOG_DOMAIN=\"libxfce4smclient-private\" \
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\" \
	-DPREFIX=\"$(prefix)\" \
	$(PLATFORM_CPPFLAGS)

if PLATFORM_OSX
platform_sources = eggsmclient-osx.c
platform_defines = -xobjective-c
platform_ldflags = -framework Carbon
else
platform_sources = \
	eggsmclient-xsmp.c \
	eggdesktopfile.c \
	eggdesktopfile.h
platform_libs = -lSM -lICE
endif

lib_LTLIBRARIES = libxfce4smclient-private-1.la

libxfce4smclient_headers = \
	eggsmclient.h

libxfce4smclient_private_includedir = \
	$(includedir)/xfce4/libxfce4smclient-private-$(LIBXFCE4SMCLIENT_PRIVATE_VERSION_API)/libxfce4kbd-private

libxfce4smclient_private_include_HEADERS = \
	$(libxfce4smclient_headers)

libxfce4smclient_private_1_la_SOURCES = \
	$(libxfce4kbd_headers) \
	eggsmclient.c \
	eggsmclient-private.h \
	$(platform_sources)

libxfce4smclient_private_1_la_CFLAGS = \
	$(PLATFORM_CFLAGS) \
	$(GLIB_CFLAGS)  \
	$(GTK_CFLAGS) \
	$(LIBX11_CFLAGS)

libxfce4smclient_private_1_la_LDFLAGS = \
	-export-dynamic \
	-version-info $(LIBXFCE4SMCLIENT_PRIVATE_VERINFO) \
	-export-symbols-regex "^[^_].*" \
	-no-undefined \
	$(LIBX11_LDFLAGS) \
	$(platform_ldflags)

libxfce4smclient_private_1_la_LIBADD = \
	$(PLATFORM_LDFLAGS) \
	$(GLIB_LIBS) \
	$(GTK_LIBS) \
	$(LIBX11_LIBS) \
	$(platform_libs)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libxfce4smclient-private-1.pc

EXTRA_DIST = \
	$(settings_DATA) \
	eggsmclient-osx.c \
	eggsmclient-xsmp.c \
	eggdesktopfile.c \
	eggdesktopfile.h

endif # ENABLE_SMCLIENT_LIBRARY
