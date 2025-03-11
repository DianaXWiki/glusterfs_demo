/*
 *   Copyright (c) 2025 Red Hat, Inc. <http://www.redhat.com>
 *   This file is part of GlusterFS.
 *
 *   This file is licensed to you under your choice of the GNU Lesser
 *   General Public License, version 3 or any later version (LGPLv3 or
 *   later), or the GNU General Public License, version 2 (GPLv2), in all
 *   cases as published by the Free Software Foundation.
 */


#ifndef __TDE_MESSAGES_H__
#define __TDE_MESSAGES_H__

#include <glusterfs/glfs-message-id.h>

/* First of all the new component needs to be declared at the end of
 * enum _msgid_comp in glusterfs/glfs-message-id.h. Then the ID used
 * needs to be referenced here to start defining messages associated
 * with this component.
 *
 * More than one component can be defined, but its messages need to
 * be defined sequentially. There can't be definitions of messages
 * from different components interleaved. */

/* Example:
 *
 *    GLFS_COMPONENT(COMPONENT);
 */

/* Add every new message at the end. The position of the message
 * determines its ID, so adding the message at the beginning would
 * change the IDs of all other messages. Also never remove one message
 * once it has been present in at least one release. This would cause
 * the same message id to be reused by another message.
 *
 * For new messages, use GLFS_NEW(). To deprecate a message, leave
 * it as it is, but change GLFS_NEW by GLFS_OLD. To remove a message
 * (i.e. the message cannot be used by the code), replace GLFS_OLD
 * by GLFS_GONE. */

// clang-format off

GLFS_MSGID(TDE, TDE_MSG_BASE_FILE_LOOKUP_FAILED, TDE_MSG_DICT_OP_FAILED,
    TDE_MSG_DOT_SHARD_NODIR, TDE_MSG_FD_CTX_SET_FAILED,
    TDE_MSG_INODE_CTX_GET_FAILED, TDE_MSG_INODE_CTX_SET_FAILED,
    TDE_MSG_INODE_PATH_FAILED, TDE_MSG_INTERNAL_XATTR_MISSING,
    TDE_MSG_INVALID_VOLFILE, TDE_MSG_LOOKUP_SHARD_FAILED,
    TDE_MSG_MEM_ACCT_INIT_FAILED, TDE_MSG_NULL_THIS,
    TDE_MSG_SIZE_SET_FAILED, TDE_MSG_STAT_FAILED,
    TDE_MSG_TRUNCATE_LAST_SHARD_FAILED,
    TDE_MSG_UPDATE_FILE_SIZE_FAILED, TDE_MSG_FOP_NOT_SUPPORTED,
    TDE_MSG_INVALID_FOP, TDE_MSG_MEMALLOC_FAILED,
    TDE_MSG_FOP_FAILED, TDE_MSG_SHARDS_DELETION_FAILED,
    TDE_MSG_SHARD_DELETION_COMPLETED);


// clang-format on

#endif /* __TDE_MESSAGES_H__ */

