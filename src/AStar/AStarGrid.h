#pragma once
#include <stdint.h>
#include <vector>
class Node;

class AStarGrid
{
public:
	AStarGrid(const int32_t width, const int32_t height, const int32_t obstructions);
	~AStarGrid();
	
	void GenerateGrid();

	std::vector<Node*> grid;
	
	int32_t GetIndexOfNode(Node* const n) const;
	int32_t GetDistanceBetweenNodes(Node* const a, Node* const b) const;

	void GetGridDimensions(int32_t& x, int32_t& y) const;
	void GetTargetIndexes(int32_t& start, int32_t& end) const;
	void GetNeighbors(Node* const n, std::vector<Node*>& outVector) const;
	
private:
	int32_t gridWidth;
	int32_t gridHeight;
	int32_t obstructionCount;

	int32_t startIndex;
	int32_t endIndex;

	void CleanGrid();	
};