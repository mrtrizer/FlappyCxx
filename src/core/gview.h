#ifndef GVIEW_H
#define GVIEW_H

#include "gtools.h"

class GPresenter;

/// @brief Interface for all object views.
/// Contains abstract draw() method for implementation in
/// derived classes.
class GView : public GTools::enable_sptr<GView> {
public:
    typedef float * PMatrix;
    typedef float * MVMatrix;
    virtual ~GView(){}
    virtual void draw(const PMatrix, const MVMatrix) = 0;
    virtual void update(const GPresenter &) {}
};

#endif // GVIEW_H
