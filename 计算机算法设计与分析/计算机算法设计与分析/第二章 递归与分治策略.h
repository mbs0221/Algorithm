#pragma once

#include <iostream>
#include <iomanip>
#include <string>

namespace DivideAndConquer {

	// ���̸���
	namespace ChessBoard {

		static int tile = 0;

		void Init(int **board, int dr, int dc);
		/**
		* ���̸���
		* tr �������ϽǷ����к�
		* tc �������ϽǷ����к�
		* dr ���ⷽ�������к�
		* dc ���ⷽ�������к�
		* size ���̴�С
		*/
		void Solve(int **board, int tr, int tc, int dr, int dc, int size);
	}

	// �鲢����
	namespace MergeSort {
		
		template<class T>
		void MergeArray(T a[], T b[], int left, int mid, int right);

		template<class T>
		void Sort(T a[], T b[], int left, int right);
	}

	// �ǵݹ��鲢����
	namespace MergeSortNonrecursive {
		template<class T>
		void Merge(T a[], T b[], int left, int mid, int right);
		template<class T>
		void MergePass(T a[], T b[], int sz, int n);
		template<class T>
		void Sort(T a[], T b[], int n);
	}

	// ��������
	namespace QuickSort {
		template<class T>
		int Partition(T a[], int p, int r);
		template<class T>
		void Sort(T a[], int left, int right);
	}

	/**
	* ��ʼ������
	* mat ����
	* size ��С
	*/
	int **InitMatrix(int size);

	/**
	* ��ӡ����
	* mat ����
	* size ��С
	*/
	void PrintMatrix(int **mat, int size);

	/**
	 * ��ӡ����
	 * a ����
	 * n ����
	 */
	template<class T>
	void PrintArray(T a[], int n);

	// ����
	void test_2_6();
	void test_2_7();
	void test_2_8();
	void test_2_11();

	void test();
}