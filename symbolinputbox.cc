#include <QPlainTextEdit>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QDrag>
#include <QLabel>
#include <QTextBlock>
#include <QTextCursor>
#include <QMessageBox>

#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mathesymbole.h"
#include "symbolinputbox.h"

extern int ACTIVE_SYMBOL_PAGE;

SymbolInputBox::SymbolInputBox(QWidget * parent)
    : QPlainTextEdit(parent)
{
    QFont font;
    font.setPixelSize(20);
    
    setWordWrapMode(QTextOption::WordWrap);
    setFont(font);
    
    selected_symbol = 1;
}

void SymbolInputBox::init()
{
    setMouseTracking(true);
    htpos = 0;
}

void SymbolInputBox::mouseReleaseEvent(QMouseEvent *e)
{
    e->accept();
}

void SymbolInputBox::mousePressEvent(QMouseEvent *e)
{
    QPlainTextEdit::mousePressEvent(e);
    e->accept();

    QString str;
    int cs=selected_symbol - 1;
    
    if (cs < 0) {
        QMessageBox::information(win,
        "Warnung !!!",
        "Berechnungsfeld ist leer oder falscher Index.");
        return;
    }
    
    switch (ACTIVE_SYMBOL_PAGE)
    {
    case 1: str = QString("%1")  .arg(struct_zahlen     [cs].html); break;
    case 2: str = QString("&%1;").arg(greek_alpha       [cs].html); break;
    case 3: str = QString("%1")  .arg(struct_operatoren [cs].html); break;
    case 4: str = QString("%1")  .arg(struct_mathsymbole[cs].html); break;
    };
    
    ht = document()->toPlainText();
    ht.insert(textCursor().anchor(),
    
    QString("<font size='10'>%1</font>").arg(str));

    win->ui->inputBox->clear();
    document()->setHtml(ht);
}

void SymbolInputBox::mouseMoveEvent(QMouseEvent *e)
{
    e->accept();
}

