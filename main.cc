#include "mainwindow.h"
#include <QApplication>

MainWindow *win = nullptr;
int main(int argc, char *argv[])
{
    // ---------------------------------
    // IMPORTANT: set plugin path's ...
    // ---------------------------------  
    setenv("QT_QPA_PLATFORM_PLUGIN_PATH",
    "/home/jens/Qt5.10/5.10.0/gcc_64/plugins", 1);
    
    QApplication a(argc, argv);
    win = new MainWindow;
    win->show();
    
    return a.exec();
}
