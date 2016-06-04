#ifndef _SORT_H_
#define _SORT_H_

class Sort{
private:
	int THRESHOLD = 28;
	//交换元素
	template<class T>
	void swap(T &a, T &b);
	//调整堆
	template<class T>
	void heap_adjust(T array[], int i, int length);
	//初始建堆
	template<class T>
	void build_heap(T array[], int length);
	//合并有序序列
	template<class T>
	void merge(T array[], T temp[], int left, int middle, int right);
public:
	//插入排序
	template<class T>
	void insert_sort(T array[], int length);
	//shell排序
	template<class T>
	void shell_sort(T array[], int length);
	//选择排序
	template<class T>
	void select_sort(T array[], int length);
	//堆排序
	template<class T>
	void heap_sort(T array[], int length);
	//冒泡排序
	template<class T>
	void bubble_sort(T array[], int length);
	//快速排序
	template<class T>
	void quick_sort(T array[], int left, int right);
	//插入优化快排
	template<class T>
	void mode_quick_sort(T array[], int left, int right);
	//归并排序
	template<class T>
	void merge_sort(T array[], T temp[], int left, int right);
	//插入优化归并排序
	template<class T>
	void mode_merge_sort(T array[], T temp[], int left, int right);
	//桶排序
	template<class T>
	void bucket_sort(T array[], int n, int max);
};

#endif