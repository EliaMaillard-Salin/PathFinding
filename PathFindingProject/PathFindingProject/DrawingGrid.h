#pragma once

#include <vector>
#include "Vec2.h"
#include "PathFindingAlgo.h"

class DrawingGrid
{
public:
	enum AvailableAlgorithm
	{
		DIJKSTRA,
		A_STAR,
	};

	DrawingGrid();
	~DrawingGrid();

	void InitGridWindow(int width, int height, std::string title);
	void InitGrid(int width, int height);
	void SetObstacles(std::vector<Vec2> const& obstacleList);
	void SetRandomObstacles();

	void ChooseAlgorithm(AvailableAlgorithm algo);

	void FindPath(Vec2 const& from, Vec2 const& to);

	void CloseGridWindow();

private:
	void DrawPathFindingGrid();
	void DrawResult(PathfindingResult res);
private:
	PathFindingAlgo* m_pPathFindingAlgo;
	AvailableAlgorithm m_useAlgo;
	std::vector<std::vector<Node*>> m_grid;

	int tileW;
	int tileH;

	int winW;
	int winH;
};

