#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include <functional>
#include <QObject>
#include <QDebug>
#include <QTest>
#include <QTime>
#include "assert.h"

#include <gobjcontainer.h>
#include <gobjcircle.h>
#include <gobjrect.h>

class Test_GObjContainer : public QObject {
    Q_OBJECT

    const unsigned int TEST_N = 1;
    const GObjContainer::Id ID = TEST_N * TEST_N + TEST_N + 1;
    GObjContainer * gObjContainer;

private slots:

    void initTestCase() {
        gObjContainer = new GObjContainer(0);
        assert(TEST_N > 0);
        for (unsigned int i = 0; i < TEST_N; i++)
            gObjContainer->addChild(GObjContainer(i + 1));
        int offset = 0;
        for (unsigned int i = 0; i < TEST_N; i++) {
            offset += TEST_N;
            for (unsigned int j = 0; j < TEST_N; j++) {
                GObjContainer * gObjSubContainer = dynamic_cast<GObjContainer *>(gObjContainer->findChild(i + 1));
                gObjSubContainer->addChild(GObjCircle(offset + j + 1));
            }
        }
    }

    void addChild_test() {
        gObjContainer->addChild(GObjRect(ID));
        QVERIFY_EXCEPTION_THROWN(gObjContainer->addChild(GObjRect(ID)), GObjContainer::obj_id_exists_exception);
        gObjContainer->removeChild(ID);
    }

    void removeChild_test() {
        gObjContainer->addChild(GObjRect(ID));
        gObjContainer->removeChild(ID);
        QVERIFY_EXCEPTION_THROWN(gObjContainer->removeChild(ID), GObjContainer::no_child_with_id_exception);
    }

    void findChild_test() {
        QVERIFY(gObjContainer->findChild(1)->getId() == 1);
        QVERIFY_EXCEPTION_THROWN(gObjContainer->findChild(TEST_N + 1),GObjContainer::no_child_with_id_exception);
    }

    void findChildR_test() {
        QVERIFY(gObjContainer->findChildR(TEST_N + 1)->getId() == TEST_N + 1);
        QVERIFY_EXCEPTION_THROWN(gObjContainer->findChildR(TEST_N * TEST_N + TEST_N + 1),GObjContainer::no_child_with_id_exception);
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
