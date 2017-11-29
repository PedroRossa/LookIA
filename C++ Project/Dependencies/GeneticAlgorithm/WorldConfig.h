#pragma once
class WorldConfig
{
private:

#pragma region Attributes

	int populationSize;     //size of population in each generation
	int generations;        //number of generations
	int crossoverTax;       //tax of crossover in each generation
	int crossoverDivisions; //number ov divisions in a crossover
	int mutationTax;        //tax of mutation in each generations
	bool useElitism;        //use eletism on generations
	int elitismFactor;      //define the number of individuals to next generations

#pragma endregion

public:

#pragma region Constructors

	WorldConfig();
	WorldConfig(int populationSize, int generations, int crossoverTax = 20, int crossoverDivisions = 1, int mutationTax = 5, bool useElitism = false, int elitismFactor = 1);
	~WorldConfig();

#pragma endregion

#pragma Gets 

	int GetPopulationSize();
	int GetGenerations();
	int GetCrossoverTax();
	int GetCrossoverDivision();
	int GetMutationTax();
	bool UseElitism();
	int GetElitismFactor();

#pragma endregion
	
};

