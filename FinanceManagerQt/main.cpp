#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


extern "C" int qMain(int argc, char **argv)
{
    return main(argc, argv);
}
