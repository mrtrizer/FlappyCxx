#include <cmath>
#include <functional>

#include "tools.h"
#include "gcollider.h"
#include "gobj.h"

namespace Tools {
using namespace std;

double calcDist2D(const GObj & obj1, const GObj & obj2) {
    double dX = obj1.getPosAbsolute().x - obj2.getPosAbsolute().x;
    double dY = obj1.getPosAbsolute().y - obj2.getPosAbsolute().y;
    return sqrt(dX * dX + dY * dY);
}

bool isIntersect(const GColliderCircle & obj1, const GColliderCircle & obj2) {
    if ((obj1.getR() + obj2.getR()) > calcDist2D(dynamic_cast<const GObj &>(obj1),dynamic_cast<const GObj &>(obj2)))
        return true;
    return false;
}

bool isIntersect(const GColliderRect &, const GColliderCircle &) {
    throw not_implemented();
}

bool isIntersect(const GColliderCircle &, const GColliderRect &) {
    throw not_implemented();
}


bool isIntersect(const GColliderRect &, const GColliderRect &) {
    throw not_implemented();
}

class Done {
public:
    Done(bool result): result(result){}
    inline bool getResult() const {return result;}
private:
    bool result;
};

//Die matherfucker die!
template <typename GColliderT1, typename GColliderT2>
static void check(const GObj &gObj1, const GObj &gObj2) {
    try { //is it valid cast?
    auto gColliderT1 = dynamic_cast<const GColliderT1 &>(gObj1);
    auto gColliderT2 = dynamic_cast<const GColliderT2 &>(gObj2);
    throw Done(isIntersect(gColliderT1, gColliderT2)); //allright, return checking result
    } catch (std::bad_cast &) { //if bad cast, try to reverse and over
        try {
        auto gColliderT1 = dynamic_cast<const GColliderT2 &>(gObj1);
        auto gColliderT2 = dynamic_cast<const GColliderT1 &>(gObj2);
        throw Done(isIntersect(gColliderT1, gColliderT2)); //allright, return checking result
        } catch (std::bad_cast &) {} //we can't cast, ignore checking
    }
}

bool isIntersect(const GObj &gObj1, const GObj &gObj2) {
    try { //if checking done, catch Done exception
        check<GColliderCircle, GColliderCircle>(gObj1, gObj2);
        check<GColliderRect, GColliderCircle>(gObj1, gObj2);
        check<GColliderRect, GColliderRect>(gObj1, gObj2);
    } catch (Done & done) {
        return done.getResult();
    }
    //no appropriate intersect checking function
    throw unknown_intersect_obj();
}

}
