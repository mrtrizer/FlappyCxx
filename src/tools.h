#ifndef TOOLS_H
#define TOOLS_H

class GObjCircle;
class GObjRect;
class GObj;

namespace Tools
{
    double calcDist2D(const GObj &, const GObj &);
    bool isIntersect(const GObjCircle &, const GObjCircle &);
    bool isIntersect(const GObjRect &, const GObjRect &);
    bool isIntersect(const GObjCircle &, const GObjRect &);
    bool isIntersect(const GObj &, const GObj &);
    class not_implemented {};
    class unknown_intersect_obj {};
}

#endif // TOOLS_H
