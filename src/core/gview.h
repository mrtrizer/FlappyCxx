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
    void redraw(const PMatrix & pMartrix, const MVMatrix & mvMatrix) {
        auto gPresenterLock = gPresenter.lock();
        if (gPresenterLock != nullptr)
            update(*gPresenterLock);
        draw(pMartrix, mvMatrix);
    }
    void externUpdate(const std::shared_ptr<GPresenter> & gPresenter) {
        this->gPresenter = gPresenter;
    }
protected:
    virtual void draw(const PMatrix, const MVMatrix) = 0;
    virtual void update(const GPresenter & gPresenter) {}
private:
    std::weak_ptr<GPresenter> gPresenter;
};

#endif // GVIEW_H
