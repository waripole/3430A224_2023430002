**README EJERCICIO N°2**
***
El ingreso de contenedores al puerto la realiza el usuario, ingresando primeramente los parámetros de la cantidad de pilas (parámetro **m**) y la cantidad de contenedores posibles de acoplar en cada una de las pilas (parámetro **n**).

Luego, las opciones para la manipulación de contenedores son:
* Agregar contenedor [1]
* Remover contenedor [2]
* Ver orden          [3]

Además de una opción para salir del programa:
* Salir              [0]


***
Para gestionar el ingreso y salida de contenedores se utilizará la siguiente lógica automática:

Ingreso:
1. Checar si la pila está llena o no
    Donde nos encontramos con dos casos:
    (a) Si la pila NO está llena, entonces el contenedor se agregará a la pila con un  push().
    (b) Si la SI está llena, entonces se pasa a la siguiente pila para repetir el proceso de chequeo().
2. En caso de que ninguna pila esté vacia para agregar un contenedor, entonces se imprimirá un mensaje adoc al contexto.

Salida:
1. Iterar sobre cada pila hasta encontrar el contenedor a eliminar
2. Checar si hay pilas que no estén llenas, para así agregar a estas los contenedores movidos para permitir la salida del elemento contenedor* a sacar (pop()).
3. Mover los contenedores superiores a otras pilas
4. Eliminar el contenedor seleccionado

***
**Autor: Sofía Mieres Vignolo** 

**Ingeniería Civil en Bioinformática**