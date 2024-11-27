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
* C1 **S.tex** corresponde a la secuencia 1 (o cadena 1)
* C2 **T.tex** corresponde a la secuencia 2 (o cadena 2)
* u **U.tex** corresponde a la matriz de coincidencia
* **V** n corresponde al valor de penalidad

## Ejemplo de salida

Con un valor de penalida igual a **0** y comparando las secuencias:
* C1 **AGCTTC**
* C2 **ACCTT**

La terminal mostrará el siguiente alineamiento:

```bash
    C1 | AGCT-TC
    C2 | AC-CTT-
```

Además, se crea un archivo **png** para la visualización de este:
![This is an alt text.](/image/sample.webp "Alineamiento de secuencias.")

###

<div align="left">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" height="40" alt="cplusplus logo"  />
</div>

###