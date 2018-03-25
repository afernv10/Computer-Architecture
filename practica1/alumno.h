#ifndef ALUMNO_H
#define ALUMNO_H

#include <vector>
#include "persona.h"

class Alumno : public Persona
{
public:
    Alumno();
    ~Alumno();

    void addNota(float nota);
    float getNota(int n);
    string verNotas();
    int getNumeroNotas();
    void setMedia();
    float getMedia();
    string imprimeAlumno();
    string mostrarDatosAlumno();

private:
    float notaMedia;
    vector<float> listaNotas;
};

#endif // ALUMNO_H
