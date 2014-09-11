#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <math.h>


struct deviceParams {
    int temp;
    int period;
    int noise;
};

class Generator : public QObject
{
    Q_OBJECT
    QVector<double> spectrum;
    QVector<double> lambVec;
    QTimer *timer;
    deviceParams params;
    double normConst;

    void prepareDimensionHacks();
    void prepareVectors();
    inline double tempConv(int);
public:
    explicit Generator(QObject *parent = 0);
public slots:
    void changePeriod();

signals:
    void sendQVectors(QVector<double>);
    void requestParams();



public slots:
    void startStop(bool);
    void getParams(int,int,int);
    void doStuff();
    void startTimer(){timer->start();}
    void stopTimer(){timer->stop();}


private:
    enum { RESOLUTION = 2048 };

};

#endif // GENERATOR_H
