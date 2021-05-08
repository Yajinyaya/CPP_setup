/**
 * @file ibet.cpp
 * @author Yajin Li
 * @brief 
 * The lp is constructed in the following way. The first 2k are constraints 
 * for player 1's strategy p_1 to p_k to be in [0,1].
 * Since there are at most k+1 strategies for player 2(for i, j values, if 
 * i > j, possibility for remaining q_j are all 0 to minimize player 1's payoff)
 * we use LP to find the max out of k+1 possibilities for p1. The remainging 
 * part is to calculate the expected min value of each strategy and take the max.
 * @version 0.1
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
//    This code was adapted from the UBC CODEARCHIVE 2014.
//    It is in the public domain.  ---Danny Sleator Nov. 2017

#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <math.h>
#include <algorithm>
#include <time.h>
using namespace std; 

class Simplex {

private:
    int m, n;
    std::vector<std::vector<double> > A;
    std::vector<int> basic;                 // size m.  indices of basic vars
    std::vector<int> nonbasic;              // size n.  indices of non-basic vars

public:
    std::vector<double> soln;
    double z; // return value of the objective function.
    int lp_type; // for return.  1 if feasible, 0 if not feasible, -1 if unbounded

    const double INF; // unbelivably, C++ doesn't support static doubles initialized in a class
    const double EPS;
    const static int FEASIBLE = 1; // int vars are ok though 
    const static int INFEASIBLE = 0;
    const static int UNBOUNDED = -1;

  /*
    input:
      m = #constraints, n =#variables
      max c dot x s.t. a x <= b
      where a = mxn, b = m vector, c = n vector
    output:
      Infeasible, or Unbounded, or a pair Feasible (z,soln) where z is
      the maximum objective function value, and soln is an n-vector of
      variable values.
    caveats:
      Cycling is possible.  Nothing is done to mitigate loss of
      precision when the number of iterations is large.
  */
    Simplex(int m0, int n0, 
            std::vector<std::vector<double> > & A0, 
            std::vector<double> & B, 
            std::vector<double> & C) :
        m(m0),
        n(n0),
        A(m0+1),
        basic(m0),
        nonbasic(n0),
        soln(n),
        INF(1e100),
        EPS(1e-9)
    
    {
        for (unsigned int i = 0; i < A.size(); i++) {
            A[i].resize(n+1);
        }

        for (int j=0; j<m; j++) basic[j] = n+j;
        for (int i=0; i<n; i++) nonbasic[i] = i;

        for (int i=0; i<m; i++) {
            A[i][n] = B[i];
            for (int j=0; j<n; j++) A[i][j] = A0[i][j];
        }

        for (int j=0; j<n; j++) A[m][j] = C[j];

        if(!Feasible()) {
            lp_type = INFEASIBLE;
            return;
        }

        while(true) {
            int r=0, c=0;
            double p = 0.0;
            for (int i=0; i<n; i++) {if (A[m][i] > p) p = A[m][c=i];}
            if (p < EPS) {
                for(int j=0; j<n; j++) if (nonbasic[j] < n) soln[nonbasic[j]] = 0;
                for(int i=0; i<m; i++) if (basic[i] < n) soln[basic[i]] = A[i][n];
                z = -A[m][n];
                lp_type = FEASIBLE;
                break;
            }
            p = INF;
            for (int i=0; i<m; i++) {
                if (A[i][c] > EPS) {
                    double v = A[i][n] / A[i][c];
                    if (v < p) {p = v; r = i;}
                }
            }
            if (p == INF) {
                lp_type = UNBOUNDED;
                break;
            }
            Pivot(r,c);
        }
    }

private:

    void printa() {
	int i,j;
	for(i=0; i<=m; i++) {
	    for(j=0; j<=n; j++) {
		printf("A[%d][%d] = %f\n", i, j, A[i][j]);
	    };
	}
    }

    void Pivot(int r, int c) {

	// printf("pivot %d %d\n", r, c);
	// printa();
	
	swap(basic[r], nonbasic[c]);

        A[r][c] = 1 / A[r][c];
        for (int j=0; j<=n; j++) {
            if (j!=c) A[r][j] *= A[r][c];
        }
        for(int i=0; i<=m; i++) {
            if (i != r) {
                for (int j=0; j<=n; j++) {if (j!=c) A[i][j] -= A[i][c] * A[r][j];}
                A[i][c] = -A[i][c] * A[r][c];
            }
        }
    }

    bool Feasible() {
        int r=0, c=0;
        while(true) {
            double p = INF;
            for(int i=0; i<m; i++) if(A[i][n] < p) p = A[r=i][n];
            if(p > -EPS) return true;
            p = 0.0;
            for(int i=0; i<n; i++) if(A[r][i] < p) p = A[r][c=i];
            if(p > -EPS) return false;
            p = A[r][n] / A[r][c];
            for(int i=r+1; i<m; i++) {
                if(A[i][c] > EPS) {
                    double v = A[i][n] / A[i][c];
                    if(v < p) {p = v; r = i;}
                }
            }
            Pivot(r,c);
        }
    }
};


  /*
    input:
      m = #constraints, n =#variables
      max c dot x s.t. a x <= b
      where a = mxn, b = m vector, c = n vector
    output:
      Infeasible, or Unbounded, or a pair Feasible (z,soln) where z is
      the maximum objective function value, and soln is an n-vector of
      variable values.
    caveats:
      Cycling is possible.  Nothing is done to mitigate loss of
      precision when the number of iterations is large.
  */
int main(int argc, char *argv[]) {
  int m, n, k = 0;
  double a, b = 0;
  cin >> k;
  cin >> a;
  cin >> b;
  //
  m = 3 * k + 1;
  n = k + 1;
  vector<vector<double>> A(m, vector<double>(n, 0));
  vector<double> B(m, 0);
  vector<double> C(n, 0);
  for (int i = 0; i < k; i++){
    A[2 * i][i] = 1;
    B[2 * i] = 1;
  }
  for (int i = 0; i < k; i ++){
    A[2 * i + 1][i] = -1;
    B[2 * i + 1] = 0;
  }
  for (int i = 2 * k; i < m; i ++){
    vector<double> q_strategy(k, 1);
    for (int j = 0; j < i - 2 * k; j++){
      q_strategy[j] = 0;
    }

    for (int ii = 0; ii < k; ii ++){
      double p_coefficient = 0;
      for (int jj = 0; jj < k; jj++){
        if (ii == jj){
          continue;
        }
        //player 1's card is bigger
        if (jj < ii){
          p_coefficient += 2 * a + b * q_strategy[jj];
        } else{
          p_coefficient += 2 * a - (2 * a + b) * q_strategy[jj];
        }
      }
      A[i][ii] = -(p_coefficient / (k * (k - 1)));
    }
    A[i][n - 1] = 1;
  }

  C[n - 1] = 1;


  Simplex lp(m, n, A, B, C);
  printf("%.8f\n", lp.z - a);
}