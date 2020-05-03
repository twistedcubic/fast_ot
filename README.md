
## A Study of Performance of Optimal Transport

This is the code repo for our paper **A Study of Performance of Optimal Transport**

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