#include "Common.h"

template<typename T, class Predicate>
int Partition(std::vector<T>& collection, const Predicate& predicate, int l, int r)
{
    T pivot = collection[r];

    int i = l - 1;

    for (int j = l; j <= r - 1; j++)
    {
        if (predicate(collection[j], pivot))
        {
            i++;
            Swap(collection[i], collection[j]);
        }
    }

    Swap(collection[i + 1], collection[r]);
    return i + 1;
}

template<typename T, class Predicate>
void Sort(std::vector<T>& collection, const Predicate& predicate, int l, int r)
{
    if (l < r)
    {
        int index = Partition(collection, predicate, l, r);

        Sort(collection, predicate, l, index - 1);
        Sort(collection, predicate, index + 1, r);
    }
}

template<typename T, class Predicate>
void QuickSort(std::vector<T>& collection, const Predicate& predicate)
{
    if (collection.size() < 2)
    {
        return;
    }

    Sort(collection, predicate, 0, collection.size() - 1);
}

int main()
{
    std::vector<int> vec = { 5, 2, 3, 1, 0, 4 };

    QuickSort(vec, LessThan<int>);
    PrintVectorToConsole(vec);

    return 0;
}