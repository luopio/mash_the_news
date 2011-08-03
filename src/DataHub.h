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
    vector<Message *> * messages;

    // box2d engine related
    float strength;
    float damping;

    int kThreshold;
    int kFarThreshold;

    ofxPCPangoFontDescription* font;
};
