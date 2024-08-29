// 1
#include <iostream>

using namespace std;

// Definir estructura paciente
struct Paciente {
    string nombre;
    int edad;
    int peso;
    float altura;

};

int main(){

    cout<< "Lista de pacientes:"<<::endl;

    Paciente paciente1;
    paciente1.nombre = "Ian";
    paciente1.edad = 15;
    paciente1.peso = 60;
    paciente1.altura = 1.71;

    Paciente paciente2;
    paciente2.nombre = "Gabriela";
    paciente2.edad = 20;
    paciente2.peso = 65;
    paciente2.altura = 1.70;

    Paciente paciente3;
    paciente3.nombre = "Florencio";
    paciente3.edad = 50;
    paciente3.peso = 77;
    paciente3.altura = 1.85;


    // Imprimir pacientes
    cout<<"Nombre: "<<paciente1.nombre <<".\n"<<"Edad: "<<paciente1.edad<<".\n"<<"Peso: "<<paciente1.peso<<".\n"<<"Altura: "<<paciente1.altura<<".\n"<<::endl;
    cout<<""<<::endl;
    cout<<"Nombre: "<<paciente2.nombre <<".\n"<<"Edad: "<<paciente2.edad<<".\n"<<"Peso: "<<paciente2.peso<<".\n"<<"Altura: "<<paciente2.altura<<".\n"<<::endl;
    cout<<""<<::endl;
    cout<<"Nombre: "<<paciente3.nombre <<".\n"<<"Edad: "<<paciente3.edad<<".\n"<<"Peso: "<<paciente3.peso<<".\n"<<"Altura: "<<paciente3.altura<<".\n"<<::endl;


    return 0;
}