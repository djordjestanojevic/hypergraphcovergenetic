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

void generatePopulations(int _i)
{
    std::string inputLocation = "C:/Users/Djordje/OneDrive/Desktop/demofile" + std::to_string(_i) + ".txt";
    FileParser fileParser = FileParser(inputLocation);
    Hypergraph graph = fileParser.getHypergraph();

    for (int popSize = 30; popSize <= 50; popSize += 10)
    {
        for (int i = 5; i < 50; i++)
        {
            std::string location = "C:/Users/Djordje/OneDrive/Desktop/InitGen/pop" + std::to_string(popSize) + "_" + std::to_string(_i) + "_" + std::to_string(i) + ".csv";
            Population population = Population(graph, popSize, popSize == 50 ? 0.0783 : 0.8, location);

            population.outputGenerator.append(std::to_string(graph.getVertices().size()));
            population.printGeneration(false);
        }
    }
}

void initializationAnalysis()
{
    FileParser fileParser = FileParser("C:/Users/Djordje/OneDrive/Desktop/demofile7.txt");
    Hypergraph graph = fileParser.getHypergraph();

    OutputGenerator outputGenerator = OutputGenerator("C:/Users/Djordje/OneDrive/Desktop/Init/50/init50_1494_0775.csv");
    outputGenerator.append("Alele prob, Max fit, Avg fit, Diversity");

    for (double r = 0.767; r <= 0.79; r += 0.0167)
    {
        for (int i = 0; i < 50; i++)
        {

            Population population = Population(graph, 50, r, "");

            int fitSum = 0;

            for (auto unit : population.population)
            {
                if (unit.fitness() > population.maxFitness)
                {
                    population.maxFitness = unit.fitness();
                }
                fitSum += unit.fitness();
            }

            outputGenerator.append(std::to_string(r) + ", " + std::to_string(population.maxFitness) + ", " + std::to_string(fitSum / 50) + ", " + std::to_string(std::count_if(population.aleleSum.begin(), population.aleleSum.end(), [population](int i) { return (i < population.population.size()) && (i > 9 * (population.population.size() / 10)); })));

        }
    }

}

void evolvePopulation()
{    
    FileParser fileParser = FileParser("C:/Users/Djordje/OneDrive/Desktop/demofile4.txt");
    Hypergraph graph = fileParser.getHypergraph();
    for (int l = 0; l<5;l++)
    {
        fileParser = FileParser("C:/Users/Djordje/OneDrive/Desktop/InitGen/pop30_4_"+std::to_string(l) + ".csv");
        std::vector<std::vector<int>> initialPop = fileParser.parsePopulationFile(graph);
        Population population = Population(graph, initialPop, "C:/Users/Djordje/OneDrive/Desktop/Results/30/4/pop30_4_" + std::to_string(l) + ".csv");

        population.outputGenerator.append("Operator combination, Generation, Plateau counter, Maximum fitness, Average fitness, Diversity, Homogeneity");
        population.generationLimit = 80;
        population.plateauLimit = 8;
        population.uniformCrossoverProbability = 0.5;
        population.homogeneityCoef = 0.8;
    
        for (int i = 0; i < 32; i++)
        {
            population.setOperatorCombination(i);
            population.evolve();
            population.setPopulation(initialPop);
            population.reset();
        
        }
    }
}

int main()
{        
    //FileParser fileParser = FileParser("C:/Users/Djordje/OneDrive/Desktop/demofile7.txt");
    //Hypergraph graph = fileParser.getHypergraph();
    
    evolvePopulation();
    /*
    for (int i = 3; i < 8; i++)
    {
        generatePopulations(i);
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
