#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include <functional>
#include <QObject>
#include <QDebug>
#include <QTest>
#include <QTime>
#include "assert.h"

#include <gobjcontainer.h>

class GObjTest : public GObj_CRTP<GObjTest> {
public:
    explicit GObjTest(): GObj_CRTP() {
        qDebug() << "[constructor] GObjTest";
    }
    ~GObjTest() {
        qDebug() << "[destructor] GObjTest";
    }
};

class GObjContainerTest : public GObj_CRTP<GObjContainerTest, GObjContainer> {
public:
    explicit GObjContainerTest(): GObj_CRTP() {
        qDebug() << "[constructor] GObjContainerTest";
    }
    ~GObjContainerTest() {
        qDebug() << "[destructor] GObjContainerTest";
    }
};

class Test_GObjContainer : public QObject {
    Q_OBJECT

    const unsigned int TEST_N = 1;
    GObjContainerTest * gObjContainer;

private slots:

    void initTestCase() {
        gObjContainer = new GObjContainerTest();
        assert(TEST_N > 0);
        for (unsigned int i = 0; i < TEST_N; i++)
            gObjContainer->addChild(GObjContainerTest());
        int offset = 0;
        for (unsigned int i = 0; i < TEST_N; i++) {
            offset += TEST_N;
//            for (unsigned int j = 0; j < TEST_N; j++) {
//                GObjContainerTest * gObjSubContainer =
//                        dynamic_cast<GObjContainerTest *>(gObjContainer->findChild(i + 1));
//                gObjSubContainer->addChild(GObjTest());
//            }
        }
    }

    void addChild_test() {
        GObj * gObj = gObjContainer->addChild(GObjTest());
        gObjContainer->removeChild(gObj);
    }

    void removeChild_test() {
        GObj * gObj = gObjContainer->addChild(GObjTest());
        gObjContainer->removeChild(gObj);
        QVERIFY_EXCEPTION_THROWN(gObjContainer->removeChild(gObj),
                                 GObjContainer::no_child_with_id_exception);
    }

    void findChild_test() {
//        QVERIFY(gObjContainer->findChild(1)->getId() == 1);
//        QVERIFY_EXCEPTION_THROWN(gObjContainer->findChild(TEST_N + 1),
//                                 GObjContainer::no_child_with_id_exception);
    }

    void findChildR_test() {
//        QVERIFY(gObjContainer->findChildR(1)->getId() == 1);
//        QVERIFY_EXCEPTION_THROWN(gObjContainer->findChildR(TEST_N * TEST_N + TEST_N + 1),
//                                 GObjContainer::no_child_with_id_exception);
    }

    void getChilds_test() {
        GObj::GObjPList gObjPList = gObjContainer->getChilds();

        QVERIFY(gObjPList.size() == TEST_N);

//        for (unsigned int i = 0; i < TEST_N; i++) {
//            QVERIFY(gObjPList.front()->getId() == i + 1);
//            gObjPList.pop_front();
//        }
    }

    void getChildsR_test() {
        GObj::GObjPList gObjPList = gObjContainer->getChildsR();

        QVERIFY(gObjPList.size() == TEST_N * TEST_N);
    }

    void cleanupTestCase() {
        delete gObjContainer;
    }
};

#endif // TESTFUNCTIONS_H
