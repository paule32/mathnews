#ifndef STROM_H
#define STROM_H
#pragma once

#include <iostream>
#include <algorithm>
#include <functional>

#include <QVariant>
#include <QString>
#include <QVector>

#include <QDebug>

#include "simulatorvisitor.h"
#include "visitorcommando.h"

#include "visitorenergie.h"
#include "visitorwire.h"
#include "visitorlamp.h"

#include "downvisitor.h"

class Strom
{
public:
    Strom();
};

#endif // STROM_H
