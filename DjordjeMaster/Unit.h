#pragma once
#include"Hypergraph.h"
#include<random>
class Unit
{
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Unit() = delete;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_hypergraph">Hypergraph</param>
	/// <param name="_alleleProbability">double</param>
	Unit(Hypergraph _hypergraph, double _alleleProbability);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_hypergraph">Hypergraph</param>
	/// <param name="_array">std::vector<int></param>
	Unit(Hypergraph _hypergraph, std::vector<int> _array);

	/// <summary>
	/// Fitness function
	/// </summary>
	/// <returns>int</returns>
	int fitness();

	/// <summary>
	/// Mutates unit according to parameter
	/// </summary>
	/// <param name="_r">double</param>
	/// <returns>bool</returns>
	bool mutate(double _r);

	/// <summary>
	/// Adjusts unit to cover hypergraph
	/// </summary>
	/// <returns>bool</returns>
	bool adjustToAllowed();
	
	std::vector<int> unit;

private:
	static std::mt19937 generator;
	double				alleleProbability;
	Hypergraph			hypergraph;

};
