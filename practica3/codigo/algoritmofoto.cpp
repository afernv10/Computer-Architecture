#include "algoritmofoto.h"
#include "ui_algoritmofoto.h"
#include <QFile>
#include <QFileDialog>
#include <time.h>
#include <QMessageBox>
#include <string>
#include <QPixmap>
#include <chrono>

using namespace std::chrono;

AlgoritmoFoto::AlgoritmoFoto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgoritmoFoto)
{
    ui->setupUi(this);
    tiempoPasado = 0;
    media = 0;
    contadorVeces = 0;
}

AlgoritmoFoto::~AlgoritmoFoto()
{
    delete ui;
}

void AlgoritmoFoto::on_pushEjecutar_clicked(){

    if(imagenColor.isNull()){
        QMessageBox::warning(0,"ERROR", "NO HAY SELECCIONADA NINGUNA IMAGEN!");
    } else if(contadorVeces<5){
        // iniciamos reloj para que cuente
        high_resolution_clock::time_point inicio = high_resolution_clock::now();

        contadorVeces++;
        algoritmo();

        duration<double, std::milli> fin = high_resolution_clock::now() - inicio;
        tiempoPasado += fin.count();
        media = tiempoPasado/contadorVeces;
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

        if(!fileName.isNull()){
            ui->label_origen->setText("Imagen color en: " + fileName);
        }

        // guardo la imagen si hemos seleccionado directorio
        if(!imageNamePath.isNull()){
            imagenByN.save(imageNamePath);
        } else {
            QMessageBox::warning(0,"AVISO", "No se ha guardado la imagen porque no has seleccionado un directorio.");
        }

    } else {
        QMessageBox::warning(0,"ERROR", "INTENTOS MÁXIMOS REALIZADOS (5)");
    }
}

void AlgoritmoFoto::algoritmo(){


    imagenByN = imagenColor.copy();
    QSize sizeImage = imagenByN.size();
    int width = sizeImage.width();
    int height = sizeImage.height();

    QRgb color;

    for (int f1 = 0; f1 < width; f1++) {
        for (int f2 = 0; f2 < height; f2++) {
            color = imagenByN.pixel(f1, f2);
            int gray = (qRed(color) + qGreen(color) + qBlue(color))/3;
            imagenByN.setPixel(f1, f2, qRgb(gray, gray, gray));
                    // otra opcion:
            //int gray = qGray(color);
            //imagenByN.setPixel(f1, f2, qRgb(gray, gray, gray));
        }
    }

    int widthx = ui->imagenOriginal->width();
    int heightx = ui->imagenOriginal->height();
    QPixmap antes = QPixmap::fromImage(imagenColor);
    QPixmap despues = QPixmap::fromImage(imagenByN);
    ui->imagenOriginal->setPixmap(antes.scaled(widthx, heightx, Qt::KeepAspectRatio));
    ui->imagenFinal->setPixmap(despues.scaled(widthx, heightx, Qt::KeepAspectRatio));


}

void AlgoritmoFoto::on_pushImagen_clicked()
{
    fileName = QFileDialog::getOpenFileName();
    ui->label_origen->setText("Imagen color en: " + fileName);
    imagenColor.load(fileName);
}

void AlgoritmoFoto::on_pushImagen_2_clicked()
{
    imageNamePath = QFileDialog::getSaveFileName(this, tr("Guardar en..."), "b&n_image", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
    ui->label_guardado->setText("Imagen b&n en: " + imageNamePath);
}



void AlgoritmoFoto::on_pushReset_clicked()
{
    contadorVeces = 0;
    tiempoPasado = 0;
    media = 0;
    imageNamePath = QString();

    ui->tiempo1->clear();
    ui->tiempo2->clear();
    ui->tiempo3->clear();
    ui->tiempo4->clear();
    ui->tiempo5->clear();
    ui->media->clear();
    ui->imagenOriginal->clear();
    ui->imagenFinal->clear();
    ui->label_origen->clear();
    ui->label_guardado->clear();

    QMessageBox::information(0,"Reset", "Si quieres cambiar de imagen selecciona en 'Seleccionar foto...'");
}
