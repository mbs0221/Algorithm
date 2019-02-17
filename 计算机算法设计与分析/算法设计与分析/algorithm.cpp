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
		void ShellSort(int*a, int left, int right)
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
	T SMatrix<T>::deleteOLNode(int row, int col)
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
	T SMatrix<T>::getElement(int row, int col)
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
	SMatrix<T> & SMatrix<T>::MatrixAdd(SMatrix<T>& m1, SMatrix<T>& m2)
	{
		OLNode*p, *q, *u, *v;
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

	// �������ڵ���
	template<class T>
	inline BinaryTreeNode<T>::BinaryTreeNode(T element, BinaryTreeNode<T>* left, BinaryTreeNode<T>* right)
	{
		this->element = element;
		this->left = left;
		this->right = right;
	}

	// ������
	template<class T>
	BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T>* root)
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
	BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* current)
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
	BinaryTreeNode<T>* BinaryTree<T>::LeftSibling(BinaryTreeNode<T>* current)
	{
		//����current�������ֵ�
		if (current) //current��Ϊ��
		{
			//����current���ĸ����
			BinaryTreeNode<T>* temp = Parent(current);
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
	void BinaryTree<T>::DepthOrder(BinaryTreeNode<T>* root, void(*Visit)(T element))
	{
		if (!root) {
			(*Visit)(root->element);
			DepthOrder(root->left);
			DepthOrder(root->right);
		}
	}
	template<class T>
	void BinaryTree<T>::PreOrderWithoutRecursion(BinaryTreeNode<T>* root, void(*Visit)(T element))
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
	void BinaryTree<T>::InOrderWithoutRecursion(BinaryTreeNode<T>* root, void(*Visit)(T element))
	{
		// ����ǵݹ����ζ�����
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
	void BinaryTree<T>::PostOrderWithoutRecursion(BinaryTreeNode<T>* root, void(*Visit)(T element))
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
	void BinaryTree<T>::LevelOrder(BinaryTreeNode<T>* root, void(*Visit)(T element))
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

	// ���߶�����
	template<class T>
	void ThreadBinaryTree<T>::Insert(ThreadBinaryTreeNode<T>* p, ThreadBinaryTreeNode<T>* r)
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
	void BinarySearchTree<T>::Insert(BinaryTreeNode<T>* root, BinaryTreeNode<T>* node)
	{
		BinaryTreeNode<T>* p = NULL;
		if (root == NULL) {
			//�½������
			Initialize(node);
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
				else   p = p->getRightChild();
			}
		}
	}
	template<class T>
	void BinarySearchTree<T>::Delete(BinaryTreeNode<T>* p)
	{
		if (p == NULL)
			return;
		BinaryTreeNode<T>* s;
		BinaryTreeNode<T>* tempparent = NULL;
		BinaryTreeNode<T>* parent = GetParent(root, p);
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

	// ɭ��
	template<class T>
	TreeNode<T>* Tree<T>::Parent(TreeNode<T>* current)
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
				TreeNode<T>* r = root;
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
		node = heapArray[pos]; //��ɾԪ����node����
		heapArray[pos] = heapArray[--CurrentSize];
		//���Ԫ�������ɾԪ�أ���-1	
		if (heapArry[Parent(pos)] > heapArry[pos]))
		SiftUp(pos);	//С�ڸ���㣬����ɸ
		else
			SiftDown(pos);	//���ڸ�����ɸ(����SiftDown(0)) return true;
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
	void HuffmanTree<T>::MergeTree(HuffmanTreeNode<T>& ht1, HuffmanTreeNode<T>& ht2, HuffmanTreeNode<T>* parent)
	{
		parent->element = ht1.element + ht2->element;
		parent->left = &ht1;
		parent->right = &ht2;
	}
	template<class T>
	void HuffmanTree<T>::DeleteTree(HuffmanTreeNode<T>* root)
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
		HuffmanTreeNode<T>* parent, firstchild, secondchild;
		HuffmanTreeNode<T>* NodeList = new HuffmanTreeNode<T>[n];
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

	// �����
	template<class KEY, class COLOR>
	RBNode<KEY, COLOR>::RBNode(RBNode* parent, RBNode* left, RBNode* right, KEY key, COLOR color)
	{
		this->key = key;
		this->color = color;
		this->parent = parent;
		this->left = left;
		this->right = right;
	}
	template<class KEY, class COLOR>
	void RBTree<KEY, COLOR>::insert(RBNode<KEY, COLOR>*root, const KEY & key)
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
		RBNode<KEY, COLOR>*parent = root->parent;
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
					RBNode<KEY, COLOR>*temp = root->left;
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