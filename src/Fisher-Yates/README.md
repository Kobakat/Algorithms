# What is the Fisher-Yates shuffle?

The Fisher-Yates shuffle is an algorithm that, given a collection of items, generates an unbiased random permutation in O(N) time.
This means that if we pass a collection of elements into a shuffle function, we will be given back a collection that has had all
of its elements swapped around randomly.

## Implementation

To do this, we start by selecting a random element in our selection. Then, we swap that element with our last available element in our collection.
Lastly, we reduce the size of our random selection by one so we can no longer select the last element. We rinse and repeat until
we have gone over every element.

```cpp
template <typename T, size_t size>
void Shuffle(T(&array)[size])
{
	for (int i = size - 1; i > 0; i--)
	{
		const int random = rand() % i;
		Swap(array[i], array[random]);
	}
}
```

With this implementation, we take advantage of C++'s template functions to let us give any array type to a singular function. 
Additionally, swapping two values by reference is a very common thing in algorithms so I've created a handy swap function. I've marked
this function as inline which essentially tells the compiler to replace every function call with the raw implementation. This is
a nice optimization that reduces the overhead from calling the function.

```cpp
template <typename T>
inline void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
```
