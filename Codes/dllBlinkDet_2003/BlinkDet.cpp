


#include "BlinkDet.h"

#pragma data_seg("SHARED")  // Begin the shared data segment.
//CPerceptualVisionSystem PVSystem;

#define PV_MAX_CAMERAS 1
//Ali
CPVS_WithCapture pvs[PV_MAX_CAMERAS], *pPVS, PVSystem;	

#pragma data_seg()
#pragma comment(linker, "/section:SHARED,RWS")


#if 1 

// *** Face Detection functions ***************************************************************************

int __stdcall pvsDetectEyes(int &x, int &y) {
//	return PVSystem.detectFaces();
	CvPoint ptL, ptR;
	int ret = PVSystem.detectEyes(&ptL, &ptR);
	x = ptL.x;
	y = ptL.y;
	return ret;
}

int __stdcall pvsDetectFaces() {
	//Ali
	return PVSystem.detectFaces();
}


int __stdcall pvsDetectedLeftEyeX() {
	return PVSystem.m_face[0].m_fd_ptLEye.x;
}

int __stdcall pvsDetectedLeftEyeY() {
	return PVSystem.m_face[0].m_fd_ptLEye.y;
}


int __stdcall pvsDetectedRightEyeX() {
	return PVSystem.m_face[0].m_fd_ptREye.x;
}

int __stdcall pvsDetectedRightEyeY() {
	return PVSystem.m_face[0].m_fd_ptREye.y;
}

/*
int __stdcall pvsGetLeftEyeX() {
	CvPoint p1,p2;
	PVSystem.m_face.getDetectedEyes(&p1,&p2);
	return p1.x;
}


int __stdcall pvsGetLeftEyeY() {
	return PVSystem.m_face.m_fd_ptLEye.y;;
}


int __stdcall pvsGetRightEyeX() {
	CvPoint p1,p2;
	PVSystem.m_face.getEyes(&p1,&p2);
	return p2.x;
}


int __stdcall pvsGetRightEyeY() {
	CvPoint p1,p2;
	PVSystem.m_face.getEyes(&p1,&p2);
	return p2.y;
}

*/
// *** Face Analysis functions ***************************************************************************


int __stdcall pvsActivateMotionChannel(int nTheshold, int nMode, int nArea) {
	//Ali
	//PVSystem.m_chanMotion.updateImages(&PVSystem.m_imgIn, nTheshold, nMode, nArea);
	PVSystem.m_chanMotion.updateImages(&PVSystem.m_imcIn, nTheshold, nMode, nArea);
	return PVSystem.m_chanMotion.m_nNorm_dI;
}

int __stdcall pvsComputeSecondOrderChange() {		
	PVSystem.m_chanMotion.compute_ddI();
	return PVSystem.m_chanMotion.m_nNorm_ddI;
}

int __stdcall pvsDetectBlink(int nEyes, int leftX, int leftY, int rightX, int rightY, 
							 int nDistanceBetween, int nConstraints) {
	CvPoint p1,p2;
	p1.x = leftX;
	p1.y = leftY;
	p2.x = rightX;
	p2.y = rightY;
	CFace *face = &PVSystem.m_face[0];

	PVSystem.m_chanMotion.setChangeDetROI(p1, p2);
	return PVSystem.m_chanMotion.detectBlinkInROI(nEyes, 
			& face->m_pointLEye, & face->m_pointREye, nDistanceBetween, nConstraints);
}


int __stdcall pvsDetectChange(int leftX, int leftY, int rightX, int rightY) {
	CvPoint p1,p2;
	p1.x = leftX;
	p1.y = leftY;
	p2.x = rightX;
	p2.y = rightY;

	PVSystem.m_chanMotion.setChangeDetROI(p1, p2);
	return PVSystem.m_chanMotion.changeInROI();
}

// *** Colour functions ***************************************************************************


int __stdcall pvsActivateColourChannel() {
	if(PVSystem.activateColourChannel()) return 1;
	else return 0; 
}


int __stdcall pvsDetectSkins(int x, int y, int neighborhood, int flexibility) {
//	if( PVSystem.m_chanColour.isItSkin(&PVSystem.m_imgIn, x, y, neighborhood, flexibility) ) return 1;
//	else 
		return 0;
}




// ***  Nouse functions ***************************************************************************


// Intensity functions
void __stdcall pvsSetNouse(int x, int y) {
		PVSystem.m_chanIntensity.setNouse(&PVSystem.m_imgIn, x, y); // PVSystem.m_imgBW
}

void __stdcall pvsNouseOn() {
		PVSystem.m_chanIntensity.m_featureTracker.enableTracking(FEATURE_NOSE_TIP);
//		PVSystem.m_chanIntensity.m_featureTracker.resetTracking(true);
}

void __stdcall pvsNouseOff() {
//		PVSystem.m_chanIntensity.m_featureTracker.enableTracking(FEATURE_NOSE_TIP);
//		PVSystem.m_chanIntensity.m_featureTracker.resetTracking(false); // ????? 
		PVSystem.m_chanIntensity.m_featureTracker.disableTracking(FEATURE_NOSE_TIP);
}

void __stdcall pvsDetectNouse() {
	CvPoint p1,p2;
	PVSystem.m_chanIntensity.detectNouse(&PVSystem.m_imgIn, &p1);
}

void __stdcall pvsDetectNouseNew(int leftX, int leftY, int rightX, int rightY) {
	CvPoint p1,p2;
	p1.x = leftX;
	p1.y = leftY;
	p2.x = rightX;
	p2.y = rightY;
	PVSystem.m_chanIntensity.setNouseROI(leftX, leftY, rightX, rightY);
	PVSystem.m_chanIntensity.detectNouse(&PVSystem.m_imgIn, &p1);
}

int __stdcall pvsGetNouseX() {
	return PVSystem.m_chanIntensity.m_featureTracker.m_dCurrentX[LEFT_CAMERA][0];
}

int __stdcall pvsGetNouseY() {
	return PVSystem.m_chanIntensity.m_featureTracker.m_dCurrentY[LEFT_CAMERA][0];
}

// ------------------


void __stdcall pvsDrawImgEyes(HWND hwnd) {
	if(!hwnd) return;
	RECT r;
	::GetClientRect(hwnd, &r);
	PVSystem.m_chanMotion.m_imb_dIFiltered.draw(::GetDC(hwnd), &r);
}

void __stdcall pvsDrawImgSkins(HWND hwnd) {
	if(!hwnd) return;
	RECT r;
	::GetClientRect(hwnd, &r);
	PVSystem.m_chanColour.m_imgSkin.draw(::GetDC(hwnd), &r);
}


// ------------------




int __stdcall pvsGetLeftEyeX() {
	CvPoint p1,p2;
	PVSystem.m_face[0].getEyes(&p1,&p2);
	return p1.x;
}


int __stdcall pvsGetLeftEyeY() {
	return PVSystem.m_face[0].m_pointLEye.y;;
}


int __stdcall pvsGetRightEyeX() {
	CvPoint p1,p2;
	PVSystem.m_face[0].getEyes(&p1,&p2);
	return p2.x;
}


int __stdcall pvsGetRightEyeY() {
	CvPoint p1,p2;
	PVSystem.m_face[0].getEyes(&p1,&p2);
	return p2.y;
}

#endif



// *** Camera Configuration functions ***************************************************************************


int __stdcall pvsConfigureCamera(int nWidth, int nHeight, int nBpp, int deviceIndex) {
	bool retVal = 0;
	CoInitialize(NULL);
	CameraDeviceList deviceList;
	CVideoCameraEntry *selectedEntry;
	vl_getDeviceList(deviceList);
	Sleep(1000);
	if(deviceIndex>=0 && deviceIndex<deviceList.size()) {
		retVal = 1;
		selectedEntry = deviceList[deviceIndex];
		if(!PVSystem.configureCamera(NULL, nWidth, nHeight, nBpp, selectedEntry)) {
			retVal = 0;
		}
	}
	vl_purgeDeviceList(deviceList);

	Sleep(1000);
	return retVal;
}

int __stdcall pvsConfigureCameraAuto(int deviceIndex) {
	return pvsConfigureCamera(160, 120, 24, deviceIndex);
		/*
	int nWidth=160, int nHeight=120, int nBpp=24;
	bool retVal = 0;
	CoInitialize(NULL);
	CameraDeviceList deviceList;
	CVideoCameraEntry *selectedEntry;
	vl_getDeviceList(deviceList);
	Sleep(1000);
	if(deviceIndex>=0 && deviceIndex<deviceList.size()) {
		retVal = 1;
		selectedEntry = deviceList[deviceIndex];
		if(!PVSystem.configureCamera(NULL, nWidth, nHeight, nBpp, selectedEntry)) {
			retVal = 0;
		}
	}
	vl_purgeDeviceList(deviceList);

	Sleep(1000);
	return retVal;
	*/
}


void __stdcall pvsDestroyCamera() {
	PVSystem.destroyCamera();
}

void __stdcall pvsDestroy() {
	PVSystem.destroy();
	CoUninitialize();
}



int __stdcall pvsInitializeNextFrame() {
	if(PVSystem.initializeNextFrame()) return 1;
	else return 0;
}


void __stdcall pvsDrawImgIn(HWND hwnd) {
	if(!hwnd) return;
	RECT r;
	::GetClientRect(hwnd, &r);
	PVSystem.drawImgIn(::GetDC(hwnd), &r);
}

void __stdcall pvsDrawImgOut(HWND hwnd) {
	if(!hwnd) return;
	RECT r;
	::GetClientRect(hwnd, &r);
	PVSystem.drawImgOut(::GetDC(hwnd), &r);
}

void __stdcall pvsTimeStamp() {
	PVSystem.timeStamp();
}
int __stdcall pvsGetFrameNumber() {
	return PVSystem.m_nFrame;
}
int __stdcall pvsGetFrameLapseAveraged() {
	return PVSystem.m_tBetweenFrames;
}
int __stdcall pvsGetFrameLapse() {
	return PVSystem.m_tBetweenFramesNow;
}
int __stdcall pvsGetFrameTime() {
	return PVSystem.m_tLast;
}
