#include "PathFindingAlgo.h"

bool PathFindingAlgo::HasEnded()
{
    return m_hasEnded;
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
	if (position.x == Neighbour->position.x || position.y == Neighbour->position.y)
		return 1.0f;
	return 1.4f;
}

