#include "DijkstraAlgo.h"

#include <list>


DijkstraAlgo::DijkstraAlgo()
{}

DijkstraAlgo::DijkstraAlgo(std::vector<std::vector<int>> graph) : m_graph(graph)
{}

void DijkstraAlgo::SetNodeNames(std::vector<std::string> nodeNames)
{
	m_names = nodeNames;
	m_namesAssociated = std::map<std::string, int>();
	for (int i = 0; i < nodeNames.size(); i++)
	{
		m_namesAssociated.insert(std::pair < std::string, int>(nodeNames[i], i));
	}
}


std::vector<DijkstraAlgo::DijkstraSteps> DijkstraAlgo::FindCheaperPath(int from)
{
	std::vector<DijkstraAlgo::DijkstraSteps> results;
	std::list<int> accessibleNode = {};
	for (int i = 0; i < m_graph.size(); i++)
	{
		results.push_back({inf,-1,0, "", ""});
		accessibleNode.push_back(i);
	}

	int stepsTake = 0;
	int currentMinNode = from;
	results[currentMinNode].distance = 0;
	results[currentMinNode].from = currentMinNode;
	results[currentMinNode].fromName = m_names[currentMinNode];
	results[currentMinNode].nodeName = m_names[currentMinNode];
	results[currentMinNode].stepsNeeded = 0;
	while (accessibleNode.empty() == false)
	{
		stepsTake++;
		int minValue = inf;
		for (int u : accessibleNode)
		{
			 if (results[u].distance < minValue)
			 {
				 currentMinNode = u;
				 minValue = results[u].distance;
			 }

		}

		accessibleNode.remove(currentMinNode);

		for (int i = 0; i < m_graph.size(); i++)
		{
			if (m_graph[currentMinNode][i] == inf)
				continue;

			int newDistance = results[currentMinNode].distance + m_graph[currentMinNode][i];
			if (newDistance < results[i].distance)
			{
				results[i].distance = newDistance;
				results[i].from = currentMinNode;
				results[i].stepsNeeded = stepsTake;
				results[i].fromName = m_names[currentMinNode];
				results[i].nodeName = m_names[i];
			}
		}
	}
	return results;
}

bool DijkstraAlgo::CheckOneStep(std::vector<std::vector<Node*>>& grid, Node* from, Node* to, PathfindingResult& result, bool isFirstStep)
{
	if (isFirstStep)
	{
		result.calculationSteps = -1;
		from->minDistanceWithStart = 0.0f;
		from->parent = nullptr;
		from->stepsToGetHere = 0;
		from->state = Node::NodeState::OPEN;
		m_availableNode.push_back(from);
	}
	Node* currentMinNode = nullptr;
	result.calculationSteps++;
	for (Node* pNewCurrentNode : m_availableNode)
	{
		if (currentMinNode == nullptr || pNewCurrentNode->minDistanceWithStart < currentMinNode->minDistanceWithStart)
			currentMinNode = pNewCurrentNode;
	}

	if (currentMinNode == nullptr)
	{
		m_hasEnded = true;
		return false;
	}

	if (currentMinNode->position == to->position)
	{
		RunBackPath(currentMinNode, result);
		m_hasEnded = true;
		return true;
	}

	currentMinNode->state = Node::NodeState::CLOSE;
	m_availableNode.remove(currentMinNode);

	std::vector<Node*> m_neighbours = GetChildren(currentMinNode, grid);
	for (Node* pNeighbourNode : m_neighbours)
	{
		float distanceWithNeighbour = currentMinNode->GetNeighbourDistance(pNeighbourNode);
		if (distanceWithNeighbour == inf)
			continue;

		float newDistance = currentMinNode->minDistanceWithStart + distanceWithNeighbour;
		if (newDistance < pNeighbourNode->minDistanceWithStart)
		{
			pNeighbourNode->minDistanceWithStart = newDistance;
			pNeighbourNode->parent = currentMinNode;
			pNeighbourNode->stepsToGetHere = currentMinNode->stepsToGetHere + 1;
			pNeighbourNode->state = Node::NodeState::OPEN;
			m_availableNode.push_back(pNeighbourNode);
		}
	}
	return true;
}

void DijkstraAlgo::Reset()
{
	PathFindingAlgo::Reset();
	m_availableNode.clear();
}

void DijkstraAlgo::RunBackPath(Node* endNode, PathfindingResult& algo)
{
	algo.pathCost = endNode->minDistanceWithStart;
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

std::vector<DijkstraAlgo::DijkstraSteps> DijkstraAlgo::FindCheaperPath(int from, std::vector<std::vector<int>> graph)
{
	SetGraph(graph);
	return FindCheaperPath(from);
}

std::vector<DijkstraAlgo::DijkstraSteps> DijkstraAlgo::FindCheaperPath(std::string from)
{
	return FindCheaperPath(m_namesAssociated[from]);
}



int DijkstraAlgo::FindCheaperPath(int from, int to)
{
	return FindCheaperPath(from)[to].distance;
}

int DijkstraAlgo::FindCheaperPath(int from, int to, std::vector<std::vector<int>> graph)
{
	SetGraph(graph);
	return FindCheaperPath(from, to);
}

int DijkstraAlgo::FindCheaperPath(std::string from, std::string to)
{

	return FindCheaperPath(m_namesAssociated[from], m_namesAssociated[to]);
}

void DijkstraAlgo::SetGraph(std::vector<std::vector<int>> graph)
{
	m_graph = graph;
	std::vector<std::string> emptyNames = std::vector<std::string>(graph.size(), "");
	SetNodeNames(emptyNames);
}

