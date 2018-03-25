#include "persona.h"

Persona::Persona(){

}

Persona::Persona(string suNombre, string susApellidos, string suDni){

    this->nombre = suNombre;
    this->apellido = susApellidos;
    this->dni = suDni;
}

void Persona::setNombre(string value){
    nombre = value;
}

string Persona::getNombre(){
    return nombre;
}

void Persona::setApellidos(string value){
    apellido = value;
}

string Persona::getApellidos(){
    return apellido;
}

void Persona::setDni(string value){
    dni = value;
}

string Persona::getDni(){
    return dni;
}


Persona::~Persona(){
    // destructor de la clase
}
