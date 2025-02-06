// DjordjeMaster.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Hypergraph.h"
#include "Unit.h"
#include "FileParser.h"
#include "Population.h"
#include "OutputGenerator.h"
#include <utility>
#include <thread>
#include <ctime>


const std::string demoFilePrefix        = "C:/Users/Djordje/OneDrive/Desktop/demofile";
const std::string populationFilePrefix  = "C:/Users/Djordje/OneDrive/Desktop/InitGen/pop";
const std::string initFilePrefix        = "C:/Users/Djordje/OneDrive/Desktop/Init/";
const std::string outputFilePrefix      = "C:/Users/Djordje/OneDrive/Desktop/Results2/";

const std::string initColumns           = "Alele prob, Max fit, Avg fit, Diversity";
const std::string outputColumns         = "Operator combination, Generation, Plateau counter, Maximum fitness, Average fitness, Diversity, Homogeneity";


void generatePopulations(int _i)
{
    std::string inputLocation   = demoFilePrefix + std::to_string(_i) + ".txt";
    FileParser fileParser       = FileParser(inputLocation);
    Hypergraph graph            = fileParser.getHypergraph();

    for (int popSize = 30; popSize <= 50; popSize += 10)
    {
        for (int i = 0; i < 50; ++i)
        {
            std::string location    = populationFilePrefix + std::to_string(popSize) + "_" + std::to_string(_i) + "_" + std::to_string(i) + ".csv";
            Population population   = Population(graph, popSize, popSize == 50 ? 0.0783 : 0.8, location);

            population.outputGenerator.append(std::to_string(graph.getNumberOfVertices()));
            population.printGeneration(false);
        }
    }
}

void initializationAnalysis(int _popSize, int _i)
{
    std::string inputLocation       = demoFilePrefix + std::to_string(_i) + ".txt";
    FileParser fileParser           = FileParser(inputLocation);
    Hypergraph graph                = fileParser.getHypergraph();
    OutputGenerator outputGenerator = OutputGenerator(initFilePrefix + std::to_string(_popSize) + "/init" + std::to_string(_popSize) + "_" + std::to_string(_i)+".csv");
    outputGenerator.append(initColumns);

    for (double r = 0.767; r <= 0.79; r += 0.0167)
    {
        for (int i = 0; i < 50; ++i)
        {

            Population population = Population(graph, _popSize, r, "");

            int fitSum = 0;

            for (auto unit : population.population)
            {
                if (unit.fitness() > population.maxFitness)
                {
                    population.maxFitness = unit.fitness();
                }
                fitSum += unit.fitness();
            }

            outputGenerator.append(std::to_string(r) + ", " + std::to_string(population.maxFitness) + ", " + std::to_string(fitSum / _popSize) + ", " + std::to_string(std::count_if(population.aleleSum.begin(), population.aleleSum.end(), [population](int i) { return (i < population.population.size()) && (i > 9 * (population.population.size() / 10)); })));
        }
    }

}

void evolvePopulation(int _popSize, int _i)
{    
    std::string inputLocation   = demoFilePrefix + std::to_string(_i) + ".txt";
    FileParser fileParser       = FileParser(inputLocation);
    Hypergraph hypergraph       = fileParser.getHypergraph();

    for (int l = 0; l<1;++l)
    {
        inputLocation                               = populationFilePrefix + std::to_string(_popSize) + "/init" + std::to_string(_popSize) + "_" + std::to_string(_i) + ".csv";
        fileParser                                  = FileParser(inputLocation);
        std::vector<std::vector<int>> initialPop    = fileParser.parsePopulationFile(hypergraph);
        std::string outputLocation                  = outputFilePrefix + std::to_string(_popSize) + "/" + std::to_string(_i) + "/pop" + std::to_string(_popSize) + "_" + std::to_string(_i) + "_" + std::to_string(l) + ".csv";
        Population population                       = Population(hypergraph, initialPop, outputLocation);

        population.outputGenerator.append(outputColumns);

        population.generationLimit              = 80;
        population.plateauLimit                 = 8;
        population.uniformCrossoverProbability  = 0.5;
        population.homogeneityCoef              = 0.8;
    
        for (int i = 0; i < 32; ++i)
        {
            population.setOperatorCombination(i);
            population.evolve();
            population.setPopulation(initialPop);
            population.reset();
        
        }
    }
}


void evolvePopulationParallel(int _popSize)
{    
    auto worker = [&](int _i) 
    {
        std::string inputLocation   = demoFilePrefix + std::to_string(_i) + ".txt";
        FileParser  fileParser      = FileParser(inputLocation);
        Hypergraph  hypergraph      = fileParser.getHypergraph();
        int         start           = 0;
        int         end             = 10;

        for (int l = start; l < end; ++l)
        {   
            inputLocation                                   = populationFilePrefix + std::to_string(_popSize) + "_" + std::to_string(_i) + "_" + std::to_string(l) + ".csv";
            fileParser                                      = FileParser(inputLocation);
            std::vector<std::vector<int>>   initialPop      = fileParser.parsePopulationFile(hypergraph);
            std::string                     outputLocation  = outputFilePrefix + std::to_string(_popSize) + "/" + std::to_string(_i) + "/pop" + std::to_string(_popSize) + "_" + std::to_string(_i) + "_" + std::to_string(l) + ".csv";
            Population                      population      = Population(hypergraph, initialPop, outputLocation);

            population.outputGenerator.append(outputColumns);

            population.generationLimit              = 80;
            population.plateauLimit                 = 8;
            population.uniformCrossoverProbability  = 0.5;
            population.homogeneityCoef              = 0.8;

            for (int i = 0; i < 1; ++i)
            {
                population.setOperatorCombination(i);
                population.evolve();
                population.setPopulation(initialPop);
                population.reset();

            }
        }
    };

    std::vector<std::thread> threads;

    int numThreads = 4;

    for (int i = 0; i < numThreads; ++i) 
    {        
        threads.emplace_back(worker, 3 + i);
    }

    for (auto &t: threads) {
        if (t.joinable()) t.join();
    }

}

int main()
{        
   
    //evolvePopulationParallel(30);
    /*
    for (int i = 3; i < 8; i++)
    {
        generatePopulations(i);
    }
    */
    evolvePopulation(30,3);
}
