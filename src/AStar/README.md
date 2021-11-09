# A* Pathfinding

A* is a Heuristical path search algorithm that computes the most optimal path between two points. This implementation generates a random 2D grid of spaces with barriers and two
target points before solving the optimal path between them.

## How it works

To start, we find every neighboring cell around the origin and compute three scores.
These scores and how they are determined follows:

- g-Cost: The distance from the current grid point and the starting grid point
- h-Cost: The distance from the current grid point and the target grid point
- f-Cost: The sum of g-Cost and h-Cost

Using the lowest f-cost grid point, we can determine if we are making more or less progress towards the target point and eventually compute the shortest distance.

# Implementation

For visual purposes, I am using TheOneLoneCoder's PixelGameEngine to handle graphics. This is a wonderful tool that is very easy to get started with and I highly reccommend it
to anybody creating algorithm visualizations like this one! 

[**Engine Source**](https://github.com/OneLoneCoder/olcPixelGameEngine)

## Generating the grid

Lets start by creating a simple 10x10 grid of objects called a Node. Simple enough, just nest two loops and store the index of the loops as the node positions. We are also
going to store the one-dimensional value of the grid space in a separate vector for use later.

```cpp
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
```

![Grid](https://github.com/Kobakat/Algorithms/blob/master/imgdump/Grid.png)

The next thing we need are some obstacles. If we just randomly select any elements, we may end up selecting duplicates.
To get around this efficently, just resize our availableNodes vector from earlier and shrink the amount of elements after removing the selected grid space.

```cpp
//Assign random obstructions
for (int i = 0; i < obstructions; i++)
{		
    const int32_t size = availableNodes.size() - 1;
    const int32_t random = rand() % size;
	
    grid[availableNodes[random]].SetType(NodeType::Block);
    availableNodes.erase(availableNodes.begin() + random);
}
```

![Barriers](https://github.com/Kobakat/Algorithms/blob/master/imgdump/Barriers.png)

All thats left is to select two more random spaces as our start and end point. Fortunately thats easy enough as we just re-use the barrier generation code.

## Determining cell neighbors

Once we have our grid, we need to be able to get a list of every node that is an available neighbor of the provided node. This is quick and easy, all we have to
do is check in a 3x3 space around the node and make sure that point meets four conditions:

- The point actually exists on the grid
- The point isn't its own position
- The point isn't in a barrier
- If the point is a "corner" piece, we ignore it if a block adjacent to is a block. This prevents us from cutting corners

```cpp
void AStarGrid::GetNeighbors(Node* const n, std::vector<Node*>& outVector) const
{
	outVector.clear();

	int x = 0;
	int y = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (j == 0 && i == 0) continue; // dont select ourselves

			x = j + n->x;
			y = i + n->y;

			if (x < 0 || y < 0 || x > gridWidth - 1 || y > gridHeight - 1) continue; // dont go out of bounds
			
			int index = (y * gridWidth) + x;
			if (grid[index]->GetType() == NodeType::Block) continue; //dont accept blocks

			//This space we are currently evaluating is not immediatly adjacent to us
			if (j != 0 && i != 0)
			{
				int adjacentX = x + (j * -1);
				int indexX = (y * gridWidth) + adjacentX;
				if (grid[indexX]->GetType() == NodeType::Block) continue; // adjacent x tile is a block, cant cut the corner

				int adjacentY = y + (i * -1);
				int indexY = (adjacentY * gridWidth) + x;
				if (grid[indexY]->GetType() == NodeType::Block) continue; // adjacent y tile is a block, cant cut the corner
			}

			outVector.push_back(grid[index]);
		}
	}
}
```

![Neighboring Cells](https://github.com/Kobakat/Algorithms/blob/master/imgdump/Neighbor.gif)


## Finding the shortest path

Now that we have a working grid and some visual fidelity, lets actually determine the most efficent route between two paths. We start by declaring two vectors that we will store
open (unexplored) and closed (previously explored) nodes. As long as our open set contains any nodes, we will keep attempting to solve a path. If we find ourselves in a situation without any nodes, we can be certain a path does not exist.

```cpp
//Start by clearing the vectors and adding the starting node to the open set
open.clear();
closed.clear();

open.emplace_back(startNode);
```

We start by selecting the first element in the open list and assigning it to a variable "guess". Then, we loop through every node in the open set and check which has the lowest fcost. Note that this particular method of searching for the lowest fcost node is rather naive and optimizations can be done to improve it.

```cpp
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
```

Next we do a quick check to see if the node we just selected was the target node. If this is true, we have finished the path

```cpp
if (guess == endNode)
{
	startNode->SetType(NodeType::Start);
	endNode->SetType(NodeType::Target);
	return true;
}
```

Otherwise, lets add this node to the closed set and remove it from the open before actually evaluating it

```cpp
open.erase(std::remove(open.begin(), open.end(), guess), open.end());
closed.emplace_back(guess);
```

Now we can use our neighobrs function we implemented earlier. We can use this to figure out all the available nodes we can travel to, and decide which of those neighbor nodes is going to move us closest to the target node.

```cpp
std::vector<Node*> neighbors;
grid->GetNeighbors(guess, neighbors);
```

The last step is to just determine which node moves us closest

```cpp
for (Node* n : neighbors)
{
	//Node is in closed list already, skip it
	if (std::find(closed.begin(), closed.end(), n) != closed.end())
	{
		continue;
	}

	const bool bIsNotInOpen = std::find(open.begin(), open.end(), n) == open.end();
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
```
All that is left to do is run through this loop until we have found the path or determined none exists. We can visualize what a solved path looks like here.

![Solved Path](https://github.com/Kobakat/Algorithms/blob/master/imgdump/Path.png)

Grey boxes represent unevaluated nodes in the open set. Red boxes represent evaluated boxes in the closed set. And blue boxes represent evaluated boxes that make up the most efficent path.

[**Engine Source**](https://github.com/OneLoneCoder/olcPixelGameEngine)

# License (OLC-3) - PixelGameEngine

## Pixel Game Engine redistrubition is permitted following accordance with OLC-3 Licensing

Copyright 2018-2021 OneLoneCoder.com

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions 
are met:

1. Redistributions or derivations of source code must retain the above 
   copyright notice, this list of conditions and the following disclaimer.

2. Redistributions or derivative works in binary form must reproduce 
   the above copyright notice. This list of conditions and the following 
   disclaimer must be reproduced in the documentation and/or other 
   materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its 
   contributors may be used to endorse or promote products derived 
   from this software without specific prior written permission.
    
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
