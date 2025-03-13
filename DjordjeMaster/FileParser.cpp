#include "FileParser.h"
#include <fstream>
#include <algorithm>

FileParser::FileParser(std::string _location) :
	location(_location)
{
	parseGraphFile();
	hypergraph = Hypergraph(vertices, hyperedges);
}

std::vector<std::string> FileParser::split(std::string s, std::string delimiter) 
{
	size_t						pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string					token;
	std::vector<std::string>	res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) 
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));

	return res;
}


// Naredni kod (metoda parsePopulationFile) preuzet je sa https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c

std::vector<std::vector<int>> FileParser::parsePopulationFile(Hypergraph _graph)
{
	std::ifstream					input_stream(location);
	std::vector<std::vector<int>>	populationArray;
	int								popSize = stoi(split(location, "/")[6].substr(3,2));

	if (input_stream.is_open())
	{
		std::string line;

		getline(input_stream, line);
		
		int		numberOfVertices	= stoi(line);		
		int		lineNumber			= 0;
		
		while (getline(input_stream, line) && lineNumber < popSize)
		{
			int					pos			= lineNumber < 10 ?	3:4;
			std::vector<int>	hyperedge	= {};

			for (auto gene : line.substr(pos,numberOfVertices))
			{
				hyperedge.push_back((int) gene - '0');
			}

			populationArray.push_back(hyperedge);
			++lineNumber;
		}
	}

	return populationArray;
}

void FileParser::parseGraphFile()
{
	std::ifstream input_stream(location);

	if (input_stream.is_open())
	{
		std::string line;

		getline(input_stream, line);

		int numberOfVertices = stoi(line);

		for (int i = 0; i < numberOfVertices; ++i)
		{
			vertices.push_back(i);
		}

		while (getline(input_stream, line))
		{
			int					pos			= 0;
			std::vector<int>	hyperedge	= {};

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
