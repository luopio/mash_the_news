#pragma once

#include "ofMain.h"

#include "settings.h"

#include "ofxPango.h"
#include "Word.h"

using Poco::StringTokenizer;

class Message
{
    public:
        Message(string message, ofxPango * p, ofxPCPangoFontDescription* font);
        Message(string message, ofTrueTypeFont * font);
        vector<Word *> words;
        void prerender(ofxPango * p, ofxPCPangoFontDescription* font);
        void prerender(ofTrueTypeFont *font);
        void setPosition(int col, int row);
        void draw();
        int getCol();
        int getRow();
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
