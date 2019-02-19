#ifndef _TRIETREE_
#define _TRIETREE_

#include <string>
#include <map>
#include <algorithm>

using namespace std;

// �ֵ����ڵ���
struct node{
	bool isWord;
	int count;//��Ϊǰ׺�Ĵ���
	int times;//���ʴ��ڵĴ���
	node *next[26];
	node(){
		isWord = false;
		for (int i = 0; i < 26;i++){
			next[i] = NULL; 
		}
		count = 0;
		times = 0;
	}
};

// �ֵ����ڵ�Ƚ�
struct ltstr
{
	bool operator()(const string& s1, const string& s2) const
	{
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}
};

// �ֵ���
class TrieTree{
private:
	node *root;// ����
	node *location;// ��ǰָ���λ�ã��������ֵ������ҵ���
	map<string, int, ltstr> list;// ��Ƶͳ������
	void print(node *root);//����������ȱ����ֵ���
public:
	TrieTree();
	void readline(char *str);
	void print();
	void insert(string str);
	bool search(string str);
	bool deleteWord(string str);
};
#endif