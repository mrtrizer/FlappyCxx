#ifndef GWORLDMODEL_H
#define GWORLDMODEL_H

#include <thread>
#include <atomic>
#include <list>
#include <memory>

#include "gobj.h"
#include "gobjcamera.h"

/// @brief Game World
/// @details Contains and manages game objects.
/// Model in MVC terms.
class GWorldModel {
public:
    GWorldModel();
    virtual ~GWorldModel();
    void pause(){pauseFlag = true;}
    void resume(){pauseFlag = false;}
    inline std::shared_ptr<GObj> getRoot() {return gObj;}
    void run();
    void setActiveCamera(const std::shared_ptr<GObjCamera> & camera) {this->activeCamera = camera;}
    std::shared_ptr<GObjCamera> getActiveCamera() const {return activeCamera;}

protected:
    virtual void recalc(GObj::DeltaT) = 0;

private:
    bool pauseFlag;
    std::shared_ptr<GObj> gObj;
    std::shared_ptr<GObjCamera> activeCamera;
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
