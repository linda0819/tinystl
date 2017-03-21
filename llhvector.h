#pragma once
/***************************
author:Linda li
date:2016/10/13
0:llh_vector();
llh_vector(size_t n, T  obj);
llh_vector(iterator begin, iterator end);
~llh_vector();
llh_vector(const llh_vector& obj);
构造函数和析构函数
1:llh_vector& operator=(const llh_vector& obj);
重载等号操作符
2:bool empty() const { return begin() == end(); }
判断容器是否为空
3:size_type size() const { return (size_type)(finish - start); }
返回容器的元素个数
4:size_type capacity() const { return (size_type)(end_of_storage - start); }
返回容器的当前内存大小
5:iterator begin() { return start; }
const_iterator begin() const { return start; }
返回首部迭代器
6:iterator end() { return finish; }
const_iterator end() const { return finish; }
返回尾部迭代器
7:reference operator[](size_type i) { return *(start + i); }
const_reference operator[](size_type i)const { return *(start + i); }
重载[]迭代器，返回第i的元素的值
8:void push_back(const T& value);
插入元素
9:void insert(iterator position, size_type n, const T& value);
在迭代器之前插入n个值为value的元素
10:void pop_back();
从尾部弹出元素
11:void erase(iterator first, iterator last);
删除两个迭代器之间的元素
12:void clear();
删除容器的所有元素
13:void reserve(size_type n);
重新分配内存空间，若n小于当前空间大小则不作改变，反之重新分配更大空间并将当前数据拷贝至新内存
14:void resize(size_type n, value_type &value);
重新分配元素的长度，若n大于当前容器的元素个数，需要将不足部分用value进行补充，反之则去除多余部分
****************************/
#ifndef LLH_VECTOR_H
#define LLH_VECTOR_H
#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
//#include <algorithm>
#include <memory>
using namespace std;

template<class T>
void destroy(T* pointer)
{
	pointer->~T();
}
template<class ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last)
{
	for (ForwardIterator it = first; it != last; ++it)
	{
		destroy(&*it);
	}
}
template<class T>
class llh_vector {
	friend ostream& operator<<(ostream &out, llh_vector<T> &obj)
	{
		for (iterator it = obj.start; it != obj.finish; it++)
		{
			out << *it << " ";
		}
		out << endl;
		return out;
	}
public:
	using	value_type=T;
	using 	iterator= T*;
	using	const_iterator= const T*;
	using 	pointer= T*;
	using	reference= T&;
	using	const_reference= const T&;
	using	size_type=size_t;
public:
	llh_vector();
	llh_vector(size_t n, T  obj);
	llh_vector(iterator begin, iterator end);
	~llh_vector();
	llh_vector(const llh_vector& obj);
	llh_vector& operator=(const llh_vector& obj);
	bool empty() const { return begin() == end(); }
	size_type size() const { return (size_type)(finish - start); }
	size_type capacity() const { return (size_type)(end_of_storage - start); }
	iterator begin() { return start; }
	const_iterator begin() const { return start; }
	iterator end() { return finish; }
	const_iterator end() const { return finish; }
	reference operator[](size_type i) { return *(start + i); }
	const_reference operator[](size_type i)const { return *(start + i); }
	void push_back(const T& value);
	void insert(iterator position, size_type n, const T& value);
    void pop_back();
	void erase(iterator first, iterator last);
    void clear();
	void reserve(size_type n);
	void resize(size_type n, value_type &value);
	
protected:
	iterator start;   //空间的头
	iterator finish;  //空间的尾
	iterator end_of_storage; //可用空间的尾巴
private:
	static std::allocator<T> alloc; // object to get raw memory

};
template<class T>
allocator<T> llh_vector<T>::alloc;

template<class T>
llh_vector<T>::llh_vector()
{
	start = nullptr;
	finish = nullptr;
	end_of_storage = nullptr;
}

template<class T>
llh_vector<T>::llh_vector(size_t n, T  obj)
{
	start = alloc.allocate(n);
	end_of_storage = finish = start + n;
	for (iterator i = start; i != finish; ++i)
		alloc.construct(i, obj);
}
template<class T>
llh_vector<T>::llh_vector(iterator begin, iterator end)
{
	const size_type n = end - begin;
	start = alloc.allocate(n);
	end_of_storage = finish = start + n;
	std::uninitialized_copy(begin, end, start);
}
template<class T>
llh_vector<T>::~llh_vector()
{
	::destroy(start, finish);
	alloc.deallocate(start, end_of_storage - start);
}
template<class T>
llh_vector<T>::llh_vector(const llh_vector &obj)
{
    const	size_type n = obj.capacity();
	start = alloc.allocate(n);
	std::uninitialized_copy(obj.start, obj.finish, start);
	finish = start + (obj.finish - obj.start);
	end_of_storage = start + (obj.end_of_storage - obj.start);
}
template<class T>
llh_vector<T>& llh_vector<T>::operator=(const llh_vector& obj)
{
	if (this->capacity()) {
		destroy(start, finish);
		alloc.deallocate(start, end_of_storage - start);
		start = finish = end_of_storage = nullptr;
	}
	const	size_type n = obj.capacity();
	start = alloc.allocate(n);
	std::uninitialized_copy(obj.start, obj.finish, start);
	finish = start + (obj.finish - obj.start);
	end_of_storage = start + (obj.end_of_storage - obj.start);
	return *this;
}
template<class T>
void llh_vector<T>::insert(iterator position, size_type n, const T& value)
{
	if (n<end_of_storage-finish)
	{
		if (n < finish - position) {
			std::uninitialized_copy(finish - n, finish, finish);
			std::copy(position, finish - n, position + n);
			std::fill_n(position, n, value);
		}
		else {
			std::uninitialized_fill_n(finish, n - (finish - position), value);
			std::uninitialized_copy(position,finish,position+n);
			std::fill(position, finish, value);
		}
			finish += n;
	}
	else
	{
		iterator starttemp = start, finishtemp = finish, end_of_storagetemp = end_of_storage;
		size_t oldspace = end_of_storage - start;
		size_t new_size = oldspace + max(n, oldspace);
		starttemp = alloc.allocate(new_size);
		finishtemp= std::uninitialized_copy(start, position, starttemp);  //带有copy和fill的，第二个迭代器是最后一个元素的下一个迭代器
		std::uninitialized_fill_n(finishtemp, n, value);		
		finishtemp += n;
		finishtemp = std::uninitialized_copy(position, finish, finishtemp);
		destroy(start, finish);
		alloc.deallocate(start, end_of_storage - start);
		start = starttemp;
		finish = finishtemp;
		end_of_storagetemp = start + new_size;
	}
	
}

template<class T>
void llh_vector<T>::push_back(const T& value)
{
	insert(this->end(), 1, value);
}

template<class T>
void llh_vector<T>::pop_back() 
{
	if (finish > start) {
		::destroy(finish - 1, finish);
		finish--;
	}
	else
	{
		cerr<< "pop err!" << endl;
	}
}
template<class T>
void llh_vector<T>::erase(iterator first, iterator last)
{
	iterator finishtemp=finish;
    finish=copy(last,finish,first);
	::destroy(finish, finishtemp);
}
template<class T>
void llh_vector<T>::clear()
{
	 //erase(start, finish);	 //作用和下面两句一样
	::destroy(start, finish);
	finish = start;
}
/*
reserve的功能是如果当前容量小于你，则分配空间，如果当前容量大于n,则不作处理
*/
template<class T>
void llh_vector<T>::reserve(size_type n)
{

	if (capacity() < n)
	{
		size_t len = finish - start;
		iterator starttemp = alloc.allocate(n);
		std:: uninitialized_copy(start, finish, starttemp);
		::destroy(start, finish);
		alloc.deallocate(start, size());
		start = starttemp;
		finish = start+len;
		end_of_storage = starttemp + n;
	}
}
template<class T>
void llh_vector<T>::resize(size_type n, value_type &value)
{
	if (n < capacity())
	{
		erase(start + n, finish);
	}
	else
	{
		insert(end(), n - size(), value)
	}
}

#endif