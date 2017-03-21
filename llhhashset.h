#pragma once
/*********************
author:li linhua 
date:2016/10/20
���ڹ�ϣ����������ƣ�Ŀǰֻ�ܴ洢��������
�����嵥��
0:llh_hashset();
llh_hashset(int length);
���캯������Ϊ�޲ι�����вι��캯�����޲ι���Ĭ�ϴ�СΪ10���вο����Լ��趨��ϣ��ĳ���
1:~llh_hashset();
���������ͷ��ڴ�
2:void insert(T data);
��set�������Ԫ�أ�ÿһ�а��մ�С�����˳��������ͬ��Ԫ�ز�������
3:bool empty();
�ж������Ƿ�Ϊ��
4:void print();
����˳����˳��ʹ�С˳�����δ�ӡ
5:void del(T data);	
ɾ��ĳ��Ԫ��
6:void clear();	
ɾ������������Ԫ�أ����������ٹ�ϣ��
7:bool find(T data);
����ĳ��Ԫ���Ƿ���������
8:llh_hashset<T>& operator =(llh_hashset<T> &obj);
���صȺŲ�����
**********************/
#define _CRT_SECURE_NO_WARNINGS
#ifndef _LLH_HASHSET_H
#define _LLH_HASHSET_H
#include<iostream>
#include<stdio.h>
using namespace std;
template<typename T>
#define LEN 10
class node
{
public:
	T value;
	node *next;
};
template<typename T>
class llh_hashset {
public:
	llh_hashset();
	llh_hashset(int length);
	~llh_hashset();
	void insert(T data);
	bool empty();
	void print();
	void del(T data);				//delete data
	void clear();					//clear all the elements
	bool find(T data);
	llh_hashset<T>& operator =(llh_hashset<T> &obj);
	node<T> **head;
	int _size;
	int number;
};

template<typename T>
llh_hashset<T>::llh_hashset()
{
	head = new node<T> *[LEN];
	for (int i = 0; i < LEN; i++)
	{
		head[i] = new node<T>;
		head[i]->next = NULL;
	}
	_size=LEN;
	number = 0;
}
template<typename T>
llh_hashset<T>::llh_hashset(int length)
{
	if (length < LEN)  _size = LEN;
	else  _size=length;
	head = new node<T> *[length];
	for (int i = 0; i < _size; i++)
	{
		head[i] = new node<T>;
		head[i]->next = NULL;
	}
	number = 0;
}

template<typename T>
llh_hashset<T>::~llh_hashset()
{
	node<T> *p;
	node<T> *q;
	for (int i = 0; i < _size; i++)	//scan
	{
		p = head[i]->next;
		if (NULL == p)
			continue;
		q = p->next;
		while (NULL != q)
		{
			delete p;				
			p = q;
			q = p->next;
		}
		delete p;					
	}
	delete[] head;					
}

template<typename T>
void llh_hashset<T>::insert(T data)
{
	int it = data % _size;		//index
	node<T>* p = head[it];
	while (p->next && p->next->value < data)
	{
		p = p->next;			//find insert position
	}
	if (p->next && data == p->next->value)
		return;
	node<T> *q = new node<T>;
	q->value = data;			//insert data
	q->next = p->next;
	p->next = q;
	number++;
}
template<typename T>
bool llh_hashset<T>::empty()
{
	if (number == 0)  return true;
	else return false;
}
template<typename T>
void llh_hashset<T>::print()
{
	for (int i = 0; i < _size; i++)
	{
		if (head[i]->next != NULL)
		{
			node<T> *q = head[i]->next;
			while (q != NULL)
			{
				cout << q->value<<" ";
				q = q->next;
			}
		}
	}
	cout << endl;
}
template<typename T>
void llh_hashset<T>::del(T data)
{
	int it = data % _size;		//index
	node<T>* p = head[it];
	node<T>* q=p->next;
	if (q==NULL)  return;
	while (q->next!=NULL && q->value != data)
	{
		p = q;
		q = q->next;
	}
	if (q->next == NULL && q->value != data)		
	{
		cout << "no data: " << data << endl;
		return;
	}
	p->next = q->next;
	delete q;
	number--;
}

template<typename T>
bool llh_hashset<T>::find(T data)
{
	int it = data % _size;		//index
	node<T>* p = head[it];
	node<T>* q = p->next;
	if (p->next == NULL)
	{
		return false;
	}
	while (q->next != NULL &&q->value != data)
	{
		p = q;
		q = q->next;
	}
	if (q->next != NULL &&q->value != data)
	{
		return false;
	}
	return true;
}
template<typename T>
void llh_hashset<T>::clear()
{
	for (int i = 0; i < _size; i++)
	{
		node<T> *p = head[i];
		if (p->next==NULL)
		{
		continue;
		}
		else {
			node<T> *q = p->next;
			while (q->next != NULL)
			{
				p->next = q->next;
				delete q;
			}
		}
	}
	for (int i = 0; i < _size; i++)	//scan
		head[i]->next = NULL;
	number--;
}
template<typename T>
llh_hashset<T> &llh_hashset<T>:: operator =(llh_hashset<T> &obj)
{
	{
		node<T> *p;
		node<T> *q;
		for (int i = 0; i < _size; i++)	//scan
		{
			p = head[i]->next;
			if (NULL == p)
				continue;
			q = p->next;
			while (NULL != q)
			{
				delete p;
				p = q;
				q = p->next;
			}
			delete p;
		}
		delete[] head;
	}
	{
		head = new node<T> *[LEN];
		for (int i = 0; i < LEN; i++)
		{
			head[i] = new node<T>;
			head[i]->next = NULL;
		}
		_size = LEN;
	}
	for (int i = 0; i < obj._size; i++)
	{
		node<T> *p = obj.head[i];
		node<T> *q = this->head[i];
		if (p->next == NULL)
		{
			q->next = NULL;
		}
		else {
			while (p->next != NULL)
			{
				//node<T> *temp = q->next;
				node<T> *temp2 = new node<T>;
				temp2->value = p->next->value;
				temp2->next = NULL;
				q->next = temp2;
				p = p->next;
				q = q->next;
			}
		}
	}
	number = obj.number;
	return *this;
}
#endif
