#pragma once

#include <math.h>
#include <iostream>

namespace Backtracking{

	template<class T>
	class Loading {
	public:
		Loading(T[] w, T c, int n);
		~Loading();
		friend T MaxLoading(T[], T, int);

	private:
		void Backtrack(int n);
		int n; // ��װ����
		T *w, c, cw, bestw; // ��װ���������飬ÿһ���ִ�������������ǰ����������ǰ����������
	};

	template<class T>
	class XLoading {
	public:
		XLoading(T[] w, T c, int n, int[] bestx);
		~XLoading();
		friend T MaxXLoading(T[], T, int, int[] bestx);

	private:
		void Backtrack(int i);
		int n; // ��װ����
		int *x, *bestx; // ��ǰ�⣬��ǰ���Ž�
		T *w, c, cw, bestw; // ��װ���������飬ÿһ���ִ�������������ǰ����������ǰ����������
		T r; // ʣ�༯װ������
	};

	class Flowshop {
		friend int Flow(int**, int, int[]);
	public:
		Flowshop(int **, int, int[]);
		~Flowshop();
	private:
		void Backtrack(int i);
		int **M; // ����ҵ����Ĵ���ʱ��
		int *x; // ��ǰ��ҵ����
		int *bestx; // ��ǰ������ҵ����
		int *f2; // ����2��ɴ����ʱ��
		int f1; // ����1��ɴ����ʱ��
		int f; // ���ʱ���
		int bestf; // ��ǰ����ֵ
		int n; // ��ҵ��
	};

	void test_5_2();
	void test_5_3();
	void test();
}