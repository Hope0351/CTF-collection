# :globe_with_meridians: From SSRF to RCE: A 7-Step Chain Against PostHog

---

# From SSRF to RCE: A 7-Step Chain Against PostHog

>

*When a 24-hour research window turned into a 7-step RCE chain, we found that PostHog’s SSRF, a ClickHouse 0day, and default PostgreSQL credentials were the perfect storm for a full remote code execution.*A deep dive into how overlooked validations, a SQL escaping bug, and static credentials turned a simple webhook into a full system compromise.Source: Mehmet Ince @mdisec — [Source link](https://mdisec.com/inside-posthog-how-ssrf-a-clickhouse-sql-escaping-0day-and-default-postgresql-credentials-formed-an-rce-chain-zdi-25-099-zdi-25-097-zdi-25-096/?ref=openexploit.in)

## Highlights

## Key points

- PostHog’s webhook save endpoint bypassed SSRF validations applied during testing.

- The Rust webhook worker followed HTTP redirects, allowing POST to GET conversion for ClickHouse access.

- ClickHouse table functions accepted user input that was improperly escaped for PostgreSQL queries.

- Dollar quoting ($$) bypassed ClickHouse’s backslash escaping, enabling SQL injection into PostgreSQL.

- Static Docker names and default PostgreSQL credentials formed the final pivot point.

- The chain culminated in a reverse shell via COPY FROM PROGRAM on the PostgreSQL…

---
