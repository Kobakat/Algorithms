#pragma once
#include <vector>

class AStarGrid;
class Node;

class AStarSolver 
{
public:
	void Solve(AStarGrid* grid);
	void SetPath() const;

	std::vector<Node*> open;
	std::vector<Node*> closed;

	Node* startNode;
	Node* endNode;
};