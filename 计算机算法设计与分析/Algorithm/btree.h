#pragma once

// B+ Tree Node Type

#define ORDER 7
#define MIN_NUM_KEY ORDER-1
#define MAX_NUM_KEY 2*ORDER-1
#define MIN_NUM_CHILD MIN_NUM_KEY+1
#define MAX_NUM_CHILD MAX_NUM_KEY+1
#define MIN_NUM_LEAF MIN_NUM_KEY
#define MAX_NUM_LEAF MAX_NUM_KEY

enum Type{ INNER, OUTER };
enum Deriction { LEFT, RIGHT };

template<class Key>
class CNode {
public:
	CNode() {
	}
	~CNode() {
	}
	// operations
	Type type() { return m_Type; }
	void setType(Type t) { m_Type = t; }
	int getKeyNum() const { return m_KeyNum; }
	void setKeyNum(int n) { m_KeyNum = n; }
	Key getKeyValue(int i)const { return m_KeyValues[i]; }
	void setKeyValue(int i, Key key) { m_KeyValues[i] = key; }
	int getKeyIndex(Key key) {  }
	// interface
	virtual void removeKey(int keyIndex, int childIndex) = 0;
	virtual void split(CNode<Key>* parentNode, int childIndex) = 0;
	virtual void mergeChild(CNode<Key>* parentNode, CNode<Key> childNode, int keyIndex) = 0;
	virtual void clear() = 0;
	virtual void borrowFrom(CNode<Key>* dstNode, CNode<Key>* parentNode, int keyIndex, Deriction dir) = 0;
	virtual int getChildIndex() = 0;
protected:
	// data field
	Type m_Type;
	int m_KeyNum;
	Key m_KeyValues[MAX_NUM_KEY];
};

template<class Key>
class CInnerNode:CNode {
public:
	// constructor
	CInnerNode() { ; }
	~CInnerNode() { ; }
	// getter and setter
	CInnerNode<Key>* getChild() { return m_Childs[i]; }
	void setChild(int i, CNode<Key>* child) { m_Childs[i] = key; }
	// interface
	virtual void removeKey(int keyIndex, int childIndex) {
		;
	}
	virtual void split(CNode<Key>* parentNode, int childIndex) {
		;
	}
	virtual void mergeChild(CNode<Key>* parentNode, CNode<Key> childNode, int keyIndex) { 
		;
	}
	virtual void clear() {
		;
	}
	virtual void borrowFrom(CNode<Key>* dstNode, CNode<Key>* parentNode, int keyIndex, Deriction dir) = 0;
	virtual int getChildIndex() = 0;
private:
	// data field
	CNode<Key>* m_Childs[MAX_NUM_CHILD];
};

template<class Key, class Value>
class CLeafNode :CNode {
	CNode<Key>* m_Childs[MAX_NUM_CHILD];
	CLeafNode<Key>* m_LeftSibling;
	CLeafNode<Key>* m_RightSibling;
	Value m_Datas[MAX_NUM_LEAF];
};

// B+ Tree

template<class Key, class Value>
struct CBPlusTree {
	CNode<Key>* m_Root;
	CLeafNode<Key, Value> m_DataHead;
	Key m_MaxKey;
};