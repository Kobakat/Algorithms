#pragma once

#include <vector>
#include <iostream>

template<typename T>
__forceinline bool LessThan(const T& a, const T& b)
{
	return a < b;
}

template<typename T>
__forceinline void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
void PrintVectorToConsole(const std::vector<T>& collection)
{
	for (int i = 0; i < collection.size(); i++)
	{
		std::cout << collection[i] << std::endl;
	}

	//std::endl;
}