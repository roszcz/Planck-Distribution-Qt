#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    lambVecGUI(RESOLUTION),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGenerator();
    initGUI();
    initPLOT();
}

void MainWindow::initGenerator(){

    // FILL THE THREAD
    QThread *thread = new QThread;
    Generator *generator = new Generator();
    generator->moveToThread(thread);

    // CONNECT WITH THREAD
    // START BUTTON
    QObject::connect(ui->buttonStartStop,SIGNAL(clicked(bool)),
                     generator,SLOT(startStop(bool)));
    QObject::connect(ui->buttonStartStop,SIGNAL(clicked(bool)),
                     this,SLOT(renameButton(bool)));

    // VECTORS TRANSMISSION
    QObject::connect(generator,SIGNAL(sendQVectors(QVector<double>)),
                     this,SLOT(getQVectors(QVector<double>)));

    // PARAMS TRANSMISSION
    QObject::connect(this,SIGNAL(sendParams(int,int,int)),
                     generator,SLOT(getParams(int,int,int)));

    // START THREAD
    thread->start();

    // EDITING PARAMETERS @GUI
    QObject::connect(ui->lineInLambdaMax,SIGNAL(editingFinished()),
                     this,SLOT(readParams()));
    QObject::connect(ui->lineInLambdaMin,SIGNAL(editingFinished()),
                     this,SLOT(readParams()));
    QObject::connect(ui->lineInNoise,SIGNAL(editingFinished()),
                     this,SLOT(readParams()));
    QObject::connect(ui->lineInPeriod,SIGNAL(editingFinished()),
                     this,SLOT(readParams()));
    QObject::connect(ui->lineInTemp,SIGNAL(editingFinished()),
                     this,SLOT(readParams()));

    // PERIOD CONNECTION
    QObject::connect(ui->lineInPeriod,SIGNAL(editingFinished()),
                     generator,SLOT(changePeriod()));
}

void MainWindow::initPLOT(){
    // GET PARAMS FROM GUI
    readParams();

    // PREPARE X-AXIS' VECTOR
    for(int i = 0; i < RESOLUTION; ++i){
        lambVecGUI[i] = i + 1;
    }

    // GREEK LABEL
    QString xLabel;
    xLabel = QString::fromUtf8("λ [nm]");

    // CUSTOM FONT
    QFont font("Times", 12, QFont::Bold);

    // MAKE GRAPH
    ui->customPlot->addGraph();
    ui->customPlot->setWindowTitle("Planck's Distribution");
    ui->customPlot->graph(0)->setData(lambVecGUI,spectrumGUI);
    ui->customPlot->xAxis->setLabel(xLabel);
    ui->customPlot->xAxis->setLabelFont(font);
    ui->customPlot->yAxis->setLabelFont(font);
    ui->customPlot->yAxis->setLabel("R [arb.unit.]");
    ui->customPlot->xAxis->setRange(1,2000);
    ui->customPlot->yAxis->setRange(0,4);
    ui->customPlot->replot();
}

void MainWindow::refreshPlot(){
    ui->customPlot->graph(0)->setData(lambVecGUI,spectrumGUI);
    ui->customPlot->xAxis->setRange(params.lambdaMin,params.lambdaMax);
    ui->customPlot->replot();
}

void MainWindow::getQVectors( QVector<double> SPC){
    spectrumGUI = SPC;
    refreshPlot();
}

void MainWindow::readParams(){

    // READ FROM GUI
    params.lambdaMin = ui->lineInLambdaMin->text().toInt();
    params.lambdaMax = ui->lineInLambdaMax->text().toInt();

    // NO PLOT FLIPPING pls
    params.lambdaMax = (params.lambdaMax > params.lambdaMin) ?
                        params.lambdaMax : params.lambdaMin+100;
    ui->lineInLambdaMax->setText(QString::number(params.lambdaMax));
    //
    params.temp = ui->lineInTemp->text().toInt();
    params.period = ui->lineInPeriod->text().toInt();
    params.noise = ui->lineInNoise->text().toInt();

    // SEND TO THREAD
    emit sendParams(params.temp,
                    params.period,
                    params.noise);
}

void MainWindow::initGUI(){

    // START STOP
    ui->buttonStartStop->setCheckable(true);

    // GREEK FONT
    QString lambda = QString((QChar) 0x03BB);

    // HTML STYLE
    // LAMBDA MIN
    QString lambdaMinStr = "<b>"+lambda+"</b>" +
                        "<sub>min</sub> [nm]";
    ui->labLambdaMin->setText(lambdaMinStr);

    //LAMBDA MAX
    QString lambdaMaxStr = "<b>"+lambda+"</b>" +
                        "<sub>max</sub> [nm]";
    ui->labLambdaMax->setText(lambdaMaxStr);

    // TEMP
    QString tempStr = "<b>T</b> [K]";
    ui->labTemp->setText(tempStr);

    // PERIOD
    QString periodStr = "Period [ms]";
    ui->labPeriod->setText(periodStr);

    // NOISE
    QString noiseStr = "Noise [%]";
    ui->labNoise->setText(noiseStr);

    // INPUT VALIDATORS
    ui->lineInTemp->setValidator(new QIntValidator(0,1000,this));
    ui->lineInLambdaMin->setValidator(new QIntValidator(1,2000,this));
    ui->lineInLambdaMax->setValidator(new QIntValidator(1,2000,this));
    ui->lineInNoise->setValidator(new QIntValidator(0,100,this));
    ui->lineInPeriod->setValidator(new QIntValidator(20,2000,this));

    // INITIAL VALUES
    ui->lineInLambdaMin->setText(QString::number(1));
    ui->lineInLambdaMax->setText(QString::number(2000));
    ui->lineInTemp->setText(QString::number(137));
    ui->lineInPeriod->setText(QString::number(100));
    ui->lineInNoise->setText(QString::number(7));
}

void MainWindow::renameButton(bool test){
    QString name = test ? "STOP" : "START";
    ui->buttonStartStop->setText(name);
}

MainWindow::~MainWindow()
{
    delete ui;
}
