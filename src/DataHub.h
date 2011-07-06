#ifndef DATAHUB_H
#define DATAHUB_H

#include "ofxOpenCv.h"

struct DataHub
{
        int* mouseX;
        int* mouseY;

        ofxCvGrayscaleImage* grayDiff;

};

#endif // DATAHUB_H
