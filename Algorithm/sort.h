#ifndef _SORT_H_
#define _SORT_H_

class Sort{
private:
	int THRESHOLD = 28;
	//����Ԫ��
	template<class T>
	void swap(T &a, T &b)
	{
		T temp;
		temp = a;
		a = b;
		b = temp;
	}
	//������
	template<class T>
	void heap_adjust(T array[], int i, int length)
	{
		int lchild = 2 * i + 1;//���ӽڵ�
		int rchild = 2 * i + 2;//���ӽڵ�
		int max = i;//�����
		if (lchild < length&&array[lchild] > array[max])
		{
			max = lchild;
		}//���Ӵ�
		if (rchild < length&&array[rchild] > array[max])
		{
			max = rchild;
		}//���Ӵ�
		if (max != i)
		{
			swap(array[i], array[max]);
			heap_adjust(array, max, length);
		}//�����϶����ԣ�����Ԫ�أ���������
	}
	//��ʼ����
	template<class T>
	void build_heap(T array[], int length)
	{
		for (int i = (length - 1) / 2; i >= 0; i--)
		{
			heap_adjust(array, i, length);
		}//���ڵ����µ���
	}
	//�ϲ���������
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
		while (i <= middle){ temp[k++] = array[i++]; }//�����ʣ�ֱ࣬����ӵ�ĩβ
		while (j <= right){ temp[k++] = array[j++]; }//�ұ���ʣ�ֱ࣬����ӵ�ĩβ
		for (i = left; i <= right; i++){ array[i] = temp[i]; }
	}
public:
	//��������
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
	//shell����
	template<class T>
	void shell_sort(T array[], int length)
	{
		int delta = length / 2;//����
		while (delta != 0)//����
		{
			//��ʼλ��
			for (int i = 0; i < delta; i++)
			{
				//��������
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
	//ѡ������
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
	//������
	template<class T>
	void heap_sort(T array[], int length)
	{
		build_heap(array, length);
		for (int i = length - 1; i > 0; i--){
			swap(array[0], array[i]);
			heap_adjust(array, 0, i - 1);
		}
	}
	//ð������
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
	//��������
	template<class T>
	void quick_sort(T array[], int left, int right)
	{
		if (left >= right)return;
		int first = left;
		int last = right;
		int key = array[first];//�ݴ�
		while (first < last)
		{
			while (first < last&&array[first] <= key)++first;//��ߴ���key���Ƶ��ұ�
			array[last] = array[first];
			while (first < last&&array[last] >= key)--last;//�ұ�С��key���Ƶ����
			array[first] = array[last];
		}
		array[first] = key;//��λ
		quick_sort(array, left, first - 1);
		quick_sort(array, first + 1, right);
	}
	//�����Ż�����
	template<class T>
	void mode_quick_sort(T array[], int left, int right)
	{
		if (left >= right){
			return;
		}
		else if (right - left + 1 > THRESHOLD){
			int first = left;
			int last = right;
			int key = array[first];//�ݴ�
			while (first < last){
				while (first < last&&array[last] >= key)--last;//�ұ�С��key���Ƶ����
				array[first] = array[last];
				while (first < last&&array[first] <= key)++first;//��ߴ���key���Ƶ��ұ�
				array[last] = array[first];
			}
			array[first] = key;//��λ
			quick_sort(array, left, first - 1);
			quick_sort(array, first + 1, right);
		}
		else{
			insert_sort(&array[left], right - left + 1);
		}
	}
	//�鲢����
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
	//�����Ż��鲢����
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
	//Ͱ����
	template<class T>
	void bucket_sort(T array[], int n, int max)
	{
		T* temp = new T[n];
		int *count = new int[max];
		int i;
		for (i = 0; i < n; i++)								//���и��Ƶ���ʱ����
			temp[i] = array[i];
		for (i = 0; i < max; i++)							//��������ʼ��Ϊ0
			count[i] = 0;
		for (i = 0; i < n; i++)								//ͳ��ÿ��ȡֵ���ֵĴ���
			temp[i] = count[array[i]]++;
		for (i = 1; i < max; i++)							//ͳ��С�ڵ���i��Ԫ�ظ���
			count[i] = count[i - 1] + count[i];
		for (i = n - 1 i >= 0; i--)							//��β��˳���������������ȶ���
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