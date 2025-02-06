#pragma once
#include"Hypergraph.h"
#include <string>
class FileParser
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_location">std::string</param>
	FileParser (std::string _location);

	/// <summary>
	/// Hypergraph getter
	/// </summary>
	/// <returns>Hypergraph</returns>
	Hypergraph getHypergraph();

	/// <summary>
	/// Parses graph file and populates vertices/hyperedges
	/// </summary>
	void parseGraphFile();

	/// <summary>
	/// Parses population file and creates population
	/// </summary>
	/// <param name="_graph">Hypergraph</param>
	/// <returns>std::vector<std::vector<int>></returns>
	std::vector<std::vector<int>> parsePopulationFile(Hypergraph _graph);

	/// <summary>
	/// Splits string by delimiter
	/// </summary>
	/// <param name="s">std::string</param>
	/// <param name="delimiter">std::string</param>
	/// <returns>std::vector<std::string></returns>
	std::vector<std::string> split(std::string s, std::string delimiter);

private:
	Hypergraph						hypergraph;
	std::vector<int>				vertices;
	std::vector<std::vector<int>>	hyperedges;
	std::string						location;
};

