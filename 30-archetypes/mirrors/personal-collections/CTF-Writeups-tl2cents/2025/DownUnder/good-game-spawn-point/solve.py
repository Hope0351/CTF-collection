from pwn import remote, process, context, log
from Crypto.Util.number import getPrime
import os
from sage.all import GF, ZZ, EllipticCurve, discrete_log
import json
import secrets

def paillier_decrypt(ciphertext, n, lambda_n, mu):
    nsq = n * n
    # Decrypt using the Paillier decryption formula
    u = pow(ciphertext, lambda_n, nsq)
    plaintext = ((u - 1) // n) * mu % n
    return plaintext

def paillier_encrypt(plaintext, n):
    nsq = n * n
    r = secrets.randbelow(n)
    g = n + 1
    # Encrypt using the Paillier encryption formula
    ciphertext = (pow(g, plaintext, nsq) * pow(r, n, nsq)) % nsq
    return ciphertext

p = 0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff
K = GF(p)
a = K(0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc)
b = K(0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b)
E = EllipticCurve(K, (a, b))
G = E(0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296, 0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5)
E.set_order(0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551 * 0x1)
order = 0xFFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551 * 0x1

# AU: nc chal.2025.ductf.net 30011
# US: nc chal.2025-us.ductf.net 30011
local = True
io = remote("chal.2025.ductf.net", 30011) if not local else process(["python", "chal.py"])

io.recvuntil(b"public key:")
public_key = json.loads(io.recvline().decode().strip().replace("'", '"'))
Qx = public_key["x"]
Qy = public_key["y"]
Q = E(Qx, Qy)
io.recvuntil(b"paillier key:")
paillier_key = json.loads(io.recvline().decode().strip().replace("'", '"'))
n = paillier_key["p"] * paillier_key["q"]
n_bitlength = n.bit_length()
lambda_n = (paillier_key["p"] - 1) * (paillier_key["q"] - 1)
mu = pow(lambda_n, -1, n)

dlog_bit = 43
# 52 * 5 = 256
Bs = []
alphas = []
for i in range(1, 6):
    ct = paillier_encrypt(2**(n_bitlength - 256 + i * dlog_bit), n)
    io.sendlineafter(b"ciphertext:", str(ct).encode())
    io.recvuntil(b"mta response:")
    mta_response = int(io.recvline().decode().strip())
    io.recvuntil(b"zk schnorr:")
    zk_schnorr = json.loads(io.recvline().decode().strip().replace("'", '"'))
    Bx = zk_schnorr["beta_pub"]["x"]
    By = zk_schnorr["beta_pub"]["y"]
    B = E(Bx, By)
    # alpha = 2**m * s + beta % n
    alpha = paillier_decrypt(mta_response, n, lambda_n, mu)
    Bs.append(B)
    alphas.append(alpha)

# try dlog
nG = (n % order) * G
secret = 0
print("Trying to find secret...")
secret_ub = 2**256
secret_lb = 0
ks = []
for i in range(1, 6):
    B = Bs[i - 1]
    alpha = alphas[i - 1]
    m = (n_bitlength - 256 + i * dlog_bit)
    # alpha = 2**m * s + beta % n
    # alpha = 2**m * s + beta - kn
    A = alpha * G
    # A = (2**m) Q + B - k nG
    Y = (2**m) * Q + B - A
    # try discrete logarithm
    if i == 1:
        print(f"i: {i}, dlog interval: {dlog_bit + 1} bits")
        k = discrete_log(Y, nG, bounds=[0, 2**(dlog_bit + 1)], operation="+")
    else:
        # alpha_i = 2**(m + delta) * s + beta_i - k_i * n < 2**delta (alpha_{i-1} + k_{i-1} n) + beta_i - k_i n
        # k_i < (2**delta * (alpha_{i-1} + k_{i-1} n) + beta_i - alpha_i) / n
        # k_i > (2**delta * (alpha_{i-1} + (k_{i-1} - 1) n) + beta_i - alpha_i) / n
        k_i_ub = (2**dlog_bit * (alphas[i - 2] + ks[-1] * n) + n - alphas[i - 1]) // n
        k_i_lb = (2**dlog_bit * (alphas[i - 2] + (ks[-1] - 1) * n) + 0 - alpha + n) // n
        dlog_interval = int(k_i_ub - k_i_lb)
        print(f"i: {i}, dlog interval: {dlog_interval.bit_length()} bits")
        k = discrete_log(Y, nG, bounds=[k_i_lb, k_i_ub], operation="+")
    print(f"i: {i}, k: {k}")
    ks.append(k)
    # alpha = 2**m * s + beta - kn
    # 0 < alpha + kn -  2**m * s < n
    # alpha + (k-1)n < 2**m * s  < alpha + kn

k = ks[-1]
alpha = alphas[-1]
m = (n_bitlength - 256 + 5 * dlog_bit)
secret_lb = (alpha + (k-1) * n) // 2**m
secret_ub =  (alpha + k* n) // 2**m
dlog_interval = int(secret_ub - secret_lb).bit_length()
print(f"Final remaining {dlog_interval} bits")
secret = discrete_log(Q, G, bounds=[secret_lb, secret_ub], operation="+")
print(f"Secret found: {secret}")
io.sendlineafter(b"secret:", str(secret).encode())
io.interactive()