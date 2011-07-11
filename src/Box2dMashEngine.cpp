#include "Box2dMashEngine.h"

Box2dMashEngine::Box2dMashEngine(DataHub &h)
{
    dataHub = &h;
    box2d.init();
    box2d.setGravity(0, 0.01);
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
                ofxBox2dCircle circle;
                circle.setPhysics(1.5, 0.53, 0.1);
                circle.setup(box2d.getWorld(), letter_index * FONT_SIZE + 20,
                             i * (FONT_SIZE + 10) + 100,
                             FONT_SIZE);
                circles.push_back(circle);
                if(letter_index > 0) {
                    ofxBox2dJoint* j = new ofxBox2dJoint();
                    j->setWorld(box2d.getWorld());
                    j->addJoint(circles[circle_index - 1].body,
                                circles[circle_index].body,
                                2.0, 0.7);
                    joints.push_back(j);
                }
                circle_index++;
                letter_index++;
            }
        }
    }

    debug = true;
    bMouseForce = true;

    strength = 0.1f;
    damping  = 0.7f;
    minDis   = 100;

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

    /* apply physics to the physics objects based on the kinect image */
    tempImg.scaleIntoMe(*(dataHub->grayDiff));



    unsigned char *pixels = tempImg.getPixels();
    circle_index = 0;
    for(int i = 0; i < tempImg.width * tempImg.height; i++) {
        if(pixels[i] > 50) {
            int screen_x = i % tempImg.width * ofGetWidth()  / tempImg.width;
            int screen_y = i / tempImg.width * ofGetHeight() / tempImg.height;

            circles[circle_index].addAttractionPoint(ofPoint(screen_x, screen_y), strength, minDis);
            circles[circle_index].addDamping(damping, damping);
            circle_index++;
            if(circle_index == circles.size()) {
                circle_index = 0;
                break;
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

    if(bMouseForce) { // && false) {
        for(int i=0; i<circles.size(); i++) {
            circles[i].addAttractionPoint(ofPoint(*(dataHub->mouseX), *(dataHub->mouseY)), strength, minDis);
            //circles[i].addDamping(damping, damping);
        }
    }
}

void Box2dMashEngine::draw()
{

    if(debug) {
        for(int i=0; i<dataHub->messages->size(); i++) {
            circles[i].draw();
        }
        for(int i=0; i<circles.size(); i++) {
            circles[i].draw();
        }
        // ofDrawBitmapString(10, ofGetHeight() - 100, "")
        // dataHub->grayDiff->scaleIntoMe(tempImg);
        // dataHub->grayDiff->draw(400, 10);
        // cout << "1:" << tempImg.width << endl;

        tempImg.draw(400, 10);

        //cout << "2:" << tempImg.width << endl;
    }
}


