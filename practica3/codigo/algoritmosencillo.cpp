#include "algoritmosencillo.h"
#include "ui_algoritmosencillo.h"
#include <QFile>
#include <QFileDialog>
#include <time.h>
#include <QMessageBox>
#include <QTextStream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

AlgoritmoSencillo::AlgoritmoSencillo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgoritmoSencillo)
{
    ui->setupUi(this);
    tiempoPasado = 0;
    media = 0;
    contadorVeces = 0;
}

AlgoritmoSencillo::~AlgoritmoSencillo()
{
    delete ui;
}

void AlgoritmoSencillo::on_pushFichero_clicked()
{
    QString nombreFichero = QFileDialog::getOpenFileName();
    QFile file(nombreFichero);

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"AVISO","No se ha abierto nigún archivo.");
    } else {
        QTextStream in(&file);
        allText = in.readAll();
        file.close();
    }
}

/**
 * Algoritmo que coge palabras de un .txt y las ordena alfabeticamente, guardandolas en otro fichero
 */
void AlgoritmoSencillo::algoritmo(){

    QString fileName = "algSencillo_" + QString::number(contadorVeces) + ".txt";

    // metemos las palabras en vector para poder ordenarlas
    palabras = allText.split(" ");
    original = palabras;

    // creamos el fichero en el que vamos a meter el resultado
    QFile ficheroNuevo("../PalabrasOrdenadas/" + fileName);
    ficheroNuevo.open(QIODevice::WriteOnly | QIODevice::Truncate);

    QTextStream writingNewFile(&ficheroNuevo);

    for(int i = 0; i < palabras.length()-1; i++){
        for(int j = i+1; j < palabras.length(); j++){

            if(strcmp(palabras[i].toStdString().c_str(), palabras[j].toStdString().c_str()) > 0){
                QString temp = palabras[i];
                palabras[i] = palabras[j];
                palabras[j] = temp;
            }
        }
    }

    // una vez que lo tenemos ordenado en un vector
    // metemos en el fichero nuevo
    for(int i = 0; i < palabras.length(); i++){
        writingNewFile << palabras[i];

        if(i != palabras.length() -1){
            writingNewFile << ", ";
        }

    }
    ficheroNuevo.close();
}

void AlgoritmoSencillo::on_pushEjecutar_clicked(){

    if(allText.isEmpty()){
        QMessageBox::warning(0,"ERROR", "NO HAY SELECCIONADO NINGÚN FICHERO!");
    } else if(contadorVeces<5){

        // creamos la carpeta donde meteremos los archivos con las palabras ordenadas
        QDir dir("../PalabrasOrdenadas/");
        if(!dir.exists()){
            dir.mkdir("../PalabrasOrdenadas/");
        }

        // iniciamos reloj para que cuente
        //clock_t inicio = clock();
        high_resolution_clock::time_point inicio = high_resolution_clock::now();

        contadorVeces++;
        algoritmo();

        //double fin = (double) (clock() - inicio)/CLOCKS_PER_SEC;
        /*clock_t fin =(clock() - inicio)/CLOCKS_PER_SEC;
        tiempoPasado += (long)fin;
        media = (double) tiempoPasado/contadorVeces;*/

        duration<double, std::milli> fin = high_resolution_clock::now() - inicio;
        tiempoPasado += fin.count();
        media = tiempoPasado/contadorVeces;
        //QString sTs = QString::number(fin.count()*1000) + " ms";
        QString sTs = QString::number(fin.count()) + " ms";

        switch (contadorVeces) {
        case 1:
            ui->tiempo1->setText(sTs);
            break;
        case 2:
            ui->tiempo2->setText(sTs);
            break;
        case 3:
            ui->tiempo3->setText(sTs);
            break;
        case 4:
            ui->tiempo4->setText(sTs);
            break;
        case 5:
            ui->tiempo5->setText(sTs);
            break;
        }

        ui->media->setText(QString::number(media) + " ms");

        // limpiamos los cuadros donde mostramos las palabras
        ui->sinOrdenar->clear();
        ui->ordenadas->clear();

        for(int i = 0; i<original.length(); i++){
            ui->sinOrdenar->append(original[i] + "\n");
        }

        for(int i = 0; i<palabras.length(); i++){
            ui->ordenadas->append(palabras[i] + "\n");
        }

    } else {
        QMessageBox::warning(0,"ERROR", "INTENTOS MÁXIMOS REALIZADOS (5)");
    }
}

void AlgoritmoSencillo::on_pushReset_clicked(){

    contadorVeces = 0;
    tiempoPasado = 0;
    media = 0;
    allText.clear();

    for(int i = 0; i < palabras.length(); i++){
        palabras.removeAt(i);
    }

    ui->tiempo1->clear();
    ui->tiempo2->clear();
    ui->tiempo3->clear();
    ui->tiempo4->clear();
    ui->tiempo5->clear();
    ui->media->clear();
    ui->sinOrdenar->clear();
    ui->ordenadas->clear();
}
