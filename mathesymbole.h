#ifndef MATHESYMBOLE_H
#define MATHESYMBOLE_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStyledItemDelegate>
#include <QMouseEvent>

#include <QDebug>

// 0 - nothing
// 1 - Zahlen
// 2 - g.Alphabet
extern int ACTIVE_SYMBOL_PAGE;

struct matsymbole {
    int id;
    QString html;
    QString name;
};

struct zahlen {
    int id;
    QString html;
    QString name;
};

struct operatoren {
    int id;
    QString html;
    QString name;
};

struct alpha {
    int id;
    QString html;
    QString name;
    bool grade;
};

extern struct alpha      greek_alpha[];
extern struct zahlen     struct_zahlen[];
extern struct operatoren struct_operatoren[];
extern struct matsymbole struct_mathsymbole[];

class SymbolItemDelegate : public QStyledItemDelegate {
public:
    explicit SymbolItemDelegate(QObject *parent = 0);
    QString anchorAt(QString html, const QPoint &point) const;

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &_index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class Model : public QAbstractTableModel {
public:
    Model() {}
    int rowCount(const QModelIndex &parent = QModelIndex()) const {
        if(parent.isValid()) return 0;
        return 1;
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const {
        Q_UNUSED(parent);
        return 1;
    }
 
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
        Q_UNUSED(index);
        if(role != Qt::DisplayRole) return QVariant();
        qDebug() << Q_FUNC_INFO;
        return "A";
    }
};

class MatheSymbole : public QTableWidget
{
public:
    explicit MatheSymbole(QWidget * parent = nullptr);
    virtual ~MatheSymbole();
    
    void init(void);
    void init_zahlen(void);
    void init_operatoren(void);
    
    void oncellPress(int row, int col);
    void onTimerTimeOut();
    
    int cell_row;
    int cell_col;
    
    QTableWidgetItem * setNewItem(int m, int p, int flag);
protected:
    virtual void dropEvent(QDropEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
//  virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
};

extern MatheSymbole * mathsym;
extern int selected_symbol;

#endif // MATHESYMBOLE_H
