#ifndef _SORT_H_
#define _SORT_H_

class Sort{
private:
	int THRESHOLD = 28;
	//交换元素
	template<class T>
	void swap(T &a, T &b)
	{
		T temp;
		temp = a;
		a = b;
		b = temp;
	}
	//调整堆
	template<class T>
	void heap_adjust(T array[], int i, int length)
	{
		int lchild = 2 * i + 1;//左子节点
		int rchild = 2 * i + 2;//右子节点
		int max = i;//根结点
		if (lchild < length&&array[lchild] > array[max])
		{
			max = lchild;
		}//左子大
		if (rchild < length&&array[rchild] > array[max])
		{
			max = rchild;
		}//右子大
		if (max != i)
		{
			swap(array[i], array[max]);
			heap_adjust(array, max, length);
		}//不符合堆序性，交换元素，继续调整
	}
	//初始建堆
	template<class T>
	void build_heap(T array[], int length)
	{
		for (int i = (length - 1) / 2; i >= 0; i--)
		{
			heap_adjust(array, i, length);
		}//父节点向下调整
	}
	//合并有序序列
	template<class T>
	void merge(T array[], T temp[], int left, int middle, int right)
	{
		int i = left, j = middle + 1, k = left;
		while (i <= middle&&j <= right)
		{
			if (array[i] > array[j])
				temp[k++] = array[i++];
			else
				temp[k++] = array[j++];
		}
		while (i <= middle){ temp[k++] = array[i++]; }//左边有剩余，直接添加到末尾
		while (j <= right){ temp[k++] = array[j++]; }//右边有剩余，直接添加到末尾
		for (i = left; i <= right; i++){ array[i] = temp[i]; }
	}
public:
	//插入排序
	template<class T>
	void insert_sort(T array[], int length)
	{
		T temp;
		int i, j;
		for (i = 1; i < length; i++)
		{
			temp = array[i];
			j = i - 1;
			while (j >= 0 && temp < array[j])
			{
				array[j + 1] = array[j];
				j--;
			}
			array[j + 1] = temp;
		}
	}
	//shell排序
	template<class T>
	void shell_sort(T array[], int length)
	{
		int delta = length / 2;//增量
		while (delta != 0)//条件
		{
			//初始位置
			for (int i = 0; i < delta; i++)
			{
				//插入排序
				for (int j = i; j < length; j += delta)
				{
					for (int k = j; k >= delta; k -= delta)
					{
						if (array[k] < array[k - delta])
							swap(array[k], array[k - delta]);
						else
							break;
					}
				}
			}
			delta = delta / 2;
		}
	}
	//选择排序
	template<class T>
	void select_sort(T array[], int length)
	{
		T small;
		for (int i = 0; i < length - 1; i++)
		{
			small = i;
			for (int j = i + 1; j < length; j++)
			{
				if (array[j] < array[i])
				{
					small = j;
				}
			}
			swap(array[i], array[small]);
		}
	}
	//堆排序
	template<class T>
	void heap_sort(T array[], int length)
	{
		build_heap(array, length);
		for (int i = length - 1; i > 0; i--){
			swap(array[0], array[i]);
			heap_adjust(array, 0, i - 1);
		}
	}
	//冒泡排序
	template<class T>
	void bubble_sort(T array[], int length)
	{
		bool noswap;
		int i, j;
		for (i = 0; i < length - 1; i++)
		{
			noswap = true;
			for (j = length - 1; j>i; j--)
			{
				if (array[j] < array[j - 1]){ swap(array[j], array[j - 1]); noswap = false; }
			}
			if (noswap)return;
		}
	}
	//快速排序
	template<class T>
	void quick_sort(T array[], int left, int right)
	{
		if (left >= right)return;
		int first = left;
		int last = right;
		int key = array[first];//暂存
		while (first < last)
		{
			while (first < last&&array[first] <= key)++first;//左边大于key的移到右边
			array[last] = array[first];
			while (first < last&&array[last] >= key)--last;//右边小于key的移到左边
			array[first] = array[last];
		}
		array[first] = key;//归位
		quick_sort(array, left, first - 1);
		quick_sort(array, first + 1, right);
	}
	//插入优化快排
	template<class T>
	void mode_quick_sort(T array[], int left, int right)
	{
		if (left >= right){
			return;
		}
		else if (right - left + 1 > THRESHOLD){
			int first = left;
			int last = right;
			int key = array[first];//暂存
			while (first < last){
				while (first < last&&array[last] >= key)--last;//右边小于key的移到左边
				array[first] = array[last];
				while (first < last&&array[first] <= key)++first;//左边大于key的移到右边
				array[last] = array[first];
			}
			array[first] = key;//归位
			quick_sort(array, left, first - 1);
			quick_sort(array, first + 1, right);
		}
		else{
			insert_sort(&array[left], right - left + 1);
		}
	}
	//归并排序
	template<class T>
	void merge_sort(T array[], T temp[], int left, int right)
	{
		int middle;
		if (left < right)
		{
			middle = (left + right) / 2;/*left + rand() % (right - left);*/
			merge_sort(array, temp, left, middle);
			merge_sort(array, temp, middle + 1, right);
			merge(array, temp, left, middle, right);
		}
	}
	//插入优化归并排序
	template<class T>
	void mode_merge_sort(T array[], T temp[], int left, int right)
	{
		int middle;
		if (right - left + 1 > THRESHOLD)
		{
			middle = (left + right) / 2;
			merge_sort(array, temp, left, middle);
			merge_sort(array, temp, middle + 1, right);
			merge(array, temp, left, middle, right);
		}
		else
		{
			insert_sort(&array[left], right - left + 1);
		}
	}
	//桶排序
	template<class T>
	void bucket_sort(T array[], int n, int max)
	{
		T* temp = new T[n];
		int *count = new int[max];
		int i;
		for (i = 0; i < n; i++)								//序列复制到临时数组
			temp[i] = array[i];
		for (i = 0; i < max; i++)							//计数器初始化为0
			count[i] = 0;
		for (i = 0; i < n; i++)								//统计每个取值出现的次数
			temp[i] = count[array[i]]++;
		for (i = 1; i < max; i++)							//统计小于等于i的元素个数
			count[i] = count[i - 1] + count[i];
		for (i = n - 1 i >= 0; i--)							//从尾部顺序输出保持排序的稳定性
			array[--count[temp[i]]] = temp[i];
	}
};

string lcs(const string str1, const string str2){
	int length = 0;
	int position = 0;
	vector<int> row0(str2.size());
	vector<int> row1(str2.size());
	for (int i = 0; i < str1.size(); i++){
		row1.assign(row0.size(), 0);
		for (int j = 0; j < str2.size(); j++){
			if (str2[j] == str1[i]){
				if (j == 0){
					row1[j] = 1;
				}
				else{
					row1[j] = row0[j - 1] + 1;
				}
				if (row1[j]>length){
					length = row1[j];
					position = j;
				}
			}
		}
		row0.assign(row1.begin(), row1.end());
	}
	return str2.substr(position - length + 1, length);
}

string lcs2(const string str1, const string str2){
	int **matrix, length, x, y;
	matrix = new int*[str1.size()];
	length = 0;
	for (int i = 0; i < str1.size(); i++){
		matrix[i] = new int[str2.size()];
		for (int j = 0; j < str2.size(); j++){
			if (str2[j] == str1[i]){
				if (i > 0 || j > 0){
					matrix[i][j] = matrix[i - 1][j - 1] + 1;
				}
				else{
					matrix[i][j] = 1;
				}
				if (matrix[i][j]>length){
					length = matrix[i][j];
					x = j, y = i;
				}
			}
		}
	}
	return str2.substr(y - length + 1, length);
}

long int gcd(long int a, long int b)
{
	long int c;

	while (b){
		c = a%b;
		a = b;
		b = c;
	}
	return a;
}

long int lcm(long int a, long int b)
{
	return (a*b) / gcd(a, b);
}

#endif