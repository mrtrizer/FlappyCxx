#include "score.h"

Score::Score(const GPos & pos):
    GObj(pos),
    numbers(3){

}

void Score::init(){
    numbers[0] = ADD_CHILD(GDecor,"numbers", 5, 5, POS(0,0,0),10);
}

void Score::recalc(DeltaT, const GContext &){
    numbers[0]->setFrameN(score % 10);
}
