#pragma once
#include"Hypergraph.h"
#include <string>
class FileParser
{
public:
	FileParser (std::string _location);
	Hypergraph getHypergraph();

	void parseFile();
	std::vector<std::string> split(std::string s, std::string delimiter);
private:
	Hypergraph hypergraph;
	std::vector<int> vertices;
	std::vector<std::vector<int>> hyperedges;
	std::string location;
};

