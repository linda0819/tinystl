#pragma once
/*********************
author:li linhua
date:2016/10/17
�����嵥��
0.��ʼ��
void init();
1.���캯��
llh_list();
llh_list(int n);
llh_list(int num, T value);
llh_list(llh_list<T> const &obj);
llh_list(const llh_list<T> &L, int r, int n);
2.������(�ڵ�ǰ����ͽ������)
node<T>* insertAsFirst(T const&);
node<T>* insertAsLast(T const&);
node<T> *insertafter(node<T> *p, int value);
node<T> *insertbefore(node<T> *p, int value);
3���
void clear();
4.���ش�С
int size() { return _size; }
5.�ж��Ƿ�Ϊ��
bool empty() { return (_size == 0); }   //�ж��Ƿ�Ϊ�ձ�
6.��������ʽ����ʱֻ�����sort,���ǵײ�ʵ�������������㷨�������
void insertsort(node<T>* p, int n);   //��������
void selectsort(node<T>* p, int n);   //ѡ������
7.ʹ��ʱ�б���������������У�ʹlist�е�Ԫ��Ψһ��,����ֵ����ɾ�����ٸ����
int uniquify(); 
8.ѡ���б��е������
node<T>* selectmax();  //ѡ��list�������н������ֵ
node<T>* selectmax(node<T> *p, int n);
9.ɾ��ĳ����㣬��������ɾ������ֵ
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
/*      ������ʵ��           */
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
/*      list���ʵ��           */
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
	node<T>* find(T & e, int n, node<T>* p);  //�����Խ��p��β�ĵ���ǰn��������Ƿ���Ԫ��e
	node<T>* search(T const&);
	node<T>* search(T const& e, int n, node<T>* p);
	llh_list();
	llh_list(int n);
	llh_list(int num, T value);
	llh_list(llh_list<T> const &obj);
	llh_list(const llh_list<T> &L, int r, int n);
	~llh_list();
	int size() { return _size; }
	bool empty() { return (_size == 0); }   //�ж��Ƿ�Ϊ�ձ�
	bool valid(node<T>* p) { return p && (p != head) && p(!= tail); }   //�жϽ���Ƿ���Ч
	void insertsort(node<T>* p, int n);   //��������
	void selectsort(node<T>* p, int n);   //ѡ������
	node<T>* selectmax();  //ѡ��list�������н������ֵ
	node<T>* selectmax(node<T> *p, int n); 
	void reverse();   //ʹlist�е�Ԫ�ط�ת
	void sort(node<T>* p, int n);   
	void sort();     //���򣬲��������ѡ���������
	int uniquify(); //ʹ��ʱ�б���������������У�ʹlist�е�Ԫ��Ψһ��,����ֵ����ɾ�����ٸ����
	void swap(llh_list<T> &obj);
private:
	node<T>* head;
	node<T>* tail;
	int _size;
};
/*************�б��ʼ��������ͷ����β�����****************/
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
/***********************�������Ԫ��**************************/
template<class T>
void llh_list<T>::clear()
{
	while (_size > 0) remove(head->next);
}
/*************ɾ��ĳ����㣬��������ɾ������ֵ*************/
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
/*     ���캯��      */
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
/*     ��������      */
template<class T>
llh_list<T>::~llh_list()
{
	clear();
	delete head;
	delete tail;
}
/***********����ĳ��㿪ʼ��ǰn����㿽������ǰ�б��ͷ��********/
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
/*************����[]�����������ص�ǰ�����Ľ���ֵ*******************/
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
/**���ص��ںŲ���������ԭ���б��ͷŲ����Ⱥ�֮����б���󿽱�����ǰ����***/
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
/***************����ͷ���֮��ĵ�һ��Ԫ�ؽ��**********************/
template<class T>
node<T>* llh_list<T>::first()const
{
	return head->next;
}
/*************���б�ͷ������Ԫ��(�����·����ڴ�)*********************/
template <typename T>
node<T>* llh_list<T>::insertAsFirst(T const& e) {
	_size++;
	return head->insertAsnext(e);
}
/*************���б�β������Ԫ��(�����·����ڴ�)*********************/
template <typename T>
node<T>* llh_list<T>::insertAsLast(T const& e) {
	cout << "insertAsLast" <<e<< endl;
	_size++;
	return tail->insertAsPred(e);
}
/*************��ĳ���������Ԫ��(�����·����ڴ�)*********************/
template <typename T>
node<T> *llh_list<T>::insertafter(node<T> *p, int value)
{
	_size++;
	return p->insertAsnext(value);
}
/*************��ĳ�����ǰ����Ԫ��(�����·����ڴ�)*********************/
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
/****���ҽ��pǰn��������ǵ�һ��С�ڴ����ҵ�Ԫ�أ����ҵ����ؽ��*******/
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
/******���ҽ��pǰn��������Ƿ���ڴ�����Ԫ�أ����ҵ����ؽ��***********/
template <typename T>
node<T>* llh_list<T>::find(T & e, int n, node<T>* p)
{
	while (n-- > 0)
	{
		if (e == (p = p->pre)->value)   return p; 	
		return nullptr;
	}
}
/****************���򷽷�����ѡ��*********************************/
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
/**********************��������*****************************/
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
/****************************ѡ������*************************/
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
/**********�����б���ĳ�����֮��n�����������**************/
template <typename T>
node<T>* llh_list<T>::selectmax(node<T> *p, int n)
{
	node<T>* max = p;
	for (node<T>* cur = p; n > 1; n--)
		if (((cur = cur->next)->value) > max->value)  max = cur;
	return max;
}
/****************�����б�������*****************************/
template <typename T>
node<T>* llh_list<T>::selectmax()
{
	return selectmax(first(),size);
}
/****************���б��е�Ԫ�ط�ת******************************/
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
/****ȥ���б����ظ����ֵĽ�㣬ֻ����һ����������ɾ��������****/
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
/*******************�����������ֵ���жԵ�************************/
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