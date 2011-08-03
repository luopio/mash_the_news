#pragma once

#include "DataHub.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "Word.h"
#include "Message.h"

class FlowingWord
{
    public:
        ofFbo fbo;
        float col, row;
        float speed;
        Message * msg;
        Word * word;
        float impulse;
        int pixelWidth;
};

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
        vector<FlowingWord *> words;

        float lastUpdateTime;
        bool bDebug;

    protected:
    private:
};
