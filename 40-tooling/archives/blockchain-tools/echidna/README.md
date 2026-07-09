# Echidna: A Fast Smart Contract Fuzzer <a href="https://raw.githubusercontent.com/crytic/echidna/master/echidna.png"><img src="https://raw.githubusercontent.com/crytic/echidna/master/echidna.png" width="75"/></a>

![Build Status](../../../../40-tooling/archives/blockchain-tools/echidna)

Echidna is a weird creature that eats bugs and is highly electrosensitive (with apologies to Jacob Stanley)

More seriously, Echidna is a Haskell program designed for fuzzing/property-based testing of Ethereum smart contracts. It uses sophisticated grammar-based fuzzing campaigns based on a [contract ABI](https://docs.soliditylang.org/en/develop/abi-spec.html) to falsify user-defined predicates or [Solidity assertions](https://docs.soliditylang.org/en/develop/control-structures.html#error-handling-assert-require-revert-and-exceptions). We designed Echidna with modularity in mind, so it can be easily extended to include new mutations or test specific contracts in specific cases.

## Features

* Generates inputs tailored to your actual code
* Optional corpus collection, mutation and coverage guidance to find deeper bugs
* Powered by [Slither](../../../../40-tooling/archives/blockchain-tools/slither) to extract useful information before the fuzzing campaign
* Source code integration to identify which lines are covered after the fuzzing campaign
* Interactive terminal UI, text-only or JSON output
* Automatic test case minimization for quick triage
* Seamless integration into the development workflow

.. and [a beautiful high-resolution handcrafted logo](https://raw.githubusercontent.com/crytic/echidna/master/echidna.png).

<a href="https://i.imgur.com/saFWti4.png"><img src="https://i.imgur.com/saFWti4.png" width="650"/></a>

## Usage

### Executing the test runner

The core Echidna functionality is an executable called `echidna`, which takes a contract and a list
of invariants (properties that should always remain true) as input. For each invariant, it generates
random sequences of calls to the contract and checks if the invariant holds. If it can find some way
to falsify the invariant, it prints the call sequence that does so. If it can't, you have some
assurance the contract is safe.

### Writing invariants

Invariants are expressed as Solidity functions with names that begin with `echidna_`, have no arguments, and return a boolean. For example, if you have some `balance` variable that should never go below `20`, you can write an extra function in your contract like this one:

```solidity
function echidna_check_balance() public returns (bool) {
    return(balance >= 20);
}
```

To check these invariants, run:

```sh
$ echidna myContract.sol
```

An example contract with tests can be found [tests/solidity/basic/flags.sol](tests/solidity/basic/flags.sol). To run it, you should execute:

```sh
$ echidna tests/solidity/basic/flags.sol
```

Echidna should find a call sequence that falsifies `echidna_sometimesfalse` and should be unable to find a falsifying input for `echidna_alwaystrue`.

### Testing modes

The example above uses the default **property** mode, but Echidna supports several testing modes, configured via `testMode` in the config file or `--test-mode` on the CLI:

* **`property`** (default): Test `echidna_`-prefixed functions that return `bool`.
* **`assertion`**: Detect assertion failures from `assert()` and Foundry's `assertX` helpers (`assertTrue`, `assertEq`, etc.).
* **`foundry`**: Run Foundry-style `test`-prefixed unit tests and `invariant_`-prefixed stateful invariants.
* **`overflow`**: Detect integer over/underflows (Solidity >= 0.8.0).
* **`optimization`**: Maximize the return value of `echidna_`-prefixed functions that return `int256` (uses the same configurable prefix as property mode).
* **`exploration`**: Collect coverage without checking properties.

### Collecting and visualizing coverage

After finishing a campaign, Echidna can save a coverage maximizing **corpus** in a special directory specified with the `corpusDir` config option. This directory will contain two entries: (1) a directory named `coverage` with JSON files that can be replayed by Echidna and (2) a plain-text file named `covered.txt`, a copy of the source code with coverage annotations.

If you run `tests/solidity/basic/flags.sol` example, Echidna will save a few files serialized transactions in the `coverage` directory and a `covered.$(date +%s).txt` file with the following lines:

```text
*r  |  function set0(int val) public returns (bool){
*   |    if (val % 100 == 0)
*   |      flag0 = false;
  }

*r  |  function set1(int val) public returns (bool){
*   |    if (val % 10 == 0 && !flag0)
*   |      flag1 = false;
  }
```

Our tool signals each execution trace in the corpus with the following "line marker":

* `*` if an execution ended with a STOP
* `r` if an execution ended with a REVERT
* `o` if an execution ended with an out-of-gas error
* `e` if an execution ended with any other error (zero division, assertion failure, etc)

### Support for smart contract build systems

Echidna can test contracts compiled with different smart contract build systems, including [Foundry](https://book.getfoundry.sh/), [Hardhat](https://hardhat.org/), and [Truffle](https://archive.trufflesuite.com/), using crytic-compile. To invoke Echidna with the current compilation framework, use `echidna .`.

On top of that, Echidna supports two modes of testing complex contracts. Firstly, one can [take advantage of existing network state](https://secure-contracts.com/program-analysis/echidna/advanced/state-network-forking.html) and use that as the base state for Echidna. Secondly, Echidna can call into any contract with a known ABI by passing in the corresponding Solidity source in the CLI. Use `allContracts: true` in your config to turn this on.

### Crash course on Echidna

Our Building Secure Smart Contracts repository contains a crash course on Echidna, including examples, lessons and exercises.

### Using Echidna in a GitHub Actions workflow

There is an Echidna action which can be used to run `echidna` as part of a
GitHub Actions workflow. Please refer to the
crytic/echidna-action repository for
usage instructions and examples.

### Configuration options

Echidna's CLI can be used to choose the contract to test and load a
configuration file.

```sh
$ echidna contract.sol --contract TEST --config config.yaml
```

The configuration file allows users to choose EVM and test generation
parameters. An example of a complete and annotated config file with the default
options can be found at
[tests/solidity/basic/default.yaml](tests/solidity/basic/default.yaml).
See the [documentation](https://secure-contracts.com/program-analysis/echidna/configuration.html)
for more detailed information on the available configuration options.

Echidna supports three different output drivers. There is the default `text`
driver, a `json` driver, and a `none` driver, which should suppress all
`stdout` output. The JSON driver reports the overall campaign as follows.

```
Campaign = {
  "success"      : bool,
  "error"        : string?,
  "tests"        : [Test],
  "seed"         : number,
  "coverage"     : Coverage
}
Test = {
  "contract"     : string,
  "name"         : string,
  "status"       : string,
  "error"        : string?,
  "testType"     : string,
  "transactions" : [Transaction]?
}
Transaction = {
  "contract"     : string,
  "function"     : string,
  "arguments"    : [string]?,
  "gas"          : number,
  "gasprice"     : number
}
```

`Coverage` is a dict describing certain coverage-increasing calls. These interfaces are
subject to change to be slightly more user-friendly at a later date. `testType`
will be one of `property`, `assertion`, `optimization`, `exploration`, or `call`,
and `status` always takes on either `fuzzing`, `shrinking`, `solved`, `passed`, or `error`.

### Debugging Performance Problems

One way to diagnose Echidna's performance issues is to run `echidna` with profiling on.
To run Echidna with basic profiling, add `+RTS -p -s` to your original `echidna` command:

```sh
$ nix develop # alternatively nix-shell
$ cabal --enable-profiling run echidna -- ... +RTS -p -s
$ less echidna.prof
```

This produces a report file (`echidna.prof`), that shows which functions take up the most CPU and memory usage.

If the basic profiling doesn't help, you can use more [advanced profiling techniques](https://haskell.foundation/hs-opt-handbook.github.io/src/Measurement_Observation/Haskell_Profiling/eventlog.html).

Common causes for performance issues that we observed:

- Costly functions called in hot paths
- Lazy data constructors that accumulate thunks
- Inefficient data structures used in hot paths

Checking for these is a good place to start. If you suspect some computation is too lazy and
leaks memory, you can use `force` from `Control.DeepSeq` to make sure it gets evaluated.

## Limitations and known issues

EVM emulation and testing are hard. Echidna has some limitations in the latest release. Some of
these are inherited from hevm while some are results from
design/performance decisions or simply bugs in our code. We list them here including their
corresponding issue and the status ("wont fix", "on hold", "in review", "fixed"). Issues that are
"fixed" are expected to be included in the next Echidna release.

| Description | Issue | Status |
| :---        | :---: | :---:  |
| Vyper support is limited | [#652](../../../../40-tooling/archives/blockchain-tools/echidna) | *wont fix* |
| Limited library support for testing | [#651](../../../../40-tooling/archives/blockchain-tools/echidna) | *wont fix* |

## Installation

### Precompiled binaries

Before starting, make sure Slither is [installed](../../../../40-tooling/archives/blockchain-tools/slither) (`pip3 install slither-analyzer --user`).
If you want to quickly test Echidna in Linux or MacOS, we provide statically linked Linux binaries built on Ubuntu and mostly static MacOS binaries on our [releases page](../../../../40-tooling/archives/blockchain-tools/echidna). You can also grab the same type of binaries from our [CI pipeline](../../../../40-tooling/archives/blockchain-tools/echidna), just click the commit to find binaries for Linux or MacOS.

### Homebrew (macOS / Linux)

If you have Homebrew installed on your Mac or Linux machine, you can install Echidna and all of its dependencies (Slither, crytic-compile) by running `brew install echidna`.

You can also compile and install the latest `master` branch code by running `brew install --HEAD echidna`

You can get further information in the [`echidna` Homebrew Formula](https://formulae.brew.sh/formula/echidna) page. The formula itself is maintained as part of the homebrew-core repository

### Docker container

If you prefer to use a pre-built Docker container, check out our [docker
package](https://github.com/orgs/crytic/packages?repo_name=echidna), which is
auto-built via GitHub Actions. The `echidna` container is based on
`ubuntu:noble` and it is meant to be a small yet flexible enough image to use
Echidna on. It provides a pre-built version of `echidna`, as well as
`slither`, `crytic-compile`, `solc-select`, `nvm`, and `foundry` (including
`forge`, `cast`, `anvil`, and `chisel`) under 200 MB.

Note that the container images currently only build on x86 systems. Running them
on ARM devices, such as Mac M1 systems, is not recommended due to the performance
loss incurred by the CPU emulation.

Different tags are available for the Docker container image:

| Tag           | Build in tag
|---------------|-------------
| `vx.y.z`      | Build corresponding to release `vx.y.z`
| `latest`      | Latest Echidna tagged release.
| `edge`        | Most recent commit on the default branch.
| `testing-foo` | Testing build based on the `foo` branch.

To run the container with the latest Echidna version interactively, you can use
something like the following command. It will map the current directory as
`/src` inside the container, and give you a shell where you can use
`echidna`:

```sh
$ docker run --rm -it -v "$(pwd)":/src ghcr.io/crytic/echidna/echidna
```

Otherwise, if you want to locally build the latest version of Echidna, we
recommend using Docker. From within a clone of this repository, run the
following command to build the Docker container image:

```sh
$ docker build -t echidna -f docker/Dockerfile --target final-ubuntu .
```

Then, you can run the `echidna` image locally. For example, to install solc
0.5.7 and check `tests/solidity/basic/flags.sol`, you can run:

```sh
$ docker run -it -v "$(pwd)":/src echidna bash -c "solc-select install 0.5.7 && solc-select use 0.5.7 && echidna /src/tests/solidity/basic/flags.sol"
```

The Docker image also includes Foundry tools for comprehensive smart contract development and testing. You can use `forge`, `cast`, `anvil`, and `chisel` directly in the container:

```sh
# Run an interactive shell with Foundry tools available
$ docker run -it -v "$(pwd)":/src echidna bash

# Inside the container, you can use Foundry commands:
$ forge --version
$ cast --version
$ anvil --version
$ chisel --version

# Example: Initialize a new Foundry project
$ forge init my-project
$ cd my-project
$ forge build
$ forge test
```

### Building using Stack

If you'd prefer to build from source, use [Stack](https://docs.haskellstack.org/en/stable/). `stack install` should build and compile `echidna` in `~/.local/bin`. You will need to link against libreadline and libsecp256k1 (built with recovery enabled), which should be installed with the package manager of your choosing. You also need to install the latest release of libff. Refer to our [CI tests](.github/scripts/install-libff.sh) for guidance.

Some Linux distributions do not ship static libraries for certain things that Haskell needs, e.g. Arch Linux, which will cause `stack build` to fail with linking errors because we use the `-static` flag. In that case, use `--flag echidna:-static` to produce a dynamically linked binary.

If you're getting errors building related to linking, try tinkering with `--extra-include-dirs` and `--extra-lib-dirs`.

### Building using Nix (works natively on Apple M1 systems)

[Nix users](https://nixos.org/download/) can install the latest Echidna with:

```sh
$ nix-env -i -f chidna/tarball/master
```

With flakes enabled, you can run Echidna straight from this repo:
```sh
$ nix run github:crytic/echidna # master
$ nix run github:crytic/echidna/v2.1.1 # specific ref (tag/branch/commit)
```

To build a standalone release for non-Nix macOS systems, the following will
build Echidna in a mostly static binary. This can also be used on Linux systems
to produce a fully static binary.

```sh
$ nix build .#echidna-redistributable
```

Nix will automatically install all the dependencies required for development
including `crytic-compile` and `solc`. A quick way to start developing Echidna:

```sh
$ git clone chidna
$ cd echidna
$ nix develop # alternatively nix-shell
[nix-shell]$ cabal run echidna
[nix-shell]$ cabal run tests
[nix-shell]$ cabal new-repl
```

## Public use of Echidna

### Property testing suites

This is a partial list of smart contracts projects that use Echidna for testing:

* Curvance
* Primitive
* [Uniswap-v3](https://github.com/search?q=org%3AUniswap+echidna&type=commits)
* Balancer
* MakerDAO vest
* Optimism DAI Bridge
* WETH10
* Yield
* Convexity Protocol
* Aragon Staking
* Centre Token
* Tokencard
* Minimalist USD Stablecoin

### Security reviews

The following shows public security reviews that used Echidna to uncover vulnerabilities

- Advanced Blockchain
- Amp
- Ampleforth
- Atlendis
- Balancer
- Basis
- Dai
- Frax
- Liquity
- LooksRare
- Maple
- Optimism
- Opyn
- Origin Dollar
- Origin
- Paxos
- Primitive
- RocketPool
- Seaport
- Set Protocol
- Shell protocol
- Sherlock
- Pegasys Pantheon
- TokenCard
- Uniswap
- Yearn
- Yield
- 88mph
- 0x

### Trophies

The following security vulnerabilities were found by Echidna. If you found a security vulnerability using our tool, please submit a PR with the relevant information.

| Project | Vulnerability | Date |
|--|--|--|
0x Protocol | If an order cannot be filled, then it cannot be canceled | Oct 2019
0x Protocol | If an order can be partially filled with zero, then it can be partially filled with one token | Oct 2019
0x Protocol | The cobbdouglas function does not revert when valid input parameters are used | Oct 2019
Balancer Core | An attacker cannot steal assets from a public pool | Jan 2020
Balancer Core | An attacker cannot generate free pool tokens with joinPool | Jan 2020
Balancer Core | Calling joinPool-exitPool does not lead to free pool tokens | Jan 2020
Balancer Core |  Calling exitswapExternAmountOut does not lead to free assets | Jan 2020
Liquity Dollar | Closing troves require to hold the full amount of LUSD minted | Dec 2020
Liquity Dollar | Troves can be improperly removed | Dec 2020
Liquity Dollar | Initial redeem can revert unexpectedly | Dec 2020
Liquity Dollar | Redeem without redemptions might still return success | Dec 2020
Origin Dollar | Users are allowed to transfer more tokens that they have | Nov 2020
Origin Dollar | User balances can be larger than total supply | Nov 2020
Yield Protocol | Arithmetic computation for buying and selling tokens is imprecise | Aug 2020

### Research

We can also use Echidna to reproduce research examples from smart contract fuzzing papers to show how quickly it can find the solution. All of these can be solved, in a few seconds to one or two minutes on a laptop computer.

| Source | Code
|--|--
[Using automatic analysis tools with MakerDAO contracts](https://forum.openzeppelin.com/t/using-automatic-analysis-tools-with-makerdao-contracts/1021) | [SimpleDSChief](../../../../40-tooling/archives/blockchain-tools/echidna)
Integer precision bug in Sigma Prime | [VerifyFunWithNumbers](../../../../40-tooling/archives/blockchain-tools/echidna)
[Learning to Fuzz from Symbolic Execution with Application to Smart Contracts](https://files.sri.inf.ethz.ch/website/papers/ccs19-ilf.pdf) | [Crowdsale](../../../../40-tooling/archives/blockchain-tools/echidna)
[Harvey: A Greybox Fuzzer for Smart Contracts](https://arxiv.org/abs/1905.06944) | [Foo](../../../../40-tooling/archives/blockchain-tools/echidna), [Baz](../../../../40-tooling/archives/blockchain-tools/echidna)

### Academic Publications

| Paper Title | Venue | Publication Date |
| --- | --- | --- |
| [echidna-parade: Diverse multicore smart contract fuzzing](https://agroce.github.io/issta21.pdf) | [ISSTA 2021](https://conf.researchr.org/home/issta-2021) | July 2021 |
| [Echidna: Effective, usable, and fast fuzzing for smart contracts](https://agroce.github.io/issta20.pdf) | [ISSTA 2020](https://conf.researchr.org/home/issta-2020) | July 2020 |
| Echidna: A Practical Smart Contract Fuzzer | [FC 2020](https://fc20.ifca.ai/program.html) | Feb 2020 |

If you are using Echidna for academic work, consider applying to the [Crytic $10k Research Prize](https://blog.trailofbits.com/2019/11/13/announcing-the-crytic-10k-research-prize/).

## Getting help

Feel free to stop by our #ethereum slack channel in [Empire Hacking](https://slack.empirehacking.nyc/) for help using or extending Echidna.

* Get started by reviewing these simple [Echidna invariants](tests/solidity/basic/flags.sol)

* Considering [emailing](mailto:opensource@trailofbits.com) the Echidna development team directly for more detailed questions

## License

Echidna is licensed and distributed under the [AGPLv3 license](../../../../40-tooling/archives/blockchain-tools/echidna).
