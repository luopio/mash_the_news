#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    int our_width = 320;
    int our_height = 240;

    #ifdef _USE_KINECT
        kinect.init();
        kinect.setVerbose(true);
        kinect.open();
        cout << "kinect opened with resolution " << kinect.width << "," << kinect.height << endl;
        our_height = kinect.height;
        our_width = kinect.width;
        nearThreshold = 254;
        farThreshold = 0;

    #else
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
        cout << "webcam opened with resolution " << endl;

        threshold = 13;

    #endif

    bLearnBakground = true;

    // These images are for webcam capture, resolution is webcams/kinects reso!
    grayDiff.allocate(our_width,our_height);
    grayBg.allocate(our_width,our_height);
    colorImg.allocate(our_width,our_height);
    grayImage.allocate(our_width,our_height);
    grayThresh.allocate(our_width, our_height);
    grayThreshFar.allocate(our_width, our_height);

    scaleImage.allocate(our_width,our_height);

    dataHub.grayDiff = &grayDiff;
    dataHub.mouseX = &mouseX;
    dataHub.mouseY = &mouseY;
    dataHub.bDebug = true;

    screen = new MashScreen(dataHub);
    screen->setup();

    oscTunnel = new OscTunnel(OSC_OUT_IP, OSC_PORT, screen);
    #ifdef _USE_KINECT
        oscTunnel->addKinect(&kinect);
    #endif

    oscTunnel->addDataHub(&dataHub);

    bgFont.loadFont("VeraMono.ttf", 16);

}

//--------------------------------------------------------------
void testApp::update(){
    screen->update();

    oscTunnel->update();

    bool bNewFrame = false;

    #ifdef _USE_KINECT
        kinect.update();
        if(kinect.isFrameNew())
        {


            grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
            grayImage.mirror(false,true);
            //we do two thresholds - one for the far plane and one for the near plane
            //we then do a cvAnd to get the pixels which are a union of the two thresholds.
            grayThreshFar = grayImage;
            grayThresh = grayImage;
            grayThresh.threshold(oscTunnel->kThreshold, true);
            grayThreshFar.threshold(oscTunnel->kFarThreshold);
            cvAnd(grayThresh.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);

            grayImage.flagImageChanged();
            grayDiff = grayImage; // ????

            //grayImage.flagImageChanged();
        }

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

            grayThresh = grayDiff;


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

	//grayBg.draw(20,280);
	#ifdef _USE_KINECT
        //if (oscTunnel->kDebug) {
         //   scaleImage = grayImage;
            //scaleImage.draw(ofGetWidth() / 2 - scaleImage.width / 2, ofGetHeight() / 2 - scaleImage.height / 2);
         //   scaleImage.draw(0,0, ofGetWidth(), ofGetHeight());
        //}
        //scaleImage.draw()
	#else

    #endif

    if(dataHub.bDebug) {
        //grayImage.draw(20,20);
        grayImage.draw(0,0, ofGetWidth(), ofGetHeight());
    }
    screen->draw();
    asciiBackground();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
        case '1':
            screen->hilightMessage(0); break;
        case '2':
            screen->hilightMessage(1); break;
        case '3':
            screen->hilightMessage(2); break;
        case '0':
            screen->hilightMessage(-10); break;
        case 'e':
            screen->changeEngine(); break;
        case 'd':
            dataHub.bDebug = !dataHub.bDebug; break;
        case 'o':
            oscTunnel->sendTestMessage(); break;
    }
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

void testApp::asciiBackground() {
    ofSetColor(255,255,255);
    bgFont.drawString(oscTunnel->bgString, 0, 0);
}
