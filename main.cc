#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#include "mainwindow.h"
#include "strom.h"

#include <QApplication>
#include <QtWebEngineWidgets/QWebEngineSettings>

MainWindow *win = nullptr;
int main(int argc, char *argv[])
{
    // ---------------------------------
    // IMPORTANT: set plugin path's ...
    // ---------------------------------  
    setenv("QT_QPA_PLATFORM_PLUGIN_PATH",
    "/home/jens/Qt5.10/5.10.0/gcc_64/plugins", 1);

    Strom strom;
    return 0;
    
    QApplication a(argc, argv);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled   , true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);

    win = new MainWindow;
    win->show();
    
    return a.exec();
}
