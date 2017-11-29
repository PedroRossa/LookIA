#include "WorldConfig.h"

#pragma region Constructors

WorldConfig::WorldConfig(): WorldConfig(10,1000,20,5,false,1)
{
}

//populationSize - size of population in each generation
//generations - number of generations
//crossoverTax - tax of crossover in each generation
//crossoverDivisions - number of divisions in a crossover
//mutationTax - tax of mutation in each generations
//useElitism - use eletism on generations
//elitismFactor - define the number of individuals to next generations
WorldConfig::WorldConfig(int populationSize, int generations, int crossoverTax, int crossoverDivisions, int mutationTax, bool useElitism, int elitismFactor)
{
	this->populationSize = populationSize;
	this->generations = generations;
	this->crossoverTax = crossoverTax;
	this->crossoverDivisions = crossoverDivisions;
	this->mutationTax = mutationTax;
	this->useElitism = useElitism;
	this->elitismFactor = elitismFactor;
}

WorldConfig::~WorldConfig()
{
}

#pragma endregion

#pragma Gets 

int WorldConfig::GetPopulationSize() { return this->populationSize; }
int WorldConfig::GetGenerations() { return this->generations; }
int WorldConfig::GetCrossoverTax() { return this->crossoverTax; }
int WorldConfig::GetCrossoverDivision() { return this->crossoverDivisions; }
int WorldConfig::GetMutationTax() { return this->mutationTax; }
bool WorldConfig::UseElitism() { return this->useElitism; }
int WorldConfig::GetElitismFactor() { return this->elitismFactor; }

#pragma endregion
