#ifndef COMPUTER_EYE_H
#define COMPUTER_EYE_H

#include "Helper.h"

class ComputerEye
{
private:

#pragma region Attributes

	char* mainWindowName;
	char* smallWindowName;

	HWND hwndDesktop;
	float desktopScale;
	Mat screen;

	Mat croppedScreen;
	Mat croppedScreen_Gray;
	Mat smallScreen;

	bool showMainWindow;
	bool showSmallWindow;

	vec2 croppedPos;
	vec2 croppedSize;

	bool useAtualCroppedImage;

#pragma endregion

#pragma Private Methods

	Mat hwnd2mat(float scaleX, float scaleY);

#pragma endregion

public:

#pragma Constructors

	ComputerEye(char* mainWindowName = "Main Screen", char* smallWindowName = "Small Screen");
	~ComputerEye();

#pragma endregion

#pragma Getters and Setters

	char* GetMainWindowName();
	char* GetSmallWindowName();

	int GetDesktopScale();

	Mat GetScreen();
	Mat GetCroppedScreen(bool gray);
	Mat GetSmallScreen();
	bool UseAtualCroppedImage();
	vec2 GetCroppedPos();
	vec2 GetCroppedSize();

	bool ShowMainWindow();
	bool ShowSmallWindow();


	void SetMainWindowName(char* name);
	void SetCropedScreen(vec2 bottomLeft = vec2(0, 0), vec2 upperRight = vec2(480, 320));
	void SetDesktopScale(float scale);

	void SetSmallScreen(Mat screen);
	void UseAtualCroppedImage(bool val);
	void SetCroppedPos(vec2 pos);
	void SetCroppedSize(vec2 pos);

	void ShowMainWindow(bool show);
	void ShowSmallWindow(bool show);
	
#pragma endregion

#pragma region Public Methods

	void Update();
	
	void CreateMainWindow();
	void CreateSmallWindow();

	void DestroyMainWindow();
	void DestroySmallWindow();

	void RecreateMainWindow();
	void RecreateSmallWindow();
	
#pragma endregion

};

#endif