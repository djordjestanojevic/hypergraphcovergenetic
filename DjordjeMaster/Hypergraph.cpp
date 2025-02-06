#include "Hypergraph.h"

Hypergraph::Hypergraph(std::vector<int> _vertices, std::vector<std::vector<int>> _hyperedges) :
	vertices(_vertices),
	hyperedges(_hyperedges)
{
	initDegrees();
}

std::vector<int> Hypergraph::getVertices() 
{
	return vertices;
}


std::vector<std::vector<int>> Hypergraph::getHyperedges()
{
	return hyperedges;
}

std::vector<int> Hypergraph::getVerticesByDegrees()
{
	return verticesByDegrees;
}

std::vector<int> Hypergraph::getDegrees()
{
	return degrees;
}

const int Hypergraph::getNumberOfVertices() const
{
	return (int) vertices.size();
}

void Hypergraph::initDegrees()
{
	for (int i = 0; i < vertices.size(); ++i)
	{
		degrees.push_back(0);
		verticesByDegrees.push_back(i);
	}

	for (auto& hyperedge : hyperedges)
	{
		for (auto& vertex : hyperedge)
		{
			++degrees[vertex];
		}
	}

	std::sort(verticesByDegrees.begin(), verticesByDegrees.end(), [&](int i, int j) { return degrees[i] > degrees[j]; });
}


bool Hypergraph::isCovering(std::vector<int> _array)
{
	for (auto hyperedge : hyperedges)
	{
		bool hyperedgeCovered = false;

		for (auto vertex : hyperedge)
		{
			if (_array[vertex])
			{
				hyperedgeCovered = true;
				break;
			}
		}

		if (!hyperedgeCovered)
		{
			return false;
		}
	}
	return true;
}


