// 2 - los datos de la etructura a un arreglo luego en el siguiente arhchivo de paciente dlist pasarlos a una listaa
#include <iostream>


// Definir estructura paciente
struct Paciente {
    std::string nombre;
    int edad;
    int peso;
    float altura;

};


int main(){

    // Arreglo de 3 objetos tipo paciente
    Paciente paciente[3];

    // mantener info del struct/datos del paciente pasarla a un arreglo
    //datos[0] = [nombre: ian, edad: 15, peso: 60, altura: 1.71]

    // Inicializar el arreglo
    paciente[0].nombre = "Ian";
    paciente[0].edad = 15;
    paciente[0].peso = 60;
    paciente[0].altura = 1.71;

    paciente[1].nombre = "Gabriela";
    paciente[1].edad = 25;
    paciente[1].peso = 65;
    paciente[1].altura = 1.70;

    paciente[2].nombre = "Florencio";
    paciente[2].edad = 50;
    paciente[2].peso = 77;
    paciente[2].altura = 1.85;

    // Acceder y recorrer el arreglo e imprimir datos pacientes
    for(int i = 0; i < 3; i++){
        std::cout<<"Nombre: " << paciente[i].nombre <<std::endl;
        std::cout<<"Edad: "<< paciente[i].edad <<std::endl;
        std::cout<<"Peso: "<< paciente[i].peso <<std::endl;
        std::cout<<"Altura: "<< paciente[i].altura <<std::endl;
        std::cout<<std::endl;
    }

    return 0;
}