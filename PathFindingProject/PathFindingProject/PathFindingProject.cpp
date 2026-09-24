// PathFindingProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DijkstraAlgo.h"
#include "AStarAlgo.h"

#include "DrawingGrid.h"
#include "raylib.h"

int main()
{

    //DijkstraAlgo dijkstra = DijkstraAlgo();

    //std::vector<std::vector<int>> table =
    //{
    //    {0  ,10 ,15 ,inf,30 ,inf,inf},
    //    {inf,0  ,inf,inf,inf,57 ,inf},
    //    {15 ,inf,0  ,16 ,inf,inf,52 },
    //    {inf,inf,13 ,0  ,inf,inf,inf},
    //    {30 ,inf,inf,inf,0  ,11 ,34 },
    //    {inf,49 ,inf,inf,12 ,0  ,inf},
    //    {inf,inf,63 ,inf,35 ,inf,0  }
    //};

    //dijkstra.SetGraph(table);
    //dijkstra.SetNodeNames({ "A", "B" ,"C" ,"D" ,"E" ,"F" ,"G" });
    //std::vector<DijkstraAlgo::DijkstraSteps> allOut = dijkstra.FindCheaperPath("C");

    //Node* start = new Node({ 1,5 });
    //Node* end   = new Node({ 5,1 });
    //std::vector<std::vector<Node*>> grid =
    //{
    //    {new Node({0,0}),new Node({1,0}) ,new Node({2,0}) ,new Node({3,0}),new Node({4,0}) ,new Node({5,0}),new Node({6,0}) },
    //    {new Node({0,1}),new Node({1,1}) ,new Node({2,1}) ,nullptr        ,new Node({4,1}) ,end            ,new Node({6,1}) },
    //    {new Node({0,2}),new Node({1,2}) ,new Node({2,2}) ,nullptr        ,nullptr         ,nullptr        ,nullptr         },
    //    {new Node({0,3}),new Node({1,3}) ,new Node({2,3}) ,new Node({3,3}),new Node({4,3}) ,new Node({5,3}),new Node({6,3}) },
    //    {new Node({0,4}),new Node({1,4}) ,new Node({2,4}) ,new Node({3,4}),new Node({4,4}) ,new Node({5,4}),new Node({6,4}) },
    //    {new Node({0,5}),start           ,new Node({2,5}) ,new Node({3,5}),new Node({4,5}) ,new Node({5,5}),new Node({6,5}) },
    //    {new Node({0,6}),new Node({1,6}) ,new Node({2,6}) ,new Node({3,6}),new Node({4,6}) ,new Node({5,6}),new Node({6,6}) },
    //};

    //AStarAlgo Astar = AStarAlgo();
    //Astar.SetGrid(grid);
    //AStarAlgo::AStarResult res = Astar.FindCheaperPath(start,end);
    //std::cout << "Path : \n";
    //std::cout << "Path Cost : " + std::to_string(res.pathLenght) + " \n";
    //std::cout << "steps count : " + std::to_string(res.pathStep) + " \n";
    //std::cout << "Calculation steps: " + std::to_string(res.calculSteps) + " \n";
    //std::cout << "Node Steps : \n";
    //for (Node* n : res.nodeSteps)
    //{
    //    std::cout << n->position.ToString() << "\n";
    //}

    //std::cout << "G -> B : " << value;

    DrawingGrid grid = DrawingGrid();
    grid.InitGridWindow(1000, 1000, "Dijkstra* PathFinding");
    grid.ChooseAlgorithm(DrawingGrid::AvailableAlgorithm::A_STAR);
    grid.InitGrid(50,50);
    //grid.SetObstacles({ {1,10},{3,2},{4,2},{5,2},{6,2}});

    grid.OpenGridWindow();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
