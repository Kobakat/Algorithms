#include "Common.h"

template<typename T, class Predicate>
void InsertionSort(std::vector<T>& collection, const Predicate& predicate)
{
	//Any collection with less than 2 elements is already sorted
	if (collection.size() < 2)
	{
		return;
	}
	
	for (int i = 1; i < collection.size(); i++)
	{
		int key = i;
		int j = i - 1;

		//As long as our key value satisfies the predicate with the value before it, switch the two elements
		while(j >= 0 && predicate(collection[key], collection[j]))
		{
			Swap(collection[key], collection[j]);
			key--;
			j--;			
		}
	}
}

int main()
{
	std::vector<int> vec = { 5, 2, 3, 1, 0, 4 };

	InsertionSort(vec, LessThan<int>);
	PrintVectorToConsole(vec);

	return 0;
}