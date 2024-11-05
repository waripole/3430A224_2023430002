#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

void llenarArreglo(int* arr, int size) {
    // Llenar el arreglo con numeros aleatorios entre 1 y 1000
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000 + 1; // Genera un numero entre 1 y 1000
    }
}

void mostrarArreglo(int* arr, int size) {
    // Mostrar los valores del arreglo
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// para usar Hash habia que tener el arreglo ordenado
// intercambiar los valoress de dos variables int con punteros
void swap(int *xp, int *yp){
    int temp = *xp; // guardar el valor apuntado en una variables temporal
    *xp = *yp;		// asignar el valor apuntado por 'yp' al lugar apuntado por 'xp'
    *yp = temp;		// asignar el valor apuntado por 'temp' al lugar apuntado por 'yp's
}

//  Mètodo QuickSort-----------------------------------------

/*funciòn para partir el arreglo de elementos adoc al pivote, 
los elementos menores se van a la izquierda y los mayores a la derecha

low -> corresponde a la posiciòn 0
high -> corresponde a la ùltima posiciòn 
*/
int partir_arreglo (int arr[], int low, int high){
    
    int pivote = arr[high];
    int i = (low - 1); // -> esto marca la ùltima posiciòn en donde se puso un elemento menor o igual al pivote

    // recorrer el arreglo dessde la posiciòn 0 hasta 1 antes de la ùltima (pivote no se recorre)
    for (int j = low; j <= high -1; j++){

    	// si el elemento es menor o igual al pivote entonces...
        if (arr[j] <= pivote){

        	// incrementamos el valor de i
            i++;

            // intercambiamos las posiciones            
            // posiciòn que guardamos antes // posiciòn en la que vamos
            swap(&arr[i], &arr[j]);
        }
    }
    // todos los elementos hasta el arr[i] son menores o iguales al pivote
    // hacemos el cambio de lugar del pivote a una posiciòn luego de estos elementos menores o =
    swap(&arr[i + 1], &arr[high]);

    // se devuelve la posiciòn del pivote
    return (i + 1);
}

// se dividel el arreglo principal en subarreglos (valores menor y mayores al pivote) y se ordena c/u
void quickSort(int arr[], int low, int high){

    if (low < high){
    	// posiciòn del pivote
        int pivote = partir_arreglo(arr, low, high);

      	// ordenar el arreglo con los datos menores al pivote
        quickSort(arr, low, pivote - 1);

        // ordenar el arreglo con los datos mayores al pivote
        quickSort(arr, pivote + 1, high);
    }
}


// busca un lugar desocupado y lo ocupa XD
void pruebaLineal(int arr[], int SIZE, int claveHash){
	//recorrer el arreglo_claves_hash
	//buscar uno vacìo (= 0)
	//ubicar el colisionado ahì
	// (k mod N) + 1

	/*
	int clave_lineal = claveHash +1;

	for(int i = 0; i < SIZE; i++){
		if(arr[i] == 0){
			std::cout<<"Vuelta: "<< i << "// clave lienal-> " << clave_lineal<<std::endl;
			arr[i] = clave_lineal;

			std::cout<<"-> " << arr[i]<<std::endl;
			
			break;		
		}else{
			std::cout<<"lugar ocupao"<<std::endl;			
		}
		i++;
    }
	*/

	// usar la claveHash como ìndice
	int indice = claveHash;

	while(arr[indice] != 0){
		std::cout<<"lugar ocupao en: "<< indice <<std::endl;
		indice = (indice + 1) % SIZE;
	}

	arr[indice] = claveHash;
}

// implementaciòn de prueba cuadràtica
void pruebaCuadratica(int arr[], int SIZE, int claveHash){
	int i = 0;
	int indice = claveHash;

	while(arr[indice] != 0){
		std::cout<<"lugar ocupao en: "<< indice <<std::endl;
		i++;
		indice = (indice + i^2) % SIZE;
	}

	arr[indice] = claveHash;
}


void dobleHash(int arr[], int SIZE, int claveHash){
	//generar otra clave a partir de la ya claveHash


	int indice = claveHash % SIZE;

	//((claveHash mod Size) + 1 ------ -1 para no salirse del size
	int claveHash_ii = (claveHash % (SIZE-1)) + 1;

	while(arr[indice] != 0){
		std::cout<<"lugar ocupao en: "<< indice <<std::endl;

		indice = ((indice + claveHash_ii) % SIZE);
	}

	arr[indice] = claveHash;
}

void encadenamiento(){

}


// calcular hash con el mod
int hash(int k, int SIZE){
	//recorrer el arreglo y asignar un valor a c/u
	int claveHash = (k % SIZE);
	//std::cout<<"clave hash: "<< claveHash <<std::endl;
	return claveHash;
}

// buscar colisiones 
bool colision(int arr[], int SIZE){

	// inicializar falso para encontrar colisiones
	bool colision = false;

	for(int i = 0; i < SIZE; i++){

    	for(int j = i + 1; j < SIZE; j++){

    		if(arr[i] == arr[j]){
    			colision = true;
    			std::cout<<"Colision entre: " << arr[i] << " y  " << arr[j] <<std::endl;
    			return colision;
    		}
    	}
    }
    return colision;
}


int main(){

	const int SIZE_temp = 25; // tamaño predeterminado del arreglo
	int arr[SIZE_temp];

	int SIZE;

	while(true){

		std::cout<<"Ingrese el tamaño del arreglo (n<25): "<<std::endl;
		std::cin>> SIZE;
		

	    if (std::cin.fail() || SIZE > 25) {
	        // limpìar las banderas de error
	        std::cin.clear();

	        // ignorar el resto de la entreada no validas
	        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	        std::cout << "Eleccion invalida. Porfavor ingrese otro valor.\n"<<std::endl;
	    }else{


		    // Llamar a la funcion para llenar el arreglo
		    llenarArreglo(arr, SIZE);

		    std::cout << "Arreglo de numeros enteros:\n";

		    // Llamar a la funcion para mostrar el arreglo
		    mostrarArreglo(arr, SIZE);
			
			// aki llamar a la funciòn
			int high = SIZE-1;
			int low = 0;

			quickSort(arr, low, high);

			std::cout << "\n";
		    std::cout << "Arreglo ORDENADO:\n";
		    mostrarArreglo(arr, SIZE);


		    //----------------------- definir las claves Hash ---------------------------------

		    //arreglo para guardar las claves Hash, inicializamos los valores con 0
		    int arr_claves_hash[25] = {0}; 

            for(int i = 0; i < SIZE; i++){
                int clave = hash(arr[i], SIZE);

                if (arr_claves_hash[clave] == 0) { // solo se  asigna si está vacío
                    arr_claves_hash[clave] = arr[i];
                    std::cout << "valor k: " << arr[i] << "// clave hash: " << clave << std::endl;
                } else {

					std::cout << "Colision en idice " << clave << " para valor k: " << arr[i] << std::endl;
                	//oks aqui pedir que eliga que tipo de soluciòn le da a la colisiòn pero desde la terminal

                	//---------------------------------------------------------------------------------------
                	char opcion = '\0';

				    while (true) {
				        std::cout << "Ingrese su opcion: (L/C/D/E) \n";
				        std::cin >> opcion;

				        if(opcion == 'L'|| opcion == 'C' || opcion == 'D' || opcion == 'E'){
				        	break;
				        } else{
				        	std::cout << "Eleccion invalida. Porfavor ingrese otra opcion.\n"<<std::endl;
				        }
				    }


			    	switch (opcion) {
			            case 'L':{
			                std::cout << "Opcion [1] - PRUEBA LINEAL\n";
		                    // uso de PRUEBA LINEAL
		                    pruebaLineal(arr_claves_hash, 25, arr[i]);
			                break;                
			            }
			            case 'C':{
			                std::cout << "Opcion [2] - PRUEBA CUADRÀTICA\n";
		                    // uso de PPRUEBA CUADRÀTICA
		                    pruebaCuadratica(arr_claves_hash, 25, arr[i]);
			                break;
			            }
			            case 'D':{
			                std::cout << "Opcion [3] - DOBLE DIRECCIÒN HASH\n";
			                dobleHash(arr_claves_hash, 25, arr[i]);
			                break;          
			            }
			            case 'E':{
			                std::cout << "Opcion [4] - ENCADENAMIENTO\n";
			                // hola
			                break;           
			            }
			        }
                }
            }
			//---------------------------------------------------------------------------------------
            std::cout << "Arreglo de valores hash (hasta 25 espacios): \n";
            mostrarArreglo(arr_claves_hash, 25);
            break;


		    //---------------

		    bool colision_ono = colision(arr_claves_hash, SIZE);

		    if(!colision_ono){
		    	std::cout<<"No hay colisiones !!!!" <<std::endl;
		    }else{
		    	std::cout<<"hayay colisiones " <<std::endl;
		    }                

	    }
	}

	return 0;
}