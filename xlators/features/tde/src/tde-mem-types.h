/*
 *   Copyright (c) 2025 Red Hat, Inc. <http://www.redhat.com>
 *   This file is part of GlusterFS.
 *
 *   This file is licensed to you under your choice of the GNU Lesser
 *   General Public License, version 3 or any later version (LGPLv3 or
 *   later), or the GNU General Public License, version 2 (GPLv2), in all
 *   cases as published by the Free Software Foundation.
 */


#ifndef __TDE_MEM_TYPES_H__
#define __TDE_MEM_TYPES_H__

#include <glusterfs/mem-types.h>

enum gf_mdc_mem_types_ {
    gf_tde_mt_ = gf_common_mt_end + 1,
    gf_tde_mt_end
};

#endif /* __TDE_MEM_TYPES_H__ */


