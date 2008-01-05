#!/bin/sh
#
# Copyright (c) 2004 The GLib Development Team.
# Copyright (c) 2007 The Xfce Development Team.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

cpp -P -DINCLUDE_INTERNAL_SYMBOLS -DINCLUDE_VARIABLES -DALL_FILES ${srcdir:-.}/libxfce4ui.symbols | sed -e '/^$/d' -e 's/ LIBXFCE4UI_GNUC.*$//' -e 's/ G_GNUC.*$//' -e 's/ PRIVATE//' | sort > expected-abi
nm -D .libs/libxfce4ui-1.so | grep " T\|R " | cut -d ' ' -f 3 | grep -v '^_.*' | sort > actual-abi
diff -u expected-abi actual-abi && rm expected-abi actual-abi
