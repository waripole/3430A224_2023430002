#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node* root = nullptr;

    // Metodo recursivo privado para insertar un nodo en el arbol binario de busqueda
    Node* insertNode(Node* node, int data) {
        if (node == nullptr) {
            // Crear un nuevo nodo si se encuentra una posicion vacia
            return createNode(data);
        }

        if (data < node->info) {
            // Insertar en el subarbol izquierdo
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            // Insertar en el subarbol derecho
            node->right = insertNode(node->right, data);
        } else {
            // El dato ya esta en el arbol
            std::cout << "El nodo ya se encuentra en el árbol: " << data << std::endl;
        }

        return node;
    }

    // Metodo recursivo privado para imprimir el arbol en pre-orden
    void printPreOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        cout << node->info << " "; // Imprimir el dato del nodo actual
        printPreOrder(node->left);  // Recorrer el subarbol izquierdo
        printPreOrder(node->right); // Recorrer el subarbol derecho
    }

    // Metodo recursivo privado para imprimir el arbol en in-orden
    void printInOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);  // Recorrer el subarbol izquierdo
        cout << node->info << " "; // Imprimir el dato del nodo actual        
        printInOrder(node->right); // Recorrer el subarbol derecho
    }

    // Metodo recursivo privado para imprimir el arbol en post-orden
    void printPostOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printPostOrder(node->left);  // Recorrer el subarbol izquierdo
        printPostOrder(node->right); // Recorrer el subarbol derecho
        cout << node->info << " "; // Imprimir el dato del nodo actual        
    }

    /*
    Para la funciòn buscar y modificar:
        1- recorrer el grafo
        2- verificar si el nodo corresponde al nodo ingresado a modificar
        3- eliminarlo
        4- agregar el nuevo valor
    */


    // nodo màss pequeño
    Node* nodoPetit(Node* node) {
        Node* actual = node;
        while (actual && actual->left != nullptr) {
            actual = actual->left;
        }
        return actual;
    }


    Node* eliminarNodo(Node* node, int data){
        if(node == nullptr){
            return node;
        }

        if(data<node->info){
            node->left = eliminarNodo(node->left, data);
        } else if(data > node->info){
            node->right = eliminarNodo(node->right, data);
        } else{
            // nodo encontrado
            if(node->left == nullptr){
                Node* temp = node->right;
                delete node;
                return temp;
            } else if(node->right ==nullptr){
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = nodoPetit(node->right);
            node->info = temp -> info;
            node->right = eliminarNodo(node->right, temp->info);
        }
        return node;
    }



public:
    Arbol() : root(nullptr) {}

    // Metodo publico para insertar un nodo en el arbol
    void insert(int data) {
        root = insertNode(root, data);
    }

    void eliminar(int data){
        root = eliminarNodo(root, data);
    }

    // Metodo publico para imprimir el arbol en preorden
    void printPreOrder() const {
        std::cout<<"Pre-order:"<<std::endl;
        printPreOrder(root);
        std::cout<<"\n"<<std::endl;
        cout << endl;
    }

    // Metodo publico para imprimir el arbol en post-orden
    void printInOrder() const {
        std::cout<<"In-order:"<<std::endl;
        printInOrder(root);
        std::cout<<"\n"<<std::endl;
        cout << endl;
    }

    // Metodo publico para imprimir el arbol en post-orden
    void printPostOrder() const {
        std::cout<<"Post-order:"<<std::endl;  
        printPostOrder(root);
        std::cout<<"\n"<<std::endl;
        cout << endl;
    }


    void modificarNodo(int nodoEliminar, int nodoInsertar){
        eliminar(nodoEliminar);
        insert(nodoInsertar);
    }

// -----------------------------------------------------

    // Constructor de la clase Àrbol
    Arbol(Node* node) : root(node) {}

    // Recorrer el arbol en preorden y escribir en el archivo
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << node->info << "->" << node->left->info << ";" << endl;
            } else {
                //string cadena = node->info + "i";
                string cadena = "null_" + to_string(node->info) + "i";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                //string cadena = node->info + "d";
                string cadena = "null_" + to_string(node->info) + "d";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }

    // Generar y mostrar la visualizacion del arbol
    void visualize() {
        ofstream fp("grafo.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo grafo.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=green];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;

        fp.close();

        // Generar y mostrar la imagen del arbol
        system("dot -Tpng -o grafo.png grafo.txt");
        system("eog grafo.png");
    }

// -----------------------------------------------------
};

int main() {
    Arbol arbol;

    int eleccion;

    while(true){
        std::cout<<"Insertar elementos                       [1]\n"<<std::endl;
        std::cout<<"Eliminar elemento 65                     [2]\n"<<std::endl;
        std::cout<<"Modificar elemneto 52                    [3]\n"<<std::endl;
        std::cout<<"Mostrar contenido Pre / In / Post order  [4]\n"<<std::endl;
        std::cout<<"Generar grafo (Linux)                    [5]\n"<<std::endl;
        std::cout<<"Salir                                    [0]\n"<<std::endl;
        std::cout<<"--------------------------------------------\n"<<std::endl;

        //manejo errores de la elecciòn !!!!
        std::cin>>eleccion;


        if (cin.fail()) {
            // limpìar las banderas de error
            cin.clear();

            // ignorar el resto de la entreada no valida
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            std::cout << "Eleccion invalida. Porfavor ingrese un numero entero.\n"<<std::endl;
        }
        else {

            if(eleccion >= 0 && eleccion <=5){
                switch (eleccion)
                {
                case 0:{
                    return 0;
                }
                case 1:{
                    std::cout<<"Opcion [1] - Insertar elementos \n"<<std::endl;
                    // Insertar numeros en el arbol usando el metodo insert
                    arbol.insert(120);
                    arbol.insert(87);
                    arbol.insert(140);
                    arbol.insert(43);
                    arbol.insert(99);
                    arbol.insert(130);
                    arbol.insert(22);
                    arbol.insert(65);
                    arbol.insert(93);
                    arbol.insert(135);
                    arbol.insert(56);
                    std::cout<<"\n"<<std::endl;
                    break;
                }
                case 2:{
                    std::cout<<"Opcion [2] - Eliminar elemento\n"<<std::endl;
                    //arbol.eliminarNodo();
                    cout<<"nadi que se hace con el de modificar altiro";
                    std::cout<<"\n"<<std::endl;
                    break;
                }
                case 3:{
                    std::cout<<"Opcion [3] - Modificar elemento\n"<<std::endl;
                    arbol.modificarNodo(65,52);
                    std::cout<<"\n"<<std::endl;            
                    break;
                }
                case 4:{
                    std::cout<<"Opcion [4] - Mostrar contenido \n"<<std::endl;
                    arbol.printPreOrder();
                    arbol.printInOrder();            
                    arbol.printPostOrder();
                    std::cout<<"\n"<<std::endl;
                    break;            
                }
                case 5:{
                    std::cout<<"Opcion [5] - Generar grafo \n"<<std::endl;
                    std::cout<<"\n"<<std::endl;
                    arbol.visualize();
                    break;    
                }
                default:
                    std::cout << "Eleccion invalida. Ingrese otra opción."<<std::endl;
                    std::cout<<"\n"<<std::endl;
                    break;
                }
            }

        } 
    }

    return 0;
}