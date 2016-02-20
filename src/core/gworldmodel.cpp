#include <iostream>

#include "gworldmodel.h"

using namespace std;

GWorldModel::GWorldModel():
    pauseFlag(false),
    gObj(std::make_shared<GObj>()),
    lastTime(chrono::steady_clock::now())
{
    //game initialization
}

GWorldModel::~GWorldModel() {
}

void GWorldModel::run() {
    auto newTime = chrono::steady_clock::now();
    float deltaT = chrono::duration <float, milli> (newTime - lastTime).count() / 1000.0f;
    lastTime = newTime;
    if (!pauseFlag) {
        auto objects = getRoot()->findChilds();
        for (auto i : objects)
            i->recalc(deltaT);
        recalc(deltaT);
    }
}
