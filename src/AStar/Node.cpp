#include "Node.h"

Node::Node(const int32_t X, const int32_t Y)
{
	x = X;
	y = Y;

	gCost = 0;
	hCost = 0;

	type = NodeType::Empty;
	root = nullptr;
}

void Node::SetType(const NodeType Value)
{
	type = Value;
}