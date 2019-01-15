template<class T>
class Loading {
public:
	Loading(T[] w, T c, int n);
	~Loading();
	friend T MaxLoading(T[], T, int);

private:
	void Backtrack(int n);
	int n; // 集装箱数
	T *w, c, cw, bestw; // 集装箱重量数组，每一艘轮船的载重量，当前载重量，当前最优载重量
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
	int n; // 集装箱数
	int *x, *bestx; // 当前解，当前最优解
	T *w, c, cw, bestw; // 集装箱重量数组，每一艘轮船的载重量，当前载重量，当前最优载重量
	T r; // 剩余集装箱重量
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

// MLoading
template<class T> T MaxXLoading(T w[], T c, int n, int[] bestx) {
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
		} else {
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