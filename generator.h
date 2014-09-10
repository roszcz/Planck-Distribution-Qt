#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>

class Generator : public QObject
{
    Q_OBJECT
    static const int N = 5;
    QVector<double> spectrum;

    void test(QVector<double>&);
public:
    explicit Generator(QObject *parent = 0);

signals:

public slots:

};

#endif // GENERATOR_H
