#include "Population.h"
#include<numeric>
#include<time.h>
#include<algorithm>

/// <summary>
/// Constructor for Population class
/// </summary>
/// <param name="_hypergraph">Hypergraph</param>
/// <param name="_populationSize">int</param>
/// <param name="_alleleProbability">int</param>
Population::Population(Hypergraph _hypergraph, int _operationCombination, int _populationSize, double _alleleProbability)
	: hypergraph(_hypergraph)
	, operatorCombination(_operationCombination)
	, populationSize(_populationSize)
	, alleleProbability(_alleleProbability)
	, generation(0)
	, plateauCounter(0)
	, plateauLimit(0)
	, generationLimit(0)
	, maxFitness(0)
	, valueLimit(_hypergraph.getVertices().size())
{
	for (int i = 0; i < populationSize; i++)
	{
		population.push_back(Unit(hypergraph, alleleProbability));
	}
}

/// <summary>
/// Roulette selection operator
/// </summary>
/// <returns></returns>
std::pair<Unit, Unit> Population::selectionRoulette()
{
	int theSum = std::accumulate(population.begin(), population.end(), 0.0, [](double _sum, Unit _unit) {return _sum + _unit.fitness(); });

	std::random_device					device;
	std::mt19937						generator(device());
	std::uniform_int_distribution<>		distribution(0, theSum);


	int r1 = distribution(generator);
	int r2 = distribution(generator);

	int i = 0;
	int n = hypergraph.getVertices().size();

	int		currentSum1 = 0; 
	int		currentSum2 = 0;
	
	int		parent1 = 0;
	int		parent2 = 0;

	for (auto currentUnit : population)
	{
		++i;
		if (currentSum1 < r1)
		{
			currentSum1 += currentUnit.fitness();

			if (currentSum1 < r1)
			{
				parent1 = i;
			}
		}
		if (currentSum2 < r2)
		{
			currentSum2 += currentUnit.fitness();

			if (currentSum2 < r2)
			{
				parent2 = i;
			}
		}
		if ((currentSum1 >= r1) && (currentSum2 >= r2))
		{
			break;
		}
	}
	population[parent1].index = parent1;
	population[parent2].index = parent2;
	return std::make_pair(population[parent1], population[parent2]);
}


/// <summary>
/// Tournament selection operator
/// </summary>
/// <param name="_k">int</param>
/// <returns>Unit</returns>
Unit Population::selectionTournament()
{
	double	currentMax = 0;
	int		currentIndex = 0;
	
	std::random_device					device;
	std::mt19937						generator(device());
	std::uniform_int_distribution<>		distribution(0, hypergraph.getVertices().size()-1);


	for (int i = 0; i < k; i++)
	{
		int index = distribution(generator);
		if (population[index].fitness() > currentMax)
		{
			currentMax		= population[index].fitness();
			currentIndex	= index;
		}
	}
	population[currentIndex].index = currentIndex;

	return population[currentIndex];
}

void Population::evolve() 
{
	while (stopCriterion())
	{
		//std::pair<Unit, Unit> parents, children;
		for (int i = 0; i < populationSize / 2; i++)
		{
			std::pair<Unit, Unit> parents = selectParents();
			std::pair<Unit, Unit> children = crossover(parents);

			replaceGeneration(parents, children);
		}
	}
}

void Population::replaceEntire(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children)
{
	population[_parents.first.index] = _children.first;
	population[_parents.second.index] = _children.second;
}
void Population::replaceElite(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children)
{
	Unit parent1 = _parents.first;
	Unit parent2 = _parents.second;

	Unit child1 = _children.first;
	Unit child2 = _children.second;

	std::vector<Unit> array = { parent1, parent2, child1, child2 };
	std::sort(array.begin(), array.end(), [](Unit _unit1, Unit _unit2) {return _unit1.fitness() > _unit2.fitness(); });

	population[parent1.index] = array[0];
	population[parent2.index] = array[1];

}

void Population::replaceGeneration(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children)
{
	if (operatorCombination % 12 > 5)
		return replaceEntire(_parents, _children);
	else
		return replaceElite(_parents, _children);
}

std::pair<Unit, Unit> Population::selectParents()
{
	if (operatorCombination % 1)
		return selectionRoulette();

	Unit parent1 = selectionTournament();
	Unit parent2 = selectionTournament();

	return std::make_pair(parent1, parent2);
}

bool Population::stopCriterion()
{
	if (operatorCombination % 3 == 0)
		return iterationCriterion();

	if (operatorCombination % 3 == 1)
		return plateauCriterion();
	
	return valueCriterion();
}


bool Population::valueCriterion()
{
	return maxFitness < valueLimit;
}


/// <summary>
/// Uniform crossover operator
/// </summary>
/// <param name="_parent1">Unit</param>
/// <param name="_parent2">Unit</param>
/// <param name="_p">double</param>
/// <returns>std::pair<Unit, Unit></returns>
std::pair<Unit, Unit> Population::uniformCrossover(std::pair<Unit, Unit> _parents)
{
	std::vector<int>					child1;
	std::vector<int>					child2;
	double								r;
	std::random_device					device;
	std::mt19937						generator(device());
	std::uniform_real_distribution<>	distribution(0, 1.0);

	Unit parent1 = _parents.first;
	Unit parent2 = _parents.second;

	for (int i = 0; i < parent1.unit.size(); i++)
	{
		r = distribution(generator);

		if (r > uniformCrossoverProbability)
		{
			child1.push_back(parent1.unit[i]);
			child2.push_back(parent2.unit[i]);
		}
		else
		{
			child1.push_back(parent2.unit[i]);
			child2.push_back(parent1.unit[i]);
		}
	}

	return std::make_pair(Unit(hypergraph, child1), Unit(hypergraph, child2));
}


/// <summary>
/// Multipoint crossover operator
/// </summary>
/// <param name="_parent1">Unit</param>
/// <param name="_parent2">Unit</param>
/// <param name="_n">int</param>
/// <returns>std::pair<Unit, Unit></returns>
std::pair<Unit, Unit> Population::multipointCrossover(std::pair<Unit, Unit> _parents)
{
	std::vector<int>	indices;
	std::vector<int>	child1;
	std::vector<int>	child2;
	int					currentIndex = 0;
	int					i;

	std::random_device					device;
	std::mt19937						generator(device());
	std::uniform_int_distribution<>		distribution(0, hypergraph.getVertices().size()-1);

	Unit parent1 = _parents.first;
	Unit parent2 = _parents.second;

	bool indicator = true;

	for (i = 0; i < crossoverPoints; i++)
	{
		indices[i] = distribution(generator);
	}

	std::sort(indices.begin(), indices.end());

	for (i=0 ; i< parent1.unit.size() && currentIndex<crossoverPoints; i++  )
	{
		if (indicator) 
		{
			child1[i] = parent1.unit[i];
			child2[i] = parent2.unit[i];
		}
		else
		{
			child1[i] = parent2.unit[i];
			child2[i] = parent1.unit[i];
		}

		while (i+1 == indices[currentIndex])
		{
			indicator = not indicator;
			currentIndex++;
		}
	}
	for (; i < parent1.unit.size(); i++)
	{
		if (indicator)
		{
			child1[i] = parent1.unit[i];
			child2[i] = parent2.unit[i];
		}
		else
		{
			child1[i] = parent2.unit[i];
			child2[i] = parent1.unit[i];
		}
	}


	return std::make_pair(Unit(hypergraph,child1), Unit(hypergraph,child2));
}


/// <summary>
/// Plateau stopping criterion
/// </summary>
/// <returns>bool</returns>
bool Population::plateauCriterion()
{
	return plateauCounter < plateauLimit;
}

/// <summary>
/// Iteration stopping criterion
/// </summary>
/// <returns>bool</returns>
bool Population::iterationCriterion()
{
	return generation < generationLimit;
}


std::pair<Unit, Unit> Population::crossover(std::pair<Unit, Unit> parents)
{
	if (operatorCombination > 11)
	{
		return multipointCrossover(parents);
	}
	else
	{
		return uniformCrossover(parents);
	}
}