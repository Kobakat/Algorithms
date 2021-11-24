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
Doing this is effective and guranteed to work, but is generally considered a naive approach 

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
Best case - O(n^2)
Worst case - O(n^2)

**Pros**
- Easy implementation
- Can run faster than more complex sorts on smaller data sets
- In place sorting. Requires no extra memory allocation

**Cons**
- Has to check every single element against every other element regardless if its already sorted.
- Very bad performance on large data sets

## Insertion Sort

Insertion sort is like bubble sorts more successful sibling. It works very similarly but avoids the need to compare very element to every other element.
It does so by 