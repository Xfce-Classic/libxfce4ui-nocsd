# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
#
# Copyright (c) 2016 Eric Koegel <eric@xfce.org>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Library General Public License for more details.
#
# You should have received a copy of the GNU Library General
# Public License along with this library; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301, USA.

AM_CPPFLAGS =								\
	-I$(top_srcdir)							\
	-DG_LOG_DOMAIN=\"libxfce4ui-tests\"

noinst_PROGRAMS =

# test-ui-gtk2
if ENABLE_GTK2_LIBRARY
noinst_PROGRAMS += \
	test-ui-gtk2

test_ui_gtk2_SOURCES =				\
	test-ui.c

test_ui_gtk2_CFLAGS =					\
	$(LIBSM_CFLAGS) \
	$(GTK2_CFLAGS) \
	$(LIBSTARTUP_NOTIFICATION_CFLAGS) \
	$(LIBXFCE4UTIL_CFLAGS) \
	$(PLATFORM_CFLAGS)

test_ui_gtk2_DEPENDENCIES =				\
	$(top_builddir)/libxfce4ui/libxfce4ui-1.la

test_ui_gtk2_LDADD =					\
	$(LIBSM_LIBS) \
	$(GTK2_LIBS) \
	$(LIBSTARTUP_NOTIFICATION_LIBS) \
	$(LIBXFCE4UTIL_LIBS) \
	$(top_builddir)/libxfce4ui/libxfce4ui-1.la

endif

# test-ui-gtk3
noinst_PROGRAMS +=					\
	test-ui-gtk3

test_ui_gtk3_SOURCES =				\
	test-ui.c

test_ui_gtk3_CFLAGS =					\
	$(LIBSM_CFLAGS) \
	$(GTK3_CFLAGS) \
	$(LIBSTARTUP_NOTIFICATION_CFLAGS) \
	$(LIBXFCE4UTIL_CFLAGS) \
	$(PLATFORM_CFLAGS)

test_ui_gtk3_DEPENDENCIES =				\
	$(top_builddir)/libxfce4ui/libxfce4ui-2.la

test_ui_gtk3_LDADD =					\
	$(LIBSM_LIBS) \
	$(GTK3_LIBS) \
	$(LIBSTARTUP_NOTIFICATION_LIBS) \
	$(LIBXFCE4UTIL_LIBS) \
	$(top_builddir)/libxfce4ui/libxfce4ui-2.la
