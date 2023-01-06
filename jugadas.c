

void actualizarJugadasPosibles(char turno, Jugador * jugador1, Jugador * jugador2, int * cantJugadasPosibles, Ficha * jugadasPosibles)
{
    // actualizarJugadasPosibles :: char Jugador Jugador int -> int *
    // La funcion devuelve las jugadas posibles que puede realizar el jugador con el 
    // color que indique el turno.
    
    // . Chequea el color y obtiene las fichas tangentes del color contrario
    // . Descarta las fichas fuera del rango, en casillas ocupadas, 
    // . Devuelve el malloc correspondiente



}

int generaCambios(Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2)
{

    

}

int repetida(Ficha fichaTangente, Ficha * jugadasPosibles, int cantFichasTangentes)
{
    for (int i = 0; i < cantFichasTangentes; i++) if (jugadasPosibles[i].x == fichaTangente.x && jugadasPosibles[i].y == fichaTangente.y) return 1;   
    return 0;
}

int ocupada(Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2)
{
    for (int i = 0; i < jugador1->cantFichas; i++)
    {
        if ((jugador1->fichasJugadas[i].x == fichaTangente.x) && (jugador1->fichasJugadas[i].y == fichaTangente.y)) return 1;
        return 0;
    }
}

int * vecinasColorOpuesto(char turno, Jugador * jugador1, Jugador * jugador2, Ficha * jugadasPosibles)
{
    //vecinasColorOpuesto :: char Jugador* Jugador* -> int*
    // La funcion recibe el turno y los jugadores, y calcula las fichas que son tangentes 
    // al color contrario que indica el turno dado. Es decir, si es el turno de las blancas,
    // devuelve todas las fichas que son tangentes a todas las fichas negras.

    int cantFichasVecinas = 0;

    if (jugador1->color == turno) // Si es el turno del color del jugador 1, analiza todas las fichas tangentes del color contrario
    { 
        jugadasPosibles = malloc(sizeof(Ficha) * (jugador2->cantFichas * 8));
        // Nota: cada ficha tiene 8 tangentes, entonces el maximo del malloc debe ser 8 x cantFichas.

        for (int ficha = 0; ficha < jugador2->cantFichas; ficha++)
        {
            
            for (int columna = jugador2->fichasJugadas[ficha].x - 1; columna <= columna + 1; columna++)
            {

                for (int fila = jugador2->fichasJugadas[ficha].y -1 ; fila <= fila + 1; fila++)
                {
                    
                    Ficha fichaTangente = {columna, fila};

                    if ((1 <= columna <= 8) && (1 <= fila <= 8) && (ocupada(fichaTangente, jugador1, jugador2) == 0) && (repetida(fichaTangente, jugadasPosibles, cantFichasVecinas) == 0) && (generaCambios(fichaTangente, jugador1, jugador2) == 0))
                    {
                        jugadasPosibles[cantFichasVecinas] = fichaTangente;
                        cantFichasVecinas++;
                    }

                }

            }
            
        }

        jugadasPosibles = realloc(jugadasPosibles, sizeof(int) * cantFichasVecinas);    
        // Nota: Si el malloc no llegase a ocupar todos sus espacios, lo achica con la cantidad de fichas tangentes obtenidas.

    }

    else
    {
        jugadasPosibles = malloc(sizeof(Ficha) * (jugador1->cantFichas * 8)); 
        // Nota: cada ficha tiene 8 tangentes, entonces el maximo del malloc debe ser 8 * cantFichas.

        for (int i = 0; i < jugador1->cantFichas; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                int ficha;
                switch(j) 
                {
                    case 0:
                        ficha = jugador1->fichasJugadas[i] + 10; // Ficha lateral derecha
                        fichasVecinas = actualizaFichasVecinas(ficha, fichasVecinas, &cantFichasVecinas, jugador1, jugador2); 
                        break;
                    case 1:
                        ficha = jugador1->fichasJugadas[i] + 11; // Ficha diagonal inferior derecha
                        fichasVecinas = actualizaFichasVecinas(ficha, fichasVecinas, &cantFichasVecinas, jugador1, jugador2);
                        break;
                    case 2:
                        ficha = jugador1->fichasJugadas[i] + 1; // Ficha inferior
                        fichasVecinas = actualizaFichasVecinas(ficha, fichasVecinas, &cantFichasVecinas, jugador1, jugador2);
                        break;
                    case 3:
                        ficha = jugador1->fichasJugadas[i] - 9; // Ficha diagonal inferior izquierda
                        fichasVecinas = actualizaFichasVecinas(ficha, fichasVecinas, &cantFichasVecinas, jugador1, jugador2);
                        break;
                    case 4:
                        ficha = jugador1->fichasJugadas[i] - 10; // Ficha lateral izquierda
                        fichasVecinas = actualizaFichasVecinas(ficha, fichasVecinas, &cantFichasVecinas, jugador1, jugador2);
                        break;
                    case 5: 
                        ficha = jugador1->fichasJugadas[i] - 11; // Ficha diagonal superior izquierda
                        fichasVecinas = actualizaFichasVecinas(ficha, fichasVecinas, &cantFichasVecinas, jugador1, jugador2);
                        break;
                    case 6: 
                        ficha = jugador1->fichasJugadas[i] - 1; // Ficha superior
                        fichasVecinas = actualizaFichasVecinas(ficha, fichasVecinas, &cantFichasVecinas, jugador1, jugador2);
                        break;
                    case 7:
                        ficha = jugador1->fichasJugadas[i] + 9; // Ficha diagonal superior derecha
                        fichasVecinas = actualizaFichasVecinas(ficha, fichasVecinas, &cantFichasVecinas, jugador1, jugador2);
                        break;
                }   
            }
        }

        fichasVecinas = realloc(fichasVecinas, sizeof(int) * cantFichasVecinas);    
        // Nota: Si el malloc no llegase a ocupar todos sus espacios, lo achica con la cantidad de fichas tangentes obtenidas.
        return fichasVecinas;
    }
}

