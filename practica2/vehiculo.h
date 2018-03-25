#ifndef VEHICULO_H
#define VEHICULO_H

#include <QString>
#include <iostream>
#include <string>
#include <vector>
//#include <string.h>
//#include <sstream>
//#include <stdlib.h>

using namespace std;

class vehiculo
{
public:
    vehiculo();
    ~vehiculo();

    void setNombre(QString name);
    void setRuedas(QString ruedas);
    void setPotencia(int pot);
    void setColor(QString color);
    void setCombustible(bool gasoil, bool gasolina, bool electrico, bool aPedales);
    void setBurbuja(bool burbuja);
    void setBocina(bool bocina);
    void setPosavasos(bool portavasos);
    void setReparaAverias(bool kitRepara, bool repuesto);
    QString getNombre();
    QString getTipo();
    QString getRuedas();
    QString getPotencia();
    QString getColor();
    QString getCombustible();
    QString getAccesorios();
    QString getReparacionTipo();
    QString getMatricula();
    QString generarMatricula();
    vehiculo getVehiculo(int i);
    void addVehiculo(vehiculo nuevo);
    int numeroVehiculos();
    QString toString();


private:
    QString name;
    QString matricula;
    QString ruedas;
    int potencia;
    QString color;
    QString tipo;
    bool gasolina;
    bool gasoil;
    bool electrico;
    bool aPedales;
    bool kitRepara;
    bool repuesto;
    bool burbuja;
    bool bocinas;
    bool portavasos;
    vector<vehiculo> vehiculosGuardados;
};

#endif // VEHICULO_H
