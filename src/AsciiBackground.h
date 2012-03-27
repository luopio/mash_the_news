#ifndef ASCIIBACKGROUND_H
#define ASCIIBACKGROUND_H

#include "settings.h"
#include "DataHub.h"

#include "ofFbo.h"
#include "ofxPango.h"

#ifdef _USE_OFFBO
    #define FBO ofFbo
#else
    #define FBO ofxFBOTexture
    #include "ofxFBOTexture.h"
#endif


class AsciiBackground
{
    public:
        AsciiBackground();
        virtual ~AsciiBackground();

        void setBackground(string s);
        void addFrame(string s);
        void addDatahub(DataHub * h);
        void setupFBO(ofxPCContext* c, ofxPCPangoLayout* l);

        void setup();
        void update();
        void draw();

        DataHub* dataHub;

        string background;

        FBO *tex;
        ofImage text_image;

        vector<FBO *> frames;

        ofxPango * pango;
        ofxPCContext* context;
        ofxPCPangoLayout* layout;
        void setOfxPango(ofxPango * p);

        ofImage * test;

    protected:
    private:
};

#endif
