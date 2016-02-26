#include "coin.h"
#include "shapes/ganimation.h"

void Coin::init() {
    ADD_CHILD(GAnimation,"coin", RADIUS * 2, RADIUS * 2, POS(-RADIUS, -RADIUS, 20),2,0.3);
}
