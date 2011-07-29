#include "Box2dMashEngine.h"

Box2dMashEngine::Box2dMashEngine(DataHub &h)
{
    dataHub = &h;
    box2d.init();
    box2d.setGravity(0.0, 0.1f);
    // box2d.createFloor();
    box2d.createBounds();
    box2d.checkBounds(true);
    box2d.setFPS(30.0);
    cout << "scale to " << dataHub->grayDiff->width << " and " << dataHub->grayDiff->height << endl;
    tempImg.allocate(dataHub->grayDiff->width / 10,
                     dataHub->grayDiff->height / 10);
}

Box2dMashEngine::~Box2dMashEngine()
{
    //dtor
}

void Box2dMashEngine::setup()
{

    Message *m = NULL;
    int circle_index = 0;
    for(int i = 0; i < dataHub->messages->size(); i++) {
        m = (*dataHub->messages)[i];
        for(vector<Word *>::iterator wi = m->words.begin(); wi != m->words.end(); ++wi) {
            int letter_index = 0;
            for(vector<Letter *>::iterator li = (*wi)->letters.begin(); li != (*wi)->letters.end(); ++li)
            {
                LetterCircle circle;
                // mass, bounce, friction
                circle.setPhysics(.9f, 0.03f, 0.2f);
                circle.setup(box2d.getWorld(),
                             letter_index * FONT_SIZE + 100,
                             i * FONT_SIZE * 2 + 100,
                             FONT_SIZE, FONT_SIZE);
                circle.letterInWordIndex = letter_index;
                circle.letter = (*li);
                circles.push_back(circle);
                if(letter_index > 0) {
                    ofxBox2dJoint* j = new ofxBox2dJoint();
                    j->setup(box2d.getWorld(),
                             circles[circle_index - 1].body,
                             circles[circle_index].body,
                             2.0, 0.7);
                    joints.push_back(j);
                }
                circle_index++;
                letter_index++;
            }
        }
    }

    bMouseForce = false;
    dataHub->strength = 0.33f;
    dataHub->damping  = 0.30f;

}

void Box2dMashEngine::update()
{
    box2d.update();

    /* update the locations of the letters based on the physics objects */
    Message *m = NULL;
    Word *w = NULL;
    int circle_index = 0;
    for(int i = 0; i < dataHub->messages->size(); i++) {
        m = (*dataHub->messages)[i];
        for(int wi = 0; wi < m->words.size(); wi++) {
            w = m->words[wi];
            for(int li = 0; li < w->letters.size(); li++)
            {
                int col = circles[circle_index].getPosition().x / FONT_SIZE;
                int row = circles[circle_index].getPosition().y / FONT_SIZE;
                w->letters[li]->row = row;
                w->letters[li]->col = col;
                circle_index++;
            }
        }
    }


    /*for(int i=0; i<circles.size(); i++) {
        if(i >= dataHub->messages->size()) {
            break;
        }

        Message *m = (*dataHub->messages)[i];
        int col = circles[i].getPosition().x / FONT_SIZE;
        int row = circles[i].getPosition().y / FONT_SIZE;
        int ocol = col;

        for(vector<Word *>::iterator wi = m->words.begin(); wi != m->words.end(); ++wi) {
            for(vector<Letter *>::iterator li = (*wi)->letters.begin(); li != (*wi)->letters.end(); ++li)
            {
                (*li)->col = col++;
                (*li)->row = row;
            }
            row++;
            col = ocol;
        }
    }*/

    if(bMouseForce) {
        for(int i=0; i<circles.size(); i++) {
            circles[i].addAttractionPoint(ofPoint(*(dataHub->mouseX), *(dataHub->mouseY)), dataHub->strength);
            //circles[i].addDamping(damping, damping);
        }
    }
}

void Box2dMashEngine::draw()
{

    /* apply physics to the physics objects based on the kinect image */
    tempImg.scaleIntoMe(*(dataHub->grayDiff));
    //tempImg.scaleIntoMe(*(dataHub->grayImage));

    float distance = 0;

    unsigned char *pixels = tempImg.getPixels();
    int circle_index = 0;
    for(int i = 0; i < tempImg.width * tempImg.height; i++) {
        if(pixels[i] > 0) {
            int screen_x = i % tempImg.width / (float)tempImg.width  * ofGetWidth();
            int screen_y = i / tempImg.width / (float)tempImg.height * ofGetHeight();

            // find the next circle representing the first letter of a word
            // and apply physics force to it
            int totalCirclesMoved = 0;
            while(circle_index < circles.size()) {
                if(circles[circle_index].letterInWordIndex == 0) {

                    distance = sqrt(  pow(screen_x - circles[circle_index].letter->col * FONT_SIZE, 2)
                                    + pow(screen_y - circles[circle_index].letter->row * FONT_SIZE, 2));

                    if(distance < 300) {
                        circles[circle_index].addAttractionPoint(ofPoint(screen_x, screen_y),
                                                                 dataHub->strength / distance);
                        circles[circle_index].setDamping(dataHub->damping, dataHub->damping);

                        if(dataHub->bDebug) {
                            ofPushStyle();
                                ofSetColor(0, 255, 0);
                                ofCircle(screen_x, screen_y, 10);
                            ofPopStyle();
                        }

                        totalCirclesMoved++;
                    }
                }
                circle_index++;

                if(totalCirclesMoved > 10) {
                    totalCirclesMoved = 0;
                    break;
                }
            }

            if(circle_index == circles.size()) {
                circle_index = 0;
            }
        }
    }

    if(dataHub->bDebug) {
//        for(int i=0; i<dataHub->messages->size(); i++) {
//            circles[i].draw();
//        }

        for(int i=0; i<circles.size(); i++) {
            circles[i].draw();
        }
        // ofDrawBitmapString(10, ofGetHeight() - 100, "")
        // dataHub->grayDiff->scaleIntoMe(tempImg);
        // dataHub->grayDiff->draw(400, 10);
        // cout << "1:" << tempImg.width << endl;

        tempImg.draw(ofGetWidth() - tempImg.width, 10);

        //cout << "2:" << tempImg.width << endl;
    }
}


