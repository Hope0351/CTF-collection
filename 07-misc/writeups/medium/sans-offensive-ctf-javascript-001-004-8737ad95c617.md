# :game_die: SANS Offensive CTF - JavaScript☕::001-004

---

>

**JavaScript Stage 004:**

*Code — 4*

**Explanation: **JavaScript’s type coercion is the automatic conversion of values from one data type to another. It happens when JavaScript expects a certain type of data, but it receives a different type. Type coercion can sometimes lead to unexpected behavior or vulnerabilities if not handled properly.

In the context of the provided code, the following line is crucial:

```
let dayOfWeek = Math.abs(parseInt(days) % 7);
```

Here’s how this line works:

- `parseInt(days)`: This attempts to parse the days variable as an integer. If `days` is not a string representing a valid integer, `parseInt` will return `NaN` (Not-a-Number).

- `Math.abs()`: This function returns the absolute value of a number. It ensures that the number passed to it is positive.

- `% 7`: This is the modulo operation, which calculates the remainder of dividing the number by 7.

Now, let’s consider how type coercion could be exploited in this scenario:

- If a very large or very small number (outside the range of representable integers in JavaScript) is passed as the value of `days`, the `parseInt()` function may return `NaN` due to overflow or underflow.

- When `% 7` is performed on `NaN`, it will result in `NaN` because any arithmetic operation involving `NaN` yields `NaN`.

- Therefore, by sending a very large or very small number that causes an overflow or underflow during parsing, an attacker could exploit the code to make `dayOfWeek` become `NaN`. This would lead the execution flow to the `default` case in the `switch` statement, where day is assigned the value “Payday”. As a result, the server would respond with the flag associated with the “Payday” case.

This demonstrates how improper handling of type coercion and numeric operations in JavaScript can lead to unexpected behavior and security vulnerabilities. It’s crucial to validate and sanitize user inputs to prevent such exploits.

**Solution: {“**days”:1.7976931348623157E+10308}

*Flag — 4*

---
