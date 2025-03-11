#include <ctype.h>
#include <sys/uio.h>
#include <glusterfs/glusterfs.h>
#include <glusterfs/xlator.h>
#include <glusterfs/logging.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

// A structure to hold the private data for TDE

// The encryption and decryption routines using AES (as an example)
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

    if (!this->children || this->children->next) {
        gf_log("tde", GF_LOG_ERROR, "FATAL: TDE should have exactly one child");
        return -1;
    }

    if (!this->parents) {
        gf_log(this->name, GF_LOG_WARNING, "dangling volume. check volfile ");
    }

    priv = GF_CALLOC(sizeof(tde_private_t), 1, 0);
    if (!priv)
        return -1;

    priv->decrypt_read = 1;  // Default: decrypt on read
    priv->encrypt_write = 1; // Default: encrypt on write

    data = dict_get(this->options, "encrypt-write");
    if (data) {
        if (gf_string2boolean(data->data, &priv->encrypt_write) == -1) {
            gf_log(this->name, GF_LOG_ERROR, "encrypt-write takes only boolean options");
            GF_FREE(priv);
            return -1;
        }
    }

    data = dict_get(this->options, "decrypt-read");
    if (data) {
        if (gf_string2boolean(data->data, &priv->decrypt_read) == -1) {
            gf_log(this->name, GF_LOG_ERROR, "decrypt-read takes only boolean options");
            GF_FREE(priv);
            return -1;
        }
    }

    // Set the encryption key (in real use, this should come from a key manager)
    if (RAND_bytes((unsigned char *)&priv->enc_key, sizeof(AES_KEY)) != 1) {
        gf_log(this->name, GF_LOG_ERROR, "Failed to generate encryption key");
        GF_FREE(priv);
        return -1;
    }

    // Set the decryption key (same as the encryption key for simplicity)
    priv->dec_key = priv->enc_key;

    this->private = priv;
    gf_log("tde", GF_LOG_DEBUG, "TDE xlator loaded");
    return 0;
}

// Finalize the TDE translator
void fini(xlator_t *this) {
    tde_private_t *priv = this->private;

    if (!priv)
        return;
    this->private = NULL;
    GF_FREE(priv);
}

struct xlator_fops fops = {
    .readv = tde_readv,
    .writev = tde_writev
};

struct xlator_cbks cbks = {
};

struct volume_options options[] = {
    {.key = {"tde-enabled"}, .type = GF_OPTION_TYPE_BOOL, .default_value = "off"},
    {.key = {"encrypt-write"}, .type = GF_OPTION_TYPE_BOOL},
    {.key = {"decrypt-read"}, .type = GF_OPTION_TYPE_BOOL},
    {.key = {NULL}},
};
