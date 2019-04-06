#include "ds.h"

namespace Exam2015 {

	using namespace std;

	namespace Problem1 {

		class Polynomial {
			Polynomial*child;
		};
	}
	// ������
	void SimplePath(int*path, int depth, int**G, int u, int v) {
		// ��¼·��
		path[depth] = u;
		// ���·��
		if (u == v) {
			for (int i = 0; i < depth; i++) {
				printf("%d ", path[i]);
			}
			return;
		}
		// ������ȱ���
		for (int j = 0; j < 10; j++) {
			if (G[u][j] > 0) {
				SimplePath(path, depth + 1, G, j, v);
			}
		}
	}
	// ������
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
	// ������
	int PatternMatch(string s, string p, int startIndex) {
		int lastIndex = s.size() - p.size();
		if (lastIndex < startIndex)
			return -1;
		int i = startIndex, j = 0;
		int start; // ��¼��ǰƥ�����ʼλ��
		start = i;
		while (i < s.size() && j < p.size()) {
			if (p[j] == s[i]) {
				i++, j++;
			}
			// ���俼�ǡ���������*�������
			else if (p[j] == '?') {
				i++, j++;
				continue;
			}
			else if (p[j] == '*') {
				j++;
				// ȡ��p�С�*������ַ���ȡ����s�ж�Ӧ�ڡ�*�����ַ���������ַ������µ�ƥ��
				int a = PatternMatch(s.substr(i, s.size() - i), p.substr(j, p.size() - j), 0);
				if (a >= 0) {
					// ��a����0��˵���Ѿ�ƥ��ɹ���ֻ��Ҫ���س�ʼƥ��λ��
					return start;
				}
			}
			else {
				// ��start������¼��ƥ�����ʼλ��
				i = i - j + 1;
				start = i;
				j = 0;
			}
		}
		// ��ƥ��ɹ����򷵻ص�����ʼλ��start
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

	// ϡ����� - ʮ������
	template<class T>
	void SMatrix<T>::Insert(int row, int col, T val)
	{
		OLNode<T>*p, *q, *r, *u, *v;
		if (row<0 || row>rowNum || col<0 || col>colNum)
			return;
		r = new OLNode<T>(row, col, val);
		// ��
		p = rowhead[row];
		q = p->right;
		while (q->col < col) {
			p = q;
			q = q->right;
		}
		if (q->col == col)
			return;
		// ��
		u = colhead[col];
		v = u->down;
		while (v->row < row) {
			u = v;
			v = v->down;
		}
		if (v->row == row)
			return;
		// ����
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
		// ��
		p = rowhead[row];
		q = p->right;
		while (q->col <= col) {
			p = q;
			q = q->right;
		}
		if (q->col != col) // ����û��col��Ԫ��
			return;
		q = q->right;
		// ��
		u = colhead[col];
		v = u->down;
		while (v->row <= row) {
			u = v;
			v = v->down;
		}
		if (v->row != row) // ����û��row��Ԫ��
			return;
		v = v->down;
		// ɾ���ɹ�
		r = p->right;
		T val = r->element;
		delete r;
		// ����
		p->right = q; u->down = v;
		return val;
	}

	template<class T>
	T SMatrix<T>::Get(int row, int col)
	{
		OLNode<T>*p, *q;
		if (row<0 || row>rowNum || col<0 || col>colNum)
			return;
		// ����
		p = rowhead[row];
		q = p->right;
		while (q->col <= col) {
			p = q;
			q = q->right;
		}
		// ����û��col��Ԫ��
		if (q->col != col)
			return NULL;
		return q->element;
	}

	template<class T>
	SMatrix<T>& SMatrix<T>::operator+(SMatrix<T>& b)
	{
		// TODO: �ڴ˴����� return ���
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
			// ����ÿһ�з���Ԫ�ظ���
			for (int i = 0; i < length; i++) {
				num[data[i].col]++;
			}
			// ����ÿһ�е���ʼλ��
			position[0] = 0;
			for (int j = 1; j < col; j++) {
				position[j] = position[j - 1] + num[j - 1];
			}
			// ת��
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

		// �������ڵ���
		template<class T>
		BinaryTreeNode<T>::BinaryTreeNode(T element, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right)
		{
			this->element = element;
			this->left = left;
			this->right = right;
		}

		// ������
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
				// ������ǰ�ڵ���������
				temp = root->left;
				root->left = root->right;
				root->right = temp;
				// �ݹ齻��
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
			//��current˫�׷���
			using std::stack;
			stack <BinaryTreeNode<T>*> aStack;
			BinaryTreeNode<T>*p = root;
			if (root != NULL&& current != NULL) {
				while (!aStack.empty() || p) {
					if (p != NULL) {
						if (current == p->left || current == p->right)
							return p; //����˫��
						aStack.push(p);	 p = p->left;
					}//��ջ ָ����
					else {
						p = aStack.top();
						aStack.pop(); //��ջ
						p = p->right; //ָ������
					}
				}
			}
		}

		template<class T>
		BinaryTreeNode<T> *BinaryTree<T>::LeftSibling(BinaryTreeNode<T> *current)
		{
			//����current�������ֵ�
			if (current) //current��Ϊ��
			{
				//����current���ĸ����
				BinaryTreeNode<T> *temp = Parent(current);
				//��������Ϊ�գ�����currentû�����ֵ�
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
				// �ȷ��ʵ�ǰ�ڵ�
				(*Visit)(p->element);
				// ���ӷǿ���ջ
				if (p->right != NULL)aStack.push(p->right);
				// ������������
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
			// ����ǵݹ����ζ�����
			using std::stack;
			stack<BinaryTreeNode<T>*> aStack;
			BinaryTreeNode<T> *p = root;
			while (!aStack.empty() || p) {
				if (p) {
					// �������ߵ��ף�������ֻ��ջ
					aStack.push(p);
					p = p->left;
				}
				else {
					p = aStack.top(); // ȡջ��
					aStack.pop(); // ��ջ
					(*Visit)(p->element); // ���ʵ�ǰ�ڵ�
					p = p->right; // �ҿ�һ��ָ�����ӣ��ظ�֮ǰ����
				}
			}
		}

		template<class T>
		void BinaryTree<T>::PostOrderWithoutRecursion(void(*Visit)(T element))
		{
			// ����ǵݹ����ζ�����
			using std::stack;
			StackElement<T> element;
			stack<StackElement<T>> aStack;
			BinaryTreeNode<T>*p;
			if (root == NULL)
				return;
			else
				p = root;
			while (!aStack.empty() || p) {
				// ����p��������
				while (p != NULL) {
					element.pointer = p;
					element.tag = LEFT;
					aStack.push(element);
					p = p->left;
				}
				// ȡջ��Ԫ�أ���ջ
				element = aStack.top();
				aStack.pop();
				p = element.pointer;
				// ������������
				if (element.tag == LEFT) {
					element.tag = RIGHT;
					aStack.push(element);
					// p�Ƶ�������
					p = p->right;
				}
				else {
					// ���ʵ�ǰ�ڵ�
					(*Visit)(p->element);
					p = NULL; // ���Ϊ�˼�����ջ
				}
			}
		}

		template<class T>
		void BinaryTree<T>::LevelOrder(void(*Visit)(T element))
		{
			//����������ζ�����
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

		// ����������

		template<class T>
		void ThreadBinaryTree<T>::Insert(ThreadBinaryTreeNode<T> *p, ThreadBinaryTreeNode<T> *r)
		{
			// rΪ��������½ڵ㣬pָ���߶�������һ���ڵ�
			ThreadBinaryTreeNode<T> *temp = NULL;
			if (p->left == NULL) {
				temp = NULL;
			}
			else if (p->ltag == true) {
				// ����Ϊ������ǰ��Ϊ����
				temp = p->left;
			}
			else {
				// ǰ��Ϊ�������������ε����һ����
				temp = p->left;
				while (temp->rtag == false) {
					temp = temp->right;
				}
			}
			// ��ʱ��tempָ��p������ǰ��
			if (temp != NULL && temp->rtag == true) {
				temp->right = r;
			}
			// �����½ڵ����ָ���������
			r->ltag = p->ltag;
			r->left = p->left;
			// �����½ڵ�
			p->ltag = false;
			p->left = r;
			// �����½ڵ�������
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
					// ���������ӽڵ�
					if (p->left != NULL)
						p->ltag = false;
					else
					{
						p->ltag = true; p->left = last;
					}
					// ���������ӽڵ�
					if (last != NULL)
						if (last->right != NULL)
							last->rtag = false;
						else
						{
							last->rtag = true, last->right = p;
						}
					last = p;
					// �������
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
					// ��ǰ�ڵ��������
					if (p->left != NULL) p->ltag = false;
					else { p->ltag = true; p->left = last; }
					// ��һ���ڵ��������
					if (last != NULL)
						if (last->right != NULL) last->rtag = false;
						else { last->rtag = true; last->right = p; }
						// ��¼��ǰ�ڵ�
						last = p;
						// �����ҽڵ�
						p = p->right;
				}
				last->rtag = true; // ���һ���ڵ���Ҷ�ӽڵ�
			}
		}

		template<class T>
		void ThreadBinaryTree<T>::PreOrderThread(void(*Visit)(T elem))
		{
			// �����������������������
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
					p = p->left; // Ѱ������Ľڵ�
				while (p != NULL) {
					Visit(p->element);
					if (p->rtag = true)
						p = p->right; // ͨ���������ҵ����
					else {
						// ����������������ڵ�Ϊ���
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
			// �������߶������в���ָ���ڵ��ں����µ�ǰ��
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

		// ����������

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
			// �ǵݹ��������������
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
				//�½������
				root = node;
				return;
			}
			else
				p = root;
			while (p != NULL) {
				//��� ���ò���
				if (node->getValue() == p->getValue())
					return;
				else if (node->getValue() < p->getValue()) {
					//����С
					if (p->getLeftChild() == NULL) {
						//��Ϊ������
						p->left = node;
						return;
					}
					else
						p = p->getLeftChild();
				}
				else {
					if (p->getRightChild() == NULL) {
						//��Ϊ������
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
				// ��������
				s = p->right;
			}
			else {
				// ��������
				s = p->left;
				while (s->right != NULL) {
					tempparent = s;
					s = s->right;
				}
				//p->lcû����(CrΪ��û�������ƶ�)
				if (tempparent == NULL)
					p->left = s->left;  //p��������C���,p->lcָCl
				else
					tempparent->right = s->left; //tempp����Sl���丸Q������
				s->left = p->left;//tempp(��S)����p�ӹ�p��������
				s->right = p->right;
			}
			if (parent == NULL) //FΪ����p���������tempp�滻��ɾp����
				root = s;
			else if (parent->left == p) //ifɾparent������p
				parent->left = s;  //��s(��tempp)���p��parent����
			else
				parent->right = s; //ɾ����parent����p
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

		// AVL��

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
			// ��ʼ��
			b = a->left; c = b->right;
			// ж��c�������Ӹ�b��a
			a->left = c->right; b->right = c->left;
			// ����c��������Ϊb��a
			c->left = b; c->right = a;
			// ����ƽ������
			if (c->factor == 1) {
				a->factor = -1;	b->factor = 0;// �����
			}
			else if (c->factor == 0) {
				a->factor = b->factor = 0; // ƽ��
			}
			else {
				a->factor = 0; b->factor = 1; // �ұ���
			}
			// ����������
			a = c;
		}

		template<class T>
		void AVLTree<T>::RRRotate(AVLTreeNode<T>* a)
		{
			AVLTreeNode<T> *b;
			b = a->right;
			// ж��b�����Ӹ�a������
			a->right = b->left;
			// a��Ϊb������
			b->left = a;
			// ����ƽ�����ӣ�����������
			a->factor = b->factor = 0; a = b;
		}

		template<class T>
		void AVLTree<T>::RLRotate(AVLTreeNode<T>* a)
		{
			AVLTreeNode<T> *b, *c;
			// ��ʼ��b��c
			b = a->right; c = b->left;
			// ж��c�������Ӹ�a��b
			a->right = c->left; b->left = c->right;
			// ����c��������Ϊa��b
			c->left = a; c->right = b;
			// ����ƽ������
			if (c->factor == 1) {
				a->factor = 0; b->factor = -1;
			}
			else if (c->factor == 0) {
				a->factor = b->factor = 0;
			}
			else {
				a->factor = 1; b->factor = 0;
			}
			// ��������
			a = c;
		}

		// ɭ�� - �������ֱ�ʾ��

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
				// ɭ�ֵ������������
				while (pointer != NULL) {
					if (current == pointer)
						return NULL;
					aQueue.push(pointer);
					pointer = pointer->pSibling;
				}
				while (!aQueue.empty()) {
					pointer = aQueue.front();
					aQueue.pop(); // ȡ��ͷ
					parent = pointer; // ��
					pointer = pointer->LeftMostChild(); // ��
					// pointer�������ֵ���current��
					while (pointer) {
						if (current == pointer)
							return parent; // �ҵ�parent
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
			// ��������ɾ
			if (subroot == NULL) return;
			// pointָ��subroot(��ɾ��������)�����
			pointer = Parent(subroot);
			// subrootû��:��ɾ������ɭ��ĳ����(���ָ��� )
			if (pointer == NULL) {
				// ��ɾ������ɭ���е�һ����
				if (subroot == root) {
					root = subroot->RightSibling();
				}
				else {
					// ɾ������:��root���ұ�ɾ��ǰ��(����)
					TreeNode<T> *r = root;
					while (r->RightSibling() != subroot) {
						r = r->RightSibling();
					}
					r->RightSibling() = subroot->RightSibling();
				}
			}
			else if (pointer->LeftMostChild() == subroot) {
				// ��ɾ���Ǹ��������ӣ���subroot��������pointer������
				pointer->setChild(subroot->RightSibling());
			}
			else {
				// ��ɾ(subroot����������)������,��subroot����pSiblingָ��ɾ������
				pointer = pointer->LeftMostChild();
				// ����ֱ������
				while (pointer->RightSibling() != subroot)
					pointer = pointer->RightSibling();
				//������pointer�����Ǳ�ɾ��subroot����
				pointer->setSibling(subroot->RightSibling());
			}
			//��ɾ�������ÿ�(�ж���ԭ�����ӳ�Ϊ������ɭ��)
			subroot->setSibling(NULL);
			//ɾ��
			DestroyNodes(subroot);
		}

		// ��С��
		template<class T>
		void MinHeap<T>::BuildHeap()
		{
			//�����һ�������������һɸѡ
			for (int i = CurrentSize / 2 - 1; i >= 0; i--)
				SiftDown(i);
		}

		template<class T>
		MinHeap<T>::MinHeap(const int n)
		{
			if (n <= 0)
				return;
			CurrentSize = 0;
			MaxSize = n; 			//��ʼ��������Ϊn
			heapArray = new T[MaxSize]; //�����ѿռ�
			BuildHeap();  			//����
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
			return 2 * pos + 1;	//����pos������λ��
		}

		template<class T>
		int MinHeap<T>::RightChild(int pos) const
		{
			return 2 * pos + 2;  	//����pos���Һ���λ��
		}

		template<class T>
		int MinHeap<T>::Parent(int pos) const
		{
			return (pos - 1) / 2; 	//����pos�ĸ����λ��
		}

		template<class T>
		bool MinHeap<T>::Remove(int pos, T & node)
		{
			// ɾ�������±��Ԫ��
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
			if (CurrentSize == MaxSize)	//if�ѿռ��Ѿ���
				return FALSE;
			heapArray[CurrentSize] = newNode; //׷����β
			SiftUp(CurrentSize); //���ϵ���
			CurrentSize++; //��+1
		}

		template<class T>
		T & MinHeap<T>::RemoveMin()
		{
			if (CurrentSize == 0) {//�ն�
				cout << "Can't Delete";	exit(1);
			}
			else {
				swap(0, --CurrentSize); //�����Ѷ���βԪ��
				if (CurrentSize > 1)         // <=1���õ���  
					SiftDown(0); 	//�ӶѶ���ʼɸѡ
				return heapSize[CurrentSize];
			}
		}

		template<class T>
		void MinHeap<T>::SiftUp(int position)
		{
			//��position���Ͽ�ʼ������ʹ���г�Ϊ��
			int temppos = position;
			T temp = heapArray[temppos];  //temp�ݴ汻�����ֵ
			while ((temppos > 0) && (heapArray[parent(temppos)] > temp))
			{
				//�и�&&��>�ӣ����ӽ���
				heapArray[temppos] = heapArray[parent(temppos)];
				temppos = parent(temppos);
			}  //���������Ҹ�
			heapArray[temppos] = temp; 	//�����վ�λ
		}

		template<class T>
		void MinHeap<T>::SiftDown(int left)
		{
			int i = left;  //��ʶ�����i
			int j = 2 * i + 1;     //��ʶ�ؼ�ֵ��С���ӽ��		
			T	temp = heapArray[i]; //���游���
			while (j < CurrentSize) {
				if ((j < CurrentSize - 1) && (heapArray[j] > heapArray[j + 1]))
					j++;  //jָ����ֵ��С���ӽ��
				if (temp > heapArray[j]) {   //��>��С����
					heapArray[i] = heapArray[j];  //С���滻��
					i = j;     	j = 2 * j + 1;
				}  //�����¼����뺢�ӱ�
				else break;
			}
			heapArray[i] = temp;
		}

		// Huffman��
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
			//weight��Ȩֵ����;n���鳤
			//������Сֵ��
			MinHeap<HuffmanTreeNode<T>> heap(n);
			//parent��ָ������ָ�룬 firstchild, secondchild ��2������
			HuffmanTreeNode<T> *parent, firstchild, secondchild;
			HuffmanTreeNode<T> *NodeList = new HuffmanTreeNode<T>[n];
			for (int i = 0; i < n; i++) {		//��ʼ��
				NodeList[i].element = weight[i]; //Ȩֵ
				NodeList[i].parent = NodeList[i].left = NodeList[i].right = NULL;
				heap.Insert(NodeList[i]); //��������Ԫ��
			}
			for (i = 0; i < n - 1; i++)
			{ //ͨ��n-1�κϲ�����Huffman��
				parent = new HuffmanTreeNode<T>;
				firstchild = heap.RemoveMin();
				secondchild = heap.RemoveMin();
				//�ϲ�Ȩֵ��С��������
				MergeTree(firstchild, secondchild, parent);
				//��parent��ָ�����뵽����ȥ
				heap.Insert(*parent);
				root = parent;  //���������
			}
			delete[] NodeList;
		}

		// Trie�ֵ���

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
				// ������ȱ���
				for (int i = 0; i < KIND; i++) {
					if (temp->next[i] != NULL) {
						if (temp == root) {
							// ��ǰ�ڵ��Ǹ��ڵ�
							temp->next[i]->fail = root;
						}
						else
						{
							// ���ӽڵ�
							p = temp->fail;
							while (p != NULL) {
								if (p->next[i] != NULL)
								{
									// ��child��Failָ��ʱ����������Ҫ�ҵ���father��Failָ����ָ��Ľڵ�, 
									// ������t�Ļ������Ǿ�Ҫ��t�ĺ�������û�к�child�ڵ�����ʾ����ĸ��ͬ�Ľڵ㣬
									// ����еĻ�������ڵ����child��failָ��
									temp->next[i]->fail = p->next[i];
									break;
								}
								// �������û�У�����Ҫ��father->fail->fail����ڵ㣬Ȼ���ظ�������̣�
								p = p->fail;
							}
							// ���һֱ�Ҷ��Ҳ�������child��Failָ���Ҫָ��root��
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
				// ����i=0,1��Trie��û�ж�Ӧ��·�����ʲ����κβ�����
				while (p->next[index] == NULL&&p != root) {
					p = p->fail;
				}
				// i=2,3,4ʱ��ָ��p�ߵ����½ڵ�e��
				p = p->next[index];
				p = (p == NULL) ? root : p;
				TrieNode<T> *t;
				while (t != root && t->count != -1) {
					// ��Ϊ�ڵ�e��count��ϢΪ1������cnt+1��
					count += t->count;
					//���ҽ��ڵ�e��countֵ����Ϊ-1����ʾ�ĵ����Ѿ����ֹ��ˣ���ֹ�ظ�������
					t->count = -1;
					// ���tempָ��e�ڵ��ʧ��ָ����ָ��Ľڵ�������ң��Դ����ƣ�
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
				// Ѱ�Ҳ���λ��
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

		// �����

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
				// �常ͬΪ��ɫ �����汲��ɫ
				parent->color = RED;
				parent->left->color = BLACK;
				parent->right->color = BLACK;
				// ����汲�ĸ���Ҳ�Ǻ�ɫ����ݹ鴦��
				if (parent->parent->color = RED)
					RedToBlack(parent->parent);
			}
			else {
				// �常��ͬɫ��������������
				if (root->parent->left) {
					// ���ڵ������ӽڵ㣬������ ��������ڵ������ӽڵ㣬�����Ϊ���ӽڵ�
					if (root->left->key == NULL) {
						// �����սڵ���Ϊtemp�ڵ�
						root->left->key = root->key;
						root->key = root->right->key;
						root->right->key = root->left->key;
						root->left->key = NULL;
						// ���Ӻ����ӽ�������
						RBNode<T>*temp = root->left;
						root->left = root->right;
						root->right = temp;
						temp = NULL;
					}
					// �ĸ��ڵ�ĸ��ڵ�ָ��ԭ�游�ĸ��ڵ�
					root->parent = parent->parent;
					// ��ָ��ԭ��ڵ���ӽڵ�ָ�򸸽ڵ�
					if (root->parent->left == parent)
						root->parent->left = root;
					else
						root->parent->right = root;

					// ��ԭ��ڵ�ĸ��ڵ�����ӽڵ�
				}
				else {
					// ���ڵ������ӽڵ㣬������
				}
			}
		}

	}
	namespace Graph {

		// �ڽӶ��ر�
		template<class TV, class TE>
		void AMGraph<TV, TE>::AddVertex(AMVertex<TV, TE> *v)
		{
			vec.push_back(v);
		}

		template<class TV, class TE>
		void AMGraph<TV, TE>::AddEdge(AMEdge<TV, TE> *e)
		{
			// ���uָ��ı�
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
			// ��ӵ���v�ı�
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

		// ʮ������

		template<class TV, class TA>
		OLGraph<TV, TA>::OLGraph(vector<Point<TV>> points, vector<Edge<TA>> edges)
		{
			// ������нڵ�
			for (Point<TV> point : points) {
				vertices.push_back(Vertex<TV, TA>(point.element));
			}
			for (Edge<TA> edge : edges) {
				// ������
				Arc<TA> *arc = new Arc<TA>();
				arc->from = edge.from;
				arc->to = edge.to;
				// ����ڵ�
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
				// low��ʾ���ֲ��Ҳ����λ��
				while (low < high) {
					mid = (low + high) / 2;
					if (vec[mid] > temp) {
						high = mid - 1;
					}
					else {
						low = mid + 1;
					}
				}
				// ������в���λ�ú��Ԫ�غ���
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
					int k = (tail + 1 + n) % n; // β��
					while (dst[(k - 1 + n) % n] > vec[i]) {
						// ��������ƶ�
						dst[(k + n) % n] = dst[(k - 1 + n) % n];
						k = (k - 1 + n) % n;
					}
					// �����ֵ
					dst[(k + n) % n] = vec[i];
					// �ı�tail��λ��
					tail = (tail + 1 + n) % n;
				}
			}
			// �������¼���Ƶ�ԭ����˳�����
			for (int k = 0; k < n; k++) {
				vec[k] = dst[(head + k) % n];
			}
		}

		template<class T>
		void ShellSort(T *vec, int left, int right)
		{
			// ѡȡ����
			for (int k = right / 2; k > 1; k /= 2) {
				// ����ÿһ��
				for (int i = 0; i < k; i++) {
					// ��������
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
			cout << "2.8 ϣ������" << endl;
			ShellSort(a, 0, 10);
			std::cout << "a:" << std::endl;
			PrintArray(a, 11);
			getchar();
		}
	}
}