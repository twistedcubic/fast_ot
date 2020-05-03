# Kuhn-Munker (Hungarian) min-cost perfect matching algorithm

KM.cpp implements the exact version of the algorithm. The file \_Run\_KM.sh runs the code on all data files.

For the approximate version, we simply divide all costs by a large enough integer, creating a sparser graph with lesser unique entries. This is implemented in KMsparse.cpp. We binary search for all possible divisors (DIV) and find the largest divisor which gives us the required approximation factor. The file \_Run\_KM\_Sparse.sh runs the code on all data files.