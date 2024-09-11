#include <iostream>
#include <string>

class Pila{
// Atributos privados por defecto, se deben pasar a públicos
public:
    int max;
    int tope;
    int* datos; // puntero para un array dinámico - array[max] datos;
    bool band;

    // Constructor
    Pila(int max){ //se incia con un valor máximo que es el que ingresará el usuario
        max = max;
        tope = 0;
        datos = new int[max];
        band = false; // band  = true -> pila llena / vacía
    }

    // BAND por referencia
    // int tope, bool &band
    void pilaVacia(){
        if(tope == 0){
            band = true; // band = true -> pila vacia
        } else{
            band = false;
        }
    }

    // BAND por referencia
    //int tope, int max, bool &band
    void pilaLlena(){
        if(tope == max){
            band = true; // band = true -> pila llena
        } else{
            band = false;
        }
    }    

    // PILA y TOPE por referencia
    void push(int dato){
        //tope, max, band
        pilaLlena();
        if(band){ // si band = true -> pila llena
            std::cout<<"Desbordamiento, pila llena"<<std::endl;
        } else{ // si no -> se agrega el dato encima de la pila
            datos[tope] = dato;
            tope++;
        }
    }

    // PILA y TOPE por referencia
    void pop(){
        // tope, band
        pilaVacia();
        if(band){
            std::cout<<"Subdesbordamiento, pila vacía"<<std::endl;
        } else{
            int dato = datos[--tope];
            std::cout<<"~ Elemento eliminado: " << dato <<std::endl;
        }
    }

    // Mostrar datos
    void imprimirPila(){
        // Iterar sobre los elementos de la pila
        for(int i = 0; i < tope; i++){
            // Imprimir cada dato
            std::cout<< datos[i] << "\n"<<std::endl;
        }
    }
};

int main(){
    int max;
    std::cout<<"Ingrese tamaño maximo de la pila: "<<std::endl;
    std::cin>> max;

    Pila pila(max);

    int eleccion;
    while(true){
        std::cout<<"Agregar / push  [1]\n"<<std::endl;
        std::cout<<"Remover / pop   [2]\n"<<std::endl;
        std::cout<<"Ver pila        [3]\n"<<std::endl;       
        std::cout<<"Salir           [0]\n"<<std::endl;
        std::cout<<"-------------------\n"<<std::endl;

        std::cin>>eleccion;
        switch (eleccion)
        {
        case 0:{
            return 0;
        }
        case 1:{
            std::cout<<"Opcion [1]\n"<<std::endl;
            while(true){
                std::cout<<"Ingrese valor: \n"<<std::endl;
                int valor;
                std::cin>> valor;
                pila.push(valor);
                pila.pilaLlena();
                if(pila.band){
                    break;
                }              
            }
            break;
        }
        case 2:{
            std::cout<<"Opcion [2]\n"<<std::endl;
            pila.pop();
            break;
        }
        case 3:{
            std::cout<<"Opcion [3]\n"<<std::endl;
            pila.imprimirPila();            
            break;
        }
        default:
            std::cout << "Eleccion invalida. Ingrese otra opción."<<std::endl;
            break;
        }
    }
}