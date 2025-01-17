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
Population::Population(Hypergraph _hypergraph, int _populationSize, double _alleleProbability, std::string _outputLocation)
	: hypergraph(_hypergraph)
	, operatorCombination(0)
	, populationSize(_populationSize)
	, alleleProbability(_alleleProbability)
	, generation(0)
	, plateauCounter(0)
	, plateauLimit(0)
	, generationLimit(0)
	, maxFitness(0)
	, valueLimit(_hypergraph.getVertices().size())
	, bestUnit(_hypergraph, 1)
	, crossoverPoints(0)
	, uniformCrossoverProbability(0)
	, k(0)
	, outputGenerator(_outputLocation)
{
	for (int i = 0; i < populationSize; i++)
	{
		population.push_back(Unit(hypergraph, alleleProbability));
	}
	for (int i = 0; i < _hypergraph.getVertices().size(); i++)
	{
		aleleSum.push_back(0);
	}

	calculateDiversity();
}

Population::Population(Hypergraph _hypergraph, std::vector<std::vector<int>> _population, std::string _outputLocation)
	: hypergraph(_hypergraph)
	, operatorCombination(0)
	, alleleProbability(0)
	, generation(0)
	, plateauCounter(0)
	, plateauLimit(0)
	, generationLimit(0)
	, maxFitness(0)
	, valueLimit(_hypergraph.getVertices().size())
	, bestUnit(_hypergraph, 1)
	, crossoverPoints(0)
	, uniformCrossoverProbability(0)
	, k(0)
	, outputGenerator(_outputLocation)
	, populationSize(_population.size())
{
	for (auto unit : _population)
	{
		population.push_back(Unit(_hypergraph, unit));
	}

	for (int i = 0; i < _hypergraph.getVertices().size(); i++)
	{
		aleleSum.push_back(0);
	}

	calculateDiversity();
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
	/*
	outputGenerator.append("Roulette selection " + std::to_string(r1) + ", " + std::to_string(r2));
	outputGenerator.append(population[parent1], "Selected parent: " + std::to_string(parent1) + " ");
	outputGenerator.append(population[parent2], "Selected parent: " + std::to_string(parent2) + " ");
	*/
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
	std::uniform_int_distribution<>		distribution(0, populationSize-1);


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

	//outputGenerator.append(std::to_string(k) + "- tournament selection");
	//outputGenerator.append(population[currentIndex],"Selected parent: " + std::to_string(currentIndex) + " ");

	return population[currentIndex];
}


void Population::calculateDiversity()
{
	for (auto unit : population)
	{
		std::transform(aleleSum.begin(), aleleSum.end(), unit.unit.begin(), aleleSum.begin(), [](int a, int b) {return a + b; });
	}

}


void Population::printGeneration(bool _statistics = false)
{	

	int theSum = std::accumulate(population.begin(), population.end(), 0.0, [](double _sum, Unit _unit) {return _sum + _unit.fitness(); });
	int diverseCounter = std::count_if(aleleSum.begin(), aleleSum.end(), [this](int i) { return (i < populationSize) && (i > 9 * (population.size() / 10)); });
	int homogeneityCounter = std::count_if(aleleSum.begin(), aleleSum.end(), [this](int i) { return (i == populationSize) || (i==0); });
	
	if (_statistics)
	{
		outputGenerator.append(std::to_string(operatorCombination) + "," + std::to_string(generation) + "," + std::to_string(plateauCounter) + "," + std::to_string(maxFitness) + "," + std::to_string((double)theSum/populationSize) + "," + std::to_string((double)diverseCounter/hypergraph.numberOfVertices) + "," + std::to_string((double)homogeneityCounter / hypergraph.numberOfVertices));
	}

}

void Population::evolve() 
{
	while (!stopCriterion())
	{
		generation++;
		plateauCounter++;
		
		printGeneration(true);

		for (int i = 0; i < populationSize / 2; i++)
		{
			std::pair<Unit, Unit> parents = selectParents();
			std::pair<Unit, Unit> children = crossover(parents);

			mutateAndAdjust(children);

			if (children.first.fitness() > maxFitness)
			{
				bestUnit = children.first;
				maxFitness = children.first.fitness();
				plateauCounter = 0;
			}
			if (children.second.fitness() > maxFitness)
			{
				bestUnit = children.second;
				maxFitness = children.second.fitness();
				plateauCounter = 0;
			}

			addChildren(parents, children);
		}

		replaceGeneration();
	}
}

void Population::addEntire(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children)
{
	newPopulation.push_back(_children.first);
	newPopulation.push_back(_children.second);

	//outputGenerator.append("Full replacement");
}

void Population::reset()
{
	generation = 0;
	plateauCounter = 0;
	maxFitness = 0;
	plateauLimit = 8;
	homogeneityCoef = 0.8;
	std::transform(aleleSum.begin(), aleleSum.end(), aleleSum.begin(), [](int a) {return 0; });
	calculateDiversity();
}

void Population::setPopulation(std::vector<std::vector<int>> _array)
{
	for (int i = 0; i < populationSize; i++)
	{
		population[i] = Unit(hypergraph, _array[i]);
	}
}

void Population::addElite(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children)
{
	Unit parent1 = _parents.first;
	Unit parent2 = _parents.second;

	Unit child1 = _children.first;
	Unit child2 = _children.second;

	std::vector<Unit> array = { parent1, parent2, child1, child2 };
	std::sort(array.begin(), array.end(), [](Unit _unit1, Unit _unit2) {return _unit1.fitness() > _unit2.fitness(); });

	newPopulation.push_back(array[0]);
	newPopulation.push_back(array[1]);

	//outputGenerator.append(array[0], "New gen1: ");
	//outputGenerator.append(array[1], "New gen2: ");
}

void Population::addChildren(std::pair<Unit, Unit> _parents, std::pair<Unit, Unit> _children)
{
	if (operatorCombination % 2)
		return addEntire(_parents, _children);
	else
		return addElite(_parents, _children);
}

void Population::replaceGeneration()
{
	population = newPopulation;
	newPopulation = {};
	std::transform(aleleSum.begin(), aleleSum.end(), aleleSum.begin(), [](int a) {return 0; });
	calculateDiversity();
}

std::pair<Unit, Unit> Population::selectParents()
{
	if (operatorCombination < 8)
		return selectionRoulette();

	if (operatorCombination < 24)
	{
		k = operatorCombination < 16 ? 2 : 3;
		Unit parent1 = selectionTournament();
		Unit parent2 = selectionTournament();

		return std::make_pair(parent1, parent2);
	}

	if (generation > generationLimit / 2)
	{
		return selectionRoulette();
	}
	else
	{
		k = 2;
		Unit parent1 = selectionTournament();
		Unit parent2 = selectionTournament();

		return std::make_pair(parent1, parent2);
	

	}
}

bool Population::stopCriterion()
{
	if (iterationCriterion() && (generation % 10 == 0))
	{
		plateauLimit--;
	}
	return plateauCriterion() && (iterationCriterion() || homogeneityCriterion()) ;
}

bool Population::homogeneityCriterion()
{
	bool ret = std::count_if(aleleSum.begin(), aleleSum.end(), [this](int i) { return (i == populationSize) || (i == 0); }) > homogeneityCoef * hypergraph.numberOfVertices;
	homogeneityCoef -= 0.05;
	return ret;
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
	/*
	outputGenerator.append("Uniform crossover");
	outputGenerator.append(child1, "Child 1: ");
	outputGenerator.append(child2, "Child 2: ");
	*/

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
		indices.push_back(distribution(generator));
	}

	std::sort(indices.begin(), indices.end());

	while ((currentIndex < crossoverPoints) && (indices[currentIndex] == 0))
	{
		indicator = not indicator;
		currentIndex++;
	}

	for (i=0 ; i< parent1.unit.size() && currentIndex<crossoverPoints; i++  )
	{
		if (indicator) 
		{
			child1.push_back(parent1.unit[i]);
			child2.push_back(parent2.unit[i]);
		}
		else
		{
			child1.push_back(parent2.unit[i]);
			child2.push_back(parent1.unit[i]);
		}

		while ((currentIndex < crossoverPoints) && (i+1 == indices[currentIndex]))
		{
			indicator = not indicator;
			currentIndex++;
		}
	}
	for (; i < parent1.unit.size(); i++)
	{
		if (indicator)
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
	/*
	outputGenerator.append(std::to_string(crossoverPoints) + "- point crossover: " + std::to_string(indices[0]) + ", " + (crossoverPoints==1? "":std::to_string(indices[1])));
	outputGenerator.append(child1, "Child 1: ");
	outputGenerator.append(child2, "Child 2: ");
	*/
	return std::make_pair(Unit(hypergraph,child1), Unit(hypergraph,child2));
}


/// <summary>
/// Plateau stopping criterion
/// </summary>
/// <returns>bool</returns>
bool Population::plateauCriterion()
{
	return plateauCounter >= plateauLimit;
}

/// <summary>
/// Iteration stopping criterion
/// </summary>
/// <returns>bool</returns>
bool Population::iterationCriterion()
{
	return generation >= generationLimit;
}


int Population::getOperatorCombination()
{
	return operatorCombination;
}

void Population::setOperatorCombination(int _combination)
{
	operatorCombination = _combination;
}

std::pair<Unit, Unit> Population::crossover(std::pair<Unit, Unit> parents)
{
	if (operatorCombination % 8 < 4)
	{
		crossoverPoints = 2;
		return multipointCrossover(parents);
	}
	else
	{
		return uniformCrossover(parents);
	}	
}


void Population::mutateAndAdjust(std::pair<Unit, Unit>& _children)
{
	mutationParameter = operatorCombination % 4 < 2 ? 0.2 : 0.25;

	if (_children.first.mutate(mutationParameter))
	{
	//	outputGenerator.append(_children.first, "Child 1 mutated");
	}
	if(_children.first.adjustToAllowed())
	{
		//outputGenerator.append(_children.first, "Child 1 adjusted");
	}

	if (_children.second.mutate(mutationParameter))
	{
		//outputGenerator.append(_children.second, "Child 2 mutated");
	}

	if (_children.second.adjustToAllowed())
	{
		//outputGenerator.append(_children.second, "Child 2 adjusted");
	}
		
}