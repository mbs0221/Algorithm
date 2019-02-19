#include "trie.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

TrieTree::TrieTree(){
	root = new node();
	location = root;
}
// ���Ҷ�ڵ���Ϣ
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
}//����������ȱ����ֵ���
// �������£�ͳ�ƴ�Ƶ
void TrieTree::readline(char *str){
	int index = 0;
	while (str[index] != NULL){
		if (isalpha(str[index])){
			int i = tolower(str[index]) - 'a';
			if (location->next[i] == NULL){
				location->next[i] = new node();//�����½ڵ�
				location->count++;//ǰ׺����
			}//��ӽڵ�
			location = location->next[i];//������һ�ڵ�
		}else{
			location->isWord = true;//�ǵ���
			location->times++;//����
			location = root;//����location
		}
		index++;//��ȡ��һ�ַ�
	}
}
// �����Ƶ��Ϣ
void TrieTree::print(){
	print(root);
	map<string, int, ltstr>::iterator iter;
	for (iter = list.begin(); iter != list.end(); iter++){
		cout << (*iter).first << ":" << (*iter).second << endl;
	}
	cout << "size:" << list.size() << endl;
}
// ��ӵ���
void TrieTree::insert(string str){
	node *location = root;
	cout << "Insert string \"" << str << "\"" << endl;
	for (int i = 0; i < str.length(); i++){
		int num = tolower(str[i]) - 'a';
		if (location->next[num] == NULL){
			location->next[num] = new node();
			location->count++;
		}//��ӽڵ�
		location = location->next[num];
	}
	location->isWord = true;//�������ǵ���
	cout << "Insert string \"" << str << "\" finished" << endl;
}
// ���ҵ���
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
// ɾ������
bool TrieTree::deleteWord(string str){
	node *location = root;
	for (int i = 0; i < str.length(); i++){
		int num = tolower(str[i]) - 'a';
		if (location->next[num] == NULL){
			cout << "Delete \"" << str << "\" from passage failed" << endl;
			return false;
		}//���û�иôʣ�����ɾ��ʧ��
		location = location->next[num];
	}//���ҵ���
	location->isWord = false;
	cout << "Delete \"" << str << "\" from passage success" << endl;
	return true;
}