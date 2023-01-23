#include<string.h>
#include <stdio.h>


FILE * reingresaArchivo(char * nombre) 
{
    // reingresaArchivo: char * -> FILE *
    // 
    // La funcion recibe el puntero del argumento e intenta abrirlo como archivo. Si fue ingresado
    // incorrectamente, en el bloque while en el que se encuentra en main, devolvera NULL, por lo 
    // que no saldra del bucle while, repitiendo el proceso.

    FILE * archivo = fopen(nombre, "r");
    return archivo;
}

