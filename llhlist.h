#pragma once
/*********************
author:li linhua
date:2016/10/17
功能清单：
0.初始化
void init();
1.构造函数
llh_list();
llh_list(int n);
llh_list(int num, T value);
llh_list(llh_list<T> const &obj);
llh_list(const llh_list<T> &L, int r, int n);
2.插入结点(节点前插入和结点后插入)
node<T>* insertAsFirst(T const&);
node<T>* insertAsLast(T const&);
node<T> *insertafter(node<T> *p, int value);
node<T> *insertbefore(node<T> *p, int value);
3清除
void clear();
4.返回大小
int size() { return _size; }
5.判断是否为空
bool empty() { return (_size == 0); }   //判断是否为空表
6.两种排序方式，用时只需调用sort,但是底层实现是两种排序算法随机出现
void insertsort(node<T>* p, int n);   //插入排序
void selectsort(node<T>* p, int n);   //选择排序
7.使用时列表必须是已排序序列，使list中的元素唯一化,返回值代表删除多少个结点
int uniquify(); 
8.选择列表中的最大结点
node<T>* selectmax();  //选择list对象所有结点的最大值
node<T>* selectmax(node<T> *p, int n);
9.删除某个结点，并返回已删除结点的值
T llh_list<T>::remove(node<T> *obj)
**********************/
#ifndef LLH_LIST_H
#define LLH_LIST_H
#include<iostream>
#include<iterator>
#include <algorithm>
#include <memory>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
/*      链表结点实现           */
template<class T>
class node {
public:
	T value;
	node<T> *pre;
	node<T> *next;
	node();
	node(T val, node *preobj = nullptr, node *nextobj = nullptr);
	node<T>* insertAsPred(const T &val);
	node<T>* insertAsnext(const T &val);
};
template<class T>
node<T>::node()
{
	value = 0, pre = nullptr, next = nullptr;
}
template<class T>
node<T>::node(T val, node<T> *preobj=nullptr,  node<T> *nextobj=nullptr)
{
	value = val;
	pre = preobj;
	next=nextobj;
}
template<class T>
node<T>* node<T>::insertAsPred(const T &val)
{
	node<T>* x = new node<T>(val,pre, this);
	pre->next = x;
	pre = x;
	return x;
}

template<class T>
node<T>* node<T>::insertAsnext(const T &val)
{
	node<T>* x = new node<T>(val, this, next);
	next->pre = x;
	next = x;
	return x;
}
/*      list类的实现           */
template<class T>
class llh_list {
	friend ostream & operator<<(ostream &out, llh_list<T> &obj)
	{
		for (int i = 0; i < obj.size(); i++)
			out << obj[i] << "  ";
		return out;
	}
public:
	void init();
	void clear();
	node<T>* first()const;
	T remove(node<T> *obj);
	void copy_node(node<T> *start, int n);
	T& operator[] (int index);
	llh_list& operator=(const llh_list<T> &obj);
	node<T>* insertAsFirst(T const&);
	node<T>* insertAsLast(T const&);
	node<T> *insertafter(node<T> *p, int value);
	node<T> *insertbefore(node<T> *p, int value);
	node<T>* find(T & e, int n, node<T>* p);  //查找以结点p结尾的倒数前n个结点中是否有元素e
	node<T>* search(T const&);
	node<T>* search(T const& e, int n, node<T>* p);
	llh_list();
	llh_list(int n);
	llh_list(int num, T value);
	llh_list(llh_list<T> const &obj);
	llh_list(const llh_list<T> &L, int r, int n);
	~llh_list();
	int size() { return _size; }
	bool empty() { return (_size == 0); }   //判断是否为空表
	bool valid(node<T>* p) { return p && (p != head) && p(!= tail); }   //判断结点是否有效
	void insertsort(node<T>* p, int n);   //插入排序
	void selectsort(node<T>* p, int n);   //选择排序
	node<T>* selectmax();  //选择list对象所有结点的最大值
	node<T>* selectmax(node<T> *p, int n); 
	void reverse();   //使list中的元素翻转
	void sort(node<T>* p, int n);   
	void sort();     //排序，插入排序和选择排序随机
	int uniquify(); //使用时列表必须是已排序序列，使list中的元素唯一化,返回值代表删除多少个结点
	void swap(llh_list<T> &obj);
private:
	node<T>* head;
	node<T>* tail;
	int _size;
};
/*************列表初始化，创建头结点和尾部结点****************/
template<class T>
void llh_list<T>::init()
{
	head = new node<T>;
	tail = new node<T>;
	head->next = tail;
	head->pre = nullptr;
	tail->pre = head;
	tail->next= nullptr;
	_size = 0;
}
/***********************清除所有元素**************************/
template<class T>
void llh_list<T>::clear()
{
	while (_size > 0) remove(head->next);
}
/*************删除某个结点，并返回已删除结点的值*************/
template<class T>
T llh_list<T>::remove(node<T> *obj)
{
	T temp = obj->value;
	obj->pre->next =obj->next;
	obj->next->pre=obj->pre;
	delete obj;
	_size--;
	return temp;
}
/*     构造函数      */
template<class T>
llh_list<T>::llh_list()
{
	init();
}
template<class T>
llh_list<T>::llh_list(int n)
{
	init();
	head->insertAsnext(n);
	_size++;
}
template<class T>
llh_list<T>::llh_list(int num, T value)
{
	init();
	node<T>* temp = head;
	while (num--) head=insertAsFirst(value);
	head = temp;

}
template<class T>
llh_list<T>::llh_list( llh_list<T> const &obj)
{
	copy_node(obj.first(), obj._size);
}
template<class T>
llh_list<T>::llh_list(const llh_list<T> &L, int r, int n)
{
	copy_node(L[r], n);
}
/*     析构函数      */
template<class T>
llh_list<T>::~llh_list()
{
	clear();
	delete head;
	delete tail;
}
/***********将以某结点开始的前n个结点拷贝至当前列表的头部********/
template<class T>
void llh_list<T>::copy_node(node<T> *start,int n)
{
	init();
	while (n--)
	{
		insertAsLast(start->value);
		start = start->next;
	}
}
/*************重载[]操作符，返回当前索引的结点的值*******************/
template<class T>
T& llh_list<T>::operator[] (int index) 
{
	node<T> *p = first();
	while (index--)
	{
		p = p->next;
	}
	return p->value;
}
/**重载等于号操作符，将原来列表释放并将等号之后的列表对象拷贝至当前对象***/
template<class T>
llh_list<T>& llh_list<T>::operator=(const llh_list<T> &obj)
{
	_size = obj._size;
	clear();
	int temp= obj._size;
	while (temp--)
	{
		insertAsLast(obj.head->next->value);
		obj.head->next = obj.head->next->next;
	}
	return *this;
}
/***************返回头结点之后的第一个元素结点**********************/
template<class T>
node<T>* llh_list<T>::first()const
{
	return head->next;
}
/*************在列表头部插入元素(会重新分配内存)*********************/
template <typename T>
node<T>* llh_list<T>::insertAsFirst(T const& e) {
	_size++;
	return head->insertAsnext(e);
}
/*************在列表尾部插入元素(会重新分配内存)*********************/
template <typename T>
node<T>* llh_list<T>::insertAsLast(T const& e) {
	cout << "insertAsLast" <<e<< endl;
	_size++;
	return tail->insertAsPred(e);
}
/*************在某个结点后插入元素(会重新分配内存)*********************/
template <typename T>
node<T> *llh_list<T>::insertafter(node<T> *p, int value)
{
	_size++;
	return p->insertAsnext(value);
}
/*************在某个结点前插入元素(会重新分配内存)*********************/
template <typename T>
node<T> *llh_list<T>::insertbefore(node<T> *p, int value)
{
	_size++;
	return p->insertAsPred(value);
}
template <typename T>
node<T>* llh_list<T>::search(T const& e)
{
	return search(e, _size,tail);
}
/****查找结点p前n个结点中是第一个小于待查找的元素，若找到返回结点*******/
template <typename T>
node<T>* llh_list<T>::search(T const& e, int n, node<T>* p)
{
	std::cout << "Searching for" << e << std::endl;
	while (n-- > 0)
	{
		if ( (p = p->pre)->value<=e) break;
	}
	return p;
}
/******查找结点p前n个结点中是否存在待查找元素，若找到返回结点***********/
template <typename T>
node<T>* llh_list<T>::find(T & e, int n, node<T>* p)
{
	while (n-- > 0)
	{
		if (e == (p = p->pre)->value)   return p; 	
		return nullptr;
	}
}
/****************排序方法进行选择*********************************/
template <typename T>
void llh_list<T>::sort(node<T>* p, int n)
{
	srand((unsigned int)time(0));
	int num = rand() % 2;
	switch (num)
	{
	case 1:insertsort(p, n); break;
	case 0:selectsort(p, n); break;
	default:
		break;
	}
	
}
/**********************插入排序*****************************/
template <typename T>
void llh_list<T>::insertsort(node<T>* p, int n)
{
	cout << "insertsort :" << endl;
		for (int i = 1; i <= n; i++)
		{
			insertafter(search(p->value,i,p),p->value);
			p = p->next;
			remove(p->pre);
		}
}
/****************************选择排序*************************/
template <typename T>
void llh_list<T>::selectsort(node<T>* p, int n)
{
	cout << "selectsort : " << endl;
	node<T>* head = p->pre;
	node<T>* tail = p;
	for (int i = 0; i < n; i++)
		tail = tail->next;
	while (n>1)
	{
		node<T> *max=selectmax(head->next,n);
		insertbefore(tail, remove(max));
		tail = tail->pre;
		n--;
	}
}
template <typename T>
void llh_list<T>::sort()
{
	cout << _size << endl;
	sort(first(), _size);
}
/**********返回列表中某个结点之后n个结点的最大结点**************/
template <typename T>
node<T>* llh_list<T>::selectmax(node<T> *p, int n)
{
	node<T>* max = p;
	for (node<T>* cur = p; n > 1; n--)
		if (((cur = cur->next)->value) > max->value)  max = cur;
	return max;
}
/****************返回列表的最大结点*****************************/
template <typename T>
node<T>* llh_list<T>::selectmax()
{
	return selectmax(first(),size);
}
/****************将列表中的元素翻转******************************/
template <typename T>
void llh_list<T>::reverse()
{
	node<T> *headtemp = head;
	node<T> *tailtemp = tail;
	for (int i = 0; i < _size;i++ )
	{
		insertafter(headtemp, remove(tailtemp->pre));
		headtemp = headtemp->next;
	}
}
/****去除列表中重复出现的结点，只保留一个，并返回删除结点个数****/
template <typename T>
int llh_list<T>::uniquify()
{
	node<T> *headtemp = first();
	int oldsize = _size;
	while(tail!= headtemp->next)
	{
		if ((headtemp->value) == (headtemp->next)->value)
			remove(headtemp->next);
		else
			headtemp=headtemp->next;
	}
	return oldsize - _size;
}
/*******************将两个对象的值进行对调************************/
template <typename T>
void llh_list<T>::swap(llh_list<T> &obj)
{
	llh_list<T> *temp=new llh_list<T>;
	temp->copy_node(this->first(), this->size());
	clear();
	copy_node(obj.first(), obj.size());
	obj.clear();
	obj.copy_node(temp->first(), temp->size());
	delete temp;
}
#endif