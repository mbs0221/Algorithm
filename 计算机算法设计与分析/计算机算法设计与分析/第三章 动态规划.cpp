#include "������ ��̬�滮.h"

using namespace std;

namespace Algorithm {

	namespace DynamicProgramming {

		// 3.1 ������������
		namespace MatrixChain {

			void Solve(int *p, int **m, int **s, int n) {
				for (int i = 0; i < n; i++) m[i][i] = 0;
				// ����ÿһ��
				for (int r = 0; r < n; r++) {
					// ����ÿһ�ַָ��
					for (int i = 1; i <= n - r; i++) {
						int j = i + r - 1;
						m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
						s[i][j] = i;
						// Ѱ����ѷָ��
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
				// �����ά��
				int p[] = { 30, 35, 15, 5, 10, 20, 25 };
				int **m, **s;
				cout << "3.1 ������������" << endl;
				m = InitMatrix(6, 6);
				s = InitMatrix(6, 6);
				MatrixChain::Solve(p, m, s, 6);
				MatrixChain::TraceBack(0, 5, s);
				delete[] m;
				delete[] s;
			}
		}

		// 3.3 �����������
		namespace LongestCommonSubsequence {

			/* ����������� */
			void Solve(string a, string b, int **c, int **s) {
				int m = a.length();
				int n = b.length();
				// ��ʼ����1��
				for (int i = 0; i < m; i++)c[i][0] = a[i] == b[0] ? 1 : 0;
				// ��ʼ����1��
				for (int i = 0; i < n; i++)c[0][i] = a[0] == b[i] ? 1 : 0;
				// ��̬�滮
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

			/* ��ӡ����������� */
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

			/* 3.3 ��������������� */
			void test() {
				string a = "ABCBDAB";
				string b = "BDCABA";
				int **c, **s;
				c = InitMatrix(a.length(), b.length());
				s = InitMatrix(a.length(), b.length());
				cout << "3.3 �����������" << endl;
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

		// 3.4 ����Ӷκ�
		namespace MaxSubSum {

			/* ����Ӷκ�����ļ��㷨*/
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

			/* ����Ӷκ�����ķ����㷨*/
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
					// ��ߺ�
					int s1 = 0;
					int left_s = 0;
					for (int i = mid; i >= left; i--) {
						left_s += a[i];
						if (left_s > s1) {
							s1 = left_s;
						}
					}
					// �ұߺ�
					int s2 = 0;
					int right_s = 0;
					for (int i = mid + 1; i <= right; i++) {
						right_s += a[i];
						if (right_s > s2) {
							s2 = right_s;
						}
					}
					// �鲢���
					sum = s1 + s2;
					if (sum < left_sum) sum = left_sum;
					if (sum < right_sum) sum = right_sum;
				}
				return sum;
			}

			/* ����Ӷκ�����Ķ�̬�滮�㷨*/
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

			/* ����3.4 ����Ӷκ�*/
			void test()
			{
				int a[] = { -2, 11,-4, 13, -5, -2 };
				int sum, besti, bestj;
				cout << "3.4 ����Ӷκ�" << endl;
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
			cout << "������ ��̬�滮" << endl;
			MaxSubSum::test();
			MatrixChain::test();
			LongestCommonSubsequence::test();
			getchar();
		}
	}
}