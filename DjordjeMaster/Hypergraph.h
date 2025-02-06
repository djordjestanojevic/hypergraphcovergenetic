#pragma once
#include<vector>
#include<numeric>
#include<algorithm>
class Hypergraph
{

public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Hypergraph() = default;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_vertices">std::vector<int></param>
	/// <param name="_hyperedges">std::vector<std::vector<int>></param>
	Hypergraph(std::vector<int> _vertices, std::vector<std::vector<int>> _hyperedges);

	/// <summary>
	/// Checks whether array of vertices covers hypergraph
	/// </summary>
	/// <param name="_array">std::vector<int></param>
	/// <returns>bool</returns>
	bool isCovering(std::vector<int> _array);
	
	/// <summary>
	/// Vertices getter
	/// </summary>
	/// <returns>std::vector<int></returns>
	std::vector<int> getVertices();

	/// <summary>
	/// Hyperedges getter
	/// </summary>
	/// <returns>std::vector<std::vector<int>></returns>
	std::vector<std::vector<int>> getHyperedges();

	/// <summary>
	/// VerticesByDegrees getter
	/// </summary>
	/// <returns>std::vector<int></returns>
	std::vector<int> getVerticesByDegrees();


	/// <summary>
	/// Degrees getter
	/// </summary>
	/// <returns>std::vector<int></returns>
	std::vector<int> getDegrees();


	/// <summary>
	/// NumberOfVertices getter
	/// </summary>
	/// <returns>int</returns>
	const int getNumberOfVertices() const;

private:
	std::vector<int>				vertices;
	std::vector<std::vector<int>>	hyperedges;	
	std::vector<int>				verticesByDegrees;
	std::vector<int>				degrees;

	/// <summary>
	/// Initializes degrees array
	/// </summary>
	void initDegrees();
	
};

