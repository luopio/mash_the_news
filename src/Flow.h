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
        int rowTotalLength;
};

class Flow
{
    public:
        Flow(DataHub &h);
        virtual ~Flow();

        void setup();
        void update();
        void draw();
        void hilightFirstWord(Word *w);
        void addMessage(Message *m);

        DataHub* dataHub;
        vector<FlowingWord *> words;

        float lastUpdateTime;
        bool bDebug;
        float fadeSpeed;

    protected:
    private:
};
