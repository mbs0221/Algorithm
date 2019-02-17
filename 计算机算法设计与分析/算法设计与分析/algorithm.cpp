#include "algorithm.h"

namespace Exam2015 {

	using namespace std;

	template<class T>
	void PrintArray(T a[], int n) {
		for (int i = 0; i < n; i++) {
			std::cout << std::setw(4) << a[i];
		}
		std::cout << std::endl;
	}

	namespace Problem1 {
		void ShellSort(int *a, int left, int right)
		{
			// ѡȡ����
			for (int k = right / 2; k > 1; k /= 2) {
				// ����ÿһ��
				for (int i = 0; i < k; i++) {
					// ��������
					for (int j = k; j < right; j += k) {
						int p = j - k;
						int t = a[p];
						while ((p >= left) && (a[p] > t)) {
							a[p + k] = a[p];
							p -= k;
						}
						a[p + k] = t;
					}
				}
			}
		}
		class Polynomial {
			Polynomial *child;
		};
	}
	// ������
	void SimplePath(int *path, int depth, int **G, int u, int v) {
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
		DigitalSearchTree *child[27];
	public:
		void Add(string name) {
			DigitalSearchTree *tree = this;
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

	void test_2_8()
	{
		int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
		cout << "2.8 ϣ������" << endl;
		Problem1::ShellSort(a, 0, 10);
		std::cout << "a:" << std::endl;
		PrintArray(a, 11);
		getchar();
	}
}

namespace Algorithm {

	// ϡ����� - ʮ������
	template<class T>
	void SMatrix<T>::insertOLNode(int row, int col, T val)
	{
		OLNode<T> *p, *q, *r, *u, *v;
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
	T SMatrix<T>::deleteOLNode(int row, int col)
	{
		OLNode<T> *p, *q, *r, *u, *v;
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
	T SMatrix<T>::getElement(int row, int col)
	{
		OLNode<T> *p, *q;
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
	SMatrix<T> & SMatrix<T>::MatrixAdd(SMatrix<T>& m1, SMatrix<T>& m2)
	{
		OLNode *p, *q, *u, *v;
		SMatrix r(m1.rowNum, m2.colNum);
		p = m1.rowhead;
		u = m2.rowhead;
		
		// TODO: �ڴ˴����� return ���
		return r;
	}
	template<class T>
	TSMatrix<T>& TSMatrix<T>::Transpose(TSMatrix<T>& a)
	{
		int num[MAX_SIZE], position[MAX_SIZE];
		TSMatrix<T> b;
		b.lenght = a.lenght; b.n = a.m; b.m = a.n;
		if (b.lenght) {
			for (int col = 0; col < a.m; col++) {
				num[col] = 0;
			}
			// ����ÿһ�з���Ԫ�ظ���
			for (int t = 0; t < a.lenght; t++) {
				num[a.data[t].col]++;
			}
			// ����ÿһ�е���ʼλ��
			position[0] = 0;
			for (int col = 1; col < a.n; col++) {
				position[col] = position[col - 1] + num[col - 1];
			}
			// ת��
			for (int p = 0; p < a.lenght; p++) {
				int col = a.data[p].col;
				int q = position[col];
				b.data[q].row = a.data[p].col;
				b.data[q].col = a.data[p].row;
				b.data[q].e = a.data[p].data;
				position[col]++;
			}
		}
		// TODO: �ڴ˴����� return ���
		return b;
	}

	// ������
	template<class T>
	int BinaryTree<T>::LeafNumber(BinaryTreeNode<T>* root)
	{
		if (root == NULL) return 0;
		if (root->isLeaf()) return 1;
		return LeafNumber(root->left) + LeafNumber(root->right);
	}
	template<class T>
	int BinaryTree<T>::GetHeight(BinaryTreeNode<T>* root)
	{
		if (root == NULL) return 0;
		int h1 = GetHeight(root->left) + 1;
		int h2 = GetHeight(root->right) + 1;
		return h1 > h2 ? h1 : h2;
	}
	template<class T>
	int BinaryTree<T>::Exchange(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T> *temp;
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
	void BinaryTree<T>::DepthOrder(BinaryTreeNode<T>* root, void (*Visit)(T element))
	{
		if (!root) {
			(*Visit)(root->element);
			DepthOrder(root->left);
			DepthOrder(root->right);
		}
	}
	template<class T>
	void BinaryTree<T>::PreOrderWithoutRecursion(BinaryTreeNode<T>* root, void (*Visit)(T element))
	{
		using std::stack;
		stack<BinaryTreeNode<T>*> aStack;
		BinaryTreeNode<T>* p = root;
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
	void BinaryTree<T>::InOrderWithoutRecursion(BinaryTreeNode<T>* root, void (*Visit)(T element))
	{
		using std::stack;
		stack<BinaryTreeNode<T>*> aStack;
		BinaryTreeNode<T>* p = root;
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

	// ɭ��
	TreeNode<T>* Tree<T>::Parent(TreeNode<T>* current)
	{
		using std::queue;
		queue<TreeNode<T>*> aQueue;
		TreeNode<T> *pointer = root;
		TreeNode<T> *parent = NULL;
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
	void Tree<T>::DestroyNodes(TreeNode<T>* root)
	{
		if (root != NULL) {
			DestroyNodes(root->LeftMostChild());
			DestroyNodes(root->RightSibling());
			delete root;
		}
	}
	template<class T>
	void Tree<T>::DeletSubTree(TreeNode<T>* subroot)
	{
		TreeNode<T> *pointer;
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
				TreeNode<T> * r = root;
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
	template<class T>

	// �� - ˫��Ǳ�ʾ��
	DualTagTree<T>::DualTagTree(DualTagTreeNode<T>* nodeArray, int count)
	{
		using std::stack;
		stack<DualTagTreeNode<T>*> aStack;
		
	}
	
	// �����
	template<class KEY, class COLOR>
	RBNode<KEY, COLOR>::RBNode(RBNode * parent, RBNode * left, RBNode * right, KEY key, COLOR color)
	{
		this->key = key;
		this->color = color;
		this->parent = parent;
		this->left = left;
		this->right = right;
	}
	template<class KEY, class COLOR>
	void RBTree<KEY, COLOR>::insert(RBNode<KEY, COLOR> *root, const KEY & key)
	{
		if (root->isLeaf()) {
			root->key = key;
			root->left = new RBNode<KEY, COLOR>(root);
			root->right = new RBNode<KEY, COLOR>(root);
			if (root->parent->color == RED) {
				RedToBlack(root);
			}
		}
		else if (key < root->key) {
			insert(root->left, key);
		}
		else if (key > root->key) {
			insert(root->right, key);
		}
		else {
			throw exception();
		}
	}
	template<class KEY, class COLOR>
	void RBTree<KEY, COLOR>::RedToBlack(RBNode<KEY, COLOR>* root)
	{
		RBNode<KEY, COLOR> *parent = root->parent;
		if (parent->left->color == parent->right->color) {
			// �常ͬΪ��ɫ
			// �����汲��ɫ
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
				// ���ڵ������ӽڵ㣬������
				// ��������ڵ������ӽڵ㣬�����Ϊ���ӽڵ�
				if (root->left->key == NULL) {
					// �����սڵ���Ϊtemp�ڵ�
					root->left->key = root->key;
					root->key = root->right->key;
					root->right->key = root->left->key;
					root->left->key = NULL;
					// ���Ӻ����ӽ�������
					RBNode<KEY, COLOR> *temp = root->left;
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

void main() {
	Exam2015::test_2_8();
}