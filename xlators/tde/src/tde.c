#include "glusterfs/api/glfs.h"
#include "tde.h"
#include <grpc/grpc.h>
#include <grpc/tde.grpc.pb-c.h>

int
tde_writev(call_frame_t *frame, xlator_t *this, fd_t *fd, struct iovec *vector,
           int count, off_t offset, struct iatt *prebuf, struct iatt *postbuf)
{
    /* Combine iovec chunks into a single buffer */
    char *chunk_data = combine_iovec(vector, count);

    /* Call Python gRPC service to encrypt the chunk */
    char *encrypted_data = call_grpc_encrypt(chunk_data);

    /* Pass encrypted data downstream */
    struct iovec encrypted_vector = { .iov_base = encrypted_data,
                                      .iov_len = strlen(encrypted_data) };
    STACK_WIND(frame, next_writev, fd, &encrypted_vector, 1, offset, prebuf,
               postbuf);
    return 0;
}
