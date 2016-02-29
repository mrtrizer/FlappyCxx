#include "score.h"

Score::Score(const GPos & pos):
    GObj(pos),
    numbers(CAPACITY){

}

void Score::init(){
    for (int i = 0; i < CAPACITY; i++)
        numbers[i] = ADD_CHILD(GPresenterSprite,"numbers", 5, 5, POS(i * 4.0f,0,0),10);
}

void Score::recalc(DeltaT, const GContext &){
    int scoreTmp = score;
    for (int i = CAPACITY - 1; i >= 0; i--) {
        numbers[i]->setFrameN(scoreTmp % 10);
        scoreTmp /= 10;
    }
}
