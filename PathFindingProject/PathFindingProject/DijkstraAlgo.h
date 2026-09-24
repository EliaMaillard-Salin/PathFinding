#pragma once

#include <limits>
#define inf std::numeric_limits<int>::max()

#include <vector>
#include <string>
#include <map>

#include "PathFindingAlgo.h"

class DijkstraAlgo : public PathFindingAlgo
{
public:

	struct DijkstraSteps
	{
		int distance;
		int from;
		int stepsNeeded;
		std::string fromName;
		std::string nodeName;
	};

	DijkstraAlgo();
	DijkstraAlgo(std::vector<std::vector<int>> graph);

	void SetGraph(std::vector<std::vector<int>> graph);
	void SetNodeNames(std::vector<std::string> nodeNames);

	int FindCheaperPath(int from, int to);
	int FindCheaperPath(int from, int to, std::vector<std::vector<int>> graph);
	int FindCheaperPath(std::string from, std::string to);

	std::vector<DijkstraSteps> FindCheaperPath(int from);
	std::vector<DijkstraSteps> FindCheaperPath(int from, std::vector<std::vector<int>> graph);
	std::vector<DijkstraSteps> FindCheaperPath(std::string from);
	
	void CheckOneStep(std::vector<std::vector<Node*>>& grid, Node* from, Node* to, PathfindingResult& result, bool isFirstStep = false) override;

	void Reset() override;

private:
	void RunBackPath(Node* endNode, PathfindingResult& algo);

private:
	std::vector<std::vector<int>> m_graph;
	std::map<std::string, int> m_namesAssociated;
	std::vector<std::string> m_names;

	std::list<Node*> m_availableNode;
	
};

