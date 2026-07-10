# :game_die: SAT-Solver, Optimization, and Belief Propagation Attacks on SHA-256

> **Original Source:** [SAT-Solver, Optimization, and Belief Propagation Attacks on SHA-256](https://infosecwriteups.com/sat-solver-optimization-and-belief-propagation-attacks-on-sha-256-33c0233440e9)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# SAT-Solver, Optimization, and Belief Propagation Attacks on SHA-256


## Four rounds of the SHA-256 hash function generate 17,806 unknown bits and 26,383 logical relationships. We can solve this in under a second.


If you track all bits and their logical relationships in 4 out of 64 rounds of the infamous SHA-256 hash function used by BitCoin, this is what it would look like. A graph with 17806 nodes, 26383 edges. We can solve it in less than a second.


*4-round SHA-256 bit relationships [image by author]*

## Description


In this post, we will attempt to reverse one-way cryptographic hash functions, with specific focus on [SHA-256](https://en.bitcoinwiki.org/wiki/SHA-256). A hash function `f` can be thought of as an operation on bits `X` to produce output bits `Y`: `f(X) = Y`. Given knowledge of `Y` and how `f` works, we want to find some bits `X'` such that `f(X') = Y`. This is commonly known as a [preimage attack](https://en.wikipedia.org/wiki/Preimage_attack). Note that `X` does not necessarily need to equal `X'`.


A successful preimage attack has serious implications for basically the entire Internet, financial community, and national defense of major governments. Hash functions are used in all kinds of domains: from BitCoin mining and transactions, to HTTPS encryption, to storage of user passwords in server databases.


I’ve spent a long time (too long!) trying to solve this “impossible” problem using a variety of methods, detailed below. As a disclaimer: I do not claim that any of these methods break the security of the full 64-round SHA-256 hash function. It’s probably still infeasible (prove me wrong!). Some methods here can solve up to 16 rounds, others can’t even solve 1 round. But the main point is to share ideas and inspire you to build on these ideas.


The corresponding Python and C++ code for this project can be found on [GitHub](https://github.com/trevphil/preimage-attacks). The article was originally posted on [trevphil.com](https://trevphil.com/posts/preimage-attacks).

## Symbolic representation of hash functions


The first thing we need in order to approach this problem is to find out how the hash function `f` operates on input bits `X` to produce output bits `Y` without making any assumptions about `X`. To this end, I coded some hash functions, including SHA-256 and some simple "test" functions, which operate on *symbolic* bit vectors. This symbolic representation allows us to track the relationship between input and output bits for all computations in the hash function, e.g. if `C = A & B`, we track the relationship that bit `C` is the result of AND-ing `A` and `B`. Ultimately after all of the computations, we will have the relationship between each bit of `Y` and each bit of `X` in the function `f(X) = Y`.


Some simplifications can be made during this process. For example, let’s say that bit `A` is a bit from the unknown input `X` and bit `B` is a *constant* in the hash algorithm equal to 0. Well then we know that `C = A & 0 = 0` so `C = 0` no matter the value of `A`. Some more simplifications for operations on single bits are listed below:


- `B = A & 1 = A`

- `B = A | 0 = A`

- `B = A | 1 = 1`

- `B = A ^ 1 = ~A`

- `B = A ^ 0 = A`

- `B = A ^ A = 0`

- `B = A & A = A | A = A`


These simplifications help to reduce the size of the symbolic representation of the hash function, since the output bit `B` is sometimes a constant or equal to the unknown input `A`. When this happens, we don't need to introduce a new unknown variable.


Furthermore, the problem can be made easier to handle by reducing all operations (XOR, OR, addition) to only using AND and NOT logic gates. I refer to NOT gates as INV (for inverse): `B = ~A`. Let's see an example where we rewrite XOR using AND and INV gates: `C = A ^ B` is equivalent to


```
X = ~(A & B)
Y = ~(A & X)
Z = ~(B & X)
C = ~(Y & Z)
```


This *does* introduce intermediate variables, but critically, the AND and INV operations can be linearized and also represented in the continuous domain, which is important mathematically. Normally in the discrete domain, we would consider each bit as a binary “ [random variable](https://en.wikipedia.org/wiki/Random_variable)” taking the value 0 or 1.


The AND operation can be represented with multiplication: `C = A & B = A * B`, and the INV operation with subtraction: `B = ~A = 1 - A`. To linearize the AND operation, we can use [the following method](https://or.stackexchange.com/questions/37/how-to-linearize-the-product-of-two-binary-variables):


```
C = A & B = A * B
Equivalent to:
C <= A
C <= B
C >= A + B - 1
```


Note that no information is lost during the INV operation (we can always recover the input from the output of INV), but there *is* information lost during AND when the output is 0. When the output is 1, we know that both inputs must have been 1. But when the output is 0, there are three possible inputs: `0 = 0 & 0 = 0 & 1 = 1 & 0`. Thus, all complexity in reversing a hash function comes from AND gates whose output is 0.

## Example


Here is a relatively simple (compared to SHA-256) “hash function” that I created as a test function. If we can predict the input bits `X` (shown in black) using the observed values of the output bits `Y` (shown in green), we're on the right track.


*Image by author*


The hash function itself looks something like this:


```
def hash(hash_input, difficulty):
n = len(hash_input)
n4 = n // 4 np.random.seed(1)
A = int.from_bytes(np.random.bytes(n // 8), 'big')
B = int.from_bytes(np.random.bytes(n // 8), 'big')
C = int.from_bytes(np.random.bytes(n // 8), 'big')
D = int.from_bytes(np.random.bytes(n // 8), 'big') mask = SymBitVec((1 << n4) - 1, size=n)
h = hash_input
for _ in range(difficulty):
a = ((h >> (n4 * 0)) & mask) ^ A
b = ((h >> (n4 * 1)) & mask) ^ B
c = ((h >> (n4 * 2)) & mask) ^ C
d = ((h >> (n4 * 3)) & mask) ^ D
a = (a | b)
b = (b & c)
c = (c ^ d)
h = a | (b << (n4 * 1)) | (c << (n4 * 2)) | (d << (n4 * 3))
return h
```


Not trivial, but still simple enough that solvers can be evaluated quickly. One thing we can do right at the beginning is a “ pre-solve” technique. Let’s say we observe a hash bit `A = 1` and we know it is related to its "parent" bit in the graph via INV: `A = ~B`. We can automatically assign `B = 0`. Similarly, for bits which are the output of AND gates with the value 1, the parent bits in the graph can be assigned the value 1. After "backpropagating" these bit values to the parents, we can "forward propagate" again, since we may have found values for inputs to logic gates whose inputs were previously unknown. The backward/forward pass can be repeated until no new bit values are discovered. This can already solve a surprising number of bits in the hash computation.

## Solving Methods


After the pre-solve operation, the directed graph of bit relationships may still have a lot of unknown bits. We could brute-force solve the graph, but there are other techniques available which are faster and more efficient. Using the latest and greatest as of November 2020, the solving methods are listed from what I believe to be most effective to least effective. Even the best methods seem to fail on the 17th round of SHA-256 (discussed below).


- [CryptoMiniSat](https://www.msoos.org/cryptominisat5/)

- [MiniSat](http://minisat.se/)

- [Gurobi MILP](https://www.gurobi.com/documentation/9.0/quickstart_mac/py_python_interface.html#section:Python)

- [Google](https://developers.google.com/optimization/mip/mip)`[ortools](https://developers.google.com/optimization/mip/mip)`[MILP](https://developers.google.com/optimization/mip/mip)

- [Google](https://developers.google.com/optimization/cp)`[ortools](https://developers.google.com/optimization/cp)`[constraint programming](https://developers.google.com/optimization/cp)

- [Cplex constraint programming](https://www.ibm.com/analytics/cplex-cp-optimizer)

- [Cplex MILP](https://www.ibm.com/support/knowledgecenter/SSSA5P_12.7.1/ilog.odms.cplex.help/CPLEX/UsrMan/topics/discr_optim/mip/01_mip_title_synopsis.html)

- Traditional optimization

- [Graduated non-convexity](https://arxiv.org/pdf/1909.08605)

- Loopy belief propagation

- Neural network


These strategies can be broken into a few general categories that I will discuss soon.


## Get Trevor Phillips’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


First, here is a log-log plot of problem size (# unknown variables) vs. runtime for a select number of solvers, as well as a linear regression on this log-log data. The problem sizes correspond to SHA-256 rounds of 1, 4, 8, 12, and 16. These solvers were run on my weak dual-core 16 GB MacBook Air, and none were allowed to run for more than 24 hours.


*Image by author*


I think it is interesting to see how the SHA-256 algorithm’s complexity increases with the number of rounds. Something happens in the 17th round that causes a major spike in complexity. My best guess is that an AND gate between bits “very far apart” in the computation is the issue. If you assign a monotonically increasing index to each bit created during the hash computation, and you look at the maximum distance between the indices of bits which are inputs to an AND gate, the maximum gap is around 126,000 bits apart up to 16 rounds. At 17 rounds, the gap increases to 197,000 bits. For a SAT solver, this could mean that it doesn’t detect an invalid variable assignment until values have been propagated a long way. For the full 64-round SHA-256, the maximum gap is 386,767.


Below, we can see that the number of INV and AND gates in the graph of bit relationships growing (approximately) linearly as the number of rounds increases. The prior factors correspond to hash input bits, so naturally they stay constant.


*Image by author*

## SAT Solvers


*Image modified from [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Tree-depth.svg)*


Satisfiability (SAT) solvers operate on boolean logic relationships to find a satisfying assignment for free boolean variables. I would put solvers like MiniSat, CryptoMiniSat, `ortools` constraint programming, and Cplex constraint programming in this category. These types of solvers generally work by assigning fixed values to free variables until there is a logical conflict, and then backtracking until the conflict is resolved and trying new variable assignments in the conflict region. This is a gross simplification though. There are a lot of tricks people have come up with to speed up the process, heuristics to pick the order of variable assignments, learning from conflicts, etc. [Here](https://www.msoos.org/minisat-faq/) is a nice website to get started learning, and [this guy](https://www.youtube.com/watch?v=d76e4hV1iJY&ab_channel=ClojureTV) gives a nice talk.


From what I can tell, this is one of the best methods for preimage attacks to date. A lot of the solvers are implemented in C or C++ so they run extremely fast, and they are heavily optimized with heuristics. People have already tried to use SAT solvers to break cryptographic hash functions, but you do eventually hit a limit on the feasible problem size. To use MiniSat or CryptoMiniSat, I converted the bit relationships to [DIMACS Conjunctive Normal Form](https://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html) (CNF). I didn’t even take advantage of CryptoMiniSat’s optimized treatment of XOR gates since everything was reduced to AND and INV gates.

## MILP


*Image from [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Branch-and-bound-polytopes.png)*


Mixed-integer linear programming (MILP) is a form of optimization where the optimization variables may be integer-valued, rather than the usual real-valued. Gurobi MILP, Cplex MILP, and `ortools` MILP fall into this category. The theory underpinning MILP solvers is honestly pretty complex (or should I say... [simplex](https://en.wikipedia.org/wiki/Simplex)). However, if you want to read more, Google terms like "linear programming relaxations," "branch and bound," or "cutting planes." A good place to start is [Gurobi's introduction to MIP](https://www.gurobi.com/resource/mip-basics/).


Solvers from the major players like Gurobi, Cplex, and [coin-or](https://www.coin-or.org/) work well (much like the SAT solvers) until 17 rounds of SHA-256. INV logic gates are encoded as equality constraints for the solver (`B = 1 — A`) and AND gates as 3 inequality constraints described previously. The optimization objective is arbitrary, but I usually maximize the sum of the unknown bit values.

## Traditional Optimization


*Image from [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Gradient_descent_method.png)*


As opposed to mixed-integer optimization, I also tried out plain-ol’ regular optimization with real-valued optimization variables. A vector `x` with N elements is optimized, which represents the value of each bit in the hash computation. To convert to boolean values, I set bit *i* to 1 if `x[i] > 0.5`, otherwise 0. Bit inversions are represented as equality constraints in the optimization, `Ax = b`, and AND gates are represented by 3 inequalities (described earlier), giving inequality constraints `Cx <= d`. Upper and lower bounds on `x` can also be added to the inequality constraints, enforcing `0 <= x <= 1`.


For an example of a bit inversion constraint, let’s say `bit_1 = ~bit_0 = 1 - bit_0`. Then we would have a row in `A` like `[1 1 0 ... 0]` and the corresponding element in the `b` vector would be `1`. Then `Ax = b` gives `bit_0 + bit_1 = 1`.


The initial guess for `x` is initialized to `0.5` except for the observed hash output bits, which are initialized to their observed values. I didn't add the observed bits to the equality constraints because [SLSQP](https://docs.scipy.org/doc/scipy/reference/optimize.minimize-slsqp.html) complains that the system is overdetermined.


This method turns out to perform poorly if the problem gets even moderately complex. Approximating boolean values by rounding real numbers doesn’t translate well into a valid solution.

## Robust Estimation and Graduated Non-Convexity


*Image from [H. Yang, P. Antonante, V. Tzoumas, and L. Carlone](https://arxiv.org/pdf/1909.08605.pdf)*


I’ve done [a fair bit of work](https://driverless.amzracing.ch/) on graph-based [SLAM](https://en.wikipedia.org/wiki/Simultaneous_localization_and_mapping) and had an idea to apply something from robust estimation techniques to solving the preimage problem. This something is called “Graduated Non-Convexity” (GNC), introduced in [this](https://arxiv.org/abs/1909.08605) paper.


In GraphSLAM, a lot of research has gone into rejecting outliers that are incorrectly added to the graph. When the graph is optimized, certain techniques like [dynamic covariance scaling](http://www2.informatik.uni-freiburg.de/~stachnis/pdf/agarwal13icra.pdf) (DCS) can help the graph optimization to ignore outliers that influence the objective function. GNC achieves a similar outcome but works by turning a non-convex optimization problem into a convex one, and then gradually *decreasing* the convexity with a hyperparameter which changes after each iteration. My idea was to apply the same thing to the preimage problem. For each AND gate, we can add “conflicting” constraints which make different assumptions about the AND gate variables (think: `0&0`, `0&1`, `1&0`, `1&1`), some of which will be incorrect. As the optimization proceeds, the robust estimation technique will reject the bad constraints and keep the good ones.


Unfortunately, much like before, this turned out to not work very well for even moderately complex problems. However, if this technique could be extended for MIP optimization, maybe we would see quite different results.

## Belief Propagation


*Image from [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Factor_Graph_representation.png)*


Belief propagation (BP) is an iterative “message passing” algorithm in which messages are passed between factors and random variables (RVs) in a factor graph. We say the algorithm has *converged* when none of the messages change by more than some small value ε.


Once the messages have converged, we can use them to perform queries on the factor graph, for example to answer the question “What is the probability that the input message bit 0 is a 1, given that I know all of the hash bits?”


What exactly is a “message”? It’s hard to explain, to be honest. It’s a bit mathematical, theoretical, and unintuitive. I would recommend [this article](http://nghiaho.com/?page_id=1366) to understand it.


A factor graph is a bipartite graph wherein one side of the graph has RVs (bits) as nodes, and the other side has all of the “factors” as nodes (AND, INV logic gates). Each factor represents a conditional probability distribution and has a “query” RV (output of the logic gate) as well as a list of “dependency” RVs (inputs to the logic gate).


For example, let `C = A & B`. Then a factor `f` may represent `P(C | A, B)`, i.e. the probability of observing `C = 0` or `C = 1`, given that we know the values of `A` and `B`.


Each factor has a table which contains the [conditional probability distribution](https://en.wikipedia.org/wiki/Conditional_probability_distribution) (CPD) of the query bit, given all possible values of the dependencies. The table is used during the message-passing algorithm. If there are N dependencies in a factor, the table size is 2^N, so you can see how it is beneficial to keep the size of each factor low. Our factor `f` would have a table such as:

*CPD table for C = A & B [image by author]*Note: It’s not necessary to compute `P(C = 0 | A, B)` because it can be derived by `1.0 - P(C = 1 | A, B)`.


I have implemented the belief propagation algorithm in C++ since it can be quite slow in Python with a large problem size. However I found that this method performs poorly in practice. Belief propagation on a tree structure will always converge, but there are no convergence guarantees for a cyclic factor graph (so-called “loopy belief propagation”).


What often ends up happening is divergence of the message values because of the cyclic message passing, and we run into numerical overflow/underflow errors. A possible solution could be a logarithmic version of the sum-product algorithm, which I *tried* to implement but gave up on (see [here](https://www.researchgate.net/publication/3924103_Efficient_implementations_of_the_sum-product_algorithm_for_decoding_LDPC_codes), [here](https://www2.cs.duke.edu/research/AI/papers/Felzenszwalb06.pdf)).

## Neural Network


*Image from [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:NeuralNetwork.png)*


The idea here is that one could train a neural network to predict a valid hash input `X` given knowledge of hash output `Y` and the hash function `f` where `f(X) = Y`. In other words, a neural network should learn an inverse function `g` where `f(g(Y)) = Y` by observing many instances of random inputs and outputs. To this end, I (painfully) modified the symbolic bit vector primitive to support [PyTorch](https://pytorch.org/) tensors and work 100% with backpropagation.


The neural network architectures I implemented need more work and thought put into them. As of now they don’t perform well at all. I have struggled with enforcing “hard” relationships between bits, for example the network tries to learn valid assignments for all bits in the hash computation, but at the same time needs to be aware that if two bits are related by an INV operation, then `B = 1 - A`. Graph-based neural networks are one possible approach, but I recently saw this [talk](https://www.youtube.com/watch?v=EqvzIGY_bI4&ab_channel=MicrosoftResearch) and corresponding [code](https://github.com/dselsam/neurosat/tree/master/python) for a network called "NeuroSAT", which is extremely interesting and maybe promising.


Backpropagation through the hash function (and more in general, training a network on a large problem) is unfortunately quite slow. I believe this is a result of the complex [Autograd](https://pytorch.org/docs/stable/autograd.html) graph that the hash function creates, due to all of the slicing and moving around of individual tensor elements (bits).

## References and Resources


I hope you learned something here, or maybe this article sparked an idea for a creative solution that I haven’t thought of. You can always try to contact me (trevphil3 -at- gmail -dot- com) and I will do my best to respond. I have spent over a year working on this problem in my free time and I’m quite passionate about it! Besides the links in the body of the article, here are some more helpful links and papers:

---

*Originally published on [Medium](https://infosecwriteups.com/sat-solver-optimization-and-belief-propagation-attacks-on-sha-256-33c0233440e9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
