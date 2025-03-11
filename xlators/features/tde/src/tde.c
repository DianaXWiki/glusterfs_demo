#include <ctype.h>
#include <sys/uio.h>
#include <glusterfs/glusterfs.h>
#include <glusterfs/xlator.h>
#include <glusterfs/logging.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include "tde.h"
#include "tde-messages.h"
#include "tde-mem-types.h"

void aes_encrypt(char *data, int len, AES_KEY *key) {
    unsigned char iv[AES_BLOCK_SIZE] = {0};  // Simple IV, should be random in production
    unsigned char out[AES_BLOCK_SIZE];
    
    for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt((unsigned char*)&data[i], out, AES_BLOCK_SIZE, key, iv, AES_ENCRYPT);
        memcpy(&data[i], out, AES_BLOCK_SIZE);
    }
}

void aes_decrypt(char *data, int len, AES_KEY *key) {
    unsigned char iv[AES_BLOCK_SIZE] = {0};  // Simple IV, should be random in production
    unsigned char out[AES_BLOCK_SIZE];

    for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt((unsigned char*)&data[i], out, AES_BLOCK_SIZE, key, iv, AES_DECRYPT);
        memcpy(&data[i], out, AES_BLOCK_SIZE);
    }
}

// Callback function for read operations, performing decryption
int32_t tde_readv_cbk(call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, struct iovec *vector,
                      int32_t count, struct iatt *stbuf, struct iobref *iobref,
                      dict_t *xdata) {
    tde_private_t *priv = (tde_private_t *)this->private;

    if (priv->decrypt_read) {
        for (int i = 0; i < count; i++) {
            aes_decrypt(vector[i].iov_base, vector[i].iov_len, &priv->dec_key);
        }
    }

    STACK_UNWIND_STRICT(readv, frame, op_ret, op_errno, vector, count, stbuf, iobref, xdata);
    return 0;
}

// Read operation handler
int32_t tde_readv(call_frame_t *frame, xlator_t *this, fd_t *fd, size_t size,
                  off_t offset, uint32_t flags, dict_t *xdata) {
    STACK_WIND(frame, tde_readv_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->readv, fd, size, offset, flags, xdata);
    return 0;
}

// Callback function for write operations, performing encryption
int32_t tde_writev_cbk(call_frame_t *frame, void *cookie, xlator_t *this,
                       int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                       struct iatt *postbuf, dict_t *xdata) {
    STACK_UNWIND_STRICT(writev, frame, op_ret, op_errno, prebuf, postbuf, xdata);
    return 0;
}

// Write operation handler
int32_t tde_writev(call_frame_t *frame, xlator_t *this, fd_t *fd,
                   struct iovec *vector, int32_t count, off_t offset, uint32_t flags,
                   struct iobref *iobref, dict_t *xdata) {
    tde_private_t *priv = (tde_private_t *)this->private;

    if (priv->encrypt_write) {
        for (int i = 0; i < count; i++) {
            aes_encrypt(vector[i].iov_base, vector[i].iov_len, &priv->enc_key);
        }
    }

    STACK_WIND(frame, tde_writev_cbk, FIRST_CHILD(this),
               FIRST_CHILD(this)->fops->writev, fd, vector, count, offset, flags, iobref, xdata);
    return 0;
}

// Initialize the TDE translator
int32_t init(xlator_t *this) {
    data_t *data = NULL;
    tde_private_t *priv = NULL;

    if (!this) {
        gf_msg("tde", GF_LOG_ERROR, 0, TDE_MSG_NULL_THIS,
               "this is NULL. init() failed");
        return -1;
    }

    if (!this->parents) {
        gf_msg(this->name, GF_LOG_ERROR, 0, TDE_MSG_INVALID_VOLFILE,
               "Dangling volume. Check volfile");
        goto out;
    }

    if (!this->children || this->children->next) {
        gf_msg(this->name, GF_LOG_ERROR, 0, TDE_MSG_INVALID_VOLFILE,
               "tde not configured with exactly one sub-volume. "
               "Check volfile");
        goto out;
    }
    priv = GF_CALLOC(1, sizeof(tde_private_t), gf_tde_mt_priv_t);
    if (!priv)
        goto out;

        GF_OPTION_INIT("tde", priv->tde_enabled, bool, out);
        GF_OPTION_INIT("tde-encrypt-write", priv->encrypt_write, bool, out);
        GF_OPTION_INIT("tde-decrypt-read", priv->decrypt_read, bool, out);

   

    // Set the encryption key (in real use, this should come from a key manager)
    if (RAND_bytes((unsigned char *)&priv->enc_key, sizeof(AES_KEY)) != 1) {
        gf_log(this->name, GF_LOG_ERROR, "Failed to generate encryption key");
        GF_FREE(priv);
        return -1;
    }

    // Set the decryption key (same as the encryption key for simplicity)
    priv->dec_key = priv->enc_key;

    this->private = priv;
    LOCK_INIT(&priv->lock);
    gf_log("tde", GF_LOG_DEBUG, "TDE xlator loaded");
    ret = 0;
out:
    if (ret) {
        GF_FREE(priv);
    }

    return ret;
}

// Finalize the TDE translator
void fini(xlator_t *this) {
    tde_private_t *priv = this->private;

    GF_VALIDATE_OR_GOTO("tde", this, out);
    this->itable = NULL;

    // mem_pool_destroy(this->local_pool);
    // this->local_pool = NULL;

    priv = this->private;
    if (!priv)
        goto out;

    //shard_unlink_handler_fini(&priv->thread_info);

    this->private = NULL;
    LOCK_DESTROY(&priv->lock);
    GF_FREE(priv);

out:
    return;
}

int
reconfigure(xlator_t *this, dict_t *options)
{
    int ret = -1;
    tde_private_t *priv = NULL;

    priv = this->private;

    GF_OPTION_RECONF("tde-encrypt-write", priv->encrypt_write, options, uint64, out);

    GF_OPTION_RECONF("tde-decrypt-read", priv->decrypt_read, options, uint64,
                     out);
    ret = 0;

out:
    return ret;
}

struct xlator_fops fops = {
    .readv = tde_readv,
    .writev = tde_writev
};

struct xlator_cbks cbks = {
};

struct volume_options options[] = {
    {
        .key = {"tde"},
        .type = GF_OPTION_TYPE_BOOL,
        .default_value = "off",
        .description = "enable/disable tde",
        .op_version = {GD_OP_VERSION_6_0},
        .flags = OPT_FLAG_SETTABLE,
    },
    {.key = {"tde-encrypt-write"}, .type = GF_OPTION_TYPE_BOOL,  .tags = {"tde"},},
    {.key = {"tde-decrypt-read"}, .type = GF_OPTION_TYPE_BOOL,  .tags = {"tde"},},
    {.key = {NULL}},
};

xlator_api_t xlator_api = {
    .init = init,
    .fini = fini,
    .reconfigure = reconfigure,
    //.mem_acct_init = mem_acct_init,
    .op_version = {1}, /* Present from the initial version */
    //.dumpops = &dumpops,
    .fops = &fops,
    .cbks = &cbks,
    .options = options,
    .identifier = "tde",
    .category = GF_MAINTAINED,
};
