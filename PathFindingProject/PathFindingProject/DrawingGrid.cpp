#include "DrawingGrid.h"
#include "raylib.h"

#include "AStarAlgo.h"
#include "DijkstraAlgo.h"
#include <iostream>
#include <cstdlib>

DrawingGrid::DrawingGrid():
    m_pPathFindingAlgo(new AStarAlgo()), m_useAlgo(AvailableAlgorithm::A_STAR), m_grid({}),
    tileW(20),tileH(20),winW(0), winH(0), 
    m_resetPathButton(),m_changeAlgoButton(),m_setNewStartEnd(),m_startSetObstacles(),m_startSetWeight(), m_launchFinding()
{
}

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
    m_launchFinding.position = { 10.0f, height - 90.0f };
    m_launchFinding.size = { 100.0f, 70.0f };
    m_launchFinding.textInButton = "START";
    
    m_resetPathButton.position = { 120.0f, height - 85.0f };
    m_resetPathButton.size = { 100.0f, 60.0f };
    m_resetPathButton.textInButton = "Reset\n Path";

    m_changeAlgoButton.position = { 240.0f, height - 85.0f };
    m_changeAlgoButton.size = { 100.0f, 60.0f };
    m_changeAlgoButton.textInButton = "Change\n Algo";
    
    m_setNewStartEnd.position = { 360.0f, height - 85.0f };
    m_setNewStartEnd.size = { 100.0f, 60.0f };
    m_setNewStartEnd.textInButton = "Set Start \n And End";
    
    m_startSetObstacles.position = { 480.0f, height - 90.0f };
    m_startSetObstacles.size = { 200.0f, 30.0f };
    m_startSetObstacles.textInButton = "Set Obstacles";

    m_resetObstacles.position = { 480.0f, height - 40.0f };
    m_resetObstacles.size = { 200.0f, 30.0f };
    m_resetObstacles.textInButton = "Reset Obstacles";

    m_startSetWeight.position = { 700.0f, height - 90.0f };
    m_startSetWeight.size = { 200.0f, 30.0f };
    m_startSetWeight.textInButton = "Set Weights";

    m_resetWeight.position = { 700.0f, height - 40.0f };
    m_resetWeight.size = { 200.0f, 30.0f };
    m_resetWeight.textInButton = "Reset Weights";
    
    std::srand(time(0));
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    winW = width;
    winH = height - 100;
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

void DrawingGrid::SetRandomObstacles(int obstacleCount)
{
    int gHeight = m_grid.size() - 1;
    int gWidth = m_grid[0].size() -1;
    if (obstacleCount == 0)
    {
        int maxObstacles = (gWidth * gHeight) - gWidth;
        int range = maxObstacles - gWidth + 1;
        obstacleCount = (std::rand() % range) + gWidth;
    }

    for (int i = 0; i < obstacleCount; i++)
    {
        int rPosX = std::rand() % ((gHeight - 1) + 1);
        int rPosY = std::rand() % ((gWidth - 1) + 1);
        if (m_grid[rPosY][rPosX] != nullptr)
            delete m_grid[rPosY][rPosX];
        m_grid[rPosY][rPosX] = nullptr;
    }
}

void DrawingGrid::SetRandomWeightOnNodes(int weightedCount, int maxWeight)
{
    int gHeight = m_grid.size() - 1;
    int gWidth = m_grid[0].size() - 1;
    if (weightedCount == 0)
    {
        int maxObstacles = (gHeight * gWidth) - gHeight;
        int range = maxObstacles - gHeight + 1;
        weightedCount = (std::rand() % range) + gHeight;
    }

    for (int i = 0; i < weightedCount; i++)
    {
        int rPosX = std::rand() % (gWidth + 1);
        int rPosY = std::rand() % (gHeight + 1);
        float rWeight = std::rand() % maxWeight + 1;
        if (m_grid[rPosY][rPosX] != nullptr)
            m_grid[rPosY][rPosX]->weight = rWeight;
    }
}

void DrawingGrid::ChooseAlgorithm(AvailableAlgorithm algo)
{
    if (algo == m_useAlgo)
        return;

    if (m_pPathFindingAlgo != nullptr)
        delete m_pPathFindingAlgo;

    switch (algo)
    {
    case DrawingGrid::DIJKSTRA:
        m_pPathFindingAlgo = new DijkstraAlgo();
        break;
    case DrawingGrid::A_STAR:
        m_pPathFindingAlgo = new AStarAlgo();
        break;
    default:
        break;
    }
}

void DrawingGrid::UpdateButtons()
{
    if (m_launchFinding.IsPressed() && IsSESet())
    {
        ResetNodes();
        FindPath(m_from, m_to);
    }

    if (m_setNewStartEnd.IsPressed())
        m_isSettingSE = 0;

    if (m_isSettingSE >= 0)
        SetNewStartAndEnd();

    if (m_resetPathButton.IsPressed())
        ResetNodes();
    if (m_resetObstacles.IsPressed())
        ResetObstacles();
    if (m_resetWeight.IsPressed())
        ResetWeight();


    if (m_startSetObstacles.IsPressed())
        m_setObstacles = !m_setObstacles;
    if (m_startSetWeight.IsPressed())
        m_setWeight = !m_setWeight;

    SetObstaclesByHand();
    SetWeightByHand();
}

void DrawingGrid::FindPath(Vec2 const& from, Vec2 const& to)
{
    bool firstStep = true;

    while (!m_pPathFindingAlgo->HasEnded())
    {
        m_pPathFindingAlgo->CheckOneStep(m_grid, m_grid[from.y][from.x], m_grid[to.y][to.x], m_currentresult, firstStep);
        firstStep = false;

        BeginDrawing();
        ClearBackground(m_bgColor);

        m_grid[from.y][from.x]->state = Node::NodeState::START;
        m_grid[to.y][to.x]->state = Node::NodeState::END;
        DrawPathFindingGrid();

        EndDrawing();

        //for(int i = 0; i < 100000000 ;i++)
        //{ }
    }
    m_pPathFindingAlgo->Reset();
}


void DrawingGrid::OpenGridWindow()
{
    m_from = Vec2(inf,inf);
    m_to = Vec2(inf,inf);

    while (!WindowShouldClose())
    {
        UpdateButtons();

        BeginDrawing();
        ClearBackground(m_bgColor);

        DrawPathFindingGrid();

        DrawResult(m_currentresult);

        m_launchFinding.DrawRlButton();
        m_resetPathButton.DrawRlButton();
        m_changeAlgoButton.DrawRlButton();
        m_setNewStartEnd.DrawRlButton();
        m_startSetObstacles.DrawRlButton();
        m_startSetWeight.DrawRlButton();
        m_resetObstacles.DrawRlButton();
        m_resetWeight.DrawRlButton();

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
            case Node::NodeState::START:
                tileColor = ORANGE;
                break;
            case Node::NodeState::END:
                tileColor = PURPLE;
                break;
            default:
                break;
            }
            Node* nodeToDraw = m_grid[y][x];
            DrawRectangle(nodeToDraw->position.x * tileW, nodeToDraw->position.y * tileH, tileW, tileH, tileColor);
            DrawRectangleLines(nodeToDraw->position.x * tileW, nodeToDraw->position.y * tileH, tileW, tileH, BLACK);

            if (m_grid[y][x]->weight > 1.0f)
            {
                Color wColor = {255,255,200,255};
                wColor.b -= 30 * m_grid[y][x]->weight;
                DrawEllipse(nodeToDraw->position.x * tileW + tileW*0.5f, nodeToDraw->position.y * tileH + tileH * 0.5f, tileW / 3.0f,  tileH / 3.0f, wColor);
            }
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

bool DrawingGrid::IsSESet()
{
    if (m_from.x == inf || m_from.y == inf)
        return false;
    if (m_to.x == inf || m_to.y == inf)
        return false;
    
    return true;
}

void DrawingGrid::SetNewStartAndEnd()
{
    if (m_isSettingSE == 0)
    {
        if (IsSESet())
        {
            m_grid[m_from.y][m_from.x]->state = Node::NodeState::UNCHECK;
            m_grid[m_to.y][m_to.x]->state = Node::NodeState::UNCHECK;
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition();
        int x = mousePos.x / tileW;
        int y = mousePos.y / tileH;

        if ((x >= 0 && x < m_grid[0].size())&& (y >= 0 && y < m_grid.size()))
        {
            if (m_grid[y][x] == nullptr)
                m_grid[y][x] = new Node({ (float)x, (float)y });
            switch (m_isSettingSE)
            {
            case 0:
                m_from = { (float)x,(float)y };
                m_grid[y][x]->state = Node::NodeState::START;
                m_isSettingSE++;
                break;
            case 1:
                m_to = { (float)x,(float)y };
                m_grid[y][x]->state = Node::NodeState::END;
                m_isSettingSE = -1;
                break;
            default:
                break;
            }

        }

    }
}

void DrawingGrid::SetObstaclesByHand()
{
    if (!m_setObstacles)
        return;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition();
        int x = mousePos.x / tileW;
        int y = mousePos.y / tileH;
        if ((x >= 0 && x < m_grid[0].size()) && (y >= 0 && y < m_grid.size()))
        {
            if (m_grid[y][x] == nullptr)
                return;
        }
    }
}

void DrawingGrid::SetWeightByHand()
{
    if (!m_setWeight)
        return;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition();
        int x = mousePos.x / tileW;
        int y = mousePos.y / tileH;
        if ((x >= 0 && x < m_grid[0].size()) && (y >= 0 && y < m_grid.size()))
        {
        }
    }
}

void DrawingGrid::ResetNodes()
{
    m_currentresult = {};
    for (int y = 0; y < m_grid.size(); y++)
    {
        for (int x = 0; x < m_grid[0].size(); x++)
        {
            if (m_grid[y][x] == nullptr)
                continue;
            m_grid[y][x]->Reset();
        }
    }
    m_grid[m_from.y][m_from.x]->state = Node::NodeState::START;
    m_grid[m_to.y][m_to.x]->state = Node::NodeState::END;
}

void DrawingGrid::ResetObstacles()
{
    for (int y = 0; y < m_grid.size(); y++)
    {
        for (int x = 0; x < m_grid[0].size(); x++)
        {
            if (m_grid[y][x] == nullptr)
                m_grid[y][x] = new Node({ (float)x,(float)y });
        }
    }
}

void DrawingGrid::ResetWeight()
{
    for (int y = 0; y < m_grid.size(); y++)
    {
        for (int x = 0; x < m_grid[0].size(); x++)
        {
            if (m_grid[y][x] == nullptr)
                continue;
            m_grid[y][x]->weight = 1;
        }
    }
}

bool rlButton::IsPressed()
{
    Rectangle btnBounds = { position.x, position.y, size.x, size.y };
    if (CheckCollisionPointRec(GetMousePosition(), btnBounds))
    {
        return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }
    return false;
}

void rlButton::DrawRlButton()
{
    Rectangle btnBounds = { position.x, position.y, size.x, size.y };
    DrawRectangleRounded(btnBounds, 2.0f, 1, backGroundColor);
    DrawRectangleRoundedLines(btnBounds, 2.0f, 1, 2.5f,BLACK);

    DrawText(textInButton.c_str(),position.x, position.y, 20,BLACK);
}

