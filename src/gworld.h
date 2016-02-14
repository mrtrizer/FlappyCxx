#ifndef GWORLD_H
#define GWORLD_H

#include <thread>
#include <atomic>
#include <list>
#include "gobjcontainer.h"

/// @brief Game World
/// @details Contains and manages game objects.
/// Model in MVC terms.
/// Creates and manages gameloop thread.
class GWorld {
public:
    GWorld();
    virtual ~GWorld();
    void pause(){pauseFlag = true;}
    void resume(){pauseFlag = false;}
    inline GObjContainer & getObjTree() {return gObjContainer;}

protected:
    virtual void recalc(int){}

private:
    bool pauseFlag;
    GObjContainer gObjContainer;

    void run();
};

class GWorldFlappy: public GWorld
{
public:
    void flap();

protected:
    void recalc(int) override;

private:
    double speed;
};

#endif // GWORLD_H
