#include "第三章 动态规划.h"

using namespace std;

namespace DynamicProgramming {

	namespace LongestCommonSubsequence {

		/**
		 * 最长公共子序列
		 *
		 */
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

		/**
		 * 打印最长公共子序列
		 * 
		 */
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
	}

	void test_3_3() {
		string a = "ABCBDAB";
		string b = "BDCABA";
		int **c, **s;
		c = DynamicProgramming::InitMatrix(a.length(), b.length());
		s = DynamicProgramming::InitMatrix(a.length(), b.length());
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