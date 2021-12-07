# Searching

Another one of the most common uses of algorithms is finding a desired element in an exisiting collection. There are several common approaches
to this. I will be going over three of the most common: Linear, Binary, and Interpolation. Its important to note that search algorithms can have
many different return values such as a bool (does the target element exist?), an int (the index of the element in the collection), or a pointer
(the actual object exisiting at the target). In these examples I'm simply going to return a boolean stating whether or not the element is contained
in the provided collection.

## Linear

Linear search is about as basic as a search gets. All we do is loop through the collection and compare every value to our target element and return
true if we find one. Linear search benefits from being super easy and intuitive to implement and can be performed on any sorted or randomly distriuted collection.

### Time complexities

**Worst Case:** O(N) - Worst case scenario occurs when the element we are looking for is the last in the collection
**Best Case:** O(1) - Best case scenario occurs when the element we are looking for is the first in the collection
**Average Case:** O(N/2) - On average the target element is found in the middle of the collection

```cpp
template<typename T>
bool LinearSearch(const std::vector<T>& Container, T target)
{
	//Simply loop over every element in our container and check if the value is found
	for (T element : Container)
	{
		if (element == object) return true;
	}

	//If we haven't found the target yet, this container does not have the target
	return false;
}
```

## Binary

Binary search works by continually cutting the search length into halves until the element is found or none remain.
This only works on the assumption that the provided collection has already been sorted. If you haven't seen my
page for sorting algorithms, you can check that out $[**here**](link). Additionally, in order to maintain our wonderful
portable template functions, we need to provide a predicate function that defines HOW the collection is sorted. In this 
example case I will be providing a sorted vector of integers from smallest to largest.

**Worst Case:** O(Log(N)) - Worst case scenario occurs when the element we are looking for requires us to split a floored log(n) times
**Best Case:** O(1) - Best case scenario occurs when the element we are looking for is the first middle value in the collection
**Average Case:** O(Log(N)) - The calculus behind this proof is a bit out of scope for this readme, but there are many proofs you can look into online

```cpp
template<typename T, class Predicate>
bool BinarySearch(const std::vector<T>& Container, T target, const Predicate& SortingPredicate)
{
	//Create two pointers that denote the respective start and end of our current search 
	int l = 0;
	int r = Container.size() - 1;

	//Because this collection is sorted, we can very quickly use the predicate to determine if the target value provided
	//Exists outside the container bounds

	//Break early if the target value would fall behind the left most sorted point
	if(SortingPredicate(target, Container[l])) return false;

	//Break early if the target vlaue would fall beyond the right most sorted point
	if(SortingPredicate(Container[r], target)) return false;

	while (r >= l)
	{
		//Get the middle index of our current search width
		int mid = (l + r) / 2;

		if (Container[mid] == target)
		{
			return true;
		}

		bool predicateResult = SortingPredicate(Container[mid], Container[l]);

		//If our predicate succeeded we cut the collection in half and only evaluate the left half
		if (predicateResult)
		{
			r = mid - 1;
		}

		//The predicate failed, so instead we evaluate the right half after cutting the collection in half
		else
		{
			l = mid + 1;
		}
	}

	return false;
}
```

## Interpolation

Interpolation search is actually just an optimization of binary search for collections that follow two rules. First, 
the elements in the collection need to be numeric because we will be determining a "probe" point using a mathematical
formula. Second, the optimization only works when there is a uniform distribution of values in the collection. Binary
search simply splits the collection into twos every time right down the middle. Interpolation sort on the other hand
tries to find a splitting point close the the target value by using a special formula.


**Worst Case:** O(N) - Worst case scenario occurs when the distribution is completely random and we have to search every element
**Best Case:** O(1) - The best case scenario occurs when the element we are looking for is the first middle value in the collection
**Average Case:** O(Log(Log(N))) - The average case occurs when the elements in our array are uniformly distributed

```cpp
template<typename T, class Predicate>
bool BinarySearch(const std::vector<T>& Container, T target, const Predicate& SortingPredicate)
{
	//Create two pointers that denote the respective start and end of our current search 
	int l = 0;
	int r = Container.size() - 1;

	//Because this collection is sorted, we can very quickly use the predicate to determine if the target value provided
	//Exists outside the container bounds

	//Break early if the target value would fall behind the left most sorted point
	if(SortingPredicate(target, Container[l])) return false;

	//Break early if the target vlaue would fall beyond the right most sorted point
	if(SortingPredicate(Container[r], target)) return false;

	while (r >= l)
	{
		//Get the middle index of our current search width
		int mid = (l + r) / 2;

		if (Container[mid] == target)
		{
			return true;
		}

		bool predicateResult = SortingPredicate(Container[mid], Container[l]);

		//If our predicate succeeded we cut the collection in half and only evaluate the left half
		if (predicateResult)
		{
			r = mid - 1;
		}

		//The predicate failed, so instead we evaluate the right half after cutting the collection in half
		else
		{
			l = mid + 1;
		}
	}

	return false;
}
```

