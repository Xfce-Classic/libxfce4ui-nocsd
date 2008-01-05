# $Id$

SUBDIRS =								\
	libxfce4ui							\
	docs								\
	po

distclean-local:
	rm -rf *.spec *.cache *~

rpm: dist
	rpmbuild -ta $(PACKAGE)-$(VERSION).tar.gz
	@rm -f $(PACKAGE)-$(VERSION).tar.gz

EXTRA_DIST =								\
	libxfce4ui.spec.in						\
	intltool-extract.in						\
	intltool-merge.in						\
	intltool-update.in
	
DISTCLEANFILES =							\
	libxfce4ui.spec							\
	intltool-extract						\
	intltool-merge							\
	intltool-update

DISTCHECK_CONFIGURE_FLAGS =						\
	--enable-gtk-doc

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
