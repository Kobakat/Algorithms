#pragma once

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Node;
class AStarGrid;
class AStarSolver;

class AStar : public olc::PixelGameEngine
{
public:
	AStar();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fDeltaTime) override;
	bool OnUserDestroy() override;
	
	void DrawNode(Node* const n);
	
	AStarGrid* grid;
	AStarSolver* solver;

	int32_t nodeSize;
	int32_t debugNodeIndex;
private:
	void DebugNode();
};