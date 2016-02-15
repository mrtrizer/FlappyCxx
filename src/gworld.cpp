#include "gworld.h"
#include <chrono>
#include <iostream>

/// 1000ms / 60fps
#define DELTA_T (1000 / 60)

using namespace std;

GWorld::GWorld():
    pauseFlag(false),
    gObjContainer(std::make_shared<GObjContainer>())
{
    //game initialization
}

GWorld::~GWorld() {
}

void GWorld::run() {
    if (!pauseFlag)
        recalc(DELTA_T);
}

void GWorldFlappy::recalc(int deltaT) {
    //do essentials
}
