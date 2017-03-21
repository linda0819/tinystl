#pragma once
/*********************
author:li linhua
date:2016/10/19
功能清单：

0:llh_map();
~llh_map() {};
构造和析构函数
1:bool empty() { return _size == 0; };
判断容器是否为空
2:void  Insert(const Pair<T,U>& pair);
void InsertFixup(rbtree_node<T, U>* newNode);
向容器中插入元素，插入元素之后需要调整红黑树使其满足红黑树的性质
3:void RotateLeft(rbtree_node<T, U>* node);
void RotateRight(rbtree_node<T, U>* node);
左旋和右旋是为了保证红黑树是一棵平衡二叉树
4:Pair<T, U>* Find(const T& value);
在红黑树中查找键值为value的元素，若查到则返回当前的pair，没有找到则返回NULL
5:Pair<T,U>* operator [] (const T& value);
重载[]运算符，返回键值的pair
6:void Erase(const T& value);
void DeleteFixup(rbtree_node<T, U>* node);
删除某个键的pair，需要重新调整使其满足红黑树的性质
7:void  Clear();
删除map中的所有元素
8:void print();
void inordersort(rbtree_node<T, U>* temp);
按照键值的顺序依次打印数据，即二叉树的中序遍历
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

/***************************map类声明************************/
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
/***************************map类具体实现************************/
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
	if (NULL == node->parent)    //判断之前的node节点是否为根节点
		root = right;
	else if (node == node->parent->right)   //判断node节点是爷爷节点的左节点还是右节点
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
	//情况1：如果是根节点，则将根节点置为黑色
	if (NULL == newNode->parent)
	{
		newNode->color = RB_BLACK;
		return;
	}
	//情况2：如果当前节点的父节点是黑色，保持不变
	if (RB_BLACK == newNode->parent->color)
		return;
	//情况3：如果当前节点的父节点、叔叔节点为红色，将父节点、叔叔节点置为黑色，爷爷节点置为红色，并传入爷爷节点递归调用InsertFixup()
	rbtree_node<T,U>* tmp = UncleNode(newNode);
	if (RB_RED == tmp->color)
	{
		tmp->color = RB_BLACK;
		newNode->parent->color = RB_BLACK;
		newNode->parent->parent->color = RB_RED;
		InsertFixup(newNode->parent->parent);
		return;
	}
	//情况4：父节点P是红色，叔叔节点U是黑色或NIL，插入节点N是其父节点P的左孩子，而父节点P又是其父节点的右孩子。
	if (newNode == newNode->parent->left && newNode->parent == newNode->parent->parent->right)
		
	{
		RotateRight(newNode->parent);
		newNode = newNode->right;
	}
	//情况5：父节点P是红色，叔叔节点U是黑色或NIL，插入节点N是其父节点P的右孩子，而父节点P又是其父节点的左孩子。
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