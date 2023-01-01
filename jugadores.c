#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char color;
    int cantFichas;
    char * fichasJugadas;
} Jugador;


int colorValido (char color)
{
    return (color == 'N' || color == 'B') ? 0 : 1;
}

int mismosColores(char color1, char color2)
{
    printf("%c", color1);
    return (color1 == color2) ? 1 : 0;
}