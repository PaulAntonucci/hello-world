#include "mainwindow.h"
#include <QApplication>


//#include "read_write_globals.h"
// Now making a change from github.com Aug 25 2015
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
