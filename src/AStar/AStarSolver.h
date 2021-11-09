#pragma once
#include <vector>

class AStarGrid;
class Node;

class AStarSolver 
{
public:

	/** Solves a path. Returns true if a path was successfully found*/
	bool Solve(AStarGrid* grid);

	void SetPath() const;
	void ShowScores(const bool bValue) const;

	std::vector<Node*> open;
	std::vector<Node*> closed;

	Node* startNode;
	Node* endNode;
};