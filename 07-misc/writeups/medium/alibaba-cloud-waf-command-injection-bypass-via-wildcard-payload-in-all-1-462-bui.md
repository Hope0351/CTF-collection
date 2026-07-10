# :game_die: Alibaba Cloud WAF Command Injection Bypass via Wildcard Payload in All 1,462 Built-in Rule Set

---

# Alibaba Cloud WAF Command Injection Bypass via Wildcard Payload in All 1,462 Built-in Rule Set

>

Alibaba WAF version 3.0 was tested and very common payload was found bypassing command injection.

While testing the capabilities of the firewall itself it was found that it was possible to bypass the rules. Due to the testing scope limitations, not all rules were tested, but bypass have been highlighted below.

### Description

A web application firewall (WAF) is an HTTP application firewall that applies a set of rules to an HTTP conversation.

In this case, Alibaba WAF 3.0 was tested against the Damn Vulnerable Web Application (DVWA), a known vulnerable application, with all 1,462 built-in rules enabled. These rules generally cover common attacks such as RCE, XSS, LFI, and SQL injection.

The WAF is designed to protect against attacks; however, it was found that some payloads were not protected by the WAF, and command injection was possible even when the WAF rule to protect against RCE was enabled.

The payload used to bypass command injection was through a wildcard, `“?”, i.e. /???/??t%20/???/??ss?? `~ /bin/cat /etc/passwd.

`Payload: cat /etc/pa??wd or any wild card which works on linux using ?.`

WAF Endpoint: yikddcuvffqc4pf6bnvwrkct2p3extri.aliyunwaf4.com.

## Get Divyanshu’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Load Balancer: alb-4mtl8i5bgretjudf2j.ap-southeast-1.alb.aliyuncs.com

*DNS Settings*

## Steps To Reproduce:

- Set up vulnerable DVWA on the ec2 instance along with ALB and Alibaba WAF 3.0 enabled with 1,462 built-in rules enabled

- Enable the AWS WAF: [http://mywaf.xxxxx.co.in](http://mywaf.securitydojo.co.in)

- Login via admin/password and visit Command Injection.

- Perform the below-mentioned use cases by running: `8.8.8.8; cat /etc/passw?`

- Check for the bypass

Note: In case of other payload it will show blocked which shows WAF has been implemented Successfully.

## Impact

- The impact of the vulnerability is significant and can lead to financial loss for companies that heavily rely on Alibaba WAF 3.0. This is due to the fact that they may switch to other, better-paid services such as Cloudflare.

- The exploitation of a vulnerable application protected by Alibaba WAF is a serious concern as it defeats the basic feature of WAF, which is to protect against attacks. Command injection can be easily exploited as a result of this bypass.

- Companies and users who rely on Alibaba WAF for protection are now exposed to OWASP attacks in case their applications are vulnerable. To mitigate this risk, they may need to purchase WAF from a marketplace or a third party, which can be costly. Some companies may even migrate to another cloud provider, resulting in a loss for both Alibaba and their customers who rely on WAF to protect their applications.

### Status: Closed — Informative

Credit: 

---
