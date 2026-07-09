
import os
import sys
import time
import hashlib
import hmac
import base64


round_number = int(sys.argv[1])
with open("server/hmacsecret.key", "rb") as f:
    secret = f.read().strip()
msg = str(round_number).encode()
challenge = hmac.new(secret, msg, hashlib.sha256).hexdigest()
print(challenge)

os.system("rm pulled/*")

os.system('adb install apks/confFun.apk')
os.system('adb install apks/biometricFun.apk')


os.system('adb shell "am force-stop antonio.pizza.conffun"')
os.system('adb shell "am force-stop antonio.pizza.biometricfun"')
time.sleep(1)
os.system('adb shell "am start -n antonio.pizza.biometricfun/.MainActivity --es extra_data \''+challenge+'\'"')
print("auth now")
time.sleep(10)
print("done")
os.system('adb shell run-as antonio.pizza.biometricfun ls -1 /data/data/antonio.pizza.biometricfun/files/ | xargs -P1 -I {}  bash -c "adb shell run-as antonio.pizza.biometricfun cat /data/data/antonio.pizza.biometricfun/files/{} > pulled/{}"')

#sys.exit(2)


os.system('adb shell "am force-stop antonio.pizza.conffun"')
os.system('adb shell "am force-stop antonio.pizza.biometricfun"')
time.sleep(1)
os.system('adb shell "am start -n antonio.pizza.conffun/.MainActivity --es extra_data \''+challenge+'\'"')
print("auth now")
time.sleep(10)
print("done")
os.system('adb shell run-as antonio.pizza.conffun ls -1 /data/data/antonio.pizza.conffun/files/ | xargs -P1 -I {}  bash -c "adb shell run-as antonio.pizza.conffun cat /data/data/antonio.pizza.conffun/files/{} > pulled/{}"')


NB64 = 12
def pad_file_to_10_lines(filepath):
    with open(filepath, "rb") as f:
        lines = f.read().split(b"\n")
    # If the file ends with a newline, the last element will be empty
    if lines and lines[-1] == b"":
        lines = lines[:-1]
    if len(lines) < NB64:
        lines += [base64.b64encode(b"DUMMY")] * (NB64 - len(lines))
    # Reassemble content with newline
    content = b"\n".join(lines) + b"\n"
    with open(filepath, "wb") as f:
        f.write(content)
NTEAMS = 12

'''
with open("server/submissions/12.in", "wb") as fd:
    fd.write(open("server/certs/v6/bioCert1", "rb").read()+b"\n")
    fd.write(open("server/certs/v6/bioCert2", "rb").read()+b"\n")
    fd.write(open("server/certs/v6/bioCert3", "rb").read()+b"\n")
    fd.write(open("server/certs/v6/bioCert4", "rb").read()+b"\n")
    fd.write(base64.b64encode(open("server/certs/v6/bioSignature", "rb").read())+b"\n")

    fd.write(open("pulled/confCert1", "rb").read()+b"\n")
    fd.write(open("pulled/confCert2", "rb").read()+b"\n")
    fd.write(open("pulled/confCert3", "rb").read()+b"\n")
    fd.write(open("pulled/confCert4", "rb").read()+b"\n")
    fd.write(base64.b64encode(open("pulled/confSignature", "rb").read())+b"\n")
    fd.write(base64.b64encode(open("pulled/confCBOR", "rb").read())+b"\n")
pad_file_to_10_lines("server/submissions/12.in")

'''
with open("server/submissions/1.in", "wb") as fd:
    fd.write(open("pulled/bioCert1", "rb").read()+b"\n")
    fd.write(open("pulled/bioCert2", "rb").read()+b"\n")
    fd.write(open("pulled/bioCert3", "rb").read()+b"\n")
    fd.write(open("pulled/bioCert4", "rb").read()+b"\n")
    fd.write(base64.b64encode(open("pulled/bioSignature", "rb").read())+b"\n")
    fd.write(open("pulled/confCert1", "rb").read()+b"\n")
    fd.write(open("pulled/confCert2", "rb").read()+b"\n")
    fd.write(open("pulled/confCert3", "rb").read()+b"\n")
    fd.write(open("pulled/confCert4", "rb").read()+b"\n")
    fd.write(base64.b64encode(open("pulled/confSignature", "rb").read())+b"\n")
    fd.write(base64.b64encode(open("pulled/confCBOR", "rb").read())+b"\n")
pad_file_to_10_lines("server/submissions/1.in")


'''
with open("server/submissions/4.in", "wb") as fd:
    fd.write(base64.b64encode(b"DUMMY")+b"\n")
    fd.write(base64.b64encode(b"DUMMY")+b"\n")
    fd.write(base64.b64encode(b"DUMMY")+b"\n")
    fd.write(base64.b64encode(b"DUMMY")+b"\n")
    fd.write(base64.b64encode(b"DUMMY")+b"\n")
    fd.write(open("pulled/confCert1", "rb").read()+b"\n")
    fd.write(open("pulled/confCert2", "rb").read()+b"\n")
    fd.write(open("pulled/confCert3", "rb").read()+b"\n")
    fd.write(open("pulled/confCert4", "rb").read()+b"\n")
    fd.write(base64.b64encode(open("pulled/confSignature", "rb").read())+b"\n")
    fd.write(base64.b64encode(open("pulled/confCBOR", "rb").read())+b"\n")
pad_file_to_10_lines("server/submissions/4.in")
'''
