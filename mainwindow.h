#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include "generator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QVector<double> spectrumGUI;
    QVector<double> lambVecGUI;
    Generator *generator;
    QThread *thread;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void getQVectors(QVector<double>,QVector<double>);

private:
    Ui::MainWindow *ui;

    void initGUI();
    void initPLOT();
    void initGenerator();
    void refreshPlot();

    enum { RESOLUTION = 321 };



};

#endif // MAINWINDOW_H
