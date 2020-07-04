
## A Study of Performance of Optimal Transport

This is the code repo for our paper [**A Study of Performance of Optimal Transport**](https://arxiv.org/abs/2005.01182).

By Yihe Dong, Yu Gao, Richard Peng, Ilya Razenshteyn, Saurabh Sawlani

We investigate the performance profiles of the most commonly used algorithms for solving the optimal transport problem, both exact and approximate, bridging classical combinatorial methods with the more recently-developed matrix scaling methods.

### Data

Data files for comparing optimal transport algorithms are formatted as:

+ Line 1: n and m, the # of rows and columns respectively
+ Line 2: n numbers, demands (in integers) of the left side
+ Line 3: m numbers, demands (in integers) of the right side (total of line 2 equals total of line 3)
+ Line 4 - n + 3: m numbers per line, the costs of transporting something from i to j

A format checker for this format is in Data/Verify.cpp

### Build
The C++ code can be compiled by e.g.:

`g++ -std=c++11 -O3 Sinkhorn.cpp libopenblas.a -o temp -lpthread`

And run as in [_Run_Sinkhorn.sh](MatrixRescaling/_Run_Sinkhorn.sh).

For ease of use, we also provide compiled [libopenblas.a](MatrixRescaling/libopenblas.a) and [cblas.h](MatrixRescaling/cblas.h), which has been tested on several versions of Ubuntu.
