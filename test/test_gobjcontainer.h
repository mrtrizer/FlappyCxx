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
    GObjTest(Id id): GObj_CRTP(id) {
        qDebug() << "[constructor] GObjTest Id:" << getId();
    }
    ~GObjTest() {
        qDebug() << "[destructor] GObjTest Id:" << getId();
    }
};

class GObjContainerTest : public GObj_CRTP<GObjContainerTest, GObjContainer> {
public:
    GObjContainerTest(Id id): GObj_CRTP(id) {
        qDebug() << "[constructor] GObjContainerTest Id:" << getId();
    }
    ~GObjContainerTest() {
        qDebug() << "[destructor] GObjContainerTest Id:" << getId();
    }
};

class Test_GObjContainer : public QObject {
    Q_OBJECT

    const unsigned int TEST_N = 1;
    const GObjContainerTest::Id ID = TEST_N * TEST_N + TEST_N + 1;
    GObjContainerTest * gObjContainer;

private slots:

    void initTestCase() {
        gObjContainer = new GObjContainerTest(0);
        assert(TEST_N > 0);
        for (unsigned int i = 0; i < TEST_N; i++)
            gObjContainer->addChild(GObjContainerTest(i + 1));
        int offset = 0;
        for (unsigned int i = 0; i < TEST_N; i++) {
            offset += TEST_N;
            for (unsigned int j = 0; j < TEST_N; j++) {
                GObjContainerTest * gObjSubContainer =
                        dynamic_cast<GObjContainerTest *>(gObjContainer->findChild(i + 1));
                gObjSubContainer->addChild(GObjTest(offset + j + 1));
            }
        }
    }

    void addChild_test() {
        gObjContainer->addChild(GObjTest(ID));
        QVERIFY_EXCEPTION_THROWN(gObjContainer->addChild(GObjTest(ID)),
                                 GObjContainerTest::obj_id_exists_exception);
        gObjContainer->removeChild(ID);
    }

    void removeChild_test() {
        gObjContainer->addChild(GObjTest(ID));
        gObjContainer->removeChild(ID);
        QVERIFY_EXCEPTION_THROWN(gObjContainer->removeChild(ID),
                                 GObjContainerTest::no_child_with_id_exception);
    }

    void findChild_test() {
        QVERIFY(gObjContainer->findChild(1)->getId() == 1);
        QVERIFY_EXCEPTION_THROWN(gObjContainer->findChild(TEST_N + 1),
                                 GObjContainerTest::no_child_with_id_exception);
    }

    void findChildR_test() {
        QVERIFY(gObjContainer->findChildR(TEST_N + 1)->getId() == TEST_N + 1);
        QVERIFY_EXCEPTION_THROWN(gObjContainer->findChildR(TEST_N * TEST_N + TEST_N + 1),
                                 GObjContainerTest::no_child_with_id_exception);
    }

    void getChilds_test() {
        GObj::GObjPList gObjPList = gObjContainer->getChilds();

        QVERIFY(gObjPList.size() == TEST_N);

        for (unsigned int i = 0; i < TEST_N; i++) {
            QVERIFY(gObjPList.front()->getId() == i + 1);
            gObjPList.pop_front();
        }
    }

    void getChildsR_test() {
        GObj::GObjPList gObjPList = gObjContainer->getChildsR();

        QVERIFY(gObjPList.size() == TEST_N * TEST_N);
    }

    void deinitTestCase() {
        delete gObjContainer;
    }
};

#endif // TESTFUNCTIONS_H
