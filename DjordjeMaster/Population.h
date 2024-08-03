#pragma once
#include<vector>
#include<utility>
#include"Hypergraph.h"
#include"Unit.h"
#include<random>
class Population
{
public:
	Population();
	Population(Hypergraph _hypergraph, int _operatorCombination, int _populationSize, double _alleleProbability);
	
	void createPopulation();
	void evolve();

	std::pair<Unit, Unit> selectParents();
	std::pair<Unit, Unit> selectionRoulette();
	Unit selectionTournament();
	
	std::pair<Unit, Unit> crossover(std::pair<Unit, Unit> _parents);
	std::pair<Unit, Unit> multipointCrossover(std::pair<Unit, Unit> _parents);
	std::pair<Unit, Unit> uniformCrossover(std::pair<Unit, Unit> _parents);

	void replaceGeneration(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children);
	void replaceEntire(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children);
	void replaceElite(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children);

	bool stopCriterion();
	bool iterationCriterion();
	bool plateauCriterion();
	bool valueCriterion();


	std::vector<Unit>	population;
	
private:
	Hypergraph			hypergraph;
	int					populationSize;
	int					generation, plateauCounter;
	int					generationLimit, plateauLimit, valueLimit;
	int					maxFitness;
	int					k, crossoverPoints;
	double				alleleProbability, uniformCrossoverProbability;
	int					operatorCombination;
};

