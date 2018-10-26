#ifndef MATHWEBPAGE_H
#define MATHWEBPAGE_H

#include <QObject>
#include <QWidget>

#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>

class MathWebPage : public QWebEnginePage
{
public:
    MathWebPage(QWebEngineProfile *profile, QObject *parent = nullptr);
    virtual ~MathWebPage() override;

    void getPosts();
protected:
    bool certificateError(const QWebEngineCertificateError &error) override;
};

#endif // MATHWEBPAGE_H
