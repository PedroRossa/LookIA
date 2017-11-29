#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "Chromosome.h"

class Individual
{
protected:

#pragma region Attributes

	size_t id;
	int generation;
	float fitness;

	Chromosome chromosome;

#pragma endregion

public:

#pragma region Constructors

	Individual();
	~Individual();

#pragma endregion

#pragma region Gets

	size_t GetId();
	int GetGeneration();
	float GetFitness();

	Chromosome GetChromosome();

	void SetFitness(float fitness);
	void SetChromosome(Chromosome chromosome);

#pragma endregion
	
};

#endif