// 3 as lissta, aca e deben agregar
#include <iostream>
//#include <string>

// Definir estructura paciente
struct Paciente {
    std::string nombre;
    int edad;
    int peso;
    float altura;
    Paciente* next; // puntero para la siguiente persona

};



// Función para agregar pacientes a la lista
void agregarPaciente(Paciente*& head, const std::string& nombre, int edad, int peso, float altura){
    
    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente -> nombre = nombre;
    nuevoPaciente -> edad = edad;
    nuevoPaciente -> peso = peso;
    nuevoPaciente -> altura = altura;
    nuevoPaciente -> next = head;
    head = nuevoPaciente;

}

// Función para imprimir pacientes
void imprimirPaciente(const Paciente* head){
    const Paciente* actual = head;

    while(actual != nullptr){
        std::cout<<"Paciente actual -------------"<<std::endl;

        std::cout<<"Nombre: " << actual -> nombre <<std::endl;
        std::cout<<"Edad: "<< actual -> edad <<std::endl;
        std::cout<<"Peso: "<< actual -> peso <<std::endl;
        std::cout<<"Altura: "<< actual -> altura <<std::endl;

        actual = actual->next;
    }
}



int main(){

    Paciente* head = nullptr;

    // Agregar pacientes
    agregarPaciente(head, "Ian", 15, 60, 1.71);
    agregarPaciente(head, "Gabriela", 25, 65, 1.70);
    agregarPaciente(head, "Florencio", 50, 77, 1.85);

    imprimirPaciente(head);


/*
    Paciente* paciente1 = new Paciente();
    paciente1-> nombre = "Ian";
    paciente1-> edad = 15;
    paciente1 -> peso = 60;
    paciente1 -> altura = 1.71;

    Paciente* paciente2 = new Paciente();
    paciente2-> nombre = "Gabriela";
    paciente2-> edad = 25;
    paciente2 -> peso = 65;
    paciente2 -> altura = 1.70;

    Paciente* paciente3 = new Paciente();
    paciente3-> nombre = "Florencio";
    paciente3-> edad = 50;
    paciente3 -> peso = 77;
    paciente3 -> altura = 1.85;

    // Linkear los pacientess
    //maybe esto en un ciclo for
    paciente1 -> next = paciente2;
    paciente2 -> next = paciente3;


    // Acceder a la lista linkeada
    Paciente* current = paciente1;

    while(current != nullptr){
        std::cout<< current->nombre << " es paciente" << std::endl;
        current = current ->next;
    }
*/

    return 0;
}