#ifndef VISITORENERGIE_H
#define VISITORENERGIE_H
#pragma once

#include <QString>
#include <QtDebug>

#include "visitorcommando.h"
#include "visitorenergie.h"
#include "visitorwire.h"

class Connection: public VisitorCommando {
public:
    Connection()
        : m_plus(0)
        , m_minus(0)
    { }

    Connection(int p, int m)
        : m_plus(p)
        , m_minus(m)
    { }

    virtual ~Connection() { }

    // getter ...
    QString getName() const { return m_name; }

    int getPlus () const { return m_plus ; }
    int getMinus() const { return m_minus; }

    // setter ...
    void setName(QString value) { m_name = value; }

    void setPlus (int value) { m_plus  = value; }
    void setMinus(int value) { m_minus = value; }

private:
    QString m_name;

    int m_plus;
    int m_minus;
};

class AddVisitorEnergie: public Connection
{
public:
    // default ctor ...
    AddVisitorEnergie(QString name, int p, int m) {
        setOutputLHS(p);
        setOutputLRS(m);

        setName(name);
    }

    AddVisitorEnergie(
        QString name,
        AddVisitorWire * out_lhs,
        AddVisitorWire * out_rhs)
    {
        Q_UNUSED(out_lhs);
        Q_UNUSED(out_rhs);

        setName(name);
        setPlus (0);
        setMinus(0);

        qDebug() << QString("Energie ctor: %1, %2 %3")
        .arg(getName())
        .arg(getPlus()).arg(getMinus());
    }

    virtual ~AddVisitorEnergie()  { }
    virtual void accept(class SimulatorVisitor &v) { v.visit(this); }

    QString getWireNameLHS() const { return w_lhs_connect->getName(); }
    QString getWireNameRHS() const { return w_rhs_connect->getName(); }

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

    // setter
    void setOutputLHS(int value) { m_lhs_output = value; }
    void setOutputLRS(int value) { m_rhs_output = value; }

    void connectLHS(class AddVisitorWire *w) { w_lhs_connect = w; }
    void connectRHS(class AddVisitorWire *w) { w_rhs_connect = w; }

private:
    QString m_name;

    int m_lhs_output;
    int m_rhs_output;

    class AddVisitorWire * w_lhs_connect = nullptr;
    class AddVisitorWire * w_rhs_connect = nullptr;
};

#endif // VISITORENERGIE_H
