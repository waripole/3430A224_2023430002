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
        - Checar si la pila está llena o no
            Donde nos encontramos con dos casos:
            - Si la pila NO está llena, entonces el contenedor se agregará a la pila con un push().
            - Si la SI está llena, entonces se pasa a la siguiente pila para repetir el proceso de chequeo().

            - En caso de que ninguna pila esté vacia para agregar un contenedor, entonces se imprimirá un mensaje adoc.

    Salida:
        [contenedor a sacar -> contenedor*]
        - Primero se chequea si hay pilas que no estén llenas, para así agregar a estas los contenedores movidos
         para permitir la salida del elemento contenedor* a sacar (pop()).
        - Si existen otras pilas no llenas, entonces se hará un pop() a los contenedores sobre el contenedor* y se 
            agregarán a la siguiente pila no llena.
        - Luego de cada push() de un contenedor movido a una pila nueva, se chequea si la pila está llena o no para
        determinar si se le pueden seguir agregando elementos contenedor o no.


