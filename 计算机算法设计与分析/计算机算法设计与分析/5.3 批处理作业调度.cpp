#include <math.h>
#include <iostream>

class Flowshop {
	friend int Flow(int**, int, int[]);
public:
	Flowshop(int **, int, int[]);
	~Flowshop();
private:
	void Backtrack(int i);
	int **M; // 各作业所需的处理时间
	int *x; // 当前作业调度
	int *bestx; // 当前最优作业调度
	int *f2; // 机器2完成处理的时间
	int f1; // 机器1完成处理的时间
	int f; // 完成时间和
	int bestf; // 当前最优值
	int n; // 作业数
};

template<class T>
void Swap(T &a, T &b) {
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
