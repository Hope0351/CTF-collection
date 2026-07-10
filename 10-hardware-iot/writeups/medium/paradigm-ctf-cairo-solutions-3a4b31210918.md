# :electric_plug: Paradigm-CTF Cairo Solutions. Paradigm CTF was a blast. Unlike last…

---

# Paradigm-CTF Cairo Solutions

Paradigm CTF was a blast. Unlike last year, when challenges were mostly focused on Solidity and the EVM, this year introduced challenges in two new ecosystems. Solana/Rust, and StarkNet/Cairo.

This write-up will focus on the solutions to the Cairo challenges. The code for setting up the environment, as well as the solutions are available here: [https://github.com/amanusk/cairo-paradigm-ctf](https://github.com/amanusk/cairo-paradigm-ctf)

## Preamble

StarkNet is an emerging ecosystem, and thus not all toolings are fully matured. This might have caused some difficulties connecting to the private node of the exercise. This can definitely be improved and is also a great opportunity for new developers to get involved in a new ecosystem with lots of opportunities to build.

In this CTF, the best way to connect to the custom environment provided by the organizers was to follow the implementation of the Paradigm infrastructure setup, publicly available [here](https://github.com/paradigmxyz/paradigm-ctf-infrastructure). Using [starknet.py](https://starknetpy.readthedocs.io/en/latest/) was the best way to connect with the node.

Another difference of StarkNet from Ethereum has to do with the different accounts architecture of StarkNet. Unlike Ethereum and similar chains, where there are two types of accounts: EOAs and Smart Contracts, StarkNet does not have an EOA. This means a private/public key pair can be in charge of many account contracts, and their addresses need to be known. This can be a very powerful and useful tool. However, in this CTF, the address of the account to the player was not printed out as part of the challenge information. Finding it was possible but was not immediately obvious (more on this later)

## Challenge 1: RIDDLE-OF-THE-SPHINX

This is the first “Sanity Check” challenge. Reading the challenge script, we see we need to call the `solution` function of the contract, and have the answer be “man”.

```
async def checker(client: AccountClient, riddle_contract: Contract, player_address: int) -> bool:
solution = (await riddle_contract.functions["solution"].call()).solution return to_bytes(solution).lstrip(b"\\x00") == b"man"
```

Cairo does not have a `string` type. Short [strings](https://starknet.io/docs/how_cairo_works/consts.html#short-string-literals) can be encoded/decoded as a felt, and are thus limited to 31 bytes.

To solve the challenge, all we need is to encode the word “man” as a felt, and invoke the `solve` function on the contract.

```
def str_to_felt(text):
if len(text) > MAX_LEN_FELT:
raise Exception("Text length too long to convert to felt.") return int.from_bytes(text.encode(), "big")input_string = str_to_felt("man")
response = await account_client.execute(calls=[riddle_contract.functions["solve"].prepare(input_string)], max_fee=int(1e16))
```

## Challenge 2: CAIRO-PROXY

This is the first challenge that really required some Cairo knowledge. The challenge consisted of 3 contracts.

- First, as the name would suggest: a simple proxy contract that forwards calls to an implementation contract.

- An ERC20 contract where only the owner has access to a `mint` function, allowing him to mint tokens to addresses

- A `utils` contract with a read and write function

To pass the challenge the player needs to have exactly 50000e18 tokens when calling the implementation contract

```
player_balance = (await wrapper_contract.functions["balanceOf"].call(player_address)).balance
return player_balance == int(50000e18)
```

The critical flaw was that the `utils` contract imported by the proxy had a write function to the storage. The function `auth_write_storage` does not check the caller against the existing storage but rather receives the `auth_account` as a parameter.

The plan is thus:

- Call the `auth_write_storage` function with the address of the owner as the target

- Change the owner to the player’s address

- Mint tokens for the player

The import [statement](https://github.com/amanusk/cairo-paradigm-ctf/blob/7b2d0f2d8b6ff2b5b070ebb0aa9e3e493c85201e/contracts/proxy.cairo#L6) imports both the read and write function from the utils contract. All we need do to is combine the ABI of the `ERC20` contract, with the ABI of the `utils` contract, and specify the address of the proxy when making the calls.

The address of the variable `owner` which we need to do the write is callcualted as `starknet_keccak(VAR_NAME)`. The function is available in the StarkNet standard library.

We also need to know the address of the player. This is the bit where many got confused. The testnet environment setup for the challenge uses the `starknet-devnet` utility. It creates several accounts pre-loaded with ETH for transaction fees on initiation. To know the address of the account the following parameters are required:

- The class hash of the account contract

- The public key used in the calldata of the constructor

- Salt

Neither these parameters nor the address of the player’s account were presented during the challenge initiation. To get the `salt` and the `class_hash` required searching the infrastructure repository, and simply copy the same code to recreate the account. But hey, this is a CTF. Compared to other challenges in the CTF (e.g. breaking the stack of Foundry) this was a breeze.

```
player_address = calculate_contract_address_from_hash(
salt=20,
class_hash=1803505466663265559571280894381905521939782500874858933595227108099796801620,
constructor_calldata=[player_public_key],
deployer_address=0,
)
```

From this point on we have all we need to complete the challenge:

- Calculate the address of `owner`

```
ownerVarAddress = starknet_keccak(b"owner")
print("OwnerVar address", ownerVarAddress)
```

- Call the function `auth_write_storage` with the player as the `auth_account` and as the new owner to write to the filed

```
response = await account_client.execute(
calls=[
proxyContract.functions["auth_write_storage"].prepare(player_address, ownerVarAddress, player_address)
],
max_fee=int(1e16)
)
```

- Call the `mint` function using the ABI of ERC20, and the address of the proxy, with player’s address as the target of the mint

```
response = await account_client.execute(calls=[proxyContract.functions["mint"].prepare(player_address, int(50000e18))], max_fee=int(0))
```

To protect against this vulnerability, it would have been better if the proxy contract implemented the functions to check the owner themselves, or, if the implementation had the desired functions, where the owner is checked against the storage.

## Challenge 3: CAIRO-AUCTION

Unfortunately, I was not able to solve this challenge during the CTF event itself, which is why I wanted to recreate the environment and take the time to solve it properly once the event was over.

The challenge had only one contract, `auction.cairo`. Winning the challenge required winning an auction. Reading the deployment script, it was clear that two other participants received 100K tokens, while the player received 50K, and was required to win.

The contract had several “clues” as to where to look for the vulnerability. The ERC20 contract used to implement the token uses the OpenZeppelin implementation, and is thus (most likely) to be safe and not the place to look for the bug.

The bug reveals itself in this [line](https://github.com/amanusk/cairo-paradigm-ctf/blob/7b2d0f2d8b6ff2b5b070ebb0aa9e3e493c85201e/contracts/auction.cairo#L188) of the contract. Can you guess what it is?

To answer that we need to go a bit deeper into the dependencies. On the face of it, the contract is doing the right thing. It checks that the amount passed to increase the bid is less_that_or_equal to the unlocked funds the player has in the auction account. However the check might not behave exactly as expected.

The call `uint256_le` is implemented in the following way:

```
let (not_le) = uint256_lt(a=b, b=a)
return (1 - not_le)
```

I.e. for the numbers `a` and `b` check if `b` is less than `a`, and return the inverse. If `a==b`, then `a` is not less than `b` and the answer is `true`. if `a<b` then `b` is not less than `a` and the answer is `false`. As expected.

The function `uint256_lt` is implemented as follows:

```
if a.high == b.high:
return is_le(a.low + 1, b.low)
end
return is_le(a.high + 1, b.high)
```

Since felt is a number of 252 bits, and uint256 has (surprise..) 256 bits, one felt is not enough to represent the entire range of uint256. It is thus comprised of two felts, (low, high).

This is however not that too important for our case. We need to look deeper at `is_le`

The function `is_le`is implemented as follows:

```
return is_nn(b - a)
```

I.e: check that `b - a` is not a negative number

Going deeper to `is_nn`, we see the comment says:

```
# Returns 1 if a >= 0 (or more precisely 0 <= a < RANGE_CHECK_BOUND).
# Returns 0 otherwise.
```

Aha! It is not enough for it to be the case that `a>=0`, but it also needs to be `< RANGE_CHECK_BOUND`. The value of `RANGE_CHECK_BOUND` is `2^128`... There is a reason `2^128` was chosen as the bound for the range check, even though `felt` supports numbers higher than this. The discussion can be read [here](https://stackoverflow.com/questions/72922293/why-does-range-check-ptr-chek-for-0-2128-instead-of-0-p-2/72965351#72965351). The reason is mainly that it is costly to make the range check to `2^250` and it is not commonly used. The implementer must be aware of this limit, and if required, perform checks on the upper value of the range as well.

So what happens if we provide a number higher than `2^128` as the amount, even if our current balance in the contract is 0:

```
uint256_le(2^128+1,0)=>
1 - uint256_lt(0,2^128+1)=>
is_le(2*128+1 - 0) =>
is_nn(2*128+1) => false
# boom. Going up the stack:
is_le(2*128+1 - 0) == false
uint256_lt(0,2^128+1) == false
1 - uint256_lt(0,2^128+1) == true
uint256_le(2^128+1,0) == true # The check passes here!
```

A few lines later in the contract, there is a [check](https://github.com/amanusk/cairo-paradigm-ctf/blob/7b2d0f2d8b6ff2b5b070ebb0aa9e3e493c85201e/contracts/auction.cairo#L193) that we have not created an overflow.

Tripping it can be avoided by passing the `low` part of the `uint256` as `2^128+1`, it will be more than enough to beat the bid of `100k` of the other players, without tripping an overflow. It is still well within the bounds of `uint256`. Passing `high` as `2^128+1` will fail this check.

Later in the contract, the check if you are the new winner will pass. `uint256_lt` will check if `2^128+1 - 100K` is not negative, which it is.

## Conclusion

Coding on StarkNet is awesome. It introduces a new paradigm (😉) of security and scaling. As with any new ecosystem, it takes time for tools, standards, and best practices to mature.

Challenges as this CTF offers a great glimpse into the ecosystem and helps to push forward security awareness and best practices. More please next time!

Join the StarkNet community in the discord at [http://starknet.io/discord](http://starknet.io/discord) and begin your Cairo hacking journey. The atmosphere is ✨!

---
