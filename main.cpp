#include <iostream.h>
#include "system.h"
#include "userapp.h"

int main(int argc, char* argv[]) {

    System::initialize();

    UserApp *userApp = new UserApp(argc, argv);
    userApp->start();

    userApp->waitToComplete();

    int ret = userApp->getRetVal();

    SOFT_LOCK
    delete userApp;
    SOFT_UNLOCK

    System::restore();

    return ret;
}
