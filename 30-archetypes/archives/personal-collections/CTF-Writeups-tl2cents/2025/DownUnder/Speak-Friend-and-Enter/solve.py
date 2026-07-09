from Crypto.Cipher import AES
from Crypto.Util.number import bytes_to_long, long_to_bytes, isPrime
from Crypto.Util.py3compat import bord
from Crypto.Util.strxor import strxor
from Crypto.Hash import CMAC, SHA512
import os
from binascii import unhexlify
from pwn import remote, process
import json

BLOCK_SIZE = 16
RB = 0x87

def _shift_bytes(bs, xor_lsb=0):
    num = (bytes_to_long(bs) << 1) ^ xor_lsb
    return long_to_bytes(num, len(bs))[-len(bs):]

def aes_cbc_mac(key: bytes, data: bytes) -> bytes:
    cipher_ecb = AES.new(key, AES.MODE_ECB)
    L = cipher_ecb.encrypt(b'\x00' * BLOCK_SIZE)
    cipher_cbc = AES.new(key, AES.MODE_CBC, iv = b"\x00" * BLOCK_SIZE)
    if len(data) % BLOCK_SIZE != 0:
        data += b'\x80' + b'\x00' * (BLOCK_SIZE - len(data) % BLOCK_SIZE - 1)
    if bord(L[0]) & 0x80:
        K1 = _shift_bytes(L, RB)
    else:
        K1 = _shift_bytes(L)
    if bord(K1[0]) & 0x80:
        K2 = _shift_bytes(K1, RB)
    else:
        K2 = _shift_bytes(K1)
    ct = cipher_cbc.encrypt(data)
    assert len(ct) == len(data)
    if len(data) >= 2*BLOCK_SIZE:
        second_last = ct[-2*BLOCK_SIZE:-BLOCK_SIZE]
    else:
        second_last = b"\x00" * BLOCK_SIZE
    last_pt = strxor(second_last, data[-BLOCK_SIZE:])
    return cipher_ecb.encrypt(strxor(last_pt, K1))

def forge_cbc_mac(key: bytes, target_mac: bytes, total_bytes: int):
    assert total_bytes % BLOCK_SIZE == 0
    n_blocks = total_bytes // BLOCK_SIZE
    cipher_ecb = AES.new(key, AES.MODE_ECB)
    L = cipher_ecb.encrypt(b'\x00' * BLOCK_SIZE)
    if bord(L[0]) & 0x80:
        K1 = _shift_bytes(L, RB)
    else:
        K1 = _shift_bytes(L)
    
    c_last = os.urandom(BLOCK_SIZE)
    pt_last = strxor(strxor(cipher_ecb.decrypt(target_mac), K1), c_last)
    pt_blocks_reverse = [pt_last]
    for i in range(n_blocks - 1):
        if i == n_blocks - 2:
            # the iv is zero block
            new_c_last = b"\x00" * BLOCK_SIZE
        else:
            new_c_last = os.urandom(BLOCK_SIZE)
        pt_last = strxor(cipher_ecb.decrypt(c_last), new_c_last)
        pt_blocks_reverse.append(pt_last)
        c_last = new_c_last
    pt_blocks_reverse.reverse()
    return b''.join(pt_blocks_reverse)
    

def test():
    NIST_SP_800_38B_Appendix_D1_K = bytes.fromhex("2b7e1516 28aed2a6 abf71588 09cf4f3c".replace(" ", ""))
    cc = CMAC.new(NIST_SP_800_38B_Appendix_D1_K, ciphermod=AES)
    mac1 = cc.update(b"\x00" * 32).digest()
    mac2 = aes_cbc_mac(NIST_SP_800_38B_Appendix_D1_K, b"\x00" * 32)
    print(f"{mac1.hex() = }")
    print(f"{mac2.hex() = }")
    print(f"{mac2.hex() == mac1.hex() }")
    fake = forge_cbc_mac(NIST_SP_800_38B_Appendix_D1_K, mac2, 64)
    print(f"{fake.hex() = }")
    new_mac = aes_cbc_mac(NIST_SP_800_38B_Appendix_D1_K, fake)
    print(f"{new_mac.hex() = }")
    print(f"{new_mac.hex() == mac1.hex() }")

# NIST_SP_800_38B_Appendix_D1_K = bytes.fromhex("2b7e1516 28aed2a6 abf71588 09cf4f3c".replace(" ", ""))
# server_cmac_publickey = unhexlify('9d4dfd27cb483aa0cf623e43ff3d3432')
# cc = CMAC.new(NIST_SP_800_38B_Appendix_D1_K, ciphermod=AES)
# while True:
#     n_bytes = forge_cbc_mac(NIST_SP_800_38B_Appendix_D1_K, server_cmac_publickey, 2048 // 8)
#     n = int.from_bytes(n_bytes, 'big')
#     if n.bit_length() == 2048 and isPrime(n):
#         print(f"Found a valid public key: {n = }")
#         break

# https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38b.pdf
NIST_SP_800_38B_Appendix_D1_K = bytes.fromhex("2b7e1516 28aed2a6 abf71588 09cf4f3c".replace(" ", ""))
server_cmac_publickey = unhexlify('9d4dfd27cb483aa0cf623e43ff3d3432')
cc = CMAC.new(NIST_SP_800_38B_Appendix_D1_K, ciphermod=AES)
n = 28820206493588447008746090302284853639546136320404095125596636689682406385330694351586552922448711589443889356163596369278846074364251272231248429321834561757745426629442454937402033815450095576613352750744923297708600469312419911793921000880934167630401641828848304372984776245020443492178546750689178398279995393079144743297808780124266558952497251752972959691023618031531852504193197592266358140473437876604403520546254594953657774538929287289388355804827986934647490748008085045301844184757662277098954042039096481144682656347068460759940523129002797879162375689266082142897452515887446952422551354193755368485111

assert cc.update(long_to_bytes(n)).digest() == server_cmac_publickey
# AU: nc chal.2025.ductf.net 30008
# US: nc chal.2025-us.ductf.net 30008
io = remote('chal.2025.ductf.net', 30008)

io.recvuntil(b"challenge string: ")
challenge_string = io.recvline().strip()
hm = bytes_to_long(SHA512.new(challenge_string).digest())
d = pow(65537, -1, n - 1)
sig = pow(hm, d, n)
io.sendline(json.dumps({"public_key": n, "signature": sig}).encode())
io.interactive()