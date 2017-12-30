
#ifndef _BLINK_DET_DLL_
#define _BLINK_DET_DLL_

#include "..\libVideoRec\pvsystem.h"

int __stdcall pvsConfigureCamera(int nWidth, int nHeight, int nBpp, int deviceIndex);
int __stdcall pvsConfigureCameraAuto(int deviceIndex); 
void __stdcall pvsDestroyCamera();
void __stdcall pvsDestroy();

int __stdcall pvsInitializeNextFrame();
void __stdcall pvsTimeStamp();
int __stdcall pvsGetFrameNumber();
int __stdcall pvsGetFrameLapse();
int __stdcall pvsGetFrameLapseAveraged();
int __stdcall pvsGetFrameTime();


void __stdcall pvsDrawImgIn(HWND hwnd); //HDC hDC, RECT *pClientRect);
void __stdcall pvsDrawImgOut(HWND hwnd); //HDC hDC, RECT *pClientRect);
void __stdcall pvsDrawImgEyes(HWND hwnd); //HDC hDC, RECT *pClientRect);
void __stdcall pvsDrawImgSkins(HWND hwnd); //HDC hDC, RECT *pClientRect);


// Main Blink Detection function

int __stdcall pvsDetectFaces();
//int __stdcall pvsDetectEyes(int &x, int &y);

int __stdcall pvsDetectedLeftEyeX();
int __stdcall pvsDetectedLeftEyeY();
int __stdcall pvsDetectedRightEyeX();
int __stdcall pvsDetectedRightEyeY();


int __stdcall pvsActivateMotionChannel(int nTheshold, int nMode, int nArea);
int __stdcall pvsComputeSecondOrderChange();
int __stdcall pvsDetectChange(int leftX, int leftY, int rightX, int rightY);
int __stdcall pvsDetectBlink(int nEyes, int leftX, int leftY, int rightX, int rightY, 
							 int nDistanceBetween, int nConstraints);
int __stdcall pvsGetLeftEyeX();
int __stdcall pvsGetLeftEyeY();
int __stdcall pvsGetRightEyeX();
int __stdcall pvsGetRightEyeY();


// Colour functions
int __stdcall pvsActivateColourChannel();
//void __stdcall pvsDetectSkins();


// Intensity functions
void __stdcall pvsSetNouse(int x, int y);
void __stdcall pvsNouseOn();
void __stdcall pvsNouseOff();
void __stdcall pvsDetectNouse();
int __stdcall pvsGetNouseX();
int __stdcall pvsGetNouseY();

#endif