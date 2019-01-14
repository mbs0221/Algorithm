#include "������ ��̬�滮.h"

using namespace std;

namespace DynamicProgramming {

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
	}

	/**
	* ��ʼ������
	* rows ����
	* cols ����
	*/
	int **InitMatrix(int rows, int cols) {
		int **mat = new int*[rows];
		for (int i = 0; i < rows; i++) {
			mat[i] = new int[cols];
			for (int j = 0; j < cols; j++) {
				mat[i][j] = 0;
			}
		}
		return mat;
	}

	void test_3_1()
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
