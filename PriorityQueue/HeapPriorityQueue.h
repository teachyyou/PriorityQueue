#pragma once
#include<iostream>
#include<vector>
#include<string>

template<typename T, class _Container = std::vector<T>, class Compare = std::less<T>>
class HeapPriorityQueue
{
	_Container vector;
	size_t _size;
	Compare comparator = Compare();
public:
	HeapPriorityQueue() {
		_size = 0;
	}
	HeapPriorityQueue(std::initializer_list<T> lst)
	{
		_size = 0;
		for (const T& x : lst) {
			push(x);
		}
	}
	HeapPriorityQueue(const _Container& inputVector)
	{
		_size = inputVector.size();
		vector = inputVector;
		for (size_t i = (_size - 1) / 2; i > 0; --i) {
			heapify(i);
		}
		heapify(0);
		std::cout << _size << " tutti " << vector.size();
	}
	void push(const T& elem)
	{
		vector.push_back(elem);
		size_t i = _size;
		++_size;
		while (i > 0 && comparator(vector[i / 2], elem)) {
			std::swap(vector[i], vector[i / 2]);
			i = i / 2;
		}
	}

	void push(T&& elem)
	{
		vector.push_back(std::move(elem));
		size_t i = _size;
		++_size;
		while (i > 0 && comparator(vector[i / 2], vector[i])) {
			std::swap(vector[i], vector[i / 2]);
			i = i / 2;
		}
	}
	T top() const {
		return vector[0];
	}
	void pop()
	{
		if (_size > 0)
		{
			vector[0] = vector[vector.size() - 1];
			--_size;
			heapify(0);
			vector.pop_back();
		}
	}
	void print()
	{
		copy(vector.cbegin(), vector.cend(), std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	}
	size_t size() const {
		return _size;
	}
private:
	void heapify(size_t i)
	{
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
		size_t largest = i;
		if (left < _size && comparator(vector[largest], vector[left]))
			largest = left;
		if (right < _size && comparator(vector[largest], vector[right]))
			largest = right;
		if (largest != i)
		{
			std::swap(vector[i], vector[largest]);
			heapify(largest);
		}
		//std::cout << this->top() << std::endl;
	}
};