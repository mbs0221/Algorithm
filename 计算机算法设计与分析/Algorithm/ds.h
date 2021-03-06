#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <string>
#include <regex>
#include <map>
#include <fstream>
#include <math.h>

using namespace std;

namespace DataStructure {

	// 向量
	template<class T>
	class Vector {
		T x, y;
	public:
		static vector<Vector<int>> EightDirs;
		static vector<Vector<int>> QuadDirs;
	public:
		Vector() :x(0), y(0) {  }
		Vector(T x, T y) :x(x), y(y) {  }
		Vector(Vector<T> &b) { x = b.x; y = b.y; }
		T norm() { return sqrt(x*x + y*y); }
		Vector& operator - (Vector<T> &b) {
			return Vector(x - b.x, y - b.y);
		}
		Vector& operator + (Vector<T> &b) {
			return Vector(x + b.x, y + b.y);
		}
		Vector& operator = (Vector<T> &b) {
			x = b.x; y = b.y;
		}
		bool operator ==(Vector<T> &b) {
			return (x == b.x && y = b.y);
		}
		friend ostream & operator << (ostream & out, const Vector & p) {
			out << '(' << p.x << ',' << p.y << ')';
			return out;
		}
		friend istream & operator >> (istream & in, Vector & p) {
			in >> p.x >> p.y;
			return in;
		}
	};

	template<class T>
	vector<Vector<int>> Vector<T>::QuadDirs = {
		Vector<int>(0, 1), Vector<int>(1,0), Vector<int>(-1,0), Vector<int>(0,-1),
	};

	template<class T>
	vector<Vector<int>> Vector<T>::EightDirs = {
		Vector<int>(1, 2), Vector<int>(2,1), Vector<int>(2,-1), Vector<int>(1,-2),
		Vector<int>(-1, -2), Vector<int>(-2,-1), Vector<int>(-2,1), Vector<int>(-1,2)
	};

	// 矩阵
	template<class T>
	class Matrix {
	private:
		int row, col;
		T **mat;
	public:
		Matrix() { row = 1; col = 1; mat = NULL; }
		Matrix(int size);
		Matrix(int r, int c);
		int GetRowCount() { return row; }
		int GetColumnCount() { return col; }
		T* operator [](int i);
		void Print();
		Matrix<T> & operator-(Matrix<T> &b);
		Matrix<T> & operator=(Matrix<T> &b);
	public:
		friend ostream & operator << (ostream & out, const Matrix & p) {
			out << '(' << p.row << ',' << p.col << ')';
			return out;
		}
		friend istream & operator >> (istream & in, Matrix & p) {
			in >> p.row >> p.col;
			return in;
		}
		friend class MatrixChain;
	};

	template<class T>
	class Triangle {
		Vector<T> a, b, c;
	public:
		Triangle(Vector<T> &a, Vector<T> &b, Vector<T> &c) :a(a), b(b), c(c) {  }
		T area() { return abs((a - b).norm()) + abs((a - c).norm()) + abs(b - c).norm(); }
	};

	template<class T>
	class Polygon {
		vector<Vector<T>> list;
	public:
		void AddEdge(Vector<T> &a) { list.push_back(a); }
	};

	template<class T>
	class SMatrix;

	// 十字链表节点
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

	// 稀疏矩阵 - 十字链表表示
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

	// 三元组
	template<class T>
	class Triple {
		int row, col;
		T e;
		Triple(int row, int col, int e) :row(row), col(col), e(e) {  }
		//friend class TSMatrix<T>;
	};

	// 稀疏矩阵 - 三元组表示
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

	namespace Tree {

		// 二叉树节点
		template<class T>
		class BinaryTreeNode {
		private:
			T element;
			BinaryTreeNode<T> *left, *right;
		public:
			BinaryTreeNode(T element, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right);
			// 基本操作
			bool isLeaf() { return left == NULL && right == NULL; }
			T getValue() { return element; }
			BinaryTreeNode<T>* getLeftChild() { return left; }
			BinaryTreeNode<T>* getRightChild() { return right; }
			// 比较
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

		// 二叉树
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
			BinaryTreeNode<T>* GetRoot();
			BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);
			BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T>* current);
			bool isEmpty() const;
			// 增删查改
			virtual void Insert(BinaryTreeNode<T> *node);
			bool Compare(BinaryTreeNode<T> *root1, BinaryTreeNode<T> *root2);
			bool RootPath(BinaryTreeNode<T> *root, BinaryTreeNode<T> *current);
			void CollectiveAncester(BinaryTreeNode<T> *root, BinaryTreeNode<T> *pchild, BinaryTreeNode<T> *qchild);
			// 遍历
			void DepthOrder(BinaryTreeNode<T> *root, void(*Visit)(T element));
			void PreOrderWithoutRecursion(void(*Visit)(T element));
			void InOrderWithoutRecursion(void(*Visit)(T element));
			void PostOrderWithoutRecursion(void(*Visit)(T element));
			void LevelOrder(void(*Visit)(T element));
		};

		// 穿线二叉树
		template<class T>
		class ThreadBinaryTreeNode : BinaryTreeNode<T> {
			bool ltag, rtag;
		};

		template<class T>
		class ThreadBinaryTree : BinaryTree<T> {
		public:
			void Insert(ThreadBinaryTreeNode<T> *p, ThreadBinaryTreeNode<T> *r);
			// 线索化
			void PreOrderThreading();
			void InOrderThreading();
			// 遍历
			void PreOrderThread(void(*Visit)(T elem));
			void InOrderThread(void(*Visit)(T elem));
			void PostOrder(ThreadBinaryTreeNode<T> *root, void(*Visit)(ThreadBinaryTreeNode<T> *node));
			ThreadBinaryTreeNode<T> FindPreInPostOrder(ThreadBinaryTreeNode<T> *pointer);
		};

		// 二叉搜索树
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

		// AVLTreeNode
		template<class T>
		class AVLTreeNode : public BinaryTreeNode<T> {
			int factor;
		};

		// AVLTree
		template<class T>
		class AVLTree : public BinarySearchTree<T> {
		public:
			virtual void Insert(AVLTreeNode<T> *node);
		protected:
			void LLRotate(AVLTreeNode<T> *a);
			void LRRotate(AVLTreeNode<T> *a);
			void RRRotate(AVLTreeNode<T> *a);
			void RLRotate(AVLTreeNode<T> *a);
		};

		// 带左链的层次表示
		template<class T>
		class LLinkRTag {
			T element;
			int LLink, RTag;
		};

		// 带右链的先根次序表示法
		template<class T>
		class LTagRLink {
			T element;
			int LTag, RLink;
		};

		// 带双标记位的先根次序表示法
		template<class T>
		class LTagRTag {
			T element;
			int LTag, RTag;
		};

		// 带度数的后跟次序表示法
		template<class T>
		class DegreePost {
			T element;
			int degree;
		};

		// 树节点-左子右兄表示法
		template<class T>
		class TreeNode {
			T mValue;
			TreeNode<T> *pChild, *pSibling;
		public:
			TreeNode(T value) :mValue(value) {  }
			bool isLeaf() { return pChild == NULL; }
			void setValue(T value) { mValue = value; }
			T getValue() { return mValue; }
			void insertFirst(TreeNode<T>* node) {
				//以第一个子结点的身份插入结点
				if (!pChild) {
					pChild = node;
				}
				else {
					node->pSibling = pChild;
					pChild = node;
				}
			}
			TreeNode<T>* getSibling() { return pSibling; }
			TreeNode<T>* getChild() { return pChild; }
			void setChild(TreeNode<T> *child) { pChild = child; }
			void setSibling(TreeNode<T> *sibling) { pSibling = sibling; }
		};

		// Forest
		template<class T>
		class Forest {
		private:
			TreeNode<T> *root;
			Forest() { root = NULL; }
			TreeNode<T>* Convert(vector<DegreePost<T>> nodes);
			TreeNode<T>* Parent(TreeNode<T> *current);
			void DestroyNodes(TreeNode<T> *root);
			void DeleteSubTree(TreeNode<T> *root);
		public:
			TreeNode<T> *getRoot() { return root; }
		};

		// 最小堆ADT定义
		template <class T>
		class MinHeap {
		private:
			T *heapArray;		//存放堆数据的数组
			int CurrentSize;	//当前堆中元素数目
			int MaxSize;		//堆所能容纳的最大元素数目
			void BuildHeap();	//建堆
		public:
			MinHeap(const int n);//n最大元素数
			~MinHeap() { delete[] heapArray; }; //析构函数
			int LeftChild(int pos) const; 	//返回左孩子位置
			int RightChild(int pos) const; 	//返回右孩子位置
			int Parent(int pos) const; 		// 返回父结点位置
			bool isEmpty();
			bool isLeaf(int pos) const;		//如果是叶结点，返回true
			bool isMinHeap();				// 是最小堆	
			bool Remove(int pos, T& node); 	// 删除给定下标的元素
			bool Insert(const T& newNode);	//向堆中插入新元素
			T&  RemoveMin(); 				//从堆顶删除最小值
			void SiftUp(int position);		//从position向上开始调整，使序列成为堆
			void SiftDown(int left);		//筛选法函数，参数left表示开始处理的数组下标
		};

		// HuffmanTreeNode类

		template<class T>
		class HuffmanTreeNode : BinaryTreeNode<T>;

		// Huffman树
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

		// Trie Tree
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
		class TrieTree  {
			TrieNode<T> *root;
		public:
			void insert(char *str);
			void build_ac_automation();
			int query(char *str);
		};

		class KeywordTree : Forest<char> {
		public:
			void insert(string & str);
		};

		// Red-Black Tree Node
		enum COLOR { RED, BLACK };

		template<class T>
		class RBNode : BinaryTreeNode<T> {
			T key;
			COLOR color;
			RBNode<T> *parent;
		public:
			RBNode(RBNode<T> *parent = NULL, RBNode<T> *left = NULL, RBNode<T> *right = NULL, T key = NULL, COLOR color = RED);
			bool isLeaf() { return key = NULL; }
		};

		// Red-Black Tree
		template<class T>
		class RBTree :BinarySearchTree<T> {
		public:
			void Insert(const T & key);
			void Remove(const T & key);
			void Find(const T & key);
			void RedToBlack(RBNode<T> *root);
		};
}
	
	// Graph
	namespace Graph {

		// Vertex
		template<class T>
		class Vertex {
			T element;
			Vertex(T e) {
				element = e;
			}
		};

		// Edge
		template<class TV, class TE>
		class Edge {
			Vertex<TV> *from, *to;
			TE element;
		};

		// Graph
		template<class TV, class TE>
		class Graph {
			virtual void AddVertex() = 0;
			virtual void AddEdge(Edge<TV, TE> e) = 0;
			virtual void RemoveVertex(int v) = 0;
			virtual void RemoveEdge(int u, int v) = 0;
			virtual void toposort();
		};

		// Multiple Ajacency List
		template<class TV, class TE>
		class AMVertex : Vertex<TV> {
			AMEdge<TV, TE> *head;
		};

		template<class TV, class TE>
		class AMEdge : Edge<TV, TE>{
			AMEdge<TV, TE> *ulink, *vlink;
		};

		template<class TV, class TE>
		class AMGraph {
			vector<AMVertex<TV, TE>*> vec;
		public:
			void AddVertex(AMVertex<TV, TE> *v);
			void AddEdge(AMEdge<TV, TE> *e);
			void RemoveVertex(int v);
			void RemoveEdge(int u, int v);
		};

		// 十字链表
		template<class T>
		class Point {
			int id;
			T element;
		};

		template<class T>
		class Arc : Edge<T> {
			Arc<T> *hLink, *tLink;
		};

		template<class TV, class TA>
		class OLGraph : Graph <TV, TE> {
			vector<Vertex<TV, TA>> vertices;
			int numVertices, numArcs;
		public:
			OLGraph() {  }
			OLGraph(vector<Point<TV>> points, vector<Edge<TA>> edges);
		};
	};

	namespace Sort {

		// 插入排序算法
		template<class T>
		void InsertSort(T *vec, int n);

		// 折半插入排序
		template<class T>
		void BinaryInsertSort(T *vec, int n);

		// 2-路插入排序
		template<class T>
		void TwoWayInsertSort(T *vec, T *dst, int n);

		// 希尔排序
		template<class T>
		void ShellSort(T *vec, int left, int right);

		// 冒泡排序
		template<class T>
		void BubbleSort(T *vec, int n);

		// 快速排序
		template<class T>
		void QuickSort(T *vec, int left, int right);

		// 选择排序
		template<class T>
		void SelectSort(T *vec, int n);
	}
}