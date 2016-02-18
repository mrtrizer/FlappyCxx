#include <iostream>

#include "gworldmodel.h"

/// 1000ms / 60fps
#define DELTA_T (1000 / 60)

using namespace std;

GWorldModel::GWorldModel():
    pauseFlag(false),
    gObj(std::make_shared<GObj>())
{
    //game initialization
}

GWorldModel::~GWorldModel() {
}

void GWorldModel::run() {
    if (!pauseFlag) {
        auto objects = getRoot()->getChildsR();
        for (auto i : objects) {
            i->recalc(DELTA_T);
        }
        recalc(DELTA_T);
    }
}

void GWorldFlappy::recalc(GObj::DeltaT) {

}
