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
    ofImage * colorMap;
    unsigned int currentSlideIndex;
    float colorMapWeight;
    float colorMapImageWeight;

    vector<Message *> * messages;

    // box2d engine related
    float strength;
    float damping;

    int kThreshold;
    int kFarThreshold;

    float flowFadeSpeed;
    float pongSpeed;

    float zoom;

    ofxPCPangoFontDescription* font;

    ofColor box2dColor;
    ofColor flowColor;
    ofColor pongColor;
    ofColor asciiBackgroundColor;
    ofColor CMVColor;
    ofColor bigLetterColor;

    // new ones
    ofColor freezeColor;
    float freezeFadeSpeed;
    float freezeSmokeSpeed;

    float flowBGbrightness;

    bool learnBackground;

    string backGroundString;

};
