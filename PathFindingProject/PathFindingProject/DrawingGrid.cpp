#include "DrawingGrid.h"
#include "raylib.h"

#include "AStarAlgo.h"
#include <iostream>

DrawingGrid::DrawingGrid():
    m_pPathFindingAlgo(new AStarAlgo()), m_useAlgo(AvailableAlgorithm::A_STAR), m_grid({}),
    tileW(20),tileH(20),winW(0), winH(0)
{}

DrawingGrid::~DrawingGrid()
{
    for (int y = 0; y < m_grid.size(); y++)
    {
        for (int x = 0; x < m_grid[0].size(); x++)
        {
            delete m_grid[y][x];
        }
    }
    m_grid.clear();
}

void DrawingGrid::InitGridWindow(int width, int height, std::string title)
{
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    winW = width;
    winH = height;
}

void DrawingGrid::InitGrid(int width, int height)
{
    m_grid = std::vector<std::vector<Node*>>(height);
    for (int y = 0; y < height; y++)
    {
        m_grid[y] = std::vector<Node*>(width);
        for (int x = 0; x < width; x++)
        {
            m_grid[y][x] = new Node(Vec2(x, y));
        }
    }
    tileW = winW / width;
    tileH = winH / height;
}

void DrawingGrid::SetObstacles(std::vector<Vec2> const& obstacleList)
{
    for (int i = 0; i < obstacleList.size(); i++)
    {
        delete m_grid[obstacleList[i].y][obstacleList[i].x];
        m_grid[obstacleList[i].y][obstacleList[i].x] = nullptr;
    }
}

void DrawingGrid::SetRandomObstacles()
{
}

void DrawingGrid::ChooseAlgorithm(AvailableAlgorithm algo)
{
}

void DrawingGrid::FindPath(Vec2 const& from, Vec2 const& to)
{
    PathfindingResult result = {};
    bool firstStep = true;
    m_grid[from.y][from.x]->state = Node::NodeState::START_END;
    m_grid[to.y][to.x]->state = Node::NodeState::START_END;
    while (!WindowShouldClose())
    {
        while(!m_pPathFindingAlgo->HasEnded())
        {
            m_pPathFindingAlgo->CheckOneStep(m_grid, m_grid[from.y][from.x], m_grid[to.y][to.x], result, firstStep);
            firstStep = false;

            BeginDrawing();
            ClearBackground(DARKGREEN);

            m_grid[from.y][from.x]->state = Node::NodeState::START_END;
            m_grid[to.y][to.x]->state = Node::NodeState::START_END;
            DrawPathFindingGrid();

            EndDrawing();

            for(int i = 0; i < 100000000 ;i++)
            { }
        }

        BeginDrawing();
        ClearBackground(DARKGREEN);

        DrawPathFindingGrid();

        DrawResult(result);

        EndDrawing();
    }

    CloseWindow();
}

void DrawingGrid::CloseGridWindow()
{
    CloseWindow();
}

void DrawingGrid::DrawPathFindingGrid()
{
    for (int y = 0; y < m_grid.size();y++)
    {
        for (int x = 0; x < m_grid[0].size();x++)
        {
            if (m_grid[y][x] == nullptr)
            {
                DrawRectangle(x * tileW, y * tileH, tileW, tileH, BLACK);
                DrawRectangleLines(x * tileW, y * tileH, tileW, tileH, BLACK);
                continue;
            }


            Color tileColor = BLACK;
            switch (m_grid[y][x]->state)
            {
            case Node::NodeState::OPEN:
                tileColor = BLUE;
                break;
            case Node::NodeState::CLOSE:
                tileColor = RED;
                break;
            case Node::NodeState::CHECKED:
                tileColor = LIGHTGRAY;
                break;
            case Node::NodeState::UNCHECK:
                tileColor = GRAY;
                break;
            case Node::NodeState::START_END:
                tileColor = ORANGE;
                break;
            default:
                break;
            }
            Node* nodeToDraw = m_grid[y][x];
            DrawRectangle(nodeToDraw->position.x * tileW, nodeToDraw->position.y * tileH, tileW, tileH, tileColor);
            DrawRectangleLines(nodeToDraw->position.x * tileW, nodeToDraw->position.y * tileH, tileW, tileH, BLACK);
        }
    }

}

void DrawingGrid::DrawResult(PathfindingResult res)
{
    for (Node* nodeToDraw : res.nodeStepsFromBeginning)
    {
        DrawRectangle(nodeToDraw->position.x * tileW, nodeToDraw->position.y * tileH, tileW, tileH, GREEN);
        DrawRectangleLines(nodeToDraw->position.x * tileW, nodeToDraw->position.y * tileH, tileW, tileH, BLACK);
    }
}
