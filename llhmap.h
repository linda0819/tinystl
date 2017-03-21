#pragma once
/*********************
author:li linhua
date:2016/10/19
�����嵥��

0:llh_map();
~llh_map() {};
�������������
1:bool empty() { return _size == 0; };
�ж������Ƿ�Ϊ��
2:void  Insert(const Pair<T,U>& pair);
void InsertFixup(rbtree_node<T, U>* newNode);
�������в���Ԫ�أ�����Ԫ��֮����Ҫ���������ʹ����������������
3:void RotateLeft(rbtree_node<T, U>* node);
void RotateRight(rbtree_node<T, U>* node);
������������Ϊ�˱�֤�������һ��ƽ�������
4:Pair<T, U>* Find(const T& value);
�ں�����в��Ҽ�ֵΪvalue��Ԫ�أ����鵽�򷵻ص�ǰ��pair��û���ҵ��򷵻�NULL
5:Pair<T,U>* operator [] (const T& value);
����[]����������ؼ�ֵ��pair
6:void Erase(const T& value);
void DeleteFixup(rbtree_node<T, U>* node);
ɾ��ĳ������pair����Ҫ���µ���ʹ����������������
7:void  Clear();
ɾ��map�е�����Ԫ��
8:void print();
void inordersort(rbtree_node<T, U>* temp);
���ռ�ֵ��˳�����δ�ӡ���ݣ������������������
**********************/
#ifndef  LLH_MAP_H
#define  LLH_MAP_H
#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <list>
#include <cstdlib>
using namespace std;

enum rb_color
{
	RB_BLACK,
	RB_RED,
	NIL,
};
template<typename T, typename U>
class Pair
{
public:
	T t_value;
	U u_value;
	void set(T key,U value);
};
template<typename T, typename U>
void Pair<T,U>::set(T key, U value)
{
	t_value = key;
	u_value = value;
}

template<typename T, typename U>
class rbtree_node
{
public:
	rbtree_node() {
		parent = nullptr;
		left = nullptr;
		right= nullptr;
		color = NIL;
	};
	 rbtree_node* parent;
	 rbtree_node* left;
	 rbtree_node* right;
	enum rb_color color;
	Pair<T, U> obj;
};

/***************************map������************************/
template<typename T, typename U>
class llh_map {
public:	
	llh_map();
	~llh_map() {};
private:
	rbtree_node<T,U> *root;
	int _size;
public:
	bool empty() { return _size == 0; };
	void  Insert(const Pair<T,U>& pair);
	void RotateLeft(rbtree_node<T, U>* node);
	void RotateRight(rbtree_node<T, U>* node);
	void InsertFixup(rbtree_node<T, U>* newNode);
	Pair<T, U>* Find(const T& value);
	Pair<T,U>* operator [] (const T& value);
	void Erase(const T& value);
	void DeleteFixup(rbtree_node<T, U>* node);
	void inordersort(rbtree_node<T, U>* temp);
	rbtree_node<T, U>* 		UncleNode(rbtree_node<T, U>* node) {
		return node->parent == node->parent->parent->left ? node->parent->parent->right : node->parent->parent->left;
	}
	rbtree_node<T, U>*  BrotherNode(rbtree_node<T, U>*  node) {
		return node == node->parent->left ? node->parent->right : node->parent->left;
	}
	void  Clear();
	void print();
};
/***************************map�����ʵ��************************/
template<typename T, typename U>
llh_map<T, U>::llh_map()
{
	root= new rbtree_node<T,U>;
	_size = 0;
}
template<typename T, typename U>
Pair<T, U>* llh_map<T, U>::Find(const T& value)
{
	rbtree_node<T, U> *temp = root;  
	while(temp->color != NIL)
	{
		if (value == temp->obj.t_value)   return  &(temp->obj);
		else if (value > temp->obj.t_value)
		{
			temp = temp->right;
		}
		else
		{
			temp = temp->left;
		}
	}
	return NULL;
}
template<typename T, typename U>
Pair<T, U>* llh_map<T, U>::operator [] (const T& value)
{
	return Find(value);

}
template<typename T, typename U>
void llh_map<T, U>::print()
{
	inordersort(root);
}
template<typename T, typename U>
void llh_map<T, U>::inordersort(rbtree_node<T, U>* temp)
{
	if (temp->color == NIL)  return;
	inordersort(temp->left);
	cout << temp->obj.u_value << "  ";
	inordersort(temp->right);
}
template<typename T, typename U>
void llh_map<T, U>::RotateRight(rbtree_node<T,U>* node)
{
	rbtree_node<T,U>* lchild = node->left;

	node->left = lchild->right;
	node->left->parent = node;

	lchild->parent = node->parent;
	if (NULL == node->parent)
		root = lchild;
	else if (node == node->parent->right)
		node->parent->right = lchild;
	else
		node->parent->left = lchild;

	node->parent = lchild;
	lchild->right = node;
}
template<typename T, typename U>
void  llh_map<T, U>::RotateLeft(rbtree_node<T,U>* node)
{
	rbtree_node<T,U>* right = node->right;

	node->right = right->left;
	node->right->parent = node;

	right->parent = node->parent;  
	if (NULL == node->parent)    //�ж�֮ǰ��node�ڵ��Ƿ�Ϊ���ڵ�
		root = right;
	else if (node == node->parent->right)   //�ж�node�ڵ���үү�ڵ����ڵ㻹���ҽڵ�
		node->parent->right = right;
	else
		node->parent->left = right;

	node->parent = right;
	right->left = node;
}

template<typename T, typename U>
void llh_map<T, U>::Insert(const Pair<T,U>& pair)
{
	rbtree_node<T,U>* tmpNode = root;
	while (tmpNode->color != NIL)
	{
		if (tmpNode->obj.t_value == pair.t_value)
		{
			tmpNode->obj = pair;
			return;
		}

		if (tmpNode->obj.t_value< pair.t_value)
			tmpNode = tmpNode->right;
		else
			tmpNode = tmpNode->left;
	}
	tmpNode->color = RB_RED;
	tmpNode->obj = pair;
	tmpNode->left = new rbtree_node<T,U>;
	tmpNode->right = new rbtree_node<T, U>;
	tmpNode->left->parent = tmpNode;
	tmpNode->right->parent = tmpNode;
	tmpNode->left->color = NIL;
	tmpNode->right->color = NIL;
	_size++;
	InsertFixup(tmpNode);
}

template<class T, class U>
void llh_map<T,U>::InsertFixup(rbtree_node<T,U>* newNode)
{
	//���1������Ǹ��ڵ㣬�򽫸��ڵ���Ϊ��ɫ
	if (NULL == newNode->parent)
	{
		newNode->color = RB_BLACK;
		return;
	}
	//���2�������ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ�����ֲ���
	if (RB_BLACK == newNode->parent->color)
		return;
	//���3�������ǰ�ڵ�ĸ��ڵ㡢����ڵ�Ϊ��ɫ�������ڵ㡢����ڵ���Ϊ��ɫ��үү�ڵ���Ϊ��ɫ��������үү�ڵ�ݹ����InsertFixup()
	rbtree_node<T,U>* tmp = UncleNode(newNode);
	if (RB_RED == tmp->color)
	{
		tmp->color = RB_BLACK;
		newNode->parent->color = RB_BLACK;
		newNode->parent->parent->color = RB_RED;
		InsertFixup(newNode->parent->parent);
		return;
	}
	//���4�����ڵ�P�Ǻ�ɫ������ڵ�U�Ǻ�ɫ��NIL������ڵ�N���丸�ڵ�P�����ӣ������ڵ�P�����丸�ڵ���Һ��ӡ�
	if (newNode == newNode->parent->left && newNode->parent == newNode->parent->parent->right)
		
	{
		RotateRight(newNode->parent);
		newNode = newNode->right;
	}
	//���5�����ڵ�P�Ǻ�ɫ������ڵ�U�Ǻ�ɫ��NIL������ڵ�N���丸�ڵ�P���Һ��ӣ������ڵ�P�����丸�ڵ�����ӡ�
	else if (newNode == newNode->parent->right && newNode->parent == newNode->parent->parent->left)
		
	{
		RotateLeft(newNode->parent);
		newNode = newNode->left;
	}

	newNode->parent->color = RB_BLACK;
	newNode->parent->parent->color = RB_RED;

	if (newNode == newNode->parent->left)
		RotateRight(newNode->parent->parent);
	else
		RotateLeft(newNode->parent->parent);
}

template<class T, class U>
void llh_map<T, U>::Erase(const T& value)
{
	rbtree_node<T,U>* node = root;

	while (NIL != node->color)
	{
		if (value==node->obj.t_value)
			break;

		if (node->obj.t_value<value)
			node = node->right;
		else
			node = node->left;
	}

	if (NIL == node->color)
		return;

	if (NIL == node->right->color && NIL == node->left->color)
	{
		delete node->right;
		delete node->left;

		if (RB_RED == node->color)
			node->color = NIL;

		else
		{
			node->color = NIL;
			DeleteFixup(node);
		}
	}
	else if (NIL != node->left->color)
	{
		rbtree_node<T,U>* tmpDel = node->left, *replace;

		while (NIL != tmpDel->right->color)
			tmpDel = tmpDel->right;
		node->obj = tmpDel->obj;

		replace = tmpDel->right->color != NIL ? tmpDel->right : tmpDel->left;

		if (replace == tmpDel->right)
			delete tmpDel->left;
		else
			delete tmpDel->right;

		replace->parent = tmpDel->parent;

		if (replace->parent == NULL)
			root = replace;
		else if (tmpDel == tmpDel->parent->right)
			tmpDel->parent->right = replace;
		else
			tmpDel->parent->left = replace;

		if (RB_BLACK == tmpDel->color)
		{
			if (RB_RED == replace->color)
				replace->color = RB_BLACK;
			else
				DeleteFixup(replace);
		}
		delete tmpDel;
		_size--;
	}
	else
	{
		rbtree_node<T,U>* tmpDel = node->right, *replace;

		while (NIL != tmpDel->left->color)
			tmpDel = tmpDel->left;
		node->obj = tmpDel->obj;

		replace = tmpDel->right->color != NIL ? tmpDel->right : tmpDel->left;

		if (replace == tmpDel->right)
			delete tmpDel->left;
		else
			delete tmpDel->right;

		replace->parent = tmpDel->parent;

		if (replace->parent == NULL)
			root = replace;
		else if (tmpDel == tmpDel->parent->right)
			tmpDel->parent->right = replace;
		else
			tmpDel->parent->left = replace;

		if (RB_BLACK == tmpDel->color)
		{
			if (RB_RED == replace->color)
				replace->color = RB_BLACK;
			else
				DeleteFixup(replace);
		}
		delete tmpDel;
	}

}

template<class T, class U>
void llh_map<T, U>::DeleteFixup(rbtree_node<T,U>* node)
{
	if (NULL == node->parent)
		return;

	rbtree_node<T,U>* brother = BrotherNode(node);

	if (RB_RED == brother->color)
	{
		node->parent->color = RB_RED;
		brother->color = RB_BLACK;

		if (node == node->parent->left)
			RotateLeft(node->parent);
		else
			RotateRight(node->parent);
	}

	brother = BrotherNode(node);

	if ((RB_RED != node->parent->color) && (RB_RED != brother->color) &&( RB_RED != brother->left->color )&& (RB_RED != brother->right->color))
	{
		brother->color = RB_RED;
		DeleteFixup(node->parent);
	}
	else
	{
		if ((RB_RED == node->parent->color) && (RB_RED != brother->color) && (RB_RED != brother->left->color) && (RB_RED != brother->right->color))
		{
			brother->color = RB_RED;
			node->parent->color = RB_BLACK;
		}
		else
		{
			if ((node == node->parent->left) && (brother->left->color == RB_RED) && (brother->right->color != RB_RED))
			{
				brother->color = RB_RED;
				brother->left->color = RB_BLACK;
				RotateRight(brother);
			}
			else if ((node == node->parent->right) && (brother->left->color != RB_RED) && (brother->right->color == RB_RED))
			{
				brother->color = RB_RED;
				brother->right->color = RB_BLACK;
				RotateLeft(brother);
			}

			brother = BrotherNode(node);

			brother->color = node->parent->color;
			node->parent->color = RB_BLACK;

			if (node == node->parent->left)
			{
				brother->right->color = RB_BLACK;
				RotateLeft(node->parent);
			}
			else
			{
				brother->left->color = RB_BLACK;
				RotateRight(node->parent);
			}
		}
	}
}

template<class T, class U>
void llh_map<T,U>::Clear()
{
	rbtree_node<T, U>* node = root, *tmp;

	while (NULL != node)
	{
		if (NIL == node->color || NULL == node->left && NULL == node->right)
		{
			tmp = node;
			node = node->parent;
			if (NULL != node)
			{
				if (tmp == node->left)
					node->left = NULL;
				else
					node->right = NULL;
			}
			delete tmp;

		}

		if (NULL != node)
		{
			if (NULL != node->left)
				node = node->left;
			else if (NULL != node->right)
				node = node->right;
		}
	}
	_size = 0;
}

#endif 