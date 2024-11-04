#include <iostream>
#include <fstream>

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


void pruebaLineal(){

}

void pruebaCuadratica(){

}

void dobleHash(){

}

void encadenamiento(){

}

void hash(){

}

int main(){

	const int SIZE_temp = 10; // tamaño predeterminado del arreglo
	int arr[SIZE_temp];

	int SIZE;

	int SIZE;

	while(true){

		std::cout<<"Ingrese el tamaño del arreglo (n<10): "<<std::endl;
		std::cin>> SIZE;


	    if (std::cin.fail() || SIZE > 50) {
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
			
			std::cout << "\n";

		    break;
	    }
	}

	return 0;
}