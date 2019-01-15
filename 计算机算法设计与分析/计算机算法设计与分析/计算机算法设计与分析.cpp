#include "计算机算法设计与分析.h"

namespace Algorithm {

	int ** InitMatrix(int rows, int cols)
	{

		int **mat = new int*[rows];
		for (int i = 0; i < rows; i++) {
			mat[i] = new int[cols];
			for (int j = 0; j < cols; j++) {
				mat[i][j] = 0;
			}
		}
		return mat;
	}


	/**
	* 初始化矩阵
	* mat 矩阵
	* size 大小
	*/
	int **InitMatrix(int size) {
		int **mat = new int*[size];
		for (int i = 0; i < size; i++) {
			mat[i] = new int[size];
			for (int j = 0; j < size; j++) {
				mat[i][j] = -1;
			}
		}
		return mat;
	}

	/**
	* 打印矩阵
	* mat 矩阵
	* size 大小
	*/
	void PrintMatrix(int **mat, int size) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				std::cout << std::setw(4) << mat[i][j];
			}
			std::cout << std::endl;
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