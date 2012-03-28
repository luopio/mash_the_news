#include "Word.h"

Word::Word(string word)
{
    UTF8Encoding utf8Encoding;
    TextIterator it(word, utf8Encoding);
    TextIterator end(it.end());
    int n = 0;

    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));

    while (it != end) {
        Letter *l = NULL;

        if ((*it) > 127) { // ascii
            l = new Letter(word.substr(n,2));
            n += 2;
           // cout << "joo" << endl;

        } else { // utf8
           l = new Letter(word.substr(n,1));
           n++;
          //cout << "ei" << endl;
        }

        ofColor c;
        c.r = 255; c.g = 255; c.b = 255;
        l->color = c;
        letters.push_back(l);
        ++it;
    }
}

void Word::draw()
{
    if(color.r && color.g && color.b) {
        ofSetColor(color);
    }

    for(vector<Letter *>::iterator ii = letters.begin();
        ii != letters.end(); ++ii) {
        (*ii)->draw();
    }
    ofSetColor(255);
}

void Word::draw(int x, int y)
{
    if(color.r && color.g && color.b) {
        ofSetColor(color);
    }

    int letterCounter = 0;
    for(vector<Letter *>::iterator ii = letters.begin();
        ii != letters.end(); ++ii) {
        (*ii)->draw(x + letterCounter * FONT_W, y);
        letterCounter++;
    }
    ofSetColor(255);
}


void Word::draw(int x, int y, int r, int g, int b)
{
    ofSetColor(r, g, b, 255);

    int letterCounter = 0;
    for(vector<Letter *>::iterator ii = letters.begin();
        ii != letters.end(); ++ii) {
        (*ii)->draw(x + letterCounter * FONT_W, y);
        letterCounter++;
    }
    ofSetColor(255);
}


void Word::drawww(int col, int row, ofImage * colorMap)
{
    int letterCounter = 0;
    unsigned char r = 255; unsigned char g = 255; unsigned char b = 255;
    for(vector<Letter *>::iterator ii = letters.begin();
        ii != letters.end(); ++ii) {
        int colIndex = col + letterCounter;
        ofColor c = colorMap->getColor(colIndex, row);

        (*ii)->draw((colIndex) * FONT_W, row * FONT_H, c.r, c.g, c.b);
        letterCounter++;
    }
}

void Word::drawww(int col, int row, int r, int g, int b, ofImage * colorMap, float weight)
{
    int letterCounter = 0;
    unsigned char wr, wb, wg;
    for(vector<Letter *>::iterator ii = letters.begin();
        ii != letters.end(); ++ii) {
        int colIndex = col + letterCounter;
        ofColor c = colorMap->getColor(colIndex, row);

        wr = (unsigned char)(c.r * weight + r * (1.0 - weight));
        wb = (unsigned char)(c.b * weight + b * (1.0 - weight));
        wg = (unsigned char)(c.g * weight + g * (1.0 - weight));

        (*ii)->draw((colIndex) * FONT_W, row * FONT_H, wr, wg, wb);
        letterCounter++;
    }
}
