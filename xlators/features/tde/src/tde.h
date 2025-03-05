/*
 *   Copyright (c) 2025 Red Hat, Inc. <http://www.redhat.com>
 *   This file is part of GlusterFS.
 *
 *   This file is licensed to you under your choice of the GNU Lesser
 *   General Public License, version 3 or any later version (LGPLv3 or
 *   later), or the GNU General Public License, version 2 (GPLv2), in all
 *   cases as published by the Free Software Foundation.
 */


#ifndef __TDE_H__
#define __TDE_H__

#define GFAPI_SET_ATTR_MODE 0x1
#define GFAPI_SET_ATTR_UID 0x2
#define GFAPI_SET_ATTR_GID 0x4
#define GFAPI_SET_ATTR_SIZE 0x8
#define GFAPI_SET_ATTR_ATIME 0x10
#define GFAPI_SET_ATTR_MTIME 0x20

#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64
#endif

#ifndef __USE_FILE_OFFSET64
#define __USE_FILE_OFFSET64
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "tde-mem-types.h"
#include "tde-messages.h"
#include <glusterfs/glusterfs.h>
#include <glusterfs/xlator.h>
#include <glusterfs/defaults.h>

#endif /* __TDE_H__ */


