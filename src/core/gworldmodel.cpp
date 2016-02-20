#include <iostream>

#include "gworldmodel.h"

#define DELTA_T (1.0 / 10.0)

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
        auto objects = getRoot()->findChildsR();
        for (auto i : objects) {
            i->recalc(DELTA_T);
        }
        recalc(DELTA_T);
    }
}
