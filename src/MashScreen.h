#ifndef MashScreen_H
#define MashScreen_H

#include "Letter.h"
#include "MashEngine.h"
#include "Box2dMashEngine.h"

class MashScreen
{
    public:
        MashScreen();
        virtual ~MashScreen();

        vector<Letter *> letters;
        ofTrueTypeFont font;
        MashEngine *currentEngine;

        unsigned int rows, cols;

        void setup();
        void update();
        void draw();

    protected:

    private:
};

#endif // MashScreen_H
