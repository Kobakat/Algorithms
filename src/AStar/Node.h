#pragma once
#include <stdint.h>

enum NodeType { Empty, Block, Target, Path };

class Node
{
public:
	Node() { }
	Node(const int32_t X, const int32_t Y, const int32_t Width, const int32_t Height);

	int32_t x;
	int32_t y;
	int32_t width;
	int32_t height;

	int32_t gCost;
	int32_t hCost;
	int32_t fCost() const { return gCost + hCost; }

	int32_t GetIndex() const { return (y * 10) + x; }
	NodeType GetType() const { return type; }
	
	void SetType(const NodeType Value);

private:
	NodeType type;
};