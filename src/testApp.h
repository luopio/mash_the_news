#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxBox2d.h"
#include "MashScreen.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

#define __USE_KINECT

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

        ofxBox2d    box2d;
        MashScreen      screen;

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

};

#endif
