#include "MashScreen.h"

MashScreen::MashScreen(DataHub &h)
{
    dataHub = &h;
    bChangeText = true;
    // dataHub->messages = &messages;
}

MashScreen::~MashScreen()
{
    cout << "mashscreen being destroyed" << endl;
}

void MashScreen::setup()
{
    // load the font slightly smaller to fit it completely on the FBO (adjust for font change!)
    //font.loadFont("Sans", FONT_SIZE, true, true);

    cols = ofGetWidth()  / FONT_W;
    rows = ofGetHeight() / FONT_H;
    bShowImage = false;
    dataHub->colorMapWeight = 0.0;
    dataHub->colorMapImageWeight = 0.0;

    dataHub->currentSlideIndex = 0;
    dataHub->rows = &rows;
    dataHub->cols = &cols;
    cout << "cols&rows" << cols << "," << rows << "w&h " << ofGetWidth() << "," << ofGetHeight() << endl;

    /* Pango stuff */
    pango = new ofxPango();
    dataHub->font = new ofxPCPangoFontDescription();
    //dataHub->font->createFromString("Arial Unicode MS 11");
    // dataHub->font->createFromString("Courier 11");
    // dataHub->font->createFromString("Trebuchet MS 10");
    // dataHub->font->createFromString("Bitstream Vera Sans Mono 11");
    dataHub->font->createFromString("FixedsysTTF 11");
    // dataHub->font->setWeight(PANGO_WEIGHT_ULTRAHEAVY);

    cairo_font_options_t * co = cairo_font_options_create ();
    cairo_font_options_set_antialias(co,CAIRO_ANTIALIAS_NONE);

    letterBuffer = new LetterBuffer(pango, dataHub->font);
    flow = new Flow(*dataHub);
    // box2d->setup();

    ofBackground(0, 0, 0);

    //asciiBG.addDatahub(dataHub);
    cmv = new CameraMaskViewer(dataHub, letterBuffer);
    //asciiBG.setOfxPango(pango);

    // Initialize the slideshow images //////////////////////////////////
    vector<string> msgs1;
    msgs1.push_back("Berman, Nina");
    msgs1.push_back("crops, agriculture");
    msgs1.push_back("green, nature, life, urban farming");
    msgs1.push_back("farmer, bling-bling and sunglasses");
    msgs1.push_back("train, urban farming next to the tracks");
    SlideShowImage * s1 = new SlideShowImage(msgs1, "1.jpg", letterBuffer, dataHub);
    slideshow.push_back(s1);

    vector<string> msgs2;
    msgs2.push_back("Christina Seely: Metropolis 40°47' N 73°58' W, from series: LUX, 2006–2008.");
    msgs2.push_back("New York");
    msgs2.push_back("Lights by night");
    msgs2.push_back("water, calm, darkness, electricity");
    msgs2.push_back("no wind, no life, nobody");
    SlideShowImage * s2 = new SlideShowImage(msgs2, "2.jpg", letterBuffer, dataHub);
    slideshow.push_back(s2);

    vector<string> msgs3;
    msgs3.push_back("Duncan John: Silver Stream, Belfast");
    msgs3.push_back("nature, grass, green");
    msgs3.push_back("urban landscape");
    msgs3.push_back("tires, loads of tires, a tower of tires");
    msgs3.push_back("somebody lives there");
    SlideShowImage * s3 = new SlideShowImage(msgs3, "3.jpg", letterBuffer, dataHub);
    slideshow.push_back(s3);

    vector<string> msgs4;
    msgs4.push_back("Isidro Blasco: Untitled. From series: Shanghai at last I, 2008.");
    msgs4.push_back("art with architecture");
    msgs4.push_back("clean, colorful, distruptive");
    msgs4.push_back("out of place, but well integrated");
    SlideShowImage * s4 = new SlideShowImage(msgs4, "4.jpg", letterBuffer, dataHub);
    slideshow.push_back(s4);

    vector<string> msgs5;
    msgs5.push_back("Jiang Pengyi. No. 1, from series: Unregistered City, 2008-2010.");
    msgs5.push_back("miniature");
    msgs5.push_back("dust, rubble, needs some cleaning");
    msgs5.push_back("sunlight from the windows");
    msgs5.push_back("order rising out of chaos");
    msgs5.push_back("new life");
    SlideShowImage * s5 = new SlideShowImage(msgs5, "5.jpg", letterBuffer, dataHub);
    slideshow.push_back(s5);

    vector<string> msgs6;
    msgs6.push_back("Juha Allan Ekholm. Clowns by Night, from series: Carnival Portraits, 2012");
    msgs6.push_back("sisters in the night");
    msgs6.push_back("red, green, blue, R, G, B");
    msgs6.push_back("happy or sad or both?");
    msgs6.push_back("late night. is it time for bed? maybe not just yet.");
    SlideShowImage * s6 = new SlideShowImage(msgs6, "6.jpg", letterBuffer, dataHub);
    slideshow.push_back(s6);

    vector<string> msgs7;
    msgs7.push_back("David McMillan. Basketball court, Pripyat, October, from series: The Chernobyl zone, 2004.");
    msgs7.push_back("forest, wild, civilization, competition");
    msgs7.push_back("sports is good for you");
    msgs7.push_back("nature is good for you");
    msgs7.push_back("sport in nature - double the goodness");
    SlideShowImage * s7 = new SlideShowImage(msgs7, "7.jpg", letterBuffer, dataHub);
    slideshow.push_back(s7);

    vector<string> msgs8;
    msgs8.push_back("Dana Popa. (Untitled) From series: not Natasha, 2006–2008. Courtesy of Autograph ABP.");
    msgs8.push_back("birth, beginning, growth");
    msgs8.push_back("security and calmness, adventures and excitement");
    msgs8.push_back("void of worry");
    SlideShowImage * s8 = new SlideShowImage(msgs8, "8.jpg", letterBuffer, dataHub);
    slideshow.push_back(s8);

    vector<string> msgs9;
    msgs9.push_back("Christopher Thomas, Grand Central Terminal and Chrysler Building, 2008. Series: New York Sleeps. Courtesy Ira Stehmann, Munich.");
    msgs9.push_back("architecture, landmark, scene, black and white");
    msgs9.push_back("New York");
    msgs9.push_back("rising to the heights");
    SlideShowImage * s9 = new SlideShowImage(msgs9, "9.jpg", letterBuffer, dataHub);
    slideshow.push_back(s9);

    vector<string> msgs10;
    msgs10.push_back("William Raban. Film still from: About Now MMX, 2010.");
    msgs10.push_back("cityscape, life, the hive");
    msgs10.push_back("practicality versus personal space");
    msgs10.push_back("living in pigeonholes");
    SlideShowImage * s10 = new SlideShowImage(msgs10, "10.jpg", letterBuffer, dataHub);
    slideshow.push_back(s10);

    vector<string> msgs11;
    msgs11.push_back("Michael Wolf. # 39, from series: Tokyo Compression, 2010.");
    msgs11.push_back("living in the big city");
    msgs11.push_back("in the middle of everybody, alone");
    msgs11.push_back("woman, longing, rain");
    SlideShowImage * s11 = new SlideShowImage(msgs11, "11.jpg", letterBuffer, dataHub);
    slideshow.push_back(s11);


    dataHub->messages = &(s1->messages);

    flow->setup();

    randomBG();
    // asciiBG.setBackground(q);
    // shader.load("shaders/noise.vert", "shaders/noise.frag");
    // cout << "binding tex0 to " << asciiBG.tex->getTextureReference().texData.textureID << endl;
    // shader.setUniform1i("tex0", fbo.getTextureReference().texData.textureID); //send which texture to the shader
    // shader.setUniformTexture("tex0", fbo, fbo.getTextureReference().texData.textureID); //send which texture to the shader

    dataHub->box2dColor             = ofColor(255, 255, 255, 0);
    dataHub->flowColor              = ofColor(255, 25,  98,  255);
    dataHub->asciiBackgroundColor   = ofColor(25,  25,  205, 0);
    dataHub->CMVColor               = ofColor(255,  0,  178, 255);

    dataHub->flowBGbrightness       = 40;

    dataHub->roCoImg = new ofxCvGrayscaleImage(); // This is kinect image scaled to row/col-space
    dataHub->roCoImg->allocate(*(dataHub->cols), *(dataHub->rows));

    dataHub->colorMap = slideshow[0]->colorMap;
    cout << "colorMap size" << dataHub->colorMap->getWidth() << "," << dataHub->colorMap->getHeight() << endl;

    flowFbo.allocate(ofGetWidth(), ofGetHeight());
    asciiBackgroundFbo.allocate(ofGetWidth(), ofGetHeight());
    CMVFbo.allocate(ofGetWidth(), ofGetHeight());

    ofEnableAlphaBlending();
}


void MashScreen::update()
{
    if(dataHub->flowColor.a) {
        flow->update();
    }

    // control refresh rate for the rest
    float now = ofGetElapsedTimef();
    if(now - lastUpdateTime < 0.15) {
        return;
    }
    lastUpdateTime = now;
}


void MashScreen::draw()
{

    ofSetColor(255, 255, 255, 255);

    /*
    if(dataHub->asciiBackgroundColor.a) {
        asciiBackgroundFbo.begin();
            ofClear(0, 0, 0, 0);
            asciiBG.draw();
        asciiBackgroundFbo.end();
        ofSetColor(dataHub->asciiBackgroundColor);
        asciiBackgroundFbo.draw(0, 0);
    }
    */

    if(dataHub->flowColor.a) {
        flowFbo.begin();
            ofSetColor(255, 255, 255, 255);
            ofClear(0, 0, 0, 0);
            flow->draw();
        flowFbo.end();
        //ofSetColor(dataHub->flowColor);
        flowFbo.draw(0, 0);
    }



    if(dataHub->colorMapImageWeight > 0.01) {
        ofSetColor(255, 255, 255, 255 * dataHub->colorMapImageWeight);
        dataHub->colorMap->draw(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(255);
    }
    if(bShowImage) {
        dataHub->colorMap->draw(0, 0, ofGetWidth(), ofGetHeight());
    }

/*
    if(dataHub->CMVColor.a) {
        CMVFbo.begin();
            ofSetColor(255, 255, 255, 255);
            ofClear(0, 0, 0, 0);
            cmv->draw();
        CMVFbo.end();
        //ofSetColor(dataHub->CMVColor);
        CMVFbo.draw(0, 0);
    }
    */
}

void MashScreen::randomBG() {
    string tmps = "";

    for (int i = 0; i < rows -1; i++) {
        string tmp = "";
        for (int j = 0; j < cols; j++) {
            tmp += (rand()*1.0/RAND_MAX)*60+33;
            //tmp += "*";
        }
        tmp += "\n";
        tmps += tmp;
    }

    tmps += "ÖÄöÖÄÖÄÄÄÖ***************";

    // asciiBG.setBackground(tmps);

}

void MashScreen::hilightWordAt(int wordIndex)
{
    Message *m = NULL;
    Word *w = NULL;
    Word *wantedWord = NULL;
    int curIndex = 0;
    for(int i = 0; i < dataHub->messages->size(); i++) {
        m = (*dataHub->messages)[i];
        for(vector<Word *>::iterator wi = m->words.begin();
            wi != m->words.end(); ++wi) {
            if(curIndex == wordIndex) {
                wantedWord = *wi;
                flow->hilightFirstWord(wantedWord);
                return;
            }
            curIndex++;
        }
    }
}


void MashScreen::nextSlide()
{
    if(bChangeText) {
        dataHub->currentSlideIndex++;
        if(dataHub->currentSlideIndex > slideshow.size() - 1) {
            dataHub->currentSlideIndex = 0;
        }
        cout << "moved to slide " << dataHub->currentSlideIndex << endl;
        dataHub->messages = &(slideshow[dataHub->currentSlideIndex]->messages);
        flow->setup();
        bChangeText = false;
    } else {
        cout << "moved to next image " << dataHub->currentSlideIndex << endl;
        dataHub->colorMap = slideshow[dataHub->currentSlideIndex]->colorMap;
        bChangeText = true;
    }
}


SlideShowImage::SlideShowImage(vector<string> msgs, string imagePath, LetterBuffer * letterBuffer, DataHub * dataHub)
{
    string m;
    for(int i = 0; i < msgs.size(); i++) {
        m = msgs[i];
        messages.push_back( new Message(m, letterBuffer) );
    }
    image = new ofImage();
    image->loadImage(imagePath);
    colorMap = new ofImage();
    colorMap->loadImage(imagePath);
    colorMap->resize(*(dataHub->cols), *(dataHub->rows));
}
