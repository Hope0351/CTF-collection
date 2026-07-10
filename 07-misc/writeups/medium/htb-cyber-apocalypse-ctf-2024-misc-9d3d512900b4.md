# :game_die: Define the dictionary mapping scenarios to actions

> **Original Source:** [Define the dictionary mapping scenarios to actions](https://infosecwriteups.com/htb-cyber-apocalypse-ctf-2024-misc-9d3d512900b4)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2024

---

## Stop Drop and Roll


>

The Fray: The Video Game is one of the greatest hits of the last… well, we don’t remember quite how long. Our “computers” these days can’t run much more than that, and it has a tendency to get repetitive…


### 💡Solution


When you connect to this service, you’ll be presented with a console-based game. It’s a challenge-and-response setup where you’ll be shown randomlt one or more words, and your task is to provide a matching response for each one.


Check out the instructions below along with a demo of how the game is played manually.

*Playing the game manually*


It seems like the challenge isn’t intended to be solved manually, and the goal is to automate the interaction using code. The author mentioned that the game consists of 500rounds.


## Get Abdul Issa’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Below is a Python script I used to automate the process. Although it’s a bit lengthy, it did the job. However, I encountered a bug where the script exits at the end in an ungraceful manner and fails to display the flag on the console.


```
from pwn import *

# Define the dictionary mapping scenarios to actions
scenario_actions = {"GORGE": "STOP", "PHREAK": "DROP", "FIRE": "ROLL"}
# Connect to the remote service
io = remote("94.237.54.170", 39826)
# Receive initial messages
io.recvuntil(b"===== THE FRAY: THE VIDEO GAME =====\nWelcome!\n")
io.recvuntil(b"Are you ready? (y/n) ")
io.sendline(b"y")
io.recvuntil(b"Ok then! Let's go!\n")
# Loop until no more scenarios are provided
while True:
# Receive the scenario
scenario_line = io.recvuntil(b"What do you do? ")
# Extract the scenario
scenario = scenario_line.split(b"\n")[0]
# Check if the scenario is empty, indicating the end of the game
if not scenario:
break
# Split the scenario into individual actions
actions = scenario.split(b", ")
# Map each action to its corresponding response and join them with "-"
response = "-".join([scenario_actions[action.decode()] for action in actions])
# Send the response
io.sendline(response)
```


The only way I could confirm that the interaction occurred as expected was by using Wireshark packet sniffer. I found all the challenge and response requests, as well as the flag, in the packet capture.


*Wireshark packet capture of the interaction*


The JavaScript code below was provided by a colleague as an alternative to the Python solution. It’s worth exploring different approaches to solving the same problem.


```
const net = require('net');
const client = new net.Socket();
const host = '94.237.54.170'; // replace with your host ip
const port = 39826; // replace with your port

client.connect(port, host, function() {
console.log('[CONNECTED]');
});
let challengeStarted = false; //store if the challenge started
let dataString = ""; //store the data received
client.on('data', function(data) {
dataString += `\n${data}`;
console.log(`[NEW DATA RECEIVED]\n${dataString.trim()}`);
if (data.includes('Are you ready? (y/n)')) {
dataString = "";
console.log("[SENT] : y")
client.write("y\n");
}
if(dataString.includes("Unfortunate! You died!")){
console.log("[ENDED] : You died")
challengeStarted = false;
dataString = "";
client.destroy();
}
if(dataString.includes("Ok then! Let's go!")){
challengeStarted = true;
console.log("[Challenge Started]")
}
if(challengeStarted && dataString.includes("What do you do?")) {
let returnString = [];
const validQuestionWords = [{ques: "GORGE",ans:"STOP"},{ques: "PHREAK",ans:"DROP"},{ques: "FIRE",ans:"ROLL"}];
let currentQuestionString = dataString.toString().replace("Ok then! Let's go!","").replace("What do you do?","").trim().split(',');
console.log({currentQuestionString})
for (let i = 0; i < currentQuestionString.length; i++) {
const currWord = currentQuestionString[i].trim();
if (validQuestionWords.map((item)=>item.ques).includes(currWord)) {
returnString.push(validQuestionWords.find((item)=>item.ques === currWord).ans);
}else {
console.log(`[ERROR] : ${currWord} is not a valid word`);
}
}
console.log(`[SENT] : '${returnString.join('-')}'`);
dataString = "";
client.write(`${returnString.join('-')}\n`);

}
});
client.on('close', function() {
console.error('Connection closed');
});
```


It would indeed be helpful if HackTheBox provided a Docker image or the source code for challenges like this. Having access to the source code would allow participants to continue experimenting and refining their solutions even after the CTF ends.

>

Flag: HTB{1_wiLl_sT0p_dR0p_4nD_r0Ll_mY_w4Y_oUt!}

---

*Originally published on [Medium](https://infosecwriteups.com/htb-cyber-apocalypse-ctf-2024-misc-9d3d512900b4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
