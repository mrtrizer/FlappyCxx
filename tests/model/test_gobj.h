#ifndef TEST_GOBJCIRCLE_H
#define TEST_GOBJCIRCLE_H

#include <QObject>
#include <QTest>

#include <memory>

#include <gobjcircle.h>
#include <gobjcontainer.h>

class Test_GObj : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase() {

    }

    void getPosAbsolute() {
        auto gObjContainer = std::make_shared<GObjContainer>();
        auto gObjSubContainer1 = gObjContainer->addChild<GObjContainer>(std::make_shared<GObjContainer>(GObj::Pos({10,0,0})));
        auto gObjSubContainer2 = gObjSubContainer1->addChild<GObjContainer>(std::make_shared<GObjContainer>(GObj::Pos({0,10,0})));
        auto gObjCircle = gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(10,GObj::Pos({10,10,0})));
        QVERIFY(gObjCircle->getPosAbsolute().x == 20);
        QVERIFY(gObjCircle->getPosAbsolute().y == 20);
    }

    void isIntersectWith() {
        GObjCircle gObjCircle (10);
        GObjCircle gObjCircle1(10, {10,0,0});
        GObjCircle gObjCircle2(10, {20,0,0});
        QVERIFY(gObjCircle.isIntersectWith(gObjCircle1) == true);
        QVERIFY(gObjCircle.isIntersectWith(gObjCircle2) == false);
    }

    void cleanupTestCase() {
    }
};

#endif // TEST_GOBJCIRCLE_H
