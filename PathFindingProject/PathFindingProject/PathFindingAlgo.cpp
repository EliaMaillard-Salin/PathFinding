#include "PathFindingAlgo.h"

#include <limits>
#define inf std::numeric_limits<int>::max()

bool PathFindingAlgo::HasEnded()
{
    return m_hasEnded;
}



std::vector<Node*> PathFindingAlgo::GetChildren(Node* parent, std::vector<std::vector<Node*>>& grid)
{
	std::vector<Node*> children = {};
	int offsetX = -1;
	int offsetY = -1;

	for (int i = 0; i < 9; i++)
	{
		offsetX = (i % 3) - 1;
		offsetY = (i / 3) - 1;
		if (offsetX == 0 && offsetY == 0)
			continue;
		if ((parent->position.x + offsetX) < 0 || (parent->position.x + offsetX) > grid[0].size() - 1)
			continue;
		if ((parent->position.y + offsetY) < 0 || (parent->position.y + offsetY) > grid.size() - 1)
			continue;
		children.push_back(grid[parent->position.y + offsetY][parent->position.x + offsetX]);
	}
	return children;
}

Node::Node(Vec2 _position) :
	position(_position), g(0), h(0), f(0), parent(nullptr),
	state(UNCHECK),weight(1.0f)
{
}

Node::~Node()
{
}

float Node::GetDistance(Node* from)
{
	Vec2 newPos = from->position - position;
	//return newPos.SqrDistance();
	return std::abs(newPos.x) + std::abs(newPos.y);
}

float Node::GetNeighbourDistance(Node* Neighbour)
{
	if (Neighbour == nullptr)
		return inf;

	if (position.x == Neighbour->position.x || position.y == Neighbour->position.y)
		return 1.0f;
	return 1.4f;
}

