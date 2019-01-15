#include "第五章 回溯法.h"

using namespace std;

namespace Algorithm {

	namespace Backtracking {

		// 5.2 装载问题
		template<class T> Loading<T>::Loading(T[] w, T c, int n)
		{
			this->w = w;
			this->c = c;
			this->n = n;
			this->bestw = 0;
			this->cw = 0;
		}

		template<class T> Loading<T>::~Loading()
		{
		}

		template<class T>
		void Loading<T>::test()
		{
		}

		template<class T> void Loading<T>::Backtrack(int i)
		{
			if (i > n) {
				if (cw > bestw) {
					bestw = cw;
					return;
				}
			}
			// 搜索子树
			if (cw + w[i] <= c) {
				cw += w[i];
				Backtrack(i + 1); // x[i] = 1
				cw -= w[i];
			}

			Backtrack(i + 1); // x[i] = 0
		}

		template<class T> T MaxLoading(T w[], T c, int n)
		{
			Loading<T> x(w, c, n);
			x.Backtrack(0);
			return T();
		}

		// 5.2 装载问题
		template<class T> XLoading::XLoading(T[] w, T c, int n, int[] bestx)
		{
			this->x = new int[n + 1];
			this->w = w;
			this->c = c;
			this->n = n;
			this->bestx = bestx;
			this->bestw = 0;
			this->cw = 0;
			this->r = 0;
			for (int i = 0; i < n; i++) {
				this->r += w[i];
			}
		}

		template<class T> XLoading::~XLoading()
		{
			delete[] x;
		}

		template<class T>
		void XLoading<T>::test()
		{
		}

		template<class T> void XLoading<T>::Backtrack(int i)
		{
			if (i > n) { // 到达叶节点
				for (int j = 0; j < n; j++) {
					bestx[j] = x[j];
				}
				bestw = cw;
				return;
			}

			// 搜索子树
			r -= w[i];
			if (cw + w[i] < c) { // x[i] = 1
				x[i] = 1; // 装x[i]
				cw += w[i];
				Backtrack(i + 1);
				cw -= w[i];
			}

			if (cw + r > bestw) { // x[i] = 0
				x[i] = 0; // 不装x[i]
				Backtrack(i + 1);
			}

			r += w[i];
		}

		template<class T> T MaxXLoading(T w[], T c, int n, int[] bestx)
		{
			XLoading<T> x(w, c, n, bestx);
			x.Backtrack(0);
			return x.bestw;
		}

		// 5.2 装载问题
		template<class T> T MaxMLoading(T w[], T c, int n, int[] bestx) {
			// 返回最优载重量及其相应解，初始化根节点

			int i = 0; // 当前层
			int *x = new int[n + 1]; // 最优路径
			T bestw = 0; // 当前最优载重量
			T cw = 0; // 当前载重量
			T r = 0; // 剩余集装箱重量
			for (int j = 0; j < n; j++) {
				r += w[j];
			}

			while (true) {
				// 进入左子树
				while (i < n&& cw + w[i] <= c) {
					r -= w[i];
					cw += w[i];
					x[i] = 1;
					i++;
				}

				// 到达叶节点
				if (i >= n) {
					for (int j = 0; j < n; j++) {
						bestx[j] = x[j];
					}
				}
				else {
					// 进入右子树
					r -= w[i];
					x[i] = 0;
					i++;
				}

				// 剪枝回溯
				while (cw + r < bestw) {
					// 从右子树返回
					i--;
					while (i > 0 && !x[i]) {
						r += w[i];
						i--;
					}
					if (i == 0) {
						delete[] x;
						return bestw;
					}
					// 进入右子树
					x[i] = 0;
					cw -= w[i];
					i++;
				}
			}
		}
		
		// 5.3 批处理作业调度
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

		void Flowshop::test()
		{
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

		// 
		void test() {
		}
	}
}