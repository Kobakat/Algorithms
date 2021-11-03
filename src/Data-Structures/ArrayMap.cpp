#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
	std::string arr[] = { "Jim", "Sally", "Suzy", "Robert", "John" };
	std::unordered_map<int, std::string> map;

	map[505] = "Jim";
	map[123] = "Sally";
	map[897] = "Suzy";
	map[321] = "Robert";
	map[534] = "John";

	std::cout << arr[0] << std::endl;
	std::cout << map[897] << std::endl;

	return 0;
}