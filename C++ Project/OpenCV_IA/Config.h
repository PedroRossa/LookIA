#ifndef CONFIG_H
#define CONFIG_H

#include "ComputerEye.h"
#include "Serial.h"
#include "NeuralNetwork.h"

//SERIAL STUFF

Serial* SP;
NeuralNetwork* neuralNetwork;
bool nnInitialized = false;

float* lastOutputs;

const int outputBufferSize = 5;
int outputCount = 0;
bool isEndGame = false;


char incomingData[256] = "";// don't forget to pre-allocate memory
							//printf("%s\n",incomingData);
int dataLength = 255;
int readResult = 0;

//-------------------------

ComputerEye computerEye;

int thresholdValue = 90;
int thresholdType = 1;

char* trackbarType = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbarValue = "Value";
char* trackBarSmallWindowScale = "Fingerprint Scale";

int scaleSmallScreen = 25;
int lastScaleSmallScreen;

int key = 0;

vec2 mouseDown;
vec2 mouseUp;

#endif