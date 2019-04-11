#ifndef TEXTER_H
#define TEXTER_H
#include <iostream>
using namespace std;

class Texter
{
public:
    Texter();

private:
    void checkMessenger(ifstream &fileIn);
};

#endif // TEXTER_H

