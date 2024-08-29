// 3
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
        std::cout<<"**Paciente actual:"<<std::endl;

        std::cout<<"Nombre: " << actual -> nombre <<std::endl;
        std::cout<<"Edad: "<< actual -> edad <<std::endl;
        std::cout<<"Peso: "<< actual -> peso <<std::endl;
        std::cout<<"Altura: "<< actual -> altura <<std::endl;
        std::cout<<""<<std::endl;
        actual = actual->next;
    }
}

// Función para eliminar paciente
void eliminarPaciente(Paciente*& head, const std::string& nombre){

    Paciente* actual = head;
    Paciente* anterior = nullptr;

    while(actual != nullptr && actual->nombre != nombre){
        anterior = actual;
        actual = actual ->next;
    }

    if(actual != nullptr){
        
        if(anterior == nullptr){
            head = actual->next;
        } else{
            anterior->next = actual->next;
        }

        delete actual;
    }
}

int main(){

    Paciente* head = nullptr;

    // Agregar pacientes
    agregarPaciente(head, "Ian", 15, 60, 1.71);
    agregarPaciente(head, "Gabriela", 25, 65, 1.70);
    agregarPaciente(head, "Florencio", 50, 77, 1.85);


    std::cout<<""<<std::endl;
    std::cout<<"Imprimir lista de pacientes ---------"<<std::endl;
    imprimirPaciente(head);

    std::cout<<""<<std::endl;
    std::cout<<"Accion de eliminar paciente ---------"<<std::endl;
    eliminarPaciente(head, "Florencio");

    imprimirPaciente(head);

    std::cout<<""<<std::endl;
    std::cout<<"Accion de agregar paciente"<<std::endl;
    agregarPaciente(head, "Fernanda", 20, 60, 1.72);

    imprimirPaciente(head);



    return 0;
}