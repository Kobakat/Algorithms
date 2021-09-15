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