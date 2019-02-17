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
	private:
		T element;
		BinaryTreeNode<T> *left, *right;
	public:
		BinaryTreeNode(T element, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right);
		bool isLeaf() { return left == NULL && right == NULL; }
		T getValue() { return element; }
		BinaryTreeNode<T>* getLeftChild() { return left; }
		BinaryTreeNode<T>* getRightChild() { return right; }
	};
	
	// ������
	template<class T>
	class BinaryTree {
	private:
		BinaryTreeNode<T> *root;
	protected:
		DeleteBinaryTree(BinaryTreeNode<T>* root);
	public:
		BinaryTree(const T& elem, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree);
		~BinaryTree();
		int LeafNumber(BinaryTreeNode<T> *root);
		int GetHeight(BinaryTreeNode<T> *root);
		int Exchange(BinaryTreeNode<T> *root);
		BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);
		BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T>* current);
		bool isEmpty() const;
		bool RootPath(BinaryTreeNode<T> *root, BinaryTreeNode<T> *current);
		void CollectiveAncester(BinaryTreeNode<T> *root, BinaryTreeNode<T> *pchild, BinaryTreeNode<T> *qchild);
		void DepthOrder(BinaryTreeNode<T> *root, void(*Visit)(T element));
		void PreOrderWithoutRecursion(BinaryTreeNode<T> *root, void��*Visit)(T element));
		void InOrderWithoutRecursion(BinaryTreeNode<T> *root, void (*Visit)(T element));
		void PostOrderWithoutRecursion(BinaryTreeNode<T> *root, void (*Visit)(T element));
		void LevelOrder(BinaryTreeNode<T> *root, void (*Visit)(T element));
	};

	// ���߶�����
	template<class T>
	class ThreadBinaryTreeNode :BinaryTreeNode<T> {
		bool ltag, rtag;
	};

	template<class T>
	class ThreadBinaryTree : BinaryTree<T> {
	public:
		void Insert(ThreadBinaryTreeNode<T>* p, ThreadBinaryTreeNode<T> *r);
		void PostOrder(ThreadBinaryTreeNode<T> *root, void (*Visit)(ThreadBinaryTreeNode<T> *node));
		ThreadBinaryTreeNode<T> FindPreInPostOrder(ThreadBinaryTreeNode<T> *pointer);
	};

	// ����������
	template<class T>
	class BinarySearchTree : BinaryTree<T> {
	public:
		void Insert(BinaryTreeNode<T> *root, BinaryTreeNode *node);
		void Delete(BinaryTreeNode<T> *node);
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

	// ��С��ADT����
	template <class T>
	class MinHeap {
	private:
		T* heapArray;		//��Ŷ����ݵ�����
		int CurrentSize;	//��ǰ����Ԫ����Ŀ
		int MaxSize;		//���������ɵ����Ԫ����Ŀ
		void BuildHeap();	//����
	public:
		MinHeap(const int n);//n���Ԫ����
		~MinHeap() { delete[] heapArray; }; //��������
		bool isEmpty();
		bool isLeaf(int pos) const; //�����Ҷ��㣬����true
		int LeftChild(int pos) const; 	//��������λ��
		int RightChild(int pos) const; 	//�����Һ���λ��
		int Parent(int pos) const; 		// ���ظ����λ��	
		bool Remove(int pos, T& node); 	// ɾ�������±��Ԫ��
		bool Insert(const T& newNode);	//����в�����Ԫ��
		T&  RemoveMin(); 		//�ӶѶ�ɾ����Сֵ
		void SiftUp(int position); //��position���Ͽ�ʼ������ʹ���г�Ϊ��
		void SiftDown(int left);//ɸѡ������������left��ʾ��ʼ����������±�
	};

	// HuffmanTreeNode��̳���BinaryTreeNode��
	template<class T>
	class HuffmanTreeNode : BinaryTreeNode<T> {
		
	};

	// Huffman�����ඨ��[����5.12]
	template <class T>
	class HuffmanTree : BinaryTree<T> {
	private:
		HuffmanTreeNode<T>* root; //Huffman��������
		void MergeTree(HuffmanTreeNode<T> &ht1, HuffmanTreeNode<T> &ht2, HuffmanTreeNode<T>* parent);
		//��ht1��ht2Ϊ���������ϲ���һ����parentΪ���Ķ�����
		void DeleteTree(HuffmanTreeNode<T>* root);//ɾ
	public:
		HuffmanTree(T weight[], int n);//weight��Ȩֵ����;n���鳤
		virtual ~HuffmanTree() { DeleteTree(root); } //��������
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