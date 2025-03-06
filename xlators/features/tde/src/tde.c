/*
 *   Copyright (c) 2025 Red Hat, Inc. <http://www.redhat.com>
 *   This file is part of GlusterFS.
 *
 *   This file is licensed to you under your choice of the GNU Lesser
 *   General Public License, version 3 or any later version (LGPLv3 or
 *   later), or the GNU General Public License, version 2 (GPLv2), in all
 *   cases as published by the Free Software Foundation.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <errno.h>
 #include <string.h>
 #include <sys/wait.h>      /* For waitpid() */
 #include <glusterfs/logging.h>
 #include <glusterfs/xlator.h>
 #include "tde.h"
 #include <sys/types.h>
 #include <fcntl.h>  
 #include<socket.h>
 #include<sys/un.h>

int32_t tde_fgetxattr_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * dict,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(fgetxattr, frame, op_ret, op_errno, dict, xdata);
    return 0;
}


        int32_t tde_fgetxattr(call_frame_t *frame, xlator_t *this, fd_t * fd,
	const char * name,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fgetxattr_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fgetxattr, fd, name, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fgetxattr, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_fsetxattr_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(fsetxattr, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_fsetxattr(call_frame_t *frame, xlator_t *this, fd_t * fd,
	dict_t * dict,
	int32_t flags,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fsetxattr_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fsetxattr, fd, dict, flags, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fsetxattr, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_setxattr_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(setxattr, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_setxattr(call_frame_t *frame, xlator_t *this, loc_t * loc,
	dict_t * dict,
	int32_t flags,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_setxattr_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->setxattr, loc, dict, flags, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(setxattr, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_statfs_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct statvfs * buf,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(statfs, frame, op_ret, op_errno, buf, xdata);
    return 0;
}


        int32_t tde_statfs(call_frame_t *frame, xlator_t *this, loc_t * loc,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_statfs_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->statfs, loc, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(statfs, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_fsyncdir_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(fsyncdir, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_fsyncdir(call_frame_t *frame, xlator_t *this, fd_t * fd,
	int32_t flags,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fsyncdir_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fsyncdir, fd, flags, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fsyncdir, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_opendir_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, fd_t * fd,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(opendir, frame, op_ret, op_errno, fd, xdata);
    return 0;
}


        int32_t tde_opendir(call_frame_t *frame, xlator_t *this, loc_t * loc,
	fd_t * fd,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_opendir_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->opendir, loc, fd, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(opendir, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_fstat_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * buf,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(fstat, frame, op_ret, op_errno, buf, xdata);
    return 0;
}


        int32_t tde_fstat(call_frame_t *frame, xlator_t *this, fd_t * fd,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fstat_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fstat, fd, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fstat, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_fsync_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * prebuf,
	struct iatt * postbuf,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(fsync, frame, op_ret, op_errno, prebuf, postbuf, xdata);
    return 0;
}


        int32_t tde_fsync(call_frame_t *frame, xlator_t *this, fd_t * fd,
	int32_t flags,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fsync_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fsync, fd, flags, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fsync, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_flush_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(flush, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_flush(call_frame_t *frame, xlator_t *this, fd_t * fd,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_flush_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->flush, fd, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(flush, frame, -1, errno, NULL);
    return 0;
}


static int32_t tde_writev_cbk(call_frame_t *frame, void *cookie, xlator_t *this,
    int32_t op_ret, int32_t op_errno,
    struct iatt *prebuf, struct iatt *postbuf,
    dict_t *xdata)
{
    gf_msg(this->name, GF_LOG_DEBUG, 0, 0,
        "%s: writev callback reached: op_ret=%d, op_errno=%d",
        this->name, op_ret, op_errno);
    STACK_UNWIND_STRICT(writev, frame, op_ret, op_errno, prebuf, postbuf, xdata);
    return 0;
}


void send_shard_to_grpc(char *data, size_t size, off_t offset) {
    int sockfd;
    struct sockaddr_un addr;
    
    // Open Unix domain socket
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket error");
        return;
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/tde_shard_socket");

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("connect error");
        close(sockfd);
        return;
    }

    // Format the message
    char message[1024];
    snprintf(message, sizeof(message), "%ld|%zu|%s", offset, size, "shard_data_here");

    // Send message
    write(sockfd, message, strlen(message));
    close(sockfd);
}


/* Revised writev FOP */
int32_t tde_writev(call_frame_t *frame, xlator_t *this, fd_t *fd,
    struct iovec *vector, int32_t count, off_t off,
    uint32_t flags, struct iobref *iobref, dict_t *xdata)
    {
        gf_msg(this->name, GF_LOG_DEBUG, 0, 0,
            "%s: writev intercepted at offset %ld, count=%d",
            this->name, off, count);
     
    
    if (count > 0) {
    char *shard_data = (char *)vector[count - 1].iov_base;
    size_t shard_size = vector[count - 1].iov_len;
    gf_msg(this->name, GF_LOG_DEBUG, 0, 0,
        "%s: Sending shard data (size %zu) via gRPC",
        this->name, shard_size);
 
    send_shard_to_grpc(shard_data, shard_size, off);
    }
    
    STACK_WIND(frame, tde_writev_cbk, FIRST_CHILD(this),
    FIRST_CHILD(this)->fops->writev, fd, vector, count, off, flags, iobref, xdata);
    return 0;
}


static int32_t
tde_readv_cbk(call_frame_t *frame, void *cookie, xlator_t *this,
              int32_t op_ret, int32_t op_errno,
              struct iovec *vector, int32_t count,
              struct iatt *stbuf, struct iobref *iobref, dict_t *xdata)
{
    gf_msg(this->name, GF_LOG_DEBUG, 0, 0,
        "%s: readv callback reached: op_ret=%d, op_errno=%d",
        this->name, op_ret, op_errno);
 
    STACK_UNWIND_STRICT(readv, frame, op_ret, op_errno, vector, count, stbuf, iobref, xdata);
    return 0;
}

void fetch_shard_from_grpc(off_t offset) {
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        char offset_str[32];
        snprintf(offset_str, sizeof(offset_str), "%ld", offset);

        char *args[] = {
            "python3", 
            "/opt/glusterfs/xlators/features/tde/src/grpc_client.py",
            "fetch",
            offset_str,
            NULL
        };
        execvp(args[0], args);
        perror("execvp failed");  // If exec fails
        exit(1);
    } else if (pid < 0) {
        perror("fork failed");  // Fork error
    }
}


int32_t
tde_readv(call_frame_t *frame, xlator_t *this, fd_t *fd, size_t size,
          off_t off, uint32_t flags, dict_t *xdata)
{

    gf_msg(this->name, GF_LOG_DEBUG, 0, 0,
        "%s: Sending shard data (offset %ld, size %zu) via gRPC",
        this->name, off, size);
 
    fetch_shard_from_grpc(off);

    STACK_WIND(frame, tde_readv_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->readv, fd, size, off, flags, xdata);
    return 0;
}


int32_t tde_open_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, fd_t * fd,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(open, frame, op_ret, op_errno, fd, xdata);
    return 0;
}


        int32_t tde_open(call_frame_t *frame, xlator_t *this, loc_t * loc,
	int32_t flags,
	fd_t * fd,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_open_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->open, loc, flags, fd, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(open, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_create_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, fd_t * fd,
	inode_t * inode,
	struct iatt * buf,
	struct iatt * preparent,
	struct iatt * postparent,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(create, frame, op_ret, op_errno, fd, inode, buf, preparent, postparent, xdata);
    return 0;
}


        int32_t tde_create(call_frame_t *frame, xlator_t *this, loc_t * loc,
	int32_t flags,
	mode_t mode,
	mode_t umask,
	fd_t * fd,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_create_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->create, loc, flags, mode, umask, fd, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(create, frame, -1, errno, NULL, NULL, NULL, NULL, NULL, NULL);
    return 0;
}


int32_t tde_link_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, inode_t * inode,
	struct iatt * buf,
	struct iatt * preparent,
	struct iatt * postparent,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(link, frame, op_ret, op_errno, inode, buf, preparent, postparent, xdata);
    return 0;
}


        int32_t tde_link(call_frame_t *frame, xlator_t *this, loc_t * oldloc,
	loc_t * newloc,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_link_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->link, oldloc, newloc, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(link, frame, -1, errno, NULL, NULL, NULL, NULL, NULL);
    return 0;
}


int32_t tde_rename_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * buf,
	struct iatt * preoldparent,
	struct iatt * postoldparent,
	struct iatt * prenewparent,
	struct iatt * postnewparent,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(rename, frame, op_ret, op_errno, buf, preoldparent, postoldparent, prenewparent, postnewparent, xdata);
    return 0;
}


        int32_t tde_rename(call_frame_t *frame, xlator_t *this, loc_t * oldloc,
	loc_t * newloc,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_rename_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->rename, oldloc, newloc, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(rename, frame, -1, errno, NULL, NULL, NULL, NULL, NULL, NULL);
    return 0;
}


int32_t tde_symlink_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, inode_t * inode,
	struct iatt * buf,
	struct iatt * preparent,
	struct iatt * postparent,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(symlink, frame, op_ret, op_errno, inode, buf, preparent, postparent, xdata);
    return 0;
}


        int32_t tde_symlink(call_frame_t *frame, xlator_t *this, const char * linkpath,
	loc_t * loc,
	mode_t umask,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_symlink_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->symlink, linkpath, loc, umask, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(symlink, frame, -1, errno, NULL, NULL, NULL, NULL, NULL);
    return 0;
}


int32_t tde_rmdir_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * preparent,
	struct iatt * postparent,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(rmdir, frame, op_ret, op_errno, preparent, postparent, xdata);
    return 0;
}


        int32_t tde_rmdir(call_frame_t *frame, xlator_t *this, loc_t * loc,
	int32_t flags,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_rmdir_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->rmdir, loc, flags, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(rmdir, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_unlink_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * preparent,
	struct iatt * postparent,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(unlink, frame, op_ret, op_errno, preparent, postparent, xdata);
    return 0;
}


        int32_t tde_unlink(call_frame_t *frame, xlator_t *this, loc_t * loc,
	int32_t flags,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_unlink_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->unlink, loc, flags, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(unlink, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_mkdir_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, inode_t * inode,
	struct iatt * buf,
	struct iatt * preparent,
	struct iatt * postparent,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(mkdir, frame, op_ret, op_errno, inode, buf, preparent, postparent, xdata);
    return 0;
}


        int32_t tde_mkdir(call_frame_t *frame, xlator_t *this, loc_t * loc,
	mode_t mode,
	mode_t umask,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_mkdir_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->mkdir, loc, mode, umask, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(mkdir, frame, -1, errno, NULL, NULL, NULL, NULL, NULL);
    return 0;
}


int32_t tde_mknod_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, inode_t * inode,
	struct iatt * buf,
	struct iatt * preparent,
	struct iatt * postparent,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(mknod, frame, op_ret, op_errno, inode, buf, preparent, postparent, xdata);
    return 0;
}


        int32_t tde_mknod(call_frame_t *frame, xlator_t *this, loc_t * loc,
	mode_t mode,
	dev_t rdev,
	mode_t umask,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_mknod_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->mknod, loc, mode, rdev, umask, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(mknod, frame, -1, errno, NULL, NULL, NULL, NULL, NULL);
    return 0;
}


int32_t tde_readlink_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, const char * path,
	struct iatt * buf,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(readlink, frame, op_ret, op_errno, path, buf, xdata);
    return 0;
}


        int32_t tde_readlink(call_frame_t *frame, xlator_t *this, loc_t * loc,
	size_t size,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_readlink_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->readlink, loc, size, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(readlink, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_access_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(access, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_access(call_frame_t *frame, xlator_t *this, loc_t * loc,
	int32_t mask,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_access_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->access, loc, mask, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(access, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_ftruncate_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * prebuf,
	struct iatt * postbuf,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(ftruncate, frame, op_ret, op_errno, prebuf, postbuf, xdata);
    return 0;
}


        int32_t tde_ftruncate(call_frame_t *frame, xlator_t *this, fd_t * fd,
	off_t offset,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_ftruncate_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->ftruncate, fd, offset, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(ftruncate, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_getxattr_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * dict,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(getxattr, frame, op_ret, op_errno, dict, xdata);
    return 0;
}


        int32_t tde_getxattr(call_frame_t *frame, xlator_t *this, loc_t * loc,
	const char * name,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_getxattr_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->getxattr, loc, name, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(getxattr, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_xattrop_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * dict,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(xattrop, frame, op_ret, op_errno, dict, xdata);
    return 0;
}


        int32_t tde_xattrop(call_frame_t *frame, xlator_t *this, loc_t * loc,
	gf_xattrop_flags_t flags,
	dict_t * dict,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_xattrop_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->xattrop, loc, flags, dict, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(xattrop, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_fxattrop_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * dict,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(fxattrop, frame, op_ret, op_errno, dict, xdata);
    return 0;
}


        int32_t tde_fxattrop(call_frame_t *frame, xlator_t *this, fd_t * fd,
	gf_xattrop_flags_t flags,
	dict_t * dict,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fxattrop_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fxattrop, fd, flags, dict, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fxattrop, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_removexattr_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(removexattr, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_removexattr(call_frame_t *frame, xlator_t *this, loc_t * loc,
	const char * name,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_removexattr_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->removexattr, loc, name, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(removexattr, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_fremovexattr_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(fremovexattr, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_fremovexattr(call_frame_t *frame, xlator_t *this, fd_t * fd,
	const char * name,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fremovexattr_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fremovexattr, fd, name, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fremovexattr, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_lk_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct gf_flock * lock,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(lk, frame, op_ret, op_errno, lock, xdata);
    return 0;
}


        int32_t tde_lk(call_frame_t *frame, xlator_t *this, fd_t * fd,
	int32_t cmd,
	struct gf_flock * lock,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_lk_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->lk, fd, cmd, lock, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(lk, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_inodelk_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(inodelk, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_inodelk(call_frame_t *frame, xlator_t *this, const char * volume,
	loc_t * loc,
	int32_t cmd,
	struct gf_flock * lock,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_inodelk_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->inodelk, volume, loc, cmd, lock, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(inodelk, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_finodelk_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(finodelk, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_finodelk(call_frame_t *frame, xlator_t *this, const char * volume,
	fd_t * fd,
	int32_t cmd,
	struct gf_flock * lock,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_finodelk_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->finodelk, volume, fd, cmd, lock, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(finodelk, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_entrylk_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(entrylk, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_entrylk(call_frame_t *frame, xlator_t *this, const char * volume,
	loc_t * loc,
	const char * basename,
	entrylk_cmd cmd,
	entrylk_type type,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_entrylk_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->entrylk, volume, loc, basename, cmd, type, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(entrylk, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_fentrylk_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(fentrylk, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_fentrylk(call_frame_t *frame, xlator_t *this, const char * volume,
	fd_t * fd,
	const char * basename,
	entrylk_cmd cmd,
	entrylk_type type,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fentrylk_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fentrylk, volume, fd, basename, cmd, type, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fentrylk, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_rchecksum_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, uint32_t weak_cksum,
	uint8_t * strong_cksum,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(rchecksum, frame, op_ret, op_errno, weak_cksum, strong_cksum, xdata);
    return 0;
}


        int32_t tde_rchecksum(call_frame_t *frame, xlator_t *this, fd_t * fd,
	off_t offset,
	int32_t len,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_rchecksum_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->rchecksum, fd, offset, len, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(rchecksum, frame, -1, errno, -1, NULL, NULL);
    return 0;
}


int32_t tde_readdir_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, gf_dirent_t * entries,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(readdir, frame, op_ret, op_errno, entries, xdata);
    return 0;
}


        int32_t tde_readdir(call_frame_t *frame, xlator_t *this, fd_t * fd,
	size_t size,
	off_t off,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_readdir_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->readdir, fd, size, off, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(readdir, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_readdirp_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, gf_dirent_t * entries,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(readdirp, frame, op_ret, op_errno, entries, xdata);
    return 0;
}


        int32_t tde_readdirp(call_frame_t *frame, xlator_t *this, fd_t * fd,
	size_t size,
	off_t off,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_readdirp_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->readdirp, fd, size, off, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(readdirp, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_setattr_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * statpre,
	struct iatt * statpost,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(setattr, frame, op_ret, op_errno, statpre, statpost, xdata);
    return 0;
}


        int32_t tde_setattr(call_frame_t *frame, xlator_t *this, loc_t * loc,
	struct iatt * stbuf,
	int32_t valid,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_setattr_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->setattr, loc, stbuf, valid, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(setattr, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_truncate_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * prebuf,
	struct iatt * postbuf,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(truncate, frame, op_ret, op_errno, prebuf, postbuf, xdata);
    return 0;
}


        int32_t tde_truncate(call_frame_t *frame, xlator_t *this, loc_t * loc,
	off_t offset,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_truncate_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->truncate, loc, offset, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(truncate, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_stat_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * buf,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(stat, frame, op_ret, op_errno, buf, xdata);
    return 0;
}


        int32_t tde_stat(call_frame_t *frame, xlator_t *this, loc_t * loc,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_stat_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->stat, loc, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(stat, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_lookup_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, inode_t * inode,
	struct iatt * buf,
	dict_t * xdata,
	struct iatt * postparent)
{
    STACK_UNWIND_STRICT(lookup, frame, op_ret, op_errno, inode, buf, xdata, postparent);
    return 0;
}


        int32_t tde_lookup(call_frame_t *frame, xlator_t *this, loc_t * loc,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_lookup_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->lookup, loc, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(lookup, frame, -1, errno, NULL, NULL, NULL, NULL);
    return 0;
}


int32_t tde_fsetattr_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * statpre,
	struct iatt * statpost,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(fsetattr, frame, op_ret, op_errno, statpre, statpost, xdata);
    return 0;
}


        int32_t tde_fsetattr(call_frame_t *frame, xlator_t *this, fd_t * fd,
	struct iatt * stbuf,
	int32_t valid,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fsetattr_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fsetattr, fd, stbuf, valid, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fsetattr, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_fallocate_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * pre,
	struct iatt * post,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(fallocate, frame, op_ret, op_errno, pre, post, xdata);
    return 0;
}


        int32_t tde_fallocate(call_frame_t *frame, xlator_t *this, fd_t * fd,
	int32_t keep_size,
	off_t offset,
	size_t len,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_fallocate_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->fallocate, fd, keep_size, offset, len, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(fallocate, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_discard_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * pre,
	struct iatt * post,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(discard, frame, op_ret, op_errno, pre, post, xdata);
    return 0;
}


        int32_t tde_discard(call_frame_t *frame, xlator_t *this, fd_t * fd,
	off_t offset,
	size_t len,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_discard_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->discard, fd, offset, len, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(discard, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_zerofill_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * pre,
	struct iatt * post,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(zerofill, frame, op_ret, op_errno, pre, post, xdata);
    return 0;
}


        int32_t tde_zerofill(call_frame_t *frame, xlator_t *this, fd_t * fd,
	off_t offset,
	off_t len,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_zerofill_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->zerofill, fd, offset, len, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(zerofill, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_ipc_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(ipc, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_ipc(call_frame_t *frame, xlator_t *this, int32_t op,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_ipc_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->ipc, op, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(ipc, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_seek_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, off_t offset,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(seek, frame, op_ret, op_errno, offset, xdata);
    return 0;
}


        int32_t tde_seek(call_frame_t *frame, xlator_t *this, fd_t * fd,
	off_t offset,
	gf_seek_what_t what,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_seek_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->seek, fd, offset, what, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(seek, frame, -1, errno, -1, NULL);
    return 0;
}


int32_t tde_getspec_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, char * spec_data)
{
    STACK_UNWIND_STRICT(getspec, frame, op_ret, op_errno, spec_data);
    return 0;
}


        int32_t tde_getspec(call_frame_t *frame, xlator_t *this, const char * key,
	int32_t flags)
{
    STACK_WIND(frame, tde_getspec_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->getspec, key, flags);
    return 0;
err:
    STACK_UNWIND_STRICT(getspec, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_lease_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct gf_lease * lease,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(lease, frame, op_ret, op_errno, lease, xdata);
    return 0;
}


        int32_t tde_lease(call_frame_t *frame, xlator_t *this, loc_t * loc,
	struct gf_lease * lease,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_lease_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->lease, loc, lease, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(lease, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_getactivelk_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, lock_migration_info_t * locklist,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(getactivelk, frame, op_ret, op_errno, locklist, xdata);
    return 0;
}


        int32_t tde_getactivelk(call_frame_t *frame, xlator_t *this, loc_t * loc,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_getactivelk_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->getactivelk, loc, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(getactivelk, frame, -1, errno, NULL, NULL);
    return 0;
}


int32_t tde_setactivelk_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, dict_t * xdata)
{
    STACK_UNWIND_STRICT(setactivelk, frame, op_ret, op_errno, xdata);
    return 0;
}


        int32_t tde_setactivelk(call_frame_t *frame, xlator_t *this, loc_t * loc,
	lock_migration_info_t * locklist,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_setactivelk_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->setactivelk, loc, locklist, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(setactivelk, frame, -1, errno, NULL);
    return 0;
}


int32_t tde_put_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, inode_t * inode,
	struct iatt * buf,
	struct iatt * preparent,
	struct iatt * postparent,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(put, frame, op_ret, op_errno, inode, buf, preparent, postparent, xdata);
    return 0;
}


        int32_t tde_put(call_frame_t *frame, xlator_t *this, loc_t * loc,
	mode_t mode,
	mode_t umask,
	uint32_t flags,
	struct iovec * vector,
	int32_t count,
	off_t off,
	struct iobref * iobref,
	dict_t * dict,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_put_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->put, loc, mode, umask, flags, vector, count, off, iobref, dict, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(put, frame, -1, errno, NULL, NULL, NULL, NULL, NULL);
    return 0;
}


int32_t tde_icreate_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, inode_t * inode,
	struct iatt * buf,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(icreate, frame, op_ret, op_errno, inode, buf, xdata);
    return 0;
}


        int32_t tde_icreate(call_frame_t *frame, xlator_t *this, loc_t * loc,
	mode_t mode,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_icreate_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->icreate, loc, mode, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(icreate, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_namelink_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * prebuf,
	struct iatt * postbuf,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(namelink, frame, op_ret, op_errno, prebuf, postbuf, xdata);
    return 0;
}


        int32_t tde_namelink(call_frame_t *frame, xlator_t *this, loc_t * loc,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_namelink_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->namelink, loc, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(namelink, frame, -1, errno, NULL, NULL, NULL);
    return 0;
}


int32_t tde_copy_file_range_cbk(call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt * stbuf,
	struct iatt * prebuf_dst,
	struct iatt * postbuf_dst,
	dict_t * xdata)
{
    STACK_UNWIND_STRICT(copy_file_range, frame, op_ret, op_errno, stbuf, prebuf_dst, postbuf_dst, xdata);
    return 0;
}


        int32_t tde_copy_file_range(call_frame_t *frame, xlator_t *this, fd_t * fd_in,
	off_t  off_in,
	fd_t * fd_out,
	off_t  off_out,
	size_t len,
	uint32_t flags,
	dict_t * xdata)
{
    STACK_WIND(frame, tde_copy_file_range_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->copy_file_range, fd_in, off_in, fd_out, off_out, len, flags, xdata);
    return 0;
err:
    STACK_UNWIND_STRICT(copy_file_range, frame, -1, errno, NULL, NULL, NULL, NULL);
    return 0;
}


int32_t tde_forget(xlator_t * this,
	inode_t * inode)
{
    return 0;
}


int32_t tde_release(xlator_t * this,
	fd_t * fd)
{
    return 0;
}


int32_t tde_releasedir(xlator_t * this,
	fd_t * fd)
{
    return 0;
}


int32_t tde_invalidate(xlator_t * this,
	inode_t * inode)
{
    return 0;
}


int32_t tde_client_destroy(xlator_t * this,
	client_t * client)
{
    return 0;
}


int32_t tde_client_disconnect(xlator_t * this,
	client_t * client)
{
    return 0;
}


void tde_ictxmerge(xlator_t * this,
	fd_t * fd,
	inode_t * inode,
	inode_t * linked_inode)
{
    return ;
}


int32_t tde_priv(xlator_t * this)
{
    return 0;
}


int32_t tde_inode(xlator_t * this)
{
    return 0;
}


int32_t tde_fd(xlator_t * this)
{
    return 0;
}


int32_t tde_inodectx(xlator_t * this,
	inode_t * ino)
{
    return 0;
}


int32_t tde_fdctx(xlator_t * this,
	fd_t * fd)
{
    return 0;
}


static int32_t tde_priv_to_dict(xlator_t *this, dict_t *dict, char *str) {
    if (str)
        snprintf(str, 256, "TDE Translator");
    
    return 0;
}



int32_t tde_inode_to_dict(xlator_t * this,
	dict_t * dict)
{
    return 0;
}


int32_t tde_fd_to_dict(xlator_t * this,
	dict_t * dict)
{
    return 0;
}


int32_t tde_inodectx_to_dict(xlator_t * this,
	inode_t * ino,
	dict_t * dict)
{
    return 0;
}


int32_t tde_fdctx_to_dict(xlator_t * this,
	fd_t * fd,
	dict_t * dict)
{
    return 0;
}


int32_t tde_history(xlator_t * this)
{
    return 0;
}


struct xlator_fops fops = {
        .fgetxattr            = tde_fgetxattr,
        .fsetxattr            = tde_fsetxattr,
        .setxattr             = tde_setxattr,
        .statfs               = tde_statfs,
        .fsyncdir             = tde_fsyncdir,
        .opendir              = tde_opendir,
        .fstat                = tde_fstat,
        .fsync                = tde_fsync,
        .flush                = tde_flush,
        .writev               = tde_writev,
        .readv                = tde_readv,
        .open                 = tde_open,
        .create               = tde_create,
        .link                 = tde_link,
        .rename               = tde_rename,
        .symlink              = tde_symlink,
        .rmdir                = tde_rmdir,
        .unlink               = tde_unlink,
        .mkdir                = tde_mkdir,
        .mknod                = tde_mknod,
        .readlink             = tde_readlink,
        .access               = tde_access,
        .ftruncate            = tde_ftruncate,
        .getxattr             = tde_getxattr,
        .xattrop              = tde_xattrop,
        .fxattrop             = tde_fxattrop,
        .removexattr          = tde_removexattr,
        .fremovexattr         = tde_fremovexattr,
        .lk                   = tde_lk,
        .inodelk              = tde_inodelk,
        .finodelk             = tde_finodelk,
        .entrylk              = tde_entrylk,
        .fentrylk             = tde_fentrylk,
        .rchecksum            = tde_rchecksum,
        .readdir              = tde_readdir,
        .readdirp             = tde_readdirp,
        .setattr              = tde_setattr,
        .truncate             = tde_truncate,
        .stat                 = tde_stat,
        .lookup               = tde_lookup,
        .fsetattr             = tde_fsetattr,
        .fallocate            = tde_fallocate,
        .discard              = tde_discard,
        .zerofill             = tde_zerofill,
        .ipc                  = tde_ipc,
        .seek                 = tde_seek,
        .getspec              = tde_getspec,
        .lease                = tde_lease,
        .getactivelk          = tde_getactivelk,
        .setactivelk          = tde_setactivelk,
        .put                  = tde_put,
        .icreate              = tde_icreate,
        .namelink             = tde_namelink,
        .copy_file_range      = tde_copy_file_range,
};
struct xlator_cbks cbks = {
        .forget               = tde_forget,
        .release              = tde_release,
        .releasedir           = tde_releasedir,
        .invalidate           = tde_invalidate,
        .client_destroy       = tde_client_destroy,
        .client_disconnect    = tde_client_disconnect,
        .ictxmerge            = tde_ictxmerge,
};
struct xlator_dumpops dumpops = {
        .priv                 = tde_priv,
        .inode                = tde_inode,
        .fd                   = tde_fd,
        .inodectx             = tde_inodectx,
        .fdctx                = tde_fdctx,
        .priv_to_dict         = tde_priv_to_dict,
        .inode_to_dict        = tde_inode_to_dict,
        .fd_to_dict           = tde_fd_to_dict,
        .inodectx_to_dict     = tde_inodectx_to_dict,
        .fdctx_to_dict        = tde_fdctx_to_dict,
        .history              = tde_history,
};


int32_t tde_init(xlator_t *this)
{
    /* Use gf_msg to log (if available) instead of printf */
    gf_msg(this->name, GF_LOG_DEBUG, 0, 0,
        "%s: Initializing TDE Translator...", this->name);

    pid_t pid = fork();
    if (pid < 0) {
        gf_msg(this->name, GF_LOG_ERROR, errno, 0,
            "%s: fork failed: %s", this->name, strerror(errno));
        return -errno;
    } else if (pid == 0) {
        /* In first child: perform a double-fork to detach from parent */
        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("Second fork failed");
            _exit(1);
        } else if (pid2 > 0) {
            /* First child exits so that the grandchild is re-parented to init */
            _exit(0);
        }
        /* In grandchild: detach from controlling terminal */
        if (setsid() < 0) {
            perror("setsid failed");
            _exit(1);
        }
        /* Execute the Python script */
        char *args[] = {"python3",
                        "/opt/glusterfs/xlators/features/tde/src/grpc_client.py",
                        "start",
                        NULL};
        execvp(args[0], args);
        /* If execvp returns, it failed */
        perror("execvp failed");
        _exit(1);
    }
    /* Parent: wait for the first child to prevent zombie */
    int status = 0;
    waitpid(pid, &status, 0);
    return 0;
}

static void tde_fini(xlator_t *this)
{
    return;
}

static int32_t tde_reconfigure(xlator_t *this, dict_t *dict)
{
    return 0;
}

static int tde_notify(xlator_t *this, int event, void *data, ...)
{
    return default_notify(this, event, data);
}

static int32_t tde_mem_acct_init(xlator_t *this)
{
    int ret = -1;

    ret = xlator_mem_acct_init(this, gf_tde_mt_end + 1);
    return ret;
}

static int32_t tde_dump_metrics(xlator_t *this, int fd)
{
    return 0;
}

static struct volume_options tde_options[] = {
    {
        .key            = "features.tde",
        .type           = GF_OPTION_TYPE_BOOL,
        .default_value  = "false",
        .op_version     = GD_OP_VERSION_6_0,
        .flags          = OPT_FLAG_SETTABLE,
        .tags           = "features",
        .description    = "Enable Transparent Data Encryption (TDE) for file I/O",
    },
    { .key = NULL }
};


// struct xlator_fops tde_fops = {
//     .lookup         = tde_lookup,
//     .open           = tde_open,
//     .opendir        = tde_opendir,
//     .readv          = tde_readv,
//     .writev         = tde_writev,
//     .truncate       = tde_truncate,
//     .ftruncate      = tde_ftruncate,
//     .getxattr       = tde_getxattr,
//     .fgetxattr      = tde_fgetxattr,
//     .setxattr       = tde_setxattr,
//     .fsetxattr      = tde_fsetxattr,
//     .removexattr    = tde_removexattr,
//     .fremovexattr   = tde_fremovexattr,
//     .stat           = tde_stat,
//     .fstat          = tde_fstat,
//     .copy_file_range= tde_copy_file_range,
//     /* Add additional FOP function pointers as needed */
// };
// struct xlator_cbks tde_cbks = {
//     .forget         = tde_forget,     /* e.g. a function that handles forgetting an inode */
//     .release        = tde_release,    /* e.g. a function to handle file descriptor release */
//     .releasedir     = tde_releasedir, /* e.g. a function to handle directory release */
//     /* Add additional callback pointers as needed */
// };

xlator_api_t xlator_api = {
    .init          = tde_init,
    .fini          = tde_fini,
    .notify        = tde_notify,
    .reconfigure   = tde_reconfigure,
    .mem_acct_init = tde_mem_acct_init,
    .dump_metrics  = tde_dump_metrics,
    .op_version    = GD_OP_VERSION_6_0,
    .fops          = &tde_fops,
    .cbks          = &tde_cbks,
    .options       = tde_options,  /* This is critical! */
    .identifier    = "tde",
    .category      = GF_MAINTAINED,
};
