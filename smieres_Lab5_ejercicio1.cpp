#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define TRUE 1
#define FALSE 0

enum {IZQUIERDO, DERECHO};

struct Nodo {
    int dato;
    int FE;
    Nodo* derecho;
    Nodo* izquierdo;
    Nodo* padre;
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

/* Insertar en arbol ordenado: */
void Insertar(Arbol* a, int dat);

/* Borrar un elemento: */
bool Borrar(Arbol* a, int dat);

/* Funcion de busqueda: */
bool Buscar(Arbol a, int dat);

//agregar el de Modificar
int Modificar(Arbol a, int dat);

/* Comprobar si es un nodo hoja: */
int EsHoja(pNodo r);

/* Contar numero de nodos: */
int NumeroNodos(Arbol a, int* c);

/* Calcular la altura de un arbol: */
int AlturaArbol(Arbol a, int* altura);

/* Calcular altura de un dato: */
int Altura(Arbol a, int dat);

/* Generar salida para Graphiz */
void PreOrden(Arbol, std::ofstream &fp);

// Funciones de equilibrado:
void Equilibrar(Arbol* raiz, pNodo nodo, int, int);
void RotaDerechaDerecha(Arbol* raiz, pNodo nodo);
void RotaIzquierdaIzquierda(Arbol* raiz, pNodo nodo);
void RotaDerechaIzquierda(Arbol* raiz, pNodo nodo);
void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo);

/* Funciones auxiliares: */
void Podar(Arbol* a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);

void MenuPrincipal();
void GenerarGrafo(Arbol);

int main() {
    Arbol ArbolInt = NULL;
    int opcion = 0;
    int valor;

    while (opcion != 6) {
        MenuPrincipal();
        std::cout << "Ingrese su opcion: \n";
        std::cin >> opcion;

        switch (opcion) {
            case 1:{
                std::cout << "Opcion [1] - Ingresar\n";
                Insertar(&ArbolInt, 60);
                Insertar(&ArbolInt, 40);
                Insertar(&ArbolInt, 90);
                Insertar(&ArbolInt, 45);
                Insertar(&ArbolInt, 75);
                Insertar(&ArbolInt, 97);
                Insertar(&ArbolInt, 68);

                break;                
            }
            case 2:{
                std::cout << "Opcion [2] - Buscar\n";
                int valor = 1;
                if(Buscar(ArbolInt, valor) == true){
                    std::cout<<"\nEl elemento ["<<valor<<"] se encuentra en el arbol.\n";
                }else{
                    std::cout<<"\nEl elemento ["<<valor<<"] NO se encuentra en el arbol.\n";
                }

                int valor2 = 75;
                if(Buscar(ArbolInt, valor2) == true){
                    std::cout<<"\nEl elemento ["<<valor2<<"] se encuentra en el arbol.\n";
                }else{
                    std::cout<<"\nEl elemento ["<<valor2<<"] NO se encuentra en el arbol.\n";
                }
                break;
            }
            case 3:{
                std::cout << "Opcion [3] - Borrar\n";
                //Nodo* nodo;
                //bool bo = false;
                int valor = 45;
                Borrar(&ArbolInt, valor);
                break;          
            }
            case 4:{
                std::cout << "Opcion [4] - Modificar\n";

                int valor = 68;
                int valor_add = 35;
                bool bo = false;
                //Modificar(&ArbolInt, valor1, valor2);
                //eliminar y agregar un elementos
                Borrar(&ArbolInt, valor);
                Insertar(&ArbolInt, valor_add);

                break;           
            }
            case 5:{
                std::cout << "Opcion [5] - Generar Grafo\n";
                GenerarGrafo(ArbolInt);
                break;                
            }
        }
    }

    /* Liberar memoria asociada al arbol. */
    Podar(&ArbolInt);
    return 0;
}

void GenerarGrafo(Arbol ArbolInt) {
    std::ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=green];\n";

    fp << "nullraiz [shape=point];\n";
    fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
    PreOrden(ArbolInt, fp);

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png &");
}

void MenuPrincipal() {
    std::cout << "\n";
    std::cout << "<1> Ingresar numero\n";
    std::cout << "<2> Busqueda numero\n";
    std::cout << "<3> Eliminar numero\n";
    std::cout << "<4> Modificar\n";
    std::cout << "<5> Generar Grafo\n";
    std::cout << "<6> Salir\n";
    std::cout << "\n";
}

void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        free(*a);
        *a = NULL;
    }
}

void Insertar(Arbol* a, int dat) {
    pNodo padre = NULL;
    pNodo actual = *a;

    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }

    if (actual != NULL)
        return;

    if (padre == NULL) {
        *a = new Nodo{dat, 0, NULL, NULL, NULL};
    } else if (dat < padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->izquierdo = actual;
        Equilibrar(a, padre, IZQUIERDO, TRUE);
    } else if (dat > padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->derecho = actual;
        Equilibrar(a, padre, DERECHO, TRUE);
    }
}

//----------------------------------------------------


bool Buscar(Arbol node, int n){
    if(node ==nullptr){
        return false;
    }
    else if(node->dato==n){
        return true;
    }
    else if(n < node->dato){
        return Buscar(node->izquierdo,n); //menor - recorrer subarbol izq
    } else{
        return Buscar(node->derecho,n); //mayor - recorrer subarbol der
    }
}


bool Borrar(Arbol* a, int dat){
    pNodo padre = NULL;
    pNodo actual = *a;

    //1 si el nodo aactual no es nulo then...
    if(actual != NULL){
        //1.1 dato a borrar es menor al nodo actual
        if(dat < actual->dato){
            Borrar(&(actual->izquierdo), dat);

            //dato a borrar es mayor al nodo actual
        }else if(dat > actual->dato){
            Borrar(&(actual->derecho), dat);
        }else{
            //nodo pillado
            //si el nodo a borrar corresponde al nodo actual se elimina
            pNodo nodo_i = actual;

            //Si el nodo a eliminar NO tiene hijo DERecho, lo reemplaza el hijo IZQ
            if(nodo_i->derecho == NULL){
                pNodo temp = actual;
                *a = actual->izquierdo;

                //si no tiene hijo IZQ, lo reemplaza su hijo DERecho
            }else if(nodo_i->izquierdo == NULL){
                pNodo temp = actual;
                *a = actual->derecho;   
            }else{
                //si tiene hijos tanto en DER como IZQ, se busca el nodo más grande del subarbol IZQQ
                pNodo aux = actual->izquierdo;
                pNodo aux1;

                while(aux->derecho != NULL){
                    aux1 = aux;
                    aux = aux->derecho;
                };

                //se reemplaza el dato del nodo actual con el nodo reemplazante
                actual->dato = aux->dato;

                //ajustar los punteros
                if(aux1 == aux){
                    aux1->derecho = aux->izquierdo;
                }else{
                    aux1->izquierdo = aux->izquierdo;
                }

                Podar(&aux);

                return TRUE;
            }
        }
    }else{
        //si eele nodo actual es nulo, se imprime el mensaje de que el dato no se encuentraa en el arbol
        std::cout<<"La información no se encuentra en el arbol";
        return FALSE;
    }
    //retorna true si se eliminó el nodo correctamente
    return TRUE;
}



//----------------------------------------------------

void Equilibrar(Arbol* a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo){
            if (rama == IZQUIERDO){
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        }
        else{
            if (rama == IZQUIERDO){
                nodo->FE += 1;
            } 
            else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0)
            salir = TRUE;
        else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == 1)
                RotaIzquierdaDerecha(a, nodo);
            else
                RotaIzquierdaIzquierda(a, nodo);
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == -1)
                RotaDerechaIzquierda(a, nodo);
            else
                RotaDerechaDerecha(a, nodo);
            salir = TRUE;
        }

        if (nodo->padre) {
            if (nodo->padre->derecho == nodo) {
                rama = DERECHO;
            } else {
                rama = IZQUIERDO;
            }
        }
        nodo = nodo->padre;
    }
}

void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo R = Q->derecho;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        }
        else {
            Padre->izquierdo = R;
        }
    }
    else
        *raiz = R;

    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;

    switch (R->FE) {
        case -1: Q->FE = 0; P->FE = 1; break;
        case 0: Q->FE = 0; P->FE = 0; break;
        case 1: Q->FE = -1; P->FE = 0; break;
    }

    R->FE = 0;
}

void RotaDerechaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo R = Q->izquierdo;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        } else {
            Padre->izquierdo = R;
        }
    }
    else
        *a = R;

    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    switch (R->FE) {
        case -1: P->FE = 0; Q->FE = 1; break;
        case 0: P->FE = 0; Q->FE = 0; break;
        case 1: P->FE = -1; Q->FE = 0; break;
    }
    R->FE = 0;
}

void RotaIzquierdaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo B = Q->derecho;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->izquierdo = B;
    Q->derecho = P;

    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void RotaDerechaDerecha(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo B = Q->izquierdo;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->derecho = B;
    Q->izquierdo = P;

    P->padre = Q;
    
    if (B){
        B->padre = P;
    } 
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void PreOrden(Arbol a, std::ofstream &fp) {
    if (a) {
        //fp << a->dato << ";\n";
        fp << a->dato << " [label=\"" << a->dato <<"(FE: " << a->FE << ")\"];\n";

        //hijo hacia el lado izquierdo
        if (a->izquierdo) {
            fp << a->dato << "->" << a->izquierdo->dato << ";\n";
            PreOrden(a->izquierdo, fp);
        }
        //hijo hacia el lado derecho
        if (a->derecho) {
            fp << a->dato << "->" << a->derecho->dato << ";\n";
            PreOrden(a->derecho, fp);
        }
    }
}