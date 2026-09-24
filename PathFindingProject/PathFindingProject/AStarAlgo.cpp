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
	res.calculSteps = steps;
	res.pathStep = 0;
	res.nodeSteps.push_front(endNode);
	Node* nextNode = endNode;
	while (nextNode->parent != nullptr)
	{
		nextNode = nextNode->parent;
		res.nodeSteps.push_front(nextNode);
		res.pathStep++;
	}
	return res;
}

void AStarAlgo::RunBackPath(Node* endNode, PathfindingResult& algo)
{
	algo.pathCost = endNode->g;
	algo.pathStep = 0;
	algo.nodeStepsFromBeginning.push_front(endNode);
	Node* nextNode = endNode;
	while (nextNode->parent != nullptr)
	{
		nextNode = nextNode->parent;
		algo.nodeStepsFromBeginning.push_front(nextNode);
		algo.pathStep++;
	}
	return;
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

	from->g = 0;
	from->h = from->GetDistance(to);
	from->f = from->g + from->h;
	Node* currentNode = nullptr;
	openNodes.push_back(from);
	int steps = -1;

	while (!openNodes.empty())
	{
		currentNode = openNodes.front();
		for (Node* open : openNodes)
		{
			if (open->f < currentNode->f)
				currentNode = open;
		}
		openNodes.remove(currentNode);
		closedNode.push_back(currentNode);
		steps++;
		if (currentNode->position == to->position)
		{
			result = RunBackPath(currentNode, steps);
			break;
		}
		if (currentNode->position == Vec2(3,3))
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

			if (children[i]->parent != nullptr && children[i]->g < (currentNode->g + currentNode->GetNeighbourDistance(children[i])))
				continue;

			children[i]->g = currentNode->g + currentNode->GetNeighbourDistance(children[i]);
			children[i]->h = children[i]->GetDistance(to);
			int roundUpF = (children[i]->g + children[i]->h) * 100.0f;
			children[i]->f = roundUpF / 100.0f;
			children[i]->parent = currentNode;

			int contLoop = false;
			for(Node* open : openNodes)
			{
				if (open == children[i])
				{
					contLoop = true;
					break;
				}
			}
			if (contLoop)
				continue;
			openNodes.push_back(children[i]);
		}
	}
	return result;
}

void AStarAlgo::CheckOneStep(std::vector<std::vector<Node*>>& grid, Node* from, Node* to, PathfindingResult& result, bool isFirstStep)
{
	
	if (isFirstStep)
	{
		result.calculationSteps = -1;
		from->g = 0;
		from->h = from->GetDistance(to);
		from->f = from->g + from->h;
		from->state = Node::NodeState::OPEN;
		m_openNodes.push_back(from);
	}
	result.calculationSteps++;
	Node* currentNode = m_openNodes.front();
	
	for (Node* open : m_openNodes)
	{
		if (open->f < currentNode->f)
			currentNode = open;
	}
	m_openNodes.remove(currentNode);
	m_closedNode.push_back(currentNode);
	currentNode->state = Node::NodeState::CLOSE;
	if (currentNode->position == to->position)
	{
		RunBackPath(currentNode,result);
		m_hasEnded = true;
	}

	std::vector<Node*> children = PathFindingAlgo::GetChildren(currentNode,grid);
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] == nullptr)
			continue;

		if (std::find(m_closedNode.begin(), m_closedNode.end(), children[i]) != m_closedNode.end())
			continue;

		if (children[i]->parent != nullptr && children[i]->g < (currentNode->g + currentNode->GetNeighbourDistance(children[i])))
			continue;

		children[i]->g = currentNode->g + currentNode->GetNeighbourDistance(children[i]);
		children[i]->h = children[i]->GetDistance(to);
		int roundUpF = (children[i]->g + children[i]->h) * 100.0f;
		children[i]->f = roundUpF / 100.0f;
		children[i]->parent = currentNode;
		children[i]->state = Node::NodeState::CHECKED;

		int contLoop = false;
		for (Node* open : m_openNodes)
		{
			if (open == children[i])
			{
				contLoop = true;
				break;
			}
		}
		if (contLoop)
			continue;
		m_openNodes.push_back(children[i]);
		children[i]->state = Node::NodeState::OPEN;
	}
}

void AStarAlgo::Reset()
{
	PathFindingAlgo::Reset();
	m_openNodes.clear();
	m_closedNode.clear();
}


