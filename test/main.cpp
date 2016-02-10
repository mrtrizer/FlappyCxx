#include <QTest>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "test_gobjcontainer.h"

int main(int argc, char** argv)
{
   int status = 0;

   const auto RUN_TEST = [&status, argc, argv] (QObject * obj) {
     status |= QTest::qExec(obj, argc, argv);
     delete obj;
   };

   RUN_TEST(new Test_GObjContainer());

   return status;
}
