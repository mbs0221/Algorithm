#include "计算机算法设计与分析.h"

using namespace std;

namespace Algorithm {

	template<class T>
	Matrix<T>::Matrix(int size)
	{
		row = col = size;
		mat = new T*[row];
		for (int i = 0; i < row; i++) {
			mat[i] = new T[col];
			for (int j = 0; j < col; j++) {
				mat[i][j] = -1;
			}
		}
	}

	template<class T>
	Matrix<T>::Matrix(int r, int c)
	{
		row = r, col = c;
		mat = new T*[row];
		for (int i = 0; i < row; i++) {
			mat[i] = new T[col];
			for (int j = 0; j < col; j++) {
				mat[i][j] = -1;
			}
		}
	}

	template<class T>
	T* Matrix<T>::operator [](int i)
	{
		return mat[i];
	}

	template<class T>
	void Matrix<T>::Print() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				std::cout << std::setw(8) << mat[i][j];
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
		ChessBoard::ChessBoard(int n)
		{
			size = n;
			board = Matrix<int>(n);
		}

		void ChessBoard::Init(int dr, int dc) {
			tile = 0;
			board[dr][dc] = tile++;
		}

		void ChessBoard::Solve(int tr, int tc, int dr, int dc, int size)
		{
			if (size == 1) {
				return;
			}
			int t = tile++;
			int sz = size / 2;
			// 覆盖左上角子棋盘
			if (dr < tr + sz && dc < tc + sz) {
				// 特殊方格在此棋盘中
				Solve(tr, tc, dr, dc, sz);
			}
			else {
				// 此棋盘无特殊方格，用t号L型骨牌覆盖右下角
				board[tr + sz - 1][tc + sz - 1] = t;
				// 覆盖其余方格
				Solve(tr, tc, tr + sz - 1, tc + sz - 1, sz);
			}

			// 覆盖右上角子棋盘
			if (dr < tr + sz && dc >= tc + sz) {
				// 特殊方格在此棋盘中
				Solve(tr, tc + sz, dr, dc, sz);
			}
			else {
				// 此棋盘无特殊方格，用t号L型骨牌覆盖左下角
				board[tr + sz - 1][tc + sz] = t;
				// 覆盖其余方格
				Solve(tr, tc + sz, tr + sz - 1, tc + sz, sz);
			}

			// 覆盖左下角子棋盘
			if (dr >= tr + sz && dc < tc + sz) {
				// 特殊方格在此棋盘中
				Solve(tr + sz, tc, dr, dc, sz);
			}
			else {
				// 用t号L型骨牌覆盖右上角
				board[tr + sz][tc + sz - 1] = t;
				// 覆盖其余方格
				Solve(tr + sz, tc, tr + sz, tc + sz - 1, sz);
			}

			// 覆盖右下角子棋盘
			if (dr >= tr + sz&& dc >= tc + sz) {
				// 特殊方格在此棋盘中
				Solve(tr + sz, tc + sz, dr, dc, sz);
			}
			else {
				// 用t号L型骨牌覆盖左上角
				board[tr + sz][tc + sz] = t;
				// 覆盖其余方格
				Solve(tr + sz, tc + sz, tr + sz, tc + sz, sz);
			}
		}

		void ChessBoard::Print()
		{
			board.Print();
		}

		void ChessBoard::test()
		{
			int size, dr, dc;
			std::cout << "2.6 棋盘覆盖" << std::endl;
			std::cout << "请输入：size，dr，dc" << std::endl;
			std::cin >> size >> dr >> dc;
			std::cout << "棋盘覆盖" << std::endl;
			ChessBoard solver(size);
			solver.Init(dr, dc);
			solver.Solve(0, 0, dr, dc, size);
			std::cout << "覆盖结果" << std::endl;
			solver.Print();
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

		template<class T>
		MatrixChain<T>::MatrixChain()
		{
		}

		template<class T>
		void MatrixChain<T>::AddMatrix(Matrix<T> & m)
		{
			chain.push_back(m);
		}

		template<class T>
		void MatrixChain<T>::Solve() {
			int n = chain.size();
			// 矩阵链长度r递增的顺序
			for (int r = 1; r < n; r++) {
				// 对于每一对r长的矩阵链（i，j）
				for (int i = 0; i < n - r; i++) {
					int j = i + r;// 右界
					m[i][j] = m[i + 1][j] + chain[i].GetRowCount()*chain[i].GetColumnCount()*chain[j].GetColumnCount(); // 计算次数
					s[i][j] = i; // 从i处断开
					for (int k = i + 1; k < j; k++) {
						// 从k断开
						int t = m[i][k] + m[k + 1][j] + chain[i].GetRowCount()*chain[k].GetColumnCount()*chain[j].GetColumnCount();
						if (t < m[i][j]) {
							m[i][j] = t; // 记录新的最小值
							s[i][j] = k; // 记录（i，j）断开的位置
						}
					}
				}
			}
		}

		template<class T>
		void MatrixChain<T>::Print()
		{
			int n = chain.size();
			TraceBack(0, n - 1, s);
			// 输出求解
			cout << "m[i][j]" << endl;
			m.Print();
			cout << "s[i][j]" << endl;
			s.Print();
		}

		template<class T>
		void MatrixChain<T>::PrintChain()
		{
			for (Matrix<T> m : chain) {
				cout << m;
			}
			cout << endl;
		}

		template<class T>
		void MatrixChain<T>::TraceBack(int i, int j, Matrix<int> & s)
		{
			if (i == j) return;
			TraceBack(i, s[i][j], s); // （i，j）断开位置的左边
			TraceBack(s[i][j] + 1, j, s); // （i，j）断开位置的右边
			printf("Chain(%d,%d) = Chain(%d,%d) * Chain(%d,%d)\n", i, j, i, s[i][j], s[i][j] + 1, j);
		}

		template<class T>
		int MatrixChain<T>::Count(Matrix<T> & a, Matrix<T> & b)
		{
			return a.row*b.row*b.col;
		}

		template<class T>
		void MatrixChain<T>::test()
		{
			cout << "3.1 矩阵连乘问题" << endl;
			MatrixChain<T> mat;
			mat.AddMatrix(Matrix<T>(30, 35));
			mat.AddMatrix(Matrix<T>(35, 15));
			mat.AddMatrix(Matrix<T>(15, 5));
			mat.AddMatrix(Matrix<T>(5, 10));
			mat.AddMatrix(Matrix<T>(10, 20));
			mat.AddMatrix(Matrix<T>(20, 25));
			// 新增两个矩阵
			mat.AddMatrix(Matrix<T>(25, 35));
			mat.AddMatrix(Matrix<T>(35, 15));
			mat.PrintChain();
			mat.Solve();
			mat.Print();
			cout << "求解完毕" << endl;
		}

		// 3.3 最长公共子序列

		void LCS::Solve(string a, string b, Matrix<int> & c, Matrix<int> & s) {
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

		void LCS::Print(string a, string b, Matrix<int> & s)
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

		void LCS::test() {
			string a = "ABCBDAB";
			string b = "BDCABA";
			Matrix<int> c(a.length(), b.length());
			Matrix<int> s(a.length(), b.length());
			cout << "3.3 最长公共子序列" << endl;
			cout << "a:" << a << endl;
			cout << "b:" << b << endl;
			cout << "Solve" << endl;
			LCS solver;
			solver.Solve(a, b, c, s);
			cout << "PrintLCS" << endl;
			solver.Print(a, b, s);
		}

		// 3.4 最大子段和

		int MaxSubSum::Solve(int n, int *a, int &besti, int &bestj)
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

		int MaxSubSum::SolveDC(int *a, int left, int right)
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

		int MaxSubSum::SolveDP(int *a, int left, int right)
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

		void MaxSubSum::test()
		{
			int a[] = { -2, 11,-4, 13, -5, -2 };
			int sum, besti, bestj;
			cout << "3.4 最大子段和" << endl;
			MaxSubSum solver;
			sum = solver.Solve(6, a, besti, bestj);
			cout << "Simple Solution:" << setw(4) << sum << endl;
			sum = solver.SolveDC(a, 0, 5);
			cout << "Divide and Conquer:" << setw(4) << sum << endl;
			sum = solver.SolveDP(a, 0, 6);
			cout << "Dynamic Programming:" << setw(4) << sum << endl;
		}

		// 3.11 最优二叉搜索树
		void OptimalBST::Solve()
		{
			for (int i = 0; i < n; i++) {
				w[i + 1][0] = w[i][0];
				m[i + 1][0] = 0;
			}
			for (int r = 0; r < n; r++) {
				for (int i = 0; i < n - r; i++) {
					int j = i + r;
					w[i][j] = w[i][j - 1] + a[j][0] + b[j][0];
					m[i][j] = m[i + 1][j];

				}
			}
		}

		// KMP 算法
		void GetNextVal(char *p, int next[]) {
			int len = strlen(p);
			next[0] = -1;
			int i = -1;
			int j = 0;
			while (j < len) {
				if (i == -1 || p[i] == p[j]) {
					i++, j++;
					if (p[i] != p[j])
						next[j] = i;
					else
						next[j] = next[i];
				}
				else {
					i = next[i];
				}
				printf("%3d --- %3d --- %3d\n", i, j, next[j]);
			}
		}
		
		// 编辑距离
		int String::EditDistance(string a, string & b)
		{
			int m = a.length();
			int n = b.length();
			Matrix<int> dist(m + 1, n + 1);
			for (int i = 0; i < m + 1; i++)
				dist[i][0] = i;
			for (int j = 0; j < n; j++)
				dist[0][j] = j;
			auto min = [](int a, int b)->bool {return a < b; };
			//auto amin = [](int a[], int n)->bool {return amin(a, n - 1) < a[n]; };
			auto f = [](int a, int b)->int {return a == b ? 0 : 1; };
			for (int i = 1; i <= m; i++) {
				for (int j = 1; j <= n; j++) {
					dist[i][j] = min(dist[i - 1][j] + 1, min(dist[i][j - 1] + 1, dist[i - 1][j - 1] + f(a[i], b[j])));
				}
			}
			return dist[m][n];
		}

		void String::test() {
			char p[] = "abab";
			int next[4];
			GetNextVal(p, next);
			getchar();
		}

		// 测试
		void test()
		{
			cout << "第三章 动态规划" << endl;
			MatrixChain<double>::test();
			LCS::test();
			MaxSubSum::test();
			String::test();
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

		// 骑士巡游

		BoxPop::BoxPop()
		{
		}

		BoxPop::BoxPop(int m, int n)
		{
			this->m = m;
			this->n = n;
			grid = new int*[m];
			for (int i = 0; i < m; i++) {
				grid[i] = new int[n];
				for (int j = 0; j < n; j++) {
					grid[i][j] = 0;
				}
			}
		}

		void BoxPop::Solve(int i, int j)
		{
			Backtracking(i, j, 1);
		}

		void BoxPop::Show()
		{
			for (Vector<int> p : path) {
				std::cout << p;
			}
			std::cout << std::endl;
		}

		void BoxPop::test()
		{
			// 骑士巡游
			std::cout << "骑士巡游" << std::endl;
			BoxPop bp(5, 5);
			bp.Solve(0, 0);
			std::cout << "搜索完毕" << std::endl;
			getchar();
		}

		void BoxPop::Backtracking(int x, int y, int step)
		{
			// 访问（x，y）
			grid[x][y] = step;
			path.push_back(Vector<int>(x, y));
			// 输出path
			if (step == m*n) {
				Show();
				return;
			}
			// 深度优先遍历
			for (int i = 0; i < 8; i++) {
				int next_x = x + dirs[i][0];
				int next_y = y + dirs[i][1];
				if (IsValid(next_x, next_y)) {
					// 访问（next_x, next_y）
					Backtracking(next_x, next_y, step + 1);
				}
			}
			// 回溯
			path.pop_back();
			grid[x][y] = 0;
		}

		bool BoxPop::IsValid(int i, int j)
		{
			return !(i < 0 || j < 0 || i >= m || j >= n || grid[i][j] > 0);
		}

		// 素数环

		bool PrimeRing::isPrime(int num)
		{
			return prime[num];
		}

		PrimeRing::PrimeRing()
		{
			for (int i = 0; i < 100; i++)
				prime[i] = true;
			for (int i = 2; i < 100; i++)
				if (prime[i])
					for (int j = 2 * i; j < 100; j += i)
						prime[j] = false;
		}

		void PrimeRing::Solve(int n)
		{
			// 素数环初始化
			number = n;
			table = new int[n];
			visited = new bool[n];
			memset(visited, false, sizeof(bool)*n);
			// 回溯
			table[0] = 1;
			visited[0] = true;
			Backtracking(1);
			// 清理空间
			delete[] table;
			delete[] visited;
		}

		void PrimeRing::Backtracking(int step)
		{
			// 输出结果
			if (step == number) {
				if (isPrime(table[0] + table[number - 1])) {
					Print();
					return;
				}
			}
			// 深搜
			for (int i = 1; i < number; i++) {
				table[step] = i + 1;
				if (visited[i] == false && isPrime(table[step - 1] + table[step])) {
					visited[i] = true;
					Backtracking(step + 1);
					visited[i] = false;
				}
			}
		}

		void PrimeRing::Print()
		{
			cout << table[0];
			for (int i = 1; i < number; i++) {
				cout << " " << table[i];
			}
			cout << endl;
		}

		void PrimeRing::test()
		{
			int num, Case = 1;
			PrimeRing solver;
			do {
				cin >> num;
				if (num > 0 && num < 20) {
					cout << "Case " << Case++ << ":" << endl;
					solver.Solve(num);
					cout << endl;
				}
			} while (num > 0 && num < 20);
		}

		void main() {
			PrimeRing::test();
		}

		// 测试

		void test() {
			cout << "第五章 回溯法" << endl;
			//Loading<int>::test();
			//XLoading<int>::test();
			//Flowshop::test();
			//BoxPop::test();
			PrimeRing::test();
		}
	}

	namespace DataMining {

		// FP-Tree
		void FPTree::put(string item)
		{
			if (table.find(item) == table.end()) {
				table[item] = new Item(table.size(), 1);
				cout << "add item: " << item << " freq:" << table[item]->getFrequency() << endl;
			}
			else {
				table[item]->increase();
				cout << "update item: " << item << " freq:" << table[item]->getFrequency() << endl;
			}
		}

		void FPTree::build(list<string> ts)
		{
			//sort(table.begin(), table.end());
			// transform
			list<list<string>> rows;
			regex exp("(\\w+)");
			smatch m;
			for (auto line : ts) {
				string::const_iterator iterStart = line.begin();
				string::const_iterator iterEnd = line.end();
				list<string> row;
				while (regex_search(iterStart, iterEnd, m, exp)) {
					row.push_back(m[0]);
					iterStart = m[0].second;
				}
				rows.push_back(row);
			}
			// 1. 扫描数据库一次，得到频繁1-项集
			for (auto row : rows) {
				for (auto item : row) {
					put(item);
				}
			}
			// show 
			for (auto row : table) {
				Item *item = row.second;
				row.second->setSupport(item->getFrequency() / ((double)rows.size()));
				printf("%-12s: %3d --- %3d --- %.2f\n", row.first, item->getId(), item->getFrequency(), item->getSupport());
			}
			// 2. 把项按支持度递减排序
			auto pred = [this](string &a, string &b) { 
				auto vala = *table[a];
				auto valb = *table[b];
				if (vala > valb) {
					return true;
				} else {
					return a <= b;
				}
			}					;
			auto cond = [this](string &a) {return (*table[a]).getSupport() < 0.5; };
			for (auto row : rows) {
				row.remove_if(cond);
				row.sort(pred);
				for (auto item : row) {
					cout << item <<" ";
				}
				cout << endl;
			}
			// 3. 再一次扫描数据库，建立FP-tree
			for (auto row : rows) {
				for (auto item : row) {
					 
				}
			}
		}

		void FPTree::test() {
			list<string> transactions;
			readlines(transactions, "Transactions.txt");
			FPTree t;
			t.build(transactions);
		}
		

		void readlines(list<string> &lines, string file) {
			ifstream f(file);
			if (!f.is_open()) {
				cout << "open failed" << endl;
			}
			string line;
			while (getline(f, line)) {
				lines.push_back(line);
			}
		}

		void test()
		{
			FPTree::test();
		}
	}

	void test() {
		//DivideAndConquer::test();
		//DynamicProgramming::test();
		//Backtracking::test();
		DataMining::test();
	}
}

void main()
{
	Algorithm::test();
	getchar();
}