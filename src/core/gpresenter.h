#ifndef GPRESENTER_H
#define GPRESENTER_H

#include <string>
#include <memory>

#include "gtools.h"

class IGViewFactory;
class GView;

class GPresenter : public GTools::enable_sptr<GPresenter> {
public:
    virtual ~GPresenter(){}
    std::shared_ptr<GView> getGView(const IGViewFactory & factory);
protected:
    virtual std::shared_ptr<GView> makeGView(const IGViewFactory & factory) = 0;
private:
    std::shared_ptr<GView> gView;
};

class GPresenterSprite : public GPresenter {
public:
    GPresenterSprite(std::string path):
        path(path)
    {}
    virtual ~GPresenterSprite(){}
    inline std::string getPath() const { return path; }
protected:
    virtual std::shared_ptr<GView> makeGView(const IGViewFactory & factory) override;
private:
    std::string path;
};

class GPresenterCircle : public GPresenter {
public:
    GPresenterCircle(float r):
        r(r)
    {}
    virtual ~GPresenterCircle(){}
    inline float getR_() const { return r; }
protected:
    virtual std::shared_ptr<GView> makeGView(const IGViewFactory & factory) override;
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
    virtual std::shared_ptr<GView> makeGView(const IGViewFactory & factory) override;
private:
    float width;
    float height;
};


#endif // GPRESENTER_H
