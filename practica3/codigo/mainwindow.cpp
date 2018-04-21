#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ventanaAlg1 = new AlgoritmoSencillo();
    ventanaAlg2 = new AlgoritmoFoto();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //ventanaAlg1 = new AlgoritmoSencillo();
    if(!this->ventanaAlg1->isVisible()){
        ventanaAlg1->show();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    //ventanaAlg2 = new AlgoritmoFoto();
    if(!ventanaAlg2->isVisible()){
        ventanaAlg2->show();
    }
}
