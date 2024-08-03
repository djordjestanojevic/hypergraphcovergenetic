// DjordjeMaster.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include"Hypergraph.h"
#include"Unit.h"
#include"Population.h"
#include<utility>

int main()
{/*
    std::vector<int> vertices = {0, 1, 2, 3, 4, 5};
    std::vector<std::vector<int>> hyperedges = { {0,1,2},{0,3},{3,4,5}, {2,3},{0,1,5} };
    Hypergraph graph = Hypergraph(vertices, hyperedges);

    std::vector<int> array = { 1,0,0,1,1,0 };
    Population population = Population(graph, 0, 5, 0.3);

    std::cout << "Population \n";

    for (auto unit : population.population)
    {
        for (auto vertex : unit.unit)
        {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }


    std::cout << "Parents: \n";
    std::pair<Unit, Unit> pair = population.selectionRoulette();
    Unit parent1 = pair.first;
    Unit parent2 = pair.second;
    for (auto vertex : parent1.unit)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    for (auto vertex : parent2.unit)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    
    //pair = population.uniformCrossover(parent1, parent2, 0.5);

    Unit child1 = pair.first;
    Unit child2 = pair.second;

    
    std::cout << "Child1 after crossover \n";
    for (auto vertex : child1.unit)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    child1.adjustToAllowed();


    std::cout << "Child1 after adjustment\n";
    for (auto vertex : child1.unit)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;



    std::cout << "Child2 after crossover \n";
    for (auto vertex : child2.unit)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    std::cout << "Child2 after adjustment\n";

    child2.adjustToAllowed();
    for (auto vertex : child2.unit)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    child1.mutate(1.0);
    std::cout << "Child1 after mutation\n";

    for (auto vertex : child1.unit)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    
    child1.adjustToAllowed();


    std::cout << "Child1 after adjustment\n";

    for (auto vertex : child1.unit)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;



    // inicijalizuj sve
    // pokreni evoluciju za sve brojeve (svaki broj jedna kombinacija)

    for (int i = 0; i < 12; i++)
    {

    }
    */
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
