#include <iostream>
#include <string>
#include <stdio.h>

void es_par_ono(int num)
{
    if(num%2==0)
    {
        //printf("El numero es par");
        std::cout <<"El numero "<< num <<" es par";
    }
    else
    {
        //printf("El numero es impar");
        std::cout <<"El numero "<< num <<" es IMpar";
    }

}


int long_strig(const std::string& str)
{
    int longitud = 0;
    int espacios = 0;


    // Iterar sobre cada caracter
    for(char i: str){
        
        longitud++;

        // Contar los espacios
        if( i == ' ' ){
            espacios ++;
        }
    }

    // Restarle al total el número de espacios
    int longitud_string = longitud - espacios;

    std::cout<<"Longitud string: "<<longitud_string<<"";

    return 0;
}

int main()
{
    int num;

    std::cout<<"Ingrese un numero entero: "; // Escribir pregunta
    std::cin>> num; // Leer respuesta

    es_par_ono(num);


    //imprimir lo mismo para los números de 1 al 10
    //for(int i = valor inicial; i <= valor final; i = i + paso)
    for(int i=1; i<=10; i++)
    {
        es_par_ono(i);
    }
    
    char input[100]; //arreglo de caracteres

    std::cout<<"Ingrese una cadena de texto: ";
    std::cin>> input;


    long_strig(input);


    return 0;
}