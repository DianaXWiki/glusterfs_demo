xlator_LTLIBRARIES = tde.la
xlatordir = $(libdir)/glusterfs/$(PACKAGE_VERSION)/xlator/features

tde_la_LDFLAGS = -module -avoid-version

tde_la_SOURCES = tde.c

tde_la_LIBADD = $(top_builddir)/libglusterfs/src/libglusterfs.la

noinst_HEADERS = tde.h tde-mem-types.h

AM_CPPFLAGS = $(GF_CPPFLAGS) -I$(top_srcdir)/libglusterfs/src

AM_CFLAGS = -Wall $(GF_CFLAGS)

CLEANFILES =
