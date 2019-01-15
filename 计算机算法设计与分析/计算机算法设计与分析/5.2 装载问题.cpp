template<class T>
class Loading {
public:
	Loading(T[] w, T c, int n);
	~Loading();
	friend T MaxLoading(T[], T, int);

private:
	void Backtrack(int n);
	int n; // ��װ����
	T *w, c, cw, bestw; // ��װ���������飬ÿһ���ִ�������������ǰ����������ǰ����������
};

template<class T>
class XLoading
{
public:
	XLoading(T[] w, T c, int n, int[] bestx);
	~XLoading();
	friend T MaxXLoading(T[], T, int, int[] bestx);

private:
	void Backtrack(int i);
	int n; // ��װ����
	int *x, *bestx; // ��ǰ�⣬��ǰ���Ž�
	T *w, c, cw, bestw; // ��װ���������飬ÿһ���ִ�������������ǰ����������ǰ����������
	T r; // ʣ�༯װ������
};

// Loading

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

template<class T> void Loading<T>::Backtrack(int i)
{
	if (i > n) {
		if (cw > bestw) {
			bestw = cw;
			return;
		}
	}
	// ��������
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

// XLoading

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

template<class T> void XLoading<T>::Backtrack(int i)
{
	if (i > n) { // ����Ҷ�ڵ�
		for (int j = 0; j < n; j++) {
			bestx[j] = x[j];
		}
		bestw = cw;
		return;
	}

	// ��������
	r -= w[i];
	if (cw + w[i] < c) { // x[i] = 1
		x[i] = 1; // װx[i]
		cw += w[i];
		Backtrack(i + 1);
		cw -= w[i];
	}

	if (cw + r > bestw) { // x[i] = 0
		x[i] = 0; // ��װx[i]
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

// MLoading
template<class T> T MaxXLoading(T w[], T c, int n, int[] bestx) {
	// ��������������������Ӧ�⣬��ʼ�����ڵ�

	int i = 0; // ��ǰ��
	int *x = new int[n + 1]; // ����·��
	T bestw = 0; // ��ǰ����������
	T cw = 0; // ��ǰ������
	T r = 0; // ʣ�༯װ������
	for (int j = 0; j < n; j++) {
		r += w[j];
	}
	
	while (true) {
		// ����������
		while (i < n&& cw + w[i] <= c) {
			r -= w[i];
			cw += w[i];
			x[i] = 1;
			i++;
		}
		
		// ����Ҷ�ڵ�
		if (i >= n) {
			for (int j = 0; j < n; j++) {
				bestx[j] = x[j];
			}
		} else {
			// ����������
			r -= w[i];
			x[i] = 0;
			i++;
		} 

		// ��֦����
		while (cw + r < bestw) {
			// ������������
			i--;
			while (i > 0 && !x[i]) {
				r += w[i];
				i--;
			}
			if (i == 0) {
				delete[] x;
				return bestw;
			}
			// ����������
			x[i] = 0;
			cw -= w[i];
			i++;
		}
	}
}