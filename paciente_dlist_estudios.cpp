// 4
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

// Función para determinar la edad promedio del grupo
float edadPromedio(Paciente* head){

    int suma_edades = 0;
    int cant_pacientes = 0;

    Paciente* actual = head;

    while(actual != nullptr){

        suma_edades = suma_edades + actual -> edad;
        cant_pacientes++;

        actual = actual -> next;

    }

    float promedio_edad = suma_edades/cant_pacientes;

    std::cout<<"Edad promedio del grupo: "<< promedio_edad << "." <<std::endl;
    return promedio_edad;

}

// Función para determinar el peso promedio del grupo
float pesoPromedio(Paciente* head){

    int suma_peso = 0;
    int cant_pacientes = 0;

    Paciente* actual = head;

    while(actual != nullptr){

        suma_peso = suma_peso + actual -> peso;
        cant_pacientes++;

        actual = actual -> next;

    }

    float peso_promedio = suma_peso/cant_pacientes;

    std::cout<<"Peso promedio del grupo: "<< peso_promedio <<"."<<std::endl;
    return peso_promedio;

}

//Función para determinar el peso promedio del grupo
void IMC(Paciente*head){
    
    // peso / altura^2

    Paciente* actual = head;

    while(actual != nullptr){

        float imc_paciente = actual -> peso / (actual-> altura * actual-> altura);

        std::cout<<"Paciente: " << actual -> nombre << "| IMC = " << imc_paciente << "." <<std::endl;
        
        actual = actual -> next;
    }

}


// Función para imprimir pacientes
void imprimirPaciente(const Paciente* head){
    const Paciente* actual = head;

    while(actual != nullptr){
        std::cout<<"**Paciente actual:"<<std::endl;

        std::cout<<"Nombre: " << actual -> nombre <<std::endl;
        std::cout<<"Edad: "<< actual -> edad <<std::endl;
        std::cout<<"Peso: "<< actual -> peso <<std::endl;
        std::cout<<"Altura: "<< actual -> altura <<std::endl;
        std::cout<<""<<std::endl;
        actual = actual->next;
    }
}


int main(){

    Paciente* head = nullptr;

    // Agregar pacientes
    agregarPaciente(head, "Ian", 15, 60, 1.71);
    agregarPaciente(head, "Gabriela", 25, 65, 1.70);
    agregarPaciente(head, "Florencio", 50, 77, 1.85);


    std::cout<<""<<std::endl;
    std::cout<<"Imprimir lista de pacientes ----pan-----"<<std::endl;
    imprimirPaciente(head);

    edadPromedio(head);
    pesoPromedio(head);

    std::cout<<""<<std::endl;

    IMC(head);

    return 0;
}