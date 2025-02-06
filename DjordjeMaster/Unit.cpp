#include "Unit.h"
#include<numeric>

std::mt19937 Unit::generator(std::random_device{}());

Unit::Unit(Hypergraph _hypergraph, double _alleleProbability):
	hypergraph(_hypergraph),
	alleleProbability(_alleleProbability)
{
	std::uniform_real_distribution<>	distribution(0, 1.0);

	for (int i = 0; i < _hypergraph.getNumberOfVertices(); ++i)
	{
		double r = distribution(generator);
		unit.push_back(r < _alleleProbability ? 1: 0);
	}

	adjustToAllowed();
}

/// <summary>
/// Mutation operator
/// </summary>
/// <param name="_r">double</param>
bool Unit::mutate(double _r)
{
	std::uniform_real_distribution<>	distribution(0, 1.0);
	std::uniform_int_distribution<>		intDistribution(0,(int) unit.size() - 1);
	double								r = distribution(generator);
	bool ret = false;

	if (r < _r)
	{
		int index = intDistribution(generator);
		unit[index] = 1 - unit[index];
		ret = true;
	}

	return ret;
}

Unit::Unit(Hypergraph _hypergraph, std::vector<int> _array):
	hypergraph(_hypergraph),
	unit(_array),
	alleleProbability(0.0)
{
}

/// <summary>
/// Modifies unit to allowed set
/// </summary>
bool Unit::adjustToAllowed()
{	
	int i = 0;
	int maxDegreeIndex = hypergraph.getVerticesByDegrees()[0];

	bool ret = false;
	// For any hypergraph without isolated nodes with n vertices, any combination of n-1 vertices will result in a hyperedge cover
	// so the situation where all vertices are part of cover is impossible and index could not go out of bounds

	while (!hypergraph.isCovering(unit))
	{		
		if (!unit[maxDegreeIndex])
		{
			unit[hypergraph.getVerticesByDegrees()[i]] = 1;		
			ret = true;
		}
		++i;
		maxDegreeIndex = hypergraph.getVerticesByDegrees()[i];
	}

	return ret;
}

int Unit::fitness()
{
	return (int) unit.size() - std::accumulate(unit.begin(), unit.end(), 0);
}