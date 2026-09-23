#include "AStarAlgo.h"


#include <algorithm>
#include <iostream>

std::vector<Node*> AStarAlgo::GetChildren(Node* parent)
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
		if ((parent->position.x + offsetX) < 0 || (parent->position.x + offsetX) > m_nodeGrid[0].size() - 1)
			continue;
		if ((parent->position.y + offsetY) < 0 || (parent->position.y + offsetY) > m_nodeGrid.size() - 1)
			continue;
		children.push_back(m_nodeGrid[parent->position.y + offsetY][parent->position.x + offsetX]);
	}
	return children;
}

AStarAlgo::AStarResult AStarAlgo::RunBackPath(Node* endNode, int steps)
{
	AStarResult res = {};
	res.pathLenght = endNode->g;
	res.steps = steps;
	res.nodeSteps.push_front(endNode);
	Node* nextNode = endNode->parent;
	for (int i = 0; i < steps; i++)
	{
		res.nodeSteps.push_front(nextNode);
		nextNode = nextNode->parent;
	}
	return res;
}


void AStarAlgo::SetGrid(std::vector<std::vector<Node*>> grid)
{
	m_nodeGrid = grid;
}

AStarAlgo::AStarResult AStarAlgo::FindCheaperPath(Node* from, Node* to)
{
	AStarResult result = {};

	std::list<Node*> openNodes = {};
	std::list<Node*> closedNode = {};

	Node* closestNode = from;
	from->g = 0;
	from->h = from->GetDistance(to);
	from->f = from->g + from->h;
	Node* currentNode = nullptr;
	openNodes.push_back(closestNode);
	int steps = -1;
	while (!openNodes.empty())
	{
		closestNode = openNodes.front();
		for (Node* open : openNodes)
		{
			if (open->f < closestNode->f)
				closestNode = open;
		}
		currentNode = closestNode;
		openNodes.remove(currentNode);
		closedNode.push_back(currentNode);
		steps++;
		if (currentNode->position == to->position)
		{
			result = RunBackPath(currentNode, steps);
			break;
		}
		if (currentNode->position == Vector2(2,1))
		{
			std::cout << "T";
		}

		std::vector<Node*> children = GetChildren(currentNode);
		for (int i = 0; i < children.size(); i++)
		{
			if (children[i] == nullptr)
				continue;

			if (std::find(closedNode.begin(), closedNode.end(), children[i]) != closedNode.end())
				continue;

			children[i]->g = currentNode->g + currentNode->GetNeighbourDistance(children[i]);
			children[i]->h = children[i]->GetDistance(to);
			children[i]->f = children[i]->g + children[i]->h;

			int contLoop = false;
			for(Node* open : openNodes)
			{
				if (open == children[i])
				{
					contLoop = true;
					break;
				}
				if (children[i]->f > open->f)
				{
					contLoop = true;
					break;
				}
			}
			if (contLoop)
				continue;

			children[i]->parent = currentNode;
			openNodes.push_back(children[i]);
		}
	}
	return result;
}





Node::Node(Vector2 _position) : 
	position(_position), g(0),h(0),f(0),parent(nullptr)
{}

Node::~Node()
{
}

float Node::GetDistance(Node* from)
{
	Vector2 newPos = from->position - position;
	//newPos.SqrDistance()
	return std::abs(newPos.x) + std::abs(newPos.y);
}

float Node::GetNeighbourDistance(Node* Neighbour)
{
	if (position.x == Neighbour->position.x || position.y == Neighbour->position.y)
		return 1.0f;
	return 1.4f;
}

