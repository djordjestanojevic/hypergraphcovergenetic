// DjordjeMaster.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include"Hypergraph.h"
#include"Unit.h"
#include"FileParser.h"
#include"Population.h"
#include"OutputGenerator.h"
#include<utility>

int main()
{
    //std::vector<int> vertices = {0, 1, 2, 3, 4, 5,6,7,8,9};
    //std::vector<std::vector<int>> hyperedges = { {0},{0,1}, {0,2,3},{1},{0,4,5}, {1,6},{6},{6,7},{6,8},{7},{9,3},{8}, {8,5} };
    //Hypergraph graph = Hypergraph(vertices, hyperedges);
    
    

    FileParser fileParser = FileParser("C:/Users/Djordje/OneDrive/Desktop/demofile2.txt");
    //std::vector<int> array = { 1,0,0,1,1,0 };
    Hypergraph graph = fileParser.getHypergraph();
    

    Population population = Population(graph, 6, 0.3 );
    
    population.generationLimit = 20;
    population.plateauLimit = 5;
    population.valueLimit = 4;
    population.uniformCrossoverProbability = 0.5;

    std::vector<int> combinations = {8,23,37,67};
    for (auto i: combinations)
    {
        population.setOperatorCombination(i);
        population.evolve();
        break;
    }
    
    for (auto v : population.bestUnit.unit)
    {
        std::cout << v << " ";
    }

    std::cout << "\nFitness: " << population.bestUnit.fitness() << " ";
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
