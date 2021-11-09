#pragma once
#include <stdint.h>

enum NodeType { Empty, Block, Target, Start, Path, Open, Closed };

class Node
{
public:
	Node(const int32_t X, const int32_t Y);

	int32_t x;
	int32_t y;

	bool bDrawScores;

	int32_t gCost;
	int32_t hCost;
	inline int32_t fCost() const { return gCost + hCost; }

	NodeType GetType() const { return type; }
	void SetType(const NodeType Value);

	Node* root;
private:
	NodeType type;
};