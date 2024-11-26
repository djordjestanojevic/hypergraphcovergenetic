#include "FileParser.h"
#include <fstream>
#include <algorithm>

std::vector<std::string> FileParser::split(std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

FileParser::FileParser(std::string _location) :
	location(_location)
{
	parseFile();
	hypergraph = Hypergraph(vertices, hyperedges);
}

void FileParser::parseFile()
{
	std::ifstream input_stream(location);
	if (input_stream.is_open())
	{
		std::string line;

		// one line
		getline(input_stream, line);
		int numberOfVertices = stoi(line);
		for (int i = 0; i < numberOfVertices; i++)
		{
			vertices.push_back(i);
		}

		// extract all the text from the input file
		while (getline(input_stream, line))
		{
			int pos = 0;
			std::vector<int> hyperedge = {};

			for (std::string vertex : split(line, ","))
			{
				hyperedge.push_back(stoi(vertex));
			}

			hyperedges.push_back(hyperedge);
		}
	}
	

}

Hypergraph FileParser::getHypergraph()
{
	return hypergraph;
}
