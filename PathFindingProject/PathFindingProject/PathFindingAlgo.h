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
		START,
		END,
	};

	Node(Vec2 _position = Vec2());
	~Node();

	float GetDistance(Node* from);
	float GetNeighbourDistance(Node* Neighbour);
	void Reset();

	Vec2 position;

	NodeState state;
	int weight;
	Node* parent;

	// AStar Var
	float g, h, f;

	// Dijsktra Var
	float minDistanceWithStart;
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

	virtual void Reset();
protected:
	std::vector<Node*> GetChildren(Node* parent, std::vector<std::vector<Node*>>& grid);

protected:
	bool m_hasEnded;

};

