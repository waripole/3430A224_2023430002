#include <iostream>
#include <string>
#include <stdio.h>

void es_par_ono(int num)
{
    if(num%2==0)
    {
        printf("El número es par");
    }
    else
    {
        printf("El número es impar");
    }

}

//WRONG POR AHORA
int longitud_string(const std::string& str)
{
    int longitud = 0;

    //for(int i = valor inicial; i <= valor final; i = i + paso)
    for(char c : str)
    {
        longitud = longitud + 1;
    }

    printf("La longitud de la palabra es: ");

    return longitud;
}

int main()
{
    int num;
    printf("Ingrese un numero entero: ");
    scanf("%d", &num);
    //printf("Se ingreso un %d", num);

    es_par_ono(num);

    //imprimir lo mismo para los números de 1 al 10 - MASOMENOS
    //for(int i = valor inicial; i <= valor final; i = i + paso)
    for(int i=1;i<=10;i+=1)
    {
        es_par_ono(i);
    }
    
    char input[100]; //arreglo de caracteres
    printf("Ingrese una cadena de texto: ");
    scanf("%99s", input);

    return 0;
}