#ifndef GTOOLS_H
#define GTOOLS_H

#include <memory>

#ifdef QT_CORE_LIB
#include <QDebug>
#define  LOGI(...) qDebug(__VA_ARGS__)
#define  LOGE(...) qDebug(__VA_ARGS__)
#else
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

class GObj;
class GColliderCircle;
class GColliderRect;

namespace GTools
{
    /// Solution of diamond problem.
    class enable_sptr_vbase: public std::enable_shared_from_this<enable_sptr_vbase> {
    public:
        virtual ~enable_sptr_vbase(){}
    };

    template <typename Base>
    class enable_sptr: virtual public enable_sptr_vbase {
    public:
        std::shared_ptr<Base> shared_from_this() {
            return std::dynamic_pointer_cast<Base>(enable_shared_from_this::shared_from_this());
        }
    };

    bool isIntersect(const GObj &, const GObj &);
    bool isPowOfTwo(int x);

    class not_implemented {};
    class unknown_intersect_obj {};
}

#endif // GTOOLS_H
