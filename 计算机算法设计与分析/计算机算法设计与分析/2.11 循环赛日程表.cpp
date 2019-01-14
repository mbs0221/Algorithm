#include "第二章 递归与分治策略.h"

using namespace std;

namespace DivideAndConquer {

	// 循环赛
	namespace RoundRobin {

		void Table(int k, int **a) {
			int n = 1;
			for (int i = 0; i < k; i++) n *= 2;
			for (int i = 0; i < n; i++)a[1][i] = i;
			int m = 1;
		}
	};

	void test_2_11() {
		cout << "2.11 循环赛日程表" << endl;
	}
}