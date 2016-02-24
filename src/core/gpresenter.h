#ifndef GPRESENTER_H
#define GPRESENTER_H

#include <string>
#include <memory>

class IGViewFactory;
class GView;

class GPresenter {
public:
    virtual ~GPresenter(){}
    std::shared_ptr<GView> getGView(const IGViewFactory & factory);
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
private:
    std::string path;
};

class GPresenterCircle : public GPresenter {
public:
    GPresenterCircle(float r):
        r(r)
    {}
    virtual ~GPresenterCircle(){}
    inline float getR() const { return r; }
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
private:
    float width;
    float height;
};


#endif // GPRESENTER_H
