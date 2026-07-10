# :game_die: REQUIRED vs REQUIRES_NEW in Spring Boot: Transaction Propagation Demystified

---

*REQUIRED vs REQUIRES_NEW in Spring Boot: Transaction Propagation Demystified*

# REQUIRED vs REQUIRES_NEW in Spring Boot: Transaction Propagation Demystified

Spring Boot makes transaction management dead simple with `@Transactional`, but things get interesting when multiple methods, nested calls, or services interact with the same transaction.

Two of the most commonly misunderstood propagation modes are:

- `Propagation.REQUIRED`

- `Propagation.REQUIRES_NEW`

This post breaks down what they mean, how they behave, and when to use each — with real-world examples and code.

## ⚙️ What is Transaction Propagation?

In Spring, transaction propagation defines how a method should behave if a transaction already exists.

- Should it join the existing one?

- Should it start a new one?

- Or should it run without any transaction?

That’s what propagation modes decide.

## 🧩 Propagation.REQUIRED (default)

- Joins the existing transaction if one exists.

- If no transaction is active, starts a new one.

- Rollbacks affect the entire chain.

Code Example:

```
@Service
public class PaymentService {…
```

---
