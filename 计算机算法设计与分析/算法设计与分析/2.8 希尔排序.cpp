#include <iostream>
#include <iomanip>

using namespace std;

namespace Sort {

	void ShellSort(int *a, int left, int right)
	{
		// 选取步长
		for (int k = right / 2; k > 1; k /= 2) {
			// 对于每一列
			for (int i = 0; i < k; i++) {
				// 插入排序
				for (int j = k; j < right; j += k) {
					int p = j - k;
					int t = a[p];
					while ((p >= left) && (a[p] > t)) {
						a[p + k] = a[p];
						p -= k;
					}
					a[p + k] = t;
				}
			}
		}
	}

	template<class T>
	void PrintArray(T a[], int n) {
		for (int i = 0; i < n; i++) {
			std::cout << std::setw(4) << a[i];
		}
		std::cout << std::endl;
	}
}

void test_2_8()
{
	int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
	cout << "2.8 希尔排序" << endl;
	Sort::ShellSort(a, 0, 10);
	std::cout << "a:" << std::endl;
	Sort::PrintArray(a, 11);
	getchar();
}

void main() {
	test_2_8();
}