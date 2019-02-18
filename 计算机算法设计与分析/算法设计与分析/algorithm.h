#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

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
		void Insert(int row, int col, T val);
		T Remove(int row, int col);
		T Get(int row, int col);
		SMatrix<T>& operator +(SMatrix<T> &b);
	};

#define MAX_SIZE 100

	// ��Ԫ��
	template<class T>
	class Triple {
		int row, col;
		T e;
		Triple(int row, int col, int e) :row(row), col(col), e(e) {  }
		//friend class TSMatrix<T>;
	};

	// ϡ����� - ��Ԫ���ʾ
	template<class T>
	class TSMatrix {
	private:
		int row, col, length;
		Triple<T> data[MAX_SIZE];
	public:
		TSMatrix<T>() :row(0), col(0), length(0) {  }
		TSMatrix<T>(int row, int col, int length) :row(row), col(col), length(length) {  }
		TSMatrix<T>& Transpose();
	};

	// �������ڵ�
	template<class T>
	class BinaryTreeNode {
	private:
		T element;
		BinaryTreeNode<T> *left, *right;
	public:
		BinaryTreeNode(T element, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right);
		// ��������
		bool isLeaf() { return left == NULL && right == NULL; }
		T getValue() { return element; }
		BinaryTreeNode<T>* getLeftChild() { return left; }
		BinaryTreeNode<T>* getRightChild() { return right; }
		// �Ƚ�
		bool operator < (const BinaryTreeNode & B) { return element < B.element; }
		bool operator <= (const BinaryTreeNode & B) { return element <= B.element; }
		bool operator == (const BinaryTreeNode & B) { return element == B.element; }
		bool operator >= (const BinaryTreeNode & B) { return element >= B.element; }
		bool operator > (const BinaryTreeNode & B) { return element > B.element; }
	};

	enum Tag { LEFT, RIGHT };
	template<class T>
	class StackElement {
		BinaryTreeNode<T> *pointer;
		Tag tag;
	};

	// ������
	template<class T>
	class BinaryTree {
	private:
		BinaryTreeNode<T> *root;
	protected:
		void DeleteBinaryTree(BinaryTreeNode<T>* root);
	public:
		BinaryTree(const T& elem, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree);
		~BinaryTree();
		int LeafNumber(BinaryTreeNode<T> *root);
		int GetHeight(BinaryTreeNode<T> *root);
		int Exchange(BinaryTreeNode<T> *root);
		BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);
		BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T>* current);
		bool isEmpty() const;
		// ��ɾ���
		virtual void Insert(BinaryTreeNode<T> *node);
		bool Compare(BinaryTreeNode<T> *root1, BinaryTreeNode<T> *root2);
		bool RootPath(BinaryTreeNode<T> *root, BinaryTreeNode<T> *current);
		void CollectiveAncester(BinaryTreeNode<T> *root, BinaryTreeNode<T> *pchild, BinaryTreeNode<T> *qchild);
		// ����
		void DepthOrder(BinaryTreeNode<T> *root, void (*Visit)(T element));
		void PreOrderWithoutRecursion(void (*Visit)(T element));
		void InOrderWithoutRecursion(void (*Visit)(T element));
		void PostOrderWithoutRecursion(void (*Visit)(T element));
		void LevelOrder(void (*Visit)(T element));
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
		void PostOrder(ThreadBinaryTreeNode<T> *root, void(*Visit)(ThreadBinaryTreeNode<T> *node));
		ThreadBinaryTreeNode<T> FindPreInPostOrder(ThreadBinaryTreeNode<T> *pointer);
	};

	// ����������
	template<class T>
	class BinarySearchTree : BinaryTree<T> {
	public:
		int PrintRange(BinaryTreeNode<T> *root, T min, T max);
		int SmallCount(BinaryTreeNode<T> *root, T key);
		int SmallCountWithoutRecursion(T key);
		bool isBST(BinaryTreeNode<T> *root);
		bool Search(T key);
		bool SearchWithoutRecursion(T key);
		virtual void Insert(BinaryTreeNode<T> *node);
		void Delete(BinaryTreeNode<T> *node);
		void DeleteNode(BinaryTreeNode<T> *root, T key);
		void DeleteNodeEx(BinaryTreeNode<T> *root);
	};

	// �������Ĳ�α�ʾ
	template<class T>
	class LLinkRTag {
		T element;
		int LLink, RTag;
	};

	// ���������ȸ������ʾ��
	template<class T>
	class LTagRLink {
		T element;
		int LTag, RLink;
	};

	// ��˫���λ���ȸ������ʾ��
	template<class T>
	class LTagRTag {
		T element;
		int LTag, RTag;
	};

	// �������ĺ�������ʾ��
	template<class T>
	class DegreePost {
		T element;
		int degree;
	};

	// ���ڵ�-�������ֱ�ʾ��
	template<class T>
	class TreeNode {
		T mValue;
		TreeNode<T> *pChild, *pSibling;
	public:
		TreeNode(T value) :mValue(value) {  }
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

	// ��-�������ֱ�ʾ��
	template<class T>
	class Tree {
	private:
		TreeNode<T> *root;
		Tree() { root = NULL; }
		TreeNode<T>* Convert(vector<DegreePost<T>> nodes);
		TreeNode<T>* Parent(TreeNode<T> *current);
		void DestroyNodes(TreeNode<T> *root);
		void DeleteSubTree(TreeNode<T> *root);
	};

	// ��С��ADT����
	template <class T>
	class MinHeap {
	private:
		T *heapArray;		//��Ŷ����ݵ�����
		int CurrentSize;	//��ǰ����Ԫ����Ŀ
		int MaxSize;		//���������ɵ����Ԫ����Ŀ
		void BuildHeap();	//����
	public:
		MinHeap(const int n);//n���Ԫ����
		~MinHeap() { delete[] heapArray; }; //��������
		int LeftChild(int pos) const; 	//��������λ��
		int RightChild(int pos) const; 	//�����Һ���λ��
		int Parent(int pos) const; 		// ���ظ����λ��
		bool isEmpty();
		bool isLeaf(int pos) const;		//�����Ҷ��㣬����true
		bool isMinHeap();				// ����С��	
		bool Remove(int pos, T& node); 	// ɾ�������±��Ԫ��
		bool Insert(const T& newNode);	//����в�����Ԫ��
		T&  RemoveMin(); 				//�ӶѶ�ɾ����Сֵ
		void SiftUp(int position);		//��position���Ͽ�ʼ������ʹ���г�Ϊ��
		void SiftDown(int left);		//ɸѡ������������left��ʾ��ʼ����������±�
	};

	// HuffmanTreeNode��

	template<class T>
	class HuffmanTreeNode : BinaryTreeNode<T> {

	};

	// Huffman��
	template <class T>
	class HuffmanTree : BinaryTree<T> {
	private:
		HuffmanTreeNode<T>* root;
		void MergeTree(HuffmanTreeNode<T> &ht1, HuffmanTreeNode<T> &ht2, HuffmanTreeNode<T>* parent);
		void DeleteTree(HuffmanTreeNode<T>* root);
	public:
		HuffmanTree(T weight[], int n);
		virtual ~HuffmanTree() { DeleteTree(root); }
	};

	// Trie�ֵ���
#define KIND 26

	template<class T>
	class TrieNode {
	public:
		TrieNode<T> *next[KIND];
		TrieNode<T> *fail;
		int count;
		TrieNode() :fail(NULL), count(0) { memset(next, NULL, sizeof(next)); }
	};

	template<class T>
	class TrieTree {
		TrieNode<T> *root;
	public:
		void insert(char *str);
		void build_ac_automation();
		int query(char *str);
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
		void Insert(RBNode<KEY, COLOR> *root, const KEY & key);
		void Remove(const KEY & key);
		void RedToBlack(RBNode<KEY, COLOR> *root);
	};

	// �ڽӶ��ر�
	class AdjacencyMultiListNode {
		int u, v; // ����u��v
		int u_next, v_next; // ��u��v��������һ����
		int weight; // Ȩ��
	};

	class AdjacencyMultiList{
		vector<AdjacencyMultiListNode> list;
	};

	// ʮ������
	template<class T>
	class Point {
		int id;
		T element;
	};

	template<class T>
	class Edge {
		int from, to;
		T element;
	};

	template<class TA>
	class Arc {
		int head, tail;
		Arc<TA> *hLink, *tLink;
		TA element;
	};

	template<class TV, class TA>
	class Vertex {
		TV element;
		Arc<TA> *first_in, *first_out;
		Vertex(TV e) {
			element = e;
			first_in = NULL;
			first_out = NULL;
		}
	};

	// �ڽӾ���
	class Graph {
		int **matrix;
		void toposort();
	};

	template<class TV, class TA>
	class OLGraph{
		vector<Vertex<TV, TA>> vertices;
		int numVertices, numArcs;
	public:
		OLGraph() {  }
		OLGraph(vector<Point<TV>> points, vector<Edge<TA>> edges);
	};

	namespace Sort {
		// ���������㷨
		template<class T>
		void InsertSort(T *vec, int n);

		// �۰��������
		template<class T>
		void BinaryInsertSort(T *vec, int n);

		// 2-·��������
		template<class T>
		void TwoWayInsertSort(T *vec, T *dst, int n);

		// ϣ������
		template<class T>
		void ShellSort(T *vec, int left, int right);

		// ð������
		template<class T>
		void BubbleSort(T *vec, int n);

		// ��������
		template<class T>
		void QuickSort(T *vec, int left, int right);

		// ѡ������
		template<class T>
		void SelectSort(T *vec, int n);
	}
}