#ifndef GWORLD_H
#define GWORLD_H

#include <thread>
#include <atomic>
#include <list>
#include <memory>

#include "gobjcontainer.h"

/// @brief Game World
/// @details Contains and manages game objects.
/// Model in MVC terms.
/// Creates and manages gameloop thread.
class GWorldModel {
public:
    GWorldModel();
    virtual ~GWorldModel();
    void pause(){pauseFlag = true;}
    void resume(){pauseFlag = false;}
    inline std::shared_ptr<GObjContainer> getRoot() {return gObjContainer;}

protected:
    virtual void recalc(int){}

private:
    bool pauseFlag;
    std::shared_ptr<GObjContainer> gObjContainer;

    void run();
};

class GWorldFlappy: public GWorldModel
{
public:
    void flap();

protected:
    void recalc(int) override;

private:
    double speed;
};

#endif // GWORLD_H
