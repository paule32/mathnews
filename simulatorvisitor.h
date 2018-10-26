#ifndef SIMULATORVISITOR_H
#define SIMULATORVISITOR_H
#pragma once

#include "strom.h"

class SimulatorVisitor {
public:
    SimulatorVisitor() {
        qDebug() << "SimulatorVisitor";
    }
    virtual ~SimulatorVisitor() { }

    virtual void visit(class AddVisitorEnergie *e) { Q_UNUSED(e); }
    virtual void visit(class AddVisitorWire    *e) { Q_UNUSED(e); }
    virtual void visit(class AddVisitorLamp    *e) { Q_UNUSED(e); }
};

#endif // SIMULATORVISITOR_H
