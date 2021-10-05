#include "Node.h"

Node::Node(const int32_t X, const int32_t Y, const int32_t Width, const int32_t Height)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;

	gCost = 0;
	hCost = 0;

	type = NodeType::Empty;
}

void Node::SetType(const NodeType Value)
{
	type = Value;
}