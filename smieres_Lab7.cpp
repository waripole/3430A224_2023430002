#include <iostream>
#include <fstream>
#include <climits>


using namespace std;

struct Node {
    char info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(char data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

class Arbol {
private:
    Node* root = nullptr;

    // Método recursivo privado para insertar un nodo en el árbol binario de búsqueda
    Node* insertNode(Node* node, char data) {
        if (node == nullptr) {
            // Crear un nuevo nodo si se encuentra una posición vacía
            return createNode(data);
        }

        if (data < node->info) {
            // Insertar en el subárbol izquierdo
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            // Insertar en el subárbol derecho
            node->right = insertNode(node->right, data);
        } else {
            // El dato ya está en el árbol
            //std::cout << "El nodo ya se encuentra en el árbol: " << data << std::endl;
        }

        return node;
    }


    // Nodo más pequeño
    Node* nodoPetit(Node* node) {
        Node* actual = node;
        while (actual && actual->left != nullptr) {
            actual = actual->left;
        }
        return actual;
    }


public:
    Arbol() : root(nullptr) {}

    // Método público para insertar un nodo en el árbol
    void insert(char data) {
        root = insertNode(root, data);
    }



    // Método para recorrer el árbol y escribir en un archivo
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << node->info << "->" << node->left->info << ";" << endl;
            } else {
                string cadena = "null_" + to_string(node->info) + "i";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                string cadena = "null_" + to_string(node->info) + "d";
                fp << cadena << "[shape=point];" << endl;
                fp << node->info << "->" << cadena << ";" << endl;
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }

    // Generar y mostrar la visualización del árbol
    void visualize() {
        ofstream fp("grafo_2.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo grafo_2.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=green];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;

        fp.close();

        // Generar y mostrar la imagen del árbol
        system("dot -Tpng -o grafo_2.png grafo_2.txt");
        system("eog grafo_2.png");
    }
};



/*
Algoritmo de PRIM
	G -> gràfica G 
	N -> nª de vèrtices

	V -> conjunto de vèrtices de G
	U -> subconjunto de V, siendo su valor inicial el primer vèrtice
	L -> es la lista de aristas que se va formando con las aristas de menor costo que se van selecionando
		 L al inicio es vacìa


//---------------------------------------------------------------------------

// funciòn para elegir una arista (u,v) E A(G) tal que su costo sea mìnimo
// buscar un vèrtice que aùn no estè en el àrbol y del menor costo

int costo[] -> arreglo que contiene los costos mìnimos
bool U_nodos[] -> arreglo de bools que indica si un un vèrtice
				està en el àrbol de costo mìnimo o no


INT_MAX -> costo mìnimo actual
min_index -> ìndice del que tiene menor costo

V mayùscula -> nùmero total de nodos

*/


int costoMinimo(int costo[], bool U_nodos[], int V){
    // inicializar valores mìnimos
    int min = INT_MAX, min_index;

    for (int nodo_i = 0; nodo_i < V; nodo_i++){

        if (U_nodos[nodo_i] == false && costo[nodo_i] < min){
            min = costo[nodo_i], min_index = nodo_i;
        }
    }
    // devuelve el ìndice del ndo con el menor costo que aùn no està entre los recorridos
    return min_index;
}


// funciòn para imprimir el arbol construido a partir del grafo
// parent[]-> representar a què nodo està conectado c/u nodo_i
void imprimirConexiones(int parent[], int** graph, int V, Arbol& arbol){

	char letters[V];

	// Llenar el arreglo con letras de 'A' a 'F'
    for (int i = 0; i < V; ++i) {
        letters[i] = 'A' + i; // Asignar valores ASCII de 'A' a 'F'
        //letters[i] = 97 + i; // Asignar valores ASCII de 'a' a 'f'
        //letters[i] = 65 + i; // Asignar valores ASCII de 'A' a 'F'
    }

    std::cout<<"Conexiones entre los nodos: "<<std::endl;
    std::cout << "[Arista------Peso]\n"<<std::endl;

    //recorrer nodos
    for (int nodo_i = 1; nodo_i < V; nodo_i++){
		if(parent[nodo_i] != -1){
	    	//std::cout<<"hola print el arbolit"<<std::endl;
	    	//imrpimir la arista que conecta ambos nodos
	    	int peso = graph[nodo_i][parent[nodo_i]];
	        
	        //costo entre el nodo 'padre' y el nodo i
	        std::cout << letters[parent[nodo_i]]<< " - " << letters[nodo_i] <<std::endl;
	        //------------------------------------------------------
	        arbol.insert(letters[nodo_i]); // insertar el nodo en el árbol
        	arbol.insert(letters[parent[nodo_i]]); // insertar el padre de i
	        
	        //ok nome sirviò esto ok me rindo ok
	        if(peso > 0){
	        	
	        	std::cout<< graph[nodo_i][parent[nodo_i]] << " \n"<<std::endl;	        	
	        }
		}
    }
}

//------------------------------------------------------------------------------------

// PRIM 
void prim(int** graph, int V, Arbol& arbol){

	// arreglo para almacenar el arbol construido a partir del grafo y la implementaciòn del prim
    // almacena el ìndice del padre de cada nodo del novo arbol
    int* parent = new int[V];

    // valores para elegir la arista de menor peso
    // almacena el costo mìnimo para nicluir el vèrtice
    int* key = new int[V];

    // To represent set of vertices included in MST
    //bool mstSet[V];
    // almacena los valores de true / false segùn estè o no el nodo en el arbol (como que ya haya sido seleccionado/visitado)
    bool* mstSet = new bool[V];

    // Inicializar todo como sin conexiòn -> infinito
    for (int i = 0; i < V; i++){
        key[i] = INT_MAX;
        mstSet[i] = false; // al principio ningùn vèrtice està dentro del arbol (visitados)
    }

    // incluir el primer nodo en el arbol
    //costo 0 para que sea elegido el prmiero
    key[0] = 0;
  
    // primer nodo -> raiz del àrbol
    parent[0] = -1;
 

    // V -> nùmero de nodos/vèrtices
    for (int i = 0; i < V - 1; i++) {
        
    	//elegir la arista de costo mìnimo para incluirla (de los que no estèn)
        int u = costoMinimo(key, mstSet, V);

        // agregar el nodo seleccionado a los visitados (ya està en el àrbol)
        mstSet[u] = true;


        for (int v = 0; v < V; v++){

            // graph[u][v] != 0 -> para nodos adyacentes (unidos->)
            // mstSet[v] = false para los nodos q todavia no son agregados al arbol
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]){
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    //felis jalowin
    imprimirConexiones(parent, graph, V, arbol);
}
//------------------------------------------------------------------------------------

int main(){

	Arbol arbol; 

	// pedir al user el N de nodos
	int V = 0;
	int input_user;
	std::cout<<"Ingrese el numero de vertices/nodos (V): "<<std::endl;
	std::cin>>input_user;

	V = input_user;

	std::cout<<"numero de nodos user: "<<V<<std::endl;

	char letters[V];

	// Llenar el arreglo con letras de 'A' a 'F'
    for (int i = 0; i < V; ++i) {
        letters[i] = 'A' + i; // Asignar valores ASCII de 'A' a 'F'
        //letters[i] = 97 + i; // Asignar valores ASCII de 'a' a 'f'
        //letters[i] = 65 + i; // Asignar valores ASCII de 'A' a 'F'
    }

    // Imprimir los valores y sus correspondientes códigos ASCII
    std::cout << "Nodos:" << std::endl;
    for (int i = 0; i < V; ++i) {
        //std::cout << letters[i] << " : " << static_cast<int>(letters[i]) << std::endl;
        std::cout << letters[i] << std::endl;
    }

	//--------------------------------------
	
    int** matriz_ady = new int*[V];
    for (int i = 0; i < V; i++) {
        matriz_ady[i] = new int[V];
    }

	//int matriz_ady[V][V];

	std::cout<<"[Datos matriz]"<<std::endl;

	for(int i = 0; i < V; i++){

		for(int j = 0; j < V; j++){
			if(i == j){
				char input_matriz;
				std::cout<<"¿Existe conexion entre el nodo [" << letters[i] <<"] consigo mismo? [y/n]"<<std::endl;
				std::cin >> input_matriz;

				if(input_matriz == 'y'){
					int peso;
					std::cout<<"Ingrese conexiòn entre el mesmo: "<<std::endl;
					std::cin>> peso;

					matriz_ady[i][j] = peso;
				}else{
					//no tiene conexiòn consigomismo -> 0 
					matriz_ady[i][j] = 0;
				}
			}else{
				char input_matriz;
				std::cout<<"¿Existe conexion entre los nodos ["<< letters[i] <<"] y ["<< letters[j] <<"]? [y/n]"<<std::endl;
				std::cin>>input_matriz;

				if(input_matriz == 'y'){
					int peso;
					std::cout<<"Peso conexiòn entre los nodos ["<< letters[i] <<"] y ["<< letters[j] <<"]"<<std::endl;
					std::cin>> peso;
					matriz_ady[i][j] = peso;					
				}else{
					// no tienen conexiòn -> infinito -> -1
					matriz_ady[i][j] = -1;
				}
			}
		}
	}


	// imprimir matriz
	std::cout << std::endl;

	for (int fila=0; fila<V; fila++) {
		for (int col=0; col<V; col++) {
	      std::cout << matriz_ady[fila][col] << " ";
	    }
	    std::cout << std::endl;
	}


//----------------------------------------------------------------------grafo
	// crear el archivo de salida
	std::ofstream fp("grafo.txt");

	// manejo errores
	if (!fp.is_open()) {
		std::cerr << "Error al abrir el archivo para escribir el grafo.\n";
		return 0;
	}

	// escribir el grafo en formato DOT
	fp << "digraph grafo {\n";
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (matriz_ady[i][j] > 0) {
			fp << letters[i] << " -> " << letters[j] << " [label=\"" << matriz_ady[i][j] << "\"];\n";
			}
		}
	}
	fp << "}\n";

	fp.close();
	std::cout << "\nArchivo 'grafo.txt' generado correctamente.\n";

	// crear imagen del grafo usando Graphviz
	system("dot -Tpng grafo.txt -o grafo.png");


	//------------------------------------------- implementaciòn del prim
	prim(matriz_ady, V, arbol);

	//d espues generar el arbol kfkdslfjdsk
	arbol.visualize();

	return 0;
}	