# :globe_with_meridians: Test Burp is reachable from the host

---

## 11. Troubleshooting Matrix — Windows-Specific Issues

## Diagnostic Commands

```
# Test Burp is reachable from the host
curl -x http://127.0.0.1:8080 http://httpbin.org/get

# Test Burp is reachable from a container
docker run --rm alpine:latest wget -qO- http://host.docker.internal:8080

# Check Docker proxy settings
docker info | Select-String -Pattern "Proxy|proxy"

# Verify portproxy rules (WSL2 method)
netsh interface portproxy show all

# Check Docker Desktop proxy UI is active
# Settings → Resources → Proxies should show your values

# Reset Docker proxy to default
# Remove or empty the "proxy" key in %ProgramData%\Docker\config\daemon.json
# Reset Docker Desktop proxy UI to "No proxy"
```

## 12. Complete PoC Walkthrough — Step-by-Step Lab

Here’s a full end-to-end lab you can run on a clean Windows machine with Docker Desktop.

## Lab Goal

Intercept all outbound HTTPS traffic from an `ubuntu:22.04` container making API calls.

## Step 1: Export Burp CA

- Open Burp Suite → Proxy → Options → Import/Export CA Certificate

- Click Export → Certificate in DER format

- Save to `C:\burp-lab\burp.der`

## Step 2: Convert to PEM

```
# Using OpenSSL for Windows
openssl x509 -inform DER -in C:\burp-lab\burp.der -out C:\burp-lab\burp.pem -outform PEM
```

## Step 3: Configure Burp Listener

Burp → Proxy → Options → Proxy Listeners:

- Default listener: Edit → change to All interfaces

- Add secondary listener: `0.0.0.0:8081` (for WSL scenarios)

## Step 4: Configure Windows Firewall

```
New-NetFireWallRule -DisplayName "Burp Lab" -Direction Inbound -LocalPort 8080 -Action Allow -Protocol TCP
```

## Step 5: Create a PoC Container with a Custom Dockerfile

```
# C:\burp-lab\Dockerfile
FROM ubuntu:22.04

# Install Burp CA
COPY burp.pem /usr/local/share/ca-certificates/burp.crt
RUN apt-get update && \
apt-get install -y ca-certificates curl dnsutils && \
update-ca-certificates && \
rm -rf /var/lib/apt/lists/*

# Proxy env vars
ENV http_proxy=http://host.docker.internal:8080
ENV https_proxy=http://host.docker.internal:8080
ENV HTTP_PROXY=http://host.docker.internal:8080
ENV HTTPS_PROXY=http://host.docker.internal:8080
ENV no_proxy=localhost,127.0.0.1

# Test script
COPY test.sh /test.sh
RUN chmod +x /test.sh
CMD ["/test.sh"]
```

```
# C:\burp-lab\test.sh
#!/bin/bash
echo "=== Testing HTTP ==="
curl -v http://httpbin.org/get 2>&1 | head -20

echo "=== Testing HTTPS ==="
curl -v https://api.github.com/zen 2>&1

echo "=== Testing API call ==="
curl -s https://jsonplaceholder.typicode.com/posts/1 | head -100
```

## Step 6: Build and Run

```
cd C:\burp-lab
docker build -t burp-lab .
docker run --rm burp-lab
```

## Step 7: Observe in Burp

- Set Burp’s Intercept to ON

- Watch each request pause in the Proxy → Intercept tab

- Click Forward to release each one

- After completion, review all traffic in Proxy → HTTP history

## Step 8: Modify a Request in Flight (The “Killer Feature”)

- With Intercept ON, run the container again

- When the `jsonplaceholder.typicode.com` request appears:

- Modify the URL from `/posts/1` to `/posts/2`

- Or modify the `Accept` header

- Or change `GET` to `POST` and inject a body

3. Click Forward to send the modified request

4. The container receives the modified response

## 13. Appendix: PowerShell Automation Scripts

## Script 1: One-Click Burp + Docker Intercept Setup

Save as `C:\Scripts\setup-burp-docker.ps1`:

```
# setup-burp-docker.ps1
# Run as Administrator

param(
[int]$BurpPort = 8080,
[string]$BurpCertPath = "$env:USERPROFILE\Desktop\burp.der"
)

Write-Host "[*] Setting up Burp + Docker interception on Windows" -ForegroundColor Cyan

# 1. Firewall rule
Write-Host "[*] Adding Windows Firewall rule for port $BurpPort..."
Remove-NetFireWallRule -DisplayName "Burp Suite Docker Proxy" -ErrorAction SilentlyContinue
New-NetFireWallRule -DisplayName "Burp Suite Docker Proxy" `
-Direction Inbound -LocalPort $BurpPort -Action Allow -Protocol TCP

# 2. Convert DER to PEM if needed
$pemPath = $BurpCertPath -replace '\.der$', '.pem'
if (Test-Path $BurpCertPath) {
Write-Host "[*] Converting DER to PEM..."
openssl x509 -inform DER -in $BurpCertPath -out $pemPath -outform PEM
Write-Host "[+] PEM saved to: $pemPath"
}

# 3. Docker Desktop proxy config (via daemon.json)
$daemonPath = "$env:ProgramData\Docker\config\daemon.json"
$config = @{
proxy = @{
"http-proxy" = "http://host.docker.internal:$BurpPort"
"https-proxy" = "http://host.docker.internal:$BurpPort"
"no-proxy" = "localhost,127.0.0.1,.local,.internal"
}
}

if (Test-Path $daemonPath) {
$existing = Get-Content $daemonPath -Raw | ConvertFrom-Json
$existing | Add-Member -Force -NotePropertyMembers @{proxy = $config.proxy}
$existing | ConvertTo-Json -Depth 10 | Set-Content $daemonPath
} else {
$config | ConvertTo-Json | Set-Content $daemonPath
}

Write-Host "[+] daemon.json updated at: $daemonPath"

# 4. Create test Dockerfile
$testDir = "$env:TEMP\burp-docker-test"
New-Item -ItemType Directory -Force -Path $testDir | Out-Null

@"
FROM ubuntu:22.04
COPY burp.pem /usr/local/share/ca-certificates/burp.crt
RUN apt-get update && apt-get install -y ca-certificates curl && update-ca-certificates
ENV http_proxy=http://host.docker.internal:$BurpPort
ENV https_proxy=http://host.docker.internal:$BurpPort
ENV HTTP_PROXY=http://host.docker.internal:$BurpPort
ENV HTTPS_PROXY=http://host.docker.internal:$BurpPort
ENV no_proxy=localhost,127.0.0.1
CMD curl -v https://api.github.com/zen
"@ | Out-File -FilePath "$testDir\Dockerfile" -Encoding ascii

if (Test-Path $pemPath) {
Copy-Item $pemPath "$testDir\burp.pem"
}

Write-Host @"

[+] Setup complete!

Next steps:
1. Ensure Burp is listening on ALL interfaces (0.0.0.0:$BurpPort)
2. Restart Docker Desktop to pick up proxy changes
3. Build the test container:
cd $testDir
docker build -t burp-test .
docker run --rm burp-test
4. Watch traffic appear in Burp's HTTP history

Verification:
- Firewall rule: netsh advfirewall firewall show rule name='Burp Suite Docker Proxy'
- Docker proxy: docker info | Select-String Proxy
"@ -ForegroundColor Green
```

## Script 2: WSL2 Port Forward on Boot (Scheduled Task)

```
# Create a Scheduled Task that runs on logon
$action = New-ScheduledTaskAction -Execute "PowerShell.exe" `
-Argument "-WindowStyle Hidden -ExecutionPolicy Bypass -File C:\Scripts\wsl2-portforward.ps1"

$trigger = New-ScheduledTaskTrigger -AtLogOn -User $env:USERNAME
$settings = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries
$principal = New-ScheduledTaskPrincipal -UserId $env:USERNAME -RunLevel Highest

Register-ScheduledTask -TaskName "WSL2-Burp-PortForward" `
-Action $action `
-Trigger $trigger `
-Settings $settings `
-Principal $principal `
-Description "Forwards WSL2 port 8080 to Windows host for Burp Suite interception"
```

## Quick Reference Card

*Docker + Burp Simple FAQ*

### ❓ If I open a Docker web app in browser, is browser proxy enough to capture traffic?

>

Yes ✅
Browser → Burp Suite → Docker app
This is enough for basic testing.

### ❓ Then why do blogs use complex Docker + Burp setup?

>

Because not all traffic comes from the browser. Some requests are made directly by the container.

### ❓ When is browser proxy enough?

>

When you manually use the website in a browser (manual testing like login, forms, XSS, etc.).

### ❓ When do you need Docker proxy setup?

>

When the container itself sends requests, such as:

backend API calls

microservices communication

CLI tools inside container

external HTTP requests (`curl`, `requests`, etc.)

### ❓ Simple difference?

>

Browser proxy = captures what *you click in browser*

Docker proxy = captures what *container sends automaticallyGitHub: *[SecurityTalent](https://github.com/SecurityTalent)* | Medium: *Security Talent* | Twitter: *[Securi3yTalent](https://twitter.com/Securi3yTalent)

*#BugBounty #WebSecurity #EthicalHacking #Hinglish #InfoSec #securityTalent *#CyberSecurity #BurpSuite #Docker #WindowsSecurity #PenetrationTesting #MITM #ProxyInterception #DockerDesktop #WSL2 #Infosec #WebApplicationSecurity #AppSec #RedTeam #EthicalHacking #APIsecurity #PowerShell

---
