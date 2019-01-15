#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

namespace Algorithm {

	/**
	* ��ʼ������
	* rows ����
	* cols ����
	*/
	int **InitMatrix(int rows, int cols);

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

	void test();
};