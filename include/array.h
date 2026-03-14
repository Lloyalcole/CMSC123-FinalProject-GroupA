#pragma once

#include <cassert>
#include <cstddef>

template <typename T>
struct array
{
	array(size_t n)
	{
		a = new T[n];
		length = n;
	}

	~array()
	{
		delete[] a;
	}

	T& operator[](size_t i)
	{
		assert(i < length);
		return a[i];
	}

	array<T>& operator=(array<T>& other)
	{
		if (a != nullptr)
		{
			delete[] a;
		}
		a = other.a;
		other.a = nullptr;
		length = other.length;
		other.length = 0;
		return *this;
	}

	size_t length;
	T* a;
};

