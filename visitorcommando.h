#ifndef VISITORCOMANDO_H
#define VISITORCOMANDO_H
#pragma once

#include <QString>

class VisitorCommando {
public:
    VisitorCommando() { }

    virtual ~VisitorCommando() { }

    virtual void accept(class SimulatorVisitor  &v) { Q_UNUSED(v); }
    virtual void accept(class AddVisitorEnergie &v) { Q_UNUSED(v); }
    virtual void accept(class AddVisitorWire    &v) { Q_UNUSED(v); }
    virtual void accept(class AddVisitorLamp    &v) { Q_UNUSED(v); }
};

#endif // VISITORCOMANDO_H
