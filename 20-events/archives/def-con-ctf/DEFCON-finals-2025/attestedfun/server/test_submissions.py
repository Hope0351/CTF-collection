
import subprocess
import time
import os
import signal
import sys
import codecs
from collections import defaultdict
import re
import resource
from datetime import datetime

from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad


TIMEOUT = 60

KTESTS = [
    "b1", #10 b64
    "biosig1", #bio signature of challenge
    "biochain0",
    "biochain1", #bio signs are chained correctly
    "biochain2",#bio chain not revoked
    "biochain3",#bio chain google root
    "biocert1",#bio authtype and level correct
    "biocert2",#bio auth time correct
    "biocert3",#bio os version correct
    "biochall1",#bio attchallenge correct
    "biobstate1",#bio boot state

    "pcsig1", #pc signature of challenge
    "pcsig2", #pc cbor of challenge
    "pcchain0",
    "pcchain1", #pc signs are chained correctly
    "pcchain2",#pc chain not revoked
    "pcchain3",#pc chain google root
    "pccert1",#pc authtype and level correct
    "pccert2",#pc auth time correct
    "pccert3",#pc os version correct
    "pcchall1",#pc attchallenge correct
    "pcbstate1",#pc boot state

    "di0",#any valid json
    "di1",#strong integrity
    "di2",#correct app and version
    "di3",#correct hash
    "di4",#all combined

]
ONESOLVEMAXPOINTS = 1000


def decrypt_mm(ciphertext_hex: str):
    try:
        key = b"1fenudafnH23ujj#" ###
        iv  = b"889asdNN23ujjXXD" ###
        data = bytes.fromhex(ciphertext_hex)
        cipher = AES.new(key, AES.MODE_CBC, iv)
        padded = cipher.decrypt(data)
        plain = unpad(padded, AES.block_size, style='pkcs7')
        return plain.decode('utf-8')
    except Exception:
        return None


def translate_byte_string(data: bytes) -> str:
    text = data.decode('utf-8', errors='ignore')
    pattern = re.compile(r'\[\[\[([0-9A-Fa-f]+)\s+([^\]]+)\]\]\]')

    def _repl(match):
        cipher_hex, suffix = match.group(1), match.group(2)
        plain = decrypt_mm(cipher_hex)
        if plain is None:
            return match.group(0)
        return f"{{{{{plain} {suffix}}}}}"

    return pattern.sub(_repl, text)


def set_death_and_limits():
    import ctypes
    libc = ctypes.CDLL("libc.so.6")
    libc.prctl(1, signal.SIGKILL)
    mem_limit = 800 * 1024 * 1024
    resource.setrlimit(resource.RLIMIT_AS, (mem_limit, mem_limit))


def outcontent2solved(outcontent):
    solved = set()
    for line in outcontent.split("\n"):
        if not line: continue
        if line in KTESTS:
            solved.add(line)
    return solved


def get_testvalue_and_solvingteams(solved_dict, test):
    nsolves = 0
    test_value = 0
    solving_teams = set()
    for k,v in solved_dict.items():
        if test in v:
            nsolves += 1
            solving_teams.add(k)
    if nsolves == 0:
        return 0, set()
    elif nsolves == 1: # bonus
        test_value = int(ONESOLVEMAXPOINTS*2)
        return test_value, solving_teams
    else:
        test_value = int(ONESOLVEMAXPOINTS/nsolves)
        return test_value, solving_teams


def score_solved_dict(solved_dict):
    score_dict = defaultdict(int)
    for test in KTESTS:
        test_value, solving_teams = get_testvalue_and_solvingteams(solved_dict, test)
        for team in solving_teams:
            score_dict[team] += test_value

    scored_dict_s = {i:score_dict[i] for i in range(1,len(solved_dict)+1)}
    return scored_dict_s


def generate_solved_dict_table(solved_dict, score_dict):
    def force_len(tstr, tlen, centered=False):
        if len(tstr) > tlen:
            display = tstr[0] + '..' + tstr[-(tlen - 3):]
        else:
            display = tstr
        align = '^' if centered else '>'
        return f"{display:{align}{tlen}}"

    first_line_tokens = [force_len(" ", 12)]
    first_line_tokens.extend([f"{i:>2}"+":"+force_len(TEAMS_DICT[i][:5],5) for i in range(1, len(TEAMS_DICT)+1)])
    first_line = "|".join(first_line_tokens)
    tstr = first_line+"|\n"

    for test in KTESTS:
        line_tokens = []
        line_tokens.append(force_len(test, 12))
        test_value, solving_teams = get_testvalue_and_solvingteams(solved_dict, test)
        for i in range(1, len(TEAMS_DICT)+1):
            if i in solving_teams:
                line_tokens.append(force_len(str(test_value), 5+3, True))
            else:
                line_tokens.append(force_len(".", 5+3, True))
        tstr += ("|".join(line_tokens)+"|\n")

    last_line_tokens = [force_len("TOTAL", 12)]
    last_line_tokens.extend([force_len(str(score_dict[i]), 5+3, True) for i in range(1, len(TEAMS_DICT)+1)])
    last_line = "|".join(last_line_tokens)
    tstr += last_line+"|\n"

    return tstr


def test_all(round_id):
    print("=" * 20, datetime.now().strftime("%Y-%m-%d %H:%M:%S"), "STARTING EVAL FOR ROUND: " + str(round_id))
    procs = []
    NUM_PROCS = len(TEAMS_DICT)

    for i in range(1, NUM_PROCS + 1):
        try:
            os.unlink("results/"+str(i)+".out")
        except OSError:
            pass

    for i in range(1, NUM_PROCS + 1):
        p = subprocess.Popen(
            ['./attestedfun', str(round_id), str(i)],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            preexec_fn=set_death_and_limits
        )
        procs.append(p)

    start_time = time.time()
    while True:
        if not any([p.poll() is None for p in procs]):
            break
        if time.time() - start_time > TIMEOUT:
            print("Timeout reached, killing all running processes.")
            break
        time.sleep(1)
    for p in procs:
        p.kill()

    outputs = []
    for i, p in enumerate(procs, 1):
        out, err = p.communicate()
        retcode = p.returncode
        fcontent = ""
        try:
            fp = open("results/"+str(i)+".out", "r")
            fcontent = fp.read()
            fp.close()
        except OSError:
            pass
        outputs.append((i, out, err, retcode, fcontent))

    for i, out, err, retcode, fcontent in outputs:
        print(f"--- Process {i} ---")
        print("STDOUT:\n" + translate_byte_string(out))
        print("STDERR:\n" + translate_byte_string(err))
        print("RETVALUE:", retcode)
        print("OUTCONTENT:")
        print(fcontent)

    solved_dict = {}
    for i in range(1, NUM_PROCS + 1):
        solved_dict[i] = outcontent2solved(outputs[i-1][4])
    print(solved_dict)

    score_dict = score_solved_dict(solved_dict)
    print(score_dict)
    table_str = generate_solved_dict_table(solved_dict, score_dict)
    #print(table_str)

    with open("output/results.txt", "wb") as fp:
        fp.write(repr(score_dict).encode("utf-8"))
        fp.write(b"\n")
        fp.write(b"Results for round: "+str(round_id).encode("utf-8")+b"\n")
        fp.write(b"\n")
        fp.write(table_str.encode("utf-8"))
        fp.write(b"\n")



def decode_dict(tstr):
    d = {}
    for kv in tstr.split(b"_"):
        k, v = kv.split(b"-")
        d[int(k)] = codecs.decode(codecs.decode(v, "hex"))
    return d


def encode_dict(d):
    assert all((type(k)==int and type(v)==str for k, v in d.items()))
    return b"_".join((codecs.encode(str(k))+b"-"+codecs.encode(codecs.encode(v), "hex") for k, v in d.items()))


if __name__ == "__main__":
    if len(sys.argv) !=2:
        print("Usage:\npython3 ./test_submissions.py <round_id>")
        sys.exit(1)

    TEAMS_DICT = {
        1: "mmm",
        2: "friendly-maltese-citizens",
        3: "kalmarunionen",
        4: "repokemonedcollections",
        5: "blue-water",
        6: "superdicecode",
        7: "mhackeroni",
        8: "nu1l",
        9: "shellphish",
        10: "kuk-hofhackerei",
        11: "this-years-organizers",
        12: "cold-fusion"
    }
    test_all(int(sys.argv[1]))



