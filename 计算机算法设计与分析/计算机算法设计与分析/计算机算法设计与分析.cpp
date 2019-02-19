#include "计算机算法设计与分析.h"

using namespace std;

namespace Algorithm {

	int ** InitMatrix(int rows, int cols) {
		int **mat = new int*[rows];
		for (int i = 0; i < rows; i++) {
			mat[i] = new int[cols];
			for (int j = 0; j < cols; j++) {
				mat[i][j] = 0;
			}
		}
		return mat;
	}
	
	/**
	* 初始化矩阵
	* mat 矩阵
	* size 大小
	*/
	int **InitMatrix(int size) {
		int **mat = new int*[size];
		for (int i = 0; i < size; i++) {
			mat[i] = new int[size];
			for (int j = 0; j < size; j++) {
				mat[i][j] = -1;
			}
		}
		return mat;
	}

	/**
	* 打印矩阵
	* mat 矩阵
	* size 大小
	*/
	void PrintMatrix(int **mat, int size) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				std::cout << std::setw(4) << mat[i][j];
			}
			std::cout << std::endl;
		}
	}
	
	template<class T>
	void PrintArray(T a[], int n) {
		for (int i = 0; i < n; i++) {
			std::cout << std::setw(4) << a[i];
		}
		std::cout << std::endl;
	}

	// 第二章 分治算法
	namespace DivideAndConquer {

		// 2.6 棋盘覆盖
		namespace ChessBoard {

			void Init(int **board, int dr, int dc) {
				tile = 0;
				board[dr][dc] = tile++;
			}

			/**
			* 棋盘覆盖
			* tr 棋盘左上角方格行号
			* tc 棋盘左上角方格列号
			* dr 特殊方格所在行号
			* dc 特殊方格所在列号
			* size 棋盘大小
			*/
			void Solve(int **board, int tr, int tc, int dr, int dc, int size)
			{
				if (size == 1) {
					return;
				}
				int t = tile++;
				int sz = size / 2;

				// 覆盖左上角子棋盘
				if (dr < tr + sz && dc < tc + sz) {
					// 特殊方格在此棋盘中
					Solve(board, tr, tc, dr, dc, sz);
				}
				else {
					// 此棋盘无特殊方格，用t号L型骨牌覆盖右下角
					board[tr + sz - 1][tc + sz - 1] = t;
					// 覆盖其余方格
					Solve(board, tr, tc, tr + sz - 1, tc + sz - 1, sz);
				}

				// 覆盖右上角子棋盘
				if (dr < tr + sz && dc >= tc + sz) {
					// 特殊方格在此棋盘中
					Solve(board, tr, tc + sz, dr, dc, sz);
				}
				else {
					// 此棋盘无特殊方格，用t号L型骨牌覆盖左下角
					board[tr + sz - 1][tc + sz] = t;
					// 覆盖其余方格
					Solve(board, tr, tc + sz, tr + sz - 1, tc + sz, sz);
				}

				// 覆盖左下角子棋盘
				if (dr >= tr + sz && dc < tc + sz) {
					// 特殊方格在此棋盘中
					Solve(board, tr + sz, tc, dr, dc, sz);
				}
				else {
					// 用t号L型骨牌覆盖右上角
					board[tr + sz][tc + sz - 1] = t;
					// 覆盖其余方格
					Solve(board, tr + sz, tc, tr + sz, tc + sz - 1, sz);
				}

				// 覆盖右下角子棋盘
				if (dr >= tr + sz&& dc >= tc + sz) {
					// 特殊方格在此棋盘中
					Solve(board, tr + sz, tc + sz, dr, dc, sz);
				}
				else {
					// 用t号L型骨牌覆盖左上角
					board[tr + sz][tc + sz] = t;
					// 覆盖其余方格
					Solve(board, tr + sz, tc + sz, tr + sz, tc + sz, sz);
				}
			}

			void test()
			{
				int **board = NULL;
				int size, dr, dc;
				std::cout << "2.6 棋盘覆盖" << std::endl;
				std::cout << "请输入：size，dr，dc" << std::endl;
				std::cin >> size >> dr >> dc;
				std::cout << "初始化" << std::endl;
				board = InitMatrix(size);
				std::cout << "棋盘覆盖" << std::endl;
				ChessBoard::Init(board, dr, dc);
				ChessBoard::Solve(board, 0, 0, dr, dc, size);
				std::cout << "覆盖结果" << std::endl;
				PrintMatrix(board, size);
			}
		}

		// 2.7 归并排序
		namespace MergeSort {

			template<class T>
			void MergeArray(T a[], T b[], int left, int mid, int right) {
				int i = left, j = mid + 1;
				int k = left;
				while (i <= mid && j <= right) {
					if (a[i] <= a[j]) {
						b[k++] = a[i++];
					}
					else {
						b[k++] = a[j++];
					}
				}
				while (i <= mid) {
					b[k++] = a[i++];
				}
				while (j <= right) {
					b[k++] = a[j++];
				}
				for (i = left; i < k; i++) {
					a[i] = b[i];
				}
			}

			template<class T>
			void Sort(T a[], T b[], int left, int right) {
				if (left < right) {
					int mid = (left + right) / 2;
					Sort(a, b, left, mid);
					Sort(a, b, mid + 1, right);
					MergeArray(a, b, left, mid, right);
				}
			}

			void test()
			{
				int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
				int *b = new int[11];
				cout << "2.7 合并排序" << endl;
				Sort(a, b, 0, 10);
				cout << "a:" << endl;
				PrintArray(a, 11);
				cout << "b:" << endl;
				PrintArray(b, 11);
				delete[] b;
			}
		}

		// 2.7 非递归版归并排序
		namespace MergeSortNonrecursive {

			template<class T>
			void Merge(T a[], T b[], int left, int mid, int right)
			{
				int i = left, j = mid + 1;
				int k = left;
				while (i <= mid && j <= right) {
					if (a[i] <= a[j]) {
						b[k++] = a[i++];
					}
					else {
						b[k++] = a[j++];
					}
				}
				while (i <= mid) {
					b[k++] = a[i++];
				}
				while (j <= right) {
					b[k++] = a[j++];
				}
			}

			template<class T>
			void MergePass(T a[], T b[], int sz, int n)
			{
				int i = 0;
				// 合并大小为sz的相邻2段子数组
				while (i < n - 2 * sz) {
					Merge(a, b, i, i + sz - 1, i + 2 * sz - 1);
					i += (2 * sz);
				}
				// 剩下的元素个数少于2*sz
				if (i + sz < n) {
					Merge(a, b, i, i + sz - 1, n - 1);
				}
				else {
					for (int j = i; j < n; j++) {
						b[j] = a[j];
					}
				}
			}

			template<class T>
			void Sort(T a[], T b[], int n) {
				int sz = 1;
				while (sz < n) {
					MergePass(a, b, sz, n);
					sz += sz;
					MergePass(b, a, sz, n);
					sz += sz;
				}
			}

			void test()
			{
				int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
				int *b = new int[11];
				cout << "2.7 合并排序【非递归】" << endl;
				Sort(a, b, 11);
				cout << "a:" << endl;
				PrintArray(a, 11);
				cout << "b:" << endl;
				PrintArray(b, 11);
				delete[] b;
			}
		}

		// 2.8 快速排序
		namespace QuickSort {

			template<class T> int Partition(T a[], int p, int r) {
				int i = p, j = r + 1;
				T x = a[p];
				// 将小于x的元素交换到左边区域
				// 将大于x的元素交换到右边区域
				while (true) {
					while (a[++i] < x&&i < r);
					while (a[--j] > x);
					if (i >= j) break;
					T t = a[i];
					a[i] = a[j];
					a[j] = t;
				}
				a[p] = a[j];
				a[j] = x;
				return j;
			}

			template<class T> void Sort(T a[], int left, int right) {
				if (left < right) {
					int q = Partition(a, left, right);
					Sort(a, left, q - 1); // 对左半段排序
					Sort(a, q + 1, right); // 对右半段排序
				}
			}

			void test()
			{
				int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
				int *b = new int[11];
				cout << "2.8 快速排序" << endl;
				Sort(a, 0, 10);
				std::cout << "a:" << std::endl;
				PrintArray(a, 11);
				std::cout << "b:" << std::endl;
				PrintArray(b, 11);
				delete[] b;
			}
		}

		// 2.11 循环赛
		namespace RoundRobin {

			void Table(int k, int **a) {
				int n = 1;
				for (int i = 0; i < k; i++) n *= 2;
				for (int i = 0; i < n; i++)a[1][i] = i;
				int m = 1;
			}

			void test() {
				cout << "2.11 循环赛日程表" << endl;
			}
		};

		void test() {
			cout << "第二章 递归与分治策略" << endl;
			ChessBoard::test();
			MergeSort::test();
			MergeSortNonrecursive::test();
			RoundRobin::test();
			getchar();
		}
	}

	// 第三章 动态规划
	namespace DynamicProgramming {

		// 3.1 矩阵连乘问题
		namespace MatrixChain {

			void Solve(int *p, int **m, int **s, int n) {
				for (int i = 0; i < n; i++) m[i][i] = 0;
				// 对于每一行
				for (int r = 0; r < n; r++) {
					// 对于每一种分割方法
					for (int i = 1; i <= n - r; i++) {
						int j = i + r - 1;
						m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
						s[i][j] = i;
						// 寻找最佳分割点
						for (int k = i + 1; k < j; k++) {
							int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
							if (t < m[i][j]) {
								m[i][j] = t;
								s[i][j] = k;
							}
						}
					}
				}
			}

			void TraceBack(int i, int j, int **s)
			{
				if (i == j) return;
				TraceBack(i, s[i][j], s);
				TraceBack(s[i][j] + 1, j, s);
				cout << "Multiply A" << i << ',' << s[i][j] << "and A" << (s[i][j] + 1) << "," << j << endl;
			}

			void test()
			{
				// 矩阵的维数
				int p[] = { 30, 35, 15, 5, 10, 20, 25 };
				int **m, **s;
				cout << "3.1 矩阵连乘问题" << endl;
				try
				{
					m = InitMatrix(6, 6);
					s = InitMatrix(6, 6);
					MatrixChain::Solve(p, m, s, 6);
					MatrixChain::TraceBack(0, 5, s);
					delete[] m;
					delete[] s;
				}
				catch (const std::exception&)
				{
					cout << "测试失败" << endl;
				}
			}
		}

		// 3.3 最长公共子序列
		namespace LongestCommonSubsequence {

			/* 最长公共子序列 */
			void Solve(string a, string b, int **c, int **s) {
				int m = a.length();
				int n = b.length();
				// 初始化第1列
				for (int i = 0; i < m; i++)c[i][0] = a[i] == b[0] ? 1 : 0;
				// 初始化第1行
				for (int i = 0; i < n; i++)c[0][i] = a[0] == b[i] ? 1 : 0;
				// 动态规划
				for (int i = 1; i < m; i++)
					for (int j = 1; j < n; j++) {
						if (a[i] == b[j]) {
							c[i][j] = c[i - 1][j - 1] + 1;
							s[i][j] = 1; // TOP LEFT
						}
						else if (c[i - 1][j] >= c[i][j - 1]) {
							c[i][j] = c[i - 1][j];
							s[i][j] = 2; // LEFT
						}
						else {
							c[i][j] = c[i][j - 1];
							s[i][j] = 3; // UP
						}
					}
			}

			/* 打印最长公共子序列 */
			void PrintLCS(string a, string b, int **s)
			{
				int i = a.length() - 1;
				int j = b.length() - 1;
				string lcs = "";
				while (i >= 0 && j >= 0) {
					switch (s[i][j]) {
					case 1:
						lcs.push_back(a[i]);
						i--, j--;
						break;
					case 2:
						i--;
						break;
					default:
						j--;
						break;
					}
				}
				lcs.push_back(a[i]);
				reverse(lcs.begin(), lcs.end());
				cout << lcs << endl;
			}

			/* 3.3 测试最长公共子序列 */
			void test() {
				string a = "ABCBDAB";
				string b = "BDCABA";
				int **c, **s;
				c = InitMatrix(a.length(), b.length());
				s = InitMatrix(a.length(), b.length());
				cout << "3.3 最长公共子序列" << endl;
				cout << "a:" << a << endl;
				cout << "b:" << b << endl;
				cout << "Solve" << endl;
				LongestCommonSubsequence::Solve(a, b, c, s);
				cout << "PrintLCS" << endl;
				LongestCommonSubsequence::PrintLCS(a, b, s);
				delete[] c;
				delete[] s;
			}
		}

		// 3.4 最大子段和
		namespace MaxSubSum {

			/* 最大子段和问题的简单算法*/
			int Solve(int n, int *a, int &besti, int &bestj)
			{
				int sum = 0;
				for (int i = 0; i < n; i++) {
					int thissum = 0;
					for (int j = i; j < n; j++) {
						thissum += a[j];
						if (thissum > sum) {
							sum = thissum;
							besti = i;
							bestj = j;
						}
					}
				}
				return sum;
			}

			/* 最大子段和问题的分治算法*/
			int SolveDC(int *a, int left, int right)
			{
				int sum = 0;
				if (left == right) {
					sum = a[left] > 0 ? a[left] : 0;
				}
				else {
					int mid = (left + right) / 2;
					int left_sum = SolveDC(a, left, mid);
					int right_sum = SolveDC(a, mid + 1, right);
					// 左边和
					int s1 = 0;
					int left_s = 0;
					for (int i = mid; i >= left; i--) {
						left_s += a[i];
						if (left_s > s1) {
							s1 = left_s;
						}
					}
					// 右边和
					int s2 = 0;
					int right_s = 0;
					for (int i = mid + 1; i <= right; i++) {
						right_s += a[i];
						if (right_s > s2) {
							s2 = right_s;
						}
					}
					// 归并结果
					sum = s1 + s2;
					if (sum < left_sum) sum = left_sum;
					if (sum < right_sum) sum = right_sum;
				}
				return sum;
			}

			/* 最大子段和问题的动态规划算法*/
			int SolveDP(int *a, int left, int right)
			{
				int sum = 0, b = 0;
				for (int i = left; i < right; i++) {
					if (b > 0) {
						b += a[i];
					}
					else {
						b = a[i];
					}
					if (b > sum) {
						sum = b;
					}
				}
				return sum;
			}

			/* 测试3.4 最大子段和*/
			void test()
			{
				int a[] = { -2, 11,-4, 13, -5, -2 };
				int sum, besti, bestj;
				cout << "3.4 最大子段和" << endl;
				sum = MaxSubSum::Solve(6, a, besti, bestj);
				cout << "Simple Solution:" << setw(4) << sum << endl;
				sum = MaxSubSum::SolveDC(a, 0, 5);
				cout << "Divide and Conquer:" << setw(4) << sum << endl;
				sum = MaxSubSum::SolveDP(a, 0, 6);
				cout << "Dynamic Programming:" << setw(4) << sum << endl;
			}
		}

		void test()
		{
			cout << "第三章 动态规划" << endl;
			MaxSubSum::test();
			MatrixChain::test();
			LongestCommonSubsequence::test();
			getchar();
		}
	}

	// 第五章 回溯法
	namespace Backtracking {

		// 5.2 装载问题
		template<class T>
		Loading<T>::Loading(T * w, T c, int n)
		{
			this->w = w;
			this->c = c;
			this->n = n;
			this->bestw = 0;
			this->cw = 0;
		}

		template<class T>
		Loading<T>::~Loading()
		{
		}

		template<class T>
		void Loading<T>::test()
		{
			cout << "5.2 装载问题1" << endl;
		}

		template<class T>
		void Loading<T>::Backtrack(int i)
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

		template<class T>
		T MaxLoading(T *w, T c, int n)
		{
			Loading<T> x(w, c, n);
			x.Backtrack(0);
			return T();
		}

		// 5.2 装载问题
		template<class T>
		XLoading<T>::XLoading(T *w, T c, int n, int *bestx)
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

		template<class T>
		XLoading<T>::~XLoading()
		{
			delete[] x;
		}

		template<class T>
		void XLoading<T>::test()
		{
			cout << "5.2 装载问题2" << endl;
		}

		template<class T>
		void XLoading<T>::Backtrack(int i)
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

		template<class T>
		T MaxXLoading(T *w, T c, int n, int *bestx)
		{
			XLoading<T> x(w, c, n, bestx);
			x.Backtrack(0);
			return x.bestw;
		}

		// 5.2 装载问题
		template<class T>
		T MaxMLoading(T *w, T c, int n, int *bestx) {
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
		template<class T>
		void Swap(T &a, T &b) {
			T t = a;
			a = b;
			b = t;
		}

		int Flow(int **M, int n, int *bestx)
		{
			Flowshop x(M, n, bestx);
			x.Backtrack(0);
			return x.bestf;
		}

		Flowshop::Flowshop(int **M, int n, int *bestx)
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
			cout << "5.3 批处理作业调度" << endl;
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

		// 测试
		void test() {
			cout << "第五章 回溯法" << endl;
			Loading<int>::test();
			XLoading<int>::test();
			Flowshop::test();
			getchar();
		}
	}

	void test() {
		DivideAndConquer::test();
		DynamicProgramming::test();
		Backtracking::test();
	}
}

void main()
{
	Algorithm::test();
	getchar();
}