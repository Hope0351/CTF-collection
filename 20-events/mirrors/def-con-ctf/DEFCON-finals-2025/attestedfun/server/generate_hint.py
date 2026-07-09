from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import binascii
import sys


def generate_secret_hex(plaintext: str, key: str) -> str:
    """
    Encrypt `plaintext` with AES-128-CBC (PKCS7), zero IV, using `key` (16 ASCII chars),
    and return the ciphertext as a hex string.
    """
    if len(key) != 16:
        raise ValueError("Key must be exactly 16 characters")
    iv = b'\x00' * 16
    cipher = AES.new(key.encode('ascii'), AES.MODE_CBC, iv)
    pt_bytes = plaintext.encode('utf-8')
    ct = cipher.encrypt(pad(pt_bytes, AES.block_size))
    return binascii.hexlify(ct).decode('ascii')


r = generate_secret_hex(sys.argv[1], "dHNhZDUyMwZUiKBS")

print('const HINT: &str = "'+r+'";')

