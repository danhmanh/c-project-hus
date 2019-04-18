#include "ControlCenter.h"



ControlCenter::ControlCenter()
{
}


ControlCenter::~ControlCenter()
{
}

void ControlCenter::addMessage(std::string message) {
    messages.push(message);
}

std::string ControlCenter::getMessage() {
    std::string mess;
    mess = messages.front();
    messages.pop();
    return mess;
}
