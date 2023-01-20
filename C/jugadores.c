#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int colorValido(char);
int mismosColores(char, char);

typedef struct 
{
    int x;
    int y;
} Ficha;

typedef struct 
{
    char color;
    int cantFichas;
    Ficha * fichasJugadas;
} Jugador;

int colorValido (char color)
{
    // colorValido: char -> int
    // La funcion recibe un caracter y devuelve 0 si el caracter es 'N' o 'B'. Sino, 
    // devuelve 1.

    return (color == 'N' || color == 'B') ? 0 : 1;
}

int mismosColores(char color1, char color2)
{
    // mismosColores: char char -> int
    // La funcion recibe 2 caracteres (correspondientes a los colores de los jugadores) 
    // y devuelve 1 si ambos colores son iguales o 0 si son diferentes.

    return (color1 == color2) ? 1 : 0;
}

