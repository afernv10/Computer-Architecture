#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vehiculo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void crearUnVehiculo();

private slots:
    void on_pushButtonMatricula_clicked();

    void on_pushButtonReset_clicked();

    void on_pushButtonComprobar_clicked();

    void on_pushButtonGuardar_clicked();

    void on_pushButtonMostrar_clicked();

private:
    Ui::MainWindow *ui;
    vehiculo *newVehiculo;
    int vehiculosMostrados;
    int contMostrar;
};

#endif // MAINWINDOW_H
