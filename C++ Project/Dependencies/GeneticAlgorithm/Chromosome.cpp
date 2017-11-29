#include "Chromosome.h"

#pragma region Constructors

Chromosome::Chromosome() : Chromosome(0)
{
}

//size - Size of the vector
Chromosome::Chromosome(int size)
{
	this->size = size;
	Initialize();
}

//size - Size of the vector
//directions - vector with the weights, if is an empty vector, the system gonna create a random vector
Chromosome::Chromosome(int size, vector<float> weights)
{
	this->size = size;
	this->weights = weights;
}

Chromosome::~Chromosome()
{
}

#pragma endregion

#pragma region Gets

int Chromosome::GetSize() { return this->size; }
vector<float> Chromosome::GetWeights() { return this->weights; }
float Chromosome::GetWeight(int pos) { return this->weights[pos]; }

void Chromosome::SetWeights(vector<float> weights){ this->weights = weights; }

#pragma endregion

#pragma region Public Methods

void Chromosome::Initialize()
{
	for (size_t i = 0; i < this->size; i++)
	{
		float randWeight = RandWeight(-1.0f, 1.0f);
		weights.push_back(randWeight);
	}
}

#pragma endregion