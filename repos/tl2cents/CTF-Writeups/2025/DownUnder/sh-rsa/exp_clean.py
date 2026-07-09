#!/usr/bin/env python3
from pwn import remote, process
from Crypto.Util.number import long_to_bytes, bytes_to_long
from hashlib import shake_128
from sage.all import matrix, ZZ,  RealField, log
from math import prod
from tqdm import trange
import random


def H(N, m):
    return shake_128(long_to_bytes(N) + m).digest(8)

# Connection setup: switch to remote on challenge
local = True
# local = False

io = process(["python", "sh-rsa.py"]) if local else remote(
    "chal.2025.ductf.net", 30012
)

# Receive parameters
N = int(io.recvline().decode().split(' = ')[1].strip())
e = int(io.recvline().decode().split(' = ')[1].strip())

# Precompute target exponent bounds
bit_precision = 128
RR = RealField(bit_precision)
tgt = int.from_bytes(H(N, b'challenge'))
# to find \prod hi^ki = tgt << shift, we want tgt << shift to be as large as possible but not greater than n.
# therefore, we choose shift = 4096 - 64 - 8.
shift = 4096 - 64 - 8
# the exponent bounds are then:
exp_lb = int(RR(log(tgt << shift, 2)) * 2**bit_precision)
exp_ub = int(RR(log((tgt + 1) << shift, 2)) * 2**bit_precision)
exp_mid = (exp_ub + exp_lb) // 2 

diff = exp_ub - exp_lb
# the max error we can tolerate is: diff//2
diff_bit = diff.bit_length()
print(f"Max error: {diff.bit_length()} bits")

# Collect logs and ciphertexts
ms, cs, expons = [], [], []

for i in trange(92):
    pt = long_to_bytes(i)
    mi = bytes_to_long(H(N, pt))
    ms.append(mi)
    ci = eval(io.recvline().decode().strip().split(" ")[1].strip())
    cs.append(ci)
    expons.append(int(RR(log(mi, 2)) * 2**bit_precision))
    # expons.append(int(RR(log(mi), 2) * 2**bit_precision))

# number of samples for constructing lattice
n = 48
cnt = 0
while True:
    cnt += 1
    print(f"Attempted times: {cnt}...")
    sampled_idxs = random.sample(range(len(expons)), n)
    sampled_expons = [expons[i] for i in sampled_idxs]
    sampled_ms = [ms[i] for i in sampled_idxs]  
    sampled_cs = [cs[i] for i in sampled_idxs]
    sampled_expons.append(- exp_mid)

    mat = matrix(ZZ, n + 1, n + 2)
    # the target error bit
    error_bit = diff_bit - 2
    error = 2**error_bit
    coeff_rescale = 2**(error_bit)

    for i in range(n + 1):
        mat[i, 0] = sampled_expons[i]
        mat[i, i + 1] = coeff_rescale

    mat[-1, -1] = error
    L = mat.LLL()
    L = L.BKZ(block_size = 10)

    for row in L:
        if row[-1] == error:
            coeffs = [int(num//coeff_rescale) for num in row[1:-1]]
            res = exp_mid + row[0]
            real_error_bit = row[0].bit_length()
            print(f"Found a possible valid row, check {exp_lb < res  < exp_ub = }")
            print(f"Coefficients: {coeffs} {sum(coeffs) = } {real_error_bit = }")
            if all(c >= 0 for c in coeffs) and exp_lb < res  < exp_ub:
                print(f"Valid coefficients: {coeffs}")
                # valid coefficients found, compute the signature
                result_bytes = long_to_bytes(prod([m**coeff for m, coeff in zip(sampled_ms, coeffs)]))
                print(f"Target Hex: {H(N, b'challenge').hex()}")
                print(f"Result: {result_bytes.hex()[:16]}")
                sig = 1
                for ci, coeff in zip(sampled_cs, coeffs):
                    sig *= pow(ci, coeff, N)
                    sig %= N
                # sig = prod([pow(c, coeff, n) for c, coeff in zip(cs, coeffs)])
                io.sendlineafter(b's: ', long_to_bytes(sig).hex().encode())
                io.interactive()
                exit(0)