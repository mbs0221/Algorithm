#pragma once

#include <math.h>
#include <iostream>

namespace Backtracking{

	template<class T>
	class Loading {
	public:
		Loading(T[] w, T c, int n);
		~Loading();
		friend T MaxLoading(T[], T, int);

	private:
		void Backtrack(int n);
		int n; // 集装箱数
		T *w, c, cw, bestw; // 集装箱重量数组，每一艘轮船的载重量，当前载重量，当前最优载重量
	};

	template<class T>
	class XLoading {
	public:
		XLoading(T[] w, T c, int n, int[] bestx);
		~XLoading();
		friend T MaxXLoading(T[], T, int, int[] bestx);

	private:
		void Backtrack(int i);
		int n; // 集装箱数
		int *x, *bestx; // 当前解，当前最优解
		T *w, c, cw, bestw; // 集装箱重量数组，每一艘轮船的载重量，当前载重量，当前最优载重量
		T r; // 剩余集装箱重量
	};

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

	void test_5_2();
	void test_5_3();
	void test();
}