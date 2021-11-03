#include <iostream>
#include <string>
#include <stack>
#include <queue>

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

template<typename T>
void PrintStack(std::stack<T> stack)
{
	int size = stack.size();

	for (int i = 0; i < size; i++)
	{
		std::cout << stack.top() << " ";
		stack.pop();
	}

	std::cout << std::endl;
}

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
	//Stack
	std::stack<int> originalStack;

	for (int i = 0; i < 6; i++)
	{
		originalStack.push(i * 5);
	}

	PrintStack(originalStack);
	std::stack<int> reversedStack = GetReverseStack(originalStack);
	PrintStack(reversedStack);

	std::cout << "\n" << std::endl;

	//Queue
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