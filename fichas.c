#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void fichasIniciales(Jugador *);
int charInt(char);
Ficha transformaFicha(char*);

void fichasIniciales(Jugador * jugador)
{
    // fichasIniciales :: Jugador* -> None
    // La funcion recibe un jugador y añade a sus fichas jugadas las fichas iniciales, dependiendo 
    // de su color.

    jugador->fichasJugadas = malloc(sizeof(Ficha) * 2);

    if (jugador->color == 'B')
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

int charInt(char caracter) 
{
    // charInt: char -> int
    // La funcion toma un caracter y a su valor ASCII le resta el valor ASCII de '0'. Dicho
    // resultado es el numero que representa el caracter en cuestion.
    // Ej de valores ASCII: '5' = 53, '0' = 48 ==> '5' - '0' = 5

    return caracter - '0';
}

Ficha transformaFicha(char * jugada)
{
    // transformaFicha: string -> Ficha
    // La funcion recibe un string y chequea si los formatos son correctos: El largo de la 
    // cadena es 3 (2 caracteres + espacio), el segundo caracter es un numero entre 1 y 8 y
    // que el primer caracter es una letra entre A y H. Si la jugada no cumple con lo previamente 
    // dicho, devuelve la Ficha {-1, -1}, si es un salto de turno, devuelve la ficha {0, 0}, y si 
    // es correcto lo ingresado, devuelve la ficha transformada.

    int ficha;
    char columnasLetra[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    if (strlen(jugada) != 3) // Chequea tamaño de la jugada.
    {
        printf("\n!!! La jugada debe tener un tamanio de 2 caracteres. !!!\n");
        Ficha fallo = {-1, -1};
        return fallo;
    }

    if (jugada[0] == '\0')
    {
        Ficha saltoDeTurno = {0, 0};
        return saltoDeTurno;
    }
    

    if (jugada[1] == '0' || jugada[1] == '9' || isalpha(jugada[1])) // Chequea segundo caracter.
    {
        printf("\n!!! La jugada esta fuera del rango. !!!\n");
        Ficha fallo = {-1, -1};
        return fallo;
    }

    for (int i = 0; i < 8; i++)
    {
        if (jugada[0] == columnasLetra[i])
        {
            Ficha ficha = {i+1, charInt(jugada[1])};
            return ficha;
        }
    }

    printf("\n !!! El formato de la jugada es incorrecto. !!!\n");
    
    Ficha fallo = {-1, -1};
    return fallo;
}

