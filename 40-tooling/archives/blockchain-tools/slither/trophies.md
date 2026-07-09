# Slither Trophies

The following lists security vulnerabilities that were found by Slither.
If you found a security vulnerability using Slither,
please submit a PR with the relevant information.

Project | Vulnerability | Date
--|--|--
Parity | Incorrect constructor name | July 2018
Parity | Deletion of a mapping with structure | July 2018
Parity | Uninitialized state variables | July 2018
Basis | Missing return value check | Oct 2018
Origin protocol | Reentrancy | Nov 2018
Numerai | Deletion of a mapping with structure | Jul 2019
Numerai | Missing return value | Jul 2019
Flexa | Reentrancy (events out of order) | Sep 2019
0x | Missing return value | Oct 2019
[Token mint](https://certificate.quantstamp.com/full/token-mint) | Reentrancies | Dec 2019
[Airswap](https://certificate.quantstamp.com/full/airswap) | Missing return value check | Feb 2020
[Stake Technologies Lockdrop](https://certificate.quantstamp.com/full/stake-technologies-lockdrop) | Dangerous strict equality | Mar 2020
[E&Y’s Nightfall](https://blog.trailofbits.com/2020/05/15/bug-hunting-with-crytic/) | Missing return value | May 2020
[E&Y’s Nightfall](https://blog.trailofbits.com/2020/05/15/bug-hunting-with-crytic/) | Empty return value | May 2020
[DefiStrategies](https://blog.trailofbits.com/2020/05/15/bug-hunting-with-crytic/) | Modifier can return the default value | May 2020
[DefiStrategies](https://blog.trailofbits.com/2020/05/15/bug-hunting-with-crytic/) | Dangerous strict equality allows the contract to be trapped | May 2020
[DOSnetwork](https://blog.trailofbits.com/2020/05/15/bug-hunting-with-crytic/) | Abi `encodedPacked` collision | May 2020
[EthKids](https://blog.trailofbits.com/2020/05/15/bug-hunting-with-crytic/) | `msg.value` is used two times to compute a price | May 2020
[HQ20](https://blog.trailofbits.com/2020/05/15/bug-hunting-with-crytic/) | Reentrancy | May 2020
[Dloop](https://certificate.quantstamp.com/full/dloop-art-registry-smart-contract) | Dangerous `block.timestamp` usage | Jun 2020
[Atomic Loans](https://certificate.quantstamp.com/full/atomic-loans) | Uninitialized state variable | Jul 2020
[Atomic Loans](https://certificate.quantstamp.com/full/atomic-loans) | State variable shadowing | Jul 2020
[Atomic Loans](https://certificate.quantstamp.com/full/atomic-loans) | Reentrancy | Jul 2020
Amp | Duplicate contract name | Aug 2020
[PerlinXRewards](https://certificate.quantstamp.com/full/perlin-x-rewards-sol) | Multiple reentrancies | Aug 2020
[Linkswap](https://certificate.quantstamp.com/full/linkswap) | Lack of return value check | Nov 2020
[Linkswap](https://certificate.quantstamp.com/full/linkswap) | Uninitialized state variable | Nov 2020
[Cryptex](https://certificate.quantstamp.com/full/cryptex) | Lack of return value check | Nov 2020
Hermez | Reentrancy | Nov 2020
[Unoswap](https://www.unos.finance/wp-content/uploads/2020/11/block-audit.pdf) | Contract locking ethers | Nov 2020
[Idle](https://certificate.quantstamp.com/full/idle-finance) | Dangerous divide before multiply operations | Dec 2020
[RariCapital](https://certificate.quantstamp.com/full/rari-capital) | Lack of return value check | Dec 2020
[RariCapital](https://certificate.quantstamp.com/full/rari-capital) | Uninitialized state variable | Dec 2020
wfil-factory | Reentrancy | Dec 2020
Origin Dollar | Reentrancy | Jan 2021
Origin Dollar | Variable shadowing | Jan 2021
OriginTrait | Reentrancy | Jan 2021
[AlphaHomoraV2](https://certificate.quantstamp.com/full/alpha-homora-v-2) | Dangerous divide before multiply operations | Jan 2021
[Mimo Defi](https://certificate.quantstamp.com/full/ten-x-titan) | Lack of return value check | Jan 2021
[OriginTrail](https://certificate.quantstamp.com/full/origin-trail-starfleet-staking) | Lack of return value check | Feb 2021
charmfinance | Lack of return value check | Mar 2021
[VoyagerToken](https://certificate.quantstamp.com/full/voyager-token) | Lack of return value check | Apr 2021
holdmybeer | Reentrancies | Jun 2021

## Slither Rekt
The following lists security incidents that could have been prevented using Slither.

Project | Vulnerability | Value loss | Date
---|---|---|---
Dforce | [Reentrancy](https://peckshield.medium.com/uniswap-lendf-me-hacks-root-cause-and-loss-analysis-50f3263dcc09) | $25m (recovered) | Apr 2020
Lendf.me | [Incorrect self-transfer](https://bzx.network/blog/incident) ([slither-prop](../../../../40-tooling/archives/blockchain-tools/slither)) | $8m | Sep 2020
Akropolis | [Reentrancy](https://blog.peckshield.com/2020/11/13/akropolis/) | $2m | Nov 2020
OUSD | [Reentrancy](https://blog.originprotocol.com/urgent-ousd-has-hacked-and-there-has-been-a-loss-of-funds-7b8c4a7d534c?gi=fcb8badacf40) | $7m | Nov 2020
Furucombo | [Arbitrary delegatecall](https://medium.com/furucombo/furucombo-post-mortem-march-2021-ad19afd415e) | $15m | Mar 2021
ForceDAO | [Lack of return value check](https://blog.forcedao.com/xforce-exploit-post-mortem-7fa9dcba2ac3) | $10m ($9.6m recovered) | Apr 2021
