#ifndef TOOLS_H
#define TOOLS_H

class GObj;
class GColliderCircle;
class GColliderRect;

namespace Tools
{
    double calcDist2D(const GObj &, const GObj &);
    bool isIntersect(const GObj &, const GObj &);
    class not_implemented {};
    class unknown_intersect_obj {};
}

#endif // TOOLS_H
