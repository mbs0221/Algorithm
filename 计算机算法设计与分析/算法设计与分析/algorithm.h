#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <queue>

namespace Algorithm {

	template<class T>
	class SMatrix;

	// ʮ������ڵ�
	template<class T>
	class OLNode {
		friend SMatrix<T>;
	private:
		int row, col;
		T element;
		OLNode<T> *right, *down;
	public:
		OLNode() {
			right = NULL;
			down = NULL;
		}
		OLNode(int row, int col, T val) :row(row), col(col), element(val) {
			right = NULL;
			down = NULL;
		}
	};

	// ϡ����� - ʮ�������ʾ
	template<class T>
	class SMatrix {
	private:
		int rowNum, colNum;
	public:
		OLNode<T> *rowhead, *colhead;
		SMatrix(int row, int col) :rowNum(row), colNum(col) {
			rowhead = colhead = NULL;
		}
		void insertOLNode(int row, int col, T val);
		T deleteOLNode(int row, int col);
		T getElement(int row, int col);
		SMatrix<T> & MatrixAdd(SMatrix<T> & m1, SMatrix<T> & m2);
	};

#define MAX_SIZE 100
	// ��Ԫ��
	template<class T>
	class Triple {
	public:
		int row, col;
		T e;
	};

	// ϡ����� - ��Ԫ���ʾ
	template<class T>
	class TSMatrix {
	private:
		Triple<T> data[MAX_SIZE + 1];
		int m, n, lenght;
	public:
		TSMatrix<T> & Transpose(TSMatrix<T> & a);
	};
	
	// �������ڵ�
	template<class T>
	class BinaryTreeNode {
		T element;
		BinaryTreeNode<T> *left, *right;
		bool isLeaf() { return left == NULL && right == NULL; }
	};
	
	// ������
	template<class T>
	class BinaryTree {
		BinaryTreeNode<T> *root;
	public:
		int LeafNumber(BinaryTreeNode<T> *root);
		int GetHeight(BinaryTreeNode<T> *root);
		int Exchange(BinaryTreeNode<T> *root);
		bool RootPath(BinaryTreeNode<T> *root, BinaryTreeNode<T> *current);
		void CollectiveAncester(BinaryTreeNode<T> *root, BinaryTreeNode<T> *pchild, BinaryTreeNode<T> *qchild);
		void DepthOrder(BinaryTreeNode<T> *root, void(*Visit)(T element));
		void PreOrderWithoutRecursion(BinaryTreeNode<T> *root, void��*Visit)(T element));
		void InOrderWithoutRecursion(BinaryTreeNode<T> *root, void (*Visit)(T element));
		void PostOrderWithoutRecursion(BinaryTreeNode<T> *root, void (*Visit)(T element));
		void LevelOrder(BinaryTreeNode<T> *root, void (*Visit)(T element));
	};

	enum Tag { LEFT, RIGHT };
	template<class T>
	class StackElement {
		BinaryTreeNode<T> *pointer;
		Tag tag;
	};

	// ���ڵ�-�������ֱ�ʾ��
	template<class T>
	class TreeNode {
		T mValue;
		TreeNode<T> *pChild, *pSibling;
	public:
		bool isLeaf() { return pChild == NULL; }
		void setValue(T value) { mValue = value; }
		void insertFirst(TreeNode<T>* node) {
			//�Ե�һ���ӽ�����ݲ�����
			if (!pChild) {
				pChild = node;
			}
			else {
				node->pSibling = pChild;
				pChild = node;
			}
		}
		TreeNode<T>* RightSibling() { return pSibling; }
		TreeNode<T>* LeftMostChild() { return pChild; }
		void setChild(TreeNode<T> *child) { pChild = child; }
		void setSibling(TreeNode<T> *sibling) { pSibling = sibling; }
	};

	// ��
	template<class T>
	class Tree {
	private:
		TreeNode<T> *root;
		Tree() { root = NULL; }
		TreeNode<T>* Parent(TreeNode<T> *current);
		void DestroyNodes(TreeNode<T> *root);
		void DeletSubTree(TreeNode<T> *root);
	};

	// ���������ȸ������ʾ��
	template<class T>
	class TreeNode {
		T info;
		TreeNode *llink, *rlink;
		bool ltag;
	};
	template<class T>
	class DualTagTreeNode {
		T info;
		int ltag, rtag;
	};
	template<class T>
	class DualTagTree {
		DualTagTreeNode<T> *root;
	public:
		DualTagTree(DualTagTreeNode<T> *nodeArray, int count);
	};

	// ������ڵ�
#define RED 0
#define BLACK 1

	template<class KEY, class COLOR>
	class RBNode {
	public:
		KEY key;
		COLOR color;
		RBNode *left;
		RBNode *right;
		RBNode *parent;
		RBNode(RBNode *parent = NULL, RBNode *left = NULL, RBNode *right = NULL, KEY key = NULL, COLOR color = RED);
		bool isLeaf() { return key = NULL; }
	};

	// �����
	template<class KEY, class COLOR>
	class RBTree {
		RBNode<KEY, COLOR> *root;
		void insert(RBNode<KEY, COLOR> *root, const KEY & key);
		void remove(const KEY & key);
		void RedToBlack(RBNode<KEY, COLOR> *root);
	};
}