#ifndef DATAHUB_H
#define DATAHUB_H

#include "ofxOpenCv.h"
#include "Letter.h"

struct DataHub
{
        int* mouseX;
        int* mouseY;

        unsigned int *rows, *cols;
        bool bDebug;

        ofxCvGrayscaleImage* grayDiff;
        vector<Message *> * messages;

        // box2d engine related
        int* currentEngine;
        float strength;
        float damping;

};

#endif // DATAHUB_H
