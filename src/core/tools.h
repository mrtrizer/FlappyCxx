#ifndef TOOLS_H
#define TOOLS_H

#include <memory>

class GObj;
class GColliderCircle;
class GColliderRect;

//TODO: Rename to GTools
namespace Tools
{
    /// Solution of diamond problem.
    class enable_shared_from_this_virtual_base: public std::enable_shared_from_this<enable_shared_from_this_virtual_base> {
    public:
        virtual ~enable_shared_from_this_virtual_base(){}
    };

    template <typename Base>
    class enable_shared_from_this_virtual: virtual public enable_shared_from_this_virtual_base {
    public:
        //TODO: Rename to shared_from_this. + Create template method shared_from_this_cast.
        std::shared_ptr<Base> shared_from_this_cast() {
            return std::dynamic_pointer_cast<Base>(shared_from_this());
        }
    };

    struct Rect {
        float x1;
        float y1;
        float x2;
        float y2;
    };

    bool isIntersect(const GObj &, const GObj &);
    class not_implemented {};
    class unknown_intersect_obj {};
}

#endif // TOOLS_H
