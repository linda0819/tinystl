#pragma once
/*********************
author:li linhua
date:2016/10/17
功能清单：
llh_deque()
llh_deque(const llh_deque& obj)
void clear()

~llh_deque()
**********************/
#ifndef LLH_DEQUE_H
#define  LLH_DEQUE_H
#define _SCL_SECURE_NO_WARNINGS
#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <utility>   // !=, <=, >, >=
#include <iostream>
using namespace std;

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

template<class T>
void destroy(T* pointer)
{
	pointer->~T();
}
template <typename A, typename BI>
BI destroy(A& a, BI b, BI e) {
	while (b != e) {
		--e;
		a.destroy(&*e);
	}
	return b;
}
/*
class allocator
{
public:
	// 1、为什么需要下面这些成员，有什么作用呢？
	typedef T          value_type;
	typedef T*         pointer;
	typedef const T*   const_pointer;
	typedef T&         reference;
	typedef const T&   const_reference;
	typedef size_t     size_type;       // size_t是无符号整数									
	typedef ptrdiff_t  difference_type;	// ptrdiff_t是有符号整数，代表指针相减结果的类型
}
*/
template < typename T, typename A = std::allocator<T> >
class llh_deque {
private:
	typedef A                                        allocator_type;
	typedef typename allocator_type::value_type      value_type;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::reference       reference;
	typedef typename allocator_type::const_reference const_reference;
public:
	friend bool operator == (const llh_deque& lhs, const llh_deque& rhs) {

		return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	friend bool operator < (const llh_deque& lhs, const llh_deque& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
public:
	class iterator {
	public:
		typedef std::bidirectional_iterator_tag   iterator_category;
		typedef typename llh_deque::value_type      value_type;
		typedef typename llh_deque::difference_type difference_type;
		typedef typename llh_deque::pointer         pointer;
		typedef typename llh_deque::reference       reference;

	public:
		friend bool operator == (const iterator& lhs, const iterator& rhs)
		{
			return (lhs.current_block_index == rhs.current_block_index) && (lhs.current_block == rhs.current_block);
		}
		friend bool operator != (const iterator& lhs, const iterator& rhs) {
			return !(lhs == rhs);
		}
		friend iterator operator + (iterator lhs, difference_type rhs) {
			return lhs += rhs;
		}
		friend iterator operator - (iterator lhs, difference_type rhs) {
			return lhs -= rhs;
		}
	private:
		pointer *current_block;
		std::size_t current_block_index;
	private:
		bool valid() const
		{
			return (current_block_index >= 0) && current_block_index <= (block_size - 1);
		}
	public:
		iterator()
		{
			current_block = static_cast<pointer*>(0);
			current_block_index = 0;
		}
		iterator(pointer* block, std::size_t index)
		{
			current_block = block;
			current_block_index = index;
		}
		reference operator * () const
		{
			return (*current_block)[current_block_index];
		}
		pointer operator -> () const
		{
			return &**this;
		}
		iterator& operator ++ ()
		{
			if (++current_block_index == block_size)
			{
				current_block_index = 0;
				++current_block;
			}
			return *this;
		}
		iterator operator ++ (int)
		{
			iterator x = *this;
			++(*this);
			return x;
		}
		iterator& operator -- ()
		{
			if (current_block_index-- == 0)
			{
				current_block_index = (block_size - 1);
				--current_block;
			}
			return *this;
		}
		iterator operator -- (int)
		{
			iterator x = *this;
			--(*this);
			return x;
		}
		iterator& operator += (difference_type d)
		{
			current_block += d / block_size;
			int index_inc = d % block_size;
			if ((current_block_index + index_inc) >= block_size)
			{
				current_block_index = (current_block_index + index_inc) % block_size;
				++current_block;
			}
			else
			{
				current_block_index += index_inc;
			}
			return *this;
		}
		iterator& operator -= (difference_type d)
		{
			current_block -= d / block_size;
			int index_dec = d % block_size;
			if ((current_block_index - index_dec) > current_block_index)
			{
				current_block_index = block_size - (index_dec - current_block_index);
				--current_block;
			}
			else
			{
				current_block_index -= index_dec;
			}
			return *this;
		}
		pointer* get_block_address() const
		{
			return current_block;
		}
		std::size_t get_block_index() const
		{
			return current_block_index;
		}
		void set_block_address(pointer* new_current_block)
		{
			current_block = new_current_block;
		}

	};
	 public:
		 class const_iterator {
		 public:
			 typedef std::bidirectional_iterator_tag   iterator_category;
			 typedef typename llh_deque::value_type      value_type;
			 typedef typename llh_deque::difference_type difference_type;
			 typedef typename llh_deque::const_pointer   pointer;
			 typedef typename llh_deque::const_reference reference;

		 public:
			 friend bool operator == (const const_iterator& lhs, const const_iterator& rhs)
			 {
				 return (lhs.current_block_index == rhs.current_block_index) && (lhs.current_block == rhs.current_block);
			 }

			 friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
				 return !(lhs == rhs);
			 }

			 friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
				 return lhs += rhs;
			 }
			 friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
				 return lhs -= rhs;
			 }

		 private:
			 pointer* current_block;
			 std::size_t current_block_index;

		 private:
			 bool valid() const
			 {
				 return (current_block_index >= 0) && current_block_index <= (block_size - 1);
			 }

		 public:
			 const_iterator()
			 {
				 current_block = static_cast<const_pointer>(0);
				 current_block_index = 0;
			 }
			 const_iterator(pointer* x, std::size_t index) {
				 current_block = x;
				 current_block_index = index;
			 }
			 const_iterator(iterator it)
			 {
				 current_block = const_cast<pointer*>(it.get_block_address());
				 current_block_index = it.get_block_index();
			 }

			 reference operator * () const {

				 return (*current_block)[current_block_index];
			 }
			 pointer operator -> () const {
				 return &**this;
			 }

			 const_iterator& operator ++ () {
				 if (++current_block_index == block_size)
				 {
					 current_block_index = 0;
					 ++current_block;
				 }
				 return *this;
			 }
			 const_iterator operator ++ (int) {
				 const_iterator x = *this;
				 ++(*this);
				 return x;
			 }
			 const_iterator& operator -- () {
				 if (current_block_index-- == 0)
				 {
					 current_block_index = (block_size - 1);
					 --current_block;
				 }
				 return (*this);
			 }
			 const_iterator operator -- (int) {
				 const_iterator x = *this;
				 --(*this);
				 return x;
			 }
			 const_iterator& operator += (difference_type d) {
				 current_block += d / block_size;
				 int index_inc = d % block_size;
				 if ((current_block_index + index_inc) >= block_size)
				 {
					 current_block_index = (current_block_index + index_inc) % block_size;
					 ++current_block;
				 }
				 else
				 {
					 current_block_index += index_inc;
				 }
				 return const_cast<iterator&>(*this);
			 }
			 const_iterator& operator -= (difference_type d) {
				 current_block -= d / block_size;
				 int index_dec = d % block_size;
				 if ((current_block_index - index_dec) > current_block_index)
				 {
					 current_block_index = block_size - (index_dec - current_block_index);
					 --current_block;
				 }
				 else
				 {
					 current_block_index -= index_dec;
				 }
				 return const_cast<iterator&>(*this);
			 }
			 pointer* get_block_address() const
			 {
				 return current_block;
			 }
			 std::size_t get_block_index() const
			 {
				 return current_block_index;
			 }
		 };
private:

	allocator_type _a;
//rebind的本质应该这么说:给定了类型T的分配器Allocator = allocator <T>
//现在想根据相同的策略得到另外一个类型U的分配器allocator <U>，那么
//	allocator <U> = allocator <T>::Rebind <U>::other.
	typename allocator_type::template rebind<pointer>::other _a_outer;
	pointer* first_block;
	pointer* last_block;
	iterator begin_iterator;
	iterator end_iterator;
	size_type size_num;
	static std::size_t block_size;

 private:
		 bool valid() const
		{
		 return (begin_iterator.get_block_address() <= end_iterator.get_block_address()) && (size_num >= 0) && (first_block <= last_block);
		}
		public:
			explicit llh_deque(const allocator_type& a = allocator_type()) : _a(a)
			{
				size_num = 0;
				first_block = _a_outer.allocate(5);
				for (int i = 0; i < 5; ++i)
				{
					*(first_block + i) = _a.allocate(block_size);
				}

				last_block = first_block + 5;
				begin_iterator = iterator(first_block + 2, 5);
				end_iterator = iterator(first_block + 2, 5);
			}
			
		/*llh_deque拷贝构造函数*/
			llh_deque(const llh_deque& obj)
			{
				int block_num = obj.last_block - obj.first_block;
				size_num = obj.size();
				first_block = _a_outer.allocate(block_num);
				last_block = first_block + block_num;
				for (int i = 0; i < (block_num); ++i)
				{
					*(first_block + i) = _a.allocate(block_size);
				}
				begin_iterator = iterator(first_block + (obj.begin_iterator.get_block_address() - obj.first_block), obj.begin_iterator.get_block_index());
	//			end_iterator = uninitialized_copy(_a, obj.begin_iterator, obj.end_iterator, begin_iterator);
				end_iterator = uninitialized_copy( obj.begin_iterator, obj.end_iterator, begin_iterator);
			}

			~llh_deque()
			{
				destroy(_a, begin_iterator, end_iterator);
				for (pointer* current = first_block; current != last_block; ++current)
				{
					_a.deallocate(*current, block_size);
				}
				_a_outer.deallocate(first_block, last_block - first_block);
			}
			llh_deque& operator = (const llh_deque& obj)
			{
				if (this == &obj) 
				{
					return *this;
				}
				if (size_num >= obj.size_num) 
				{
					iterator new_begin = begin_iterator + (size_num / 2);
					iterator new_end = end_iterator - (size_num / 2);
					if (size_num % 2 == 1)
					{
						--end_iterator;
					}
					std::size_t element_offset = obj.size_num / 2;
					new_begin -= element_offset;
					new_end += element_offset;
					if (obj.size_num % 2 == 1)
					{
						++new_end;
					}
					destroy(_a, begin_iterator, new_begin);
					destroy(_a, new_end, end_iterator);
					begin_iterator = new_begin;
					end_iterator = new_end;
					iterator obj_current = obj.begin_iterator;
					iterator current = begin_iterator;
					while (obj_current != obj.end_iterator)
					{
						*current = *obj_current;
						++obj_current;
						++current;
					}
				}
				else
				{
					destroy(_a, begin_iterator, end_iterator);
					for (pointer* current = first_block; current != last_block; ++current)
					{
						_a.deallocate(*current, block_size);
					}
					_a_outer.deallocate(first_block, last_block - first_block);
					int block_num = obj.last_block - obj.first_block;
					size_num = obj.size();
					first_block = _a_outer.allocate(block_num);
					last_block = first_block + block_num;
					for (int i = 0; i < (block_num); ++i)
					{
						*(first_block + i) = _a.allocate(block_size);
					}
					begin_iterator = iterator(first_block + (obj.begin_iterator.get_block_address() - obj.first_block), obj.begin_iterator.get_block_index());
	//				end_iterator = uninitialized_copy(_a, obj.begin_iterator, obj.end_iterator, begin_iterator);
					end_iterator = uninitialized_copy(obj.begin_iterator, obj.end_iterator, begin_iterator);
				}
				size_num = obj.size_num;
				return *this;
			}
			reference operator [] (size_type index) {

				return *(begin_iterator + index);
			}
			const_reference operator [] (size_type index) const {
				return const_cast<llh_deque*>(this)->operator[](index);
			}
			reference at(size_type index) {
				return *(begin_iterator + index);
			}

			const_reference at(size_type index) const {
				return const_cast<llh_deque*>(this)->at(index);
			}
			reference back() {

				return *(end_iterator - 1);
			}
			const_reference back() const {
				return const_cast<llh_deque*>(this)->back();
			}

			iterator begin() {

				return begin_iterator;
			}
			const_iterator begin() const {

				return const_iterator(begin_iterator);
			}
			void clear() {
				resize(0);
			}
			bool empty() const {
				return !size_num;
			}
			iterator end() {

				return end_iterator;
			}

			const_iterator end() const {

				return const_iterator(end_iterator);
			}

			iterator erase(iterator it)
			{
				iterator result = it + 1;
				if (distance(begin_iterator, it) <= distance(it, end_iterator))
				{
					while (it != begin_iterator)
					{
						*it = *(it - 1);
						--it;
					}
					_a.destroy(&*begin_iterator);
					++begin_iterator;
				}
				else
				{
					while (it != (end_iterator - 1))
					{
						*it = *(it + 1);
						++it;
					}
					_a.destroy(&*(--end_iterator));
				}
				--size_num;
				return result;
			}
			reference front() {

				return *begin_iterator;
			}
			const_reference front() const {
				return const_cast<llh_deque*>(this)->front();
			}

			iterator insert(iterator it, const_reference v)
			{
				if (end_iterator.get_block_address() == last_block && end_iterator.get_block_index() == 0)
				{
					std::size_t it_offset = std::distance(begin_iterator, it);  //keep track of the insertion position
					resize(size_num + 1);

					it = begin_iterator + it_offset;

					iterator temp = end_iterator - 2;

					while (temp != (it - 1))
					{
						*(temp + 1) = *temp;
						--temp;
					}
					*(it) = v;
				}
				else
				{
					++size_num;
					_a.construct(&*end_iterator, value_type());
					++end_iterator;

					iterator temp = end_iterator - 2;

					while (temp != (it - 1))
					{
						*(temp + 1) = *temp;
						--temp;
					}
					*(it) = v;
				}
				return it;
			}
			void pop_back()
			{
				_a.destroy(&*(--end_iterator));
				--size_num;

			}
			void pop_front()
			{
				_a.destroy(&*(begin_iterator++));
				--size_num;
			}

			void push_back(const_reference v)
			{
				if ((last_block == end_iterator.get_block_address()) && end_iterator.get_block_index() == 0)
				{
					resize(size_num + 1, v);
				}
				else
				{
					_a.construct(&*end_iterator, v);
					++end_iterator;
					++size_num;
				}
			}
			void push_front(const_reference v)
			{
				if ((begin_iterator.get_block_address() - first_block) == 0 && begin_iterator.get_block_index() == 0)
				{
					//if there is only one block so far, when we expand the number of blocks, the 
					resize(size_num + 1); //memory reallocation
					pop_back(); //get rid of the new element the resize appaend
					_a.construct(&*(--begin_iterator), v); //get new element in the front

				}
				else
				{
					_a.construct(&*(--begin_iterator), v);
				}
				++size_num;
			}

			void resize(size_type s, const_reference v = value_type())
			{
				if (s <= size_num)
				{
					std::size_t count = size_num - s;
					while (count-- != 0)
					{
						_a.destroy(&(*end_iterator));
						--end_iterator;
					}
					size_num = s;
				}
				else
				{
					std::size_t block_num = (s / block_size + 1) * 2;
					pointer* new_first_block = _a_outer.allocate(block_num);

					pointer* old_begin_block = begin_iterator.get_block_address();
					pointer* old_end_block = end_iterator.get_block_address();
					std::size_t blocks_filled = old_end_block - old_begin_block;
					if (end_iterator.get_block_index() != 0)
					{
						++blocks_filled;
					}

					pointer* temp_first = first_block;
					pointer* temp_last = last_block;

					while (temp_first != begin_iterator.get_block_address())
					{
						_a.deallocate(*temp_first, block_size);
						++temp_first;
					}

					if (end_iterator.get_block_index() != 0)
					{
						while (end_iterator.get_block_address() != --temp_last)
						{
							_a.deallocate(*temp_last, block_size);
						}
					}
					else
					{
						while (end_iterator.get_block_address() != temp_last)
						{
							--temp_last;
							_a.deallocate(*temp_last, block_size);
						}
					}

					begin_iterator.set_block_address(new_first_block + ((s / block_size + 1) / 2));
					end_iterator = begin_iterator + size_num;

					pointer* current = new_first_block;
					pointer* old_first_block = first_block;
					pointer* old_last_block = last_block;

					first_block = new_first_block;
					last_block = new_first_block + block_num;

					while (current != begin_iterator.get_block_address())
					{
						*current = _a.allocate(block_size);
						++current;
					}
					while (blocks_filled-- != 0)
					{
						*current = *old_begin_block;
						++current;
						++old_begin_block;
					}
					while (current != last_block)
					{
						*current = _a.allocate(block_size);
						++current;
					}
					std::size_t count = s - size_num;
					while (count-- != 0)
					{
						_a.construct(&*end_iterator, v);
						++end_iterator;
					}
					size_num = s;
					_a_outer.deallocate(old_first_block, old_last_block - old_first_block);
				}
			}
			size_type size() const {

				return size_num;
			}
			void swap(llh_deque& obj) {
				pointer* temp_first = obj.first_block;
				pointer* temp_last = obj.last_block;
				iterator temp_begin = obj.begin_iterator;
				iterator temp_end = obj.end_iterator;

				obj.first_block = first_block;
				obj.last_block = last_block;
				obj.begin_iterator = begin_iterator;
				obj.end_iterator = end_iterator;

				first_block = temp_first;
				last_block = temp_last;
				begin_iterator = temp_begin;
				end_iterator = temp_end;

				obj.size_num ^= size_num;
				size_num ^= obj.size_num;
				obj.size_num ^= size_num;
			}
};

template<typename T, typename A>
typename std::size_t llh_deque<T, A>::block_size = 10;

#endif