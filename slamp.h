#ifndef SLAMP_H
#define SLAMP_H
#pragma once

#include "strom.h"

using namespace std;
class SLamp
{
    // default ctor ...
    SLamp(class SEnergie &src)
    {
        if (src.getPlus() && src.getMinus()) {
            setOn(true);
            std::cout << "lamp on\n" << std::endl;
        }
        else {
            std::cout << "lamp off" << std::endl;
        }
    }

    SLamp() : isOn(false) { }

    bool getOn()     const { return isOn ; }
    void setOn(bool value) { isOn = value; }

    bool isOn;
};

#endif // SLAMP_H
