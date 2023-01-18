#include "fichas.c"
#include "jugadas.c"

void muestraTablero(Jugador *, Jugador *);
void escribeTablero(Jugador *, Jugador *, char);
void mensajeFinal(Jugador *, Jugador *, int, char);

void mensajeFinal(Jugador * jugador1, Jugador * jugador2, int cantFichasJugadas, char turno)
{
    // mensajeFinal :: Jugador *, Jugador *, int, char -> None
    // La funcion recibe los jugadores, la cantidad de fichas jugadas y el turno, y muestra en la consola
    // si hay ganadores en la partida, si empataron o si la partida no termino. En caso de no haber 
    // terminado, ejecuta una funcion para escribir el tablero en un archivo.

    if (cantFichasJugadas == 64)
    {
        printf("\n-------------- La partida termino correctamente. --------------\n");
        printf("\n");

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
            printf("\n\nEl jugador 1 se quedo sin fichas.\n");
            printf("Gano el jugador 2");
        }
        else if (jugador2->cantFichas == 0)
        {
            printf("\n\nEl jugador 2 se quedo sin fichas.\n");
            printf("Gano el jugador 1");
        }
        else
        {
            printf("\n-------------- La partida no termino. --------------\n");
            escribeTablero(jugador1, jugador2, turno);
        }

    }
    
    printf("\n");
}

void escribeTablero(Jugador * jugador1, Jugador * jugador2, char turno)
{
    // escribeTablero :: Jugador *, Jugador *, char -> None
    // Recibe los jugadores y el turno, y escribe en un archivo llamado "juegoContinuacion.txt" 
    // el tablero que quedo, siendo X un espacio vacio y B o N el color del jugador correspondiente
    // donde haya una ficha. La ultima linea es el turno que continuaria en la partida.

    FILE * archivo = fopen("juegoContinuacion.txt", "w");

    for (int fila = 1; fila <= 8; fila++)
    {
        for (int columna = 1; columna <= 8; columna++)
        {

            Ficha casilla = {columna, fila};
            
            if (ocupadaJugador(casilla, jugador1) == 1)
            {
                fputc(jugador1->color, archivo);
            }

            else if (ocupadaJugador(casilla, jugador2) == 1)
            {
                fputc(jugador2->color, archivo);
            }
            
            else 
            {
                fputc('X', archivo);
            }

        }

        fputc('\n', archivo);
        
    }
    
    fputc(turno, archivo);

    fclose(archivo);

}

void muestraTablero(Jugador * jugador1, Jugador * jugador2)
{
    // muestraTablero :: Jugador*, Jugador* -> None
    // La funcion recibe los jugadores e imprime el tablero, evaluando por filas y columnas
    // si las casillas estan ocupadas por uno de los jugadores o estan vacias.

    printf("\n===== TABLERO RESULTANTE =====\n\n");
    printf("|    | A  | B  | C  | D  | E  | F  | G  | H  |\n");
    printf("----------------------------------------------\n");

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
        
        printf("\n----------------------------------------------\n");

    }
    
}