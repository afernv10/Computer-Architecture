#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <sstream>

//#define _STEPimpHex_
//#define _STEPvariablesunion_

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QWidget::connect(ui->valor1Dec, SIGNAL(textChanged(QString)), ui->valor1Hex, SLOT(setText(QString)));
    //QWidget::connect(ui->valor1Dec, SIGNAL(textChanged(QString)), ui->valor1Hex, &MainWindow::ponerEnHexa);
}

QString MainWindow::ponerEnHexa(QString v){

    bool ok;
        float f = v.toFloat(&ok);
        union valor x;
        x.valorReal = f;
        // el 0 no sale como 0x00000000, sale como 0x0 :(
        QString hex = "0x" + QString::number(x.valorEntero, 16);
    #ifdef _STEPimpHex_
        std::cout << "f " << f << endl;
        std::cout << "l10 " << l << endl;
        std::cout << "l16 " << l16 << endl;
        std::cout << "hex " << hex.toStdString() << endl;
    #endif
    return hex;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enHex1_clicked()
{
    ui->valor1Hex->setText(ponerEnHexa(ui->valor1Dec->text()));
}

void MainWindow::on_enHex2_clicked()
{
    ui->valor2Hex->setText(ponerEnHexa(ui->valor2Dec->text()));
}

void MainWindow::on_bCalcula_clicked()
{
    on_enHex1_clicked();
    on_enHex2_clicked();

    asignarValoresUnion();

    myAlu.setValoresA(a.campos.s, a.campos.e, a.campos.f);
    myAlu.setValoresB(b.campos.s, b.campos.e, b.campos.f);
    myAlu.setValoresEnteros(a.valorEntero, b.valorEntero);

    if(ui->rBSum->isChecked()){

        // SUMA

        myAlu.suma();
        resultado.campos.s = myAlu.getSignoResultado();
        resultado.campos.e = myAlu.getExponenteResultado();
        resultado.campos.f = myAlu.getFraccionariaResultado();

        /*
         * accedemos a los valores del resultado en float e int de la union
         * donde ya metimos los campos por separado
         */

        // sacamos los resultados en la interfaz
        ui->resultDec->setText(QString::number(resultado.valorReal));
        QString resultHex = "0x" + QString::number(resultado.valorEntero, 16);
        ui->resultHex->setText(resultHex);

    } else if(ui->rBPro->isChecked()){

        // PRODUCTO

        myAlu.producto();
        if(myAlu.checkResultadoIndeterminado()){
            ui->resultDec->setText("Indeterminado(NaN)");
            ui->resultHex->setText("Indeterminado(NaN)");
        } else if(myAlu.checkResultadoNaN()){
                ui->resultDec->setText("NaN");
                ui->resultHex->setText("NaN");
        } else if(myAlu.checkResultadoInfinito()){
            ui->resultDec->setText("OVERFLOW");
            ui->resultHex->setText("Infinito");
        } else if(myAlu.checkResultadoUnderflow()){
            ui->resultDec->setText("UNDERFLOW");
            ui->resultHex->setText("0");
        } else {
            resultado.campos.s = myAlu.getSignoResultado();
            resultado.campos.e = myAlu.getExponenteResultado();
            resultado.campos.f = myAlu.getFraccionariaResultado();

            /*
             * accedemos a los valores del resultado en float e int de la union
             * donde ya metimos los campos por separado
             */

            // sacamos los resultados en la interfaz
            ui->resultDec->setText(QString::number(resultado.valorReal));
            QString resultHex = "0x" + QString::number(resultado.valorEntero, 16);
            ui->resultHex->setText(resultHex);
        }


    } else {

        // DIVISIÓN

        myAlu.division();
        if(myAlu.checkResultadoInfinito()){
            ui->resultHex->setText("Infinito");
        } else if(myAlu.checkResultadoNaN()){
            ui->resultHex->setText("NaN");
        } else {
            resultado.campos.s = myAlu.getSignoResultado();
            resultado.campos.e = myAlu.getExponenteResultado();
            resultado.campos.f = myAlu.getFraccionariaResultado();

            /*
             * accedemos a los valores del resultado en float e int de la union
             * donde ya metimos los campos por separado
             */

            // sacamos los resultados en la interfaz
            ui->resultDec->setText(QString::number(resultado.valorReal));
            QString resultHex = "0x" + QString::number(resultado.valorEntero, 16);
            ui->resultHex->setText(resultHex);
        }
    }
}

void MainWindow::asignarValoresUnion(){
    bool ok;
    float vf1 = ui->valor1Dec->text().toFloat(&ok);
    float vf2 = ui->valor2Dec->text().toFloat(&ok);

    a.valorReal = vf1;
    b.valorReal = vf2;
#ifdef _STEPvariablesunion_
    std::cout << "float valor real a: " << a.valorReal << endl;
    std::cout << "uint valor entero a: " << a.valorEntero << endl;
    std::cout << "ieee754 f campos a: " << a.campos.f << endl;
    std::cout << "ieee754 e campos a: " << a.campos.e << endl;
    std::cout << "ieee754 s campos a: " << a.campos.s << endl;

    std::cout << "   -------   " << endl;

    std::cout << "float valor real b: " << b.valorReal << endl;
    std::cout << "uint valor entero b: " << b.valorEntero << endl;
    std::cout << "ieee754 f campos b: " << b.campos.f << endl;
    std::cout << "ieee754 e campos b: " << b.campos.e << endl;
    std::cout << "ieee754 s campos b: " << b.campos.s << endl;
#endif
}
