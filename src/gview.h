#ifndef GVIEW_H
#define GVIEW_H

/// Interface.
/// View in MVC terms.
class GView
{
public:
    virtual ~GView(){}
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void redraw() = 0;
};

#endif // GVIEW_H
