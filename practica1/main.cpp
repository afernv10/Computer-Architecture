#include <iostream>
#include <string>

#include "alumno.h"
#include "persona.h"
#include "profesor.h"

using namespace std;

void imprimirProfesor(Persona *p){
    cout << "\nLos datos del profesor son los siguientes: " << endl;
    cout << "\tNombre: " << p->getNombre() << endl;
    cout << "\tApellidos: " << p->getApellidos() << endl;
    cout << "\tDNI: " << p->getDni() << endl;
    cout << "\n" << endl;
}

void Calificando(void){

    cout << "Vamos a proceder a conocer a un profesor y sus alumnos." << endl;

    Profesor *profe = new Profesor();
    profe->setNombre("Federico");
    profe->setApellidos("Gargola Echevarri");
    profe->setDni("09723901P");

    imprimirProfesor(profe);

    // Creamos los alumnos
    Alumno *alumno1 = new Alumno();
    alumno1->setNombre("Evaristo");
    alumno1->setApellidos("Bueno Bonito");
    alumno1->setDni("70216728G");

    Alumno *alumno2 = new Alumno();
    alumno2->setNombre("Dolores");
    alumno2->setApellidos("Fuertes Agudos");
    alumno2->setDni("71886933X");

    Alumno *alumno3 = new Alumno();
    alumno3->setNombre("Consuelo");
    alumno3->setApellidos("Grande Ausente");
    alumno3->setDni("71290022H");

    // El profesor añade a los alumnos
    profe->addAlumno(alumno1);
    profe->addAlumno(alumno2);
    profe->addAlumno(alumno3);

    profe->listaAlumnos.at(0).addNota(9.0); // alumno1 se añade una nota

    // el profesor asigna notas a varios
    profe->asignarNotas("70216728G", 8.0);
    profe->asignarNotas("71886933X", 6.3, 7.2);

    cout << "El alumno " << alumno1->imprimeAlumno() << " mira una nota suya: " << profe->listaAlumnos.at(0).getNota(1) << endl;

    cout  << "El alumno " << alumno2->imprimeAlumno() << " mira sus notas: " << profe->listaAlumnos.at(1).verNotas() << endl;

    profe->obtenerUnaMedia(alumno1);

    profe->listaAlumnos.at(1).addNota(8.5); // alumno2
    profe->asignarNotas("71290022H", 5.6, 8, 8.5);

    cout << "El alumno " << alumno2->imprimeAlumno() << " consulta su numero de notas: " <<  profe->listaAlumnos.at(1).getNumeroNotas() << endl;

    // mostramos la lista de alumnos con sus datos
    profe->mostrarLista();

    // mostramos al alumno con mejor nota media, con la condicion de que tiene que tener 3 notas
    profe->mostrarMejorAlumno();
}

int main()
{
    Calificando();

    return 0;
}
