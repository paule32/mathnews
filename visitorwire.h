#ifndef VISITORWIRE_H
#define VISITORWIRE_H
#pragma once

#include "visitorcommando.h"
#include "visitorenergie.h"

class AddVisitorWire: public VisitorCommando
{
public:
    // default ctor ...
    AddVisitorWire(QString name)
    {
        Q_UNUSED(name);
        setName(name);
    }

    virtual ~AddVisitorWire() { }
    virtual void accept(class SimulatorVisitor &v) { v.visit(this); }

    void connectLHS(class AddVisitorWire *w) { m_lhs_connect = w; }
    void connectRHS(class AddVisitorWire *w) { m_rhs_connect = w; }

    void connectLHS(class AddVisitorLamp *w) { l_lhs_connect = w; }
    void connectRHS(class AddVisitorLamp *w) { l_rhs_connect = w; }

    // getter ...
    QString getName() const { return m_name; }

    // setter ...
    void setName(QString name) { m_name = name; }

private:
    class AddVisitorWire * m_lhs_connect = nullptr;
    class AddVisitorWire * m_rhs_connect = nullptr;

    class AddVisitorLamp * l_lhs_connect = nullptr;
    class AddVisitorLamp * l_rhs_connect = nullptr;

    QString m_name;
};

#endif // VISITORWIRE_H
