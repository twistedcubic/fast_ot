#include <chrono>
#include "cblas.h"
#include<bits/stdc++.h>
using namespace std;
typedef double D;
typedef vector<D> vD;
mt19937 gene(233);
D EPS = 0.001;
bool _W = false; //warning
int MAX_ITER = 300000;

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

D max_(D* c, int n) {
	D mx = c[0];
	for(int i(1); i < n; i++) {
		if(c[i] > mx) {
			mx = c[i];			
		}
	}
	return mx;
}

D _answer, _eta;
chrono::duration<D> _time;
int _iter;

D sinkhorn_mc(int r_dim, int c_dim, D * C, D * r, D * c, D eta, D * A) {
  	D * C0 = new D[r_dim * c_dim];
	memcpy(C0, C, sizeof(D) * r_dim * c_dim);

	auto start = chrono::high_resolution_clock::now();
    
	D C_max = max_(C, r_dim*c_dim);
	cblas_daxpy (r_dim * c_dim, -1 + (1. / max(C_max, (D)0.01)), C0, 1, C, 1);	

    D *Xi = new D [r_dim * c_dim];
	exp(r_dim * c_dim, C, -eta, Xi);

    D *u = new D [r_dim];
    D *v = new D [c_dim];
    D *row_dif = new D[r_dim];
    D *col_dif = new D[c_dim];
    D dist_AU;
    int n_iter = 0;
    memcpy(v, onec, sizeof(D) * c_dim);
    for (; n_iter < MAX_ITER; n_iter += 2) {
        cblas_dgemv(CblasRowMajor, CblasNoTrans, r_dim, c_dim, 1, Xi, c_dim, v, 1, 0, u, 1);
        for (int i=0; i<r_dim; ++i) { u[i] = r[i] / u[i]; }
        cblas_dgemv(CblasRowMajor, CblasTrans,   r_dim, c_dim, 1, Xi, c_dim, u, 1, 0, v, 1);
        for (int j=0; j<c_dim; ++j) { v[j] = c[j] / v[j]; }

        if (n_iter % 100 == 0) {
            for (int i = 0; i < r_dim; ++i) {
                int k = i*c_dim;
                for (int j = 0; j < c_dim; ++j ) {
                    A[k + j] = Xi[k + j] * u[i] * v[j];
                }
            }

			cblas_dgemv (CblasRowMajor, CblasNoTrans, r_dim, c_dim, 1, A, c_dim, onec, 1, 0, row_dif, 1);
			cblas_dgemv (CblasRowMajor, CblasTrans,   r_dim, c_dim, 1, A, c_dim, oner, 1, 0, col_dif, 1);
			cblas_daxpy (r_dim, -1, r, 1, row_dif, 1);
			cblas_daxpy (c_dim, -1, c, 1, col_dif, 1);
			//take the l1 norm
			dist_AU = cblas_dasum(r_dim, row_dif, 1) + cblas_dasum(c_dim, col_dif, 1);
            // std::cout << "dist_AU: " << dist_AU << std::endl;
            if (dist_AU < EPS) {
                break;
            }
        }
    }    
	D cur_cost = cblas_ddot(c_dim * r_dim, C0, 1, A, 1);
	_answer = cur_cost; _iter = n_iter;
	auto finish = chrono::high_resolution_clock::now();

	chrono::duration<D> elapsed = finish - start;
	_time = elapsed;

    delete [] u;
    delete [] v;
    delete [] row_dif;
    delete [] col_dif;
	memcpy(C, C0, sizeof(D) * r_dim * c_dim);
    delete [] C0;
    delete [] Xi;
	return cur_cost;
}

D sinkhorn(int r_dim, int c_dim, D * C, D * r, D * c, D eta, D * A) {

  	D * C0 = new D[r_dim * c_dim];
	memcpy(C0, C, sizeof(D) * r_dim * c_dim);

	auto start = chrono::high_resolution_clock::now();
	
	D C_max = max_(C, r_dim*c_dim);
	cblas_daxpy (r_dim * c_dim, -1 + (1. / max(C_max, (D)0.01)), C, 1, C, 1);	
	exp(r_dim * c_dim, C, -eta, A);
	
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
	//for(int i(0); i < r_dim; i++) printf("%f ", row_dif[i]); printf("\n");
	
	D dist_AU = cblas_dasum(r_dim, row_dif, 1) + cblas_dasum(c_dim, col_dif, 1);
	//cout << dist_AU << endl;
	int n_iter = 0;
	vD cost_l;

	D * r_ratio = new D[r_dim];
	D * c_ratio = new D[c_dim];

	int row = 1;
	
	while(dist_AU > EPS) {
	  
	  if(n_iter > MAX_ITER) {
	    printf("MAX ITER reached with dist %f.\n", dist_AU);
	    break;
	  }
	  
		n_iter += 1;
		if(row == 1) {
			cblas_dgemv (CblasRowMajor, CblasNoTrans, r_dim, c_dim, 1, A, c_dim, onec, 1, 0, row_sum, 1);
			for(int i=0; i<r_dim; i++){
			  //r_diag[j] += log(r[j] / row_sum[j]);
			  r_ratio[i] = r[i] / row_sum[i];  
			  for(int j(0); j < c_dim; j++){
			    A[i * c_dim + j] = A[i * c_dim + j] * r_ratio[i];
			  }
			}
		}else {
			cblas_dgemv (CblasRowMajor, CblasTrans, r_dim, c_dim, 1, A, c_dim, oner, 1, 0, col_sum, 1);
			for(int j=0; j<c_dim; j++){
			  c_ratio[j] = c[j] / col_sum[j];
			  for(int i(0); i < r_dim; i++){
			    A[i * c_dim + j] = A[i * c_dim + j] * c_ratio[j];
			  }
			}
		}
		row ^= 1;
		if (1) {
			//printf(".");
			fflush(stdout);
			
			cblas_dgemv (CblasRowMajor, CblasNoTrans, r_dim, c_dim, 1, A, c_dim, onec, 1, 0, row_dif, 1);
			cblas_dgemv (CblasRowMajor, CblasTrans, r_dim, c_dim, 1, A, c_dim, oner, 1, 0, col_dif, 1);
			cblas_daxpy(r_dim, -1, r, 1, row_dif, 1);
			cblas_daxpy(c_dim, -1, c, 1, col_dif, 1);
			//take the l1 norm
			dist_AU = cblas_dasum(r_dim, row_dif, 1) + cblas_dasum(c_dim, col_dif, 1);
		}
	}
	D cur_cost = cblas_ddot(c_dim * r_dim, C0, 1, A, 1);// * C_max;
	
	_answer = cur_cost; _iter = n_iter;

	auto finish = chrono::high_resolution_clock::now();

	chrono::duration<D> elapsed = finish - start;
	_time = elapsed;
	//printf("%f %d %f\n", _answer, _iter, _time);
	
	memcpy(C, C0, sizeof(D) * r_dim * c_dim);
	return cur_cost;
}

int main(int argc, char ** argv) {
	int r_dim, c_dim;
	D OPT = -1; 
	D ACC = 0.1; 
	D ETA_INIT = 200;
	if(argc >= 2) {
		sscanf(argv[1], "%lf", &OPT); // Optimum cost given as argument
	}
	if(argc >= 3) {
		sscanf(argv[2], "%lf", &ACC); // Desired accuracy given as argument
	}
	if(argc >= 4) {
		sscanf(argv[3], "%lf", &ETA_INIT); // Initial Eta given as argument
	}
	if(argc >= 5) {
		sscanf(argv[4], "%lf", &EPS); // Initial Eps (fraction of unsatisfied demand) given as argument
	}
	while(scanf("%d%d", &r_dim, &c_dim) == 2) {
	D * r = new D[r_dim], * c = new D[c_dim];

	D total_flow = 0;

	for(int i(0); i < r_dim; i++) {
		D _r;
		scanf("%lf", &_r);
		r[i] = _r;
		total_flow += _r;
	}

	EPS = total_flow*EPS;
	
	for(int i(0); i < c_dim; i++) {
		D _r;
		scanf("%lf", &_r);
		c[i] = _r;
	}
	printf("IO done\n");
	fflush(stdout);

	oner = new D[r_dim];
	onec = new D[c_dim];
	for(int i(0); i < r_dim; i++) oner[i] = 1;
	for(int i(0); i < c_dim; i++) onec[i] = 1;
	
	D * C = new D[r_dim * c_dim], * A = new D[r_dim * c_dim];

	for(int i(0); i < r_dim * c_dim; i++) {
		int a;
		scanf("%d", &a);
		C[i] = a;// / DIV;
	}
	
	D le = 0, ri = ETA_INIT * 2;
	do {
		D mid = (le + ri) / 2;
		_eta = mid;
		printf("Trying eta = %f\n", _eta);
//		D ans = sinkhorn(r_dim, c_dim, C, r, c, _eta, A);
		D ans = sinkhorn_mc(r_dim, c_dim, C, r, c, _eta, A);
		if(abs(ans - OPT) < ACC * OPT) ri = mid;
		else le = mid;
		if(OPT == -1) break;
	} while((ri - le) > max(1., le * 0.01));
	printf("\nCost = %f\nNo of iterations = %d\nTime taken = %f\nEta = %f\n", _answer, _iter, _time, _eta);
	}
}

