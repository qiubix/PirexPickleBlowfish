#include <iostream>
#include "Dollar.hpp"

int main()
{
    std::cout << "Hello World!" << std::endl;
    //Karol właśnie dodał nową linię i się z tego bardzo cieszy.
    //Artur też chce!
    //nowy system test
    return 0;
}

int firstFunction(int argument)
{
    if (argument > 0) {
        argument = 0;
    }
    else {
        argument = 1;
    }
    return argument;
}
