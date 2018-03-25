#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vehiculo.h"
#include <ostream>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->newVehiculo = new vehiculo();
    vehiculosMostrados = 0;
    ui->radioBGasoil->setChecked(true);
    ui->radioBRepuesto->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonMatricula_clicked()
{
    ui->qTextMatricula->setText(newVehiculo->generarMatricula());
}

void MainWindow::crearUnVehiculo(){
    newVehiculo->setNombre(ui->lineEditName->text());
    newVehiculo->setRuedas(ui->spinBoxRuedas->cleanText() );
    newVehiculo->setPotencia(ui->sliderPotencia->value());
    newVehiculo->setPotencia(ui->spinBoxPotencia->value());
    newVehiculo->setColor(ui->comboColor->currentText());
    newVehiculo->setCombustible(ui->radioBGasoil->isChecked(), ui->radioBGasolina->isChecked(), ui->radioBElectrico->isChecked(), ui->radioBaPedales->isChecked());
    newVehiculo->setBurbuja(ui->checkBurbuja->isChecked());
    newVehiculo->setBocina(ui->checkBocinas->isChecked());
    newVehiculo->setPosavasos(ui->checkPortavasos->isChecked());
    newVehiculo->setReparaAverias(ui->radioBKitRepara->isChecked(),ui->radioBRepuesto->isChecked());

}

void MainWindow::on_pushButtonReset_clicked(){
    ui->lineEditName->clear();
    ui->spinBoxRuedas->clear();
    ui->checkBurbuja->setChecked(false);
    ui->checkBocinas->setChecked(false);
    ui->checkPortavasos->setChecked(false);
    ui->qTextMatricula->clear();
    ui->qTextTipo->clear();
}

void MainWindow::on_pushButtonComprobar_clicked(){
    crearUnVehiculo();
    ui->qTextTipo->setText(newVehiculo->getTipo());
}

void MainWindow::on_pushButtonGuardar_clicked(){

    newVehiculo->addVehiculo(*newVehiculo);
    QString numGuardados = "Vehículos guardados: " + QString::number(newVehiculo->numeroVehiculos());
    ui->qTextNumGuardados->setText(numGuardados);
    QString numMostrados = "Mostrando " + QString::number(vehiculosMostrados) + " de " + QString::QString::number(newVehiculo->numeroVehiculos());
    ui->qTextNumMostrados->setText(numMostrados);
}

void MainWindow::on_pushButtonMostrar_clicked(){
    int ult = (newVehiculo->numeroVehiculos()) - 1;
    vehiculosMostrados = newVehiculo->numeroVehiculos();
    contMostrar++;
    int n = 0;

    if(ult+1 > contMostrar){
        ui->qTextVehiculosLista->clear();
        while (n < newVehiculo->numeroVehiculos()) {
             ui->qTextVehiculosLista->append(newVehiculo->getVehiculo(n).toString());
             n++;
        }
    } else  {
        for(int i = ult; i < newVehiculo->numeroVehiculos(); i++){
            ui->qTextVehiculosLista->append(newVehiculo->getVehiculo(i).toString());
        }
    }

    QString numMostrados = "Mostrando " + QString::number(vehiculosMostrados) + " de " + QString::QString::number(newVehiculo->numeroVehiculos());
    ui->qTextNumMostrados->setText(numMostrados);
}
