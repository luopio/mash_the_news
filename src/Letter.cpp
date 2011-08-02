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

void Letter::prerender(ofTrueTypeFont *f) // DEPRECATED
{
    font = f;
    //tex = new ofFbo();
    tex = new ofxFBOTexture();
    //tex->allocate(font->stringWidth(letter), font->getLineHeight());
    tex->allocate(FONT_SIZE, FONT_SIZE);
    tex->begin();
        ofFill();
        ofSetColor(0, 0, 0);
        ofRect(0, 0, tex->getWidth(), tex->getHeight());
        ofSetColor(255, 255, 255);
        font->drawString(letter, 0, FONT_SIZE);
    tex->end();
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
   // cout << endl << "word: " << (int)word.char_at(0) << " " << word.substr(1,1) << " " << word.substr(2,1) << endl;

   // string * tmp = &word;

   // cout << "pointer: " << *tmp << endl;

   // wstring * ws = reinterpret_cast<wstring*>(tmp);

   // cout << "stringl: " << word.length() << "wstinrl " << ws->length() << endl;

   // ws =  &word;

   //cout << ws. << endl;

    UTF8Encoding utf8Encoding;
    //char buffer[] = word.c_str();
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


      //  ofColor c;
      //  c.r = 255; c.g = 255; c.b = 255;
      //  l->color = c;
      //  letters.push_back(l);

        //cout << "Q " << *it << endl;

        //++n;
        ++it;
        }

 /*   string::iterator i;
    for(i = tmp->begin(); i != tmp->end(); i++) {
    //    cout << ":" << i ;
        Letter *l = new Letter((*i));
        ofColor c;
        c.r = 255; c.g = 255; c.b = 255;
        l->color = c;
        letters.push_back(l);
    }*/
   // cout << endl;
}

Message::Message(string message, ofxPango * p, ofxPCPangoFontDescription* f)
{
    // vector<string> swords = split(message, ' ');

    //wstring * ws;
    //ws = (wstring)&message;

    /*wstring m_inputText(message.length(), L' ');
    std::copy(message.begin(), message.end(), m_inputText.begin());

    std::vector<std::wstring> tok;
        split(tok, m_inputText, boost::is_any_of(L" "));

        for(std::vector<std::wstring>::iterator tok_iter = tok.begin();
                        tok_iter != tok.end(); ++tok_iter)
        {
                std::wcout << *tok_iter << '\n';
        }
*/
    //StringTokenizer


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

/* DEPRECATED */
void Message::prerender(ofTrueTypeFont *f)
{
    for(vector<Word *>::iterator i = words.begin();
        i != words.end(); ++i) {

        for(vector<Letter *>::iterator ii = (*i)->letters.begin();
            ii != (*i)->letters.end(); ++ii) {

            (*ii)->prerender(f);

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
