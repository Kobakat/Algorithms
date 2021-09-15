# So what is Big O?

Big O notation is often used to describe the mathematical efficency of a computer algorithm in regards to time and space. Another way to look at is how the execution time of the software scale in regards to the input. Algorithms can achieve desired results in a variety of ways, but we should always favor algorithms that consume less memory and take less time to perform.

## Some examples

### Constant Time - O(1)
Constant time is used to describe a function that takes a fixed amount of time to execute regardless of input. For example...

```cpp
#include <iostream>

bool CompareEquality(char a, char b)
{
	return a == b;
}

int main()
{
	char a = 'g';
	char b = 'g';
	char c = 'k';

	bool ab = CompareEquality(a, b);
	bool bc = CompareEquality(b, c);

	std::cout << a << " and " << b << " are equal: " << ab << "\n" << std::endl;
	std::cout << b << " and " << c << " are equal: " << bc << "\n" << std::endl;

	return 0;
}
```
The simple CompareEquality function simply returns whether or not chars are equivalent. Since chars always have 1 byte, any input I pass in will always evaluate in the same amount of time.

### Linear Time - O(n)
Linear time describes a function whos execution time scales with the size of the input. For example...

```cpp
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
```
The ArrayContainsNumber function takes in an array of a given length and interates through it until it searches every value or finds an index with the target value. If we pass an array with 500 values, we can expect it to take half as long to search to the end compared to an input of an array with 1000 values. Since the time is directly porportional to the input, we define this as Linear time.

### Quadratic Time - O(n^2)
Similarly to linear time, Quadratic time expects to increase by the square of its input. For Example...

```cpp
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
```
The SimpleBubbleSort function takes in an array and performs an entire pass of the array for each element. If we have 5 elements, we need to pass 5 times for each of those 5. This gives us 25 iterations. If we increase the array size to 20, we have to pass 20 times for each of those 20. This gives us 400 iterations. Because the iteration is proportional to the square of the input, we define it as Quadratic time complexity.
