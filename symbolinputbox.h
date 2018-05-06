#ifndef SYMBOLINPUTBOX_H
#define SYMBOLINPUTBOX_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QMouseEvent>

class SymbolInputBox : public QPlainTextEdit
{
public:
    explicit SymbolInputBox(QWidget * parent = 0);
    void init();
    
    QString ht;
    int     htpos;
    
protected:
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
};

#endif // SYMBOLINPUTBOX_H
