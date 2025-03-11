/*
 *   Copyright (c) 2025 Red Hat, Inc. <http://www.redhat.com>
 *   This file is part of GlusterFS.
 *
 *   This file is licensed to you under your choice of the GNU Lesser
 *   General Public License, version 3 or any later version (LGPLv3 or
 *   later), or the GNU General Public License, version 2 (GPLv2), in all
 *   cases as published by the Free Software Foundation.
 */


#ifndef __ TDE_H__
#define __ TDE_H__

#include "tde-mem-types.h"
#include "tde-messages.h"
#include <glusterfs/glusterfs.h>
#include <glusterfs/xlator.h>
#include <glusterfs/defaults.h>

typedef struct tde_private_t {
    pthread_mutex_t lock; // Mutex for thread safety
    int tde_enabled; // Flag for enabling the TDE feature
    int encrypt_write;   // Flag for enabling encryption during writes
    int decrypt_read;    // Flag for enabling decryption during reads
    AES_KEY enc_key;     // AES encryption key
    AES_KEY dec_key;     // AES decryption key
} tde_private_t;


#endif /* __TDE_H__ */


