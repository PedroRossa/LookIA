#include "NeuralNetwork.h"

#pragma region Constructors

NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::NeuralNetwork(int numInput, int numOutput, int numLayers, int numHiddenNeurons)
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

void NeuralNetwork::SetWeights(float* values)
{
	fann_connection* connections = new fann_connection[sizeof(struct fann_connection) * ann->total_connections];
	fann_get_connection_array(ann, connections);

	for (size_t i = 0; i < ann->total_connections; i++)
	{
		connections[i].weight = values[i];
	}

	fann_set_weight_array(ann, connections, ann->total_connections);

	delete connections;
}

fann_type* NeuralNetwork::Run(unsigned char* inputValues)
{
	fann_type* inputs = new fann_type[this->numInput];
	for (size_t i = 0; i < this->numInput; i++)
	{
		inputs[i] = inputValues[i]/255.0f;
	}

	fann_type* out = fann_run(ann, inputs);
	float ff = out[0];
	delete inputs;

	return out;
}

#pragma endregion
