#include "AsciiBackground.h"

#include "settings.h"
#ifdef _USE_OFFBO
#define ofxFBOTexture ofFbo
#endif

AsciiBackground::AsciiBackground()
{
    dataHub = NULL;
    pango = NULL;
    background = "";
    tex = NULL;
    context = NULL;
    layout = NULL;
}

AsciiBackground::~AsciiBackground()
{
    //dtor
}

void AsciiBackground::addDatahub(DataHub * d) {
    dataHub = d;
}

void AsciiBackground::setOfxPango(ofxPango * p) {
    pango = p;
    context = pango->createContextWithSurface(ofGetWidth(), ofGetHeight());
    context->color4f(1.0f, 1.0f, 1.0f, 0.5f);
    context->paint();
    layout = context->createPangoLayout();
   // ofxPCPangoFontDescription* fd = new ofxPCPangoFontDescription();
    //fd->createFromString("Arial Unicode MS 11");
    //fd->createFromString("Courier 11");
    layout->setFontDescription(*(dataHub->font));
}

void AsciiBackground::setupFBO(ofxPCContext* c, ofxPCPangoLayout* l) {
    context = c;
    layout = l;
}

void AsciiBackground::setBackground(string s) {
    if (pango==NULL || dataHub==NULL) return;

    context = pango->createContextWithSurface(ofGetWidth(), ofGetHeight());
    context->color4f(1.0f, 1.0f, 1.0f, 0.5f);
    //context->paint();

    layout = context->createPangoLayout();

  //  layout->

    //layout->fill(0.0f,0.0f,0.0f,1.0f);
    layout->setText(s);
    //layout->setText("ライブラリーでは、所蔵資料の中からテーマにそった小さな展示を行っています。6月から始まったミニ展示「明治・大正時代の日本ガイドブック」、2回目の7月は「古都の旅」と題し、外国人旅行者のために書かれた京都や奈良のガイドブックを展示します。\n\n 한국에서 발매할 PS3는3월에 유럽에서 발매한 PS3와 동일한 최신 모델을 사용하여 새롭게 의 대용량 HDD(하드디스크 드라이브)를 표준 탑재하고 있다. 대용량HDD를 탑재함으로써 PS3발매와 동시에 실시할 온라인 서비스 “PLAYSTATION®Network”로 선보이게 될 다양한 엔터테인먼트 콘텐츠 다운로드와 온라인 게임 및 온라인 서비스를 보다 쾌적하게 사용할 수 있도록 하였다.\n\nHovedgruppen må være på minimum 10 personer, men deltakere kan knytte seg til hovedgruppen fra forskjellige destinasjoner. Tilknytningsbillett er gyldig inntil 24 timer før avreise hovedgruppe.\n\nUnicef said 3m people had been affected and more than 1,400 had been killed. The government said some 27,000 people remained trapped and awaiting help.");
    layout->setFontDescription(*(dataHub->font));
    //layout->setWidth(ofGetWidth());
    //layout->setJustify(true);

    layout->setWidth(ofGetWidth());

    //layout->show

    //layout->setJustify(true);
    //context->color4f(1.0f, 1.0f, 1.0f, 1.0f);

    layout->show();

    text_image.allocate(context->getSurface()->getWidth(), context->getSurface()->getHeight(), OF_IMAGE_COLOR_ALPHA);
    text_image.setFromPixels(context->getSurface()->getPixels(), text_image.width, text_image.height, OF_IMAGE_COLOR_ALPHA, true);

    //background = s;
    //tex = new ofFbo();
    /*if (tex!=NULL) {
        delete tex;
    }*/
    tex = new ofxFBOTexture();
    tex->allocate(ofGetWidth(), ofGetHeight());
    tex->begin();

//s    tex->setFromPixels(context->getSurface()->getPixels(), text_image.width, text_image.height, OF_IMAGE_COLOR_ALPHA, true);
        /*ofFill();
        ofSetColor(25, 0, 0);
        ofRect(0, 0, tex->getWidth(), tex->getHeight());
        ofSetColor(255, 255, 255, 128);
        f.drawString(s, 0, FONT_SIZE);*/
    text_image.draw(0,0);
   //text_image.draw(10*9,6*18);
    tex->end();
}

void AsciiBackground::draw() {
    if (tex==NULL) return;
    // ofSetColor(40,40,40);
    tex->draw(0,0);
    // ofSetColor(255,255,255);
}

