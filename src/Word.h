#pragma once

#include "ofMain.h"
#include "Poco/StringTokenizer.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/TextIterator.h"

#include "Letter.h"


using Poco::StringTokenizer;
using namespace Poco;

class Word
{
    public:
        Word(string word);
        vector<Letter *> letters;
        ofColor color;
        void draw();
        void draw(int x, int y);
        void draw(int x, int y, int r, int g, int b);
        void drawww(int x, int y, ofImage * colorMap);
        void drawww(int x, int y, int r, int g, int b, ofImage * colorMap, float weight);
        void drawww(int x, int y, int r, int g, int b, ofImage * colorMap, float weight, vector <Letter*> * asciiArt);

};
