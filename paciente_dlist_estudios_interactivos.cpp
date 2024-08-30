// 5 menú interactivo

//git status

//git branch /ver todas las ramas
//git checkout -b laboratorio1 main /crear rama
//git checkout /cambiarse de rama

#include <iostream>
#include <string>

//importar librerias para leer e archivo cvs
#include <sstream>
#include <fstream>


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


// Función para imprimir pacientes
void imprimirPaciente(const Paciente* head){
    const Paciente* actual = head;

    while(actual != nullptr){
        std::cout<<"Paciente actual:"<<std::endl;

        std::cout<<"Nombre: " << actual -> nombre << "." <<std::endl;
        std::cout<<"Edad: "<< actual -> edad << " año/s." <<std::endl;
        std::cout<<"Peso: "<< actual -> peso << " kg." <<std::endl;
        std::cout<<"Altura: "<< actual -> altura << " m." <<std::endl;
        std::cout<<""<<std::endl;
        actual = actual->next;
    }
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

    std::cout<<"[Edad promedio del grupo: "<< promedio_edad << ".\n]" <<std::endl;
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

    std::cout<<"[Peso promedio del grupo: "<< peso_promedio <<".\n]"<<std::endl;
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


void leerArchivoCVS(const std::string& nombreArchivo, Paciente*& head){

    std::ifstream archivo(nombreArchivo);
    std::string linea;

    // Ignorar primera linea del cvs
    getline(archivo, linea);

    // Leer c/u linea del CVS
    while(getline(archivo, linea)){

        std::stringstream ss(linea);
        
        std::string nombre;
        std::string edad_cvs;
        std::string peso_cvs;
        std::string altura_cvs;
        
        getline(ss, nombre, ',');
        getline(ss, edad_cvs, ',');
        getline(ss, peso_cvs, ',');
        getline(ss, altura_cvs, ',');

        //Corregir el tipo de dato (int/float)
        int edad = stoi(edad_cvs);
        int peso = stoi(peso_cvs);
        float altura = stof(altura_cvs);

        // Agregar paciente de la linea a la lista
        agregarPaciente(head, nombre, edad, peso, altura);

    }

    archivo.close();

}



int main(){

    Paciente* head = nullptr;
    char eleccion;

    while(true){
        
        std::cout<<"Elige una opcion: \n"<<std::endl;
        std::cout<<"1. Agregar paciente \n"<<std::endl;
        std::cout<<"2. Eliminar paciente \n"<<std::endl;            
        std::cout<<"3. Imprimir lista de pacientes \n"<<std::endl;
        std::cout<<"4. Calcular IMC pacientes\n"<<std::endl;
        std::cout<<"5. Calcular EDAD promedio pacientes \n"<<std::endl;
        std::cout<<"6. Calcular PESO promedio pacientes \n"<<std::endl;
        std::cout<<"7. Leer datos archivo CVS \n"<<std::endl;
        std::cout<<"8. Salir \n"<<std::endl;

        std::cin>> eleccion;


        switch(eleccion){

            case '1':{

                std::string nombre;
                int edad;
                int peso;
                float altura;

                std::cout <<"Ingresar nombre: ";
                std::cin >> nombre;

                std::cout <<"Ingresar edad: ";
                std::cin >> edad;

                std::cout <<"Ingresar peso: ";
                std::cin >> peso;

                std::cout <<"Ingresar altura: ";
                std::cin >> altura;

                agregarPaciente(head, nombre, edad, peso, altura);

                break;

            }

            case '2':{
                
                std::string nombre;

                std::cout <<"Ingresar nombre: ";
                std::cin >> nombre;

                eliminarPaciente(head, nombre);

                break;

            }

            case '3':{
                std::cout<<"Lista pacientes --------------"<<std::endl;
                imprimirPaciente(head);
                
                break;
            }

            case '4':{

                IMC(head);

                break;

            }

            case '5':{
                
                edadPromedio(head);

                break;

            }

            case '6':{

                pesoPromedio(head);

                break;
            }

            case '7':{

                leerArchivoCVS("datos.csv", head);

                break;
            }

            case '8':{

                while(head != nullptr){

                    Paciente* temp = head;
                    head = head -> next;

                    delete temp;

                }

                return 0;

            }

            default:
            std::cout << "Eleccion invalida. Ingrese otra opción.";
            
        }


    }

}
