#include "Common.h"

template<typename T, class Predicate>
void SelectionSort(std::vector<T>& collection, const Predicate& predicate)
{
	//Any collection with less than 2 elements is already sorted
	if (collection.size() < 2)
	{
		return;
	}
	
	for (int i = 0; i < collection.size() - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < collection.size(); j++)
		{
			if (predicate(collection[j], collection[min]))
			{
				min = j;
			}		
		}
			
		Swap(collection[min], collection[i]);
	}
}

int main()
{
	std::vector<int> vec = { 5, 2, 3, 1, 0, 4 };

	SelectionSort(vec, LessThan<int>);
	PrintVectorToConsole(vec);

	return 0;
}