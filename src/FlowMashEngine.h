#ifndef FLOWMASHENGINE_H
#define FLOWMASHENGINE_H

#include "MashEngine.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"

class FlowMashEngine: public MashEngine
{
    public:
        FlowMashEngine(DataHub &h);
        virtual ~FlowMashEngine();

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

#endif // FLOWMASHENGINE_H
