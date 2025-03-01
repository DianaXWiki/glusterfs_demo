lib_LTLIBRARIES = libtde.la

libtde_la_SOURCES = tde.c tde.h

# Use GlusterFS-specific compiler and linker flags.
libtde_la_CFLAGS = $(GF_CFLAGS)
libtde_la_LDFLAGS = $(GF_LDFLAGS) -module -avoid-version

# If using gRPC, include necessary flags (either via pkg-config or manually)
# For example:
# libtde_la_CFLAGS += $(GRPC_CFLAGS)
# libtde_la_LDFLAGS += $(GRPC_LIBS)
