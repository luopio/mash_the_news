#ifndef MASHENGINE_H
#define MASHENGINE_H

#include "Letter.h"

class MashEngine
{
    public:
        MashEngine();
        virtual ~MashEngine();

        void setup(vector<Letter *> &v);
        void update();
        void draw();

    protected:
    private:
};

#endif // MASHENGINE_H
