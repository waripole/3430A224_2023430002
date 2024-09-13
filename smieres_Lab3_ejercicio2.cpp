#include <iostream>
#include <string>

// Tres clases: Contenedor, Pila y Puerto

class Contenedor{
public:
    int numero;
    std::string empresa;

    // Constructor
    Contenedor(int numero, std::string empresa){
        this->numero = numero;
        this->empresa = empresa;
    }
};

class Pila{
public:
    int max;
    int tope;
    Contenedor** datos; // puntero para un array dinámico de punteros a contenedor
    bool band;

    // Constructor
    Pila(int max){ //se incia con un valor máximo que es el que ingresará el usuario
        this->max = max;
        tope = 0;
        datos = new Contenedor*[max];
        band = false; // band  = true -> pila llena / vacía
    }

    void pilaVacia(){
        if(tope == 0){
            band = true; // band = true -> pila vacia
        } else{
            band = false;
        }
    }

    void pilaLlena(){
        if(tope == max){
            band = true; // band = true -> pila llena
        } else{
            band = false;
        }
    }    

    void push(Contenedor contenedor){
        pilaLlena(); // chechar si la pila está llena antes de agregar
        if(band){ // si band = true -> pila llena
            std::cout<<"Desbordamiento, pila llena"<<std::endl;
        } else{ // si no -> se agrega el dato encima de la pila
            datos[tope] = new Contenedor(contenedor); //guardar el nuevo contenedor en el tope
            tope++; // aumentar el tope
        }
    }

    // Devuelve un elemento del tipo contenedor
    Contenedor pop(){
        pilaVacia();
        if(band){
            std::cout<<"Subdesbordamiento, pila vacía"<<std::endl;
            return Contenedor(-1,""); // Devuelve un contenedor inválido
        } else{
            tope--;            
            Contenedor contenedor = *datos[tope];
            delete datos[tope]; // free memoria
            return contenedor;
        }
    }

    // Mostrar datos
    void imprimisaonPila(){
        std::cout<<"("<<std::endl;
        for(int i = tope - 1; i>=0 ; i--) { // recorrer desde el tope hacia abajo para que se impriman coherentemente a la pila
            //std::cout<< datos[i]<<std::endl;
            std::cout << "Contenedor [" << datos[i]->numero << "] - Empresa: " << datos[i]->empresa << std::endl;
            if(tope != i+1){
                std::cout<<", "<<std::endl;
            }
        }
        std::cout<<")"<<std::endl;
    }
};

class Puerto{
public:
    int m; // número de pilas
    int n; // número de contenedores x pila
    Pila** pilas;

    // Constructor
    Puerto(int m, int n){
        this->m = m;
        this->n = n;
        pilas = new Pila*[m];
        // Iterar sobre cada pila
        for(int i = 0; i < m; i++){
            pilas[i] = new Pila(n); // Pila con "n" espacios pra contenedores
        }
    }

    void ingresoContenedor(Contenedor contenedor ){
        // recorrer todas las pilas para ver dd se puede guardar el contenedor
        for(int i = 0; i < m; i++){
            pilas[i] -> pilaLlena(); // Checar si la pila actual está vacíia
            
            //Checar si la pila no está llena
            if(!pilas[i]->band){ // si la pila NO esta llena (band = false)
                pilas[i]->push(contenedor);
                std::cout<<"Contendor: " << contenedor.numero << " | Empresa: " << contenedor.empresa <<" | Agregado a la pila ["<<i+1 <<"]\n"<<std::endl;
                return;
            }
        }
        std::cout<< "No hay espacio disponible en ninguna pila para agregar el contenedor: " << contenedor.numero <<" | "<< contenedor.empresa <<"\n"<<std::endl;
    }
    
/*1- iterar sobre cada pila hasta encontrar el contenedor a eliminar
    2- mover los contenedores superiores a otras pilas
        a- verificar si las pilas están llenas antes de agregar un contenedor
    3- eliminar el contenedor con pop()
    */
   void sacarContenedor(int numero){
        bool encontrado = false;
        
        // Recorrer las pilas (el puerto) para encontrar el contenedor
        for(int i = 0; i < m; i++){
            Pila* pila = pilas[i]; //puntero para la pila q se está revisando
            pila->pilaVacia(); // checar si la pila no está llena
            if(!pila->band){

                // Recorrer c/u pila de ARRIBA hacia abajo
                for(int j = pila->tope - 1; j >= 0; j--){
                    // verificar si el número del contendeor corresponde a la pila que se busca
                    if(pila->datos[j]->numero == numero){
                        encontrado = true;
                        
                        // mover los contenedores superiores a otras pilas
                        // temp para guardar los contenedores superiores pormientras
                        Contenedor** temp = new Contenedor*[pila->tope -j -1];
                        int topeTemp = 0;

                        // sacar los contenedores superiores
                        while(pila->tope - 1 > j){
                            temp[topeTemp++] = new Contenedor(pila->pop());
                        }

                        // eliminar el contendor requerrido
                        Contenedor contenedorSalida = pila->pop();
                        std::cout<<"Contenedor [" << numero << "] retirado de la pila []"<<i+1<<"]"<<std::endl;    

                        // volver a ingresar los contendores movidos a otras pilas
                        for(int k = 0; k < topeTemp; k++){
                            bool agregado = false;

                            // buscar una pila que no esté llena para agregar los cosos
                            // l = 1 para partir de la otra pila  y que el contenedor movido no se agrege a la misma
                            for(int l = 1; l < m; l++){
                                pilas[l]->pilaLlena();

                                if(!pilas[l]->band){
                                    pilas[l]->push(*temp[k]);
                                    std::cout<<"Contendor ["<< temp[k]->numero << "] movido a la pila [" << l+1<<"]"<<std::endl;
                                    agregado = true;
                                    break;
                                }
                            }

                            if(!agregado){
                                std::cout<<"No hay espacios para mover el contenedor ["<<temp[k]->numero<<"]\n"<<std::endl;
                            }
                            
                            delete temp[k];
                        } 

                        delete[] temp; //liberar memoria del array temporal
                        return;
                    }
                }
            }
        }

        if(!encontrado){
            std::cout<<"Contendor no encontrado en el puerto"<<std::endl;
        }

    }

    void imprimirPuerto(){
        for(int i = 0; i <m; i++){
            std::cout<<"Pila [" << i+1 << "]: "<<std::endl;
            //pilas[i]-> imprimirPila();
            pilas[i]-> imprimisaonPila();
        }
        std::cout<<"miau \n"<<std::endl;
    }
};

int main(){
    int m;
    int n;
    std::cout<<"Ingrese el numero de pilas (m): "<<std::endl;
    std::cin>> m;
    std::cout<<"Ingrese el numero de contenedores por pila (n): "<<std::endl;
    std::cin>> n;
    Puerto puerto(m, n);
    int eleccion;
    while(true){
        std::cout<<"Agregar contenedor  [1]\n"<<std::endl;
        std::cout<<"Remover contenedor  [2]\n"<<std::endl;
        std::cout<<"Ver ordenamiento    [3]\n"<<std::endl;       
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
            int numero;
            std::string empresa;
            std::cout<<"Ingrese numero del contenedor: \n"<<std::endl;
            std::cin>> numero;
            std::cout<<"Ingrese empresa del contenedor: \n"<<std::endl;
            std::cin>> empresa;
            puerto.ingresoContenedor(Contenedor(numero, empresa));            
            break;
        }
        case 2:{
            std::cout<<"Opcion [2]\n"<<std::endl;
            int numero;
            std::cout<<"Ingrese numero del contenedor a retirar: \n"<<std::endl;
            std::cin>> numero;
            puerto.sacarContenedor(numero);
            break;
        }
        case 3:{
            std::cout<<"Opcion [3]\n"<<std::endl;
            puerto.imprimirPuerto();           
            break;
        }
        default:
            std::cout << "Eleccion invalida. Ingrese otra opción."<<std::endl;
            break;
        }
    }
}