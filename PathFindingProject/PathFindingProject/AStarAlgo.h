#pragma once

#include <string>

#include "Vec2.h"

#include "PathFindingAlgo.h"

class AStarAlgo : public PathFindingAlgo
{
public:

	struct AStarResult
	{
		float pathLenght;
		int pathStep;
		int calculSteps;
		std::list<Node*> nodeSteps;
	};

	void SetGrid(std::vector<std::vector<Node*>> grid);

	AStarResult FindCheaperPath(Node* from, Node* to);

	void CheckOneStep(std::vector<std::vector<Node*>>& grid, Node* from, Node* to, PathfindingResult& result, bool isFirstStep = false) override;

	void Reset() override;

private:
	std::vector<Node*> GetChildren(Node* parent);

	AStarResult RunBackPath(Node* endNode, int steps);
	void RunBackPath(Node* endNode, PathfindingResult& algo);

private:

	std::list<Node*> m_openNodes;
	std::list<Node*> m_closedNode;
	std::vector<std::vector<Node*>> m_nodeGrid;

};

