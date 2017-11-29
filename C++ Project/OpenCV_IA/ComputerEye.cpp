#include "ComputerEye.h"

#pragma Constructors

ComputerEye::ComputerEye(char* mainWindowName, char* smallWindowName)
{
	this->mainWindowName = mainWindowName;
	this->smallWindowName = smallWindowName;

	CreateMainWindow();
	CreateSmallWindow();

	moveWindow(mainWindowName, 20, 20);
	moveWindow(smallWindowName, 40, 40);

	this->hwndDesktop = GetDesktopWindow();
	this->desktopScale = 0.5f;
	this->screen = hwnd2mat(desktopScale, desktopScale);

	this->croppedScreen = CropMatrix(screen, vec2(), vec2());

	this->useAtualCroppedImage = false;
	this->croppedPos = vec2(0, 0);
	this->croppedSize = vec2(480, 320);

	this->showMainWindow = true;
	this->showSmallWindow = false;
}

ComputerEye::~ComputerEye()
{
}

#pragma endregion

#pragma region Private Methods

Mat ComputerEye::hwnd2mat(float scaleX, float scaleY)
{
	HDC hwindowDC, hwindowCompatibleDC;

	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
	Mat src;
	BITMAPINFOHEADER  bi;

	hwindowDC = GetDC(hwndDesktop);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	RECT windowsize;    // get the height and width of the screen
	GetClientRect(hwndDesktop, &windowsize);

	//TODO: DIVIDI TUDO POR 2 AQUI
	srcheight = windowsize.bottom;
	srcwidth = windowsize.right;
	height = windowsize.bottom * scaleX;  //change this to whatever size you want to resize to
	width = windowsize.right * scaleY;

	//srcheight = 320;
	//srcwidth = 480;
	//height = 320;  //change this to whatever size you want to resize to
	//width = 480;

	src.create(height, width, CV_8UC4);

	// create a bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

																									   // avoid memory leak
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwndDesktop, hwindowDC);

	return src;
}

#pragma endregion

#pragma Getters and Setters

char* ComputerEye::GetMainWindowName() { return this->mainWindowName; }
char* ComputerEye::GetSmallWindowName() { return this->smallWindowName; }

int ComputerEye::GetDesktopScale() { return this->desktopScale; }

Mat ComputerEye::GetScreen() { return this->screen; }
Mat ComputerEye::GetCroppedScreen(bool gray)
{
	if (gray)
		return this->croppedScreen_Gray;
	else
		return this->croppedScreen;
}
Mat ComputerEye::GetSmallScreen() { return this->smallScreen; }

bool ComputerEye::UseAtualCroppedImage() { return this->useAtualCroppedImage; }
vec2 ComputerEye::GetCroppedPos() { return this->croppedPos; }
vec2 ComputerEye::GetCroppedSize() { return this->croppedSize; }

bool ComputerEye::ShowMainWindow() { return this->showMainWindow; }
bool ComputerEye::ShowSmallWindow() { return this->showSmallWindow; }


void ComputerEye::SetMainWindowName(char* name) { this->mainWindowName = name; }
void ComputerEye::SetCropedScreen(vec2 bottomLeft , vec2 width)
{ 
	try
	{
		this->croppedScreen = CropMatrix(this->screen, bottomLeft, width);
		//Set Gray cropped screen
		cvtColor(this->croppedScreen, this->croppedScreen_Gray, CV_BGR2GRAY);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void ComputerEye::SetDesktopScale(float scale) { this->desktopScale = scale; }

void ComputerEye::SetSmallScreen(Mat screen) { this->smallScreen = screen; }

void ComputerEye::UseAtualCroppedImage(bool val) { this->useAtualCroppedImage = val; }
void ComputerEye::SetCroppedPos(vec2 pos) { this->croppedPos = pos; }
void ComputerEye::SetCroppedSize(vec2 pos) { this->croppedSize = pos; }

void ComputerEye::ShowMainWindow(bool show) { this->showMainWindow = show; }
void ComputerEye::ShowSmallWindow(bool show) { this->showSmallWindow = show; }

#pragma endregion

#pragma region Public Methods

void ComputerEye::Update()
{
	this->screen = hwnd2mat(desktopScale, desktopScale);
	SetCropedScreen(croppedPos, croppedSize);

	if (showMainWindow)
		imshow(mainWindowName, screen);
	
	if (showSmallWindow)
		imshow(smallWindowName, smallScreen);

}

void ComputerEye::DestroyMainWindow() { destroyWindow(this->mainWindowName); }
void ComputerEye::DestroySmallWindow() { destroyWindow(this->smallWindowName); }

void ComputerEye::CreateMainWindow() { namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE); }
void ComputerEye::CreateSmallWindow() { namedWindow(smallWindowName, CV_WINDOW_AUTOSIZE); }

void ComputerEye::RecreateMainWindow() { DestroyMainWindow(); CreateMainWindow(); }
void ComputerEye::RecreateSmallWindow() { DestroySmallWindow(); CreateSmallWindow(); }

#pragma endregion
