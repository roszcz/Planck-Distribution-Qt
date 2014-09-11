#include "generator.h"
#include <QDebug>

Generator::Generator(QObject *parent) :
    QObject(parent),
    spectrum(RESOLUTION),
    lambVec(RESOLUTION),
    lambPovFive(RESOLUTION),
    timer(new QTimer(this))
{
    QObject::connect(timer,SIGNAL(timeout()),
                     this,SLOT(doStuff()));
    prepareDimensionHacks();
    timer->setInterval(100);

}
void Generator::prepareDimensionHacks(){
    for (int i = 0; i < RESOLUTION; ++i){
        // lambda = [0,....,2];
        lambVec[i] = i/(RESOLUTION-1.);
        lambPovFive[i] = pow(lambVec[i],-5);
    }
    normConst = pow(3.14,-4)*15.0;
}

void Generator::doStuff(){
    prepareVectors();
    emit sendQVectors(spectrum);

}
// SLOT
void Generator::getParams(int temp, int period, int noise){
    params.temp = temp;
    params.period = period;
    params.noise = noise;
}

void Generator::prepareVectors(){
    for(int i = 0; i < RESOLUTION; ++i){
//        lambVec[i] = i + 1;
//        spectrum[i] = pow( (i-1024.0+params.temp)/1024.0, 2 ) +
//                      params.noise*(rand()%100)/10000.;
        spectrum[i] = lambVec[i]*2.0 +
                      params.noise*(rand()%100)/10000.0;
    }
}
void Generator::startStop(bool test){

    if (test){
        qDebug() << "true" << spectrum[rand()%RESOLUTION];
        startTimer();

    }else{
        qDebug() << "not"<< lambVec[rand()%RESOLUTION];;
        stopTimer();
    }
}
