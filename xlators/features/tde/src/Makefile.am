# Change these to match your source code
TARGET  = tde.so
OBJECTS = tde.o

# Change these to match your GlusterFS installation paths
GLFS_SRC = /usr/local/src/glusterfs
GLFS_LIB = /usr/local/lib
HOST_OS  = GF_LINUX_HOST_OS

# Compiler Flags
CFLAGS  = -fPIC -Wall -O0 -g \
          -DHAVE_CONFIG_H -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -D$(HOST_OS) \
          -I$(GLFS_SRC) -I$(GLFS_SRC)/libglusterfs/src \
          -I$(GLFS_SRC)/contrib/uuid
LDFLAGS = -shared -nostartfiles -L$(GLFS_LIB) -lglusterfs -lpthread

# Build the translator
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Compile source files
tde.o: tde.c
	$(CC) $(CFLAGS) -c tde.c -o tde.o

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)
