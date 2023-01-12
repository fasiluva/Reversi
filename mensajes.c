#include "jugadas.c"

void muestraTablero(Jugador *, Jugador *);
void mensajeError(Ficha, char *, Jugador *, Jugador *, Ficha *, char);
void mensajeFinal(Jugador *, Jugador *, int);

void mensajeFinal(Jugador * jugador1, Jugador * jugador2, int cantFichasJugadas)
{
    //TODO . Chequea la cantidad de fichas jugadas de cada uno y en base a eso determina un ganador o empate.

    if (cantFichasJugadas == 64)
    {
        printf("\nLa partida termino correctamente.\n");

        if (jugador1->cantFichas > jugador2->cantFichas)
        {
            printf("Ha ganado el jugador 1");
        }
        if (jugador1->cantFichas < jugador2->cantFichas) 
        {
            printf("Ha ganado el jugador 2");
        }
        else
        {
            printf("Ambos jugadores empataron.");
        }
    }

    else
    {
        if (jugador1->cantFichas == 0)
        {
            print("El jugador 1 se quedó sin fichas.\n");
            print("Gano el jugador 2");
        }
        else if (jugador2->cantFichas == 0)
        {
            print("El jugador 2 se quedó sin fichas.\n");
            print("Gano el jugador 1");
        }
        else
        {
            printf("La partida no se finalizo.\n");
        }

    }
    

}

void mensajeError(Ficha jugadaFicha, char * jugadaString, Jugador * jugador1, Jugador * jugador2, Ficha * jugadasPosibles, char turno)
{
    // mensajeError :: Ficha, char*, Jugador*, Jugador*, Ficha*, char -> None
    // Dado una ficha ingresada, los jugadores, las jugadas posibles y el turno determina el tipo
    // de error que se cometio, pudiendo ser que la ficha ingresada esta en una posicion ocupada
    // o la ficha no genera cambios en el tablero.

    printf("\n============================ ERROR ============================\n");
    printf("Error en la jugada %c%d, cometida por el jugador de fichas %c\n", jugadaString[0], jugadaString[1], turno);

    if (ocupadaJugador(jugadaFicha, jugador1) == 1)
    {
        printf("\n!!! LA FICHA ESTA EN UNA POSICION OCUPADA POR EL JUGADOR 1 !!!\n");
    }
    
    else
    {
        if (ocupadaJugador(jugadaFicha, jugador2) == 1)
        {
            printf("\n!!! LA FICHA ESTA EN UNA POSICION OCUPADA POR EL JUGADOR 2 !!!\n");
        }
        
        else
        {
            if (generaCambios(turno, jugadaFicha, jugador1, jugador2) == 1)
            {
                printf("\n!!! LA FICHA NO GENERA CAMBIOS !!!\n");
            }
            
        }
    }

}

void muestraTablero(Jugador * jugador1, Jugador * jugador2)
{
    // muestraTablero :: Jugador*, Jugador* -> None
    // La funcion recibe los jugadores e imprime el tablero, evaluando por filas y columnas
    // si las casillas estan ocupadas por uno de los jugadores o estan vacias.

    printf("\n===== TABLERO RESULTANTE =====\n");
    printf("|    | A  | B  | C  | D  | E  | F  | G  | H  |");

    for (int fila = 1; fila <= 8; fila++)
    {
        printf("| %d  |", fila);

        for (int columna = 1; columna <= 8; columna++)
        {
            
            Ficha casilla = {columna, fila};

            if (ocupadaJugador(casilla, jugador1) == 1)
            {
                printf(" %c  |", jugador1->color);
            }
            
            else if (ocupadaJugador(casilla, jugador2) == 1)
            {
                printf(" %c  |", jugador2->color);
            }

            else 
            {
                printf("    |");
            }

        }
        
        printf("-------------------------------------------");

    }
    

}

