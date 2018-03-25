#include "vehiculo.h"

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

vehiculo::vehiculo(){
   // constructor
}

void vehiculo::setNombre(QString name){
    this->name = name;
}

void vehiculo::setRuedas(QString ruedas){
    this->ruedas = ruedas;
}

void vehiculo::setPotencia(int pot){
    this->potencia = pot;
}

void vehiculo::setColor(QString color){
    this->color = color;
}

void vehiculo::setCombustible(bool gasoil, bool gasolina, bool electrico, bool aPedales){
    this->gasolina = gasolina;
    this->gasoil = gasoil;
    this->electrico = electrico;
    this->aPedales = aPedales;
}

void vehiculo::setBurbuja(bool burbuja){
    this->burbuja = burbuja;
}

void vehiculo::setBocina(bool bocina){
    this->bocinas = bocina;
}

void vehiculo::setPosavasos(bool portavasos){
    this->portavasos = portavasos;
}

void vehiculo::setReparaAverias(bool kitRepara, bool repuesto){
    this->kitRepara = kitRepara;
    this->repuesto = repuesto;
}

QString vehiculo::getNombre(){
    return this->name;
}

QString vehiculo::getMatricula(){
    return this->matricula;
}

QString vehiculo::getRuedas(){
    return this->ruedas;
}

QString vehiculo::getPotencia(){
    QString s = QString::number(this->potencia) + " CV";
    return s;
}

QString vehiculo::getColor(){
    return this->color;
}

QString vehiculo::getCombustible(){
    if(this->gasoil){
        return "Gasoil";
    } else if(this->gasolina){
        return "Gasolina";
    } else if(this->electrico){
        return "Electrico";
    } else if(this->aPedales){
        return "A pedales";
    } else {
        return "No se ha especificado combustible!";
    }
}

QString vehiculo::getAccesorios(){
    if(this->burbuja && this->bocinas && this->portavasos){
        return "Burbuja para niños, bocinas múltiples y portavasos gigante";
    } else if(this->burbuja && this->bocinas){
        return "Burbuja y bocinas";
    } else if(this->burbuja && this->portavasos){
        return "Burbuja y portavasos";
    } else if(this->bocinas && this->portavasos){
        return "Bocinas y portavasos";
    } else if(this->burbuja){
        return "Burbuja";
    } else if(this->bocinas){
        return "Bocinas";
    } else if(this->portavasos){
        return "Portavasos";
    } else {
        return "No tiene accesorios";
    }
}

QString vehiculo::getReparacionTipo(){
    if(this->kitRepara){
        return "Kit de reparacion";
    } else if(this->repuesto){
        return "Rueda de repuesto";
    } else {
        return "No se ha seleccionado repara!!";
    }
}

QString vehiculo::generarMatricula(){
    srand(time(NULL));
    char matri[8];
    string numeros = "0123456789";
    string letras = "BCDFGHJKLMNPQRSTVWXYZ";

    for(int i = 0; i <= 7; i++){
        if(i<4){
            matri[i] = numeros[rand() % numeros.length()];
        } else if(i<7) {
            matri[i] = letras[rand() % letras.length()];
        } else if(i == 7){
            matri[i] = '\0';
        }
    }

    matricula = QString::fromStdString(matri);
    return matricula;
}

QString vehiculo::getTipo(){
    if(this->ruedas.contains("1")){
        this->tipo = "Monociclo";
    } else if(this->ruedas.contains("2")){
        if(gasoil || gasolina){
            tipo = "Motocicleta";
        } else if(aPedales && electrico){
            tipo = "Bicicleta con motor eléctrico";
        } else if(aPedales){
            tipo = "Bicicleta";
        }
    } else if(ruedas.contains("3")){
        if(gasoil || gasolina || electrico){
            tipo = "Moto de 3 ruedas";
        } else {
            tipo = "Triciclo";
        }
    } else if(ruedas.contains("4")){
        if(burbuja && bocinas && getColor() == "Verde" && portavasos){
            tipo = "Coche de Homer";
        } else {
            tipo = "Coche";
        }
    } else {
        tipo = "Camion";
    }
    return tipo;
}

int vehiculo::numeroVehiculos(){
    return vehiculosGuardados.size();
}

vehiculo vehiculo::getVehiculo(int i){
    return vehiculosGuardados.at(i);
}

void vehiculo::addVehiculo(vehiculo nuevo){
    vehiculosGuardados.push_back(nuevo);
}

QString vehiculo::toString(){
    int n = vehiculosGuardados.size() + 1;

    QString cad;
    cad = "\n" +  QString::number(n) + ". " + this->getNombre().toUpper() + " - " + this->getTipo() + " [" + this->getMatricula() +
            "]\n ---> " + this->getRuedas() + " ruedas / " + this->getPotencia() + " / Color " + this->getColor().toLower() +
            " / " + this->getCombustible() + " / " + this->getAccesorios() + " / " + this->getReparacionTipo() +
            "\n    ______________________";

    return cad;
}

vehiculo::~vehiculo(){
    // destructor de la clase
}
