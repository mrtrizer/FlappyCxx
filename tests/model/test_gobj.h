#ifndef TEST_GOBJCIRCLE_H
#define TEST_GOBJCIRCLE_H

#include <QObject>
#include <QTest>

#include <memory>

#include <gobjcircle.h>
#include <gobjrect.h>

class Test_GObj : public QObject
{
    Q_OBJECT

    auto getCheckFunc(int r) {
        return [r](const std::shared_ptr<GObj> & i) { //check if the droids we're looking for?
            auto gObjCircle = std::dynamic_pointer_cast<GObjCircle>(i);
            if (gObjCircle == nullptr)
                return false;
            return gObjCircle->getR() == r;
        };
    }

    auto findByRR(const GObj::GObjP & gObjContainer, int r) {
        auto gObj = gObjContainer->findChildR(getCheckFunc(r));
        return std::dynamic_pointer_cast<GObjCircle>(gObj);
    }

    const int N = 10;
    const int R = 10;

private slots:
    void initTestCase() {

    }

    void getPosAbsolute() {
        auto gObjContainer = std::make_shared<GObj>();
        auto gObjSubContainer1 = gObjContainer->addChild<GObj>(std::make_shared<GObj>(GObj::Pos({10,0,0})));
        auto gObjSubContainer2 = gObjSubContainer1->addChild<GObj>(std::make_shared<GObj>(GObj::Pos({0,10,0})));
        auto gObjCircle = gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(10,GObj::Pos({10,10,0})));
        QVERIFY(gObjCircle->getPosAbsolute().x == 20);
        QVERIFY(gObjCircle->getPosAbsolute().y == 20);
    }

    void isIntersectWith() {
        auto gObjCircle = std::make_shared<GObjCircle>(10);
        auto gObjCircle1 = std::make_shared<GObjCircle>(10, GObj::Pos({10,0,0}));
        auto gObjCircle2 = std::make_shared<GObjCircle>(10, GObj::Pos({20,0,0}));
        auto gObjRect1 = std::make_shared<GObjRect>(10,10, GObj::Pos({0,0,0}));
        auto gObjRect2 = std::make_shared<GObjRect>(10,10, GObj::Pos({0,20,0}));
        QVERIFY(gObjCircle->isIntersectWith(gObjCircle1) == true);
        QVERIFY(gObjCircle->isIntersectWith(gObjCircle2) == false);
        QVERIFY(gObjCircle->isIntersectWith(gObjRect1) == true);
        QVERIFY(gObjCircle->isIntersectWith(gObjRect2) == false);
    }

    void addChild_one_item() {
        auto gObjContainer = std::make_shared<GObj>();
        auto gObjCircle = gObjContainer->addChild<GObjCircle>(std::make_shared<GObjCircle>(R));
        QVERIFY(gObjCircle->getR() == R);
        QVERIFY(findByRR(gObjContainer, R)->getR() == R);
    }

    void addChild_multiple_item() {
        auto gObjContainer = std::make_shared<GObj>();
        for (int i = 0; i < N; i++)
            gObjContainer->addChild<GObjCircle>(std::make_shared<GObjCircle>(i,GObj::Pos({(float)i,0,0})));
        for (int i = 0; i < N; i++)
            QVERIFY(findByRR(gObjContainer, i)->getPos().x == i);
        QVERIFY(gObjContainer->getChilds().size() == (unsigned int)N);
    }

    void removeChild() {
        auto gObjContainer = std::make_shared<GObj>();
        gObjContainer->addChild<GObjCircle>(std::make_shared<GObjCircle>(R));
        QVERIFY(gObjContainer->getChilds().size() == 1);
        gObjContainer->removeChild(findByRR(gObjContainer, R));
        QVERIFY_EXCEPTION_THROWN(findByRR(gObjContainer, R),GObj::cant_find_child);
    }

    void findChildR() {
        auto gObjContainer = std::make_shared<GObj>();

        for (int i = 0; i < N; i++) {
            auto gObjSubContainer = gObjContainer->addChild<GObj>(std::make_shared<GObj>());
            gObjSubContainer->addChild(std::make_shared<GObjCircle>(i,GObj::Pos({(float)i,0,0})));
        }
        for (int i = 0; i < N; i++)
            QVERIFY(findByRR(gObjContainer, i)->getPos().x == i);
    }

    void getRoot() {
        auto gObjContainer = std::make_shared<GObj>();
        auto gObjSubContainer1 = gObjContainer->addChild<GObj>(std::make_shared<GObj>());
        auto gObjSubContainer2 = gObjSubContainer1->addChild<GObj>(std::make_shared<GObj>());
        QVERIFY(gObjSubContainer2->getRoot() == gObjContainer);
    }

    void getChilds_getChildsR() {
        auto gObjContainer = std::make_shared<GObj>();
        for (int i = 0; i < N; i++) {
            auto gObjSubContainer = gObjContainer->addChild<GObj>(std::make_shared<GObj>());
            for (int j = 0; j < N; j++)
                gObjSubContainer->addChild(std::make_shared<GObjCircle>(j,GObj::Pos({(float)j,0,0})));
        }
        //not recursive
        QVERIFY(gObjContainer->getChilds().size() == (unsigned int)N);
        //recursive
        QVERIFY(gObjContainer->getChildsR().size() ==(unsigned int)N * (unsigned int)N + (unsigned int)N + 1);
    }

    void cleanupTestCase() {
    }
};

#endif // TEST_GOBJCIRCLE_H
