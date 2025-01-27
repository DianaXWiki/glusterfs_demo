from cryptography.fernet import Fernet

# Generate or securely load the encryption key
KEY = Fernet.generate_key()
cipher = Fernet(KEY)

def encrypt_data(chunk):
    """Encrypts a chunk of data."""
    return cipher.encrypt(chunk)

def decrypt_data(encrypted_chunk):
    """Decrypts an encrypted chunk of data."""
    return cipher.decrypt(encrypted_chunk)
