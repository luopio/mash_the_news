#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    box2d.init();
    box2d.setGravity(0, 1);
    // box2d.createFloor();
    box2d.createBounds();
    box2d.checkBounds(true);
    box2d.setFPS(30.0);

    #ifdef _USE_KINECT

    #else
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);

        grayDiff.allocate(320,240);
        grayBg.allocate(320,240);
        colorImg.allocate(320,240);
        grayImage.allocate(320,240);

        bLearnBakground = true;
        threshold = 13;

    #endif



}

//--------------------------------------------------------------
void testApp::update(){

    ofBackground(100,100,100);

    bool bNewFrame = false;

    #ifdef _USE_KINECT

    #else
        vidGrabber.grabFrame();
        bNewFrame = vidGrabber.isFrameNew();
        if (bNewFrame)
        {
            colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);

            grayImage = colorImg;
            if (bLearnBakground == true)
            {
                grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
                bLearnBakground = false;
            }

            // take the abs value of the difference between background and incoming and then threshold:
            grayDiff.absDiff(grayBg, grayImage);
            grayDiff.threshold(threshold);

            // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
            // also, find holes is set to true so we will get interior contours as well....
            //contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
        }

    #endif


}

//--------------------------------------------------------------
void testApp::draw(){

    // draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(0xffffff);
	//colorImg.draw(20,20);
	//grayImage.draw(360,20);
	//grayBg.draw(20,280);
	#ifdef _USE_KINECT

	#else
        grayDiff.draw(20,20);
    #endif

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    #ifdef _USE_KINECT

    #else

        switch (key)
        {
            case ' ':
                bLearnBakground = true;
                break;
            case '+':
                threshold ++;
                if (threshold > 255) threshold = 255;
                break;
            case '-':
                threshold --;
                if (threshold < 0) threshold = 0;
                break;
        }
    #endif
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

