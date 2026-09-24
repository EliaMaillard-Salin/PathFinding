#pragma once

#include <list>
#include <vector>

#include "Vec2.h"


struct Node
{
	enum NodeState
	{
		OPEN,
		CLOSE,
		UNCHECK,
		CHECKED,
		START_END,
	};

	Node(Vec2 _position = Vec2());
	~Node();

	float GetDistance(Node* from);
	float GetNeighbourDistance(Node* Neighbour);

	NodeState state;
	Vec2 position;
	float weight;
	Node* parent;

	// AStar Var
	float g, h, f;

	// Dijsktra Var
	float distanceWithClosest;
	int stepsToGetHere;

};

struct PathfindingResult
{
	float pathCost;
	int pathStep;
	int calculationSteps;
	std::list<Node*> nodeStepsFromBeginning;
};


class PathFindingAlgo
{

public:

	virtual bool HasEnded();
	virtual void CheckOneStep(std::vector<std::vector<Node*>>& grid, Node* from, Node* to, PathfindingResult& result, bool isFirstStep = false) = 0;

protected:
	std::vector<Node*> GetChildren(Node* parent, std::vector<std::vector<Node*>>& grid);

protected:
	bool m_hasEnded;

};

