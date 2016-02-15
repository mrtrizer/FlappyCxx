#ifndef TEST_TOOLS_H
#define TEST_TOOLS_H

#include <QObject>
#include <QTest>

#include "tools.h"
#include "gobjcircle.h"

class Test_Tools : public QObject
{
    Q_OBJECT

private slots:
    void test_calcDist() {
        QVERIFY(Tools::calcDist2D(GObjCircle(1,{0,0,0}), GObjCircle(1,{10,0,0})) == 10);
        QVERIFY(Tools::calcDist2D(GObjCircle(1,{0,0,0}), GObjCircle(1,{0,10,0})) == 10);
        QVERIFY(Tools::calcDist2D(GObjCircle(1,{0,0,0}), GObjCircle(1,{10,10,0})) == std::sqrt(10 * 10 + 10 * 10));
    }
};

#endif // TEST_TOOLS_H
