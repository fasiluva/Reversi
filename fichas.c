#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void fichasIniciales(Jugador *);
int charInt(char);
Ficha transformaFicha(char*);

void fichasIniciales(Jugador * jugador)
{
    // fichasIniciales: char -> int *
    // La funcion recibe el color inicial y devuelve un espacio de memoria dinamica con 
    // las fichas iniciales, dependiendo si el color inicial es 'B' o 'N'.

    if (jugador->color== 'B')
    {
        Ficha ficha1 = {4, 4};
        Ficha ficha2 = {5, 5};
        jugador->fichasJugadas[0] = ficha1;
        jugador->fichasJugadas[1] = ficha2;
    }
    else
    {
        Ficha ficha1 = {4, 5};
        Ficha ficha2 = {5, 4};
        jugador->fichasJugadas[0] = ficha1;
        jugador->fichasJugadas[1] = ficha2;
    }
    
    jugador->cantFichas = 2;

}

int charInt( char caracter) 
{
    // charInt: char -> int
    // La funcion toma un caracter y a su valor ASCII le resta el valor ASCII de '0'. Dicho
    // resultado es el numero que representa el caracter en cuestion.
    // Ej de valores ASCII: '5' = 53, '0' = 48 ==> '5' - '0' = 5

    return caracter - '0';
}

Ficha transformaFicha(char * jugada)
{
    // transformaFicha: string -> int
    // La funcion recibe un string y chequea si los formatos son correctos: El largo de la 
    // cadena es 3 (2 caracteres + espacio), si el 2do caracter es un caracter entre 1 y 8,
    // si el primer caracter esta entre 'A' y 'H'. Si es correcto todo, devuelve la ficha 
    // transformada.

    int ficha;
    char columnasLetra[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    if (strlen(jugada) != 3) // Chequea tamaño de la jugada.
    {
        printf("La jugada debe tener un tamanio de 2 caracteres.");
        Ficha fallo = {-1, -1};
        return fallo;
    }

    if (jugada[1] == '0' || jugada[1] == '9' || isalpha(jugada[1])) // Chequea segundo caracter.
    {
        printf("La jugada esta fuera del rango.");
        Ficha fallo = {-1, -1};
        return fallo;
    }

    for (int i = 0; i < 8; i++)
    {
        if (jugada[0] == columnasLetra[i])
        {
            Ficha ficha = {i, charInt(jugada[1])};
            return ficha;
        }
    }

    printf("El formato de la jugada es incorrecto.");
    
    Ficha fallo = {-1, -1};
    return fallo;
}

