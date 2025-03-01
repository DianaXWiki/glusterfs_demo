#ifndef __GLUSTERFS_XLATOR_TDE_H__
#define __GLUSTERFS_XLATOR_TDE_H__

#include "xlator.h"

/* Exported functions for translator ops can be declared here if needed */
int tde_init(xlator_t *this);
void tde_fini(xlator_t *this);
int tde_reconfigure(xlator_t *this, dict_t *options);
int tde_mem_acct_init(xlator_t *this);

/* FOP implementations */
int tde_writev(call_frame_t *frame, xlator_t *this, fd_t *fd,
               struct iovec *vector, int32_t count, off_t offset,
               uint32_t flags, struct iobref *iobref, dict_t *xdata);
int tde_readv(call_frame_t *frame, xlator_t *this, fd_t *fd, size_t size,
              off_t offset, uint32_t flags, dict_t *xdata);

#endif /* __GLUSTERFS_XLATOR_TDE_H__ */
