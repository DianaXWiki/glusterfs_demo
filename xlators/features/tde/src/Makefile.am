
xlator_LTLIBRARIES = tde.la
xlatordir = $(libdir)/glusterfs/$(PACKAGE_VERSION)/xlator/tde
tde_la_LDFLAGS = -module $(GF_XLATOR_DEFAULT_LDFLAGS)
tde_la_SOURCES = tde.c
tde_la_LIBADD = $(top_builddir)/libglusterfs/src/libglusterfs.la
noinst_HEADERS = tde.h tde-mem-types.h tde-messages.h
AM_CPPFLAGS = $(GF_CPPFLAGS) -I$(top_srcdir)/libglusterfs/src            -I$(top_srcdir)/rpc/xdr/src -I$(top_builddir)/rpc/xdr/src
AM_CFLAGS = -Wall -fno-strict-aliasing $(GF_CFLAGS)
CLEANFILES =

EXTRA_DIST = grpc_client.py grpc_server.py shard_service.proto

install-data-local:
	mkdir -p $(DESTDIR)@sysconfdir@/glusterfs/tde
	install -m 0755 grpc_client.py $(DESTDIR)@sysconfdir@/glusterfs/tde/
	install -m 0755 grpc_server.py $(DESTDIR)@sysconfdir@/glusterfs/tde/
	install -m 0644 shard_service.proto $(DESTDIR)@sysconfdir@/glusterfs/tde/
	install -m 0644 shard_service_pb2.py $(DESTDIR)@sysconfdir@/glusterfs/tde/
	install -m 0644 shard_service_pb2_grpc.py $(DESTDIR)@sysconfdir@/glusterfs/tde/
