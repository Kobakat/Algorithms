#include "Sort.h"

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

int main()
{
	std::vector<int> a = { 1, 3, 6, 2, 5, 8, 11, 13, 55 };
	QuickSort(a, LessThan<int>);

	std::string found13 = BinarySearch(a, 13, LessThan<int>) ? "True" : "False";
	std::string didNotFind34 = BinarySearch(a, 34, LessThan<int>) ? "True" : "False";
	
	std::cout << found13 << std::endl;
	std::cout << didNotFind34 << std::endl;
}