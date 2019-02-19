#ifndef _SORT_H_
#define _SORT_H_

template<class T>
class Sort{
private:
	static int THRESHOLD = 28;
	//����Ԫ��
	void swap(T &a, T &b)
	{
		T temp;
		temp = a;
		a = b;
		b = temp;
	}
	//������
	void heap_adjust(T array[], int i, int n)
	{
		int lchild = 2 * i + 1;//���ӽڵ�
		int rchild = 2 * i + 2;//���ӽڵ�
		int max = i;//�����
		if (lchild < n&&array[lchild] > array[max])
		{
			max = lchild;
		}//���Ӵ�
		if (rchild < n&&array[rchild] > array[max])
		{
			max = rchild;
		}//���Ӵ�
		if (max != i)
		{
			swap(array[i], array[max]);
			heap_adjust(array, max, n);
		}//�����϶����ԣ�����Ԫ�أ���������
	}
	//��ʼ����
	void build_heap(T array[], int n)
	{
		for (int i = (n - 1) / 2; i >= 0; i--)
		{
			heap_adjust(array, i, n);
		}//���ڵ����µ���
	}
	//�ָ��
	void partition(T array[], int left, int right) {
		int l = left;
		int r = right;
		T temp = array[r];//����ֵ�������ʱ����
		while (l != r) {
			// lָ�������ƶ���Խ����ЩС�ڵ�����ֵ�ļ�¼��ֱ���ҵ���һ��������ֵ�ļ�¼
			while (array[l] <= temp&&r > l)l++;
			//��l��r��δ������������Ԫ�ػ����ұߵĿ�λ��rָ�������ƶ�
			if (l < r) { array[r] = array[l]; r--; }
			// lָ�������ƶ���Խ����Щ���ڵ�����ֵ�ļ�¼��ֱ���ҵ���һ��С����ֵ�ļ�¼
			while (array[r] >= temp&&r > l)r--;
			//��l��r��δ������������Ԫ�ػ�����ߵĿ�λ��lָ�������ƶ�
			if (l < r) { array[l] = array[r]; l++; }
		}
		array[l] = temp;// ����ֵ����ֽ�λ��l
		return l;// ���طֽ�λ��l
	}
	//�ϲ���������
	void merge(T array[], T temp[], int left, int middle, int right)
	{
		int i = left, j = middle + 1, k = left;
		while (i <= middle&&j <= right)
		{
			if (array[i] <= array[j])// Ϊ��֤�ȶ��ԣ����ʱ�������
				temp[k++] = array[i++];// ��ߴ󣬸�����ߵ�
			else
				temp[k++] = array[j++];// �ұߴ󣬸����ұߵ�
		}
		while (i <= middle){ temp[k++] = array[i++]; }//�����ʣ�ֱ࣬����ӵ�ĩβ
		while (j <= right){ temp[k++] = array[j++]; }//�ұ���ʣ�ֱ࣬����ӵ�ĩβ
		for (i = left; i <= right; i++){ array[i] = temp[i]; }
	}
public:
	//��������
	void insert_sort(T array[], int n)
	{
		T temp;
		int i, j;
		for (i = 1; i < n; i++)
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
	void shell_sort(T array[], int n)
	{
		int delta = n / 2;//����
		while (delta != 0)//����
		{
			//��ʼλ��
			for (int i = 0; i < delta; i++)
			{
				//��������
				for (int j = i; j < n; j += delta)
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
	void select_sort(T array[], int n)
	{
		T small;
		for (int i = 0; i < n - 1; i++)
		{
			small = i;
			for (int j = i + 1; j < n; j++)
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
	void heap_sort(T array[], int n)
	{
		build_heap(array, n);
		for (int i = n - 1; i > 0; i--){
			swap(array[0], array[i]);
			heap_adjust(array, 0, i - 1);
		}
	}
	//ð������
	void bubble_sort(T array[], int n)
	{
		bool noswap;
		int i, j;
		for (i = 0; i < n - 1; i++)
		{
			noswap = true;
			for (j = n - 1; j>i; j--)
			{
				if (array[j] < array[j - 1])
				{ 
					swap(array[j], array[j - 1]);
					noswap = false; 
				}
			}
			if (noswap)return;
		}
	}
	//��������
	void quick_sort(T array[], int left, int right){
		if (right <= left)return;
		int pivot = (left + right) / 2;			// ѡ����ֵ
		swap(array, pivot, right);				// �ָ�ǰ�Ƚ���ֵ�ŵ�����ĩ��
		pivot = partition(array, left, right);	// �ָ����ֵ�Ѿ�������ȷ��λ��
		quick_sort(array, left, pivot - 1);		// ����ֵ��ߵ������н��еݹ��������
		quick_sort(array, pivot + 1, right);	// ����ֵ�ұߵ������н��еݹ��������
	}
	//�����Ż�����
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
	//Ͱʽ����
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
	//˳�򷽷��Ļ�������
	void radix_sort(T array[], int n, int d, int r) 
	{
		T *temp = new T[n];
		int *count = new int[r];
		int i, j, k;
		int radix = 1;
		// �ֱ�Ե�i���������������
		for (i = 0; i < d;i++) {
			// ��ʼ��������
			for (j = 0; j < r; j++) {
				count[j] = 0;
			}
			// ͳ��ÿ��Ͱ�ļ�¼��
			for (j = 0; j < n; j++) {
				k = (array[j] / radix) % r;
				count[k]++;
			}
			// ��temp�е�λ�����η����r��Ͱ
			for (j = 1; j < r; j++) {
				count[j] = count[j - 1] + count[j];
			}
			// ������β�����Ѽ�¼�ռ�����ӦͰ
			for (j = n - 1; j >= 0; j--) {
				k = (array[j] / radix) % r;
				count[k]--;
				temp[count[k]] = array[j];
			}
			// ����ʱ�����е����ݸ��Ƶ�array��
			for (j = 0; j < n; j++) {
				array[j] = temp[j];
			}
			radix *= r;
		}
		delete []temp;
		delete []count;
	}
	//��������
	void index_sort(T array[], int n) {
		int i, j;
		int *index = new int[n];
		// ��ʼ���±�����
		for (i = 0; i < n; i++){
			index[i] = i;
		}
		// �򵥲�������ĵ�ַ�������
		for (i = 1; i < n; i++) {
			for (j = i; j > 0; j--) {// ���αȽϣ��������þͽ���
				if (array[index[j]] < array[index[j - 1]])
					swap(index[j], index[j - 1]);
				else 
					break;
			}
		}
		// �����������ֽ���ѭ������
		T temp;
		for (i = 0; i < n; i++) {
			j = i;
			temp = array[i];//�ݴ�i�±굱ǰ�ļ�¼
			while (index[j] != i) {//���ѭ�����������±껹����i����˳��ѭ������
				int k = index[j];//kΪ����jָ����±�
				array[j] = array[k];//��k�е�ֵ����jλ����j��Ԫ����ȷ��λ
				index[j] = j;//��Ϊ����ȷ��λ������j��������
				j = k;//jת��ѭ��������һ������������
			}
			array[j] = temp;//����ҵ���j�������±�־Ϊi����˵�i��Ԫ��˳����λ
			index[j] = j;//��Ϊ����ȷ��λ������j��������
		}
	}
};

#endif