# [Slither, the smart contract static analyzer](https://crytic.github.io/slither/slither.html)

<img src="https://raw.githubusercontent.com/crytic/slither/master/logo.png" alt="Slither Static Analysis Framework Logo" width="500" />

[![Build Status](https://img.shields.io/github/actions/workflow/status/crytic/slither/ci.yml?branch=master)](https://github.com/crytic/slither/actions?query=workflow%3ACI)
![PyPI](https://img.shields.io/pypi/v/slither-analyzer?logo=python&logoColor=white&label=slither-analyzer)
[![Slither - Read the Docs](https://img.shields.io/badge/Slither-Read_the_Docs-2ea44f)](https://crytic.github.io/slither/slither.html)
[![Slither - Wiki](https://img.shields.io/badge/Slither-Wiki-2ea44f)](https://github.com/crytic/slither/wiki/SlithIR)

> Join the Empire Hacking Slack
>
> [![Slack Status](https://slack.empirehacking.nyc/badge.svg)](https://slack.empirehacking.nyc/)
> > _- Discussions and Support_

**Slither** is a Solidity & Vyper static analysis framework written in Python3. It runs a suite of vulnerability detectors, prints visual information about contract details, and provides an API to easily write custom analyses. Slither enables developers to find vulnerabilities, enhance their code comprehension, and quickly prototype custom analyses.

* [Features](#features)
* [Usage](#usage)
* [How to install](#how-to-install)
  * [Using uv (Recommended)](#using-uv-recommended)
  * [Using Pip](#using-pip)
  * [Using Git](#using-git-development)
  * [Using Docker](#using-docker)
  * [Integration](#integration)
* [Detectors](#detectors)
* [Printers](#printers)
  * [Quick Review Printers](#quick-review-printers)
  * [In-Depth Review Printers](#in-depth-review-printers)
* [Tools](#tools)
* [API Documentation](#api-documentation)
* [Getting Help](#getting-help)
* [FAQ](#faq)
* [License](#license)
* [Publications](#publications)
  * [Trail of Bits publication](#trail-of-bits-publication)
  * [External publications](#external-publications)

## Features

* Detects vulnerable Solidity code with low false positives (see the list of [trophies](./trophies.md))
* Identifies where the error condition occurs in the source code
* Easily integrates into continuous integration and Hardhat/Foundry builds
* Built-in 'printers' quickly report crucial contract information
* Detector API to write custom analyses in Python
* Ability to analyze contracts written with Solidity >= 0.4
* Intermediate representation ([SlithIR](../../../../40-tooling/archives/blockchain-tools/slither)) enables simple, high-precision analyses
* Correctly parses 99.9% of all public Solidity code
* Average execution time of less than 1 second per contract
* Integrates with Github's code scanning in [CI](https://github.com/marketplace/actions/slither-action)
* Support for Vyper smart contracts

## Usage

Run Slither on a Hardhat/Foundry/Dapp/Brownie application:

```console
slither .
```

This is the preferred option if your project has dependencies as Slither relies on the underlying compilation framework to compile source code.

However, you can run Slither on a single file that does not import dependencies:

```console
slither tests/uninitialized.sol
```

## How to install

> **Note**
> Slither requires Python 3.10+.
If you're **not** going to use one of the supported compilation frameworks, you need solc, the Solidity compiler; we recommend using solc-select to conveniently switch between solc versions.

### Using uv (Recommended)

uv is a fast Python package manager that's 10-100x faster than pip.

```console
# Install uv if you haven't already
curl -LsSf https://astral.sh/uv/install.sh | sh

# Install slither as a tool
uv tool install slither-analyzer

# Or run slither without installation
uvx --from slither-analyzer slither <target>
```

To upgrade:

```console
uv tool upgrade slither-analyzer
```

### Using Pip

```console
python3 -m pip install slither-analyzer
```

To upgrade:

```console
python3 -m pip install --upgrade slither-analyzer
```

### Using Brew

```console
brew install slither-analyzer
```

### Using Git (Development)

```bash
git clone lither.git && cd slither

# Install as editable for development
uv tool install -e .

# Or use uv run for testing without installation
uv run slither <target>
```

The `-e` flag installs in editable mode, meaning changes to the source code are immediately reflected without reinstalling.

### Using Docker

Use the `eth-security-toolbox` docker image. It includes all of our security tools and every major version of Solidity in a single image. `/home/share` will be mounted to `/share` in the container.

```bash
docker pull trailofbits/eth-security-toolbox
```

To share a directory in the container:

```bash
docker run -it -v /home/share:/share trailofbits/eth-security-toolbox
```

### Integration

* For GitHub action integration, use [slither-action](https://github.com/marketplace/actions/slither-action).
* For pre-commit integration, use (replace `$GIT_TAG` with real tag)
  ```YAML
  - repo: lither
    rev: $GIT_TAG
    hooks:
      - id: slither
  ```
* To generate a Markdown report, use `slither [target] --checklist`.
* To generate a Markdown with GitHub source code highlighting, use `slither [target] --checklist --markdown-root EPO/blob/COMMIT/` (replace `ORG`, `REPO`, `COMMIT`)

## Detectors

Num | Detector | What it Detects | Impact | Confidence
--- | --- | --- | --- | ---
1 | `abiencoderv2-array` | [Storage abiencoderv2 array](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
2 | `arbitrary-send-erc20` | [transferFrom uses arbitrary `from`](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
3 | `array-by-reference` | [Modifying storage array by value](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
4 | `encode-packed-collision` | [ABI encodePacked Collision](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
5 | `incorrect-shift` | [The order of parameters in a shift instruction is incorrect.](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
6 | `multiple-constructors` | [Multiple constructor schemes](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
7 | `name-reused` | [Contract's name reused](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
8 | `protected-vars` | [Detected unprotected variables](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
9 | `public-mappings-nested` | [Public mappings with nested variables](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
10 | `rtlo` | [Right-To-Left-Override control character is used](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
11 | `shadowing-state` | [State variables shadowing](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
12 | `suicidal` | [Functions allowing anyone to destruct the contract](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
13 | `uninitialized-state` | [Uninitialized state variables](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
14 | `uninitialized-storage` | [Uninitialized storage variables](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
15 | `unprotected-upgrade` | [Unprotected upgradeable contract](../../../../40-tooling/archives/blockchain-tools/slither) | High | High
16 | `arbitrary-send-erc20-permit` | [transferFrom uses arbitrary from with permit](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
17 | `arbitrary-send-eth` | [Functions that send Ether to arbitrary destinations](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
18 | `controlled-array-length` | [Tainted array length assignment](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
19 | `controlled-delegatecall` | [Controlled delegatecall destination](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
20 | `delegatecall-loop` | [Payable functions using `delegatecall` inside a loop](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
21 | `incorrect-exp` | [Incorrect exponentiation](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
22 | `incorrect-return` | [If a `return` is incorrectly used in assembly mode.](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
23 | `msg-value-loop` | [msg.value inside a loop](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
24 | `reentrancy-eth` | [Reentrancy vulnerabilities (theft of ethers)](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
25 | `reentrancy-balance` | [Reentrancy vulnerabilities leading to outdated balance checks](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
26 | `return-leave` | [If a `return` is used instead of a `leave`.](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
27 | `storage-array` | [Signed storage integer array compiler bug](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
28 | `unchecked-transfer` | [Unchecked tokens transfer](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
29 | `weak-prng` | [Weak PRNG](../../../../40-tooling/archives/blockchain-tools/slither) | High | Medium
30 | `domain-separator-collision` | [Detects ERC20 tokens that have a function whose signature collides with EIP-2612's DOMAIN_SEPARATOR()](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
31 | `enum-conversion` | [Detect dangerous enum conversion](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
32 | `erc20-interface` | [Incorrect ERC20 interfaces](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
33 | `erc721-interface` | [Incorrect ERC721 interfaces](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
34 | `incorrect-equality` | [Dangerous strict equalities](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
35 | `locked-ether` | [Contracts that lock ether](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
36 | `mapping-deletion` | [Deletion on mapping containing a structure](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
37 | `pyth-deprecated-functions` | [Detect Pyth deprecated functions](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
38 | `pyth-unchecked-confidence` | [Detect when the confidence level of a Pyth price is not checked](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
39 | `pyth-unchecked-publishtime` | [Detect when the publishTime of a Pyth price is not checked](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
40 | `shadowing-abstract` | [State variables shadowing from abstract contracts](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
41 | `tautological-compare` | [Comparing a variable to itself always returns true or false, depending on comparison](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
42 | `tautology` | [Tautology or contradiction](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
43 | `write-after-write` | [Unused write](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | High
44 | `boolean-cst` | [Misuse of Boolean constant](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
45 | `chronicle-unchecked-price` | [Detect when Chronicle price is not checked.](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
46 | `constant-function-asm` | [Constant functions using assembly code](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
47 | `constant-function-state` | [Constant functions changing the state](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
48 | `divide-before-multiply` | [Imprecise arithmetic operations order](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
49 | `gelato-unprotected-randomness` | [Call to `_requestRandomness` within an unprotected function](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
50 | `out-of-order-retryable` | [Out-of-order retryable transactions](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
51 | `reentrancy-no-eth` | [Reentrancy vulnerabilities (no theft of ethers)](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
52 | `reused-constructor` | [Reused base constructor](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
53 | `tx-origin` | [Dangerous usage of `tx.origin`](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
54 | `unchecked-lowlevel` | [Unchecked low-level calls](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
55 | `unchecked-send` | [Unchecked send](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
56 | `uninitialized-local` | [Uninitialized local variables](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
57 | `unused-return` | [Unused return values](../../../../40-tooling/archives/blockchain-tools/slither) | Medium | Medium
58 | `chainlink-feed-registry` | [Detect when chainlink feed registry is used](../../../../40-tooling/archives/blockchain-tools/slither) | Low | High
59 | `incorrect-modifier` | [Modifiers that can return the default value](../../../../40-tooling/archives/blockchain-tools/slither) | Low | High
60 | `optimism-deprecation` | [Detect when deprecated Optimism predeploy or function is used.](../../../../40-tooling/archives/blockchain-tools/slither) | Low | High
61 | `shadowing-builtin` | [Built-in symbol shadowing](../../../../40-tooling/archives/blockchain-tools/slither) | Low | High
62 | `shadowing-local` | [Local variables shadowing](../../../../40-tooling/archives/blockchain-tools/slither) | Low | High
63 | `uninitialized-fptr-cst` | [Uninitialized function pointer calls in constructors](../../../../40-tooling/archives/blockchain-tools/slither) | Low | High
64 | `variable-scope` | [Local variables used prior their declaration](../../../../40-tooling/archives/blockchain-tools/slither) | Low | High
65 | `void-cst` | [Constructor called not implemented](../../../../40-tooling/archives/blockchain-tools/slither) | Low | High
66 | `calls-loop` | [Multiple calls in a loop](../../../../40-tooling/archives/blockchain-tools/slither) | Low | Medium
67 | `events-access` | [Missing Events Access Control](../../../../40-tooling/archives/blockchain-tools/slither) | Low | Medium
68 | `events-maths` | [Missing Events Arithmetic](../../../../40-tooling/archives/blockchain-tools/slither) | Low | Medium
69 | `incorrect-unary` | [Dangerous unary expressions](../../../../40-tooling/archives/blockchain-tools/slither) | Low | Medium
70 | `missing-zero-check` | [Missing Zero Address Validation](../../../../40-tooling/archives/blockchain-tools/slither) | Low | Medium
71 | `reentrancy-benign` | [Benign reentrancy vulnerabilities](../../../../40-tooling/archives/blockchain-tools/slither) | Low | Medium
72 | `reentrancy-events` | [Reentrancy vulnerabilities leading to out-of-order Events](../../../../40-tooling/archives/blockchain-tools/slither) | Low | Medium
73 | `return-bomb` | [A low level callee may consume all callers gas unexpectedly.](../../../../40-tooling/archives/blockchain-tools/slither) | Low | Medium
74 | `timestamp` | [Dangerous usage of `block.timestamp`](../../../../40-tooling/archives/blockchain-tools/slither) | Low | Medium
75 | `assembly` | [Assembly usage](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
76 | `assert-state-change` | [Assert state change](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
77 | `boolean-equal` | [Comparison to boolean constant](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
78 | `cyclomatic-complexity` | [Detects functions with high (> 11) cyclomatic complexity](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
79 | `deprecated-standards` | [Deprecated Solidity Standards](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
80 | `erc20-indexed` | [Un-indexed ERC20 event parameters](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
81 | `function-init-state` | [Function initializing state variables](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
82 | `incorrect-using-for` | [Detects using-for statement usage when no function from a given library matches a given type](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
83 | `low-level-calls` | [Low level calls](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
84 | `missing-inheritance` | [Missing inheritance](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
85 | `naming-convention` | [Conformity to Solidity naming conventions](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
86 | `pragma` | [If different pragma directives are used](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
87 | `redundant-statements` | [Redundant statements](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
88 | `solc-version` | [Incorrect Solidity version](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
89 | `unimplemented-functions` | [Unimplemented functions](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
90 | `unindexed-event-address` | [Events with address parameters but no indexed parameters](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
91 | `unused-state` | [Unused state variables](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | High
92 | `costly-loop` | [Costly operations in a loop](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | Medium
93 | `dead-code` | [Functions that are not used](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | Medium
94 | `reentrancy-unlimited-gas` | [Reentrancy vulnerabilities through send and transfer](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | Medium
95 | `too-many-digits` | [Conformance to numeric notation best practices](../../../../40-tooling/archives/blockchain-tools/slither) | Informational | Medium
96 | `cache-array-length` | [Detects `for` loops that use `length` member of some storage array in their loop condition and don't modify it.](../../../../40-tooling/archives/blockchain-tools/slither) | Optimization | High
97 | `constable-states` | [State variables that could be declared constant](../../../../40-tooling/archives/blockchain-tools/slither) | Optimization | High
98 | `external-function` | [Public function that could be declared external](../../../../40-tooling/archives/blockchain-tools/slither) | Optimization | High
99 | `immutable-states` | [State variables that could be declared immutable](../../../../40-tooling/archives/blockchain-tools/slither) | Optimization | High
100 | `var-read-using-this` | [Contract reads its own variable using `this`](../../../../40-tooling/archives/blockchain-tools/slither) | Optimization | High

For more information, see

* The [Detector Documentation](../../../../40-tooling/archives/blockchain-tools/slither) for details on each detector
* The [Detection Selection](../../../../40-tooling/archives/blockchain-tools/slither) to run only selected detectors. By default, all the detectors are run.
* The [Triage Mode](../../../../40-tooling/archives/blockchain-tools/slither) to filter individual results

## Printers

### Quick Review Printers

* `human-summary`: Print a human-readable summary of the contracts
* `inheritance-graph`: Export the inheritance graph of each contract to a dot file
* `contract-summary`: Print a summary of the contracts
* `loc`: Count the total number lines of code (LOC), source lines of code (SLOC), and comment lines of code (CLOC) found in source files (SRC), dependencies (DEP), and test files (TEST).
* `entry-points`: Print all the state-changing entry point functions and their variables of the contracts

### In-Depth Review Printers

* `call-graph`: [Export the call-graph of the contracts to a dot file](../../../../40-tooling/archives/blockchain-tools/slither)
* `cfg`: [Export the CFG of each functions](../../../../40-tooling/archives/blockchain-tools/slither)
* `function-summary`: [Print a summary of the functions](../../../../40-tooling/archives/blockchain-tools/slither)
* `vars-and-auth`: [Print the state variables written and the authorization of the functions](../../../../40-tooling/archives/blockchain-tools/slither)
* `not-pausable`: [Print functions that do not use `whenNotPaused` modifier](../../../../40-tooling/archives/blockchain-tools/slither).

To run a printer, use `--print` and a comma-separated list of printers.

See the [Printer documentation](../../../../40-tooling/archives/blockchain-tools/slither) for the complete lists.

## Tools

* `slither-check-upgradeability`: [Review `delegatecall`-based upgradeability](./docs/src/tools/Upgradeability-Checks.md)
* `slither-prop`: [Automatic unit test and property generation](./docs/src/tools/Property-generation.md)
* `slither-flat`: [Flatten a codebase](./docs/src/tools/Contract-Flattening.md)
* `slither-check-erc`: [Check the ERC's conformance](./docs/src/tools/ERC-Conformance.md)
* `slither-read-storage`: [Read storage values from contracts](./docs/src/tools/ReadStorage.md)
* `slither-interface`: [Generate an interface for a contract](./docs/src/tools/Interface.md)

See the [Tool documentation](./docs/src/tools/README.md) for additional tools.

[Contact us](https://www.trailofbits.com/contact/) to get help on building custom tools.

## API Documentation

Documentation on Slither's internals is available [here](https://crytic.github.io/slither/slither.html).

## Getting Help

Feel free to stop by our [Slack channel](https://empireslacking.herokuapp.com) (#ethereum) for help using or extending Slither.

* The [Printer documentation](../../../../40-tooling/archives/blockchain-tools/slither) describes the information Slither is capable of visualizing for each contract.

* The [Detector documentation](../../../../40-tooling/archives/blockchain-tools/slither) describes how to write a new vulnerability analyses.

* The [API documentation](../../../../40-tooling/archives/blockchain-tools/slither) describes the methods and objects available for custom analyses.

* The [SlithIR documentation](../../../../40-tooling/archives/blockchain-tools/slither) describes the SlithIR intermediate representation.

## FAQ

How do I exclude mocks or tests?

* View our documentation on [path filtering](../../../../40-tooling/archives/blockchain-tools/slither).

How do I fix "unknown file" or compilation issues?

* Because slither requires the solc AST, it must have all dependencies available.
If a contract has dependencies, `slither contract.sol` will fail.
Instead, use `slither .` in the parent directory of `contracts/` (you should see `contracts/` when you run `ls`).
If you have a `node_modules/` folder, it must be in the same directory as `contracts/`. To verify that this issue is related to slither,
run the compilation command for the framework you are using e.g `npx hardhat compile`. That must work successfully;
otherwise, slither's compilation engine, crytic-compile, cannot generate the AST.

## License

Slither is licensed and distributed under the AGPLv3 license. [Contact us](mailto:opensource@trailofbits.com) if you're looking for an exception to the terms.

## Publications

### Trail of Bits publication

* [Slither: A Static Analysis Framework For Smart Contracts](https://arxiv.org/abs/1908.09878), Josselin Feist, Gustavo Grieco, Alex Groce - WETSEB '19

### External publications

Title | Usage | Authors | Venue | Code
--- | --- | --- | --- | ---
[ReJection: A AST-Based Reentrancy Vulnerability Detection Method](https://www.researchgate.net/publication/339354823_ReJection_A_AST-Based_Reentrancy_Vulnerability_Detection_Method) | AST-based analysis built on top of Slither | Rui Ma, Zefeng Jian, Guangyuan Chen, Ke Ma, Yujia Chen | CTCIS 19 | -
[MPro: Combining Static and Symbolic Analysis for Scalable Testing of Smart Contract](https://arxiv.org/pdf/1911.00570.pdf) | Leverage data dependency through Slither | William Zhang, Sebastian Banescu, Leodardo Pasos, Steven Stewart, Vijay Ganesh | ISSRE 2019 | MPro
[ETHPLOIT: From Fuzzing to Efficient Exploit Generation against Smart Contracts](https://wcventure.github.io/FuzzingPaper/Paper/SANER20_ETHPLOIT.pdf) | Leverage data dependency through Slither | Qingzhao Zhang, Yizhuo Wang, Juanru Li, Siqi Ma | SANER 20 | -
[Verification of Ethereum Smart Contracts: A Model Checking Approach](http://www.ijmlc.org/vol10/977-AM0059.pdf) | Symbolic execution built on top of Slither’s CFG | Tam Bang, Hoang H Nguyen, Dung Nguyen, Toan Trieu, Tho Quan | IJMLC 20 | -
[Smart Contract Repair](https://arxiv.org/pdf/1912.05823.pdf) | Rely on Slither’s vulnerabilities detectors | Xiao Liang Yu, Omar Al-Bataineh, David Lo, Abhik Roychoudhury | TOSEM 20 | SCRepair
[Demystifying Loops in Smart Contracts](https://www.microsoft.com/en-us/research/uploads/prod/2020/08/loops_solidity__camera_ready-5f3fec3f15c69.pdf) | Leverage data dependency through Slither | Ben Mariano, Yanju Chen, Yu Feng, Shuvendu Lahiri, Isil Dillig | ASE 20 | -
[Trace-Based Dynamic Gas Estimation of Loops in Smart Contracts](https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=9268144) | Use Slither’s CFG to detect loops | Chunmiao Li, Shijie Nie, Yang Cao, Yijun Yu, Zhenjiang Hu | IEEE Open J. Comput. Soc. 1 (2020) | -
[SAILFISH: Vetting Smart Contract State-Inconsistency Bugs in Seconds](https://arxiv.org/pdf/2104.08638.pdf) | Rely on SlithIR to build a *storage dependency graph* | Priyanka Bose, Dipanjan Das, Yanju Chen, Yu Feng, Christopher Kruegel, and Giovanni Vigna | S&P 22 | Sailfish
[SolType: Refinement Types for Arithmetic Overflow in Solidity](https://arxiv.org/abs/2110.00677) | Use Slither as frontend to build refinement type system | Bryan Tan, Benjamin Mariano, Shuvendu K. Lahiri, Isil Dillig, Yu Feng | POPL 22 | -
[Do Not Rug on Me: Leveraging Machine Learning Techniques for Automated Scam Detection](https://www.mdpi.com/2227-7390/10/6/949) | Use Slither to extract tokens' features (mintable, pausable, ..) | Mazorra, Bruno, Victor Adan, and Vanesa Daza | Mathematics 10.6 (2022) | -
[MANDO: Multi-Level Heterogeneous Graph Embeddings for Fine-Grained Detection of Smart Contract Vulnerabilities](https://arxiv.org/abs/2208.13252) | Use Slither to extract the CFG and call graph | Hoang Nguyen, Nhat-Minh Nguyen, Chunyao Xie, Zahra Ahmadi, Daniel Kudendo, Thanh-Nam Doan and Lingxiao Jiang| IEEE 9th International Conference on Data Science and Advanced Analytics (DSAA, 2022) | ge-sc
[Automated Auditing of Price Gouging TOD Vulnerabilities in Smart Contracts](https://www.cs.toronto.edu/~fanl/papers/price-icbc22.pdf) | Use Slither to extract the CFG and data dependencies| Sidi Mohamed Beillahi, Eric Keilty, Keerthi Nelaturu, Andreas Veneris, and Fan Long | 2022 IEEE International Conference on Blockchain and Cryptocurrency (ICBC) | Smart-Contract-Repair
[Modeling and Enforcing Access Control Policies for Smart Contracts](https://publikationen.bibliothek.kit.edu/1000152805/151859658) | Extend Slither's data dependencies | Jan-Philipp Toberg, Jonas Schiffl, Frederik Reiche, Bernhard Beckert, Robert Heinrich, Ralf Reussner | IEEE International Conference on Decentralized Applications and Infrastructures (DAPPS), 2022  | SolidityAccessControlEnforcement
[Smart Contract Vulnerability Detection Based on Deep Learning and Multimodal Decision Fusion](https://www.mdpi.com/1424-8220/23/16/7246) | Use Slither to extract the CFG | Weichu Deng, Huanchun Wei, Teng Huang, Cong Cao, Yun Peng, and Xuan Hu | Sensors 2023, 23, 7246 | -
[Semantic-enriched Code Knowledge Graph to Reveal Unknowns in Smart Contract Code Reuse](https://www.researchgate.net/profile/Qing-Huang-26/publication/370638129_Semantic-enriched_Code_Knowledge_Graph_to_Reveal_Unknowns_in_Smart_Contract_Code_Reuse/links/645b7b8639c408339b3a54da/Semantic-Enriched-Code-Knowledge-Graph-to-Reveal-Unknowns-in-Smart-Contract-Code-Reuse.pdf) | Use Slither to extract the code features (CFG, function, parameters types, ..) | Qing Huang, Dianshu Liao, Zhenchang Xing, Zhengkang Zuo, Changjing Wang, Xin Xia | ACM Transactions on Software Engineering and Methodology, 2023 | -
[Smart Contract Parallel Execution with Fine-Grained State Accesses](https://personal.ntu.edu.sg/yi_li/files/Qi2023SCP.pdf) | Use Slither to build state access graphs | Xiaodong Qi, Jiao Jiao, Yi Li | International Conference on Distributed Computing Systems (ICDCS), 2023 | -
[Bad Apples: Understanding the Centralized Security Risks in Decentralized Ecosystems](https://diaowenrui.github.io/paper/www23-yan.pdf) | Implement an internal analysis on top of Slither | Kailun Yan , Jilian Zhang , Xiangyu Liu , Wenrui Diao , Shanqing Guo | ACM Web Conference April 2023 | -
[Identifying Vulnerabilities in Smart Contracts using Interval Analysis](https://arxiv.org/pdf/2309.13805.pdf) | Create 4 detectors on top of Slither | Ştefan-Claudiu Susan, Andrei Arusoaie | FROM 2023 | -
Storage State Analysis and Extraction of Ethereum Blockchain Smart Contracts (no PDF in open access) | Rely on Slither's CFG and AST | Maha Ayub , Tania Saleem , Muhammad Janjua , Talha Ahmad | TOSEM 2023 | SmartMuv

If you are using Slither on an academic work, consider applying to the [Crytic $10k Research Prize](https://blog.trailofbits.com/2019/11/13/announcing-the-crytic-10k-research-prize/).
