#ifndef _MIN_HEAP_
#define _MIN_HEAP_

#define _DEFAULT_SIZE_ 256

template <class T>
class MinHeap{
private:
	T *heap;
	int currentSize, maxSize;
	void swap(int pos_x, int pos_y);
	void buildHeap();
	void shiftUp(int pos);
	void shiftDown(int left);
public:
	MinHeap();
	MinHeap(const int n);
	MinHeap(T array[], int n);
	~MinHeap();
	int getSize();
	int leftChild(int pos) const;
	int rightChild(int pos) const;
	int Parent(int pos) const;
	bool isEmpty();
	bool isChild(int pos);
	bool isParent(int pos);
	bool remove(int pos, T& node);
	bool insert(const T& node);
	T& removeMin();
	T& getNode(int pos);
};

#endif