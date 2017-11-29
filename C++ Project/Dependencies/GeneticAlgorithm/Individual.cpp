#include "Individual.h"

#pragma region Constructors

Individual::Individual()
{
}

Individual::~Individual()
{
}

#pragma endregion

#pragma region Gets

size_t Individual::GetId() { return this->id; }
int Individual::GetGeneration() { return this->generation; }
float Individual::GetFitness() { return this->fitness; }

Chromosome Individual::GetChromosome() { return this->chromosome; }

void Individual::SetFitness(float fitness) { this->fitness = fitness; }

void Individual::SetChromosome(Chromosome chromosome) { this->chromosome = chromosome; }

#pragma endregion