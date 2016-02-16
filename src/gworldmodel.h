#ifndef GWORLDMODEL_H
#define GWORLDMODEL_H

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
    void run();

protected:
    virtual void recalc(GObj::DeltaT) = 0;

private:
    bool pauseFlag;
    std::shared_ptr<GObjContainer> gObjContainer;
};

class GWorldFlappy: public GWorldModel
{
public:
    void flap();

protected:
    void recalc(GObj::DeltaT) override;

private:
    double speed;
};

#endif // GWORLDMODEL_H
