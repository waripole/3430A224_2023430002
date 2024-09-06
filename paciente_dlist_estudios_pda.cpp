#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <fstream>

// Definir estructura paciente
struct Paciente {
    std::string nombre;
    int edad;
    float altura;
    int peso;
    float ac1;
    float imc;
    float puntaje;
    Paciente* next; // puntero para la siguiente persona

};

// Función para agregar pacientes a la lista
void agregarPaciente(Paciente*& head, const std::string& nombre, int edad, float altura, float peso, float ac1){
    
    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente -> nombre = nombre;
    nuevoPaciente -> edad = edad;
    nuevoPaciente -> altura = altura;   
    nuevoPaciente -> peso = peso;
    nuevoPaciente -> ac1 = ac1;
    //nuevoPaciente -> imc = imc;
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
        std::cout<<"Altura: "<< actual -> altura << " m." <<std::endl;        
        std::cout<<"Peso: "<< actual -> peso << " kg." <<std::endl;
        std::cout<<"AC1: " << actual -> ac1 << "%."<<std::endl;
        std::cout<<"IMC: " << actual -> imc << "." << std::endl;
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

// Función para determinar el peso promedio del grupo
void IMC(Paciente*head){
    // peso / altura^2
    Paciente* actual = head;
    while(actual != nullptr){
        float imc_paciente = actual -> peso / (actual-> altura * actual-> altura);
        // Agregar IMC del paciente calculado     
        actual -> imc = imc_paciente;
        actual = actual -> next;
    }
}

// Función para obtener los datos del archivo cvs
// No se toma en cuenta aquellas personas con un AC1 normal,
// pues no serían de interés para los diabetólogos
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
        std::string ac1_cvs;
        getline(ss, nombre, ',');
        getline(ss, edad_cvs, ',');
        getline(ss, altura_cvs, ',');        
        getline(ss, peso_cvs, ',');
        getline(ss, ac1_cvs, ',');
        //Corregir el tipo de dato (int/float)
        int edad = stoi(edad_cvs);
        float altura = stof(altura_cvs);        
        int peso = stoi(peso_cvs);
        float ac1 = stof(ac1_cvs);
        // Si su ac1 es menor a 5.7 no se agrega pues está dentro de los 
        //niveles normales y no es de interés para los diabetólogos
        if(ac1 >= 5.7){
            // Agregar paciente de la linea a la lista
            agregarPaciente(head, nombre, edad, altura, peso, ac1);            
        }
    }
    archivo.close();
}

// Función para imrprimir aquellos pacientes con 5,7 < A1C% < 6.5
void imprimirPacientesPREdiabetes(Paciente* head){
    // Recorrer la lista creada con el cvs
    Paciente* actual = head;
    while(actual != nullptr){
        float i = actual -> ac1;
        // Identificar aquellos con un 5,7 < A1C < 6.5%
        if(5,7 < i < 6,5 ){
            std::cout<<"Paciente: " << actual -> nombre << "| AC1: " << actual -> ac1 << " - Pre-diabetes.\n" <<std::endl;
        }
        actual = actual -> next;
    }
}


// Función para imrprimir aquellos pacientes con A1c > 6.5%
void imprimirPacientesDiabetes(Paciente* head){
    // Recorrer la lista creada con el cvs
    Paciente* actual = head;
    while(actual != nullptr){
        float i = actual -> ac1;
        // Identificar aquellos con un A1C > 6.5%
        if(i > 6.5){
            std::cout<<"Paciente: " << actual -> nombre << "| AC1: " << actual -> ac1 << " - Diabetes.\n" <<std::endl;
        }
        actual = actual -> next;
    }
}


// Función para imrprimir aquellos pacientes con 15 < IMC < 29.9
void imprimirPacientesSobrepeso(Paciente* head){
    // Recorrer la lista creada con el cvs
    Paciente* actual = head;
    while(actual != nullptr){
        float i = actual -> imc;
        // Identificar aquellos con un 15 < IMC < 29.9
        if(18.5 < i < 24.9){
            std::cout<<"Paciente: " << actual -> nombre << "| IMC: " << actual -> imc << " - Sobrepeso.\n" <<std::endl;
        }
        actual = actual -> next;
    }
}

// Función para imrprimir aquellos pacientes con IMC > 30
void imprimirPacientesObesidad(Paciente* head){
    // Recorrer la lista creada con el cvs
    Paciente* actual = head;
    while(actual != nullptr){
        float i = actual -> imc;
        // Identificar aquellos con un IMC > 30
        if(i > 30){
            std::cout<<"Paciente: " << actual -> nombre << "| IMC: " << actual -> imc << " - Obesidad.\n" <<std::endl;
        }
        actual = actual -> next;
    }
}

// Función para encolar pacientes
void encolar(Paciente*& head, Paciente* novoPaciente){
    if(head == nullptr){
        head = novoPaciente;
    } else{
        Paciente* actual = head;
        while(actual -> next != nullptr){    
            actual = actual -> next;
        }
        actual -> next = novoPaciente;
    }
}

// Función para des-encolar pacientes
Paciente* desencolar(Paciente*& head){
    if(head==nullptr){
        return nullptr;
    }
    Paciente* eliminado = head;
    head = head -> next;
    return eliminado;
}

// Función para imprimir la cola
void imprimirCola(Paciente* head){
    Paciente* actual = head;
    int i = 1;
    while(actual != nullptr){
        std::cout<< i << ". Nombre: "<< actual -> nombre << " | Puntaje: "<< actual -> puntaje << ".\n" <<std::endl;
        i++;
        actual = actual -> next;
    }
}

/* Los puntajes son calculados, principalmente, en base a el nivel de AC1.
En general, el punteje equivale al IMC multiplicado por el nivel de AC1 y luego
sumado a la edad. Pero, debido a que se le quiere dar mayor importancia a el nivel
de AC1 debido a su indicador en la diabetes, aquellos que tengan AC1 mayor, su puntaje
será multiplicado por un valor mayor obteniendo así un puntaje para su atención
enfocado en el nivel de AC1.
*/
void calcularPuntajes(Paciente* head){
    // Que se pueda definir el largo de la lista
    std::cout<<"-- Se han calculado los puntajes --"<<std::endl;
    //hacer lo de priorizar blabla en torno al IMC y al AC1 y probablemente edad
    Paciente* actual = head;

    // Calcular especie de puntaje para luego determinar el orden de la cola
    while(actual != nullptr){
        float imc_ptj = actual -> imc;
        float ac1_ptj = actual -> ac1;
        int edad_ptj = actual -> edad;
        // imc * ac1 + edad
        float puntaje_cola = 0;
        if(actual -> ac1 < 5.7){
            puntaje_cola = (imc_ptj * ac1_ptj) + edad_ptj;  
        }else if(actual -> ac1 >= 5.7 && actual -> ac1 < 6.5){
            puntaje_cola = ((imc_ptj * ac1_ptj) + edad_ptj) * 3;
        }else if(actual-> ac1 > 6.5){
            puntaje_cola = ((imc_ptj * ac1_ptj) + edad_ptj) * 5;
        }
        std::cout<<"Nombre: "<<actual -> nombre << " | Puntaje: " << puntaje_cola << "\n." <<std::endl;
        actual -> puntaje = puntaje_cola;
        actual = actual -> next;
    }
}

// Copiar la lista de pacientes para ordenarlos e ir modificando esta para la cola
Paciente* copiarListaa(Paciente* head){
    if(head == nullptr){
        return nullptr;
    }
    Paciente* nuevoHead = nullptr;
    Paciente* actualOriginal = head;
    Paciente* actualNuevo = nullptr;
    while(actualOriginal != nullptr){
        // Copiar el nodo
        Paciente* novoPaciente = new Paciente(*actualOriginal); 
        novoPaciente -> next = nullptr;
        if(nuevoHead == nullptr){
            nuevoHead = novoPaciente;
            actualNuevo = novoPaciente;
        } else{
            actualNuevo -> next = novoPaciente;
            actualNuevo = novoPaciente;
        }
        // Ir copiando cada paciente
        actualOriginal = actualOriginal -> next;    
    }
    return nuevoHead;
}

// Función que devuelve el paciente con mayor puntaje
Paciente* puntajeMayor(Paciente*& head){
    if(head == nullptr){
        return nullptr;
    }
    // Valores iniciales de los pacientes
    Paciente* mayor = head;
    Paciente* actual = head;
    Paciente* anteriorMayor = nullptr;
    Paciente* anteriorNormal = nullptr;
    // Recorrer la lista
    while(actual != nullptr){
        if(actual -> puntaje > mayor -> puntaje){
            mayor = actual;
            anteriorMayor = anteriorNormal;
        }
        anteriorNormal = actual;
        actual = actual -> next;
    }
    if(anteriorMayor != nullptr){
        anteriorMayor -> next = mayor -> next;
    } else{
        head = mayor -> next;
    }
    mayor -> next = nullptr;
    return mayor;    
}


void ordenarPuntajes(Paciente* headOriginal){
    // Se trabaja con una copia de la lista para facilitar la manipulación de los datos
    Paciente* headCopia = copiarListaa(headOriginal);
    Paciente* nuevoHead = nullptr;
    Paciente* mayor;
    while(headCopia != nullptr){
        mayor = puntajeMayor(headCopia);
        // Se encola al que tiene mayor puntaje de los pacientes ingresados
        encolar(nuevoHead, mayor);
    }
    headOriginal = nuevoHead;
    std::cout<<"Cola de prioridad pacientes ------------" <<std::endl;
    imprimirCola(nuevoHead);
    while(nuevoHead != nullptr){
        Paciente* temp = nuevoHead;
        nuevoHead = nuevoHead -> next;
        delete temp;
    }
}

// Función para determinar la cantidad de pacientes en la cola
int longitudCola(Paciente* head){
    int longitud = 0;
    Paciente* actual = head;
    while(actual != nullptr){
        longitud ++;
        actual = actual -> next;
    }
    return longitud;
}

// Función para vaciar la cola
void vaciarCola(Paciente*& head){
    Paciente* actual = head;
    while(actual != nullptr){
        Paciente* temp = actual;
        actual = actual ->next;
        delete temp;
    }
    head = nullptr;
}


int main(){

    Paciente* head = nullptr;
    int eleccion;
    leerArchivoCVS("patient_list.csv", head);
    IMC(head);
    calcularPuntajes(head);

    while(true){
        std::cout<<"Elige una opcion: \n"<<std::endl;
        std::cout<<"1. Agregar paciente \n"<<std::endl;
        std::cout<<"2. Eliminar paciente \n"<<std::endl;            
        std::cout<<"3. Imprimir lista de pacientes \n"<<std::endl;
        std::cout<<"4. Calcular IMC pacientes\n"<<std::endl;
        std::cout<<"5. Calcular EDAD promedio pacientes \n"<<std::endl;
        std::cout<<"6. Calcular PESO promedio pacientes \n"<<std::endl;
        std::cout<<"7. Leer datos archivo CVS \n"<<std::endl;
        std::cout<<"8. Calcular puntajes de prioridad \n"<<std::endl;
        std::cout<<"9. Imprimir pacientes con PREdiabetes \n"<<std::endl;   
        std::cout<<"10. Imprimir pacientes con diabetes \n"<<std::endl;
        std::cout<<"11. Imprimir pacientes con sobrepeso \n"<<std::endl;
        std::cout<<"12. Imprimir pacientes con obesidad \n"<<std::endl;
        std::cout<<"[13] Imprimir cola de prioridad\n"<<std::endl;
        std::cout<<"14. Vaciar cola de prioridad \n"<<std::endl;
        std::cout<<"15. Salir \n"<<std::endl;

        std::cin>> eleccion;
        switch(eleccion){
            case 1:{
                std::string nombre;
                int edad;
                float altura;                
                int peso;
                float ac1;
                std::cout <<"Ingresar nombre: ";
                std::cin >> nombre;
                std::cout <<"Ingresar edad: ";
                std::cin >> edad;
                std::cout <<"Ingresar altura: ";
                std::cin >> altura;
                std::cout <<"Ingresar peso: ";
                std::cin >> peso;
                std::cout << "Ingresar AC1: ";
                std::cin >> ac1;
                agregarPaciente(head, nombre, edad, altura, peso, ac1);
                IMC(head);
                calcularPuntajes(head);
                break;
            }
            case 2:{
                std::string nombre;
                std::cout <<"Ingresar nombre: ";
                std::cin >> nombre;
                eliminarPaciente(head, nombre);
                break;
            }
            case 3:{
                std::cout<<"Lista pacientes --------------"<<std::endl;
                imprimirPaciente(head);
                break;
            }
            case 4:{
                IMC(head);
                Paciente* actual = head;
                while(actual != nullptr){
                    std::cout<<"Paciente: " << actual -> nombre << "| IMC = " << actual -> imc << "." <<std::endl;
                    actual = actual -> next;
                }
                break;
            }
            case 5:{
                edadPromedio(head);
                break;
            }
            case 6:{
                pesoPromedio(head);
                break;
            }
            case 7:{
                leerArchivoCVS("patient_list.csv", head);
                IMC(head);
                break;
            }
            case 8:{
                calcularPuntajes(head);
                break;
            }
            case 9:{
                imprimirPacientesPREdiabetes(head);
                break;
            }
            case 10:{
                imprimirPacientesDiabetes(head);
                break;
            }
            case 11:{
                imprimirPacientesSobrepeso(head);
                break;
            }
            case 12:{
                imprimirPacientesObesidad(head);
                break;
            }
            case 13:{
                imprimirCola(head);
                break;
            }
            case 14:{
                vaciarCola(head);
                break;
            }
            case 15:{
                while(head != nullptr){
                    Paciente* temp = head;
                    head = head -> next;
                    delete temp;
                }
                return 0;
            }
            default:{
            std::cout << "Eleccion invalida. Ingrese otra opción.";
            }
        }
    }
}