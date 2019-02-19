#ifndef _MIN_HEAP_
#define _MIN_HEAP_

#define _DEFAULT_SIZE_ 256

template <class T>
class MinHeap{
private:
	T *heap;
	int currentSize, maxSize;
	void swap(int pos_x, int pos_y)
	{
		T temp;
		temp = heap[pos_x];
		heap[pos_x] = heap[pos_y];
		heap[pos_y] = temp;
	}//交换元素
	void  buildHeap()
	{
		for (int i = maxSize / 2 - 1; i > 0; i--)
		{
			shiftDown(i);
		}
	}//建堆
	void  shiftUp(int pos)
	{
		int temppos = pos;
		T temp = heap[temppos];
		while (temppos > 0 && heap[Parent(temppos)] > temp)		//父节点大于当前节点，不断向上调整
		{
			heap[temppos] = heap[Parent(temppos)];
			temppos = Parent(temppos);
		}
		heap[temppos] = temp;
	}//从pos开始向上调整
	void  shiftDown(int left)
	{
		int i = left;										//标示父节点
		int j = leftChild(i);								//用于记录关键值小的子节点
		T temp = heap[i];									//保存父节点
		while (j < currentSize)
		{
			if (j < currentSize - 1 && heap[j] > heap[j + 1])
			{
				j++;										//指向右子节点
			}												//若有右子节点，且左子节点大于右子节点
			if (temp > heap[j])								//当前节点大于子节点
			{
				heap[i] = heap[j];							//子节点向上调整
				i = j;										//标示新的父节点
				j = leftChild(j);							//指向新的关键值小的子节点
			}
			else											//有序则跳出
				break;
		}
		heap[i] = temp;
	}//从left开始向下筛选
public:
	MinHeap()
	{
		currentSize = 0;
		maxSize = _DEFAULT_SIZE_;
		heap = new T[maxSize];
		buildHeap();
	}//默认构造函数
	MinHeap(const int n)
	{
		if (n < 0)
			return;
		currentSize = 0;
		maxSize = n;
		heap = new T[maxSize];
		buildHeap();
	}//构造函数
	MinHeap(T array[], int n)
	{
		if (n < 0)
			return;
		currentSize = 0;
		maxSize = n;
		heap = new T[maxSize];
		for (int i = 0; i < n; i++)
		{
			insert(array[i]);
		}
	}
	~MinHeap()
	{
		delete[]heap;
	}//析构函数
	int  getSize()
	{
		return currentSize;
	}
	int  leftChild(int pos) const
	{
		return 2 * pos + 1;
	}//左子节点
	int  rightChild(int pos) const
	{
		return 2 * pos + 2;
	}//右子节点
	int  Parent(int pos) const
	{
		return (pos - 1) / 2;
	}//父节点
	bool  isEmpty()
	{
		return currentSize == 0;
	}//是空堆
	bool  isChild(int pos)
	{
		return (pos > currentSize / 2) && (pos < currentSize);
	}//是叶子节点
	bool  isParent(int pos)
	{
		return pos <= (currentSize - 1) / 2;
	}
	bool  remove(int pos, T& node)
	{
		if (pos < 0 || pos > currentSize)
			return false;
		node = heap[pos];							//记录删除的元素
		heap[pos] = heap[--currentSize];			//最后的元素值替代删除的元素
		if (heap[Parent(pos)] > heap[pos])			//父节点大于当前节点
		{
			shiftUp(pos);
		}
		else										//父节点小于当前节点，
		{
			shiftDown(pos);
		}
		return true;
	}//删除给定下标的元素
	bool  insert(const T& node)
	{
		if (currentSize == maxSize)
		{
			return false;							//堆已满，返回false
		}
		heap[currentSize] = node;					//新元素放到末尾
		shiftUp(currentSize);						//向上调整
		currentSize++;								//计数
		return true;
	}//插入元素
	T&  removeMin()
	{
		if (currentSize == 0)						//判断是否为空
		{
			cout << "Cant't delete" << endl;
			exit(1);
		}
		else
		{
			swap(0, --currentSize);					//交换堆顶与堆末的元素
			if (currentSize > 1)						//堆顶向下调整
			{
				shiftDown(0);
			}
			return heap[currentSize];
		}
	}//取堆顶
	T&  getNode(int pos)
	{
		return heap[pos];
	}
};

#endif