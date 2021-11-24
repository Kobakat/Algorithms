# Sorting

A very common usage of algorithms is to use them to sort a collection of data. For example, you may have a list of names that you want to re-arrange into alphabetical order.
This may be easy to do by hand for small data sets, but if you had a million names to sort using computers is way faster! There are many different wants to sort a collection
of objects. I'll be going over 6 of the most common and describe their pros and cons. 

### Implementation details

These example functions will only sort C++ standard vector containers, but do so in a templated way. This will let us sort any type of object as long as we provide a predicate 
function that determines how elements are to be sorted. To keep everything consistent, I'm just going to be sorting integers with a basic predicate that sorts by value. This will
result in any collection we pass into the sort function to be ordered from smallest to largest 

## Bubble Sort

Bubble sort is about as simple as sorting algorithms get. Essentially all it does it compare each element in the collection to every other element.
Doing this is effective and guranteed to work, but is generally considered a naive approach due to the constant time complexity of O(n<sup>2</sup>).

```cpp
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
```

**Time Complexity**

**Best case** O(n<sup>2</sup>) - Note: this implementation can be slightly altered to yield O(n) best case complexity but for the sake of example this optimization is not present.

**Worst case** O(n<sup>2</sup>)

**Pros**
- Easy implementation
- Can run faster than more complex sorts on smaller data sets
- In place sorting. Requires no extra memory allocation

**Cons**
- Has to check every single element against every other element regardless if its already sorted.
- Very bad performance on large data sets

## Insertion Sort

Insertion sort is like bubble sort's more successful sibling. It works very similarly but avoids the need to compare very element to every other element.
It does so by comparing an element to the element before it, and only switches place if the predicate is successful. If it is successful, keep checking until
the predicate fails or we reach the beginning of the list. After that we can move on to the next element.

```cpp
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
```

**Time Complexity**

**Best case** O(n) - The list has already been sorted

**Worst case** O(n<sup>2</sup>) - The list is completely backwards

**Pros**
- Easy implementation
- Can run faster than more complex sorts on smaller data sets
- In place sorting. Requires no extra memory allocation
- Decently fast on collections that are fully or almost entirely sorted

**Cons**
- Large variance in performance based on provided set
- Very bad performance on large data sets

## Selection Sort

Selection sort works by finding the smallest (or in the case of the templated predicate, most successful) value in the collection. It then swaps that element with the next value of the current loop iteration.

```cpp
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
```

**Time Complexity**

**Best case** O(n) - The list has already been sorted

**Worst case** O(n<sup>2</sup>) - The list is completely backwards

**Pros**
- Easy implementation
- Can run faster than more complex sorts on smaller data sets
- In place sorting. Requires no extra memory allocation
- Decently fast on collections that are fully or almost entirely sorted

**Cons**
- Large variance in performance based on provided set
- Very bad performance on large data sets

## Heap Sort

Heap sort works similarily to selection sort but utilizies a priority queue. To do this, we first take our collection and convert it into a max heap. This a representation of the collection as a binary tree where the least successful predicate is at the top. We use this heap to create the queue.

```cpp
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
        

    for (int i = collection.size() - 1; i > 0; i--) 
    {
        Swap(collection[i], collection[0]);
        Heapify(collection, predicate, 0);
    }
}
```

**Time Complexity**

Because we are recursively splitting each set into a tree we can readily derive log(n) complexity. However, we also have to consider that as the size of our set grows, so to does the execution time. 

**Best case** O(nlog(n))

**Worst case** O(nlog(n))

**Pros**
- Runs well on large data sets
- In place sorting. Requires no extra memory allocation

**Cons**
- Unstable sorting. Relative order of equal elements may not be maintained.
- Always swaps every element even in a completely sorted collection which lowers speed compared to other divide and conquer sorting algorithms

## Merge Sort

Merge sort is a divide and conquer strategy. It works by taking the initial collection and splitting it into smaller and smaller problems. It then solves the smaller problems and recombines them create the sorted collection.

```cpp
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
```

**Time Complexity**

Because we are recursively dividing the problem we can derive O(log(n)) complexity. However, we also have to consider that as the size of our set grows, so to does the execution time. 

**Best case** O(nlog(n))

**Worst case** O(nlog(n))

**Pros**
- Runs well on large data sets
- Runs faster than heap sort

**Cons**
- Requires O(n) extra memory allocation for the copied collections

## Quick Sort

Quick sort is another type of divide and conquer strategy. It works very similar to merge sort, but requires no extra memory allocation and almost always runs faster than heap and merge sort. It does this by selecting a pivot element and sorting every element based on the predicate on either side of the pivot. Quick sort is so efficent because it only swaps when it needs to but in rare cases can perform poorly on already sorted sets.

```cpp
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
```

**Best case** O(nlog(n))

**Worst case** O(n<sup>2</sup>) - Occurs when the first element is selected when the collection is already sorted. Provided a good pivot is selected this will not occur.
	
**Pros**
- Runs well on large data sets
- Runs faster than heap sort and merge sort

**Cons**
- Edge cases can degrade performance drastically
