#include "profesor.h"

Profesor::Profesor(){
    // constructor de profesor
}

void Profesor::addAlumno(Alumno *alu){
    cout << this->getNombre() << " añade al alumno " << alu->getNombre() << " " << alu->getApellidos() << endl;
    this->listaAlumnos.push_back(*alu);
}

void Profesor::asignarNotas(string dni, float nota1){
    cout << "El profesor realiza un cambio, en ";
    for(int i = 0; i < this->listaAlumnos.size(); i++){
        //Alumno temp = this->listaAlumnos.at(i);
        if(this->listaAlumnos.at(i).getDni() == dni){
            this->listaAlumnos.at(i).addNota(nota1);
            this->listaAlumnos.at(i).setMedia();
            //this->listaAlumnos.at(i) = temp;
            return;
        }
    }
}

void Profesor::asignarNotas(string dni, float nota1, float nota2){

    for(int i = 0; i < this->listaAlumnos.size(); i++){
        Alumno temp = this->listaAlumnos.at(i);
        if(temp.dni == dni){
            cout << "El profesor realiza un cambio, en ";
            temp.addNota(nota1);
            cout << "El profesor realiza un cambio, en ";
            temp.addNota(nota2);
            temp.setMedia();
            this->listaAlumnos.at(i) = temp;
            return;
        }
    }
}

void Profesor::asignarNotas(string dni, float nota1, float nota2, float nota3){
    for(int i = 0; i < this->listaAlumnos.size(); i++){
        Alumno temp = this->listaAlumnos.at(i);
        if(temp.dni == dni){
            cout << "El profesor realiza un cambio, en ";
            temp.addNota(nota1);
            cout << "El profesor realiza un cambio, en ";
            temp.addNota(nota2);
            cout << "El profesor realiza un cambio, en ";
            temp.addNota(nota3);
            temp.setMedia();
            this->listaAlumnos.at(i) = temp;
            return;
        }
    }
}

void Profesor::obtenerUnaMedia(Alumno *alu){
    float media;
    for(int i = 0; i < listaAlumnos.size(); i++){
        if(alu->getDni() == listaAlumnos.at(i).getDni()){
            media = listaAlumnos.at(i).getMedia();
        }
    }
    cout << alu->imprimeAlumno() << " mira su nota media que es: " << media << endl;
}

void Profesor::mostrarLista(){
    cout << "\n********************** LISTA DE ALUMNOS de " << this->getNombre() <<" **********************\n" << endl;
    Alumno temp;
    for(int i = 0; i < this->listaAlumnos.size(); i++){
        temp = this->listaAlumnos.at(i);
        cout << temp.mostrarDatosAlumno() << endl;
        cout << "\tNotas: " << temp.verNotas() << endl;
        cout << "\tNota media: " << temp.getMedia() << "\n" << endl;
    }
    cout << "*********************************************************************************************" << endl;
}

void Profesor::mostrarMejorAlumno(){
    Alumno temp;
    Alumno mejor; //= this->listaAlumnos.at(0);
    float mejorMedia = 0.0;
    for(int i = 1; i < this->listaAlumnos.size(); i++){
        temp = this->listaAlumnos.at(i);
        if(temp.getNumeroNotas() == 3){
            if(temp.getMedia() > mejorMedia){
                mejor = temp;
                mejorMedia = temp.getMedia();
            }
        }
    }
    cout << "El mejor de la clase es " << mejor.imprimeAlumno() << " con una nota de " << mejor.getMedia() << endl;
}

Profesor::~Profesor(){
    // destructor de la clase
}
