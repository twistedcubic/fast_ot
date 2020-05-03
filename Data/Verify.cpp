//Data verifier / stat generator
//
#include <bits/stdc++.h>
#include <chrono>
using namespace std; 
typedef long long LL;
typedef double D;
typedef vector<int> VI;
typedef set<int> SI;
typedef map<int, int> MII;
typedef pair<int,int> PII;


#define MP make_pair 
#define A first 
#define B second 

#define PB push_back 
#define FR(i, a, b) for(int i=(a); i<(b); i++) 
#define FOR(i, n) FR(i, 0, n) 

template <typename T> inline void SetMin(T &a, T b) {if(b < a) a = b;}
template <typename T> inline void SetMax(T &a, T b) {if(b > a) a = b;}

const int MAXNM = 5000;
int n, m;

double r_cap[MAXNM];
double c_cap[MAXNM];
double cost[MAXNM][MAXNM];

int Same(double x, double y) {
	return fabs(x - y) < 1e-9;
}

int IsInteger(double x) {
	return Same(x, int(x));
}

int main() {
	scanf("%d%d", &n, &m);
	FOR(i, n) assert(scanf("%lf", &r_cap[i]) == 1);
	FOR(j, m) assert(scanf("%lf", &c_cap[j]) == 1);
	FOR(i, n) FOR(j, m) assert(scanf("%lf", &cost[i][j]) == 1);
	puts("CHECKING ROW DEMANDS ARE INTEGERS");
	FOR(i, n) assert(IsInteger(r_cap[i]));
	puts("CHECKING COL DEMANDS ARE INTEGERS");
	FOR(j, m) assert(IsInteger(c_cap[j]));
	puts("CHECKING COSTS ARE INTEGERS");
	FOR(i, n) FOR(j, m) assert(IsInteger(cost[i][j]));

	puts("CHECKING ROW SUM == COL SUM");
	double s_r = 0;
	FOR(i, n) s_r += r_cap[i];
	double s_c = 0;
	FOR(j, m) s_c += c_cap[j];
	assert(Same(s_r, s_c));	

	printf("n = %d, m = %d\n", n, m);

//	puts("COMPUTING MIN/MAX ROW DEMANDS");
	double r_min = 1e100;
	double r_max = -1e100;
	FOR(i, n) {
		SetMin<double>(r_min, r_cap[i]);
		SetMax<double>(r_max, r_cap[i]);
	}
		
//	puts("COMPUTING MIN/MAX COLUMN DEMANDS");
	double c_min = 1e100;
	double c_max = -1e100;
	FOR(j, m) {
		SetMin<double>(c_min, c_cap[j]);
		SetMax<double>(c_max, c_cap[j]);
	}
	
	printf("Range: %0.0lf - %0.0lf\n", min(c_min, r_min), max(c_max, r_max));
	printf("Total demand = %0.0lf\n", s_r);

//	puts("COMPUTING MIN/MAX COSTS");
	double cost_min = 1e100;
	double cost_max = -1e100;
	FOR(i, n) FOR(j, m) {
		SetMin<double>(cost_min, cost[i][j]);
		SetMax<double>(cost_max, cost[i][j]);
	}
	printf("Cost Range: %0.0lf - %0.0lf\n", cost_min, cost_max);
	return 0;
}

