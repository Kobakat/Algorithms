# Data Structures

Simply put, a data structure is a way programmers can store, organize, and retrieve data. While implementations vary from language to language,
the core principles stay the same. Here I'll be comparing two pairs of common data structures and breaking down the pros and cons of each.

## Arrays vs Maps

An array is the most common and basic type of data structure. Arrays have a fixed size and provide a constant (O(1)) access times.
In C++ we can easily declare an array of strings and populate it with some values like so

```cpp
std::string arr[] = { "Jim", "Sally", "Suzy", "Robert", "John" };
```

To access any element in the array, all I need to do is provide the index of the array like so

```cpp
std::cout << arr[0] << std::endl;
```

Because array indexes are 0 based, this will print "Jim" to the screen.

Maps on the other hand are a more complex type of data structure that work by maintaining a dynamically sized collection of key-value pairs. Keys in a map
work similarly to an arrays index, except we can use any type and decide what the value should be rather than an integral expression.
For example, in C++ I can declare and use an unordered_map as follows

```cpp
std::unordered_map<int, std::string> map;

map[505] = "Jim";
map[123] = "Sally";
map[897] = "Suzy";
map[321] = "Robert";
map[534] = "John";
```

Here I'm defining an unordered map which uses the type of an integer as a key, and a string as a value. To look up a name all I need to do is provide the key

```cpp
std::cout << map[897] << std::endl;
```

This will print "Suzy" to the console because I've assigned that value to the key at 897. Maps, like arrays, provide constant access times. The main benefit of unordered_maps
are their potential search time complexity of O(1). Under the hood, unordered_maps are a hash table which use a hash function to place values into "buckets". An unordered_map
is really a collection of these buckets which themselves are a collection of hashes produced by the hash function. In some cases, the hash function used may turn a key into a 
pre-existing hash. This is known as a "collision". In the event every hash lives in the same bucket, the search time becomes O(n), which usually hints that your hash function
is pretty terrible.

## Stacks vs Queues

A stack is a data structure that follows the principle of LIFO (Last in, first out). This structure ensures that we only ever read data from the very top of the stack and provides
constant time complexity in operations such as access, addition, and removal.
In C++ I can add define a stack and populate it elements like so

```cpp
std::stack<int> stack;

for (int i = 0; i < 6; i++)
{
	stack.push(i * 5);
}
```

This will push the elements 0, 5, 10, 15, 20, and 25 onto the stack, with 25 being the top element. Stacks make it very easy to reverse the list, all we need to do is pop each element
off and add it to a new stack like so

```cpp
template<typename T>
std::stack<T> GetReverseStack(std::stack<T> original)
{
	std::stack<T> reversed;
	int size = original.size();

	for (int i = 0; i < size; i++)
	{
		reversed.push(original.top());
		original.pop();
	}

	return reversed;
}
```

Queues function the opposite way under the premise of FIFO (First in first out). While the top element of a stack is the most recently added element, the top element of a queue is the oldest.
Like stacks, Queues gurantee structure of the data they maintaing by ensuring contant addition, removal, and peek times. Here we can see what a queue looks like before and after its top element
has been popped off

```cpp
template<typename T>
void PrintQueue(std::queue<T> queue)
{
	int size = queue.size();

	for (int i = 0; i < size; i++)
	{
		std::cout << queue.front() << " ";
		queue.pop();
	}

	std::cout << std::endl;
}

int main()
{
	std::queue<std::string> queue;

	queue.push("Jim");
	queue.push("Suzy");
	queue.push("Paul");
	queue.push("Andrew");
	queue.push("Sally");
	queue.push("John");

	PrintQueue(queue);

	queue.pop();

	PrintQueue(queue);

	return 0;
}
```

This will first display "Jim Suzy Paul Andrew Sally John" and then "Suzy Paul Andrew Sally John". Because "Jim" was the top element, it is removed when we call "pop" 
