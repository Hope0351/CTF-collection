from tqdm import trange
from pwn import remote, process
from hashlib import sha256
from Crypto.Util.number import bytes_to_long, long_to_bytes
from secrets import randbits
import HashTools

def encrypt(msg: bytes, io: remote):
    io.sendlineafter(b'> ', b'1')
    io.sendlineafter(b'Username: ', msg)
    res =  io.recvline().strip().decode().partition(':')[2]
    msg, _, mac = bytes.fromhex(res).partition(b'|')
    return msg, mac

def verify(msg: bytes, mac: bytes, io: remote):
    io.sendlineafter(b'> ', b'2')
    io.sendlineafter(b'Token: ', (msg + b'|' + mac).hex().encode())
    return b'Failed' not in io.recvline().strip()

def bit_i(n, i):
    return (n >> i) & 1

def local_encrypt(inp: int):
    # r = randbits(1024)
    r = 2
    g = n + 1
    n2 = n * n
    c = pow(g, inp, n2) * pow(r, n, n2) % n2
    return c

local = True
# local = False

# nc chal.2025-us.ductf.net 30010
# nc chal.2025.ductf.net 30010
io = process(["python3", "./chall.py"]) if local else remote('chal.2025-us.ductf.net', 30010)

n = int(io.recvline().strip().decode())
n2 = n * n
print(f"{n.bit_length()} bits")
# pad the message for sha256 to 64 bytes, one block
# uname = b"a" * (64 - 16 - 5)
uname = b"a"
msg, mac = encrypt(uname, io)
print(f"Message: {msg}, MAC: {mac.hex()}")
# recover the hash of the message through the decrypt oracle
n_bit = n.bit_length()
assert bit_i(n, n_bit - 1) == 1
known_bits = ""
mac_val = bytes_to_long(mac)

c = local_encrypt(-2**(n_bit - 1))

for i in trange(256):
    if i > 0:
        unknown_mac = local_encrypt(-int(known_bits + '0' * (256 - len(known_bits)), 2)) * mac_val % n2
    else:
        unknown_mac = mac_val
    unknown_mac_shifted = pow(unknown_mac, 2**(n_bit - 256 + i), n2)
    # mac of : h' || 0...0 || h where h chunk is 32 bytes and h' is aligned to the msb of n.
    combined = unknown_mac_shifted * mac_val % n2
    ct = c * combined % n2
    if verify(msg, long_to_bytes(ct), io):
        # m - 2**n_bit valid
        known_bits += '1'
    else:
        # m - 2**n_bit invalid
        known_bits += '0'


# import HashTools
# from os import urandom

# # setup context
# secret = urandom(16)        # idk ¯\_(ツ)_/¯
# original_data = b"&admin=False"
# sig = HashTools.new(algorithm="sha256", raw=secret+original_data).hexdigest()
# # attack
# append_data = b"&admin=True"
# magic = HashTools.new("sha256")
# new_data, new_sig = magic.extension(
#     secret_length=16, original_data=original_data,
#     append_data=append_data, signature=sig
# )

magic = HashTools.new("sha256")
hashout = int(known_bits, 2).to_bytes(32, 'big')
print(f"Known Hash: {hashout.hex()}") 
extended = b'user=admin'
new_data, new_sig = magic.extension(
    secret_length=16, original_data=msg,
    append_data=extended, signature=hashout.hex()
)
print(f"New data: {new_data}, New sig: {new_sig}")
new_sig = bytes.fromhex(new_sig)
new_mac = long_to_bytes(local_encrypt(bytes_to_long(new_sig)))
check = verify(new_data, new_mac, io)
if check:
    print("Success! Admin access granted.")
    print(io.recvline().strip().decode())
else:
    print("Failed to gain admin access.")
io.close()