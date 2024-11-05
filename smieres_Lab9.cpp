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

void pruebaLineal(){

}

void pruebaCuadratica(){

}

void dobleHash(){

}

void encadenamiento(){

}

// calcular hash con el mod
int hash(int k, int SIZE){
	//recorrer el arreglo y asignar un valor a c/u
	int claveHash = (k % SIZE) + 1;
	//std::cout<<"clave hash: "<< claveHash <<std::endl;
	return claveHash;
}

int main(){

	const int SIZE_temp = 10; // tamaño predeterminado del arreglo
	int arr[SIZE_temp];

	int SIZE;

	while(true){

		std::cout<<"Ingrese el tamaño del arreglo (n<10): "<<std::endl;
		std::cin>> SIZE;


	    if (std::cin.fail() || SIZE > 10) {
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


		    //----------------------- definir las claves Hash

		    //arreglo para guardar las claves Hash, inicializamos los valores con 0
		    int arr_claves_hash[15] = {0}; 

		    for(int i = 0; i < SIZE; i++){
		    	int clave = hash(arr[i], SIZE);
		    	arr_claves_hash[i] = clave;
		    	std::cout<<"valor k: "<<arr[i]<<"// clave hash: "<< clave <<std::endl;
		    }

		    std::cout << "Arregño valores hash (hasta 15 espacios): \n"<<std::endl;
			mostrarArreglo(arr_claves_hash, SIZE);

		    break;
	    }
	}

	return 0;
}