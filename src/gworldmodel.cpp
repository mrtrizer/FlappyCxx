#include "gworldmodel.h"
#include <chrono>
#include <iostream>

/// 1000ms / 60fps
#define DELTA_T (1000 / 60)

using namespace std;

GWorldModel::GWorldModel():
    pauseFlag(false),
    gObjContainer(std::make_shared<GObjContainer>())
{
    //game initialization
}

GWorldModel::~GWorldModel() {
}

void GWorldModel::run() {
    if (!pauseFlag)
        recalc(DELTA_T);
}

void GWorldFlappy::recalc(int deltaT) {
    //do essentials
}
