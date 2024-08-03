#pragma once
#include"Hypergraph.h"
#include<random>
class Unit
{
public:
	Unit();
	Unit(Hypergraph _hypergraph, double _alleleProbability);
	Unit(Hypergraph _hypergraph, std::vector<int> _array);
	int fitness();
	void mutate(double _r);
	void adjustToAllowed();
	int index;
	Hypergraph hypergraph;
	std::vector<int> unit;

private:
	double alleleProbability;

};
//typedef std::shared_ptr<Unit> unitPtr;