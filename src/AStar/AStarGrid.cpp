#include "AStarGrid.h"
#include "Node.h"

//Hard coded constants that determine node scores
// a^2 + b^2 = c^2
// 1 + 1 = sqrt(2) ~= 1.4
//Multiplying by 10 we approximate these weights 
const int32_t sWeight = 10;
const int32_t dWeight = 14;

AStarGrid::AStarGrid(const int32_t width, const int32_t height, const int32_t obstructions)
{
	gridWidth = width;
	gridHeight = height;
	obstructionCount = obstructions;

	GenerateGrid();
}

AStarGrid::~AStarGrid()
{
	CleanGrid();
}

void AStarGrid::CleanGrid()
{
	for (Node* n : grid)
	{
		delete n;
	}

	grid.clear();
}

void AStarGrid::GenerateGrid()
{
	CleanGrid();

	const int32_t gridSize = gridWidth * gridHeight;	
	grid.reserve(gridSize);

	std::vector<int32_t> availableNodes;
	availableNodes.reserve(gridSize);

	//Generate grid
	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++)
		{
			grid.push_back(new Node(j, i));
			availableNodes.push_back(j + (i * gridWidth));
		}
	}

	//Assign random obstructions
	for (int i = 0; i < obstructionCount; i++)
	{
		const int32_t size = availableNodes.size() - 1;
		const int32_t random = rand() % size;

		grid[availableNodes[random]]->SetType(NodeType::Block);
		availableNodes.erase(availableNodes.begin() + random);
	}

	//Assign two target points
	for (int i = 0; i < 2; i++)
	{
		const int32_t random = rand() % (availableNodes.size() - 1);
		grid[availableNodes[random]]->SetType(NodeType::Target);
		availableNodes.erase(availableNodes.begin() + random);

		if (i == 0) startIndex = GetIndexOfNode(grid[availableNodes[random]]);
		else endIndex = GetIndexOfNode(grid[availableNodes[random]]);
	}

	SetScores();
}

void AStarGrid::SetScores()
{
	Node* start = grid[startIndex];
	Node* end = grid[endIndex];

	for (Node* n : grid)
	{
		if (n->GetType() == NodeType::Empty)
		{
			n->gCost = GetDistanceBetweenNodes(n, start);
			n->hCost = GetDistanceBetweenNodes(n, end);
		}
	}
}

int32_t AStarGrid::GetIndexOfNode(Node* const n) const
{
	return (n->y * gridWidth) + n->x;
}

int32_t AStarGrid::GetDistanceBetweenNodes(Node* const a, Node* const b) const
{
	const int32_t x = std::abs(a->x - b->x);
	const int32_t y = std::abs(a->y - b->y);

	if (x > y) return (dWeight * y) + (sWeight * (x-y));
	else return (dWeight * x) + (sWeight * (y-x));
}

void AStarGrid::GetGridDimensions(int32_t& x, int32_t& y) const
{
	x = gridWidth;
	y = gridHeight;
}

void AStarGrid::GetTargetIndexes(int32_t& start, int32_t& end) const
{
	start = startIndex;
	end = endIndex;
}

void AStarGrid::GetNeighbors(Node* const n, std::vector<Node*>& outVector) const
{
	outVector.clear();

	int x = 0;
	int y = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			x = j + n->x;
			y = i + n->y;

			if (x < 0 || y < 0 || x > gridWidth - 1 || y > gridHeight - 1) continue; // dont go out of bounds
			if (j == 0 && i == 0) continue; // dont select ourselves

			const int index = (y * gridWidth) + x;
			if (grid[index]->GetType() == NodeType::Block) continue; //dont accept blocks

			outVector.push_back(grid[index]);
		}
	}
}