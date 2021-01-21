#pragma once
#include <iostream>
#include <cmath>
template <class T>
class DynamicArray
{
private:
	T* arr;
	int logSize, capacity;
	void resize();
public:
	DynamicArray() :arr(nullptr), logSize(0), capacity(0) {}
	DynamicArray(const int& size) :arr(new T[size]), logSize(0), capacity(size) {}
	DynamicArray(const DynamicArray& other) :arr(nullptr) { *this = other; }
	~DynamicArray() { delete[] arr; }

	DynamicArray& operator=(const DynamicArray& other);
	T& operator[](const int& idx)const { return arr[idx]; }
	bool operator==(const DynamicArray& other) { return arr == other.arr; }
	bool operator!=(const DynamicArray& other) { return arr != other.arr; }

	const T& front() const { return arr[0]; }
	const T& back() const { return arr[logSize-1]; }

	const int& getLogSize() const { return logSize; }
	const int& getCapacity() const { return capacity; }
	bool isEmpty() const { return logSize == 0; }
	void makeEmpty() { logSize = 0; }
	
	void push_back(const T& value);

	// =============== ITERATORS
	class iterator;
	class const_iterator;
	class reverse_iterator;
	// =============== _ITERATORS

	const iterator& insert(const iterator& pos, const T& val);
	iterator erase(const iterator& iter);
	iterator erase(const iterator& first, const iterator& last);

	// =============== NEED TO ADD RBEGIN,REND ETC..

	const_iterator begin() const{ return const_iterator(*this, 0); }
	const_iterator end() const{ return const_iterator(*this, logSize); }

	iterator begin() { return iterator(*this, 0); }
	iterator end() { return iterator(*this, logSize); }
};

// =============== ITERATOR
template <class T>
class DynamicArray<T>::iterator {
private:
	DynamicArray* da;
	int i;
public:
	using iterator_category = std::bidirectional_iterator_tag;
	// other options exist, e.g., std::forward_iterator_tag
	using different_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	iterator(DynamicArray& _da, const int& _i) :da(&_da), i(_i) {}
	iterator(const iterator& other) :da(other.da), i(other.i) {}

	static int distance(const iterator& itr1, const iterator& itr2) { return abs(itr1.i - itr2.i); }

	iterator& operator=(const iterator& other) { da = other.da;	i = other.i; return *this; }
	bool operator==(const iterator& other) const { return da == other.da && i == other.i; }
	bool operator!=(const iterator& other) const { return !(*this == other); }
	bool operator>(const iterator& other)const { return this->i > other.i; }
	bool operator<(const iterator& other)const { return this->i < other.i; }
	bool operator<=(const iterator& other)const { return this->i <= other.i; }
	bool operator>=(const iterator& other)const { return this->i >= other.i; }

	T& operator*() { return da->arr[i]; }
	T* operator->() { return &(da->arr[i]); }

	iterator& operator++() { ++i; return *this; }
	iterator operator++(int) { iterator temp(*this); ++i; return temp; }
	iterator& operator--() { --i; return *this; }
	iterator operator--(int) { iterator temp(*this); --i; return temp; }
};
// =============== CONST ITERATOR
template <class T>
class DynamicArray<T>::const_iterator {
private:
	const DynamicArray* da;
	int i;
public:
	using const_iterator_category = std::bidirectional_iterator_tag;
	// other options exist, e.g., std::forward_iterator_tag
	using different_type = std::ptrdiff_t;
	using value_type = const T;
	using pointer = const T*;
	using reference = const T&;

	const_iterator(const DynamicArray& _da, const int& _i) :da(&_da), i(_i) {}
	const_iterator(const const_iterator& other) :da(&(other.da)), i(other.i) {}

	static int distance(const const_iterator& itr1, const const_iterator& itr2) { return abs(itr1.i - itr2.i); }

	const_iterator& operator=(const const_iterator& other) { da = other.da;			i = other.i;		return *this; }
	bool operator==(const const_iterator& other) const { return da == other.da && i == other.i; }
	bool operator!=(const const_iterator& other) const { return !(*this == other); }
	bool operator>(const const_iterator& other)const { return this->i > other.i; }
	bool operator<(const const_iterator& other)const { return this->i < other.i; }
	bool operator<=(const const_iterator& other)const { return this->i <= other.i; }
	bool operator>=(const const_iterator& other)const { return this->i >= other.i; }

	const T& operator*() { return da->arr[i]; }
	const T* operator->() { return &(da->arr[i]); }

	const_iterator& operator++() { ++i; return *this; }
	const_iterator operator++(int) { const_iterator temp(*this);		++i;		return temp; }
	const_iterator& operator--() { --i; return *this; }
	const_iterator operator--(int) { const_iterator temp(*this);		--i;		return temp; }
};

template <class T>
class DynamicArray<T>::reverse_iterator {
private:
	DynamicArray* da;
	int i;
public:
	using iterator_category = std::bidirectional_iterator_tag;
	// other options exist, e.g., std::forward_iterator_tag
	using different_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	reverse_iterator(DynamicArray& _da, const int& _i) :da(&_da), i(_i) {}
	reverse_iterator(const reverse_iterator& other) :da(other.da), i(other.i) {}

	static int distance(const reverse_iterator& itr1, const reverse_iterator& itr2) { return abs(itr1.i - itr2.i); }

	reverse_iterator& operator=(const reverse_iterator& other) { da = other.da;	i = other.i; return *this; }
	bool operator==(const reverse_iterator& other) const { return da == other.da && i == other.i; }
	bool operator!=(const reverse_iterator& other) const { return !(*this == other); }
	bool operator>(const reverse_iterator& other)const { return this->i < other.i; }
	bool operator<(const reverse_iterator& other)const { return this->i > other.i; }
	bool operator<=(const reverse_iterator& other)const { return this->i >= other.i; }
	bool operator>=(const reverse_iterator& other)const { return this->i <= other.i; }

	T& operator*() { return da->arr[i]; }
	T* operator->() { return &(da->arr[i]); }

	reverse_iterator& operator++() { --i; return *this; }
	reverse_iterator operator++(int) { reverse_iterator temp(*this); --i; return temp; }
	reverse_iterator& operator--() { ++i; return *this; }
	reverse_iterator operator--(int) { reverse_iterator temp(*this); ++i; return temp; }
};


// =================== DYNAMICARRAY METHODS
template <class T>
void DynamicArray<T>::resize() {
	int i;
	if (capacity == 0)
		capacity++;
	T* newArr = new T[capacity * 2];
	for (i = 0; i < logSize; i++)
		newArr[i] = arr[i];

	delete[] arr;
	arr = newArr;
	capacity *= 2;
}
template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
	if (this != &other) {
		logSize = other.logSize;
		capacity = other.capacity;
		delete[] arr;
		arr = new T[capacity];
		for (int i = 0; i < logSize; i++)
			arr[i] = other.arr[i];
	}
	return *this;
}
template <class T>
void DynamicArray<T>::push_back(const T& value) {
	if (logSize == capacity)
		resize();
	arr[logSize++] = value;
}
template <class T>
const typename DynamicArray<T>::iterator& DynamicArray<T>::insert(const typename iterator& pos, const T& val) {
	if (logSize == capacity)
		resize();

	iterator itrEnd = end();
	iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
	while (itrCurrent != pos)
	{
		*itrCurrent = *itrPrev;
		itrCurrent = itrPrev--;
	}

	iterator p = pos;
	*p = val;
	++logSize;
	return pos;
}
template <class T>
typename DynamicArray<T>::iterator DynamicArray<T>::erase(const typename iterator& iter) {
	iterator temp = iter;
	iterator iterCurrent = temp, iterNext = ++temp;
	while (iterNext != end()) {
		*iterCurrent = *iterNext;
		iterCurrent = iterNext++;
	}
	--logSize;
	return iter;
}
template <class T>
typename DynamicArray<T>::iterator DynamicArray<T>::erase(const typename iterator& first, const typename iterator& last) {
	iterator temp = last;
	iterator iterCurrent = first, iterNext = ++temp;

	while (iterCurrent <= last && iterNext != end()) {
		*iterCurrent = *iterNext;
		++iterCurrent;
		++iterNext;
	}
	logSize -= iterator::distance(first, last);
	return first;
}