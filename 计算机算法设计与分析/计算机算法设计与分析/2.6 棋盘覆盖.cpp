#include <iostream>
#include <vector>
#include <iomanip>

int tile = 0;
/**
 * 棋盘覆盖 
 * tr 棋盘左上角方格行号
 * tc 棋盘左上角方格列号
 * dr 特殊方格所在行号
 * dc 特殊方格所在列号
 * size 棋盘大小
 */
void ChessBoard(int **board, int tr, int tc, int dr, int dc, int size)
{
	if (size == 1) {
		return;
	}
	int t = tile++;
	int sz = size / 2;

	// 覆盖左上角子棋盘
	if (dr < tr + sz && dc < tc + sz) {
		// 特殊方格在此棋盘中
		ChessBoard(board, tr, tc, dr, dc, sz);
	}
	else {
		// 此棋盘无特殊方格，用t号L型骨牌覆盖右下角
		board[tr + sz - 1][tc + sz - 1] = t;
		// 覆盖其余方格
		ChessBoard(board, tr, tc, tr + sz - 1, tc + sz - 1, sz);
	}

	// 覆盖右上角子棋盘
	if (dr < tr + sz && dc >= tc + sz) {
		// 特殊方格在此棋盘中
		ChessBoard(board, tr, tc + sz, dr, dc, sz);
	}
	else {
		// 此棋盘无特殊方格，用t号L型骨牌覆盖左下角
		board[tr + sz - 1][tc + sz] = t;
		// 覆盖其余方格
		ChessBoard(board, tr, tc + sz, tr + sz - 1, tc + sz, sz);
	}

	// 覆盖左下角子棋盘
	if (dr >= tr + sz && dc < tc + sz) {
		// 特殊方格在此棋盘中
		ChessBoard(board, tr + sz, tc, dr, dc, sz);
	}
	else {
		// 用t号L型骨牌覆盖右上角
		board[tr + sz][tc + sz - 1] = t;
		// 覆盖其余方格
		ChessBoard(board, tr + sz, tc, tr + sz, tc + sz - 1, sz);
	}

	// 覆盖右下角子棋盘
	if (dr >= tr + sz&& dc >= tc + sz) {
		// 特殊方格在此棋盘中
		ChessBoard(board, tr + sz, tc + sz, dr, dc, sz);
	}
	else {
		// 用t号L型骨牌覆盖左上角
		board[tr + sz][tc + sz] = t;
		// 覆盖其余方格
		ChessBoard(board, tr + sz, tc + sz, tr + sz, tc + sz, sz);
	}
}

/**
* 初始化矩阵
* mat 矩阵
* size 大小
*/
int **InitMatrix(int size, int dr, int dc) {
	tile = 0;
	int **mat = new int*[size];
	for (int i = 0; i < size; i++) {
		mat[i] = new int[size];
		for (int j = 0; j < size; j++) {
			mat[i][j] = -1;
		}
	}
	mat[dr][dc] = tile++;
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

void test_2_6() 
{
	int **board = NULL;
	int size, dr, dc;
	std::cout << "请输入：size，dr，dc" << std::endl;
	std::cin >> size >> dr >> dc;
	std::cout << "初始化" << std::endl;
	board = InitMatrix(size, dr, dc);
	std::cout << "棋盘覆盖" << std::endl;
	ChessBoard(board, 0, 0, dr, dc, size);
	std::cout << "覆盖结果" << std::endl;
	PrintMatrix(board, size);
	std::cin >> size;
}