#include <QWidget>

#include "mainwindow.h"
#include "mathwebpage.h"

#include "ui_mainwindow.h"

#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebEngineWidgets/QWebEngineView>

#include <QTemporaryFile>
#include <QMessageBox>

#include <QDebug>

MathWebPage::MathWebPage(QWebEngineProfile *profile, QObject *parent)
    : QWebEnginePage(profile, parent)
{

}

MathWebPage::~MathWebPage() { }

bool MathWebPage::certificateError(const QWebEngineCertificateError &error)
{
    Q_UNUSED(error);

    qDebug() << "testing";
    return true;
}

void MathWebPage::getPosts()
{
    load(QUrl("https://mathnews.kallup.freecluster.eu/getpost.php?text=www.web.de"));
    win->web_view->setPage(this);
}

