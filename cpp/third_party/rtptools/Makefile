# Generated automatically from Makefile.in by configure.
# Makefile.in generated automatically by automake 1.4 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = .
top_srcdir = .
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/rtptools
pkglibdir = $(libdir)/rtptools
pkgincludedir = $(includedir)/rtptools

top_builddir = .

ACLOCAL = aclocal
AUTOCONF = autoconf
AUTOMAKE = automake
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL_PROGRAM}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = x86_64-unknown-linux-gnu
host_triplet = x86_64-unknown-linux-gnu
CC = gcc
CPP = gcc -E
MAKEINFO = /home/walter/codelab/rtptools-1.18/missing makeinfo
PACKAGE = rtptools
U = 
VERSION = 1.18

AUTOMAKE_OPTIONS = foreign

TAR = gtar

bin_PROGRAMS = rtpdump rtpplay rtpsend rtptrans

COMMON =          ansi.h         host2ip.c         hpt.c         multimer.c         multimer.h         notify.c         notify.h         rtp.h         sysdep.h         types.h         vat.h


rtpdump_SOURCES = $(COMMON) rd.c rtpdump.h rtpdump.c
#rtpplay_SOURCES = $(COMMON) rd.c hsearch.c rtpplay.c
rtpplay_SOURCES = $(COMMON) rd.c rtpplay.c
rtpsend_SOURCES = $(COMMON) rtpsend.c
rtptrans_SOURCES = $(COMMON) rtptrans.c

#rpm: rtptools-$(VERSION).spec $(bin_PROGRAMS)
#	rpm -ba 

EXTRA_DIST = ChangeLog ChangeLog.html COPYRIGHT rtptools.html bark.rtp         nt/*.c nt/include/*.h         nt/include/arpa/*.h nt/include/netinet/*.h         nt/include/rpcsvc/*.h nt/include/sys/*.h         nt/include/utilnt/*.h         hsearch.h hsearch.c multidump multiplay         rtptools.dsw rtpdump.dsp rtpplay.dsp rtpsend.dsp rtptrans.dsp         bcb/*.bp? bcb/obj/*

ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_CLEAN_FILES = 
PROGRAMS =  $(bin_PROGRAMS)


DEFS =  -DPACKAGE=\"rtptools\" -DVERSION=\"1.18\" -DHAVE_GETHOSTBYNAME=1 -DHAVE_LIBNSL=1 -DHAVE_SOCKET=1 -DSTDC_HEADERS=1 -DHAVE_SEARCH_H=1 -DHAVE_SYS_TIME_H=1 -DHAVE_UNISTD_H=1 -DPROTOTYPES=1 -DTIME_WITH_SYS_TIME=1 -DRETSIGTYPE=void -DHAVE_STRFTIME=1 -DHAVE_VPRINTF=1 -DHAVE_GETHOSTNAME=1 -DHAVE_GETTIMEOFDAY=1 -DHAVE_MKTIME=1 -DHAVE_SELECT=1 -DHAVE_STRDUP=1 -DHAVE_STRERROR=1 -DHAVE_STRSTR=1 -DHAVE_STRTOL=1 -DHAVE_UNAME=1  -I. -I$(srcdir) 
CPPFLAGS = 
LDFLAGS = 
LIBS = -lnsl 
rtpdump_OBJECTS =  host2ip.o hpt.o multimer.o notify.o rd.o rtpdump.o
rtpdump_LDADD = $(LDADD)
rtpdump_DEPENDENCIES = 
rtpdump_LDFLAGS = 
rtpplay_OBJECTS =  host2ip.o hpt.o multimer.o notify.o \
rd.o rtpplay.o
#rtpplay_OBJECTS =  host2ip.o hpt.o multimer.o notify.o rd.o \
#hsearch.o rtpplay.o
rtpplay_LDADD = $(LDADD)
rtpplay_DEPENDENCIES = 
rtpplay_LDFLAGS = 
rtpsend_OBJECTS =  host2ip.o hpt.o multimer.o notify.o rtpsend.o
rtpsend_LDADD = $(LDADD)
rtpsend_DEPENDENCIES = 
rtpsend_LDFLAGS = 
rtptrans_OBJECTS =  host2ip.o hpt.o multimer.o notify.o rtptrans.o
rtptrans_LDADD = $(LDADD)
rtptrans_DEPENDENCIES = 
rtptrans_LDFLAGS = 
CFLAGS = -g -O2 -Wall
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
DIST_COMMON =  README ChangeLog Makefile.am Makefile.in aclocal.m4 \
config.guess config.sub configure configure.in install-sh missing \
mkinstalldirs


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

GZIP_ENV = --best
SOURCES = $(rtpdump_SOURCES) $(rtpplay_SOURCES) $(rtpsend_SOURCES) $(rtptrans_SOURCES)
OBJECTS = $(rtpdump_OBJECTS) $(rtpplay_OBJECTS) $(rtpsend_OBJECTS) $(rtptrans_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .o .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --foreign --include-deps Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) ./config.status

$(ACLOCAL_M4):  configure.in 
	cd $(srcdir) && $(ACLOCAL)

config.status: $(srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	$(SHELL) ./config.status --recheck
$(srcdir)/configure: $(srcdir)/configure.in $(ACLOCAL_M4) $(CONFIGURE_DEPENDENCIES)
	cd $(srcdir) && $(AUTOCONF)

mostlyclean-binPROGRAMS:

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

distclean-binPROGRAMS:

maintainer-clean-binPROGRAMS:

install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo "  $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`"; \
	     $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	list='$(bin_PROGRAMS)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	done

.c.o:
	$(COMPILE) -c $<

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

rtpdump: $(rtpdump_OBJECTS) $(rtpdump_DEPENDENCIES)
	@rm -f rtpdump
	$(LINK) $(rtpdump_LDFLAGS) $(rtpdump_OBJECTS) $(rtpdump_LDADD) $(LIBS)

rtpplay: $(rtpplay_OBJECTS) $(rtpplay_DEPENDENCIES)
	@rm -f rtpplay
	$(LINK) $(rtpplay_LDFLAGS) $(rtpplay_OBJECTS) $(rtpplay_LDADD) $(LIBS)

rtpsend: $(rtpsend_OBJECTS) $(rtpsend_DEPENDENCIES)
	@rm -f rtpsend
	$(LINK) $(rtpsend_LDFLAGS) $(rtpsend_OBJECTS) $(rtpsend_LDADD) $(LIBS)

rtptrans: $(rtptrans_OBJECTS) $(rtptrans_DEPENDENCIES)
	@rm -f rtptrans
	$(LINK) $(rtptrans_LDFLAGS) $(rtptrans_OBJECTS) $(rtptrans_LDADD) $(LIBS)

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags $(ETAGS_ARGS) $$tags  $$unique $(LISP) -o $$here/TAGS)

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(PACKAGE)-$(VERSION)
top_distdir = $(distdir)

# This target untars the dist file and tries a VPATH configuration.  Then
# it guarantees that the distribution is self-contained by making another
# tarfile.
distcheck: dist
	-rm -rf $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) zxf $(distdir).tar.gz
	mkdir $(distdir)/=build
	mkdir $(distdir)/=inst
	dc_install_base=`cd $(distdir)/=inst && pwd`; \
	cd $(distdir)/=build \
	  && ../configure --srcdir=.. --prefix=$$dc_install_base \
	  && $(MAKE) $(AM_MAKEFLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) dvi \
	  && $(MAKE) $(AM_MAKEFLAGS) check \
	  && $(MAKE) $(AM_MAKEFLAGS) install \
	  && $(MAKE) $(AM_MAKEFLAGS) installcheck \
	  && $(MAKE) $(AM_MAKEFLAGS) dist
	-rm -rf $(distdir)
	@banner="$(distdir).tar.gz is ready for distribution"; \
	dashes=`echo "$$banner" | sed s/./=/g`; \
	echo "$$dashes"; \
	echo "$$banner"; \
	echo "$$dashes"
dist: distdir
	-chmod -R a+r $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) chozf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)
dist-all: distdir
	-chmod -R a+r $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) chozf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)
distdir: $(DISTFILES)
	-rm -rf $(distdir)
	mkdir $(distdir)
	-chmod 777 $(distdir)
	$(mkinstalldirs) $(distdir)/bcb $(distdir)/bcb/obj $(distdir)/nt \
	   $(distdir)/nt/include $(distdir)/nt/include/arpa \
	   $(distdir)/nt/include/netinet $(distdir)/nt/include/rpcsvc \
	   $(distdir)/nt/include/sys $(distdir)/nt/include/utilnt
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
host2ip.o: host2ip.c sysdep.h
hpt.o: hpt.c sysdep.h
multimer.o: multimer.c notify.h sysdep.h
notify.o: notify.c sysdep.h notify.h multimer.h ansi.h
rd.o: rd.c types.h sysdep.h rtpdump.h
rtpdump.o: rtpdump.c rtp.h types.h sysdep.h vat.h rtpdump.h ansi.h
rtpplay.o: rtpplay.c sysdep.h notify.h rtp.h types.h rtpdump.h \
	multimer.h ansi.h
rtpsend.o: rtpsend.c notify.h rtp.h types.h sysdep.h multimer.h ansi.h
rtptrans.o: rtptrans.c rtp.h types.h sysdep.h rtpdump.h ansi.h notify.h \
	multimer.h vat.h

info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am: install-binPROGRAMS
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-binPROGRAMS
uninstall: uninstall-am
all-am: Makefile $(PROGRAMS)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(bindir)


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-binPROGRAMS mostlyclean-compile \
		mostlyclean-tags mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-binPROGRAMS clean-compile clean-tags clean-generic \
		mostlyclean-am

clean: clean-am

distclean-am:  distclean-binPROGRAMS distclean-compile distclean-tags \
		distclean-generic clean-am

distclean: distclean-am
	-rm -f config.status

maintainer-clean-am:  maintainer-clean-binPROGRAMS \
		maintainer-clean-compile maintainer-clean-tags \
		maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am
	-rm -f config.status

.PHONY: mostlyclean-binPROGRAMS distclean-binPROGRAMS clean-binPROGRAMS \
maintainer-clean-binPROGRAMS uninstall-binPROGRAMS install-binPROGRAMS \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile tags mostlyclean-tags distclean-tags \
clean-tags maintainer-clean-tags distdir info-am info dvi-am dvi check \
check-am installcheck-am installcheck install-exec-am install-exec \
install-data-am install-data install-am install uninstall-am uninstall \
all-redirect all-am all installdirs mostlyclean-generic \
distclean-generic clean-generic maintainer-clean-generic clean \
mostlyclean distclean maintainer-clean


rpm_spec: rtptools.spec
	@echo "Generating RPM spec file"
	@echo "# Generated automatically from rtptools.spec"  > rtptools-$(VERSION).spec
	@echo "# DO NOT EDIT THIS FILE"                 >> rtptools-$(VERSION).spec
	@sed s/VERSION/$(VERSION)/g  rtptools.spec >> rtptools-$(VERSION).spec

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
