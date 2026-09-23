#pragma once

#include <string>
#include <list>
#include <vector>

#include "Vector2.h"


struct Node
{
	Vector2 position;
	float g, h, f;
	Node* parent;
	Node(Vector2 _position = Vector2());
	~Node();
	float GetDistance(Node* from);
	float GetNeighbourDistance(Node* Neighbour);
};


class AStarAlgo
{
public:

	struct AStarResult
	{
		int pathLenght;
		int steps;
		std::list<Node*> nodeSteps;
	};

	void SetGrid(std::vector<std::vector<Node*>> grid);

	AStarResult FindCheaperPath(Node* from, Node* to);

private:
	std::vector<Node*> GetChildren(Node* parent);
	AStarResult RunBackPath(Node* endNode, int steps);

private:
	std::vector<std::vector<Node*>> m_nodeGrid;

};

