#include "generator.h"
#include <QDebug>

Generator::Generator(QObject *parent) :
    QObject(parent)
{
    QVector<double> spectrum(QVector<double>(10));

    test(spectrum);

}
void Generator::test(QVector<double>& myVec){

    for(auto& i : myVec){
        i = rand()%100;
        qDebug() << i << "SAD";
    }
    qDebug() << "test";
}
