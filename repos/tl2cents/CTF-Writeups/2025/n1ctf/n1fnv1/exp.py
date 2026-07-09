import os, secrets, signal
from collections import deque
from math import ceil, log2, gcd
from pwn import remote, process
from tqdm import tqdm

def hash(params, msg):
    a, b, c, m, x = params
    for byte in msg:
        for bit in f'{byte:08b}':
            x = ((x * a + b + int(bit)) ^ c) % m
    return x

def hash_bits(params, bits):
    a, b, c, m, x = params
    for bit in bits:
        x = ((x * a + b + int(bit)) ^ c) % m
    return x

# Global variables for optimization
GLOBAL_A = None
GLOBAL_B = None
GLOBAL_C = None
GLOBAL_M = None
GLOBAL_TARGET = None
GLOBAL_A_INV_CACHE = {}  # Cache for modular inverses at different bit widths


def forward_step(x_init, nbit, steps, valid_paths):
    """ Generate all forward states after 'steps' using valid_paths, which is used in mitm
    """
    a, b, c, m = GLOBAL_A, GLOBAL_B, GLOBAL_C, GLOBAL_M
    mod_mask = (1 << nbit) - 1
    n_choices = len(valid_paths)
    deque_states = deque()
    deque_states.append((x_init & mod_mask, []))
    while deque_states:
        state, path = deque_states.popleft()
        if len(path) == steps:
            yield (state, path)
            continue
        for idx in range(n_choices):
            new_state = state
            new_path = path + [idx]
            for bit in valid_paths[idx]:
                new_state = ((new_state * a + b + bit) ^ c) & mod_mask
            deque_states.append((new_state, new_path))
            
def backward_step(state_target, nbit, steps, valid_paths):
    """ Generate all backward states after 'steps' using valid_paths, which is used in mitm
    """
    a, b, c, m = GLOBAL_A, GLOBAL_B, GLOBAL_C, GLOBAL_M
    mod_mask = (1 << nbit) - 1
    
    # Compute modular inverse of a modulo 2^nbit (a is odd, so inverse exists)
    if nbit not in GLOBAL_A_INV_CACHE:
        GLOBAL_A_INV_CACHE[nbit] = pow(a, -1, 1 << nbit)
    a_inv = GLOBAL_A_INV_CACHE[nbit]
    
    def inv_step(state, bit):
        """Inverse of: next = ((prev * a + b + bit) ^ c) mod 2^nbit"""
        # By adding m before the final modulo, we prevent Python from
        # dealing with negative numbers in a slow way.
        return (((state ^ c) - b - bit) * a_inv + m) & mod_mask
    
    n_choices = len(valid_paths)
    deque_states = deque()
    deque_states.append((state_target & mod_mask, []))
    while deque_states:
        state, path = deque_states.popleft()
        if len(path) == steps:
            yield (state, path)
            continue
        for idx in range(n_choices):
            new_state = state
            new_path = [idx] + path
            for bit in reversed(valid_paths[idx]):
                new_state = inv_step(new_state, bit)
            deque_states.append((new_state, new_path))


def find_lsb_path_mitm(x_init, nbit, steps, valid_paths=None, findall=True):
    """
    Optimized meet-in-the-middle approach for arbitrary valid_paths.
    Uses global parameters for better performance.
    Much faster than BFS for large step counts - O(N^(steps/2)) instead of O(N^steps).
    where N is the number of valid_paths.
    """
    global GLOBAL_A, GLOBAL_B, GLOBAL_C, GLOBAL_M, GLOBAL_TARGET, GLOBAL_A_INV_CACHE
    
    a, b, c, m, target = GLOBAL_A, GLOBAL_B, GLOBAL_C, GLOBAL_M, GLOBAL_TARGET
    mod_mask = (1 << nbit) - 1
    
    # Default to binary choices if not specified
    if valid_paths is None:
        valid_paths = [[0], [1]]
    
    n_choices = len(valid_paths)
    stride = len(valid_paths[0])  # Length of each path segment
    
    # Split steps into two halves
    k = steps // 2
    r = steps - k
    
    print(f"[MITM] Forward: {k} steps, Backward: {r} steps (total: {steps}), {n_choices} choices, stride: {stride}")
    
    # Forward phase: compute all states after k steps
    # Map: state -> list of (path_indices_tuple)
    forward = {}
    total_forward = n_choices ** k
    
    if total_forward > 1000000:
        print(f"[MITM] Warning: Forward phase has {total_forward} combinations, this may be slow...")
    
    for state, path in tqdm(forward_step(x_init, nbit, k, valid_paths), total=total_forward, desc="[MITM] Forward phase"):
        path_indices = tuple(path)
        if state not in forward:
            forward[state] = []
        forward[state].append(path_indices)
    print(f"[MITM] Forward phase done: {len(forward)} unique states")
    
    # Backward phase: search for collisions
    total_backward = n_choices ** r
    results = []
    for state, path_indices in tqdm(backward_step(target, nbit, r, valid_paths), total=total_backward, desc="[MITM] Backward phase"):
        if state in forward:
            # Reconstruct full path
            for path_indices1 in forward[state]:
                full_path_indices = list(path_indices1) + list(path_indices)
                full_path = []
                for idx in full_path_indices:
                    full_path.extend(valid_paths[idx])
                if findall:
                    results.append(full_path)
                else:
                    return full_path
    if findall:
        return results
    
    
local = False  # Set to True for local testing
nbits = 128
if local:
    rand = lambda: secrets.randbits(nbits)
    print('⚙️', params := (rand() | 1, rand(), rand(), 2 ** nbits, rand()))
    print('🎯', target := rand())
else:
    # tcp 60.205.163.215:10357
    # 60.205.163.215:36371
    conn = remote('60.205.163.215', 36371)
    conn.recvuntil('⚙️'.encode())
    params_line = conn.recvline().decode().strip().strip("()")
    a_str, b_str, c_str, m_str, x_init_str = params_line.split(', ')
    params = (int(a_str), int(b_str), int(c_str), int(m_str), int(x_init_str))
    conn.recvuntil('🎯'.encode())
    target_line = conn.recvline().decode().strip()
    target = int(target_line)
    

# Initialize global variables
GLOBAL_A, GLOBAL_B, GLOBAL_C, GLOBAL_M, x_init = params
GLOBAL_TARGET = target
orginal_params = params[:]
MIN_CIRCLE_PATHS = 16  # Minimum number of circle paths required to continue
collision_bit = 32
search_bits = 36
step_size = search_bits
final_path = []
valid_circle_paths = [[0], [1]]  # Single-bit paths
states = nbits // collision_bit
stage = 0
target_intermediate = x_init

while True:
    collided_bits = (stage + 1) * collision_bit
    print(f"\n[Stage {stage+1}] Colliding on next {collision_bit} bits with {step_size = } ({collided_bits = })...")
    mask = (1 << collided_bits) - 1
    for try_step_size in range(step_size, step_size + 4):
        if stage == 0:
            path = find_lsb_path_mitm(target_intermediate, collided_bits, try_step_size, valid_circle_paths, findall=False)
        else:
            path = find_lsb_path_mitm(target_intermediate, collided_bits, try_step_size, valid_circle_paths, findall=False)
        if path: break
    if not path:
        print(f'⚠️  No path found in stage {stage+1} with step_size={step_size}, aborting...')
        break
    final_path.extend(path)
    print(f'[+] Found path of length {len(path)} bits in stage {stage+1}, total {len(final_path)} bits')
    target_intermediate = hash_bits(orginal_params, final_path)
    assert target_intermediate &mask == GLOBAL_TARGET & mask, f"Intermediate target mismatch at stage {stage+1}"
    if collided_bits >= nbits:
        print(f'[+] Reached full {nbits} bits collision, done!')
        break
    # find circles which keeps the collided_bits unchanged
    # Circles are paths from 0 back to 0, so they don't alter the state mod 2^n
    
    for try_step_size in range(step_size, step_size + 4):
        print(f'💡 Searching for circle paths with step_size={try_step_size}...')
        # We search for circles from state LSB(GLOBAL_TARGET, collided_bits) to LSB(GLOBAL_TARGET, collided_bits).
        new_valid_circle_paths = find_lsb_path_mitm(GLOBAL_TARGET, collided_bits, try_step_size, valid_circle_paths, findall=True)
        if new_valid_circle_paths and len(new_valid_circle_paths) >= MIN_CIRCLE_PATHS:
            print(f'[+] Found {len(new_valid_circle_paths)} circle paths in stage {stage+1}')
            break

    if not new_valid_circle_paths or len(new_valid_circle_paths) < MIN_CIRCLE_PATHS:
        print(f'[-] Could not find enough circle paths in stage {stage+1}, stopping here.')
        break
    stage += 1
    # we fix the number of circle paths to MIN_CIRCLE_PATHS to avoid uncontrolled growth of paths
    valid_circle_paths = new_valid_circle_paths[:MIN_CIRCLE_PATHS]
    step_size = max(8, ceil(search_bits / log2(len(valid_circle_paths))))

# Convert final path to bytes
print(f'\n🎉 SUCCESS! Total path length: {len(final_path)} bits')
# validate final message
bits_hash = hash_bits(orginal_params, final_path)
print(f'🔗 Check final target for {nbits} lsbs {hex(bits_hash) = } and {hex(GLOBAL_TARGET) = }')
assert bits_hash == GLOBAL_TARGET, "Final target mismatch!"

# the final message must be a multiple of 8 bits to submit a byte-aligned message
assert len(final_path) % 8 == 0, "Final path length is not a multiple of 8!"

bytes_msg = bytearray()
for i in range(0, len(final_path), 8):
    byte = 0
    for j in range(8):
        if i + j < len(final_path):
            byte = (byte << 1) | final_path[i + j]
        else:
            byte = (byte << 1)
    bytes_msg.append(byte)
assert hash(orginal_params, bytes_msg) == GLOBAL_TARGET, "Final message hash mismatch!"
print(f'📩 Final message (hex): {bytes_msg.hex()[:32]}... (length: {len(bytes_msg)} bytes)')
if not local:
    conn.sendline(bytes_msg.hex().encode())
    conn.interactive()