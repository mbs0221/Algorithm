#include "trie.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

TrieTree::TrieTree(){
	root = new node();
	location = root;
}
// 输出叶节点信息
void TrieTree::print(node *root){
	static string word;
	for (int i = 0; i < 26; i++){
		if (root->next[i]){
			word.push_back('a' + i);
			print(root->next[i]);
			word.pop_back();
		}else if(root->isWord){
			list[word] = root->times;
		}
	}
}//先序深度优先遍历字典树
// 导入文章，统计词频
void TrieTree::readline(char *str){
	int index = 0;
	while (str[index] != NULL){
		if (isalpha(str[index])){
			int i = tolower(str[index]) - 'a';
			if (location->next[i] == NULL){
				location->next[i] = new node();//创建新节点
				location->count++;//前缀计数
			}//添加节点
			location = location->next[i];//进入下一节点
		}else{
			location->isWord = true;//是单词
			location->times++;//计数
			location = root;//重置location
		}
		index++;//读取下一字符
	}
}
// 输出词频信息
void TrieTree::print(){
	print(root);
	map<string, int, ltstr>::iterator iter;
	for (iter = list.begin(); iter != list.end(); iter++){
		cout << (*iter).first << ":" << (*iter).second << endl;
	}
	cout << "size:" << list.size() << endl;
}
// 添加单词
void TrieTree::insert(string str){
	node *location = root;
	cout << "Insert string \"" << str << "\"" << endl;
	for (int i = 0; i < str.length(); i++){
		int num = tolower(str[i]) - 'a';
		if (location->next[num] == NULL){
			location->next[num] = new node();
			location->count++;
		}//添加节点
		location = location->next[num];
	}
	location->isWord = true;//最后结束是单词
	cout << "Insert string \"" << str << "\" finished" << endl;
}
// 查找单词
bool TrieTree::search(string str){
	node *location = root;
	for (int i = 0; i < str.length(); i++){
		int num = tolower(str[i]) - 'a';
		if (location->next[num] == NULL){
			cout << "This passage has no \"" << str << "\"" << endl;
			return false;
		}
		location = location->next[num];
	}
	cout << "This passage has \"" << str << "\" " << location->times << endl;
	return location->isWord;
}
// 删除单词
bool TrieTree::deleteWord(string str){
	node *location = root;
	for (int i = 0; i < str.length(); i++){
		int num = tolower(str[i]) - 'a';
		if (location->next[num] == NULL){
			cout << "Delete \"" << str << "\" from passage failed" << endl;
			return false;
		}//如果没有该词，返回删除失败
		location = location->next[num];
	}//查找单词
	location->isWord = false;
	cout << "Delete \"" << str << "\" from passage success" << endl;
	return true;
}