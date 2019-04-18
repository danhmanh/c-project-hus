#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#pragma once
#include<queue>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
using namespace std;
class ControlCenter
{
public:
    ControlCenter();
    ~ControlCenter();

    void addMessage(std::string message);
    std::string getMessage();

private:
    std::queue<std::string> messages;
};

static ControlCenter controlptr;

#endif // CONTROLCENTER_H
