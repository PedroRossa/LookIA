#include "NeuralNetwork.h"

#pragma region Constructors

NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::NeuralNetwork(int numInput, unsigned char* weights, int numOutput, int numLayers, int numHiddenNeurons)
{
	this->numInput = numInput;
	this->numOutput = numOutput;
	this->numLayers = numLayers;
	this->numHiddenNeurons = numHiddenNeurons;
	this->desiredError = desiredError;
	this->maxEpochs = maxEpochs;

	if(numHiddenNeurons <= 0)
		this->ann = fann_create_standard(numLayers, numInput, numOutput);
	else
		this->ann = fann_create_standard(numLayers, numInput, numHiddenNeurons, numOutput);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID);
	fann_set_activation_function_output(ann, FANN_SIGMOID);

	//SetWeights(weights);
}

NeuralNetwork::~NeuralNetwork()
{
	fann_destroy(ann);
}

#pragma endregion

#pragma region Getters and Setters

unsigned int NeuralNetwork::GetNumInput() { return this->numInput; }
unsigned int NeuralNetwork::GetNumOutput() { return this->numOutput; }
unsigned int NeuralNetwork::GetNumLayers() { return this->numLayers; }
unsigned int NeuralNetwork::GetNumHiddenNeurons() { return this->numHiddenNeurons; }
float NeuralNetwork::GetDesiredError() { return this->desiredError; }
unsigned int NeuralNetwork::GetMaxEpochs() { return this->maxEpochs; }

struct fann* NeuralNetwork::GetAnn() { return this->ann; }

#pragma endregion

#pragma region Public Methods

void NeuralNetwork::SetWeights(unsigned char* values)
{
	for (size_t i = 0; i < ann->total_connections; i++)
	{
		ann->weights[i] = values[i];
	}
}

fann_type* NeuralNetwork::Run(unsigned char* inputValues)
{
	//minus 1 because of the BIAS (the last value is the BIAS)
	fann_type* inputs = new fann_type[ann->total_connections-1];
	for (size_t i = 0; i < ann->total_connections-1; i++)
	{
		inputs[i] = inputValues[i]/255;
	}

	fann_type* out = fann_run(ann, inputs);
	delete inputs;

	return out;
}

#pragma endregion
