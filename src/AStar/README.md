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
for (int i = 0; i < gridLength; i++)
{
    for (int j = 0; j < gridLength; j++)
    {
        grid.push_back(Node(j, i, sideLength, sideLength));
        availableNodes.push_back(j+(i*10));
    }
}
```

![Grid](https://github.com/Kobakat/Algorithms/blob/main/imgdump/Grid.png)

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

![Barriers](https://github.com/Kobakat/Algorithms/blob/main/imgdump/Barriers.png)

All thats left is to select two more random spaces as our start and end point. Fortunately thats easy enough as we just re-use the barrier generation code.

## Determining cell neighbors

Once we have our grid, we need to be able to get a list of every node that is an available neighbor of the provided node. This is quick and easy, all we have to
do is check in a 3x3 space around the node and make sure that point meets three conditions:

- The point actually exists on the grid
- The point isn't own position
- The point isn't in a barrier

```cpp
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
```

![Neighboring Cells](https://github.com/Kobakat/Algorithms/blob/main/imgdump/Neighor.gif)


## Finding the shortest path

Coming soon!

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
