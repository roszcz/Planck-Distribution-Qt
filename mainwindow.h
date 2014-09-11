#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include "generator.h"

namespace Ui {
class MainWindow;
}
struct guiParams{
    int lambdaMin;
    int lambdaMax;
    int temp;
    int period;
    int noise;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QVector<double> spectrumGUI;
    QVector<double> lambVecGUI;
    Generator *generator;
    QThread *thread;
    guiParams params;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void sendParams(int,int,int);

public slots:
    void getQVectors(QVector<double>);
    void renameButton(bool);
    void readParams();
    void testSLOT(){qDebug() << "HALO";}

private:
    Ui::MainWindow *ui;

    void initGUI();
    void initPLOT();
    void initGenerator();
    void refreshPlot();


    enum { RESOLUTION = 2048 };



};

#endif // MAINWINDOW_H
