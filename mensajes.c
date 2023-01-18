
void muestraTablero(Jugador *, Jugador *);
void mensajeFinal(Jugador *, Jugador *, int, char);

void mensajeFinal(Jugador * jugador1, Jugador * jugador2, int cantFichasJugadas, char turno)
{
    //TODO . Chequea la cantidad de fichas jugadas de cada uno y en base a eso determina un ganador o empate.

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
            printf("\n\n-------------- La partida no termino. --------------\n");
            escribeTablero(jugador1, jugador2, turno);
        }

    }
    
    printf("\n");
}
