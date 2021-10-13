#include "AStarSolver.h"
#include "AStarGrid.h"
#include "Node.h"

void AStarSolver::Solve(AStarGrid* grid)
{
	
}

void AStarSolver::SetPath() const
{
	Node* current = endNode;
	while (current != startNode)
	{
		current->SetType(NodeType::Path);
		if (current->root == nullptr)
		{
			return;
		}
		current = current->root;
	}
}