#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGUI();
    Generator* generator = new Generator(this);
    Generator g();



}
void MainWindow::initGUI(){
    // GREEK FONT
    QString lambda = QString((QChar) 0x03BB);

    // HTML STYLE
    QString lambdaMinStr = "<b>"+lambda+"</b>" +
                        "<sub>min</sub> [nm]";
    ui->labLambdaMin->setText(lambdaMinStr);

    QString lambdaMaxStr = "<b>"+lambda+"</b>" +
                        "<sub>max</sub> [nm]";
    ui->labLambdaMax->setText(lambdaMaxStr);

    QString tempStr = "<b>T</b> [K]";
    ui->labTemp->setText(tempStr);

    QString periodStr = "Period [ms]";
    ui->labPeriod->setText(periodStr);
    QString noiseStr = "Noise [%]";
    ui->labNoise->setText(noiseStr);

    // INPUT VALIDATORS
    ui->lineInTemp->setValidator(new QIntValidator(1,6000,this));
    ui->lineInLambdaMin->setValidator(new QIntValidator(1,2000,this));
    ui->lineInLambdaMax->setValidator(new QIntValidator(1,2000,this));
    ui->lineInNoise->setValidator(new QIntValidator(0,100,this));
    ui->lineInPeriod->setValidator(new QIntValidator(1,2000,this));

    // INITIAL VALUES
    ui->lineInLambdaMin->setText(QString::number(1));
    ui->lineInLambdaMax->setText(QString::number(2000));
    ui->lineInTemp->setText(QString::number(137));
    ui->lineInPeriod->setText(QString::number(1000));
    ui->lineInNoise->setText(QString::number(7));


}

MainWindow::~MainWindow()
{
    delete ui;
}
