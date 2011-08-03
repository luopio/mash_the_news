#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

#include "settings.h"
#include "DataHub.h"
#include "MashScreen.h"
#include "OscTunnel.h"

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

        #ifdef _USE_KINECT
            ofxKinect           kinect;
		#else
            ofVideoGrabber      vidGrabber;
        #endif

        bool bLearnBakground;


        OscTunnel               *oscTunnel;

        string                  bgString;

};

#endif
