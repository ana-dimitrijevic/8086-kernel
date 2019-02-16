#include "userapp.h"
#include <iostream.h>

extern int userMain(int, char*[]);


UserApp::UserApp(int argCounter, char *argVector[],
                                 StackSize stackSize, Time timeSlice):
    Thread(stackSize, timeSlice), argc(argCounter), argv(argVector),
    retVal(0)
{

}


UserApp::~UserApp() {
    waitToComplete();
}

int UserApp::getRetVal() {
    return retVal;
}

void UserApp::run() {
   retVal = userMain(argc, argv);
      }



