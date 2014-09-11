#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QTimer>

class Generator : public QObject
{
    Q_OBJECT
    QVector<double> spectrum;
    QVector<double> lambVec;
    QTimer *timer;
    int TEMP;

    void prepareVectors();
public:
    explicit Generator(QObject *parent = 0);

signals:
    void sendQVectors(QVector<double>,QVector<double>);
    void getParams();


public slots:
    void startStop(bool);
//    void sendParams();
    void testing();
    void startTimer(){timer->start();}
    void stopTimer(){timer->stop();}


private:
    enum { RESOLUTION = 321 };

};

#endif // GENERATOR_H
