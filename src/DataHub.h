#pragma once

#include "Message.h"
#include "ofxOpenCv.h"
#include "ofxPango.h"

struct DataHub
{
    int* mouseX;
    int* mouseY;

    unsigned int *rows, *cols;
    bool bDebug;

    ofxCvGrayscaleImage* grayDiff;
    ofxCvGrayscaleImage* roCoImg;

    vector<Message *> * messages;

    // box2d engine related
    float strength;
    float damping;

    int kThreshold;
    int kFarThreshold;

    ofxPCPangoFontDescription* font;

    ofColor box2dColor;
    ofColor flowColor;
    ofColor pongColor;
    ofColor asciiBackgroundColor;
};
