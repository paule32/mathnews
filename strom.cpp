#include "strom.h"
#include "visitorenergie.h"
#include "visitorlamp.h"

QVector<VisitorCommando *> ptr_cmds;

Strom::Strom()
{   
    AddVisitorEnergie * energie = new AddVisitorEnergie(QString("power:1"), 0,0);

    AddVisitorWire * wire1_p = new AddVisitorWire(QString("wire:1:left"));
    AddVisitorWire * wire2_m = new AddVisitorWire(QString("wire:2:right"));

    energie->connectLHS(wire1_p);
    energie->connectRHS(wire2_m);

    AddVisitorLamp * lamp = new AddVisitorLamp(QString("lamp:1"));

    lamp->connectLHS(wire1_p);
    lamp->connectRHS(wire2_m);

    ptr_cmds.append(energie);
    ptr_cmds.append(wire1_p);
    ptr_cmds.append(wire2_m);
    ptr_cmds.append(lamp);


    DownVisitor down;
    for (int i = 0 ; i < ptr_cmds.count(); i++) {
        ptr_cmds.at(i)->accept(down);
    }
}
