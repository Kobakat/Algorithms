#include "Common.h"

template<typename T, class Predicate>
void Merge(std::vector<T>& collection, const Predicate& predicate, int l, int m, int r)
{
    //Compute number of elements each sub collection will contain
    int lSize = (m - l) + 1;
    int rSize = (r - m);

    //Reserve appropriate amount of space in each sub collection
    std::vector<T> subL, subR;
    subL.reserve(lSize);
    subR.reserve(rSize);

    //Copy every element from the main collection and place it into 
    for (int i = 0; i < lSize; i++)
    {
        subL[i] = collection[l + i];
    }

    for (int j = 0; j < rSize; j++)
    {
        subR[j] = collection[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < lSize && j < rSize) 
    {
        if (predicate(subL[i], subR[j])) 
        {
            collection[k] = subL[i];
            i++;
        }
        else 
        {
            collection[k] = subR[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < lSize) 
    {
        collection[k] = subL[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < rSize) 
    {
        collection[k] = subR[j];
        j++;
        k++;
    }
}

template<typename T, class Predicate>
void Split(std::vector<T>& collection, const Predicate& predicate, int l, int r)
{
    //As long as our collection size is larger than two we will continue to split it up
    if (l < r)
    {
        int m = (l + r) / 2;

        //Recursively the collection into smaller and smaller halves
        Split(collection, predicate, l, m);
        Split(collection, predicate, m + 1, r);

        //Because function calls operate as a stack we can now merge each sub collection that we created with Split
        Merge(collection, predicate, l, m, r);
    }
}

template<typename T, class Predicate>
void MergeSort(std::vector<T>& collection, const Predicate& predicate)
{
    if (collection.size() < 2)
    {
        return;
    }

    Split(collection, predicate, 0, collection.size() - 1);
}

int main()
{
    std::vector<int> vec = { 5, 2, 3, 1, 0, 4 };

    MergeSort(vec, LessThan<int>);
    PrintVectorToConsole(vec);

    return 0;
}