#include <iostream>

int* SimpleBubbleSort(int* arr, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - i - 1; j++)
		{
			int current = *(arr + j);
			int next = *(arr + j + 1);

			if (current > next)
			{
				*(arr + j) = next;
				*(arr + j + 1) = current;
			}
		}
	}

	return arr;
}


int main()
{
	int a[5] = { 32, 5, 100, 94, 16 };

	std::cout << "Before sort: ";
	for (int i = 0; i < 5; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << "\n" << std::endl;

	SimpleBubbleSort(a, 5);

	std::cout << "After sort: ";
	for (int i = 0; i < 5; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << "\n" << std::endl;
	return 0;
}
