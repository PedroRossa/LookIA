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

void SetCropScreenByClick(vec2 size)
{
	vec2 cropPos(mouseDown.x, mouseDown.y);

	computerEye.SetCroppedPos(cropPos);
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
		printf("We're connected");
}

void UpdateSerial()
{
	readResult = SP->ReadData(incomingData, dataLength);
	// printf("Bytes read: (0 means no data available) %i\n",readResult);
	incomingData[readResult] = 0;

	printf("%s", incomingData);

	Sleep(450);
	SP->WriteData("0", 2);
	Sleep(100);
	SP->WriteData("1", 2);

	key = waitKey(15); // you can change wait time
	if (key == 97)
	{
		SP->WriteData("0", 2);
		Sleep(100);
		SP->WriteData("1", 2);
	}
}

void InitNeuralNetwork()
{
	int w = computerEye.GetSmallScreen().cols;
	int h = computerEye.GetSmallScreen().rows;
	int size = w*h;
	
	unsigned char* weights = new unsigned char[size];

	neuralNetwork = new NeuralNetwork(size, weights);

	lastOutputs = new float[outputBufferSize];
}

bool CheckEndGameState(float output)
{
	lastOutputs[outputCount] = output;
	outputCount++;

	if (outputCount > outputBufferSize)
		outputCount = 0;

	for (size_t i = 0; i < outputBufferSize; i++)
	{
		if (output != lastOutputs[i])
			return false;
	}
	
	return true;
}

int main(int argc, char **argv)
{
	InitSerial();
	computerEye = ComputerEye();

	//set the callback function for any mouse event
	setMouseCallback(computerEye.GetMainWindowName(), MouseCallbackFunc, NULL);
	
	//while (SP->IsConnected())
	while (true)
	{
		computerEye.Update();

		SetCropScreenByDragMouse();
		CreateTrackBars();
		ManageSmallScreen();
		
		
		if (nnInitialized)
		{
			fann_type* out = neuralNetwork->Run(computerEye.GetSmallScreen().data); 
			isEndGame = CheckEndGameState(out[0]);

			if (isEndGame)
			{
				cout << "END GAME" << endl;
			}
			else
			{

				cout << "OUT:" << out[0] << endl;
			}
		}

		int ckey = waitKey(1); 

		//if press 'A'
		if (ckey == 65 && !nnInitialized)
		{
			InitNeuralNetwork();
			nnInitialized = true;
		}


	}

}

