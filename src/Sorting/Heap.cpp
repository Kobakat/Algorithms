#include "Common.h"

template<typename T, class Predicate>
void Heapify(std::vector<T>& collection, const Predicate& predicate, int i)
{
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < collection.size() && predicate(collection[max], collection[l]))
    {
        max = l;
    }

    if (r < collection.size() && predicate(collection[max], collection[r]))
    {
        max = r;
    }


    if (max != i)
    {
        Swap(collection[i], collection[max]);
        Heapify(collection, predicate, max);
    }
}

template<typename T, class Predicate>
void HeapSort(std::vector<T>& collection, const Predicate& predicate)
{
	if (collection.size() < 2)
	{
		return;
	}

    for (int i = collection.size() / 2 - 1; i >= 0; i--)
    {
        Heapify(collection, predicate, i);
    }
        

    for (int i = collection.size() - 1; i > 0; i--) {
        Swap(collection[i], collection[0]);

        Heapify(collection, predicate, 0);
    }
}

int main()
{
    std::vector<int> vec = { 5, 2, 3, 1, 0, 4 };

    HeapSort(vec, LessThan<int>);
    PrintVectorToConsole(vec);

    return 0;
}
