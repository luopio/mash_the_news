#include "testApp.h"
#include "settings.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetLogLevel(OF_LOG_WARNING);

    int our_width = 320;
    int our_height = 240;

    #ifdef _USE_KINECT
        kinect.init(false,false,false);
        kinect.setVerbose(true);
        kinect.open();
        cout << "kinect opened with resolution " << kinect.width << "," << kinect.height << endl;
        our_height = kinect.height;
        our_width = kinect.width;
        dataHub.kFarThreshold = 240;
        dataHub.kThreshold = 250;

    #else
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
        cout << "webcam opened with resolution " << endl;

        threshold = 13;
    #endif

    dataHub.zoom = 1.0f;

    bLearnBakground = true;

    // These images are for webcam capture, resolution is webcams/kinects reso!
    grayDiff.allocate(our_width,our_height);
    grayBg.allocate(our_width,our_height);
    colorImg.allocate(our_width,our_height);
    grayImage.allocate(our_width,our_height);
    grayThresh.allocate(our_width, our_height);
    grayThreshFar.allocate(our_width, our_height);

    scaleImage.allocate(our_width,our_height);

    //testCameraImage.allocate(kinect.width,kinect.height);

    dataHub.grayDiff = &grayDiff;
    dataHub.mouseX = &mouseX;
    dataHub.mouseY = &mouseY;
    dataHub.bDebug = false;

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
            //testCameraImage.setFromPixels(kinect.getPixels(), kinect.width,kinect.height);
            #ifdef _MIRROR_VIDEO_IMAGE
                grayImage.mirror(false,true);
            #endif

            // thresholding off, does very little good and makes result image binary value
            //we do two thresholds - one for the far plane and one for the near plane
            //we then do a cvAnd to get the pixels which are a union of the two thresholds.
            //grayThreshFar = grayImage;
            //grayThresh = grayImage;
            //grayThresh.threshold(dataHub.kThreshold, true);
            //grayThreshFar.threshold(dataHub.kFarThreshold);
            //cvAnd(grayThresh.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
            //grayImage.flagImageChanged();

            grayDiff = grayImage; // ????
            //grayDiff.convertToRange(dataHub.kThreshold, dataHub.kFarThreshold);

            //roCoImg = grayImage.scale()

            //grayImage.flagImageChanged();

            if (dataHub.zoom < 1.0) { // we have to zoom!
              //  dataHub.roCoImg->crop(12,12,12,12);
                //grayDiff.translate(-100,-100);

            }

            dataHub.roCoImg->scaleIntoMe(grayDiff);

            unsigned char *pixels = dataHub.roCoImg->getPixels();
            for (int i = 0; i < (dataHub.roCoImg->width)*(dataHub.roCoImg->height); i++) {
                if (pixels[i] < dataHub.kFarThreshold || pixels[i] > dataHub.kThreshold) {
                    pixels[i] = 0;
                }
                pixels[i] = max(0,pixels[i] - (dataHub.kFarThreshold));

                pixels[i] = (int)(pixels[i] * (255.0 / (dataHub.kThreshold - dataHub.kFarThreshold)));

               // pixels[i] = (unsigned char)(pixels[i] * (255.0/dataHub.kFarThreshold));
            }
        }

    #else
        vidGrabber.grabFrame();
        if(vidGrabber.isFrameNew())
        {
            colorImg.setFromPixels(vidGrabber.getPixels(), 320, 240);

            grayImage = colorImg;
            if (dataHub.learnBackground == true)
            {
                grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
                dataHub.learnBackground = false;
            }

            // take the abs value of the difference between background and incoming and then threshold:
            grayDiff.absDiff(grayBg, grayImage);
            grayDiff.threshold(threshold);

            grayThresh = grayDiff;

            grayDiff.translate(-100,-100);

            // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
            // also, find holes is set to true so we will get interior contours as well....
            //contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
            dataHub.roCoImg->scaleIntoMe(grayDiff);
        }

    #endif

}

//--------------------------------------------------------------
void testApp::draw()
{

    screen->draw();

    if(dataHub.bDebug) {
        ofSetColor(255);
        // grayDiff.draw(0, 0);
        string debug = "";
        debug += "strength: "+ofToString(dataHub.strength) + "\n";
        debug += "damping:  "+ofToString(dataHub.damping) + "\n";
        debug += "kFarThreshold/kThreshold:  "+ofToString(dataHub.kFarThreshold) + " / " + ofToString(dataHub.kThreshold) + "\n";
        debug += "FPS:  "+ofToString(ofGetFrameRate());
        ofDrawBitmapString(debug, 10, ofGetHeight() - 90);
    }

    //testCameraImage.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    cout << "PRESSED " << key << endl;
    switch (key)
    {
        case '+':
            dataHub.flowFadeSpeed++;
            break;

        case '-':
            dataHub.flowFadeSpeed--;
            break;

        case OF_KEY_BACKSPACE: // sends same as F3?
            break;


        case OF_KEY_END:
            oscTunnel->toggleMute();
            break;

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

