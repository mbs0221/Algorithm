#include "第三章 动态规划.h"

using namespace std;

namespace DynamicProgramming {

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
	}

	void test_3_4()
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
};