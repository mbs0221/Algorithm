#ifndef _TRIETREE_
#define _TRIETREE_

#include <string>
#include <map>
#include <algorithm>

using namespace std;

// 字典树节点类
struct node{
	bool isWord;
	int count;//作为前缀的次数
	int times;//单词存在的次数
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

// 字典树节点比较
struct ltstr
{
	bool operator()(const string& s1, const string& s2) const
	{
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}
};

// 字典树
class TrieTree{
private:
	node *root;// 树根
	node *location;// 当前指针的位置，用于在字典树查找单词
	map<string, int, ltstr> list;// 词频统计数据
	void print(node *root);//先序深度优先遍历字典树
public:
	TrieTree();
	void readline(char *str);
	void print();
	void insert(string str);
	bool search(string str);
	bool deleteWord(string str);
};
#endif