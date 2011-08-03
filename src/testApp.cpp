#include "testApp.h"
#include "settings.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);

    int our_width = 320;
    int our_height = 240;

    #ifdef _USE_KINECT
        kinect.init();
        kinect.setVerbose(true);
        kinect.open();
        cout << "kinect opened with resolution " << kinect.width << "," << kinect.height << endl;
        our_height = kinect.height;
        our_width = kinect.width;
        dataHub.kFarThreshold = 0;
        dataHub.kThreshold = 255;

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
}

//--------------------------------------------------------------
void testApp::update(){
    screen->update();

    oscTunnel->update();

    #ifdef _USE_KINECT
        kinect.update();
        if(kinect.isFrameNew())
        {
            grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
            #ifdef _MIRROR_VIDEO_IMAGE
                grayImage.mirror(false,true);
            #endif
            //we do two thresholds - one for the far plane and one for the near plane
            //we then do a cvAnd to get the pixels which are a union of the two thresholds.
            grayThreshFar = grayImage;
            grayThresh = grayImage;
            grayThresh.threshold(dataHub.kThreshold, true);
            grayThreshFar.threshold(dataHub.kFarThreshold);
            cvAnd(grayThresh.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);

            grayImage.flagImageChanged();
            grayDiff = grayImage; // ????

            //roCoImg = grayImage.scale()

            //grayImage.flagImageChanged();
        }

    #else
        vidGrabber.grabFrame();
        if(vidGrabber.isFrameNew())
        {
            colorImg.setFromPixels(vidGrabber.getPixels(), 320, 240);

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
void testApp::draw()
{

    screen->draw();

    if(dataHub.bDebug) {
        string debug = "";
        debug += "strength: "+ofToString(dataHub.strength) + "\n";
        debug += "damping:  "+ofToString(dataHub.damping) + "\n";
        debug += "kFarThreshold/kThreshold:  "+ofToString(dataHub.kFarThreshold) + " / " + ofToString(dataHub.kThreshold) + "\n";
        debug += "FPS:  "+ofToString(ofGetFrameRate());
        ofDrawBitmapString(debug, 10, ofGetHeight() - 90);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    switch (key)
    {
        case ' ':
            bLearnBakground = true;
            break;

        case OF_KEY_RIGHT:
            dataHub.kFarThreshold = MIN(dataHub.kFarThreshold + 1, 254);
            break;
        case OF_KEY_LEFT:
            dataHub.kFarThreshold = MAX(dataHub.kFarThreshold - 1, 0);
            break;
        case OF_KEY_UP:
            dataHub.kThreshold = MIN(dataHub.kThreshold + 1, 254);
            break;
        case OF_KEY_DOWN:
            dataHub.kThreshold = MAX(dataHub.kThreshold - 1, 0);
            break;

        case 'd':
            dataHub.bDebug = !dataHub.bDebug; break;

        case '+':
            dataHub.strength += 0.1; break;
        case '-':
            dataHub.strength -= 0.1; break;
        case '.':
            dataHub.damping += 0.1; break;
        case ',':
            dataHub.damping -= 0.1; break;


        case 'o':
            oscTunnel->sendTestMessage(); break;
        case 'b':
            screen->randomBG(); break;
        case 'p':
            screen->pong->reset(); break;
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

