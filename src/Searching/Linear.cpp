#include <vector>
#include <iostream>

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

int main()
{
	std::vector<int> a = { 1, 2, 3, 4 ,5 };

	std::string found5 = LinearSearch(a, 5) ? "True" : "False";
	std::string didnotFind7 = LinearSearch(a, 7) ? "True" : "False";

	std::cout << found5 << std::endl;
	std::cout << didnotFind7 << std::endl;
}