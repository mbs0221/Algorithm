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
			// 选取步长
			for (int k = right / 2; k > 1; k /= 2) {
				// 对于每一列
				for (int i = 0; i < k; i++) {
					// 插入排序
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

	void test_2_8()
	{
		int a[] = { 10,9,8,7,6,5,4,3,2,1,0 };
		cout << "2.8 希尔排序" << endl;
		Problem1::ShellSort(a, 0, 10);
		std::cout << "a:" << std::endl;
		PrintArray(a, 11);
		getchar();
	}
}

namespace Algorithm {

	// 稀疏矩阵 - 十字链表
	template<class T>
	void SMatrix<T>::insertOLNode(int row, int col, T val)
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
	T SMatrix<T>::deleteOLNode(int row, int col)
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
	T SMatrix<T>::getElement(int row, int col)
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
	SMatrix<T> & SMatrix<T>::MatrixAdd(SMatrix<T>& m1, SMatrix<T>& m2)
	{
		OLNode*p, *q, *u, *v;
		SMatrix r(m1.rowNum, m2.colNum);
		p = m1.rowhead;
		u = m2.rowhead;

		// TODO: 在此处插入 return 语句
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
			// 计算每一列非零元素个数
			for (int t = 0; t < a.lenght; t++) {
				num[a.data[t].col]++;
			}
			// 计算每一列的起始位置
			position[0] = 0;
			for (int col = 1; col < a.n; col++) {
				position[col] = position[col - 1] + num[col - 1];
			}
			// 转置
			for (int p = 0; p < a.lenght; p++) {
				int col = a.data[p].col;
				int q = position[col];
				b.data[q].row = a.data[p].col;
				b.data[q].col = a.data[p].row;
				b.data[q].e = a.data[p].data;
				position[col]++;
			}
		}
		// TODO: 在此处插入 return 语句
		return b;
	}

	// 二叉树节点类
	template<class T>
	inline BinaryTreeNode<T>::BinaryTreeNode(T element, BinaryTreeNode<T>* left, BinaryTreeNode<T>* right)
	{
		this->element = element;
		this->left = left;
		this->right = right;
	}

	// 二叉树
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
	BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* current)
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
	BinaryTreeNode<T>* BinaryTree<T>::LeftSibling(BinaryTreeNode<T>* current)
	{
		//返回current结点的左兄弟
		if (current) //current不为空
		{
			//返回current结点的父结点
			BinaryTreeNode<T>* temp = Parent(current);
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
	void BinaryTree<T>::InOrderWithoutRecursion(BinaryTreeNode<T>* root, void(*Visit)(T element))
	{
		// 中序非递归周游二叉树
		using std::stack;
		stack<BinaryTreeNode<T>*> aStack;
		BinaryTreeNode<T>* p = root;
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
	void BinaryTree<T>::PostOrderWithoutRecursion(BinaryTreeNode<T>* root, void(*Visit)(T element))
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
	void BinaryTree<T>::LevelOrder(BinaryTreeNode<T>* root, void(*Visit)(T element))
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

	// 穿线二叉树
	template<class T>
	void ThreadBinaryTree<T>::Insert(ThreadBinaryTreeNode<T>* p, ThreadBinaryTreeNode<T>* r)
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
	void BinarySearchTree<T>::Insert(BinaryTreeNode<T>* root, BinaryTreeNode<T>* node)
	{
		BinaryTreeNode<T>* p = NULL;
		if (root == NULL) {
			//新结点作根
			Initialize(node);
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

	// 森林
	template<class T>
	TreeNode<T>* Tree<T>::Parent(TreeNode<T>* current)
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
				TreeNode<T>* r = root;
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
	template<class T>

	// 树 - 双标记表示法
	DualTagTree<T>::DualTagTree(DualTagTreeNode<T>* nodeArray, int count)
	{
		using std::stack;
		stack<DualTagTreeNode<T>*> aStack;

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
		node = heapArray[pos]; //被删元素由node返回
		heapArray[pos] = heapArray[--CurrentSize];
		//最后元素替代被删元素，长-1	
		if (heapArry[Parent(pos)] > heapArry[pos]))
		SiftUp(pos);	//小于父结点，上升筛
		else
			SiftDown(pos);	//大于父向下筛(不是SiftDown(0)) return true;
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
		//weight存权值数组;n数组长
		//定义最小值堆
		MinHeap<HuffmanTreeNode<T>> heap(n);
		//parent：指向对象的指针， firstchild, secondchild ：2个对象
		HuffmanTreeNode<T>* parent, firstchild, secondchild;
		HuffmanTreeNode<T>* NodeList = new HuffmanTreeNode<T>[n];
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

	// 红黑树
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
			// 叔父同为红色
			// 父辈祖辈换色
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
				// 父节点是左子节点，则右旋
				// 如果新增节点是右子节点，则调整为左子节点
				if (root->left->key == NULL) {
					// 借助空节点作为temp节点
					root->left->key = root->key;
					root->key = root->right->key;
					root->right->key = root->left->key;
					root->left->key = NULL;
					// 左子和右子交换即可
					RBNode<KEY, COLOR>*temp = root->left;
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

void main() {
	Exam2015::test_2_8();
}