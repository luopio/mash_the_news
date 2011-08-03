#ifndef _FLOW_H
#define _FLOW_H

#include "DataHub.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"

class Flow
{
    public:
        Flow(DataHub &h);
        virtual ~Flow();

        void setup();
        void update();
        void draw();

        DataHub* dataHub;
        ofxCvGrayscaleImage tempImg;

        float lastUpdateTime;
        bool bDebug;

    protected:
    private:
};

#endif // Flow_H
