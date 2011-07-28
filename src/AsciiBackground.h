#ifndef ASCIIBACKGROUND_H
#define ASCIIBACKGROUND_H

#include "DataHub.h"

class AsciiBackground
{
    public:
        AsciiBackground();
        virtual ~AsciiBackground();

        void setBackground(string s, ofTrueTypeFont &f);
        void addDatahub(DataHub * h);

        void setup();
        void update();
        void draw();

        DataHub* dataHub;

        string background;

        ofxFBOTexture *tex;

    protected:
    private:
};

#endif
