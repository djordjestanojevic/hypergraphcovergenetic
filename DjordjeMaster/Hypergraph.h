#pragma once
#include<vector>
#include<numeric>
#include<algorithm>
class Hypergraph
{

public:
	Hypergraph();
	Hypergraph(std::vector<int> _vertices, std::vector<std::vector<int>> _hyperedges);

	bool cmp(int _a, int _b);
	bool isCovering(std::vector<int> _array);

	std::vector<int> getVertices();
	std::vector<std::vector<int>> getHyperedges();
	std::vector<int> getVerticesByDegrees();

private:
	int numberOfVertices, numberOfHyperedges;

	std::vector<int>				vertices;
	std::vector<std::vector<int>>	hyperedges;
	std::vector<int>				degrees;
	std::vector<int>				verticesByDegrees;

	void initDegrees();
	
};

