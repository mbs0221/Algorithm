#include <stdio.h>
#include <iostream>

using namespace std;

// 链表节点类
class Link{
public:
	int data;
	Link *next;
public:
	Link(int t){
		this->data = t;
		this->next = NULL;
	}
};

// 链表类
class LinkList{
public:
	Link *head, *tail;
	LinkList(){
		head = NULL;
		tail = NULL;
	}// 无参构造函数
	void add(Link *l){
		if (head == NULL && tail == NULL){
			head = tail = l;
		}
		else{
			l->next = head;
			tail->next = l;
			tail = l;
		}// 循环链表
	}// 添加节点
	Link *seek(int i){
		Link *l = head;
		int count = 1;
		while (l&&count < i){
			l = l->next;
			count++;
		}
		return l;
	}// 查找第i个人，返回第i个人的指针
};

// Josephus顺序实现，n个人，从s开始报数，报m的人出队
void Josephus_seq(int n, int s, int m){
	cout << "Josephus_seq" << endl;
	int *person = new int[n];
	int i;
	for (i = 0; i < n; i++){//构建n个人的数组
		person[i] = i + 1;
	}
	int count = 0;//统计出对人数
	int t = 0;//t∈[1, m] 从第s个开始报数
	i = (s - 1) % n;//如果s>n，取模防止下标出界，从第s个人开始，数组下表要-1
	while (count < n - 1){//只剩一个人时，跳出循环
		if (person[i] != 0){
			t++;	//报数
		}
		if (t == m){//出队
			cout << person[i] << endl;	//输出出队的人
			person[i] = 0;//出队
			t = 0;//重新开始报数
			count++;//统计出队人数
		}
		i++;
		if (i == n){
			i = 0;
		}//构造循环队列
	}
}

// Josephus链表实现，n个人，从s开始报数，报m的人出队
void Josephus_lnk(int n, int s, int m){
	cout << "Josephus_lnk" << endl;
	LinkList *l = new LinkList();
	int i = 0;
	for (i = 0; i < n; i++){
		l->add(new Link(i + 1));
	}//构建n个人的循环链表						
	int count = 0;//统计人数
	Link *p = l->seek(s);//从第s个人开始
	while (p->next != p){//相等说明只剩一个人或是空链表
		count++;//报数
		if (count == m - 1){//如果到了m-1，他的下一个人m出列
			cout << p->next->data << endl;//输出出对的人的编号data
			p->next = p->next->next;//出队，跳过p->next
			count = 0;//重新开始报数
		}
		p = p->next;//转到下一个人
	}
}