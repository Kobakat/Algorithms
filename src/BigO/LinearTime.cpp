#include <iostream>

bool ArrayContainsNumber(int* arr, int length, int target)
{
	for (int i = 0; i < length; i++)
	{
		int val = *(arr + i);

		if (val == target)
		{
			return true;
		}
	}

	return false;
}

int main()
{
	int a[5] = { 1, 2, 3, 4, 5 };
	int b[10] = { 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

	bool aSearch = ArrayContainsNumber(a, 5, 16);
	bool bSearch = ArrayContainsNumber(b, 10, 11);

	std::cout << "Array a contains target: " << aSearch << "\n" << std::endl;
	std::cout << "Array b contains target: " << bSearch << "\n" << std::endl;

	return 0;
}