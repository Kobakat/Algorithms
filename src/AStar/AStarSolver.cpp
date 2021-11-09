#include "AStarSolver.h"
#include "AStarGrid.h"
#include "Node.h"

bool AStarSolver::Solve(AStarGrid* grid)
{
	//Just some set up
	int32_t start = 0;
	int32_t end = 0;
	grid->GetTargetIndexes(start, end);

	startNode = grid->grid[start];
	endNode = grid->grid[end];

	open.clear();
	closed.clear();
	open.emplace_back(startNode);

	//If our open vector is empty, no path exists
	while (open.size() > 0)
	{
		Node* guess = open[0];

		//Check every other open node for the lowest cost
		for (int i = 1; i < open.size(); i++)
		{
			//If the node's fcost is lower, thats our new guess. If the fcost is equal, we choose whichever has a lower hcost
			if (open[i]->fCost() < guess->fCost() || 
				(open[i]->fCost() == guess->fCost() && open[i]->hCost < guess->hCost))
			{
				guess = open[i];
			}
		}

		//We found the target node, we've finished
		if (guess == endNode)
		{
			startNode->SetType(NodeType::Start);
			endNode->SetType(NodeType::Target);
			return true;
		}

		//Close the guess
		open.erase(std::remove(open.begin(), open.end(), guess), open.end());
		closed.emplace_back(guess);
		guess->SetType(NodeType::Closed);

		

		//Grab all the available neighbor nodes
		std::vector<Node*> neighbors;
		grid->GetNeighbors(guess, neighbors);

		for (Node* n : neighbors)
		{
			//Node is in closed list already, skip it
			if (std::find(closed.begin(), closed.end(), n) != closed.end())
			{
				continue;
			}

			const bool bIsNotInOpen = !(std::find(open.begin(), open.end(), n) != open.end());
			const int32_t distance = guess->gCost + grid->GetDistanceBetweenNodes(guess, n);

			//Node is not in the open list, initialize costs and add it to the list
			if (distance < n->gCost || bIsNotInOpen)
			{
				n->gCost = distance;
				n->hCost = grid->GetDistanceBetweenNodes(n, endNode);
				n->root = guess;

				if (bIsNotInOpen)
				{
					open.emplace_back(n);
					n->SetType(NodeType::Open);
				}			
			}			
		}
	}

	//No path found
	return false;
}

void AStarSolver::SetPath() const
{
	Node* current = endNode->root;
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

void AStarSolver::ShowScores(const bool bValue) const
{
	for (Node* n : open)
	{
		n->bDrawScores = bValue;
	}

	for (Node* n : closed)
	{
		n->bDrawScores = bValue;
	}
}