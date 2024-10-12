#include <iostream>
#include <fstream>
#include <cstdlib>    // Para system()
#include <cstring>    // Para manejo de cadenas
#include <cmath> // para uso del floor()
#include <algorithm> //net

// los de manejo_arreglo
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
 
// hacer esste el del user
// número de nodos en el grafo
#define N 5  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// prototipos de las funciones
void leer_nodos(char vector[N]);
void inicializar_vector_D(int D[N], int M[N][N]);
void inicializar_vector_caracter(char vector[N]);
void aplicar_dijkstra(char V[N], char S[N], char VS[N], int D[N], int M[N][N]);
void actualizar_VS(char V[N], char S[N], char VS[N]);
int buscar_indice_caracter(char V[N], char caracter);
void agrega_vertice_a_S(char S[N], char vertice);
int elegir_vertice(char VS[N], int D[N], char V[N]);
void actualizar_pesos(int D[N], char VS[N], int M[N][N], char V[N], char v);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_vector_caracter(char vector[N], const char *);
void imprimir_vector_entero(int vector[N]);
void imprimir_matriz(int matriz[N][N]);
void imprimir_grafo(int matriz[N][N], char vector[N]);

// si es entero o nour ->(https://www.delftstack.com/es/howto/cpp/check-if-input-is-integer-cpp/)
bool isNumber(const std::string& str) {
  return !str.empty() && std::find_if(str.begin(), str.end(), [](unsigned char c) {
    return !std::isdigit(c);
  }) == str.end();
}

int main() {

  int nodos_user;
  bool miau = true;

  while(true) {
    std::cout << "Ingrese el numero de nodos (>= 2 / INT):" << std::endl;
    std::string input_user;
    std::cin >> input_user;

    if(isNumber(input_user)) {
      // convertir a entero
      nodos_user = std::stoi(input_user);

      if(nodos_user >= 2) {
        std::cout << "[miau VALID]-> " << nodos_user << std::endl;
        break;
      }else {
        std::cout << "No papu...no es valido" << std::endl;
      }
    }else {
      std::cout << "Ingrese un numero valido" << std::endl;
    }
  }

  std::cout<<"miau nodos user -> "<< nodos_user <<std::endl;

  //---------------------------------

  int N = nodos_user;

  char V[N], S[N], VS[N];
  // V -> nodos
  // S -> nodos visitados
  // VS -> nodos que quedan sin visitar

  int D[N];
  // D -> distancias mìnimas desde el nodo inicial

  // Matriz de adyacencia representando los pesos entre nodos
  int M[N][N] = {{ 0, 4, 11, -1, -1},
                 {-1, 0, -1,  6,  2},
                 {-1 ,3,  0,  6, -1},
                 {-1,-1, -1,  0, -1},
                 {-1,-1,  5,  3,  0}};


  

  // se inicializan llos vectores char con valores vacìos
  inicializar_vector_caracter(V);
  inicializar_vector_caracter(S);
  inicializar_vector_caracter(VS);

  leer_nodos(V);

  aplicar_dijkstra(V, S, VS, D, M);

  imprimir_grafo(M, V);

  return 0;
}


// inicializar D con los valores de la primera fila de la matriz
// col -> como un contador o un 'i'
void inicializar_vector_D(int D[N], int M[N][N]) {
  for (int col = 0; col < N; col++) {
    D[col] = M[0][col];
  }
}

// inicializar un vector de char con espacios vacìos
void inicializar_vector_caracter(char vector[N]) {
  for (int col = 0; col < N; col++) {
    // vacios -> en blanco
    vector[col] = ' ';
  }
}

// Algoritmo de Dijkstra !!"!!"
void aplicar_dijkstra(char V[N], char S[N], char VS[N], int D[N], int M[N][N]) {
  // inicializar el vector de las distancias mìnimas
  inicializar_vector_D(D, M);


  std::cout << "--------- Estados iniciales ---------\n";
  imprimir_matriz(M);
  imprimir_vector_caracter(S, "S");
  imprimir_vector_caracter(VS, "VS");
  imprimir_vector_entero(D);
  std::cout << "-------------------------------------\n\n";

  // se agrega un primer nodo al conjunto de nodos visitados (S)
  agrega_vertice_a_S(S, V[0]);
  actualizar_VS(V, S, VS);

  imprimir_vector_caracter(S, "S");
  imprimir_vector_caracter(VS, "VS");
  imprimir_vector_entero(D);

  // iteración principal del algoritmo (agrega nodos y actualiza pesos)
  for (int i = 1; i < N; i++) {
    // elegir next-> vèrtice con la distancia mìnima
    std::cout << "> Elegir vértice menor en VS[]\n";
    int v = elegir_vertice(VS, D, V);

    // agregar vèrtice a conjunto S (nodos visitados) y actualizar VS (nodos que quedan sin visitar)
    agrega_vertice_a_S(S, v);
    actualizar_VS(V, S, VS);

    imprimir_vector_caracter(S, "S");
    imprimir_vector_caracter(VS, "VS");

    // actualizar pesos en el vector D de las distancias
    actualizar_pesos(D, VS, M, V, v);
    imprimir_vector_entero(D);
  }
}

// actualizar VS (nodos que faltan por visitar) adoc a los nodos agregados en S (nodos visitados)
void actualizar_VS(char V[N], char S[N], char VS[N]) {
  // inicializar VS como vacìo
  inicializar_vector_caracter(VS);
  int k = 0;
  for (int j = 0; j < N; j++) {
    // si un vèrtice NO està en S (nodos visitados) -> se agrega a VS (nodos por visitar)
    if (std::strchr(S, V[j]) == nullptr) {
      VS[k++] = V[j];
    }
  }
}

// agregar vertice a S (nodos por visitar)
void agrega_vertice_a_S(char S[N], char vertice) {
  for (int i = 0; i < N; i++) {
    if (S[i] == ' ') {
      S[i] = vertice;
      return;
    }
  }
}

// elegir el vèrtice de menor peso en el vector D de distancias
int elegir_vertice(char VS[N], int D[N], char V[N]) {
  int menor = -1, vertice = 0;
  for (int i = 0; i < N; i++) {
    int indice = buscar_indice_caracter(V, VS[i]);
    if (D[indice] != -1 && (menor == -1 || D[indice] < menor)) {
      menor = D[indice];
      vertice = VS[i];
    }
  }
  std::cout << "\nVértice elegido: " << vertice << "\n\n";
  return vertice;
}

// Actualiza los pesos de los nodos restantes según el vértice agregado
void actualizar_pesos(int D[N], char VS[N], int M[N][N], char V[N], char v) {
    int indice_v = buscar_indice_caracter(V, v);
    for (int i = 0; i < N; i++) {
        if (VS[i] != ' ') {
          int indice_w = buscar_indice_caracter(V, VS[i]);
          D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
        }
    }
}

// calcular mìnimos entre las distancias actuales
int calcular_minimo(int dw, int dv, int mvw) {
  if (dw == -1) {
    return (dv != -1 && mvw != -1) ? dv + mvw : -1;
  }else {
    return (dv != -1 && mvw != -1 && dw > dv + mvw) ? dv + mvw : dw;
  }
}

// buscar ìndice de un char en el vector V (nodos)
int buscar_indice_caracter(char V[N], char caracter) {
  for (int i = 0; i < N; i++) {
    if (V[i] == caracter) return i;
  }
  return -1;  // Devuelve -1 si no lo encuentra
}

// imprimir vector de caracter
void imprimir_vector_caracter(char vector[N], const char *nomVector) {
  for (int i = 0; i < N; i++) {
    std::cout << nomVector << "[" << i << "]: " << vector[i] << " ";
  }
  std::cout << "\n";
}

// imprimir vector de int
void imprimir_vector_entero(int vector[N]) {
  for (int i = 0; i < N; i++) {
    std::cout << "D[" << i << "]: " << vector[i] << " ";
  }
  std::cout << "\n";
}

// lee datos de los nodos.
// inicializa utilizando código ASCII.
void leer_nodos (char vector[N]) {
  int i;
  int inicio = 97;
  
  for (i=0; i<N; i++) {
    vector[i] = inicio+i;
  }
}

// imprimir una matriz de adyacencia
void imprimir_matriz(int matriz[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << "matriz[" << i << "," << j << "]: " << matriz[i][j] << " ";
    }
    std::cout << "\n";
  }
}

// Imprime un grafo en un archivo en formato DOT y generar una imagen
void imprimir_grafo(int matriz[N][N], char vector[N]) {
  // crear el archivo de salida
  std::ofstream fp("grafo.txt");

  // manejo errores
  if (!fp.is_open()) {
    std::cerr << "Error al abrir el archivo para escribir el grafo.\n";
    return;
  }

  // escribir el grafo en formato DOT
  fp << "digraph grafo {\n";
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (matriz[i][j] > 0) {
        fp << vector[i] << " -> " << vector[j] << " [label=\"" << matriz[i][j] << "\"];\n";
      }
    }
  }
  fp << "}\n";

  fp.close();
  std::cout << "\nArchivo 'grafo.txt' generado correctamente.\n";

  // crear imagen del grafo usando Graphviz
  system("dot -Tpng grafo.txt -o grafo.png");
}
