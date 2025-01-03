#include "OutputGenerator.h"


OutputGenerator::OutputGenerator(std::string _location) :
	location(_location)
{
	createFile();
}

OutputGenerator::OutputGenerator(const OutputGenerator& _outputGenerator) :
	location(_outputGenerator.location)
{
	createFile();
}


//OutputGenerator OutputGenerator::operator=(OutputGenerator& _outputGenerator);

void OutputGenerator::createFile()
{
	outputFile.open(location);
}
void OutputGenerator::append(std::string _label)
{
	outputFile << _label;

	outputFile << "\n";
}
void OutputGenerator::append(Unit _unit, std::string _label)
{
	outputFile << _label;
	for (auto v : _unit.unit)
	{
		outputFile << v;
	}

	outputFile << "\n";
}

void OutputGenerator::append(std::vector<int> _unit, std::string _label)
{
	outputFile << _label;
	for (auto v : _unit)
	{
		outputFile << v;
	}

	outputFile << "\n";
}