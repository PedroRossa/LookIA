#include "Callbacks.h"

void SetCropScreenByDragMouse()
{
	vec2 cropPos(mouseDown.x, mouseDown.y);

	int cropW = abs(mouseUp.x - mouseDown.x);
	int cropH = abs(mouseUp.y - mouseDown.y);

	vec2 cropSize(cropW, cropH);

	if (cropH > 0 && cropW > 0)
	{
		computerEye.SetCroppedPos(cropPos);
		computerEye.SetCroppedSize(cropSize);

		computerEye.ShowSmallWindow(true);
	}
}

void SetCropScreenByClick(vec2 size, bool useDefaultValue = false)
{
	if (useDefaultValue)
	{
		computerEye.SetCroppedPos(defaultMouseDown);
	}
	else
	{
		vec2 cropPos(mouseDown.x, mouseDown.y);
		computerEye.SetCroppedPos(cropPos);
	}

	computerEye.SetCroppedSize(size);
	computerEye.ShowSmallWindow(true);
}

void ManageSmallScreen()
{
	Mat m = ApplyThreshold(computerEye.GetCroppedScreen(true), thresholdValue, (ThresholdType)thresholdType);

	if (scaleSmallScreen > 0)
	{
		float scale = scaleSmallScreen / 100.0f;
		computerEye.SetSmallScreen(ResizeMatrix(m, scale, scale, false));

		if (lastScaleSmallScreen != scaleSmallScreen)
		{
			lastScaleSmallScreen = scaleSmallScreen;
			computerEye.RecreateSmallWindow();
		}
	}
}

void CreateTrackBars() {
	Flash_TrackBar
	(
		trackbarType,
		computerEye.GetMainWindowName(),
		&thresholdType,
		4
	);

	Flash_TrackBar
	(
		trackbarValue,
		computerEye.GetMainWindowName(),
		&thresholdValue,
		255
	);

	Flash_TrackBar
	(
		trackBarSmallWindowScale,
		computerEye.GetMainWindowName(),
		&scaleSmallScreen,
		100
	);
}

void InitSerial()
{
	SP = new Serial("\\\\.\\COM11");    // adjust as needed

	if (SP->IsConnected())
		cout <<"We're connected" << endl;
}

void UpdateSerial()
{
	readResult = SP->ReadData(incomingData, dataLength);
	if (readResult > 0) {
		if (incomingData[0] == '1')
		{
			canOperate = true;
		}
	}
}
 
void InitGeneticAlgorithm(int numberOfWeights)
{
	WorldConfig config(10, 10000, 25, 20, 2, true, 2);
	w = new World(config, numberOfWeights);

	w->Start();
}

void InitNeuralNetwork()
{
	int w = computerEye.GetSmallScreen().cols;
	int h = computerEye.GetSmallScreen().rows;
	int size = w*h;
	
	neuralNetwork = new NeuralNetwork(size,1,3,20); 

	unsigned int numberOfWeights = neuralNetwork->GetAnn()->total_connections;
	InitGeneticAlgorithm(numberOfWeights);
}

bool CheckEndGameState(float output)
{
	if (output != lastOutput)
	{
		lastOutput = output;
		endGameClock = clock();
	}
	else
	{
		endGameTimer = (clock() - endGameClock) / (float)CLOCKS_PER_SEC;
		if (endGameTimer > endGameMaxTimer)
			return true;
	}
	return false;
}

void SaveFrameOnFile(string path)
{
	int totalSize = computerEye.GetSmallScreen().cols * computerEye.GetSmallScreen().rows;

	ofstream jumpFrames;
	jumpFrames.open(path,ofstream::app);

	for (size_t i = 0; i < totalSize; i++)
	{
		bool pixelState;
		unsigned char c = computerEye.GetSmallScreen().data[i];
		if (c > 0)
			pixelState = 1;
		else
			pixelState = 0;

		jumpFrames << pixelState;
	}
	jumpFrames << endl;
	jumpFrames.close();
}

void ReadFrameFromFile(string path)
{
	ifstream infile(path);

	string line;
	while (getline(infile, line))
	{
		for (size_t i = 0; i < line.size(); i++)
		{
			cout << line[i];
		}
		cout << endl;
	}
}

void UpdateScreens()
{
	computerEye.Update();

	SetCropScreenByClick(vec2(125,60), true);
	CreateTrackBars();
	ManageSmallScreen();

 	int ckey = waitKey(1);
	
	//if press 'A'
	if (ckey == 65 && !nnInitialized)
	{
		ReadFrameFromFile("jumps.txt");
		InitNeuralNetwork();
		nnInitialized = true;
		startClock = clock();
	}
	else if (ckey == 32 && !nnInitialized) //SpaceBar
	{
		SaveFrameOnFile("jumps.txt");
		jumpCounter++;
	}
}

int main(int argc, char **argv)
{
	InitSerial();
	computerEye = ComputerEye();

	//set the callback function for any mouse event
	setMouseCallback(computerEye.GetMainWindowName(), MouseCallbackFunc, NULL);
	
	while (SP->IsConnected())
	while(true)
	{
		if (!nnInitialized)
		{
			UpdateScreens();
		}
		else
		{
			for (size_t i = 0; i < w->GetPlayers().size(); i++)
			{
				isEndGame = false;
				vector<float> weights = w->GetPlayers().at(i)->GetChromosome().GetWeights();
				neuralNetwork->SetWeights(weights.data());

				SP->WriteData("1", 2);
				canOperate = false;
				Sleep(200);
				
				startClock = clock();
				duration = 0;

				while (!isEndGame)
				{
					UpdateScreens();
					UpdateSerial();

					fann_type* out = neuralNetwork->Run(computerEye.GetSmallScreen().data);

					//cout << "OUT:" << out[0] << "  -  TIME: " << duration << endl;
					if (out[0] > 0.5f && canOperate)
					{
						SP->WriteData("1", 2);
						canOperate = false;
					}

					//UPDATE CLOCK
					duration = (clock() - startClock) / (float)CLOCKS_PER_SEC;
					w->SetTimer(duration);

					isEndGame = CheckEndGameState(out[0]);
					if(isEndGame)
						Sleep(500);
				}

				if (isEndGame)
				{
					UpdateSerial();
					w->UpdatePlayerFitness(i, duration);

					cout << "-------------------------" << endl;
					cout << "END GAME for Player: " << i << endl;
					cout << "total time:" << duration << endl;
					cout << "-------------------------" << endl;
					endGameClock = clock();
				}
			}

			//update population
			w->UpdatePopulation();
		}

	}

}

