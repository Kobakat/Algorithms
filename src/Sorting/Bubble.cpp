#include "Common.h"

template<typename T, class Predicate>
void BubbleSort(std::vector<T>& collection, const Predicate& predicate)
{
	if (collection.size() < 2)
	{
		return;
	}

	for (int i = 0; i < collection.size() - 1; i++)
	{
		for (int j = i + 1; j < collection.size(); j++)
		{
			if (predicate(collection[j], collection[i]))
			{
				Swap(collection[j], collection[i]);
			}
		}
	}
}

int main()
{
	std::vector<int> vec = { 5, 2, 3, 1, 0, 4 };

	BubbleSort(vec, LessThan<int>);
	PrintVectorToConsole(vec);

	return 0;
}