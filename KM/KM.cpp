/*
taken from http://e-maxx.ru/algo/assignment_hungary
*/
#include <cstdio>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

const int INF = 1<<30;
const int MAXNM = 5010;

int n, m;
int temp;
int a[MAXNM][MAXNM];

int main() {
	printf("Reading input graph...");
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &temp);
	}
	for (int j = 1; j <= m; ++j) {
		scanf("%d", &temp);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &a[i][j]);
		}
	}
	printf("Done!\n");
	
	printf("Computing minimum cost perfect matching...");
	
	auto t1 = std::chrono::high_resolution_clock::now();
	vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
	for (int i=1; i<=n; ++i) {
		p[0] = i;
		int j0 = 0;
		vector<int> minv (m+1, INF);
		vector<char> used (m+1, false);
		do {
			used[j0] = true;
			int i0 = p[j0],  delta = INF,  j1;
			for (int j=1; j<=m; ++j)
				if (!used[j]) {
					int cur = a[i0][j]-u[i0]-v[j];
					if (cur < minv[j])
						minv[j] = cur,  way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j],  j1 = j;
				}
			for (int j=0; j<=m; ++j)
				if (used[j])
					u[p[j]] += delta,  v[j] -= delta;
				else
					minv[j] -= delta;
			j0 = j1;
		} while (p[j0] != 0);
		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	int total_cost = 0;
	for (int j = 1; j <= m; ++j) {
		total_cost += a[p[j]][j];
	}
	printf("Done!\n");
	
	printf("Time: %f seconds\n", std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count());
	printf("Optimal cost: %d\n", total_cost);
	return 0;
}
