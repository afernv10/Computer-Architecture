#ifndef ALGORITMOFOTO_H
#define ALGORITMOFOTO_H

#include <QWidget>

namespace Ui {
class AlgoritmoFoto;
}

class AlgoritmoFoto : public QWidget
{
    Q_OBJECT

public:
    explicit AlgoritmoFoto(QWidget *parent = 0);
    ~AlgoritmoFoto();

private slots:
    void on_pushEjecutar_clicked();

    void on_pushImagen_2_clicked();

    void on_pushImagen_clicked();

    void on_pushReset_clicked();

private:
    Ui::AlgoritmoFoto *ui;
    double tiempoPasado;
    double media;
    int contadorVeces;
    QImage imagenColor;
    QImage imagenByN;
    void algoritmo();
    QString imageNamePath;
    QString fileName;
};

#endif // ALGORITMOFOTO_H
