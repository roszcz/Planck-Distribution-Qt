#include "generator.h"
#include <QDebug>

Generator::Generator(QObject *parent) :
    QObject(parent),
    spectrum(RESOLUTION),
    lambVec(RESOLUTION),
    timer(new QTimer(this))
{
    QObject::connect(timer,SIGNAL(timeout()),
                     this,SLOT(doStuff()));
    prepareDimensionHacks();
}

void Generator::doStuff(){
    prepareVectors();
    emit sendQVectors(spectrum);
}

void Generator::getParams(int temp, int period, int noise){
    params.temp = temp;
    params.period = period;
    params.noise = noise;
}

void Generator::prepareVectors(){
    for(int i = 0; i < RESOLUTION; ++i){
        spectrum[i] = normConst*pow(lambVec[i],-5)*
                      1.0/(exp(1.0/(lambVec[i]*tempConv(params.temp)))-1) +
                      params.noise*(rand()%100)/10000.0;
    }
}

void Generator::prepareDimensionHacks(){
    for (int i = 0; i < RESOLUTION; ++i){
        // lambda = [0,....,2];
        lambVec[i] = (1.0+i)/RESOLUTION;
    }
    normConst = 15.0/pow(3.1415,4);
}

/* dla jednostkowej wygody temperatura transformuje sie
 * z przedzialo 0 - 1000 od przedzialu 0.4 - 1
 */
inline double Generator::tempConv(int T){
    return 0.4 + 0.6*T/1000;
}

void Generator::changePeriod(){
    timer->setInterval(params.period);
}

void Generator::startStop(bool test){

    if (test){
//        qDebug() << "true" << spectrum[rand()%RESOLUTION];
        changePeriod();
        startTimer();

    }else{
//        qDebug() << "not"<< lambVec[rand()%RESOLUTION];
        stopTimer();
    }
}
