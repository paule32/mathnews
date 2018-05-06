#include <QWidget>
#include <QApplication>
#include <QTranslator>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPainter>
#include <QTextDocument>
#include <QStyledItemDelegate>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QAbstractTextDocumentLayout>
#include <QStyleOptionViewItem>
#include <QBitmap>
#include <QLabel>
#include <QTimer>

#include "mathesymbole.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

struct matsymbole struct_mathsymbole[] = {
    1, "&Pi;", "Kreiszahl",
};

struct operatoren struct_operatoren[] = {
    1, "+", "Plus",
    2, "-", "Minus",
    3, "*", "Multiplikation",
    4, "/", "Division",
    5, "mod", "Modulo",
    6, "^2", "Hoch-2 o. Quadrat",
    7, "neg", "Negation",
};

struct zahlen struct_zahlen[] = {
    1 , "0", "Null",
    2 , "1", "Eins",
    3 , "2", "Zwei",
    4 , "3", "Drei",
    5 , "4", "Vier",
    6 , "5", "Fünf",
    7 , "6", "Sechs",
    8 , "7", "Sieben",
    9 , "8", "Acht",
    10, "9", "Neun",
};

struct alpha greek_alpha[] = {
    1, "Alpha", "Alpha", true,
    2, "alpha", "Alpha", false,
    3, "Beta" , "Beta", true,
    4, "beta" , "beta", false,
    5, "Gamma", "Gamma", true,
    6, "gamma", "gamma", false,
    7, "Delta", "Delta", true,
    8, "delta", "delta", false,
    9, "Epsilon", "Epsilon", true,
    10, "epsilon", "epsilon", false,
    11, "Zeta", "Zeta", true,
    12, "zeta", "zeta", false,
    13, "Eta", "Eta", true,
    14, "eta", "eta", false,
    15, "Theta", "Theata", true,
    16, "theta", "theata", false,
    17, "Iota", "Iota", true,
    18, "iota", "iota", false,
    19, "Kappa", "Kappa", true,
    20, "kappa", "kappa", false,
    21, "Lambda", "Lambda", true,
    22, "lambda", "lambda", false,
    23, "Mu", "Mu", true,
    24, "mu", "mu", false,
    25, "Nu", "Nu", true,
    26, "nu", "nu", false,
    27, "Xi", "Xi", true,
    28, "xi", "xi", false,
    29, "Omicron", "Omicron", true,
    30, "omicron", "omicron", false,
    31, "Pi", "Pi", true,
    32, "pi", "pi", false,
    33, "piv", "pi symbol", false,
    34, "Rho", "Rho", true,
    35, "rho", "rho", false,
    36, "Sigma", "Sigma", true,
    37, "sigma", "sigma", false,
    38, "sigmaf", "final sigma", true,
    39, "Tau", "Tau", true,
    40, "tau", "tau", false,
    41, "Upsilon", "Upsilon", true,
    42, "upsilon", "upsilon", false,
    43, "upsih", "upsilon hook", false,
    44, "Phi", "Phi", true,
    45, "phi", "phi", false,
    46, "Chi", "Chi", true,
    47, "chi", "chi", false,
    48, "Psi", "Psi", true,
    49, "psi", "psi", false,
    50, "Omega", "Omega", true,
    51, "omega", "omega", false,
    52, "thetasym", "theta", false,
};

MatheSymbole * mathsym = nullptr;
int selected_symbol = 0;
int ACTIVE_SYMBOL_PAGE = 0;

SymbolItemDelegate::SymbolItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{}

static bool mouseDown=false;

QString SymbolItemDelegate::anchorAt(QString html, const QPoint &point) const {
    QTextDocument doc;
    doc.setHtml(html);

    auto textLayout = doc.documentLayout();
    Q_ASSERT(textLayout != 0);
    return textLayout->anchorAt(point);
}

void SymbolItemDelegate::paint(
    QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &_index) const
{
    auto options = option;
    initStyleOption(&options, _index);

    painter->save();

    QTextDocument doc;
    doc.setHtml(options.text);
    
    options.text = "";
    options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &option, painter);

    painter->translate(options.rect.left(), options.rect.top());
    QRect clip(0, 0, options.rect.width(), options.rect.height());
    
    doc.drawContents(painter, clip);

    painter->restore();
}

QSize SymbolItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItemV4 options = option;
    initStyleOption(&options, index);

    QTextDocument doc;
    doc.setHtml(options.text);
    doc.setTextWidth(options.rect.width());
    return QSize(doc.idealWidth(), doc.size().height());
}

MatheSymbole::MatheSymbole(QWidget * parent)
    : QTableWidget(parent)
{
    mathsym = this;
}

void MatheSymbole::init()
{
    auto symbolItemDelegate = new SymbolItemDelegate(this);
    setItemDelegate(symbolItemDelegate);
    
    clearContents();
    ACTIVE_SYMBOL_PAGE = 2;
    
    setRowCount(52);
    setColumnCount(2);
    
    setColumnWidth(0,42);
    setColumnWidth(1,140);
    
    setSpan(0,0,1,2);
    QTableWidgetItem *m_item = new
    QTableWidgetItem;
    m_item->setFlags(Qt::NoItemFlags);
    m_item->setText("<body style='background-color:yellow;'>"
    "<div style='background-color:yellow;"
    "margin-left:-5px;margin-top:-5px;margin-right:0px;margin-bottom:0px;'"
    "><center><b>griechische Buchstaben</b></center></div></body>");
    setItem(0,0, m_item);
    
    
    QString ident = "&nbsp;&nbsp;";
    QString texts ;
    
    for (int i = 0; i < 52; ++i) {
        m_item = new QTableWidgetItem;
        m_item->setFlags(
            Qt::ItemIsEnabled |
            Qt::ItemIsDragEnabled |
            Qt::ItemIsDropEnabled);
        m_item->setText(QString(
        "<body style='background-color:lime;'>"
        "<div style='"
        "font-size:12pt;"
        "position:relative;"
        "top: 50%;"
        "transform:translateY(-50%);'>"
        "<b>%1%2%3%4</b></div></body>").
        arg(ident).
        arg("&").
        arg(greek_alpha[i].html).
        arg(";"));
        
        setItem(1+i,0, m_item);
        
        if (greek_alpha[i].grade == true)
        texts = " groß"; else
        texts = " klein";
        
        m_item = new QTableWidgetItem;
        m_item->setFlags(Qt::ItemIsEnabled);
        m_item->setText(QString(
        "<body style='background-color:cyan;'>"
        "%1%2"
        "</body>").
        arg(greek_alpha[i].name).
        arg(texts));
        
        setItem(1+i,1, m_item);
    }
    
    
    connect(this,
            &QTableWidget::cellPressed,
            this,
            &MatheSymbole::oncellPress);
}

void MatheSymbole::init_zahlen()
{
    auto symbolItemDelegate = new SymbolItemDelegate(this);
    setItemDelegate(symbolItemDelegate);

    clearContents();
    ACTIVE_SYMBOL_PAGE = 1;
    
    setRowCount(11);
    setColumnCount(2);
    
    setColumnWidth(0,42);
    setColumnWidth(1,140);
    
    setSpan(0,0,1,2);
    QTableWidgetItem *m_item = new
    QTableWidgetItem;
    m_item->setFlags(Qt::NoItemFlags);
    m_item->setText("<body style='background-color:yellow;'>"
    "<div style='background-color:yellow;"
    "margin-left:-5px;margin-top:-5px;margin-right:0px;margin-bottom:0px;'"
    "><center><b>Zahlen</b></center></div></body>");
    setItem(0,0, m_item);

    QString ident = "&nbsp;&nbsp;";
    
    for (int i = 0; i < 10; ++i) {
        m_item = new QTableWidgetItem;
        m_item->setFlags(
            Qt::ItemIsEnabled |
            Qt::ItemIsDragEnabled |
            Qt::ItemIsDropEnabled);
        m_item->setText(QString(
        "<body style='background-color:lime;'>"
        "<div style='"
        "font-size:12pt;"
        "position:relative;"
        "top: 50%;"
        "transform:translateY(-50%);'>"
        "<b>%1%2</b></div></body>").
        arg(ident).
        arg(struct_zahlen[i].html));
        
        setItem(1+i,0, m_item);
        
        m_item = new QTableWidgetItem;
        m_item->setFlags(Qt::ItemIsEnabled);
        m_item->setText(QString(
        "<body style='background-color:cyan;'>"
        "%1</body>").
        arg(struct_zahlen[i].name));
        
        setItem(1+i,1, m_item);
    }
}

void MatheSymbole::mouseReleaseEvent(QMouseEvent *event)
{
    if (win->ui->inputBox->underMouse())
    qDebug() << "relller: ";
}

void MatheSymbole::init_operatoren(void)
{
    auto symbolItemDelegate = new SymbolItemDelegate(this);
    setItemDelegate(symbolItemDelegate);

    clearContents();
    ACTIVE_SYMBOL_PAGE = 3;
    
    setRowCount(8);
    setColumnCount(2);
    
    setColumnWidth(0,42);
    setColumnWidth(1,140);
    
    setSpan(0,0,1,2);
    QTableWidgetItem *m_item = new
    QTableWidgetItem;
    m_item->setFlags(Qt::NoItemFlags);
    m_item->setText("<body style='background-color:yellow;'>"
    "<div style='background-color:yellow;"
    "margin-left:-5px;margin-top:-5px;margin-right:0px;margin-bottom:0px;'"
    "><center><b>Mathe Operatoren</b></center></div></body>");
    setItem(0,0, m_item);

    QString ident = "&nbsp;&nbsp;";
    
    for (int i = 0; i < 7; ++i) {
        m_item = new QTableWidgetItem;
        m_item->setFlags(
            Qt::ItemIsEnabled |
            Qt::ItemIsDragEnabled |
            Qt::ItemIsDropEnabled);
        m_item->setText(QString(
        "<body style='background-color:lime;'>"
        "<div style='"
        "font-size:12pt;"
        "position:relative;"
        "top: 50%;"
        "transform:translateY(-50%);'>"
        "<b>%1%2</b></div></body>").
        arg(ident).
        arg(struct_operatoren[i].html));
        
        setItem(1+i,0, m_item);
        
        m_item = new QTableWidgetItem;
        m_item->setFlags(Qt::ItemIsEnabled);
        m_item->setText(QString(
        "<body style='background-color:cyan;'>"
        "%1</body>").
        arg(struct_operatoren[i].name));
        
        setItem(1+i,1, m_item);
    }
}

void MatheSymbole::oncellPress(int row, int col)
{
    qDebug() << "row: " << row;
    qDebug() << "col: " << col;

    cell_col = col;
    cell_row = row;
    
    if (cell_row - 1 >= 0)
    {   cell_row = cell_row - 1;
        QString kg;
        
        if (ACTIVE_SYMBOL_PAGE == 1) {
            kg = struct_zahlen[cell_row].name;
            selected_symbol = struct_zahlen[cell_row].id;
        }
        else if (ACTIVE_SYMBOL_PAGE == 2) {
            if (greek_alpha[cell_row].grade == true)
            kg= greek_alpha[cell_row].name + " groß" ; else
            kg= greek_alpha[cell_row].name + " klein";
            selected_symbol = greek_alpha[cell_row].id;
        }
        else if (ACTIVE_SYMBOL_PAGE == 3) {
            kg = struct_operatoren[cell_row].html;
            selected_symbol = struct_operatoren[cell_row].id;
        }
            
        win->ui->symbolText->setText(kg);
    }
}

void MatheSymbole::onTimerTimeOut()
{

}

void MatheSymbole::dropEvent(QDropEvent *event)         { event->accept(); }
void MatheSymbole::dragMoveEvent(QDragMoveEvent *event) { event->accept(); }
