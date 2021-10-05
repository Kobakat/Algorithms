#include "AStar.h"

//tired of typing olc::
const olc::Pixel white = olc::Pixel(olc::WHITE);
const olc::Pixel black = olc::Pixel(olc::BLACK);
const olc::Pixel green = olc::Pixel(olc::GREEN);
const olc::Pixel blue = olc::Pixel(olc::BLUE);

AStar::AStar()
{
	sAppName = "A* Pathfinding"; 
	gridLength = 10;
	selectedNode = 0;
}

bool AStar::OnUserCreate()
{
	GenerateGrid();
	return true;
}

bool AStar::OnUserUpdate(float fDeltaTime)
{
	if (GetKey(olc::Key::G).bPressed)
	{
		GenerateGrid();
	}

	for (Node n : grid)
	{
		DrawNode(n);
	}

	HandleMovement();

	return true;
}

void AStar::GenerateGrid()
{
	const int32_t sideLength = 80;
	const int32_t obstructions = 20;

	const int32_t gridSize = gridLength * gridLength;

	grid.clear();
	grid.reserve(gridSize);

	std::vector<int32_t> availableNodes;
	availableNodes.reserve(gridSize);

	srand(time(NULL));

	//Generate grid
	for (int i = 0; i < gridLength; i++)
	{
		for (int j = 0; j < gridLength; j++)
		{
			grid.push_back(Node(j, i, sideLength, sideLength));
			availableNodes.push_back(j+(i*10));
		}
	}

	//Assign random obstructions
	for (int i = 0; i < obstructions; i++)
	{		
		const int32_t size = availableNodes.size() - 1;
		const int32_t random = rand() % size;
	
		grid[availableNodes[random]].SetType(NodeType::Block);
		availableNodes.erase(availableNodes.begin() + random);
	}

	//Assign a random starting point and add it to the open node list
	int32_t random = rand() % (availableNodes.size() - 1);
	const int32_t startIndex = availableNodes[random];
	grid[startIndex].SetType(NodeType::Target);
	availableNodes.erase(availableNodes.begin() + random);
	
	//Assign a random end point and mark its index as the target
	random = rand() % (availableNodes.size() - 1);
	const int32_t endIndex = availableNodes[random];
	grid[availableNodes[random]].SetType(NodeType::Target);
	availableNodes.erase(availableNodes.begin() + random);
}

std::vector<int32_t> AStar::GetNeighbors(const Node n) const
{
	std::vector<int32_t> neighbors;

	int x = 0;
	int y = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			x = j + n.x;
			y = i + n.y;

			if (x < 0 || y < 0 || x > gridLength - 1 || y > gridLength - 1) continue; // dont go out of bounds
			if (j == 0 && i == 0) continue; // dont select ourselves

			const int index = (y * 10) + x;
			if (grid[index].GetType() == NodeType::Block) continue; //dont accept blocks

			neighbors.push_back(index);
		}
	}

	return neighbors;
}

void AStar::DrawNode(Node n)
{
	olc::Pixel color = white;

	switch (n.GetType())
	{
	case NodeType::Empty:
		color = white;
		break;
	case NodeType::Target:
		color = green;
		break;
	case NodeType::Block:
		color = black;
		break;
	case NodeType::Path:
		color = blue;
		break;
	}

	const int32_t x = n.x * n.width;
	const int32_t y = n.y * n.height;

	//Fill
	FillRect(
		x,
		y,
		n.width,
		n.height, color);

	//Outline
	DrawRect(
		x,
		y,
		n.width,
		n.height, black);

	//DrawString(x, y, std::to_string(val), blue, 4);
}

void AStar::HandleMovement()
{
	int32_t x = selectedNode % gridLength;
	int32_t y = selectedNode / gridLength;
	
	Node n = Node(x, y, 80, 80);
	n.SetType(NodeType::Path);
	DrawNode(n);

	if (GetKey(olc::Key::UP).bPressed)
	{
		const int32_t temp = selectedNode - gridLength;
		if (temp >= 0)
		{
			selectedNode = temp;
		}
	}

	if (GetKey(olc::Key::DOWN).bPressed)
	{
		const int32_t temp = selectedNode + gridLength;
		if (temp < gridLength * gridLength)
		{
			selectedNode = temp;
		}
	}

	if (GetKey(olc::Key::LEFT).bPressed)
	{
		if (selectedNode % gridLength != 0)
		{
			selectedNode = selectedNode - 1;
		}
	}

	if (GetKey(olc::Key::RIGHT).bPressed)
	{
		if ((selectedNode + 1) % gridLength != 0)
		{
			selectedNode = selectedNode + 1;
		}
	}

	if (GetKey(olc::Key::T).bHeld)
	{
		std::vector<int32_t> myVector = GetNeighbors(n);

		for (int32_t t : myVector)
		{		
			const int32_t sX = grid[t].x * grid[t].width;
			const int32_t sY = grid[t].y * grid[t].height;
			
			DrawString(sX, sY, "N", blue, 4);
		}
	}	
}

int main()
{
	AStar Program;
	if (Program.Construct(801, 801, 1, 1))
		Program.Start();
	return 0;
}