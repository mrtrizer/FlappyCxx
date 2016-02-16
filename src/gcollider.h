#ifndef GCOLLIDER_H
#define GCOLLIDER_H

class GCollider {
public:
    GCollider();
    virtual ~GCollider(){}
};

class GColliderCircle: public GCollider {
public:
    typedef double R;

    explicit GColliderCircle(R r = 0):r(r){}
    inline void setR(R r) {this->r = r;}
    inline R getR() const {return r;}

private:
    R r = 0;
};

class GColliderRect: public GCollider {

};

#endif // GCOLLIDER_H
