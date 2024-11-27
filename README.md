# Alineamiento de secuencias con algoritmo de Needleman-Wunsch

Programa de alineamiento de secuencias de ADN utilizando el algoritmo Needleman-Wunsch. Para ello se requieren 2 archivos tipo *tex* que contienen las secuencias a alienear.

Este programa


## Autores

- [@sunxyco](https://github.com/sunxyco)
- [@waripole](https://github.com/waripole)



## Ejecución

Para ejecutar el programa, ejecute el siguiente comando:

```bash
  ./alineamaiento -C1 S.tex -C2 T.tex -u U.tex -V n
```

En donde:
* -C1 **S.tex** corresponde a la secuencia 1 (o cadena 1)
* -C2 **T.tex** corresponde a la secuencia 2 (o cadena 2)
* -u **U.tex** corresponde a la matriz de coincidencia
* -V **n** corresponde al valor de penalidad

## Especificaciones para los Archivos de Entrada

### Formato de los Archivos S.tex y T.tex

Para que el programa funcione correctamente, los archivos `S.tex` y `T.tex` deben cumplir con las siguientes condiciones:

* Los archivos deben ser de tipo texto plano con extención `.tex`.
* Deben contener **unicamente** la secuencia biológica en el siguiente formato.

#### Contenido del Archivo

* Cada archivo debe incluir **una única línea** con la secuencia de nucleótidos.
* La secuencia debe estar en formato **estrictamente lineal**, sin espacios ni caracteres adicionales.

Ejemplo válido:

```bash
    AGCTTC
```

### Formato del archivo U.tex
Para que el programa funcione correctamente, el archivo `U.tex` debe cumplir con las siguientes condiciones:

* El archivo debe ser de tipo texto plano con extención `.tex`.
* otra especificación...

#### Contenido del Archivo

El contenido del archivo `U.tex` debe seguir el siguiente formato:

* blabla

Ejemplo válido:

```bash
    2,-1,-1,-1,
    -1,2,-1,-1,
    -1,-1,2,-1,
    -1,-1,-1,2,
```

### Ubicación

* Asegúrese de que los archivos estén en el directorio especificado para la ejecución del programa.

Si no se cumple este formato, el programa podría generar errores.





## Ejemplo de salida

Con un valor de penalida igual a **0** y comparando las secuencias:
* C1 **AGCTTC**
* C2 **ACCTT**

La terminal mostrará el siguiente alineamiento:

```bash
    C1 | AGCT-TC
    C2 | AC-CTT-
```

Además, se crea un archivo **png** para la visualización de este
<div align="center">
  <img src="alineamiento.png" alt="Ejemplo de alineamiento" width="600" height="300"  />
</div>

###

<div align="center">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" height="40" alt="cplusplus logo"  />
</div>

###