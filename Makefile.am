# $Id$

SUBDIRS = \
	libxfce4ui \
	libxfce4kbd-private \
	xfce4-about \
	glade \
	icons \
	docs \
	po

AUTOMAKE_OPTIONS = \
	1.9 \
	dist-bzip2 \
	no-dist-gzip

distclean-local:
	rm -rf *.spec *.cache *~

rpm: dist
	rpmbuild -ta $(PACKAGE)-$(VERSION).tar.gz
	@rm -f $(PACKAGE)-$(VERSION).tar.gz

.PHONY: ChangeLog

ChangeLog: Makefile
	(GIT_DIR=$(top_srcdir)/.git git log > .changelog.tmp \
	&& mv .changelog.tmp ChangeLog; rm -f .changelog.tmp) \
	|| (touch ChangeLog; echo 'Git directory not found: installing possibly empty changelog.' >&2)

dist-hook: ChangeLog

EXTRA_DIST = \
	libxfce4ui.spec.in \
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

DISTCLEANFILES = \
	libxfce4ui.spec \
	intltool-extract \
	intltool-merge \
	intltool-update

DISTCHECK_CONFIGURE_FLAGS = \
	--enable-gtk-doc \
	--disable-gladeui

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
