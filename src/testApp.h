#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "MashScreen.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "DataHub.h"
#include "OscTunnel.h"

#define __USE_KINECT
#define OSC_PORT 7000
#define OSC_IN_IP "192.168.1.101"
#define OSC_OUT_IP "192.168.1.101"

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

         int 				threshold;

        #ifdef _USE_KINECT
            ofxKinect kinect;
            int nearThreshold;
            int farThreshold;
		#else
            ofVideoGrabber          vidGrabber;

            bool				bLearnBakground;
		#endif

        OscTunnel               *oscTunnel;

};

#endif
