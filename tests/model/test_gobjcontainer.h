#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include <functional>
#include <QObject>
#include <QDebug>
#include <QTest>
#include <QTime>

#include <gobjcontainer.h>
#include <gobjcircle.h>

class Test_GObjContainer : public QObject {
    Q_OBJECT

    auto getCheckFunc(int r) {
        return [r](const std::shared_ptr<GObj> & i) { //check if the droids we're looking for?
            auto gObjCircle = std::dynamic_pointer_cast<GObjCircle>(i);
            if (gObjCircle == nullptr)
                return false;
            return gObjCircle->getR() == r;
        };
    }

    auto findByRR(const GObj::GObjContainerP & gObjContainer, int r) {
        auto gObj = gObjContainer->findChildR(getCheckFunc(r));
        return std::dynamic_pointer_cast<GObjCircle>(gObj);
    }

    const int N = 10;
    const int R = 10;

private slots:

    void initTestCase() {

    }

    void addChild_one_item() {
        auto gObjContainer = std::make_shared<GObjContainer>();
        auto gObjCircle = gObjContainer->addChild<GObjCircle>(std::make_shared<GObjCircle>(R));
        QVERIFY(gObjCircle->getR() == R);
        QVERIFY(findByRR(gObjContainer, R)->getR() == R);
    }

    void addChild_multiple_item() {
        auto gObjContainer = std::make_shared<GObjContainer>();
        for (int i = 0; i < N; i++)
            gObjContainer->addChild<GObjCircle>(std::make_shared<GObjCircle>(i,GObj::Pos({(float)i,0,0})));
        for (int i = 0; i < N; i++)
            QVERIFY(findByRR(gObjContainer, i)->getPos().x == i);
        QVERIFY(gObjContainer->getChilds().size() == (unsigned int)N);
    }

    void removeChild() {
        auto gObjContainer = std::make_shared<GObjContainer>();
        gObjContainer->addChild<GObjCircle>(std::make_shared<GObjCircle>(R));
        QVERIFY(gObjContainer->getChilds().size() == 1);
        gObjContainer->removeChild(findByRR(gObjContainer, R));
        QVERIFY_EXCEPTION_THROWN(findByRR(gObjContainer, R),GObjContainer::no_child_with_id_exception);
    }

    void findChildR() {
        auto gObjContainer = std::make_shared<GObjContainer>();

        for (int i = 0; i < N; i++) {
            auto gObjSubContainer = gObjContainer->addChild<GObjContainer>(std::make_shared<GObjContainer>());
            gObjSubContainer->addChild(std::make_shared<GObjCircle>(i,GObj::Pos({(float)i,0,0})));
        }
        for (int i = 0; i < N; i++)
            QVERIFY(findByRR(gObjContainer, i)->getPos().x == i);
    }

    void getRoot() {
        auto gObjContainer = std::make_shared<GObjContainer>();
        auto gObjSubContainer1 = gObjContainer->addChild<GObjContainer>(std::make_shared<GObjContainer>());
        auto gObjSubContainer2 = gObjSubContainer1->addChild<GObjContainer>(std::make_shared<GObjContainer>());
        QVERIFY(gObjSubContainer2->getRoot() == gObjContainer);
    }

    void getChilds_getChildsR() {
        auto gObjContainer = std::make_shared<GObjContainer>();
        for (int i = 0; i < N; i++) {
            auto gObjSubContainer = gObjContainer->addChild<GObjContainer>(std::make_shared<GObjContainer>());
            for (int j = 0; j < N; j++)
                gObjSubContainer->addChild(std::make_shared<GObjCircle>(j,GObj::Pos({(float)j,0,0})));
        }
        //not recursive
        QVERIFY(gObjContainer->getChilds().size() == (unsigned int)N);
        //recursive
        QVERIFY(gObjContainer->getChildsR().size() ==(unsigned int)N * (unsigned int)N);
    }

    void cleanupTestCase() {
    }
};

#endif // TESTFUNCTIONS_H
