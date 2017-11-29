#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "../../OpenCV_IA/Helper.h"

class Chromosome
{
private:

#pragma region Attributes
	
	int size;
	vector<float> weights;

#pragma endregion

public:

#pragma region Constructors

	Chromosome();
	Chromosome(int size);
	Chromosome(int size, vector<float> weights);
	~Chromosome();

#pragma endregion

#pragma region Gets

	int GetSize();
	vector<float> GetWeights();
	float GetWeight(int pos);

	void SetWeights(vector<float> weights);

#pragma endregion

#pragma region Public Methods

	void Initialize();

#pragma endregion

};

#endif