#include "AStar.h"
#include "AStarSolver.h"
#include "AStarGrid.h"
#include "Node.h"

//tired of typing olc::
const olc::Pixel white = olc::Pixel(olc::WHITE);
const olc::Pixel black = olc::Pixel(olc::BLACK);
const olc::Pixel green = olc::Pixel(olc::GREEN);
const olc::Pixel blue = olc::Pixel(olc::BLUE);
const olc::Pixel red = olc::Pixel(olc::DARK_RED);
const olc::Pixel grey = olc::Pixel(olc::DARK_GREY);
const olc::Pixel dgreen = olc::Pixel(olc::DARK_GREEN);

AStar::AStar()
{
	sAppName = "A* Pathfinding"; 
}

bool AStar::OnUserCreate()
{
	nodeSize = 40;
	srand(time(nullptr));

	grid = new AStarGrid(20, 20, 100);
	solver = new AStarSolver();
	
	return true;
}

bool AStar::OnUserDestroy()
{
	delete grid;
	delete solver;
	return true;
}

bool AStar::OnUserUpdate(float fDeltaTime)
{
	if (GetKey(olc::Key::G).bPressed)
	{
		grid->GenerateGrid();
	}

	if (GetKey(olc::Key::S).bPressed)
	{
		if (solver->Solve(grid))
		{
			solver->SetPath();
			solver->ShowScores(true);
		}	
	}

	for (Node* n : grid->grid)
	{
		DrawNode(n);
	}

	DebugNode();

	return true;
}


void AStar::DrawNode(Node* const n)
{
	olc::Pixel color = white;

	switch (n->GetType())
	{
	case NodeType::Empty:
		color = white;
		break;
	case NodeType::Start:
		color = dgreen;
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
	case NodeType::Closed:
		color = red;
		break;
	case NodeType::Open:
		color = grey;
		break;
	}

	const int32_t x = n->x * nodeSize;
	const int32_t y = n->y * nodeSize;

	//Fill
	FillRect(
		x,
		y,
		nodeSize,
		nodeSize, color);

	//Outline
	DrawRect(
		x,
		y,
		nodeSize,
		nodeSize, black);

	if (n->bDrawScores)
	{
		DrawString(x, y, std::to_string(n->gCost));
		DrawString(x, y + 10, std::to_string(n->hCost));
		DrawString(x, y + 20, std::to_string(n->fCost()));
	}
}

void AStar::DebugNode()
{
	int32_t gridWidth = 0;
	int32_t gridHeight = 0;

	grid->GetGridDimensions(gridWidth, gridHeight);

	int32_t x = debugNodeIndex % gridWidth;
	int32_t y = debugNodeIndex / gridHeight;
	
	Node n = Node(x, y);
	n.SetType(NodeType::Path);
	DrawNode(&n);

	if (GetKey(olc::Key::UP).bPressed)
	{
		const int32_t temp = debugNodeIndex - gridWidth;
		if (temp >= 0)
		{
			debugNodeIndex = temp;
		}
	}

	if (GetKey(olc::Key::DOWN).bPressed)
	{
		const int32_t temp = debugNodeIndex + gridWidth;
		if (temp < gridWidth * gridHeight)
		{
			debugNodeIndex = temp;
		}
	}

	if (GetKey(olc::Key::LEFT).bPressed)
	{
		if (debugNodeIndex % gridHeight != 0)
		{
			debugNodeIndex--;
		}
	}

	if (GetKey(olc::Key::RIGHT).bPressed)
	{
		if ((debugNodeIndex + 1) % gridHeight != 0)
		{
			debugNodeIndex++;
		}
	}

	if (GetKey(olc::Key::T).bHeld)
	{
		std::vector<Node*> myVector;
		grid->GetNeighbors(&n, myVector);

		for (Node* n : myVector)
		{		
			const int32_t sX = n->x * nodeSize + (nodeSize * 0.25f);
			const int32_t sY = n->y * nodeSize + (nodeSize * 0.25f);
			
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