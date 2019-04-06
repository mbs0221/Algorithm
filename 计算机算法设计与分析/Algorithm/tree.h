#pragma once

template<class T>
class  Node{
public:
	T data;
	Node *left, *right;
	Node(T key) {
		data = key;
		left = nullptr;
		right = nullptr;
	}
};

template<class T>
class BST {
	Node<T> *root;
public:
	BST() {
		root = nullptr;
	}
	Node<T> *parent(T key) {
		Node<T> *p, *t;
		p = nullptr;
		t = root;
		while (t) {
			if (t->data == key) {
				break;
			}
			p = t;
			t = (t->data < key) ? t->right ? t->left;
		}
		return p;
	}
	void insert(T key) {
		Node<T> *s, *p, *t;
		s = new Node<T>(key);
		if (root) {
			p = root;
			while (p) {
				t = p;
				if (p->data == key) {
					return;
				}
				p = (key < p->data) ? p->left : p->right;
			}
			if (key < t->data) {
				t->left = s;
			} else {
				t->right = s;
			}
		} else {
			root = s;
		}
	}
	void remove(T key) {
		Node<T> *p, *s, *r;
		p = nullptr;
		s = root;
		while (s) {
			if (s->data == key) {
				break;
			}
			p = s;
			s = (s->data < key) ? s->right ? s->left;
		}
		if (s == nullptr) {
			return;
		}
		/* if s has no left */
		if (s->left == nullptr) {
			if (p->left == s)p->left = s->right;
			if (p->right == s)p->right = s->right;
			delete s;
		} else {
			/* if s has left */
			r = s->left
			while (r) {
				r = r->right;
			}
		}
	}
	Node<T> search(T key) {
		Node<T> *s, *p;
		if(root){
			s = p = root;
			while (p) {
				s = p;
				p = key < p->data ? p->left : p->right;
			}
			return s;
		} else {
			return nullptr;
		}
	}
};
