#ifndef GPRESENTER_H
#define GPRESENTER_H

#include <string>
#include <memory>

#include "gtools.h"

class GViewFactory;
class GView;

class GPresenter : public GTools::enable_sptr<GPresenter> {
public:
    virtual ~GPresenter(){}
    std::shared_ptr<GView> getGView(const GViewFactory & factory);
    void cleanGView();
    void updateView();
protected:
    virtual std::shared_ptr<GView> makeGView(const GViewFactory & factory) = 0;
private:
    std::shared_ptr<GView> gView;
};

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
    inline void setFrameN(int frameN) { this->frameN = frameN; updateView(); }
    int getFrameN() const { return frameN; }

protected:
    virtual std::shared_ptr<GView> makeGView(const GViewFactory & factory) override;
private:
    std::string path;
    float width;
    float height;
    int frameN = 0;
    int frameCnt = 1;
};

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
