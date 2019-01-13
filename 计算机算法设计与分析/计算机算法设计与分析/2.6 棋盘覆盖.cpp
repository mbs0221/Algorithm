#include <iostream>
#include <vector>
#include <iomanip>

int tile = 0;
/**
 * ���̸��� 
 * tr �������ϽǷ����к�
 * tc �������ϽǷ����к�
 * dr ���ⷽ�������к�
 * dc ���ⷽ�������к�
 * size ���̴�С
 */
void ChessBoard(int **board, int tr, int tc, int dr, int dc, int size)
{
	if (size == 1) {
		return;
	}
	int t = tile++;
	int sz = size / 2;

	// �������Ͻ�������
	if (dr < tr + sz && dc < tc + sz) {
		// ���ⷽ���ڴ�������
		ChessBoard(board, tr, tc, dr, dc, sz);
	}
	else {
		// �����������ⷽ����t��L�͹��Ƹ������½�
		board[tr + sz - 1][tc + sz - 1] = t;
		// �������෽��
		ChessBoard(board, tr, tc, tr + sz - 1, tc + sz - 1, sz);
	}

	// �������Ͻ�������
	if (dr < tr + sz && dc >= tc + sz) {
		// ���ⷽ���ڴ�������
		ChessBoard(board, tr, tc + sz, dr, dc, sz);
	}
	else {
		// �����������ⷽ����t��L�͹��Ƹ������½�
		board[tr + sz - 1][tc + sz] = t;
		// �������෽��
		ChessBoard(board, tr, tc + sz, tr + sz - 1, tc + sz, sz);
	}

	// �������½�������
	if (dr >= tr + sz && dc < tc + sz) {
		// ���ⷽ���ڴ�������
		ChessBoard(board, tr + sz, tc, dr, dc, sz);
	}
	else {
		// ��t��L�͹��Ƹ������Ͻ�
		board[tr + sz][tc + sz - 1] = t;
		// �������෽��
		ChessBoard(board, tr + sz, tc, tr + sz, tc + sz - 1, sz);
	}

	// �������½�������
	if (dr >= tr + sz&& dc >= tc + sz) {
		// ���ⷽ���ڴ�������
		ChessBoard(board, tr + sz, tc + sz, dr, dc, sz);
	}
	else {
		// ��t��L�͹��Ƹ������Ͻ�
		board[tr + sz][tc + sz] = t;
		// �������෽��
		ChessBoard(board, tr + sz, tc + sz, tr + sz, tc + sz, sz);
	}
}

/**
* ��ʼ������
* mat ����
* size ��С
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
 * ��ӡ����
 * mat ����
 * size ��С
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
	std::cout << "�����룺size��dr��dc" << std::endl;
	std::cin >> size >> dr >> dc;
	std::cout << "��ʼ��" << std::endl;
	board = InitMatrix(size, dr, dc);
	std::cout << "���̸���" << std::endl;
	ChessBoard(board, 0, 0, dr, dc, size);
	std::cout << "���ǽ��" << std::endl;
	PrintMatrix(board, size);
	std::cin >> size;
}