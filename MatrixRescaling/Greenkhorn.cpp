#include "cblas.h"
#include<bits/stdc++.h>
using namespace std;
typedef double D;
typedef vector<D> vD;
mt19937 gene(233);
D EPS = 0.001;
bool _W = false; //warning
int MAX_ITER = 10000000;

D * onec, * oner;

vD operator / (vD c, vD d) {
	for(int i(0); i < (int)c.size(); i++)
		c[i] /= d[i];
	return c;
}

vD operator * (D x, vD C) {
	for(D & y : C) y *= x;
	return C;
}

void exp(int len, D * c, D eta, D * A) {
	for(int i(0); i < len; i++) A[i] = exp(eta * c[i]);
}

vD abs(vD a) {
	for(D & x : a) x = abs(x);
	return a;
}

void dist(int n, D * a, D * b, D * c) {
	for(int i(0); i < n; i++) {
		c[i] = b[i] - a[i] + a[i] * log(a[i] / b[i]);
	}
}
vD operator - (const vD & a, const vD & b) {
	vD res(a.size());
	for(int i(0); i < (int)a.size(); i++) res[i] = a[i] - b[i];
	return res;
}
vD operator + (const vD & a, const vD & b) {
	vD res(a.size());
	for(int i(0); i < (int)a.size(); i++) res[i] = a[i] + b[i];
	return res;
}
void print(const vD & x) {
	for(D y : x) printf("%lf ", y);
	printf("\n");
}
void print(int n, D * x) {
	for(int i(0); i < n; i++) printf("%f ", x[i]);
	printf("\n");
}

double max_(D* c, int n) {
	D mx = c[0];
	for(int i(1); i < n; i++) {
		if(c[i] > mx) {
			mx = c[i];		
		}
	}
	return mx;
}

int _iter;
D _answer, _eta;
chrono::duration<D> _time;

double greenkhorn(int r_dim, int c_dim, D * C, D * r, D * c, double eta, D * A) {
	D * C0 = new D[r_dim * c_dim];
	memcpy(C0, C, sizeof(D) * r_dim * c_dim);

	auto start = chrono::high_resolution_clock::now();

	D C_max = max_(C, r_dim*c_dim);
	//D C_min = min_(C, r_dim*c_dim);
	
	cblas_daxpy (r_dim * c_dim, -1 + (1. / max(C_max, (D)0.01)), C, 1, C, 1);
	exp(r_dim * c_dim, C, -eta, A);

	D maxa0 = -1, mina0 = 1e50;
	for(int i(0); i < r_dim * c_dim; i++) {
		maxa0 = max(maxa0, A[i]);
		mina0 =min(mina0, A[i]);
	}
	
	D * row_sum = new D[r_dim];
	D * col_sum = new D[c_dim];

	cblas_dgemv (CblasRowMajor, CblasNoTrans, r_dim, c_dim, 1, A, c_dim, onec, 1, 0, row_sum, 1);
	cblas_dgemv (CblasRowMajor, CblasTrans, r_dim, c_dim, 1, A, c_dim, oner, 1, 0, col_sum, 1);


	D * row_dif = new D[r_dim];
	memcpy(row_dif, row_sum, sizeof(D) * r_dim);
	cblas_daxpy(r_dim, -1, r, 1, row_dif, 1);
	D * col_dif = new D[c_dim];
	memcpy(col_dif, col_sum, sizeof(D) * c_dim);
	cblas_daxpy(c_dim, -1, c, 1, col_dif, 1);
	
	D dist_AU = cblas_dasum(r_dim, row_dif, 1) + cblas_dasum(c_dim, col_dif, 1);
	
	int n_iter = 0;
	
	D * dist_r = new D[r_dim];
	D * dist_c = new D[c_dim];
	D * r_ratio = new D[r_dim];
	D * c_ratio = new D[c_dim];
	
	while(dist_AU > EPS){
		if(n_iter > MAX_ITER) {
			printf("MAX ITER reached with dist %f.\n", dist_AU);
			break;
		}		
		n_iter += 1;
		dist(r_dim, r, row_sum, dist_r);
		dist(c_dim, c, col_sum, dist_c);
		int mxri = cblas_idamax(r_dim, dist_r, 1);
		int mxci = cblas_idamax(c_dim, dist_c, 1);
		D mxr = dist_r[mxri];
		D mxc = dist_c[mxci];


		if(mxr > mxc) {
			r_ratio[mxri] = r[mxri] / row_sum[mxri];
			for(int j(0); j < c_dim; j++){
				double & aij = A[mxri * c_dim + j];
				row_sum[mxri] -= aij;
				col_sum[j] -= aij;
				aij = aij * r_ratio[mxri];
				row_sum[mxri] += aij;
				col_sum[j] += aij;
			}
		}else {
			c_ratio[mxci] = c[mxci] / col_sum[mxci];
			for(int i(0); i < r_dim; i++){
				double & aij = A[mxci + c_dim * i];
			       	row_sum[i] -= aij;
				col_sum[mxci] -= aij;	
				aij *= c_ratio[mxci];
				row_sum[i] += aij;
				col_sum[mxci] += aij;
			}
		}

		if (n_iter % (r_dim+c_dim)/2 == 0){

			row_dif = new D[r_dim];
			memcpy(row_dif, row_sum, sizeof(D) * r_dim);
			cblas_daxpy(r_dim, -1, r, 1, row_dif, 1);
			col_dif = new D[c_dim];
			memcpy(col_dif, col_sum, sizeof(D) * c_dim);
			cblas_daxpy(c_dim, -1, c, 1, col_dif, 1);
			dist_AU = cblas_dasum(r_dim, row_dif, 1) + cblas_dasum(c_dim, col_dif, 1);
			}
	}

	_iter = n_iter;
	D cur_cost = cblas_ddot (r_dim * c_dim, C0, 1, A, 1);
	_answer = cur_cost;
	
	auto finish = chrono::high_resolution_clock::now();

	chrono::duration<D> elapsed = finish - start;
	_time = elapsed;

	memcpy(C, C0, sizeof(D) * r_dim * c_dim);
	return cur_cost;
}

int main(int argc, char ** argv) {
	int n, m;
	D OPT = -1;
	D ACC = 0.1;
	D ETA_INIT = 200;
	if(argc >= 2) {
		sscanf(argv[1], "%lf", &OPT);
	}
	if(argc >= 3) {
		sscanf(argv[2], "%lf", &ACC);
	}
	if(argc >= 4) {
		sscanf(argv[3], "%lf", &ETA_INIT);
	}
	if(argc >= 5) {
		sscanf(argv[4], "%lf", &EPS);
	}
	scanf("%d%d", &n, &m);
	D * r = new D[n], * c = new D[m];
	
	D rowsum = 0;
	for(int i(0); i < n; i++) {
		double _r;
		scanf("%lf", &_r);
		r[i] = _r;
		rowsum += r[i];
	}
	EPS = rowsum*EPS;

	for(int i(0); i < m; i++) {
		double _r;
		scanf("%lf", &_r);
		c[i] = _r;
	}

	int r_dim = n, c_dim = m;

	oner = new D[r_dim];
	onec = new D[c_dim];
	for(int i(0); i < r_dim; i++) oner[i] = 1;
	for(int i(0); i < c_dim; i++) onec[i] = 1;

	D * C = new D[n * m], * A = new D[n * m];
	
	//int C_min = 0;
	for(int i(0); i < r_dim * c_dim; i++) {
		int a;
		scanf("%d", &a);
		C[i] = a;
		//if (a > 0 && a > C_min) C_min = a;
	}
	
	D le = 0, ri = 2 * ETA_INIT;
	do {
		D mid = (le + ri) / 2;
		
		_eta = mid;
		printf("Trying eta = %f\n", _eta);
		D ans = greenkhorn(r_dim, c_dim, C, r, c, mid, A);
		
		if(abs(ans - OPT) <= OPT*ACC) ri = mid;
		else le = mid;
		if(OPT == -1) break;

	} while((ri - le) > max(1., le * 0.01));
	
	printf("\nCost = %f\nNo of iterations = %d\nTime taken = %f\nEta = %f\n", _answer, _iter, _time, _eta);
}

