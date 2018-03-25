#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>

using namespace std;

class Persona
{
public:
    // Constructor de la clase
    Persona();

    // Constructor sobrecargado
    Persona(string suNombre, string susApellidos, string suDni);

    // Destructor de la clase
    ~Persona(void);

    void setNombre(string value);
    string getNombre();

    void setApellidos(string value);
    string getApellidos();

    void setDni(string value);
    string getDni();

    string nombre;
    string apellido;
    string dni;

};

#endif // PERSONA_H
