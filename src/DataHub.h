#ifndef DATAHUB_H
#define DATAHUB_H

#include "ofxOpenCv.h"
#include "Letter.h"

struct DataHub
{
        int* mouseX;
        int* mouseY;

        unsigned int *rows, *cols;

        ofxCvGrayscaleImage* grayDiff;
        vector<Message *> * messages;
};

#endif // DATAHUB_H
