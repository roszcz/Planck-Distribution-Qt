#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // SENDING VECTORS THROUGH SIGNALS
    qRegisterMetaType<QVector<double> >("QVector<double >");
    return a.exec();
}
