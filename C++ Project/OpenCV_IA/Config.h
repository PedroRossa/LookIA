#ifndef CONFIG_H
#define CONFIG_H

#include "ComputerEye.h"
#include "Serial.h"
#include "NeuralNetwork.h"
#include "../Dependencies/GeneticAlgorithm/World.h"

//SERIAL STUFF

Serial* SP;
bool canOperate = true;


NeuralNetwork* neuralNetwork;
bool nnInitialized = false;

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

vec2 defaultMouseDown(205, 150);


clock_t startClock;
float duration;

bool isEndGame = false;
float lastOutput;
clock_t endGameClock;
float endGameMaxTimer = 0.5f;
float endGameTimer = 0;

int jumpCounter = 0;

World* w;

#endif