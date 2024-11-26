#pragma once
#include<vector>
#include<utility>
#include"Hypergraph.h"
#include"Unit.h"
#include"OutputGenerator.h"
#include<random>
class Population
{
public:
	Population();
	Population(Hypergraph _hypergraph, int _populationSize, double _alleleProbability);
	
	void createPopulation();
	void evolve();

	std::pair<Unit, Unit> selectParents();
	std::pair<Unit, Unit> selectionRoulette();
	Unit selectionTournament();
	
	std::pair<Unit, Unit> crossover(std::pair<Unit, Unit> _parents);
	std::pair<Unit, Unit> multipointCrossover(std::pair<Unit, Unit> _parents);
	std::pair<Unit, Unit> uniformCrossover(std::pair<Unit, Unit> _parents);

	void addChildren(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children);
	void addEntire(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children);
	void addElite(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children);
	void replaceGeneration();

	void mutateAndAdjust(std::pair<Unit, Unit>& _children);
	
	bool stopCriterion();
	bool iterationCriterion();
	bool plateauCriterion();
	bool valueCriterion();

	int getOperatorCombination();
	void setOperatorCombination(int _combination);

	void printGeneration();


	std::vector<Unit>	population;
	std::vector<Unit>	newPopulation;
	Unit				bestUnit;
	int					generationLimit, plateauLimit, valueLimit;
	int					k, crossoverPoints;
	double				uniformCrossoverProbability;
	OutputGenerator		outputGenerator;
private:
	Hypergraph			hypergraph;
	int					populationSize;
	int					generation, plateauCounter;
	int					maxFitness;
	double				alleleProbability;
	int					operatorCombination;
};

