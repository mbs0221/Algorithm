#include <stdio.h>
#include <iostream>

using namespace std;

// ����ڵ���
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

// ������
class LinkList{
public:
	Link *head, *tail;
	LinkList(){
		head = NULL;
		tail = NULL;
	}// �޲ι��캯��
	void add(Link *l){
		if (head == NULL && tail == NULL){
			head = tail = l;
		}
		else{
			l->next = head;
			tail->next = l;
			tail = l;
		}// ѭ������
	}// ��ӽڵ�
	Link *seek(int i){
		Link *l = head;
		int count = 1;
		while (l&&count < i){
			l = l->next;
			count++;
		}
		return l;
	}// ���ҵ�i���ˣ����ص�i���˵�ָ��
};

// Josephus˳��ʵ�֣�n���ˣ���s��ʼ��������m���˳���
void Josephus_seq(int n, int s, int m){
	cout << "Josephus_seq" << endl;
	int *person = new int[n];
	int i;
	for (i = 0; i < n; i++){//����n���˵�����
		person[i] = i + 1;
	}
	int count = 0;//ͳ�Ƴ�������
	int t = 0;//t��[1, m] �ӵ�s����ʼ����
	i = (s - 1) % n;//���s>n��ȡģ��ֹ�±���磬�ӵ�s���˿�ʼ�������±�Ҫ-1
	while (count < n - 1){//ֻʣһ����ʱ������ѭ��
		if (person[i] != 0){
			t++;	//����
		}
		if (t == m){//����
			cout << person[i] << endl;	//������ӵ���
			person[i] = 0;//����
			t = 0;//���¿�ʼ����
			count++;//ͳ�Ƴ�������
		}
		i++;
		if (i == n){
			i = 0;
		}//����ѭ������
	}
}

// Josephus����ʵ�֣�n���ˣ���s��ʼ��������m���˳���
void Josephus_lnk(int n, int s, int m){
	cout << "Josephus_lnk" << endl;
	LinkList *l = new LinkList();
	int i = 0;
	for (i = 0; i < n; i++){
		l->add(new Link(i + 1));
	}//����n���˵�ѭ������						
	int count = 0;//ͳ������
	Link *p = l->seek(s);//�ӵ�s���˿�ʼ
	while (p->next != p){//���˵��ֻʣһ���˻��ǿ�����
		count++;//����
		if (count == m - 1){//�������m-1��������һ����m����
			cout << p->next->data << endl;//������Ե��˵ı��data
			p->next = p->next->next;//���ӣ�����p->next
			count = 0;//���¿�ʼ����
		}
		p = p->next;//ת����һ����
	}
}