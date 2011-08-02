#include "Letter.h"
//#include <boost/algorithm/string.hpp>

#include "settings.h"
#ifdef _USE_OFFBO
#define ofxFBOTexture ofFbo
#endif

using namespace Poco;

#include "Poco/UTF8Encoding.h"
#include "Poco/TextIterator.h"

Letter::Letter(string let)
{
    letter = let;
    col = 0;
    row = 0;
    cout << let << ",";
}


void Letter::prerender(ofxPango *p, ofxPCPangoFontDescription* font)
{
    ofxPCContext * context = p->createContextWithSurface(FONT_SIZE, FONT_SIZE*2);
    context->color4f(0.0f, 0.0f, 0.0f, 0.0f);
    context->paint();
    ofxPCPangoLayout * layout = context->createPangoLayout();

    layout->setFontDescription(*font);
    layout->setText(letter);
    context->color4f(1.0f, 1.0f, 1.0f, 1.0f);

    cout << "prerender : " << letter << endl;

    layout->show();

    /* Hopefully this will be useless step. It has to be!!! */
    ofImage text_image;
    text_image.allocate(context->getSurface()->getWidth(), context->getSurface()->getHeight(), OF_IMAGE_COLOR_ALPHA);
    text_image.setFromPixels(context->getSurface()->getPixels(), text_image.width, text_image.height, OF_IMAGE_COLOR_ALPHA, true);

    //tex = new ofFbo();
    tex = new ofxFBOTexture();
    //tex->allocate(font->stringWidth(letter), font->getLineHeight());
    tex->allocate(FONT_SIZE, FONT_SIZE*2);
    tex->begin();
        //ofFill();
        //ofSetColor(0, 0, 0);
        //ofRect(0, 0, tex->getWidth(), tex->getHeight());
        //ofSetColor(255, 255, 255);
        text_image.draw(0,0);
//        font->drawString(letter, 0, FONT_SIZE);
    tex->end();
}

Letter::~Letter()
{
    //dtor
}

void Letter::draw()
{
    tex->draw(col * FONT_SIZE, row * FONT_SIZE);
}

Word::Word(string word)
{
    UTF8Encoding utf8Encoding;
    TextIterator it(word, utf8Encoding);
    TextIterator end(it.end());
    int n = 0;

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

Message::Message(string message, ofxPango * p, ofxPCPangoFontDescription* f)
{
    StringTokenizer t(message, ", ", StringTokenizer::TOK_TRIM);
    StringTokenizer::Iterator ti = t.begin();
    for(; ti != t.end(); ++ti) {
        Word *w = new Word((string)(*ti));
        words.push_back(w);
    }
    prerender(p, f);
    setPosition(13, 13);
}

void Message::prerender(ofxPango * p, ofxPCPangoFontDescription* f) {
  for(vector<Word *>::iterator i = words.begin();
        i != words.end(); ++i) {

        for(vector<Letter *>::iterator ii = (*i)->letters.begin();
            ii != (*i)->letters.end(); ++ii) {

            (*ii)->prerender(p, f);

        }
    }
}


void Message::setPosition(int col, int row)
{
    int spacing = 0;
    int letter_index = 0;
    for(vector<Word *>::iterator i = words.begin();
        i != words.end(); ++i) {
        for(vector<Letter *>::iterator ii = (*i)->letters.begin();
            ii != (*i)->letters.end(); ++ii) {
            (*ii)->col = col + spacing + letter_index;
            (*ii)->row = row;
            letter_index++;
        }
        spacing++;
    }
}

void Message::draw()
{
    for(vector<Word *>::iterator i = words.begin();
        i != words.end(); ++i) {
        (*i)->draw();
    }
}

int Message::getCol()
{
    return words[0]->letters[0]->col;
}

int Message::getRow()
{
    return words[0]->letters[0]->row;
}
