#ifndef GWORLD_H
#define GWORLD_H

#include <thread>
#include <atomic>
#include <list>
#include "gobjcontainer.h"

/// @brief Game World
/// @details Contains and manages game objects.
/// Model in MVC terms.
/// Thread-save.
/// Creates and manages gameloop thread.
class GWorld
{
public:
    GWorld();
    virtual ~GWorld();
    void pause(){pauseFlag = true;}
    void resume(){pauseFlag = false;}
    GObjContainer getObjTree();

protected:
    virtual void recalc(int){}

private:
    std::thread gThread;
    std::atomic<bool> breakFlag;
    std::atomic<bool> pauseFlag;
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
