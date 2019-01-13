
void MatrixChain(int *p, int **m, int **s, int n) {
	for (int i = 0; i < n; i++)m[i][i] = 0;
	// ����ÿһ��
	for (int r = 1; r < n; r++)
		// ����ÿһ�ַָ��
		for (int i = 0; i <= n - r; i++) {
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