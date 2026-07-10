# :globe_with_meridians: Enforce Zero Trust With East‑West Traffic Encryption in Kubernetes with Istio - Part 1

---

# Enforce Zero Trust With East‑West Traffic Encryption in Kubernetes with Istio — Part 1

*Photo by [Ricky Kharawala](https://unsplash.com/@sweetmangostudios?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

A typical enterprise’s infrastructure has grown increasingly complex, especially when they move from traditional monolithic software platform to Kubernetes-based system to manage distributed collections of microservices, which poses unique challenges to the already demanding situation. The complexity has outstripped the legacy methods of perimeter-based network security and calls out the need for new cybersecurity model knowns as “zero trust” (ZT).

Zero trust is an evolving set of security paradigms and transforms defense from static and network based perimeters to the focuses on data, service, assets and subjects. In essence, a Zero Trust approach does not trust any user, device, or request by default, it not only acknowledges that threats exist inside and outside of the network, but it assumes that a breach is inevitable (or has likely already occurred), as a result, Zero trust assumes there is no implicit trust granted to assets or user accounts based solely on their physical or network location. All communication should be done in the most secure manner available and provide source authentication regardless of network location.

Unfortunately, Kubernetes neither encrypts or authenticates pod to pod communication, or as some people like to refer to it as East-West Traffic. Moreover, Kubernetes doesn’t provide a built-in certificate management and distribution mechanism needed to enforce TLS for cross-pod communication, which makes the TLS implementation more daunting. Service mesh can close the gap by using a mutual TLS out of the box to simplify the enforcement of ZT on east‑west traffic encryption.

In this blog, we will learn how to use service mesh like Istio to implement mutual TLS (mTLS) to improve network security.

## 1. TLS and mTLS Communication

TLS is a widely adopted security protocol used to create authenticated and encrypted connections between endpoints over the network. TLS is required when a client needs to confirm the identity of the server in order to guard against man-in-the-middle attacks.

In a simplified TLS-encrypted communication:

- Client connects to server

- Server presents its TLS certificate to client

- Client verifies the server’s certificate and confirms the identity of the server

- Client and server exchange information over encrypted TLS connection

Mutual Transport Layer Security (mTLS) is a process that establishes an encrypted TLS connection in which both server and client use X.509 digital certificates to authenticate each other. It requires that both the server and the client have a certificate and public/private key pair. The identities of both server and client are verified before a connection is established and data is exchanged.

The simplified steps in mTLS are briefly summarized as below:

- Client connects to server

- Server presents its TLS certificate to client

- Client verifies the server’s certificate and confirms the identity of the server

- Client presents its TLS certificate to server

- Server verifies the client’s certificate and confirms the identity of the client

- Server grants access

- Client and server exchange information over encrypted TLS connection

Speaking of the certificate in TLS and mTLS, one distinction is that, for TLS, the certificate is issued by a public organization, whereas for mTLS, the organization who implements mTLS will itself act as the certifying authority.

## 2. What is Service Mesh

As the deployment of distributed services, they become harder to understand and manage. In terms f security, in a Kubernetes-based system, the cross-service communication is neither secured nor restricted, every service inside can talk with each other freely. The Service Mesh is a dedicated infrastructure layer designed to facilitate service-to-service communications between microservices, it provides features like service discovery, load balancing, failure recovery, metrics, and monitoring. It also address more complex operational requirements, like access control, encryption, and end-to-end authentication.

## 3. How Istio Works for mTLS

Istio is one of implementations of Service Mesh. An Istio service mesh is logically split into a data plane and a control plane.

The data plane is composed of a group of intelligent proxies ([Envoy](https://www.envoyproxy.io/)) deployed as sidecars. The proxy deployed along with each service intercepts all your network traffic to enforce policy decisions, collect and report rich telemetry.

## Get Yani’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The control plane is a combined component — Istiod which manages and configures the Envoy proxy in each microservice pod, provides service discovery and certificate management. As we mentioned earlier, in mTLS, the certificate is signed internally, in Istio, Istiod acts as a Certificate Authority (CA) and generates certificates for mTLS communication in the data plane.

*[https://istio.io/latest/docs/ops/deployment/architecture/arch.svg](https://istio.io/latest/docs/ops/deployment/architecture/arch.svg)*

The service mesh logic and configuration is separated with the application logic and configuration. The integration of Istio to the Kubernetes-based system requires no change to the existing resource deployment YAML files. All the configurations on these Istio components will be done in Istio itself.

Istio uses Kubernetes CustomResourceDefinitions(CRD) API for configuration. We will see PeerAuthentication CRD and DestinationRule CRD when we enable mTLS for cross-service traffic in the subsequent part.

To enable mTLS inside Kubernetes-based system, we should understand Envoy proxy traffic breakdown and Auto mTLS described in [TLS Configuration in Istio](https://istio.io/latest/docs/ops/configuration/traffic-management/tls-configuration/).

*[https://istio.io/latest/docs/ops/configuration/traffic-management/tls-configuration/sidecar-connections.svg](https://istio.io/latest/docs/ops/configuration/traffic-management/tls-configuration/sidecar-connections.svg)*

There are two key resources in configuration: `[PeerAuthentication](https://istio.io/latest/docs/reference/config/security/peer_authentication/)`[resource](https://istio.io/latest/docs/reference/config/security/peer_authentication/) in 1.External inbound traffic and `[DestinationRule](https://istio.io/latest/docs/reference/config/networking/destination-rule/)`[resource](https://istio.io/latest/docs/reference/config/networking/destination-rule/) in 4.External outbound traffic which determine the traffic type between pods. Next, we will spell these two resources out in the below.

PeerAuthentication CRD

`PeerAuthentication` is used to configure what type of mTLS traffic the sidecar proxy can receive.

The following example of PeerAuthentication policy specifies that transport authentication for all workloads under namespace `foo` must use mutual TLS:

```
apiVersion: security.istio.io/v1beta1
kind: PeerAuthentication
metadata:
name: default
namespace: foo
spec:
selector:
matchLabels:
app: reviews
mtls:
mode: STRICT
​
```

The metadata.namespace specifies the namespace where the PeerAuthentication policy will be stored and applied. If spec.selector field is defined as above, the policy only applies to matched workloads, if no spec.selector is set, the policy will be applied to all workloads in the namespace specified in metadata.namespace.

Istio provides 4 mutual TLS modes for spec.mtls.mode:

`UNSET` Inherit from parent, if has one. Otherwise treated as PERMISSIVE.

`DISABLE` Connection is not tunneled, accept only plain text.

`PERMISSIVE` Connection can be either plaintext or mTLS tunnel.

`STRICT` Connection is an mTLS tunnel (TLS with client cert must be presented).

In the above example, STRICT mode indicates that the traffic must be tunneled to Envoy proxy in mTLS mode.

DestinationRule CRD

`DestinationRule` is used to configure what type of TLS traffic the sidecar proxy can send.

The following destination rule configures a client proxy to use Istio mutual TLS when talking to reviews service.

```
apiVersion: networking.istio.io/v1alpha3
kind: DestinationRule
metadata:
name: reviews
spec:
host: reviews
trafficPolicy:
tls:
mode: ISTIO_MUTUAL
​
```

spec.host field represents the name of a service from the service registry. In Kubernetes, when short names are used (e.g. “reviews” instead of “reviews.default.svc.cluster.local”), Istio will interpret the short name based on the namespace of the rule, irrespective of the actual namespace associated with the reviews service. Regarding spec.trafficPolicy.tls.mode, there are 4 TLS connection modes:

`DISABLE` Do not setup a TLS connection to the upstream endpoint.

`SIMPLE` Originate a TLS connection to the upstream endpoint.

`MUTUAL` Secure connections to the upstream using mutual TLS by presenting client certificates for authentication.

`ISTIO_MUTUAL` Secure connections to the upstream using mutual TLS by presenting client certificates for authentication. Compared to Mutual mode, this mode uses certificates generated automatically by Istio for mTLS authentication. When this mode is used, all other fields in `ClientTLSSettings` should be empty.

We will see some demos in part 2 to reinforce our understanding.

## Final Thoughts

Now it is the end of the blog. If you have any questions or feedback, feel free to leave a comment. If you think this blog post is helpful, please click the clap 👏 button below a few times to show your support!

---
