#ifndef _SORT_H_
#define _SORT_H_

class Sort{
private:
	int THRESHOLD = 28;
	//����Ԫ��
	template<class T>
	void swap(T &a, T &b);
	//������
	template<class T>
	void heap_adjust(T array[], int i, int length);
	//��ʼ����
	template<class T>
	void build_heap(T array[], int length);
	//�ϲ���������
	template<class T>
	void merge(T array[], T temp[], int left, int middle, int right);
public:
	//��������
	template<class T>
	void insert_sort(T array[], int length);
	//shell����
	template<class T>
	void shell_sort(T array[], int length);
	//ѡ������
	template<class T>
	void select_sort(T array[], int length);
	//������
	template<class T>
	void heap_sort(T array[], int length);
	//ð������
	template<class T>
	void bubble_sort(T array[], int length);
	//��������
	template<class T>
	void quick_sort(T array[], int left, int right);
	//�����Ż�����
	template<class T>
	void mode_quick_sort(T array[], int left, int right);
	//�鲢����
	template<class T>
	void merge_sort(T array[], T temp[], int left, int right);
	//�����Ż��鲢����
	template<class T>
	void mode_merge_sort(T array[], T temp[], int left, int right);
	//Ͱ����
	template<class T>
	void bucket_sort(T array[], int n, int max);
};

#endif