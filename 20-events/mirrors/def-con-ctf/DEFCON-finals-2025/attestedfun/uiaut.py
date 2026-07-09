
import uiautomator2 as u2
import time
import base64
import subprocess
import sys
import hmac
import hashlib

def xor_bytes(data: bytes, key: bytes) -> bytes:
    return bytes([b ^ key[i % len(key)] for i, b in enumerate(data)])

tt = sys.argv[1]
if len(tt)<=4:
    print("you gave me a round number, I will compute the round challenge for you")
    round_number = int(tt)
    with open("server/hmacsecret.key", "rb") as f:
        secret = f.read().strip()
    msg = str(round_number).encode()
    challengeb = hmac.new(secret, msg, hashlib.sha256).digest()
    print(challengeb.hex())

else:
    print("you gave me the round challenge, I will use it")
    challengeb = bytes.fromhex(tt.strip())


challengexor = xor_bytes(challengeb, [0x42, 0xCA, 0x7E, 0x13])
print(challengexor.hex())

d = u2.connect()

'''
for _ in range(25):
    d.press("volume_up")
    time.sleep(0.1)
d.press("volume_down")
print("Volume set close to 95% via hardware buttons")
'''


package = "com.pizza.integritycheckjava"
activity = ".MainActivity"

print("Stopping app if running...")
d.app_stop(package)

print(f"Starting app {package} with activity {activity}")
d.app_start(package, activity=activity)

time.sleep(2)  # wait for UI to load

print("Dumping UI hierarchy...")
d.dump_hierarchy()

print("Searching for editable text boxes (EditText)...")
textboxes = d(className="android.widget.EditText")

for i, textbox in enumerate(textboxes):
    info = textbox.info
    bounds = info.get("bounds")
    text = info.get("text", "")
    hint = info.get("hintText", "")
    print(f"[{i}] Bounds: {bounds} | Text: '{text}' | Hint: '{hint}'")
    buttons = d(className="android.widget.Button")

for i, button in enumerate(buttons):
    info = button.info
    bounds = info.get("bounds")
    text = info.get("text", "")
    desc = info.get("contentDescription", "")
    res_id = info.get("resourceName", "")
    print(f"[{i}] Bounds: {bounds} | Text: '{text}' | Desc: '{desc}' | ID: '{res_id}'")



tx = textboxes[0]
bt = buttons[0]

print(repr(tx), repr(bt))
time.sleep(1)
tx.set_text(challengexor.hex())
time.sleep(1)
bt.click()

#time.sleep(10)
time.sleep(90+10)


textboxes = d(className="android.widget.TextView")

for i, tb in enumerate(textboxes):
    print(i)
    text = tb.get_text()

btext = text.encode("utf-8")
print(btext)
print("")
print(base64.b64encode(btext))
print("")
btextx = xor_bytes(btext, [0xe1])
print(base64.b64encode(btextx))
print("PUT THE STRING BELOW IN THE LINE 12 (last line) OF A SUBMISSION:")
print(base64.b64encode(btextx).decode("utf-8"))



