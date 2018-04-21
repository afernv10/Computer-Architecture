#ifndef ALGORITMOSENCILLO_H
#define ALGORITMOSENCILLO_H

#include <QWidget>

namespace Ui {
class AlgoritmoSencillo;
}

class AlgoritmoSencillo : public QWidget
{
    Q_OBJECT

public:
    explicit AlgoritmoSencillo(QWidget *parent = 0);
    ~AlgoritmoSencillo();

private slots:
    void on_pushFichero_clicked();

    void on_pushEjecutar_clicked();

    void on_pushReset_clicked();

private:
    Ui::AlgoritmoSencillo *ui;
    double tiempoPasado;
    double media;
    int contadorVeces;
    QString allText;
    QStringList palabras;
    QStringList original;
    void algoritmo();
};

#endif // ALGORITMOSENCILLO_H
