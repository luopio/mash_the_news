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
    if(color != NULL) {
        ofSetColor(color);
    }

    for(vector<Letter *>::iterator ii = letters.begin();
        ii != letters.end(); ++ii) {
        (*ii)->draw();
    }
}
