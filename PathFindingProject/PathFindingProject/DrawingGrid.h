#pragma once

#include <vector>
#include "Vec2.h"
#include "PathFindingAlgo.h"
#include "raylib.h"

struct rlButton
{
	Vector2 position;
	Vector2 size;
	std::string textInButton;
	Color backGroundColor = { 137, 189, 134,255};
	bool IsPressed();

	void DrawRlButton();
};

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
	void SetRandomObstacles(int obstacleCount = 0);
	void SetRandomWeightOnNodes(int weightedCount = 0, int maxWeight = 5);

	void ChooseAlgorithm(AvailableAlgorithm algo);

	void OpenGridWindow();
	void CloseGridWindow();

private:
	void UpdateButtons();
	void FindPath(Vec2 const& from, Vec2 const& to);
	void DrawPathFindingGrid();
	void DrawResult(PathfindingResult res);
	bool IsSESet();
	void SetNewStartAndEnd();

	void SetObstaclesByHand();
	void SetWeightByHand();
	void ResetNodes();
	void ResetObstacles();
	void ResetWeight();

private:
	PathFindingAlgo* m_pPathFindingAlgo;
	AvailableAlgorithm m_useAlgo;
	std::vector<std::vector<Node*>> m_grid;

	PathfindingResult m_currentresult;
	Vec2 m_from, m_to;

	int tileW;
	int tileH;

	int winW;
	int winH;
	Color m_bgColor = { 255, 229, 248,255 };

	rlButton m_launchFinding;
	rlButton m_resetPathButton;
	rlButton m_changeAlgoButton;
	rlButton m_setNewStartEnd;
	rlButton m_startSetObstacles;
	rlButton m_resetObstacles;
	rlButton m_startSetWeight;
	rlButton m_resetWeight;

	bool m_setObstacles = false;
	bool m_setWeight = true;
	int m_isSettingSE = -1;
};

