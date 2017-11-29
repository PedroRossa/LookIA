#ifndef GENETIC_H
#define GENETIC_H

#include "Player.h"
#include "WorldConfig.h"

//TODO: Não consegui fazer passar vector de classe Parent aqui, então por enquanto estou passando
//Direto a classe filha

class Genetic
{
private:

#pragma region Private Methods

	vector<Player*> Roulette_Selection(vector<Player*> population, WorldConfig configs);

	vector<int> GenerateDivisionPoints(int numberOfDivisions, int sizeOfChromossome);

	Chromosome* MixChromosomes(vector<float>valuesA, vector<float> valuesB, vector<int> divisionPoints);

#pragma endregion

public:

#pragma region Constructors

	Genetic();
	~Genetic();

#pragma endregion

#pragma region Public Methods

	void GenerateNewPopulation(vector<Player*>& population, PopulationGeneratorType type, WorldConfig configs);

	//Return two new chromosomes
	Chromosome* Crossover(Chromosome chromosomeA, Chromosome chromosomeB, int crossoverTax, int divisions = 1);
	void Mutation(Chromosome* chromosome, int mutationTax);

#pragma endregion

};

#endif