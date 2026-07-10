# :globe_with_meridians: Enforce Zero Trust With East‑West Traffic Encryption in Kubernetes with Istio - Part 2

> **Original Source:** [Enforce Zero Trust With East‑West Traffic Encryption in Kubernetes with Istio - Part 2](https://infosecwriteups.com/enforce-zero-trust-with-east-west-traffic-encryption-in-kubernetes-with-istio-part-2-5a3454560353)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Enforce Zero Trust With East‑West Traffic Encryption in Kubernetes with Istio — Part 2


*Photo by [Степан Галагаев](https://unsplash.com/fr/@sgalagaev?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


In [part 1](https://medium.com/p/e5e1718eee2#dac6-4468b7496eaf), we have gone over concepts of East-West traffic encryption with Istio in Kubernetes. In this section, we will set up Istio deployment in Alibaba Cloud to showcase traffic types in multiple scenarios with different combination of PeerAuthentication CRD and DestinationRule CRD.

## 1. Istio Deployment Setup


First off, we need to set up Container Service for Kubernetes (ACK) based on [https://istio.io/latest/docs/setup/platform-setup/alicloud/](https://istio.io/latest/docs/setup/platform-setup/alicloud/). To install Istio, we choose to [Istioctl](https://istio.io/latest/docs/setup/install/istioctl/). Before we begin, check the [Requirements for Pods and Services](https://istio.io/latest/docs/ops/deployment/requirements/) to ensure the environment is ready.


The installation steps are outlined in the below for your reference:


Download Istio


step 1, download and extract the latest release automatically (Linux or macOS)


```
$ curl -L https://istio.io/downloadIstio | sh -
```


step 2, move to the Istio package directory. For example, if the package is `istio-1.16.1`


```
$ cd istio-1.16.1
```


step 3, add the `istioctl` client to your path (Linux or macOS):


```
$ export PATH=$PWD/bin:$PATH
```


Install Istio


There are multiple [configuration profile](https://istio.io/latest/docs/setup/additional-setup/config-profiles/), we choose the demo configuration which is designed to showcase Istio functionality with modest resource requirements. We set values.global.proxy.privileged to true as we need to install tcpdump in the sidecar proxy container to inspect the traffic sent to the server.


```
$ istioctl install --set profile=demo -y --set values.global.proxy.privileged=true
✔ Istio core installed
✔ Istiod installed
✔ Egress gateways installed
✔ Ingress gateways installed
✔ Installation complete Making this installation the default for injection and validation.
​
Thank you for installing Istio 1.16. Please take a few minutes to tell us about your install/upgrade experience! https://forms.gle/99uiMML96AmsXY5d6
```


Check what’s installed


```
$ kubectl -n istio-system get deploy
NAME READY UP-TO-DATE AVAILABLE AGE
istio-egressgateway 1/1 1 1 7m27s
istio-ingressgateway 1/1 1 1 7m27s
istiod 1/1 1 1 7m41s
```


Inject Envoy Proxy


To enable mTLS, Istio sidecar proxy must be injected. There are two ways of injecting the Istio sidecar proxy into a pod: enabling automatic Istio sidecar injection in the pod’s namespace, or by manually using the `[istioctl](https://istio.io/latest/docs/reference/commands/istioctl)` command. For the simplicity, we choose the manual injection command (`istioctl kube-inject`) in our demos.

## 2. Demo Preparation


In this section, we prepare one client and one server named reviews, they all run in foo namespace. The client will connect to reviews server with different peerauthentication CRD and destinationRule CRD in place, and we will check traffic with tcpdump in istio-proxy sidecar in the reviews server pod.


First off, let’s see the yaml files for server and client:


server — istio-reviews.yaml


```
kind: Service
metadata:
name: reviews
labels:
app: reviews
service: reviews
spec:
ports:
- name: http
port: 8000
targetPort: 80
selector:
app: reviews

apiVersion: apps/v1
kind: Deployment
metadata:
name: reviews
spec:
replicas: 1
selector:
matchLabels:
app: reviews
version: v1
template:
metadata:
labels:
app: reviews
version: v1
spec:
containers:
- image: nginx:stable
imagePullPolicy: IfNotPresent
name: reviews
ports:
- containerPort: 80
```


client — istio-client.yaml


```
apiVersion: v1
kind: Pod
metadata:
name: client
labels:
app: client
service: client
spec:
containers:
- name: client
image: busybox:1.28
command: ["/bin/sh"]
args: ["-c", "while true; do echo hello; sleep 10000;done"]
```


The yaml files for peerauthentication and destinationRule in different modes are displayed as following:


peerauthentication-strict.yaml with mtls mode STRICT and namespace foo


```
apiVersion: security.istio.io/v1beta1
kind: PeerAuthentication
metadata:
name: "default"
namespace: foo
spec:
mtls:
mode: STRICT
```


peerauthentication-disable.yaml with mtls mode DISABLE and namespace foo


```
apiVersion: security.istio.io/v1beta1
kind: PeerAuthentication
metadata:
name: "default"
namespace: foo
spec:
mtls:
mode: DISABLE
```


destinationRule-disable.yaml with tls mode DISABLE and namespace foo


```
apiVersion: networking.istio.io/v1alpha3
kind: DestinationRule
metadata:
name: reviews
namespace: foo
spec:
host: reviews
trafficPolicy:
tls:
mode: DISABLE
```


destinationRule-istio-mutual.yaml with tls mode ISTIO_MUTUAL and namespace foo


```
apiVersion: networking.istio.io/v1alpha3
kind: DestinationRule
metadata:
name: reviews
namespace: foo
spec:
host: reviews
trafficPolicy:
tls:
mode: ISTIO_MUTUAL
```


## 3. Demo Time


We will walk through some of demo, but not all of them. You can use the same method to practice the rest of them. In the end, I will summary the results in the different scenarios.


To start with, we will create the namespace foo and start client and server both with Istio sidecar proxy injected manually:


```
$ kubectl create ns foo
namespace/foo created
$ kubectl apply -f <(istioctl kube-inject -f istio-client.yaml) -n foo
pod/client created
$ kubectl apply -f <(istioctl kube-inject -f istio-reviews.yaml) -n foo
service/reviews created
deployment.apps/reviews created
```


To intercept the traffic sent to the server, we run tcpdump in istio-proxy sidecar of the reviews server pod:


```
$ kubectl exec -nfoo "$(kubectl get pod -nfoo -lapp=reviews -ojsonpath={.items..metadata.name})" -c istio-proxy -- sudo tcpdump dst port 80 -A
```


We will examine traffic in a couple of scenarios with different combination of peerauthentication CRD and destinationRule CRD.


## Get Yani’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Case 1 — neither peerauthentication CRD nor destinationRule CRD


After the client and reviews server spinning up, the first thing is to verify that there is neither peerauthentication CRD nor destinationRule CRD in the Kubernetes environment.


```
$ kubectl get peerauthentication --all-namespaces
No resources found
$ kubectl get destinationRule --all-namespaces
No resources found
```


Now we proceed to check the mTLS configuration between the client and the server in this context. We access the reviews server [http://reviews.foo:8000](http://reviews.foo:8000) from the client container.


```
$ kubectl exec "$(kubectl get pod -l app=client -n foo -o jsonpath={.items..metadata.name})" -c client -n foo -- wget --server-response http://reviews.foo:8000 2>&1 | awk 'FNR==2 {print}'
HTTP/1.1 200 OK
```


The tcpdump console outputs something like:


```
tcpdump: verbose output suppressed, use -v[v]... for full protocol decode
listening on eth0, link-type EN10MB (Ethernet), snapshot length 262144 bytes
16:50:20.893944 IP 192.168.0.127.37618 > reviews-7df9f59bd4-jqmlc.http: Flags [S], seq 1546196509, win 29200, options [mss 1460,sackOK,TS val 25059777 ecr 0,nop,wscale 9], length 0
E..<w.@.?.A........x...P\)........r..v.........
.~a........
16:50:20.893994 IP 192.168.0.127.37618 > reviews-7df9f59bd4-jqmlc.http: Flags [.], ack 4075670737, win 58, options [nop,nop,TS val 25059778 ecr 25059778], length 0
E..4w.@.?.A........x...P\).........:.n.....
.~a..~a.
16:50:20.894118 IP 192.168.0.127.37618 > reviews-7df9f59bd4-jqmlc.http: Flags [P.], seq 0:517, ack 1, win 58, options [nop,nop,TS val 25059778 ecr 25059778], length 517: HTTP
E..9w.@.?.?........x...P\).........:.s.....
.~a..~a............._
yp/....i.g..|y.'.'.....f4..0q .eL.[....7.o..:."Q)..Ww.'l.o..x-.........+.../...,.0.......4.2../outbound_.8000_._.reviews.foo.svc.cluster.local..........
```


In the above output, it is seen that the traffic sent from the client to the server is encrypted, which means that mTLS is enabled by default when there is no explicit peerauthentication CRD and destinationRule CRD.


Case 2 — no peerauthentication CRD and distinationRule in DISABLE mode


Next we will see what happen if we set distinationRule tls mode to DISABLE, which means the client will not setup a TLS connection to the server.


```
$ kubectl apply -f destinationRule-disable.yaml
destinationrule.networking.istio.io/reviews created
```


The distinationRule in DISABLE mode determines that client sidecar sends plain text traffic to the server, as there is no explicit peerauthentication policy, when client connects to server, we get 200 response code.


```
$ kubectl exec "$(kubectl get pod -l app=client -n foo -o jsonpath={.items..metadata.name})" -c client -n foo -- wget --server-response http://reviews.foo:8000 2>&1 | awk 'FNR==2 {print}'
HTTP/1.1 200 OK
```


We can observe the tcpdump result indicates the traffic isn’t encrypted:


```
...
.......8GET / HTTP/1.1
host: reviews.foo:8000
user-agent: Wget
x-forwarded-proto: http
x-request-id: 59837c92-d219-9503-ac6e-45b45e55bd0c
x-envoy-decorator-operation: reviews.foo.svc.cluster.local:8000/*
x-envoy-peer-metadata: ChoKDkFQUF9DT05UQUlORVJTEggaBmNsaWVudAoaCgpDTFVTVEVSX0lEEgwaCkt1YmVybmV0ZXMKHwoMSU5TVEFOQ0VfSVBTEg8aDTE5Mi4xNjguMC4xMjcKGQoNSVNUSU9fVkVSU0lPThIIGgYxLjE2LjEKuAEKBkxBQkVMUxKtASqqAQoPCgNhcHASCBoGY2xpZW50CiQKGXNlY3VyaXR5LmlzdGlvLmlvL3Rsc01vZGUSBxoFaXN0aW8KEwoHc2VydmljZRIIGgZjbGllbnQKKwofc2VydmljZS5pc3Rpby5pby9jYW5vbmljYWwtbmFtZRIIGgZjbGllbnQKLwojc2VydmljZS5pc3Rpby5pby9jYW5vbmljYWwtcmV2aXNpb24SCBoGbGF0ZXN0ChoKB01FU0hfSUQSDxoNY2x1c3Rlci5sb2NhbAoQCgROQU1FEggaBmNsaWVudAoSCglOQU1FU1BBQ0USBRoDZm9vCj4KBU9XTkVSEjUaM2t1YmVybmV0ZXM6Ly9hcGlzL3YxL
```


Case 3 — peerauthentication in STRICT mode and distinationRule in DISABLE mode


This time, we will set the peerauthentication mtls mode to STRICT, which indicates the sidecar proxy of reviews server only accept mTLS connection and distinationRule remains the same DISABLE mode as case 2.


```
$ kubectl apply -f peerauthentication-strict.yaml
peerauthentication.security.istio.io/default created
```


In this case, the peerauthentication policy (the sidecar proxy of reviews server only accepts mTLS connection) conflicts with distinationRule(the sidecar proxy of client doesn’t set up mTLS connection to the reviews server), when client connects to the server again, we get `503 Service Unavailable`. The plaintext traffic is tunneled to the server from the tcpdump end.


```
$ kubectl exec "$(kubectl get pod -l app=client -n foo -o jsonpath={.items..metadata.name})" -c client -n foo -- wget --server-response http://reviews.foo:8000 2>&1 | awk 'FNR==2 {print} '
HTTP/1.1 503 Service Unavailable
```


Case 4 — peerauthentication in DISABLE mode and no destinationRule CRD


We delete the peerauthentication and destinationRule in the Case 3, create a new peerauthentication with mtls mode of DISABLE to configure reviews Server’s sidecar proxy to only accept plain text traffic.


```
$ kubectl apply -f peerauthentication-disable.yaml
peerauthentication.security.istio.io/default created
```


The reviews server is accessible from the client container.


```
$ kubectl exec "$(kubectl get pod -l app=client -n foo -o jsonpath={.items..metadata.name})" -c client -n foo -- wget --server-response http://reviews.foo:8000 2>&1 | awk 'FNR==2 {print}'
HTTP/1.1 200 OK
```


The tcpdump shows the traffic in plain text:


```
GET / HTTP/1.1
host: reviews.foo:8000
user-agent: Wget
x-forwarded-proto: http
x-request-id: 64948a46-cf86-9055-9d67-4e238bd1a7ad
x-envoy-decorator-operation: reviews.foo.svc.cluster.local:8000/*
x-envoy-peer-metadata: ChoKDkFQUF9DT05UQUlORVJTEggaBmNsaWVudAoaCgpDTFVTVEVSX0lEEgwaCkt1YmVybmV0ZXMKHwoMSU5TVEFOQ0VfSVBTEg8aDTE5Mi4xNjguMC4xMjcKGQoNSVNUSU9fVkVSU0lPThIIGgYxLjE2LjEKuAEKBkxBQkVMUxKtASqqAQoPCgNhcHASCBoGY2xpZW50CiQKGXNlY3VyaXR5LmlzdGlvLmlvL3Rsc01vZGUSBxoFaXN0aW8KEwoHc2VydmljZRIIGgZjbGllbnQKKwofc2VydmljZS5pc3Rpby5pby9jYW5vbmljYWwtbmFtZRIIGgZjbGllbnQKLwojc2VydmljZS5pc3Rpby5pby9jYW5vbmljYWwtcmV2aXNpb24SCBoGbGF0ZXN0ChoKB01FU0hfSUQSDxoNY2x1c3Rlci5sb2NhbAoQCgROQU1FEggaBmNsaWVudAoSCglOQU1FU1BBQ0USBRoDZm9vCj4KBU9XTkVSEjUaM2t1YmVybmV0ZXM6Ly9hcGlzL3YxL25hbWVzcGFjZXMvZGVmYXVsdC9wb2RzL2NsaWVudAoXChFQTEFURk9STV9NRVRBREFUQRICKgAKGQoNV09SS0xPQURfTkFNRRIIGgZjbGllbnQ=
x-envoy-peer-metadata-id: sidecar~192.168.0.127~client.foo~foo.svc.cluster.local
x-envoy-attempt-count: 1
x-b3-traceid: c9dc6dce0f0aaab52dc4e89f98c47780
x-b3-spanid: 2dc4e89f98c47780
x-b3-sampled: 1
```


Case 5 — peerauthentication in STRICT mode and distinationRule in ISTIO_MUTUAL mode


We set up peerauthentication and destinationRule as below.


```
$ kubectl apply -f peerauthentication-strict.yaml
peerauthentication.security.istio.io/default created
​
$ kubectl apply -f destinationRule-istio-mutual.yaml
destinationrule.networking.istio.io/reviews created
```


Both peerauthentication policy and destinationRule agree on that only mTLS traffic is acceptable, it is as expected to see the successful communication with mTLS enabled:


```
$ kubectl exec "$(kubectl get pod -l app=client -n foo -o jsonpath={.items..metadata.name})" -c client -n foo -- wget --server-response http://reviews.foo:8000 2>&1 | awk 'FNR==2 {print}'
HTTP/1.1 200 OK
```


tcpdump gets encrypted traffic:


```
tcpdump: verbose output suppressed, use -v[v]... for full protocol decode
listening on eth0, link-type EN10MB (Ethernet), snapshot length 262144 bytes
04:06:41.053866 IP 192.168.0.127.38668 > reviews-7df9f59bd4-jqmlc.http: Flags [P.], seq 685747451:685748554, ack 2686206994, win 99, options [nop,nop,TS val 1373937 ecr 1358516], length 1103: HTTP
E...Jk@.?.j........x...P(.....D....c.......
............Jv._...>..L.....Uc&,v..T.|C....,[D.m.../..L..$Q
..I{?..?..\..>En...i;...R..UN... }.....}.T........|.....duY...f....C..D.w..!.FO4(.........l`
....lW.;.....D.....W.hm!.w.....:o5:.0$K.Y.......\..;.....j_[..E....&.O. ...;..&D...;....Y..f'Z'P..
.S....qa.W.4..f.q.....-...t..[Ly4k..?$....H..v.;....$......\....+
g..B..}>.u.o.......4|......P....h?..X.".t\......[..*.F.O.....j".w*..|...."...l.Xxy....K....Ig..|
S.]....N.Cl.i3..1]l+h.W=`P..y......XX....W3...<G..."....q`lJ......5...)....\..&...M...6...|..v5.k..H.........dy..g4x...Y.*...FW......%.......3?...h.D.1v.:#....+..,.n.4:...6.RY....5{.-<.l.JH...Q..1....u,...2..:d..5y....;.E...qVa'..#g.S....................V.>Q.}M..'.w..b....iZ.C..$....V...Xx.}.ui...`q~..U...!...7.I.....|8...........q..:..=F..../u..<.Ewnb...?.....+j..L.~K.d..:.y.\...MpY....G....R..\.det.+;.J\......^+A.8...5&.<j...".=..f.8...o!D..a...cF...../..U..hHV>[...F.n....W0.SIm..3d...... ..w,t# .MY.W..&...[.r..../A.<NJ..P.....nk!w...D........Q,.X..t\...&.`.X.[l{.p.....$.."v..@...sQM..R.8e.......R....p~*.c......6....Rg.+W.....Q;b.&;.
```


Summarize the case 1 — case 5 for the client with proxy and the reviews server with proxy in the below table:


Using the similar method, we can get the results for the client without proxy and the reviews server with proxy, which is listed for your reference:


You can try more cases as you desired to solidify your understanding of how mTLS works in the Istio service mesh.

## Final Thoughts


Now it is the end of the blog. If you have any questions or feedback, feel free to leave a comment. If you think this blog post is helpful, please click the clap 👏 button below a few times to show your support!

---

*Originally published on [Medium](https://infosecwriteups.com/enforce-zero-trust-with-east-west-traffic-encryption-in-kubernetes-with-istio-part-2-5a3454560353). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
