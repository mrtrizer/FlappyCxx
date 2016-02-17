#ifndef GVIEW_H
#define GVIEW_H

#include "shader.h"
#include "tools.h"

class GView : public Tools::enable_shared_from_this_virtual<GView> {
public:
    virtual ~GView(){}
    virtual void draw(const GLfloat *, const GLfloat *) = 0;
};

//This block of code selects View implementation and replaces View with a fake if it's not used.
#ifdef VIEW_TYPE
template <typename View>
class GViewCustom : public View {
public:
    using View::View;
};
#else
class GViewCustom: public GView {
public:
    GViewCustom(...){}
    void draw(const GLfloat *, const GLfloat *){}
};
#endif

#ifdef VIEW_TYPE
#define CONCAT_NAME_(viewType, viewClass) GViewCustom<viewType ## _ ## GView ::viewClass>
#define CONCAT_NAME(viewType, viewClass) CONCAT_NAME_(viewType, viewClass)
#define SELECT_VIEW(viewClass) CONCAT_NAME( VIEW_TYPE ,viewClass)
#else
#define SELECT_VIEW(viewClass) GViewCustom
#endif

#endif // GVIEW_H
