#ifndef TEST_GOBJCIRCLE_H
#define TEST_GOBJCIRCLE_H

#include <QObject>
#include <QTest>

#include <memory>

#include <shapes/gobjcircle.h>
#include <shapes/gobjrect.h>

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
        auto gObj = gObjContainer->findChild(getCheckFunc(r));
        return std::dynamic_pointer_cast<GObjCircle>(gObj);
    }

    const int N = 10;
    const int R = 10;

private slots:
    void initTestCase() {

    }

    void getPosAbsolute() {
        auto gObjContainer = std::make_shared<GObj>();
        auto gObjSubContainer1 = gObjContainer->addChild<GObj>(std::make_shared<GObj>(GPos({10,0,0})));
        auto gObjSubContainer2 = gObjSubContainer1->addChild<GObj>(std::make_shared<GObj>(GPos({0,10,0})));
        auto gObjCircle = gObjSubContainer2->addChild<GObjCircle>(std::make_shared<GObjCircle>(10,GPos({10,10,0})));
        QVERIFY(gObjCircle->getAPos().getX() == 20);
        QVERIFY(gObjCircle->getAPos().getY() == 20);
    }

    void isIntersectWith() {
        auto gObjCircle = std::make_shared<GObjCircle>(10);
        auto gObjCircle1 = std::make_shared<GObjCircle>(10, GPos({10,0,0}));
        auto gObjCircle2 = std::make_shared<GObjCircle>(10, GPos({20,0,0}));
        auto gObjRect1 = std::make_shared<GObjRect>(10,10, GPos({0,0,0}));
        auto gObjRect2 = std::make_shared<GObjRect>(10,10, GPos({0,20,0}));
        QVERIFY(gObjCircle->isIntersectWith(gObjCircle1) == true);
        QVERIFY(gObjCircle->isIntersectWith(gObjCircle2) == false);
        QVERIFY(gObjCircle->isIntersectWith(gObjRect1) == true);
        QVERIFY(gObjCircle->isIntersectWith(gObjRect2) == false);
    }

    void findIntersectObjs() {
        auto root = std::make_shared<GObj>();
        auto mainCircle = root->ADD_CHILD(GObjCircle, 10, GPos({0,0,0}));
        auto intersect1 = root->ADD_CHILD(GObjCircle, 5, GPos({14,0,0}));
        auto intersect2 = root->ADD_CHILD(GObjCircle, 15, GPos({0,24,0}));
        auto intersectNo = root->ADD_CHILD(GObjCircle, 15, GPos({0,25,0}));
        QVERIFY(mainCircle->findIntersectObjs().size() == 2);
        QVERIFY(mainCircle->findIntersectObjs([intersect1](const std::shared_ptr<GObj> & i){
            return i == intersect1;}).size() == 1);
        QVERIFY(mainCircle->findIntersectObjs([intersect2](const std::shared_ptr<GObj> & i){
            return i == intersect2;}).size() == 1);
        QVERIFY(mainCircle->findIntersectObjs([intersectNo](const std::shared_ptr<GObj> & i){
            return i == intersectNo;}).size() == 0);
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
            gObjContainer->addChild<GObjCircle>(std::make_shared<GObjCircle>(i,GPos({(float)i,0,0})));
        for (int i = 0; i < N; i++)
            QVERIFY(findByRR(gObjContainer, i)->getPos().getX() == i);
        QVERIFY(gObjContainer->findChilds(false).size() == (unsigned int)N);
    }

    void remove_removeChild() {
        auto gObjContainer = std::make_shared<GObj>();
        gObjContainer->ADD_CHILD(GObjCircle,1);
        gObjContainer->ADD_CHILD(GObjCircle,2);
        QVERIFY(gObjContainer->findChilds().size() == 2);
        gObjContainer->removeChild(findByRR(gObjContainer, 1));
        QVERIFY_EXCEPTION_THROWN(findByRR(gObjContainer, 1),GObj::cant_find_child);
        QVERIFY(gObjContainer->findChilds().size() == 1);
        findByRR(gObjContainer, 2)->remove();
        QVERIFY(gObjContainer->findChilds().size() == 0);
    }

    void findChildR() {
        auto gObjContainer = std::make_shared<GObj>();

        for (int i = 0; i < N; i++) {
            auto gObjSubContainer = gObjContainer->addChild<GObj>(std::make_shared<GObj>());
            gObjSubContainer->addChild(std::make_shared<GObjCircle>(i,GPos({(float)i,0,0})));
        }
        for (int i = 0; i < N; i++)
            QVERIFY(findByRR(gObjContainer, i)->getPos().getX() == i);
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
                gObjSubContainer->addChild(std::make_shared<GObjCircle>(j,GPos({(float)j,0,0})));
        }
        //not recursive
        QVERIFY(gObjContainer->findChilds(false).size() == (unsigned int)N);
        //recursive
        QVERIFY(gObjContainer->findChilds().size() ==(unsigned int)N * (unsigned int)N + (unsigned int)N);
    }

    void cleanupTestCase() {
    }
};

#endif // TEST_GOBJCIRCLE_H
