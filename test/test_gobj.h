#ifndef TEST_GOBJCIRCLE_H
#define TEST_GOBJCIRCLE_H

#include <QObject>
#include <QTest>

#include <gobjcircle.h>

class Test_GObj : public QObject
{
    Q_OBJECT

    GObjCircle * gObjCircle = nullptr;

private slots:
    void initTestCase() {
        gObjCircle = new GObjCircle(0, 10);
    }

    void test_isIntersectWith() {
        GObjCircle gObjCircle1(1, 10, {10,0,0});
        GObjCircle gObjCircle2(2, 10, {20,0,0});
        QVERIFY(gObjCircle->isIntersectWith(gObjCircle1) == true);
        QVERIFY(gObjCircle->isIntersectWith(gObjCircle2) == false);

    }

    void cleanupTestCase() {
        delete gObjCircle;
    }
};

#endif // TEST_GOBJCIRCLE_H
