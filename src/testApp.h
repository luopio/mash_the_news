#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "MashScreen.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "DataHub.h"
#include "OscTunnel.h"

#define _USE_KINECT
#define OSC_PORT 7000
#define OSC_OUT_IP "192.168.10.11"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void asciiBackground();

        MashScreen *screen;
        DataHub dataHub;

        ofxCvGrayscaleImage 	grayDiff;
        ofxCvGrayscaleImage 	grayBg;
        ofxCvColorImage         colorImg;
        ofxCvGrayscaleImage 	grayImage;
        ofxCvGrayscaleImage 	grayThresh;
        ofxCvGrayscaleImage 	grayThreshFar;
        ofxCvGrayscaleImage     scaleImage;

        int 				    threshold;
        ofTrueTypeFont          bgFont;

        #ifdef _USE_KINECT
            ofxKinect kinect;
		#else
            ofVideoGrabber          vidGrabber;
        #endif

        int nearThreshold;
        int farThreshold;
        bool bLearnBakground;
        bool bDebug;

        OscTunnel               *oscTunnel;

        string                  bgString;

};

#endif
