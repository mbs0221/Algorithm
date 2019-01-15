#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

namespace Algorithm {

	/**
	* 初始化矩阵
	* rows 行数
	* cols 列数
	*/
	int **InitMatrix(int rows, int cols);

	/**
	* 初始化矩阵
	* mat 矩阵
	* size 大小
	*/
	int **InitMatrix(int size);

	/**
	* 打印矩阵
	* mat 矩阵
	* size 大小
	*/
	void PrintMatrix(int **mat, int size);

	/**
	* 打印向量
	* a 向量
	* n 长度
	*/
	template<class T>
	void PrintArray(T a[], int n);

	void test();
};