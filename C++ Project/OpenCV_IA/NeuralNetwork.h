#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "fann.h"

class NeuralNetwork
{
private:

	unsigned int numInput;
	unsigned int numOutput;
	unsigned int numLayers;
	unsigned int numHiddenNeurons;
	float desiredError;
	unsigned int maxEpochs;

	struct fann *ann;

public:

#pragma region Constructors

	NeuralNetwork();
	NeuralNetwork(int numInput, unsigned char* weights, int numOutput = 1, int numLayers = 2, int numHiddenNeurons = 0);
	~NeuralNetwork();

#pragma endregion

#pragma region Getters and Setters

	unsigned int GetNumInput();
	unsigned int GetNumOutput();
	unsigned int GetNumLayers();
	unsigned int GetNumHiddenNeurons();
	float GetDesiredError();
	unsigned int GetMaxEpochs();

	struct fann* GetAnn();

#pragma region

#pragma region Public Methods

	void SetWeights(unsigned char* values);

	fann_type* Run(unsigned char* inputValues);

#pragma endregion

};

#endif