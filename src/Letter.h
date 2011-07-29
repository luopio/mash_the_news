#ifndef LETTER_H
#define LETTER_H

#define FONT_SIZE 16

#include "ofMain.h"
#include "ofxFBOTexture.h"
#include "Poco/StringTokenizer.h"

using Poco::StringTokenizer;

class Letter
{
    public:
        Letter(const char letter);
        virtual ~Letter();

        void prerender(ofTrueTypeFont &of);
        void draw();

        string letter;
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
        Message(string message, ofTrueTypeFont &font);
        vector<Word *> words;
        void prerender(ofTrueTypeFont &of);
        void setPosition(int col, int row);
        string msg;
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
