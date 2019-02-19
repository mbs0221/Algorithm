#ifndef _SORT_H_
#define _SORT_H_

template<class T>
class Sort{
private:
	static int THRESHOLD = 28;
	//交换元素
	void swap(T &a, T &b)
	{
		T temp;
		temp = a;
		a = b;
		b = temp;
	}
	//调整堆
	void heap_adjust(T array[], int i, int n)
	{
		int lchild = 2 * i + 1;//左子节点
		int rchild = 2 * i + 2;//右子节点
		int max = i;//根结点
		if (lchild < n&&array[lchild] > array[max])
		{
			max = lchild;
		}//左子大
		if (rchild < n&&array[rchild] > array[max])
		{
			max = rchild;
		}//右子大
		if (max != i)
		{
			swap(array[i], array[max]);
			heap_adjust(array, max, n);
		}//不符合堆序性，交换元素，继续调整
	}
	//初始建堆
	void build_heap(T array[], int n)
	{
		for (int i = (n - 1) / 2; i >= 0; i--)
		{
			heap_adjust(array, i, n);
		}//父节点向下调整
	}
	//分割函数
	void partition(T array[], int left, int right) {
		int l = left;
		int r = right;
		T temp = array[r];//将轴值存放在临时变量
		while (l != r) {
			// l指针向右移动，越过那些小于等于轴值的记录，直到找到第一个大于轴值的记录
			while (array[l] <= temp&&r > l)l++;
			//若l、r尚未相遇，将逆置元素换到右边的空位，r指针向左移动
			if (l < r) { array[r] = array[l]; r--; }
			// l指针向左移动，越过那些大于等于轴值的记录，直到找到第一个小于轴值的记录
			while (array[r] >= temp&&r > l)r--;
			//若l、r尚未相遇，将逆置元素换到左边的空位，l指针向右移动
			if (l < r) { array[l] = array[r]; l++; }
		}
		array[l] = temp;// 将轴值回填到分界位置l
		return l;// 返回分界位置l
	}
	//合并有序序列
	void merge(T array[], T temp[], int left, int middle, int right)
	{
		int i = left, j = middle + 1, k = left;
		while (i <= middle&&j <= right)
		{
			if (array[i] <= array[j])// 为保证稳定性，相等时左边优先
				temp[k++] = array[i++];// 左边大，复制左边的
			else
				temp[k++] = array[j++];// 右边大，复制右边的
		}
		while (i <= middle){ temp[k++] = array[i++]; }//左边有剩余，直接添加到末尾
		while (j <= right){ temp[k++] = array[j++]; }//右边有剩余，直接添加到末尾
		for (i = left; i <= right; i++){ array[i] = temp[i]; }
	}
public:
	//插入排序
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
	//shell排序
	void shell_sort(T array[], int n)
	{
		int delta = n / 2;//增量
		while (delta != 0)//条件
		{
			//初始位置
			for (int i = 0; i < delta; i++)
			{
				//插入排序
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
	//选择排序
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
	//堆排序
	void heap_sort(T array[], int n)
	{
		build_heap(array, n);
		for (int i = n - 1; i > 0; i--){
			swap(array[0], array[i]);
			heap_adjust(array, 0, i - 1);
		}
	}
	//冒泡排序
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
	//快速排序
	void quick_sort(T array[], int left, int right){
		if (right <= left)return;
		int pivot = (left + right) / 2;			// 选择轴值
		swap(array, pivot, right);				// 分隔前先将轴值放到数组末端
		pivot = partition(array, left, right);	// 分割后轴值已经到达正确的位置
		quick_sort(array, left, pivot - 1);		// 对轴值左边的子序列进行递归快速排序
		quick_sort(array, pivot + 1, right);	// 对轴值右边的子序列进行递归快速排序
	}
	//插入优化快排
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
	//桶式排序
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
	//顺序方法的基数排序
	void radix_sort(T array[], int n, int d, int r) 
	{
		T *temp = new T[n];
		int *count = new int[r];
		int i, j, k;
		int radix = 1;
		// 分别对第i个排序码进行排序
		for (i = 0; i < d;i++) {
			// 初始化计数器
			for (j = 0; j < r; j++) {
				count[j] = 0;
			}
			// 统计每个桶的记录数
			for (j = 0; j < n; j++) {
				k = (array[j] / radix) % r;
				count[k]++;
			}
			// 将temp中的位置依次分配给r个桶
			for (j = 1; j < r; j++) {
				count[j] = count[j - 1] + count[j];
			}
			// 从数组尾部，把记录收集到相应桶
			for (j = n - 1; j >= 0; j--) {
				k = (array[j] / radix) % r;
				count[k]--;
				temp[count[k]] = array[j];
			}
			// 将临时数组中的内容复制到array中
			for (j = 0; j < n; j++) {
				array[j] = temp[j];
			}
			radix *= r;
		}
		delete []temp;
		delete []count;
	}
	//索引排序
	void index_sort(T array[], int n) {
		int i, j;
		int *index = new int[n];
		// 初始化下标索引
		for (i = 0; i < n; i++){
			index[i] = i;
		}
		// 简单插入排序的地址排序过程
		for (i = 1; i < n; i++) {
			for (j = i; j > 0; j--) {// 依次比较，发现逆置就交换
				if (array[index[j]] < array[index[j - 1]])
					swap(index[j], index[j - 1]);
				else 
					break;
			}
		}
		// 利用索引数字进行循环调整
		T temp;
		for (i = 0; i < n; i++) {
			j = i;
			temp = array[i];//暂存i下标当前的记录
			while (index[j] != i) {//如果循环链中索引下标还不是i，则顺链循环调整
				int k = index[j];//k为链接j指向的下标
				array[j] = array[k];//把k中的值赋给j位，第j大元素正确归位
				index[j] = j;//因为是正确归位，索引j就是自身
				j = k;//j转到循环链的下一个，继续处理
			}
			array[j] = temp;//最后找到的j其索引下标志为i，因此第i大元素顺利归位
			index[j] = j;//因为是正确归位，索引j就是自身
		}
	}
};

#endif