#include "第五章 回溯法.h"

namespace Backtracking {

	template<class T> void Swap(T &a, T &b) {
		T t = a;
		a = b;
		b = t;
	}

	int Flow(int **M, int n, int bestx[])
	{
		Flowshop x(M, n, bestx);
		x.Backtrack(0);
		return x.bestf;
	}

	Flowshop::Flowshop(int **M, int n, int bestx[])
	{
		int ub = INT_MAX;
		this->x = new int[n + 1];
		this->f2 = new int[n + 1];
		this->M = M;
		this->n = n;
		this->bestx = bestx;
		this->bestf = ub;
		this->f1 = 0;
		this->f = 0;
		for (int j = 0; j < n; j++) {
			this->f2[j] = 0;
			this->x[j] = j;
		}
	}

	Flowshop::~Flowshop()
	{
		delete[] x;
		delete[] f2;
	}

	void Flowshop::Backtrack(int i)
	{
		if (i > n) {
			for (int j = 0; j < n; j++) {
				bestx[j] = x[j];
			}
			bestf = f;
		}
		else {
			for (int j = i; j < n; j++) {
				f1 += M[x[j]][0];
				f2[i] = ((f2[i - 1] > f1) ? f2[i - 1] : f1) + M[x[j]][1];
				f += f2[i];
				if (f < bestf) {
					Swap(x[i], x[j]);
					Backtrack(i + 1);
					Swap(x[i], x[j]);
				}
				f1 -= M[x[j]][0];
				f -= f2[i];
			}
		}
	}

}