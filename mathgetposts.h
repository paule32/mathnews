#ifndef MATHGETPOSTS_H
#define MATHGETPOSTS_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QKeyEvent>
#include <QByteArray>
#include <QNetworkAccessManager>

class MathGetPosts : public QTreeWidget
{
public:
    MathGetPosts(QWidget * parent = nullptr);
    virtual ~MathGetPosts() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MATHGETPOSTS_H
