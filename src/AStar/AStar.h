#pragma once

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Node.h"

class AStar : public olc::PixelGameEngine
{
public:
	AStar();

	int32_t gridLength;
	int32_t selectedNode;

	std::vector<Node> grid;

	bool OnUserCreate() override;
	bool OnUserUpdate(float fDeltaTime) override;

	void GenerateGrid();
	void DrawNode(Node n);
	std::vector<int32_t> GetNeighbors(const Node n) const;

private:
	void HandleMovement();
};