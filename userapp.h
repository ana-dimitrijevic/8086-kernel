#ifndef USERAPP_H_
#define USERAPP_H_

#include "thread.h"

class UserApp: public Thread {
public:
    UserApp(int argCounter, char *argVector[],
                    StackSize stackSize = defaultStackSize,
                    Time timeSlice = defaultTimeSlice);


    ~UserApp();
    int getRetVal();

protected:
    void run();
private:
    int argc;
    char **argv;
    int retVal;
};

#endif
