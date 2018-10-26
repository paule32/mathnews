#ifndef VISITORLAMP_H
#define VISITORLAMP_H
#pragma once

class AddVisitorLamp
{
public:
    AddVisitorLamp(QString name) {
        Q_UNUSED(name);
        setName(name);
    }

    virtual ~AddVisitorLamp() { }
    virtual void accept(class SimulatorVisitor &v) { v.visit(this); }

    void connectLHS(class AddVisitorWire *w) { w_lhs_connect = w; }
    void connectRHS(class AddVisitorWire *w) { w_rhs_connect = w; }

    int getWireLHS() const {
        if (w_lhs_connect != nullptr)
        return 1;
        return 0;
    }
    int getWireRHS() const {
        if (w_rhs_connect != nullptr)
        return 1;
        return 0;
    }

    QString getWireNameLHS() const { return w_lhs_connect->getName(); }
    QString getWireNameRHS() const { return w_rhs_connect->getName(); }

private:
    class AddVisitorWire * w_lhs_connect;
    class AddVisitorWire * w_rhs_connect;
};

#endif // VISITORLAMP_H
