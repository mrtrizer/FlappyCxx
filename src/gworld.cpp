#include "gworld.h"
#include <chrono>
#include <iostream>

/// 1000ms / 60fps
#define DELTA_T (1000 / 60)

using namespace std;

GWorld::GWorld():
    gThread(std::thread(&GWorld::run, this)),
    breakFlag(false),
    pauseFlag(false),
    gObjContainer(0,this)
{
    //game initialization
}

GWorld::~GWorld() {
    breakFlag = true;
    gThread.join();
}

void GWorld::run() {
    while (!breakFlag) {
        std::this_thread::sleep_for(std::chrono::milliseconds(DELTA_T));
        if (!pauseFlag)
            recalc(DELTA_T);
    }
}

void GWorldFlappy::recalc(int deltaT) {
    //do essentials
}
