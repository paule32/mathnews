#ifndef DOWNVISITOR_H
#define DOWNVISITOR_H
#pragma once

#include "downvisitor.h"
#include "simulatorvisitor.h"
#include "visitorwire.h"
#include "visitorlamp.h"

class DownVisitor: public SimulatorVisitor {
public:
    DownVisitor() {
        qDebug() << "DownVisitor";
    }
    virtual void visit(class AddVisitorEnergie *e) {
        Q_UNUSED(e);
        //qDebug() << "add Energie Down on: ";

        if (e->getWireLHS()) qDebug() <<
            QString("add wire: %1  -- %2")
            .arg(e->getWireNameLHS())
            .arg(e->getName());

        if (e->getWireRHS()) qDebug() <<
            QString("add wire: %1 -- %2")
            .arg(e->getWireNameRHS())
            .arg(e->getName());
    }
    virtual void visit(class AddVisitorWire *e) {
        Q_UNUSED(e);

        //qDebug() << "draht null";
    }
    virtual void visit(class AddVisitorLamp *e) {
        Q_UNUSED(e);

        if (e->getWireLHS()) qDebug() <<
            QString("add wire: %1  -- %2")
            .arg(e->getWireNameLHS())
            .arg(e->getName());

        if (e->getWireRHS()) qDebug() <<
            QString("add wire: %1 -- %2")
            .arg(e->getWireNameRHS())
            .arg(e->getName());
    }
};

#endif // DOWNVISITOR_H
