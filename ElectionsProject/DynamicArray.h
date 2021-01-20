#pragma once
#include <iostream>
#include <cmath>
template <class T>
class DynamicArray
{
private:
	T* arr;
	int logSize, capacity;
	void resize() {
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
public:
	DynamicArray() :arr(nullptr), logSize(0), capacity(0) {}
	DynamicArray(const int& size) :arr(new T[size]), logSize(0), capacity(size) {}
	DynamicArray(const DynamicArray& other) :arr(nullptr) { *this = other; }
	~DynamicArray() { delete[] arr; }

	DynamicArray& operator=(const DynamicArray& other) {
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
	T& operator[](const int& idx)const { return arr[idx]; }
	bool operator==(const DynamicArray& other) { return arr == other.arr; }
	bool operator!=(const DynamicArray& other) { return arr != other.arr; }

	const T& front() const { return arr[0]; }
	const T& back() const { return arr[logSize-1]; }

	const int& getLogSize() const { return logSize; }
	const int& getCapacity() const { return capacity; }
	bool isEmpty() const { return logSize == 0; }
	void makeEmpty() { logSize = 0; }
	
	void push_back(const T& value) {
		if (logSize == capacity)
			resize();
		arr[logSize++] = value;
	}

	class iterator {
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

		iterator& operator=(const iterator& other){
			if (*this != other) {
				da = other.da;
				i = other.i;
			}
			return *this;
		}
		bool operator==(const iterator& other) const { return da == other.da && i == other.i; }
		bool operator!=(const iterator& other) const { return !(*this == other); }
		bool operator>(const iterator& other)const { return this->i > other.i; }
		bool operator<(const iterator& other)const { return this->i < other.i; }
		bool operator<=(const iterator& other)const { return this->i <= other.i; }
		bool operator>=(const iterator& other)const { return this->i >= other.i; }

		T& operator*() { return da->arr[i]; }
		T* operator->() { return &(da->arr[i]); }
			
		iterator& operator++() { ++i; return *this; }
		iterator operator++(int) {
			iterator temp(*this);
			++i;
			return temp;
		}
		iterator& operator--() { --i; return *this; }
		iterator operator--(int){
			iterator temp(*this);
			--i;
			return temp;
		}
	};
	class const_iterator {
	private:
		const DynamicArray* da;
		int i;
	public:
		using const_iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		const_iterator(const DynamicArray& _da, const int& _i) :da(&_da), i(_i) {}
		const_iterator(const const_iterator& other) :da(&(other.da)), i(other.i) {}

		static int distance(const const_iterator& itr1, const const_iterator& itr2) { return abs(itr1.i - itr2.i); }

		const_iterator& operator=(const const_iterator& other) {
			if (*this != other) {
				da = other.da;
				i = other.i;
			}
			return *this;
		}
		bool operator==(const const_iterator& other) const { return da == other.da && i == other.i; }
		bool operator!=(const const_iterator& other) const { return !(*this == other); }
		bool operator>(const const_iterator& other)const { return this->i > other.i; }
		bool operator<(const const_iterator& other)const { return this->i < other.i; }
		bool operator<=(const const_iterator& other)const { return this->i <= other.i; }
		bool operator>=(const const_iterator& other)const { return this->i >= other.i; }

		const T& operator*() { return da->arr[i]; }
		const T* operator->() { return &(da->arr[i]); }

		const_iterator& operator++() { ++i; return *this; }
		const_iterator operator++(int) {
			const_iterator temp(*this);
			++i;
			return temp;
		}
		const_iterator& operator--() { --i; return *this; }
		const_iterator operator--(int) {
			const_iterator temp(*this);
			--i;
			return temp;
		}
	};

	const iterator& insert(const iterator& pos, const T& val) {
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
	iterator erase(const iterator& iter) {
		iterator temp = iter;
		iterator iterCurrent = temp, iterNext = ++temp;
		while (iterNext != end()) {
			*iterCurrent = *iterNext;
			iterCurrent = iterNext++;
		}
		--logSize;
		return iter;
	}
	iterator erase(const iterator& first, const iterator& last) {
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

	const_iterator begin() const { return const_iterator(*this, 0); }
	const_iterator end() const { return const_iterator(*this, logSize); }

	iterator begin() { return iterator(*this, 0); }
	iterator end() { return iterator(*this, logSize); }

	// A utility function to swap two elements  
	void swap(T& a, T& b){
		T t = a;
		a = b;
		b = t;
	}

	int partition(const int& low, const int& high)
	{
		auto pivot = arr[high]; // pivot  
		int i = (low - 1); // Index of smaller element  

		for (int j = low; j <= high - 1; j++)
		{
			// If current element is smaller than the pivot  
			if (arr[j] < pivot)
			{
				i++; // increment index of smaller element  
				//Dar Raviv is the love of my life I love Tal Lev.. does everybody know that? Answer me my friends!
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[high]);
		return (i + 1);
	}

	void quickSort(const int& low, const int& high)
	{
		if (low < high)
		{
			/* pi is partitioning index, arr[p] is now
			at right place */
			int pi = partition(low, high);

			// Separately sort elements before  
			// partition and after partition  
			quickSort(low, pi - 1);
			quickSort(pi + 1, high);
		}
	}

};
