#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include "algorithm"

template<typename T, class _Container = std::vector<T>, class Compare = std::less<T>>
class PriorityQueue
{
	_Container vector;
	size_t _size;
	Compare comparator = Compare();
public:
	PriorityQueue() {
		_size = 0;
	}
	PriorityQueue(std::initializer_list<T> lst)
	{
		_size = 0;
		for (T x : lst) {
			push(x);
		}
	}
	void push(T& elem)
	{
		push(std::move(elem));
	}
	void push(T&& elem)
	{
		vector.insert(upper_bound(vector.begin(), vector.end(), elem, comparator), std::move(elem));
		_size++;
	}
	T top() const {
		return vector.front();
	}
	void pop()
	{
		if (_size > 0) {
			vector.pop_back();
			_size--;
		}

	}
	void print()
	{
		std::copy(vector.cbegin(), vector.cend(), std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	}
	PriorityQueue merge(PriorityQueue<T>& q) const
	{
		PriorityQueue newQueue = new PriorityQueue();
		for (T x : vector) {
			push(x);
		}
		for (T x : q.vector) {
			push(x);
		}
	}
	size_t size() const {
		return _size;
	}
};