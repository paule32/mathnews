#include "mathgetposts.h"

#include <QMessageBox>
#include <QKeyEvent>
#include <QTreeWidget>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "mainwindow.h"

MathGetPosts::MathGetPosts(QWidget *parent)
    : QTreeWidget (parent)
{
}

MathGetPosts::~MathGetPosts() { }

void MathGetPosts::keyPressEvent(QKeyEvent *event)
{
    event->accept();
    if (event->key() == Qt::Key_F5) {
        win->web_page->getPosts();
    }

    QTreeWidget::keyPressEvent(event);
}

