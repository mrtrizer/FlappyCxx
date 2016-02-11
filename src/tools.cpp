#include <cmath>
#include <functional>

#include "tools.h"
#include "gobj.h"
#include "gobjcircle.h"
#include "gobjrect.h"

namespace Tools {
using namespace std;

double calcDist2D(const GObj & obj1, const GObj & obj2) {
    double dX = obj1.getPos().x - obj2.getPos().x;
    double dY = obj1.getPos().y - obj2.getPos().y;
    return sqrt(dX * dX + dY * dY);
}

bool isIntersect(const GObjCircle & obj1, const GObjCircle & obj2) {
    if ((obj1.getR() + obj2.getR()) > calcDist2D(obj1,obj2))
        return true;
    return false;
}

bool isIntersect(const GObjRect &, const GObjRect &) {
    throw not_implemented();
}

bool isIntersect(const GObjCircle &, const GObjRect &) {
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
template <typename GObjT1, typename GObjT2>
static void check(const GObj &gObj1, const GObj &gObj2) {
    try { //is it valid cast?
    auto gObjT1 = dynamic_cast<const GObjT1 &>(gObj1);
    auto gObjT2 = dynamic_cast<const GObjT2 &>(gObj2);
    throw Done(isIntersect(gObjT1, gObjT2)); //allright, return checking result
    } catch (std::bad_cast &) { //if bad cast, try to reverse and over
        try {
        auto gObjT1 = dynamic_cast<const GObjT2 &>(gObj1);
        auto gObjT2 = dynamic_cast<const GObjT1 &>(gObj2);
        throw Done(isIntersect(gObjT1, gObjT2)); //allright, return checking result
        } catch (std::bad_cast &) {} //we can't cast, ignore checking
    }
}

bool isIntersect(const GObj &gObj1, const GObj &gObj2) {
    try { //if checking done, catch Done exception
        check<GObjCircle, GObjCircle>(gObj1, gObj2);
        check<GObjRect, GObjCircle>(gObj1, gObj2);
        check<GObjRect, GObjRect>(gObj1, gObj2);
    } catch (Done & done) {
        return done.getResult();
    }
    //no appropriate intersect checking function
    throw unknown_intersect_obj();
}

}
