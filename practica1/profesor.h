#ifndef PROFESOR_H
#define PROFESOR_H

#include <vector>
#include "persona.h"
#include "alumno.h"

class Profesor : public Persona
{
public:
    Profesor();

    ~Profesor();

    void addAlumno(Alumno* alu);
    void asignarNotas(string dni, float nota1);
    void asignarNotas(string dni, float nota1, float nota2);
    void asignarNotas(string dni, float nota1, float nota2, float nota3);
    void obtenerUnaMedia(Alumno* alu);
    void mostrarLista();
    void mostrarMejorAlumno();

    vector<Alumno> listaAlumnos;

};

#endif // PROFESOR_H
