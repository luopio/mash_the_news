#ifndef LETTER_H
#define LETTER_H

#define FONT_SIZE 9

#include "ofMain.h"
#include "Poco/StringTokenizer.h"

#include "settings.h"
#ifndef _USE_OFFBO
    #include "ofxFBOTexture.h"
#endif

#include "ofxPango.h"

#include "settings.h"

#ifdef _USE_OFFBO
    #define ofxFBOTexture ofFbo
#endif

using Poco::StringTokenizer;

class Letter
{
    public:
        Letter(string letter);
        virtual ~Letter();

        void prerender(ofTrueTypeFont *of); // DEPRECATED
        void prerender(ofxPango * p, ofxPCPangoFontDescription* font);
        void draw();

        string letter;
        //ofFbo *tex;
        ofxFBOTexture *tex;
        ofTrueTypeFont *font;
        ofColor color;
        int row, col;

    protected:
    private:
};

class Word
{
    public:
        Word(string word);
        vector<Letter *> letters;
};

class Message
{
    public:
        Message(string message, ofxPango * p, ofxPCPangoFontDescription* font);
        vector<Word *> words;
        void prerender(ofTrueTypeFont *of); // DEPRECATED
        void prerender(ofxPango * p, ofxPCPangoFontDescription* font);
        void setPosition(int col, int row);
};

/*
vector<string> sssplit(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
*/


/*
vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
    // return sssplit(s, delim, elems);
}
*/

#endif // LETTER_H
