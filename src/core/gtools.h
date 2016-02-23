#ifndef GTOOLS_H
#define GTOOLS_H

#include <memory>

class GObj;
class GColliderCircle;
class GColliderRect;

namespace GTools
{
    /// Solution of diamond problem.
    class enable_shared_from_this_virtual_base: public std::enable_shared_from_this<enable_shared_from_this_virtual_base> {
    public:
        virtual ~enable_shared_from_this_virtual_base(){}
    };

    template <typename Base>
    class enable_shared_from_this_virtual: virtual public enable_shared_from_this_virtual_base {
    public:
        std::shared_ptr<Base> shared_from_this() {
            return std::dynamic_pointer_cast<Base>(enable_shared_from_this::shared_from_this());
        }
    };

    bool isIntersect(const GObj &, const GObj &);
    class not_implemented {};
    class unknown_intersect_obj {};
}

#endif // GTOOLS_H
