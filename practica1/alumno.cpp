#include "alumno.h"
#include <string>

Alumno::Alumno(){

}

void Alumno::addNota(float nota){
    if(this->listaNotas.size() < 3){
        this->listaNotas.push_back(nota);
        cout << this->imprimeAlumno() << " se añade un " << nota << endl;
    } else {
        cout << this->imprimeAlumno() << " no puede añadir más notas porque ya hay 3." << endl;
    }
}

float Alumno::getNota(int n){
    float nota;
    nota = this->listaNotas.at(n);
    return nota;
}

string Alumno::verNotas(){
    string salida;
    string num;
    for(int i = 0; i < this->listaNotas.size(); i++){
        num = to_string(this->listaNotas.at(i));
        salida = salida + " " + num;
    }
    return salida;
}

int Alumno::getNumeroNotas(){

    return this->listaNotas.size();
}

void Alumno::setMedia(){
    float sum;
    for(int i = 0; i < this->listaNotas.size(); i++){
        sum += this->listaNotas.at(i);
    }
    this->notaMedia = sum / this->listaNotas.size();
}

float Alumno::getMedia(){
    return this->notaMedia;
}

string Alumno::imprimeAlumno(){
    string cad;
    cad = this->nombre + " " + this->apellido;
    return cad;
}
string Alumno::mostrarDatosAlumno(){
    string cad;
    cad = this->nombre + " " + this->apellido + ", DNI: " + this->dni;
    return cad;
}


Alumno::~Alumno(){
    // destructor de la clase
}
