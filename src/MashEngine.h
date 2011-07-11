#ifndef MASHENGINE_H
#define MASHENGINE_H

#include "DataHub.h"

class MashEngine
{
    public:
        MashEngine();
        virtual ~MashEngine();

        virtual void setup();
        virtual void update();
        virtual void draw();

        bool debug;

        float strength;
        float damping;
        float minDis;

    protected:
    private:
};

#endif // MASHENGINE_H
