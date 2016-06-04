#include "minheap.h"

template <class T>
void MinHeap<T>::swap(int pos_x, int pos_y)
{
	T temp;
	temp = heap[pos_x];
	heap[pos_x] = heap[pos_y];
	heap[pos_y] = temp;
}//����Ԫ��
template <class T>
void  MinHeap<T>::buildHeap()
{
	for (int i = maxSize / 2 - 1; i > 0; i--)
	{
		shiftDown(i);
	}
}//����
template <class T>
void  MinHeap<T>::shiftUp(int pos)
{
	int temppos = pos;
	T temp = heap[temppos];
	while (temppos > 0 && heap[Parent(temppos)] > temp)		//���ڵ���ڵ�ǰ�ڵ㣬�������ϵ���
	{
		heap[temppos] = heap[Parent(temppos)];
		temppos = Parent(temppos);
	}
	heap[temppos] = temp;
}//��pos��ʼ���ϵ���
template <class T>
void  MinHeap<T>::shiftDown(int left)
{
	int i = left;										//��ʾ���ڵ�
	int j = leftChild(i);								//���ڼ�¼�ؼ�ֵС���ӽڵ�
	T temp = heap[i];									//���游�ڵ�
	while (j < currentSize)
	{
		if (j < currentSize - 1 && heap[j] > heap[j + 1])
		{
			j++;										//ָ�����ӽڵ�
		}												//�������ӽڵ㣬�����ӽڵ�������ӽڵ�
		if (temp > heap[j])								//��ǰ�ڵ�����ӽڵ�
		{
			heap[i] = heap[j];							//�ӽڵ����ϵ���
			i = j;										//��ʾ�µĸ��ڵ�
			j = leftChild(j);							//ָ���µĹؼ�ֵС���ӽڵ�
		}
		else											//����������
			break;
	}
	heap[i] = temp;
}//��left��ʼ����ɸѡ
template <class T>
MinHeap<T>::MinHeap()
{
	currentSize = 0;
	maxSize = _DEFAULT_SIZE_;
	heap = new T[maxSize];
	buildHeap();
}//Ĭ�Ϲ��캯��
template <class T>
MinHeap<T>::MinHeap(const int n)
{
	if (n < 0)
		return;
	currentSize = 0;
	maxSize = n;
	heap = new T[maxSize];
	buildHeap();
}//���캯��
template <class T>
MinHeap<T>::MinHeap(T array[], int n)
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
template <class T>
MinHeap<T>::~MinHeap()
{
	delete[]heap;
}//��������
template <class T>
int  MinHeap<T>::getSize()
{
	return currentSize;
}
template <class T>
int  MinHeap<T>::leftChild(int pos) const
{
	return 2 * pos + 1;
}//���ӽڵ�
template <class T>
int  MinHeap<T>::rightChild(int pos) const
{
	return 2 * pos + 2;
}//���ӽڵ�
template <class T>
int  MinHeap<T>::Parent(int pos) const
{
	return (pos - 1) / 2;
}//���ڵ�
template <class T>
bool  MinHeap<T>::isEmpty()
{
	return currentSize == 0;
}//�ǿն�
template <class T>
bool  MinHeap<T>::isChild(int pos)
{
	return (pos > currentSize / 2) && (pos < currentSize);
}//��Ҷ�ӽڵ�
template <class T>
bool  MinHeap<T>::isParent(int pos)
{
	return pos <= (currentSize - 1) / 2;
}
template <class T>
bool  MinHeap<T>::remove(int pos, T& node)
{
	if (pos < 0 || pos > currentSize)
		return false;
	node = heap[pos];							//��¼ɾ����Ԫ��
	heap[pos] = heap[--currentSize];			//����Ԫ��ֵ���ɾ����Ԫ��
	if (heap[Parent(pos)] > heap[pos])			//���ڵ���ڵ�ǰ�ڵ�
	{
		shiftUp(pos);
	}
	else										//���ڵ�С�ڵ�ǰ�ڵ㣬
	{
		shiftDown(pos);
	}
	return true;
}//ɾ�������±��Ԫ��
template <class T>
bool  MinHeap<T>::insert(const T& node)
{
	if (currentSize == maxSize)
	{
		return false;							//������������false
	}
	heap[currentSize] = node;					//��Ԫ�طŵ�ĩβ
	shiftUp(currentSize);						//���ϵ���
	currentSize++;								//����
	return true;
}//����Ԫ��
template <class T>
T&  MinHeap<T>::removeMin()
{
	if (currentSize == 0)						//�ж��Ƿ�Ϊ��
	{
		cout << "Cant't delete" << endl;
		exit(1);
	}
	else
	{
		swap(0, --currentSize);					//�����Ѷ����ĩ��Ԫ��
		if (currentSize > 1)						//�Ѷ����µ���
		{
			shiftDown(0);
		}
		return heap[currentSize];
	}
}//ȡ�Ѷ�
template <class T>
T&  MinHeap<T>::getNode(int pos)
{
	return heap[pos];
}