#pragma once
#include<vector>
#include<utility>
#include"Hypergraph.h"
#include"Unit.h"
#include"OutputGenerator.h"
#include<random>
#include<string>

class Population
{
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Population() = delete;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_hypergraph">Hypergraph</param>
	/// <param name="_population">std::vector<std::vector<int>></param>
	/// <param name="_location">std::string</param>
	Population(Hypergraph _hypergraph, std::vector<std::vector<int>> _population, std::string _location);

	/// <summary>
	/// Constructor for Population class
	/// </summary>
	/// <param name="_hypergraph">Hypergraph</param>
	/// <param name="_populationSize">int</param>
	/// <param name="_alleleProbability">double</param>
	/// <param name="_location">std::string</param>
	Population(Hypergraph _hypergraph, int _populationSize, double _alleleProbability, std::string _location);

	/// <summary>
	/// Runs evolution
	/// </summary>
	void evolve();

	/// <summary>
	/// Selects parents
	/// </summary>
	/// <returns>std::pair<Unit, Unit></returns>
	std::pair<Unit, Unit> selectParents();

	/// <summary>
	/// Roulette selection operator
	/// </summary>
	/// <returns>std::pair<Unit, Unit></returns>
	std::pair<Unit, Unit> selectionRoulette();

	/// <summary>
	/// Tournament selection operator
	/// </summary>
	/// <param name="_k">int</param>
	/// <returns>Unit</returns>
	Unit selectionTournament();
	
	/// <summary>
	/// Performs crossover of selected units
	/// </summary>
	/// <param name="_parents">std::pair<Unit, Unit></param>
	/// <returns>std::pair<Unit, Unit></returns>
	std::pair<Unit, Unit> crossover(std::pair<Unit, Unit> _parents);

	/// <summary>
	/// Multipoint crossover operator
	/// </summary>
	/// <param name="_parents">std::pair<Unit, Unit></param>
	/// <returns>std::pair<Unit, Unit></returns>
	std::pair<Unit, Unit> multipointCrossover(std::pair<Unit, Unit> _parents);

	/// <summary>
	/// Uniform crossover operator
	/// </summary>
	/// <param name="_parents">std::pair<Unit, Unit></param>
	/// <returns>std::pair<Unit, Unit></returns>
	std::pair<Unit, Unit> uniformCrossover(std::pair<Unit, Unit> _parents);

	/// <summary>
	/// Adds children to current generation
	/// </summary>
	/// <param name="_parents">std::pair<Unit, Unit></param>
	/// <param name="_children">std::pair<Unit, Unit></param>
	void addChildren(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children);

	/// <summary>
	/// Adds only children to current generation
	/// </summary>
	/// <param name="_parents">std::pair<Unit, Unit></param>
	/// <param name="_children">std::pair<Unit, Unit></param>
	void addEntire(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children);

	/// <summary>
	/// Adds best two units out of parents/children to current generation
	/// </summary>
	/// <param name="_parents">std::pair<Unit, Unit></param>
	/// <param name="_children">std::pair<Unit, Unit></param>
	void addElite(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children);

	/// <summary>
	/// Replaces previous generation with new one
	/// </summary>
	void replaceGeneration();

	/// <summary>
	/// Mutates units and adjusts them to cover hypergraph if needed
	/// </summary>
	/// <param name="_children">std::pair<Unit, Unit></param>
	void mutateAndAdjust(std::pair<Unit, Unit>& _children);
	
	/// <summary>
	/// Checks whether stop criterion is met
	/// </summary>
	/// <returns>bool</returns>
	bool stopCriterion();

	/// <summary>
	/// Iteration stopping criterion
	/// </summary>
	/// <returns>bool</returns>
	bool iterationCriterion();

	/// <summary>
	/// Plateau stopping criterion
	/// </summary>
	/// <returns>bool</returns>
	bool plateauCriterion();
	
	/// <summary>
	/// Population homogeneity criterion
	/// </summary>
	/// <returns>bool</returns>
	bool homogeneityCriterion();

	/// <summary>
	/// Operator combination getter
	/// </summary>
	/// <returns>int</returns>
	int getOperatorCombination();

	/// <summary>
	/// Operator combination setter
	/// </summary>
	/// <param name="_combination">int</param>
	void setOperatorCombination(int _combination);

	/// <summary>
	/// Resets population after evolution
	/// </summary>
	void reset();

	/// <summary>
	/// Population setter
	/// </summary>
	/// <param name="_array">std::vector<std::vector<int>></param>
	void setPopulation(std::vector<std::vector<int>> _array);

	/// <summary>
	/// Prints generation to output file
	/// </summary>
	/// <param name="_statistics">bool</param>
	void printGeneration(bool _statistics);

	/// <summary>
	/// Calculates population diversity
	/// </summary>
	void calculateDiversity();

	std::vector<Unit>	population;
	std::vector<Unit>	newPopulation;
	std::vector<int>	aleleSum;
	Unit				bestUnit;
	int					generationLimit, plateauLimit, valueLimit;
	int					k, crossoverPoints;
	double				uniformCrossoverProbability, homogeneityCoef;
	OutputGenerator		outputGenerator;
	int					maxFitness;
private:
	static std::mt19937	generator;
	Hypergraph			hypergraph;
	int					populationSize;
	int					generation, plateauCounter;
	double				alleleProbability;
	double				mutationParameter;
	int					operatorCombination;
};

