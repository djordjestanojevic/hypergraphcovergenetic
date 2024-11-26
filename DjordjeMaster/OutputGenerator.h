#pragma once
#include<vector>
#include"Unit.h"
#include <iostream>
#include <fstream>

class OutputGenerator
{
public:
	std::string location;
	std::ofstream outputFile;
	OutputGenerator(std::string _location);
	OutputGenerator(const OutputGenerator& _outputGenerator);
	// 
	//OutputGenerator operator=(OutputGenerator& _outputGenerator);
	void createFile();
	void append(Unit _unit, std::string _label);
	void append(std::string _label);
	void append(std::vector<int> _unit, std::string _label);
};

