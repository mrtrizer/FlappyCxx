#include <iostream>

#include "gworldmodel.h"

using namespace std;

GWorldModel::GWorldModel():
    pauseFlag(false),
    lastTime(chrono::steady_clock::now())
{}

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

void GWorldModel::init() {
    gObj = std::make_shared<GObj>();
    lastTime = chrono::steady_clock::now();
    init_();
}

void GWorldModel::deinit() {
    gObj.reset();
}
