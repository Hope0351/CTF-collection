# [Shop](https://play.picoctf.org/practice/challenge/134)

## Overview

**Points**: 50

**Category**: [Reverse Engineering](../)

## Description

Best Stuff - Cheap Stuff, Buy Buy Buy... Store Instance: [source](./source). The shop is open for business at `nc mercury.picoctf.net 3952`.

## Hints

1. Always check edge cases when programming

## Solution

There's 3 items on the menu, and the third one (Fruitful Flag) cost 100 coins. 

```bash
Welcome to the market!
=====================
You have 40 coins
	Item		Price	Count
(0) Quiet Quiches	10	12
(1) Average Apple	15	8
(2) Fruitful Flag	100	1
(3) Sell an Item
(4) Exit
```

We can't sell enough items to get 100 coins, so we need to find another way. The hint suggests checking edge cases, so we can try to sell items we don't have.

```bash
Choose an option: 
3
Your inventory
(0) Quiet Quiches	10	0
(1) Average Apple	15	0
(2) Fruitful Flag	100	0
What do you want to sell? 
1
How many?
1
Hey you don't have that many on your cart! What kind of scam is this?
```

It doesn't let us sell anything. However, it seems that negative numbers are allowed.

```bash
Your inventory
(0) Quiet Quiches	10	0
(1) Average Apple	15	0
(2) Fruitful Flag	100	0
What do you want to sell? 
1
How many?
-5
You have -35 coins
```

If selling a negative amount reduces our coins, then buying a negative amount should increase our coins. 

(Restart the server so your current coins are 40)

```bash
Welcome to the market!
=====================
You have 40 coins
	Item		Price	Count
(0) Quiet Quiches	10	12
(1) Average Apple	15	8
(2) Fruitful Flag	100	1
(3) Sell an Item
(4) Exit
Choose an option: 
0
How many do you want to buy?
-6
You have 100 coins
	Item		Price	Count
(0) Quiet Quiches	10	18
(1) Average Apple	15	8
(2) Fruitful Flag	100	1
(3) Sell an Item
(4) Exit
```

Now that we have 100 coins, we can buy the Fruitful Flag.

```bash
You have 100 coins
	Item		Price	Count
(0) Quiet Quiches	10	18
(1) Average Apple	15	8
(2) Fruitful Flag	100	1
(3) Sell an Item
(4) Exit
Choose an option: 
2
How many do you want to buy?
1
Flag is:  [112 105 99 111 67 84 70 123 98 52 100 95 98 114 111 103 114 97 109 109 101 114 95 57 99 49 49 56 98 98 102 125]
```

This looks like ASCII values, so we can convert it to text.

```python
>>> bytes([112, 105, 99, 111, 67, 84, 70, 123, 98, 52, 100, 95, 98, 114, 111, 103, 114, 97, 109, 109, 101, 114, 95, 57, 99, 49, 49, 56, 98, 98, 102, 125]).decode()
'picoCTF{b4d_brogrammer_9c118bbf}'
```

## Flag

`picoCTF{b4d_brogrammer_9c118bbf}`