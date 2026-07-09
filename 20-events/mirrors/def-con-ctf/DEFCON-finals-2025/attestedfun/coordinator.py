import os
import sys
import time
import json
import gzip
import requests
import traceback
import hmac
import hashlib
from datetime import datetime

SERVICE_ID=14
SSHLOGIN="ubuntu@44.241.236.67"
REMOTE=False

MANUAL_ROUND=False
UPLOAD_RES=True


if REMOTE:
    sshc = "ssh "
    sshc += SSHLOGIN
    sshc += " -- "
else:
    sshc = ""




def get_round():
    if MANUAL_ROUND == True:
        for _ in range(10): #solve concurrency issue
            try:
                dr = int(open("defcon_round").read().strip())
                break
            except:
                print("round read error")
                time.sleep(0.1)
                pass
        return (dr, 500+dr)
    else:
        while True:
            res = ""
            try:
                #FIXME
                response = requests.get("https://gamedb.finals.2025.nautilus.institute/api/v1/tick/current")
                if response.status_code == 200:
                    res = response.text
                    #print(res)
                    tick_str = "tick"
                    private_tick = int(res.split('"'+tick_str+'":')[1].split('}')[0])
                    tick_str = "public_tick"
                    public_tick = int(res.split('"'+tick_str+'":')[1].split(',')[0])
                    return (public_tick, private_tick)
                else:
                    print("TICK CONNECTION ERROR","response code")
            except Exception as e:
                print("TICK CONNECTION ERROR", str(e), res)

            time.sleep(1)


def upload_scores(cr, private_tick):
    scores = {}
    try:
        with open("/opt/finals/game/output/results.txt", "rb") as fp:
            line = fp.readline()
            print("Got line from results: " + repr(line[:300]))
            if len(line) > 2000 or len(line) < 2:
                print("=== ERROR while parsing results in round " + repr((cr, private_tick)) + ", line size is wrong: " + str(len(line)))
                return

            line_str = line.decode('utf-8', errors='strict').strip()
            if line_str.startswith("{") and line_str.endswith("}"):
                line_str = line_str[1:-1]
            if not line_str:
                scores = {}

            for entry in line_str.split(","):
                keyval = entry.split(":")
                if len(keyval) != 2:
                    print("=== ERROR while parsing results in round " + repr((cr, private_tick)) + ", keyval len wrong: " + str(len(keyval)))
                    return
                k = int(keyval[0].strip())
                v = int(keyval[1].strip())
                scores[k] = v

    except Exception as e:
        tb = traceback.extract_tb(sys.exc_info()[2])[-1]
        filename, lineno, funcname, _ = tb
        print("=== ERROR while parsing results in round " + repr((cr, private_tick)) + "!")
        print(f"Exception: {e} (line {lineno} in {filename})")
        return

    if len(scores.keys()) != 12:
        print("=== ERROR while parsing results in round " + repr((cr, private_tick)) + ", scores dict size wrong: " + str(len(scores)))
        return

    scores_list = [dict(team_id=k,score=v,metadata="") for k, v in scores.items()]
    scores_list_sorted = sorted(scores_list, key=lambda x: (-x['score']))
    for i,s in enumerate(scores_list_sorted):
        s["rank"] = i+1
    scores_str = json.dumps(scores_list_sorted)

    with open("scores.txt", "a") as fp:
        fp.write(repr((cr, private_tick)) + " --- " + scores_str + "\n")

    if UPLOAD_RES == True:
        data={
            "reason": "attestedfun ranking result for private tick "+str(private_tick)+" (public tick is " + str(cr) + ")",
            "service_id": SERVICE_ID,
            "ranking": scores_str,
            "tick_id": private_tick
        }
        print(data)
        r = requests.post("https://gamedb.finals.2025.nautilus.institute/api/v1/koh_ranking_event",data=data)
        print(r.content)


def copy_from_web_to_game(cr):
    with open("server/hmacsecret.key", "rb") as f:
        secret = f.read().strip()
    msg = str(cr).encode()
    challenge = hmac.new(secret, msg, hashlib.sha256).hexdigest()
    with open("/opt/finals/website/challenge", "w") as fp:
        fp.write(str(challenge))
    with open("/opt/finals/website/round", "w") as fp:
        fp.write(str(cr))

    os.system("rm /opt/finals/game/submissions/*")
    os.system("rm /opt/finals/game/output/*")
    os.system("cp /opt/finals/website/upload/* /opt/finals/game/submissions/")
    os.system("rm /opt/finals/website/upload/*")


def copy_from_game_to_web(cr):
    os.system(f"cp /opt/finals/game/output/results.txt /opt/finals/website/download/results_{cr:03d}.txt")


def start_game(cr):
    print("starting game evaluating round: "+str(cr))
    tstr = sshc+"docker run -it --rm -d --memory=12g --cpus=12 -u $(id -u):$(id -g)  -v /opt/finals/game/submissions:/app/submissions/ -v /opt/finals/game/output/:/app/output/ defcongame ./start_in_docker.sh " + str(cr)
    print(tstr)
    os.system(tstr)


def stop_game_docker():
    print("stopping game docker...")
    os.system(sshc+"docker stop $(docker ps -q --filter ancestor=defcongame)")
    print("...stopped")


def backup(cr, tag):
    now = datetime.now()
    fname = f"round_{cr:03d}_{tag}_{now.day:02d}_{now.hour:02d}_{now.minute:02d}_{now.second:02d}"
    ffname = "/var/tmp/defconbk/" + fname + "/"
    os.system("mkdir " + ffname)
    os.system("cp -a /opt/finals/website " + ffname)
    os.system("cp -a /opt/finals/game " + ffname)
    os.system("cp scores.txt " + ffname)


###############


# n=$(<defcon_round); echo $((n + 1)) > defcon_round

if len(sys.argv) > 1 and sys.argv[1] == "forced":
    forced = True
else:
    forced = False
if forced:
    old_round = -1
    private_tick = -1
else:
    old_round, private_tick = get_round()
cr = 0

stop_game_docker()

otime = time.time()
otime2 = time.time()
while True:
    print("="*10 + time.ctime(), time.time() - otime, time.time() - otime2)
    otime = time.time()
    time.sleep(1)
    print("OLD ROUND IS: "+str(old_round)+ " CURRENT_ROUND IS: " + str(cr), "private:", str(private_tick))
    while True:
        cr, private_tick = get_round()
        if cr != old_round:
            break
        else:
            time.sleep(1)
    otime2 = time.time()
    old_round = cr
    print("NEW ROUND!", cr, private_tick)

    backup(cr, "pre")
    copy_from_web_to_game(cr)
    
    start_game(cr-1)

    print("I am going to sleep...", time.ctime())
    time.sleep(10+60+30)
    
    print("...awake", time.ctime())
    sys.stdout.flush()

    stop_game_docker()

    upload_scores(cr, private_tick)
    copy_from_game_to_web(cr)
    backup(cr, "post")

