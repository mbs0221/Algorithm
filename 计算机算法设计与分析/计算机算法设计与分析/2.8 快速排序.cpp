#include <iostream>
#include <iomanip>

template<class T>
int Partition(T a[], int p, int r) {
	int i = p, j = r + 1;
	T x = a[p];
	// 将小于x的元素交换到左边区域
	// 将大于x的元素交换到右边区域
	while (true) {
		while (a[++i] < x&&i < r);
		while (a[--j] > x);
		if (i >= j) break;
		T t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	a[p] = a[j];
	a[j] = x;
	return j;
}

template<class T>
void QuickSort(T a[], int left, int right) {
	if (left < right) {
		int q = Partition(a, left, right);
		QuickSort(a, left, q - 1); // 对左半段排序
		QuickSort(a, q + 1, right); // 对右半段排序
	}
}

template<class T>
void PrintArray(T a[], int n) {
	for (int i = 0; i < n; i++) {
		std::cout << std::setw(4) << a[i];
	}
	std::cout << std::endl;
}

void test_2_8()
{
	int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
	int *b = new int[11];
	QuickSort(a, 0, 10);
	std::cout << "a:" << std::endl;
	PrintArray(a, 11);
	std::cout << "b:" << std::endl;
	PrintArray(b, 11);
	delete[] b;
	getchar();
}

void main() {
	test_2_8();
}