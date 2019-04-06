#include "ds.h"

namespace Exam2015 {

	using namespace std;

	namespace Problem1 {

		class Polynomial {
			Polynomial*child;
		};
	}
	// 第三题
	void SimplePath(int*path, int depth, int**G, int u, int v) {
		// 记录路径
		path[depth] = u;
		// 输出路径
		if (u == v) {
			for (int i = 0; i < depth; i++) {
				printf("%d ", path[i]);
			}
			return;
		}
		// 深度优先遍历
		for (int j = 0; j < 10; j++) {
			if (G[u][j] > 0) {
				SimplePath(path, depth + 1, G, j, v);
			}
		}
	}
	// 第四题
	class DigitalSearchTree {
	private:
		DigitalSearchTree*child[27];
	public:
		void Add(string name) {
			DigitalSearchTree*tree = this;
			for (string::iterator iter = name.begin(); iter != name.end(); iter++)
			{
				int i = *iter == ' ' ? 26 : *iter - 'A';
				tree->child[i] = new DigitalSearchTree();
				tree = tree->child[i];
			}
		}
	};
	// 第五题
	int PatternMatch(string s, string p, int startIndex) {
		int lastIndex = s.size() - p.size();
		if (lastIndex < startIndex)
			return -1;
		int i = startIndex, j = 0;
		int start; // 记录当前匹配的起始位置
		start = i;
		while (i < s.size() && j < p.size()) {
			if (p[j] == s[i]) {
				i++, j++;
			}
			// 扩充考虑“？”、“*”的情况
			else if (p[j] == '?') {
				i++, j++;
				continue;
			}
			else if (p[j] == '*') {
				j++;
				// 取出p中“*”后的字符，取出的s中对应于“*”的字符后的所有字符进行新的匹配
				int a = PatternMatch(s.substr(i, s.size() - i), p.substr(j, p.size() - j), 0);
				if (a >= 0) {
					// 若a大于0，说明已经匹配成功，只需要返回初始匹配位置
					return start;
				}
			}
			else {
				// 用start变量记录下匹配的起始位置
				i = i - j + 1;
				start = i;
				j = 0;
			}
		}
		// 若匹配成功，则返回的是起始位置start
		if (j >= p.size())
			return start;
		else
			return -1;
	}

}

namespace DataStructure {

	template<class T>
	Matrix<T>::Matrix(int size)
	{
		row = col = size;
		mat = new T*[row];
		for (int i = 0; i < row; i++) {
			mat[i] = new T[col];
			for (int j = 0; j < col; j++) {
				mat[i][j] = -1;
			}
		}
	}

	template<class T>
	Matrix<T>::Matrix(int r, int c)
	{
		row = r, col = c;
		mat = new T*[row];
		for (int i = 0; i < row; i++) {
			mat[i] = new T[col];
			for (int j = 0; j < col; j++) {
				mat[i][j] = -1;
			}
		}
	}

	template<class T>
	T* Matrix<T>::operator [](int i)
	{
		return mat[i];
	}

	template<class T>
	void Matrix<T>::Print() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				std::cout << std::setw(8) << mat[i][j];
			}
			std::cout << std::endl;
		}
	}

	template<class T>
	Matrix<T>& Matrix<T>::operator-(Matrix<T>& b)
	{
		Matrix<T> c(row, col);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < row; j++)
				c.mat[i][j] = mat[i][j] - b.mat[i][j];
		return c;
	}
	template<class T>
	Matrix<T>& Matrix<T>::operator=(Matrix<T> &b)
	{
		if (row != b.row || col != b.col)
			throw exception();
		for (int i = 0; i < row; i++)
			for (int j = 0; j < row; j++)
				mat[i][j] = b.mat[i][j];
		return *this; 
	}

	// 稀疏矩阵 - 十字链表
	template<class T>
	void SMatrix<T>::Insert(int row, int col, T val)
	{
		OLNode<T>*p, *q, *r, *u, *v;
		if (row<0 || row>rowNum || col<0 || col>colNum)
			return;
		r = new OLNode<T>(row, col, val);
		// 行
		p = rowhead[row];
		q = p->right;
		while (q->col < col) {
			p = q;
			q = q->right;
		}
		if (q->col == col)
			return;
		// 列
		u = colhead[col];
		v = u->down;
		while (v->row < row) {
			u = v;
			v = v->down;
		}
		if (v->row == row)
			return;
		// 插入
		p->right = r; r->right = q;
		u->down = r; r->down = v;
		return;
	}

	template<class T>
	T SMatrix<T>::Remove(int row, int col)
	{
		OLNode<T>*p, *q, *r, *u, *v;
		if (row<0 || row>rowNum || col<0 || col>colNum)
			return;
		// 行
		p = rowhead[row];
		q = p->right;
		while (q->col <= col) {
			p = q;
			q = q->right;
		}
		if (q->col != col) // 该行没有col列元素
			return;
		q = q->right;
		// 列
		u = colhead[col];
		v = u->down;
		while (v->row <= row) {
			u = v;
			v = v->down;
		}
		if (v->row != row) // 该列没有row行元素
			return;
		v = v->down;
		// 删除成功
		r = p->right;
		T val = r->element;
		delete r;
		// 链接
		p->right = q; u->down = v;
		return val;
	}

	template<class T>
	T SMatrix<T>::Get(int row, int col)
	{
		OLNode<T>*p, *q;
		if (row<0 || row>rowNum || col<0 || col>colNum)
			return;
		// 查找
		p = rowhead[row];
		q = p->right;
		while (q->col <= col) {
			p = q;
			q = q->right;
		}
		// 该行没有col列元素
		if (q->col != col)
			return NULL;
		return q->element;
	}

	template<class T>
	SMatrix<T>& SMatrix<T>::operator+(SMatrix<T>& b)
	{
		// TODO: 在此处插入 return 语句
		return SMatrix<T>(rowNum, colNum);
	}

	template<class T>
	TSMatrix<T> & TSMatrix<T>::Transpose()
	{
		int num[MAX_SIZE], position[MAX_SIZE];
		TSMatrix<T> mat(col, row, length);
		if (length > 0) {
			for (int i = 0; i < row; i++) {
				num[i] = 0;
			}
			// 计算每一列非零元素个数
			for (int i = 0; i < length; i++) {
				num[data[i].col]++;
			}
			// 计算每一列的起始位置
			position[0] = 0;
			for (int j = 1; j < col; j++) {
				position[j] = position[j - 1] + num[j - 1];
			}
			// 转置
			for (int i = 0; i < length; i++) {
				int col = data[i].col;
				int p = position[col];
				mat.data[p].row = data[i].col;
				mat.data[p].col = data[i].row;
				mat.data[p].e = data[i].e;
				position[col]++;
			}
		}
		return mat;
	}

	namespace Tree {

		// 二叉树节点类
		template<class T>
		BinaryTreeNode<T>::BinaryTreeNode(T element, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right)
		{
			this->element = element;
			this->left = left;
			this->right = right;
		}

		// 二叉树
		template<class T>
		void BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T> *root)
		{
			if (root) {
				DeleteBinaryTree(root->left);
				DeleteBinaryTree(root->right);
				delete root;
			}
		}

		template<class T>
		BinaryTree<T>::BinaryTree(const T & elem, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree)
		{
			root = new BinaryTreeNode<T>(elem, leftTree.root, rightTree.root);
			leftTree.root = rightTree.root = NULL;
		}

		template<class T>
		BinaryTree<T>::~BinaryTree()
		{
			DeleteBinaryTree(root);
		}

		template<class T>
		int BinaryTree<T>::LeafNumber(BinaryTreeNode<T> *root)
		{
			if (root == NULL) return 0;
			if (root->isLeaf()) return 1;
			return LeafNumber(root->left) + LeafNumber(root->right);
		}

		template<class T>
		int BinaryTree<T>::GetHeight(BinaryTreeNode<T> *root)
		{
			if (root == NULL) return 0;
			int h1 = GetHeight(root->left) + 1;
			int h2 = GetHeight(root->right) + 1;
			return h1 > h2 ? h1 : h2;
		}

		template<class T>
		int BinaryTree<T>::Exchange(BinaryTreeNode<T> *root)
		{
			BinaryTreeNode<T>*temp;
			if (root != NULL) {
				// 交换当前节点左右子树
				temp = root->left;
				root->left = root->right;
				root->right = temp;
				// 递归交换
				Exchange(root->left);
				Exchange(root->right);
			}
			return 0;
		}

		template<class T>
		BinaryTreeNode<T>* BinaryTree<T>::GetRoot()
		{
			return root;
		}

		template<class T>
		BinaryTreeNode<T> *BinaryTree<T>::Parent(BinaryTreeNode<T> *current)
		{
			//求current双亲返回
			using std::stack;
			stack <BinaryTreeNode<T>*> aStack;
			BinaryTreeNode<T>*p = root;
			if (root != NULL&& current != NULL) {
				while (!aStack.empty() || p) {
					if (p != NULL) {
						if (current == p->left || current == p->right)
							return p; //返回双亲
						aStack.push(p);	 p = p->left;
					}//入栈 指左子
					else {
						p = aStack.top();
						aStack.pop(); //出栈
						p = p->right; //指向右子
					}
				}
			}
		}

		template<class T>
		BinaryTreeNode<T> *BinaryTree<T>::LeftSibling(BinaryTreeNode<T> *current)
		{
			//返回current结点的左兄弟
			if (current) //current不为空
			{
				//返回current结点的父结点
				BinaryTreeNode<T> *temp = Parent(current);
				//如果父结点为空，或者current没有左兄弟
				if ((temp == NULL) || current == temp->left)
					return  NULL;
				else
					return temp->getLeftChild();
			}
			return NULL;
		}

		template<class T>
		bool BinaryTree<T>::isEmpty() const
		{
			return ((root) ? false : true);
		}

		template<class T>
		void BinaryTree<T>::Insert(BinaryTreeNode<T> *node)
		{
			return;
		}

		template<class T>
		bool BinaryTree<T>::Compare(BinaryTreeNode<T> *root1, BinaryTreeNode<T> *root2)
		{
			if (root1 == NULL&&root2 == NULL)
				return true;
			else if (root1->element == root2->element
				&&Compare(root1->left, root2->left)
				&& Compare(root1->right, root2->right))
				return true;
			else
				return false;
		}

		template<class T>
		bool BinaryTree<T>::RootPath(BinaryTreeNode<T> *root, BinaryTreeNode<T> *current)
		{
			return false;
		}

		template<class T>
		void BinaryTree<T>::CollectiveAncester(BinaryTreeNode<T> *root, BinaryTreeNode<T> *pchild, BinaryTreeNode<T> *qchild)
		{
		}

		template<class T>
		void BinaryTree<T>::DepthOrder(BinaryTreeNode<T> *root, void(*Visit)(T element))
		{
			if (!root) {
				(*Visit)(root->element);
				DepthOrder(root->left);
				DepthOrder(root->right);
			}
		}

		template<class T>
		void BinaryTree<T>::PreOrderWithoutRecursion(void(*Visit)(T element))
		{
			using std::stack;
			stack<BinaryTreeNode<T>*> aStack;
			BinaryTreeNode<T> *p = root;
			aStack.push(NULL);
			while (p) {
				// 先访问当前节点
				(*Visit)(p->element);
				// 右子非空入栈
				if (p->right != NULL)aStack.push(p->right);
				// 继续左下周游
				if (p->left != NULL) p = p->left;
				else[
					p = aStack.top();
					aStack.POP();
				]
			}
		}

		template<class T>
		void BinaryTree<T>::InOrderWithoutRecursion(void(*Visit)(T element))
		{
			// 中序非递归周游二叉树
			using std::stack;
			stack<BinaryTreeNode<T>*> aStack;
			BinaryTreeNode<T> *p = root;
			while (!aStack.empty() || p) {
				if (p) {
					// 向左下走到底，不访问只入栈
					aStack.push(p);
					p = p->left;
				}
				else {
					p = aStack.top(); // 取栈顶
					aStack.pop(); // 出栈
					(*Visit)(p->element); // 访问当前节点
					p = p->right; // 右跨一步指向右子，重复之前操作
				}
			}
		}

		template<class T>
		void BinaryTree<T>::PostOrderWithoutRecursion(void(*Visit)(T element))
		{
			// 后序非递归周游二叉树
			using std::stack;
			StackElement<T> element;
			stack<StackElement<T>> aStack;
			BinaryTreeNode<T>*p;
			if (root == NULL)
				return;
			else
				p = root;
			while (!aStack.empty() || p) {
				// 进入p的左子树
				while (p != NULL) {
					element.pointer = p;
					element.tag = LEFT;
					aStack.push(element);
					p = p->left;
				}
				// 取栈顶元素，出栈
				element = aStack.top();
				aStack.pop();
				p = element.pointer;
				// 从左子树回来
				if (element.tag == LEFT) {
					element.tag = RIGHT;
					aStack.push(element);
					// p移到右子树
					p = p->right;
				}
				else {
					// 访问当前节点
					(*Visit)(p->element);
					p = NULL; // 清空为了继续入栈
				}
			}
		}

		template<class T>
		void BinaryTree<T>::LevelOrder(void(*Visit)(T element))
		{
			//广度优先周游二叉树
			using std::queue;
			queue<BinaryTreeNode<T>*> aQueue;
			BinaryTreeNode<T>*p = root;
			if (p) aQueue.push(p);
			while (!aQueue.empty()) {
				p = aQueue.front();
				(*Visit)(p->element);
				aQueue.pop();
				if (p->left)
					aQueue.push(p->left);
				if (p->right)
					aQueue.push(p->right);
			}
		}

		// 线索二叉树

		template<class T>
		void ThreadBinaryTree<T>::Insert(ThreadBinaryTreeNode<T> *p, ThreadBinaryTreeNode<T> *r)
		{
			// r为待插入的新节点，p指向穿线二叉树的一个节点
			ThreadBinaryTreeNode<T> *temp = NULL;
			if (p->left == NULL) {
				temp = NULL;
			}
			else if (p->ltag == true) {
				// 左孩子为线索，前驱为左孩子
				temp = p->left;
			}
			else {
				// 前驱为左子树中序周游的最后一个点
				temp = p->left;
				while (temp->rtag == false) {
					temp = temp->right;
				}
			}
			// 此时，temp指向p的中序前驱
			if (temp != NULL && temp->rtag == true) {
				temp->right = r;
			}
			// 建立新节点的左指针或左线索
			r->ltag = p->ltag;
			r->left = p->left;
			// 插入新节点
			p->ltag = false;
			p->left = r;
			// 建立新节点右线索
			r->rtag = true;
			r->right = p;
		}

		template<class T>
		void ThreadBinaryTree<T>::PreOrderThreading()
		{
			stack<ThreadBinaryTreeNode<T>*> s;
			ThreadBinaryTreeNode<T> *last = NULL, *p;
			if (root != NULL) {
				s.push(root);
				while (!s.empty()) {
					p = s.top();
					s.pop();
					// 线索化左子节点
					if (p->left != NULL)
						p->ltag = false;
					else
					{
						p->ltag = true; p->left = last;
					}
					// 线索化右子节点
					if (last != NULL)
						if (last->right != NULL)
							last->rtag = false;
						else
						{
							last->rtag = true, last->right = p;
						}
					last = p;
					// 先序遍历
					if (p->right != NULL)
						s.push(p->right);
					if (p->left != NULL)
						s.push(p->left);
				}
				last->rtag = true;
			}
		}

		template<class T>
		void ThreadBinaryTree<T>::InOrderThreading()
		{
			stack<ThreadBinaryTreeNode<T>*> s;
			ThreadBinaryTreeNode<T> *last, *p = root;
			while (p != NULL || !s.empty()) {
				if (p != NULL) {
					s.push(p);
					p = p->left;
				}
				else {
					p = s.top();
					s.pop();
					// 当前节点的左线索
					if (p->left != NULL) p->ltag = false;
					else { p->ltag = true; p->left = last; }
					// 上一个节点的右线索
					if (last != NULL)
						if (last->right != NULL) last->rtag = false;
						else { last->rtag = true; last->right = p; }
						// 记录当前节点
						last = p;
						// 访问右节点
						p = p->right;
				}
				last->rtag = true; // 最后一个节点是叶子节点
			}
		}

		template<class T>
		void ThreadBinaryTree<T>::PreOrderThread(void(*Visit)(T elem))
		{
			// 先序线索二叉树的先序遍历
			ThreadBinaryTreeNode<T> *p = root;
			while (p != NULL) {
				Visit(p->element);
				if (p->ltag == false)
					p = p->left;
				else
					p = p->right;
			}
		}

		template<class T>
		void ThreadBinaryTree<T>::InOrderThread(void(*Visit)(T elem))
		{
			ThreadBinaryTreeNode<T> *p;
			if (root != NULL) {
				p = root;
				while (p->ltag == false)
					p = p->left; // 寻找最左的节点
				while (p != NULL) {
					Visit(p->element);
					if (p->rtag = true)
						p = p->right; // 通过右线索找到后继
					else {
						// 否则右子树的最左节点为后继
						p = p->right;
						while (p->ltag == 0)
							p = p->left;
					}
				}
			}
		}

		template<class T>
		void ThreadBinaryTree<T>::PostOrder(ThreadBinaryTreeNode<T> *root, void(*Visit)(ThreadBinaryTreeNode<T> *node))
		{
			if (root->ltag == 0)
				PostOrder(root->left);
			if (root->rtag == 0)
				PostOrder(root->right);
			Visit(root);
		}

		template<class T>
		ThreadBinaryTreeNode<T> ThreadBinaryTree<T>::FindPreInPostOrder(ThreadBinaryTreeNode<T> *pointer)
		{
			// 在中序穿线二叉树中查找指定节点在后序下的前驱
			ThreadBinaryTreeNode<T> * temp = NULL;
			if (pointer->rtag == 0)
				return pointer->right;
			else
				temp = pointer;
			while (temp->ltag == 1) {
				temp = temp->left;
			}
			temp = temp->left;
			return temp;
		}

		// 二叉搜索树

		template<class T>
		int BinarySearchTree<T>::PrintRange(BinaryTreeNode<T> *root, T min, T max)
		{
			if (root->element < min)
				return 0;
			else if (root->element == min) {
				cout << root->element << endl;
				return PrintRange(root->right, min, max) + 1;
			}
			else if (min < root->element && root->element <= max) {
				cout << root->element << endl;
				return PrintRange(root->left, min, max) + PrintRange(root->right, min, max) + 1;
			}
			else if (root->element > max)
				return PrintRange(root->left, min, max);
		}

		template<class T>
		int BinarySearchTree<T>::SmallCount(BinaryTreeNode<T> *root, T key)
		{
			if (root == NULL)
				return 0;
			else if (root->element <= key)
				return (1 + SmallCount(root->left, key) + SmallCount(root->right, key));
			else
				return SmallCount(root->left, key);
		}

		template<class T>
		int BinarySearchTree<T>::SmallCountWithoutRecursion(T key)
		{
			// 非递归中序遍历二叉树
			int n = 0;
			using std::stack;
			stack<BinaryTreeNode<T>*> aStack;
			BinaryTreeNode<T> *pointer = root;
			while (aStack.empty() || pointer) {
				if (pointer) {
					aStack.push(pointer);
					pointer = pointer->left;
				}
				else {
					pointer = aStack.top();
					if (pointer->element <= key)
						n++;
					else
						break;
					pointer = pointer->right;
					aStack.pop();
				}
			}
			return n;
		}

		template<class T>
		bool BinarySearchTree<T>::isBST(BinaryTreeNode<T> *root)
		{
			if (root == NULL)
				return true;
			if (root->left&&root->element <= root->left->element)
				return false;
			if (root->right&&root->element > root->right->element)
				return false;
			return isBST(root->left) && isBST(root->right);
		}

		template<class T>
		bool BinarySearchTree<T>::Search(T key)
		{
			if (root == NULL)
				return false;
			if (root->element == key)
				return true;
			return Search(root->left) || Search(root->right);
		}

		template<class T>
		bool BinarySearchTree<T>::SearchWithoutRecursion(T key)
		{
			using std::stack;
			stack<BinaryTreeNode<T>> aStack;
			BinaryTreeNode<T> *pointer == root;
			while (!aStack.empty() || pointer) {
				if (pointer) {
					aStack.push(pointer);
					pointer = pointer->left;
				}
				else {
					pointer = aStack.top();
					if (pointer->element == key)
						return true;
					pointer = pointer->right;
					aStack.pop();
				}
			}
			return false;
		}

		template<class T>
		void BinarySearchTree<T>::Insert(BinaryTreeNode<T> *node)
		{
			BinaryTreeNode<T> *p = NULL;
			if (root == NULL) {
				//新结点作根
				root = node;
				return;
			}
			else
				p = root;
			while (p != NULL) {
				//相等 则不用插入
				if (node->getValue() == p->getValue())
					return;
				else if (node->getValue() < p->getValue()) {
					//待插小
					if (p->getLeftChild() == NULL) {
						//作为左子树
						p->left = node;
						return;
					}
					else
						p = p->getLeftChild();
				}
				else {
					if (p->getRightChild() == NULL) {
						//作为右子树
						p->right = node;
						return;
					}
					else
						p = p->getRightChild();
				}
			}
		}

		template<class T>
		void BinarySearchTree<T>::Delete(BinaryTreeNode<T> *p)
		{
			if (p == NULL)
				return;
			BinaryTreeNode<T> *s;
			BinaryTreeNode<T> *tempparent = NULL;
			BinaryTreeNode<T> *parent = GetParent(root, p);
			if (p->left == NULL) {
				// 无左子树
				s = p->right;
			}
			else {
				// 有左子树
				s = p->left;
				while (s->right != NULL) {
					tempparent = s;
					s = s->right;
				}
				//p->lc没右子(Cr为空没向右下移动)
				if (tempparent == NULL)
					p->left = s->left;  //p左子树中C最大,p->lc指Cl
				else
					tempparent->right = s->left; //tempp左子Sl作其父Q右子树
				s->left = p->left;//tempp(即S)代替p接管p左子右子
				s->right = p->right;
			}
			if (parent == NULL) //F为空用p左子树最大tempp替换被删p作根
				root = s;
			else if (parent->left == p) //if删parent的左子p
				parent->left = s;  //让s(即tempp)替代p做parent左子
			else
				parent->right = s; //删的是parent右子p
			delete p;
			p = NULL;
			return;
		}

		template<class T>
		void BinarySearchTree<T>::DeleteNode(BinaryTreeNode<T> *root, T key)
		{
			if (root == NULL)
				return;
			if (root->element < key)
				DeleteNode(root->right, key);
			else if (root->element > key)
				DeleteNode(root->left, key);
			else
				DeleteNodeEx(root);
		}

		template<class T>
		void BinarySearchTree<T>::DeleteNodeEx(BinaryTreeNode<T> *root)
		{
			if (root == NULL)
				return;
			DeleteNodeEx(root->left);
			DeleteNodeEx(root->right);
			delete root;
		}

		// AVL树

		template<class T>
		void AVLTree<T>::Insert(AVLTreeNode<T>* node)
		{
			AVLTreeNode<T> *root, *f, *a, *b, *p, *q;
			// if (root == NULL) { root = node;}
		}

		template<class T>
		void AVLTree<T>::LLRotate(AVLTreeNode<T>* a)
		{
			AVLTreeNode<T> *b;
			b = a->left; a->left = b->right;
			b->right = a;
			a->factor = b->factor;
			a = b;
		}

		template<class T>
		void AVLTree<T>::LRRotate(AVLTreeNode<T> *a)
		{
			AVLTreeNode<T> *b, *c;
			// 初始化
			b = a->left; c = b->right;
			// 卸载c的左右子给b，a
			a->left = c->right; b->right = c->left;
			// 设置c的左右子为b，a
			c->left = b; c->right = a;
			// 调整平衡因子
			if (c->factor == 1) {
				a->factor = -1;	b->factor = 0;// 左边轻
			}
			else if (c->factor == 0) {
				a->factor = b->factor = 0; // 平衡
			}
			else {
				a->factor = 0; b->factor = 1; // 右边重
			}
			// 设置新树根
			a = c;
		}

		template<class T>
		void AVLTree<T>::RRRotate(AVLTreeNode<T>* a)
		{
			AVLTreeNode<T> *b;
			b = a->right;
			// 卸载b的左子给a当右子
			a->right = b->left;
			// a作为b的左子
			b->left = a;
			// 调整平衡因子，返回新树根
			a->factor = b->factor = 0; a = b;
		}

		template<class T>
		void AVLTree<T>::RLRotate(AVLTreeNode<T>* a)
		{
			AVLTreeNode<T> *b, *c;
			// 初始化b，c
			b = a->right; c = b->left;
			// 卸载c的左右子给a，b
			a->right = c->left; b->left = c->right;
			// 设置c的左右子为a，b
			c->left = a; c->right = b;
			// 调整平衡因子
			if (c->factor == 1) {
				a->factor = 0; b->factor = -1;
			}
			else if (c->factor == 0) {
				a->factor = b->factor = 0;
			}
			else {
				a->factor = 1; b->factor = 0;
			}
			// 设置树根
			a = c;
		}

		// 森林 - 左子右兄表示法

		template<class T>
		TreeNode<T> *Forest<T>::Convert(vector<DegreePost<T>> nodes)
		{
			TreeNode<T> *cur, *temp1, *temp2;
			stack<TreeNode<T>*> aStack;
			for (DegreePost<T> node : nodes) {
				if (node.degree == 0) {
					aStack.push(new TreeNode<T>(node.element));
				}
				else {
					cur = new TreeNode<T>(node.element);
					temp2 = aStack.top();
					aStack.pop();
					for (int j = 1; j < node.degree; j++) {
						temp1 = aStack.top();
						aStack->pop();
						temp1->setSibling(temp2);
						temp2 = temp1;
					}
					cur->setChild(temp2);
					aStack.push(cur);
				}
			}
			temp2 = aStack.top();
			aStack.pop();
			while (!aStack.empty()) {
				cur = aStack.top();
				aStack.pop();
				cur->setSibling(temp2);
				temp2 = cur;
			}
			return temp2;
		}

		template<class T>
		TreeNode<T> *Forest<T>::Parent(TreeNode<T> *current)
		{
			using std::queue;
			queue<TreeNode<T>*> aQueue;
			TreeNode<T>*pointer = root;
			TreeNode<T>*parent = NULL;
			if (current != NULL && pointer != current) {
				// 森林的所有树根入队
				while (pointer != NULL) {
					if (current == pointer)
						return NULL;
					aQueue.push(pointer);
					pointer = pointer->pSibling;
				}
				while (!aQueue.empty()) {
					pointer = aQueue.front();
					aQueue.pop(); // 取队头
					parent = pointer; // 父
					pointer = pointer->LeftMostChild(); // 子
					// pointer的所有兄弟与current比
					while (pointer) {
						if (current == pointer)
							return parent; // 找到parent
						else {
							aQueue.push(pointer);
							pointer = pointer->RightSibling();
						}
					}
				}
			}
			return NULL;
		}

		template<class T>
		void Forest<T>::DestroyNodes(TreeNode<T> *root)
		{
			if (root != NULL) {
				DestroyNodes(root->LeftMostChild());
				DestroyNodes(root->RightSibling());
				delete root;
			}
		}

		template<class T>
		void Forest<T>::DeleteSubTree(TreeNode<T> *subroot)
		{
			TreeNode<T>*pointer;
			// 空树不必删
			if (subroot == NULL) return;
			// point指向subroot(被删子树根的)父结点
			pointer = Parent(subroot);
			// subroot没父:被删子树是森林某棵树(青字改书 )
			if (pointer == NULL) {
				// 被删子树是森林中的一棵树
				if (subroot == root) {
					root = subroot->RightSibling();
				}
				else {
					// 删后面树:从root起找被删树前驱(左兄)
					TreeNode<T> *r = root;
					while (r->RightSibling() != subroot) {
						r = r->RightSibling();
					}
					r->RightSibling() = subroot->RightSibling();
				}
			}
			else if (pointer->LeftMostChild() == subroot) {
				// 被删的是父的最左子，让subroot右兄作父pointer最左子
				pointer->setChild(subroot->RightSibling());
			}
			else {
				// 被删(subroot不是最左子)有左兄,让subroot左兄pSibling指被删点右兄
				pointer = pointer->LeftMostChild();
				// 则找直接左兄
				while (pointer->RightSibling() != subroot)
					pointer = pointer->RightSibling();
				//让左兄pointer右兄是被删点subroot右兄
				pointer->setSibling(subroot->RightSibling());
			}
			//被删点右兄置空(切断与原树链接成为树而非森林)
			subroot->setSibling(NULL);
			//删树
			DestroyNodes(subroot);
		}

		// 最小堆
		template<class T>
		void MinHeap<T>::BuildHeap()
		{
			//从最后一个父结点至根逐一筛选
			for (int i = CurrentSize / 2 - 1; i >= 0; i--)
				SiftDown(i);
		}

		template<class T>
		MinHeap<T>::MinHeap(const int n)
		{
			if (n <= 0)
				return;
			CurrentSize = 0;
			MaxSize = n; 			//初始化堆容量为n
			heapArray = new T[MaxSize]; //创建堆空间
			BuildHeap();  			//建堆
		}

		template<class T>
		bool MinHeap<T>::isEmpty()
		{
			return false;
		}

		template<class T>
		bool MinHeap<T>::isLeaf(int pos) const
		{
			return (pos >= CurrentSize / 2) && (pos < CurrentSize);
		}

		template<class T>
		bool MinHeap<T>::isMinHeap()
		{
			for (int i = 0; i < (CurrentSize - 1) / 2; i++) {
				if ((2 * i + 2 <= CurrentSize)) {
					if (!((heapArray[i] <= heapArray[LeftChild(i)]) && (heapArray[i] <= heapArray[RightChild(i)])))
						return false;
				}
				else if (!(heapArray[i] <= heapArray[LeftChild(i)]))
					return false;
			}
			return true;
		}

		template<class T>
		int MinHeap<T>::LeftChild(int pos) const
		{
			return 2 * pos + 1;	//返回pos的左孩子位置
		}

		template<class T>
		int MinHeap<T>::RightChild(int pos) const
		{
			return 2 * pos + 2;  	//返回pos的右孩子位置
		}

		template<class T>
		int MinHeap<T>::Parent(int pos) const
		{
			return (pos - 1) / 2; 	//返回pos的父结点位置
		}

		template<class T>
		bool MinHeap<T>::Remove(int pos, T & node)
		{
			// 删除给定下标的元素
			if ((pos < 0) || (pos >= CurrentSize))
				return false;
			node = heapArray[pos];
			heapArray[pos] = heapArray[--CurrentSize];
			if (heapArray[Parent(pos)] > heapArray[pos])
				SiftUp(pos);
			else
				SiftDown(pos);
			return true;
		}

		template<class T>
		bool MinHeap<T>::Insert(const T & newNode)
		{
			if (CurrentSize == MaxSize)	//if堆空间已经满
				return FALSE;
			heapArray[CurrentSize] = newNode; //追加至尾
			SiftUp(CurrentSize); //向上调整
			CurrentSize++; //长+1
		}

		template<class T>
		T & MinHeap<T>::RemoveMin()
		{
			if (CurrentSize == 0) {//空堆
				cout << "Can't Delete";	exit(1);
			}
			else {
				swap(0, --CurrentSize); //交换堆顶和尾元素
				if (CurrentSize > 1)         // <=1不用调整  
					SiftDown(0); 	//从堆顶开始筛选
				return heapSize[CurrentSize];
			}
		}

		template<class T>
		void MinHeap<T>::SiftUp(int position)
		{
			//从position向上开始调整，使序列成为堆
			int temppos = position;
			T temp = heapArray[temppos];  //temp暂存被调结点值
			while ((temppos > 0) && (heapArray[parent(temppos)] > temp))
			{
				//有父&&父>子：父子交换
				heapArray[temppos] = heapArray[parent(temppos)];
				temppos = parent(temppos);
			}  //继续向上找父
			heapArray[temppos] = temp; 	//子最终就位
		}

		template<class T>
		void MinHeap<T>::SiftDown(int left)
		{
			int i = left;  //标识父结点i
			int j = 2 * i + 1;     //标识关键值较小的子结点		
			T	temp = heapArray[i]; //保存父结点
			while (j < CurrentSize) {
				if ((j < CurrentSize - 1) && (heapArray[j] > heapArray[j + 1]))
					j++;  //j指向数值较小的子结点
				if (temp > heapArray[j]) {   //父>较小孩子
					heapArray[i] = heapArray[j];  //小子替换父
					i = j;     	j = 2 * j + 1;
				}  //父向下继续与孩子比
				else break;
			}
			heapArray[i] = temp;
		}

		// Huffman树
		template<class T>
		void HuffmanTree<T>::MergeTree(HuffmanTreeNode<T>& ht1, HuffmanTreeNode<T>& ht2, HuffmanTreeNode<T> *parent)
		{
			parent->element = ht1.element + ht2->element;
			parent->left = &ht1;
			parent->right = &ht2;
		}

		template<class T>
		void HuffmanTree<T>::DeleteTree(HuffmanTreeNode<T> *root)
		{
			DeleteBinaryTree(root);
		}

		template<class T>
		HuffmanTree<T>::HuffmanTree(T weight[], int n)
		{
			//weight存权值数组;n数组长
			//定义最小值堆
			MinHeap<HuffmanTreeNode<T>> heap(n);
			//parent：指向对象的指针， firstchild, secondchild ：2个对象
			HuffmanTreeNode<T> *parent, firstchild, secondchild;
			HuffmanTreeNode<T> *NodeList = new HuffmanTreeNode<T>[n];
			for (int i = 0; i < n; i++) {		//初始化
				NodeList[i].element = weight[i]; //权值
				NodeList[i].parent = NodeList[i].left = NodeList[i].right = NULL;
				heap.Insert(NodeList[i]); //向堆中添加元素
			}
			for (i = 0; i < n - 1; i++)
			{ //通过n-1次合并建立Huffman树
				parent = new HuffmanTreeNode<T>;
				firstchild = heap.RemoveMin();
				secondchild = heap.RemoveMin();
				//合并权值最小的两棵树
				MergeTree(firstchild, secondchild, parent);
				//把parent所指结点插入到堆中去
				heap.Insert(*parent);
				root = parent;  //建立根结点
			}
			delete[] NodeList;
		}

		// Trie字典树

		template<class T>
		void TrieTree<T>::insert(char * str)
		{
			TrieNode<T> *node = root;
			int i = 0, index;
			while (str[i] != '\0') {
				index = str[i] - 'a';
				if (next[index] == NULL)
					next[index] = new TrieNode<T>();
				node = node->next[index];
				i++;
			}
			node->count++;
		}

		template<class T>
		void TrieTree<T>::build_ac_automation()
		{
			using std::queue;
			int i;
			root->fail = NULL;
			queue<TrieNode*> q;
			q.push(root);
			while (!q.empty()) {
				TrieNode<T> *temp = q.front();
				q.pop();
				TrieNode<T> *p = NULL;
				// 广度优先遍历
				for (int i = 0; i < KIND; i++) {
					if (temp->next[i] != NULL) {
						if (temp == root) {
							// 当前节点是根节点
							temp->next[i]->fail = root;
						}
						else
						{
							// 是子节点
							p = temp->fail;
							while (p != NULL) {
								if (p->next[i] != NULL)
								{
									// 求child的Fail指针时，首先我们要找到其father的Fail指针所指向的节点, 
									// 假如是t的话，我们就要看t的孩子中有没有和child节点所表示的字母相同的节点，
									// 如果有的话，这个节点就是child的fail指针
									temp->next[i]->fail = p->next[i];
									break;
								}
								// 如果发现没有，则需要找father->fail->fail这个节点，然后重复上面过程，
								p = p->fail;
							}
							// 如果一直找都找不到，则child的Fail指针就要指向root。
							if (p == NULL)
								temp->next[i]->fail = root;
						}
						q.push(temp->next[i]);
					}
				}
			}
		}

		template<class T>
		int TrieTree<T>::query(char * str)
		{
			int i = 0, count = 0, index, len = strlen(str);
			TrieNode<T> *p = root;
			while (str[i] != '\0') {
				index = str[i] - 'a';
				// 对于i=0,1。Trie中没有对应的路径，故不做任何操作；
				while (p->next[index] == NULL&&p != root) {
					p = p->fail;
				}
				// i=2,3,4时，指针p走到左下节点e。
				p = p->next[index];
				p = (p == NULL) ? root : p;
				TrieNode<T> *t;
				while (t != root && t->count != -1) {
					// 因为节点e的count信息为1，所以cnt+1，
					count += t->count;
					//并且讲节点e的count值设置为-1，表示改单词已经出现过了，防止重复计数，
					t->count = -1;
					// 最后temp指向e节点的失败指针所指向的节点继续查找，以此类推，
					t = t->fail;
				}
			}
			return count;
		}

		// Keyword Tree

		inline void KeywordTree::insert(string & str)
		{
			TreeNode<char> *p = getRoot(), *q;
			for (int i = 0; i < str.size(); i++) {
				// 寻找插入位置
				while (p->getValue() > str[i]) {
					q = p;
					p = p->getSibling();
				}
				if (p = NULL) {
					TreeNode<char> *t = new TreeNode<char>(str[i]);
					q->setSibling(t);
					t->setSibling(p);
					p = t->getChild();
				} else if (q->getValue() == str[i]){
					p = q->getChild();
				} else {
					TreeNode<char> *t = new TreeNode<char>(str[i]);
					t->setSibling(getRoot());
					p = t->getChild();
				}
			}
		}

		// 红黑树

		template<class T>
		RBNode<T>::RBNode(RBNode<T> *parent, RBNode<T> *left, RBNode<T> *right, T key, COLOR color)
		{
			this->key = key;
			this->color = color;
			this->parent = parent;
			this->left = left;
			this->right = right;
		}

		template<class T>
		void RBTree<T>::Insert(const T & key)
		{
			//if (root->isLeaf()) {
			//	root->key = key;
			//	root->left = new RBNode<T>(root);
			//	root->right = new RBNode<T>(root);
			//	if (root->parent->color == RED) {
			//		RedToBlack(root);
			//	}
			//}
			//else if (key < root->key) {
			//	Insert(root->left, key);
			//}
			//else if (key > root->key) {
			//	Insert(root->right, key);
			//}
			//else {
			//	throw exception();
			//}
		}

		template<class T>
		void RBTree<T>::Remove(const T & key)
		{
		}

		template<class T>
		void RBTree<T>::Find(const T & key)
		{
		}

		template<class T>
		void RBTree<T>::RedToBlack(RBNode<T> *root)
		{
			RBNode<T>*parent = root->parent;
			if (parent->left->color == parent->right->color) {
				// 叔父同为红色 父辈祖辈换色
				parent->color = RED;
				parent->left->color = BLACK;
				parent->right->color = BLACK;
				// 如果祖辈的父辈也是红色，则递归处理
				if (parent->parent->color = RED)
					RedToBlack(parent->parent);
			}
			else {
				// 叔父不同色，分左旋或右旋
				if (root->parent->left) {
					// 父节点是左子节点，则右旋 如果新增节点是右子节点，则调整为左子节点
					if (root->left->key == NULL) {
						// 借助空节点作为temp节点
						root->left->key = root->key;
						root->key = root->right->key;
						root->right->key = root->left->key;
						root->left->key = NULL;
						// 左子和右子交换即可
						RBNode<T>*temp = root->left;
						root->left = root->right;
						root->right = temp;
						temp = NULL;
					}
					// 改父节点的父节点指向原祖父的父节点
					root->parent = parent->parent;
					// 改指向原祖节点的子节点指向父节点
					if (root->parent->left == parent)
						root->parent->left = root;
					else
						root->parent->right = root;

					// 改原祖节点的父节点和左子节点
				}
				else {
					// 父节点是右子节点，则左旋
				}
			}
		}

	}
	namespace Graph {

		// 邻接多重表
		template<class TV, class TE>
		void AMGraph<TV, TE>::AddVertex(AMVertex<TV, TE> *v)
		{
			vec.push_back(v);
		}

		template<class TV, class TE>
		void AMGraph<TV, TE>::AddEdge(AMEdge<TV, TE> *e)
		{
			// 添加u指向的边
			AMVertex<TV, TE> *u = find(vec.begin(), vec.end(), e->from);
			if (u->head = NULL)
				u->head = e;
			else {
				AMEdge<TV, TE> *t = u->head;
				while (t->ulink != NULL) {
					t = t->ulink;
				}
				t->ulink = e;
			}
			// 添加到达v的边
			AMVertex<TV, TE> *v = find(vec.begin(), vec.end(), e->to);
			if (v->head == NULL)
				v->head = e;
			else {
				v->head = v;
			}
		}

		template<class TV, class TE>
		void AMGraph<TV, TE>::RemoveVertex(int v)
		{
		}

		template<class TV, class TE>
		void AMGraph<TV, TE>::RemoveEdge(int u, int v)
		{
		}

		// 十字链表

		template<class TV, class TA>
		OLGraph<TV, TA>::OLGraph(vector<Point<TV>> points, vector<Edge<TA>> edges)
		{
			// 添加所有节点
			for (Point<TV> point : points) {
				vertices.push_back(Vertex<TV, TA>(point.element));
			}
			for (Edge<TA> edge : edges) {
				// 建立弧
				Arc<TA> *arc = new Arc<TA>();
				arc->from = edge.from;
				arc->to = edge.to;
				// 插入节点
				arc->hLink = vertices[edge.from]->first_in;
				arc->tLink = vertices[edge.to]->first_out;
				vertices[edge.from]->first_in = arc;
				vertices[edge.to]->first_out = arc;
			}
		}
	};

	namespace Sort {

		template<class T>
		void InsertSort(T * vec, int n)
		{
		}

		template<class T>
		void BinaryInsertSort(T *vec, int n)
		{
			int i, j, low, high, mid, temp;
			low = high = temp = 0;
			for (i = 1; i < n; i++) {
				low = 0;
				high = i - 1;
				temp = vec[i];
				// low表示二分查找插入的位置
				while (low < high) {
					mid = (low + high) / 2;
					if (vec[mid] > temp) {
						high = mid - 1;
					}
					else {
						low = mid + 1;
					}
				}
				// 有序表中插入位置后的元素后移
				for (j = i; j > low; j--) {
					vec[j] = vec[j - 1];
				}
				vec[low] = temp;
			}
		}

		template<class T>
		void TwoWayInsertSort(T * vec, T * dst, int n)
		{
			int head, tail;
			head = tail = 0;
			dst[head] = vec[head];
			for (int i = 1; i < n; i++) {
				if (vec[i] < dst[head]) {
					head = (head - 1 + n) % n;
					dst[head] = vec[i];
				}
				else if (vec[i] > dst[tail]) {
					tail = (tail + 1 + n) % n;
					dst[tail] = vec[i];
				}
				else {
					int k = (tail + 1 + n) % n; // 尾部
					while (dst[(k - 1 + n) % n] > vec[i]) {
						// 大的往后移动
						dst[(k + n) % n] = dst[(k - 1 + n) % n];
						k = (k - 1 + n) % n;
					}
					// 插入该值
					dst[(k + n) % n] = vec[i];
					// 改变tail的位置
					tail = (tail + 1 + n) % n;
				}
			}
			// 将排序记录复制到原来的顺序表中
			for (int k = 0; k < n; k++) {
				vec[k] = dst[(head + k) % n];
			}
		}

		template<class T>
		void ShellSort(T *vec, int left, int right)
		{
			// 选取步长
			for (int k = right / 2; k > 1; k /= 2) {
				// 对于每一列
				for (int i = 0; i < k; i++) {
					// 插入排序
					for (int j = k; j < right; j += k) {
						int p = j - k;
						T t = vec[p];
						while ((p >= left) && (vec[p] > t)) {
							vec[p + k] = vec[p];
							p -= k;
						}
						vec[p + k] = t;
					}
				}
			}
		}

		template<class T>
		void BubbleSort(T *vec, int n)
		{
			bool key = false;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n - i; j++) {
					if (vec[j] > vec[j + 1]) {
						swap(&vec[j], &vec[j + 1]);
						key = true;
					}
				}
				if (key == 0)
					break;
			}
		}

		template<class T>
		void QuickSort(T * vec, int left, int right)
		{
		}

		template<class T>
		void SelectSort(T * vec, int n)
		{
			for (int i = 0; i < n - 1; i++) {
				int min = i;
				for (int j = i + 1; j < n; j++) {
					if (vec[min] > vec[j]) {
						min = j;
					}
				}
				if (min != i) {
					swap(&vec[i], &vec[min]);
				}
			}
		}

		template<class T>
		void PrintArray(T a[], int n) {
			for (int i = 0; i < n; i++) {
				std::cout << std::setw(4) << a[i];
			}
			std::cout << std::endl;
		}

		void test_2_8()
		{
			int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
			cout << "2.8 希尔排序" << endl;
			ShellSort(a, 0, 10);
			std::cout << "a:" << std::endl;
			PrintArray(a, 11);
			getchar();
		}
	}
}