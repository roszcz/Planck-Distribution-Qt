#include "generator.h"
#include <QDebug>

Generator::Generator(QObject *parent) :
    QObject(parent),
    spectrum(RESOLUTION),
    lambVec(RESOLUTION),
    timer(new QTimer(this)),
    TEMP(137)
{
    QObject::connect(timer,SIGNAL(timeout()),
                     this,SLOT(testing()));
    timer->setInterval(10);

}
void Generator::testing(){
    prepareVectors();
    qDebug() << spectrum[rand()%RESOLUTION];
    emit sendQVectors(lambVec,spectrum);
    qDebug() << "vectors sent";

}
void Generator::prepareVectors(){

    for(int i = 0; i < RESOLUTION; ++i){
        lambVec[i] = i + 1;
        spectrum[i] = pow( (i-160.0)/160.0, 2 ) + (rand()%100)/600.;
    }

    qDebug() << spectrum[123] << "sda";

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
