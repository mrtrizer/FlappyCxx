#ifndef GPRESENTER_H
#define GPRESENTER_H

#include <string>
#include <memory>

#include "gtools.h"

class GViewFactory;
class GView;

/// @brief Holds information about object representation need for view objects.
/// @details Contains a shared pointer to GView object, but doesn't calls any it's
/// methods except GView::externUpdate to say about state changing.
class GPresenter : public GTools::enable_sptr<GPresenter> {
public:
    virtual ~GPresenter(){}
    std::shared_ptr<GView> getGView(const GViewFactory & factory);
    void cleanGView();
    void updateView();
protected:
    /// Implement and call appropriate method from factory to get your own instance of GView.
    virtual std::shared_ptr<GView> makeGView(const GViewFactory & factory) = 0;
private:
    std::shared_ptr<GView> gView;
};

/// @brief Holds a spritesheet params. May be one solid frame or be divided into several equal parts.
class GPresenterSprite : public GPresenter {
public:
    GPresenterSprite(std::string path, float width, float height, int frameCnt = 1):
        path(path),
        width(width),
        height(height),
        frameCnt(frameCnt)
    {}
    virtual ~GPresenterSprite(){}
    inline std::string getPath() const { return path; }
    inline float getWidth() const { return width; }
    inline float getHeight() const { return height; }
    inline int getFrameCnt() const { return frameCnt; }
    void setFrameN(int frameN);
    inline int getFrameN() const { return frameN; }

protected:
    virtual std::shared_ptr<GView> makeGView(const GViewFactory & factory) override;
private:
    std::string path;
    float width;
    float height;
    /// Current frame pointer
    int frameN = 0;
    /// Summary frame count
    int frameCnt = 1;
};

/// Represents a circle shape.
class GPresenterCircle : public GPresenter {
public:
    GPresenterCircle(float r):
        r(r)
    {}
    virtual ~GPresenterCircle(){}
    inline float getR_() const { return r; }
protected:
    virtual std::shared_ptr<GView> makeGView(const GViewFactory & factory) override;
private:
    float r;
};

/// Represents a rectangle shape.
class GPresenterRect : public GPresenter {
public:
    GPresenterRect(float width, float height):
        width(width),
        height(height)
    {}
    virtual ~GPresenterRect(){}
    inline float getWidth() const { return width; }
    inline float getHeight() const { return height; }
protected:
    virtual std::shared_ptr<GView> makeGView(const GViewFactory & factory) override;
private:
    float width;
    float height;
};


#endif // GPRESENTER_H
