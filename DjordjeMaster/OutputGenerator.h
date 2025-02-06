#pragma once
#include<vector>
#include"Unit.h"
#include <iostream>
#include <fstream>

class OutputGenerator
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_location">std::string</param>
	OutputGenerator(std::string _location);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="_outputGenerator">OutputGenerator</param>
	OutputGenerator(const OutputGenerator& _outputGenerator);
	
	/// <summary>
	/// Creates output file
	/// </summary>
	void createFile();
	
	/// <summary>
	/// Appends unit (and label) t output file
	/// </summary>
	/// <param name="_unit">Unit</param>
	/// <param name="_label">std::string</param>
	void append(Unit _unit, std::string _label);
	
	/// <summary>
	/// Appends label to output file
	/// </summary>
	/// <param name="_label">std::string</param>
	void append(std::string _label);

	/// <summary>
	/// Appends unit (array) to output file
	/// </summary>
	/// <param name="_unit"></param>
	/// <param name="_label"></param>
	void append(std::vector<int> _unit, std::string _label);

private:
	std::string location;
	std::ofstream outputFile;

};

