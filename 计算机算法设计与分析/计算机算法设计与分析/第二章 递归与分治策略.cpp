#include "�ڶ��� �ݹ�����β���.h"

using namespace std;
#include "�ڶ��� �ݹ�����β���.h"

using namespace std;

namespace Algorithm {

	// �����㷨
	namespace DivideAndConquer {

		namespace ChessBoard {

			void Init(int **board, int dr, int dc) {
				tile = 0;
				board[dr][dc] = tile++;
			}

			/**
			* ���̸���
			* tr �������ϽǷ����к�
			* tc �������ϽǷ����к�
			* dr ���ⷽ�������к�
			* dc ���ⷽ�������к�
			* size ���̴�С
			*/
			void Solve(int **board, int tr, int tc, int dr, int dc, int size)
			{
				if (size == 1) {
					return;
				}
				int t = tile++;
				int sz = size / 2;

				// �������Ͻ�������
				if (dr < tr + sz && dc < tc + sz) {
					// ���ⷽ���ڴ�������
					Solve(board, tr, tc, dr, dc, sz);
				}
				else {
					// �����������ⷽ����t��L�͹��Ƹ������½�
					board[tr + sz - 1][tc + sz - 1] = t;
					// �������෽��
					Solve(board, tr, tc, tr + sz - 1, tc + sz - 1, sz);
				}

				// �������Ͻ�������
				if (dr < tr + sz && dc >= tc + sz) {
					// ���ⷽ���ڴ�������
					Solve(board, tr, tc + sz, dr, dc, sz);
				}
				else {
					// �����������ⷽ����t��L�͹��Ƹ������½�
					board[tr + sz - 1][tc + sz] = t;
					// �������෽��
					Solve(board, tr, tc + sz, tr + sz - 1, tc + sz, sz);
				}

				// �������½�������
				if (dr >= tr + sz && dc < tc + sz) {
					// ���ⷽ���ڴ�������
					Solve(board, tr + sz, tc, dr, dc, sz);
				}
				else {
					// ��t��L�͹��Ƹ������Ͻ�
					board[tr + sz][tc + sz - 1] = t;
					// �������෽��
					Solve(board, tr + sz, tc, tr + sz, tc + sz - 1, sz);
				}

				// �������½�������
				if (dr >= tr + sz&& dc >= tc + sz) {
					// ���ⷽ���ڴ�������
					Solve(board, tr + sz, tc + sz, dr, dc, sz);
				}
				else {
					// ��t��L�͹��Ƹ������Ͻ�
					board[tr + sz][tc + sz] = t;
					// �������෽��
					Solve(board, tr + sz, tc + sz, tr + sz, tc + sz, sz);
				}
			}

			void test()
			{
				int **board = NULL;
				int size, dr, dc;
				std::cout << "2.6 ���̸���" << std::endl;
				std::cout << "�����룺size��dr��dc" << std::endl;
				std::cin >> size >> dr >> dc;
				std::cout << "��ʼ��" << std::endl;
				board = InitMatrix(size);
				std::cout << "���̸���" << std::endl;
				ChessBoard::Init(board, dr, dc);
				ChessBoard::Solve(board, 0, 0, dr, dc, size);
				std::cout << "���ǽ��" << std::endl;
				PrintMatrix(board, size);
			}
		}

		// �鲢����
		namespace MergeSort {

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

			void test()
			{
				int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
				int *b = new int[11];
				cout << "2.7 �ϲ�����" << endl;
				Sort(a, b, 0, 10);
				cout << "a:" << endl;
				PrintArray(a, 11);
				cout << "b:" << endl;
				PrintArray(b, 11);
				delete[] b;
			}
		}
		
		// �ǵݹ��鲢����
		namespace MergeSortNonrecursive {

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
				// �ϲ���СΪsz������2��������
				while (i < n - 2 * sz) {
					Merge(a, b, i, i + sz - 1, i + 2 * sz - 1);
					i += (2 * sz);
				}
				// ʣ�µ�Ԫ�ظ�������2*sz
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

			void test()
			{
				int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
				int *b = new int[11];
				cout << "2.7 �ϲ����򡾷ǵݹ顿" << endl;
				Sort(a, b, 11);
				cout << "a:" << endl;
				PrintArray(a, 11);
				cout << "b:" << endl;
				PrintArray(b, 11);
				delete[] b;
			}
		}

		// ��������
		namespace QuickSort {

			template<class T> int Partition(T a[], int p, int r) {
				int i = p, j = r + 1;
				T x = a[p];
				// ��С��x��Ԫ�ؽ������������
				// ������x��Ԫ�ؽ������ұ�����
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

			template<class T> void Sort(T a[], int left, int right) {
				if (left < right) {
					int q = Partition(a, left, right);
					Sort(a, left, q - 1); // ����������
					Sort(a, q + 1, right); // ���Ұ������
				}
			}

			void test()
			{
				int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
				int *b = new int[11];
				cout << "2.8 ��������" << endl;
				Sort(a, 0, 10);
				std::cout << "a:" << std::endl;
				PrintArray(a, 11);
				std::cout << "b:" << std::endl;
				PrintArray(b, 11);
				delete[] b;
			}
		}

		// ѭ����
		namespace RoundRobin {

			void Table(int k, int **a) {
				int n = 1;
				for (int i = 0; i < k; i++) n *= 2;
				for (int i = 0; i < n; i++)a[1][i] = i;
				int m = 1;
			}

			void test() {
				cout << "2.11 ѭ�����ճ̱�" << endl;
			}
		};


		void test() {
			cout << "�ڶ��� �ݹ�����β���" << endl;
			ChessBoard::test();
			MergeSort::test();
			MergeSortNonrecursive::test();
			RoundRobin::test();
			getchar();
		}
	}
}