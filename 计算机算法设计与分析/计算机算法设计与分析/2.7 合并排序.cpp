#include "第二章 递归与分治策略.h"

using namespace std;

namespace DivideAndConquer {

	namespace MergeSort {
		// 归并排序
		template<class T>
		void MergeArray(T a[], T b[], int left, int mid, int right) {
			int i = left, j = mid + 1;
			int k = left;
			while (i <= mid && j <= right) {
				if (a[i] <= a[j]) {
					b[k++] = a[i++];
				}
				else {
					b[k++] = a[j++];
				}
			}
			while (i <= mid) {
				b[k++] = a[i++];
			}
			while (j <= right) {
				b[k++] = a[j++];
			}
			for (i = left; i < k; i++) {
				a[i] = b[i];
			}
		}

		template<class T>
		void Sort(T a[], T b[], int left, int right) {
			if (left < right) {
				int mid = (left + right) / 2;
				MergeSort(a, b, left, mid);
				MergeSort(a, b, mid + 1, right);
				MergeArray(a, b, left, mid, right);
			}
		}
	}

	namespace MergeSortNonrecursive {
		// 非递归版归并排序
		template<class T>
		void Merge(T a[], T b[], int left, int mid, int right)
		{
			int i = left, j = mid + 1;
			int k = left;
			while (i <= mid && j <= right) {
				if (a[i] <= a[j]) {
					b[k++] = a[i++];
				}
				else {
					b[k++] = a[j++];
				}
			}
			while (i <= mid) {
				b[k++] = a[i++];
			}
			while (j <= right) {
				b[k++] = a[j++];
			}
		}

		template<class T>
		void MergePass(T a[], T b[], int sz, int n)
		{
			int i = 0;
			// 合并大小为sz的相邻2段子数组
			while (i < n - 2 * sz) {
				Merge(a, b, i, i + sz - 1, i + 2 * sz - 1);
				i += (2 * sz);
			}
			// 剩下的元素个数少于2*sz
			if (i + sz < n) {
				Merge(a, b, i, i + sz - 1, n - 1);
			}
			else {
				for (int j = i; j < n; j++) {
					b[j] = a[j];
				}
			}
		}

		template<class T>
		void Sort(T a[], T b[], int n) {
			int sz = 1;
			while (sz < n) {
				MergePass(a, b, sz, n);
				sz += sz;
				MergePass(b, a, sz, n);
				sz += sz;
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

	void test_2_7()
	{
		int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
		int *b = new int[11];
		// MergeSort::Sort(a, b, 0, 10);
		cout << "2.7 合并排序" << endl;
		MergeSortNonrecursive::Sort(a, b, 11);
		cout << "a:" << endl;
		PrintArray(a, 11);
		cout << "b:" << endl;
		PrintArray(b, 11);
		delete[] b;
	}
}