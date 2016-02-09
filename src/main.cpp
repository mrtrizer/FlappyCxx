#include "gctrl.h"

int main(int argc, char * argv) {
    GCtrl::getInst()->start([](){});
    return 0;
}
