#include <iostream>

template <typename T>
inline void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template <typename T, size_t size>
void Shuffle(T(&array)[size])
{
	for (int i = size - 1; i > 0; i--)
	{
		const int random = rand() % i;
		Swap(array[i], array[random]);
	}
}

template <typename T, size_t size>
void print(T(&array)[size])
{
	for (int i = 0; i < size; i++)
	{
		std::cout << array[i] << std::endl;
	}
}

int main()
{
	srand(time(nullptr));

	int intArr[] = { 5, 2, 3, 14, 32, 65 };
	Shuffle(intArr);

	char charArr[] = { 'a', 'b', 'c', 'd', 'e' };
	Shuffle(charArr);

	print(intArr);
	std::cout << '\n' << std::endl;
	print(charArr);

	print(charArr);
	return 0;
}