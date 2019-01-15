#pragma once

#include "������㷨��������.h"

using namespace std;

namespace Algorithm {
	namespace DynamicProgramming {

		namespace MaxSubSum {

			/* ����Ӷκ�����ļ��㷨*/
			int Solve(int n, int *a, int &besti, int &bestj);
			/* ����Ӷκ�����ķ����㷨*/
			int SolveDC(int *a, int left, int right);
			/* ����Ӷκ�����Ķ�̬�滮�㷨*/
			int SolveDP(int *a, int left, int right);
			/* ��������Ӷκ�*/
			void test();
		}

		namespace MatrixChain {

			/* ����������� */
			void Solve(int *p, int **m, int **s, int n);
			/* ���ݽ� */
			void TraceBack(int i, int j, int **s);
			/* 3.1 ���Ծ������� */
			void test();
		}

		namespace LongestCommonSubsequence {

			/* ����������� */
			void Solve(string a, string b, int **c, int **s);
			/* ��ӡ����������� */
			void PrintLCS(string a, string b, int **s);
			/* 3.3 ��������������� */
			void test();
		}

		void test();
	}
}