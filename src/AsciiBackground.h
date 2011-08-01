#ifndef ASCIIBACKGROUND_H
#define ASCIIBACKGROUND_H

#include "DataHub.h"
#include "ofxFBOTexture.h"
#include "ofFbo.h"
#include "ofxPango.h"

#include "settings.h"

#ifdef _USE_OFFBO
#define ofxFBOTexture ofFbo
#endif


class AsciiBackground
{
    public:
        AsciiBackground();
        virtual ~AsciiBackground();

        void setBackground(string s);
        void addDatahub(DataHub * h);
        void setupFBO(ofxPCContext* c, ofxPCPangoLayout* l);

        void setup();
        void update();
        void draw();

        DataHub* dataHub;

        string background;

        ofxFBOTexture *tex;
        ofImage text_image;
        //ofFbo *tex;

        ofxPango * pango;
        ofxPCContext* context;
        ofxPCPangoLayout* layout;
        void setOfxPango(ofxPango * p);

    protected:
    private:
};

#endif
