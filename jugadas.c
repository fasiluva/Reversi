#include "fichas.c"

char cambiaTurno(char turno);
int ocupadaJugador(Ficha, Jugador *);
int generaHorizontal(Ficha, Jugador *, Jugador *, char);
int generaVertical(Ficha, Jugador *, Jugador *, char);
int generaDiagonalDer(Ficha, Jugador *, Jugador *, char);
int generaDiagonalIzq(Ficha, Jugador *, Jugador *, char);
Ficha * actualizarJugadasPosibles(char, Jugador *, Jugador *, int *, Ficha *);
Ficha * vecinasColorOpuesto(char, Jugador *, Jugador *, int *, Ficha *);
int jugadaCorrecta (char *, Jugador *, Jugador *, Ficha *, int, char);
void modificaFichas (Ficha, Jugador *, Jugador *, char);
void modificaHorizontal(Ficha, Jugador *, Jugador *);
void modificaVertical(Ficha, Jugador *, Jugador *);
void modificaDiagonalDer(Ficha, Jugador *, Jugador *);
void modificaDiagonalIzq(Ficha, Jugador *, Jugador *);
void removerFicha(Ficha, Jugador *);
void aniadirFicha(Ficha, Jugador *);

char cambiaTurno(char turno)
{
    return (turno == 'B') ? 'N' : 'B';
}

void aniadirFicha(Ficha casillaAniadir, Jugador * jugadorTurno)
{
    jugadorTurno->cantFichas++;
    realloc(jugadorTurno, sizeof(Ficha) * (jugadorTurno->cantFichas));
    jugadorTurno->fichasJugadas[jugadorTurno->cantFichas] = casillaAniadir;
 
}

void removerFicha(Ficha casillaCambiar, Jugador * jugadorCambiaFichas)
{

    for (int i = 0; i < jugadorCambiaFichas->cantFichas; i++)
    {
        if (jugadorCambiaFichas->fichasJugadas[i].x == casillaCambiar.x && jugadorCambiaFichas->fichasJugadas[i].y == casillaCambiar.y)
        {
            for (int j = i; j < jugadorCambiaFichas->cantFichas - 1; j++)
            {
                jugadorCambiaFichas[j] = jugadorCambiaFichas[j + 1]; 
            }
            
            jugadorCambiaFichas->cantFichas--;

            realloc(jugadorCambiaFichas->fichasJugadas, sizeof(Ficha) * jugadorCambiaFichas->cantFichas);

        }
        
    }
    
}

int ocupadaJugador(Ficha casilla, Jugador * jugadorX)
{

    for (int i = 0; i < jugadorX->cantFichas; i++) if ((jugadorX->fichasJugadas[i].x == casilla.x) && (jugadorX->fichasJugadas[i].y == casilla.y)) return 1;
    return 0;

}

void modificaHorizontal(Ficha jugadaHecha, Jugador * jugadorCambiaFichas, Jugador * jugadorTurno)
{

    for (int contadorDerecha = jugadaHecha.x + 1; contadorDerecha <= 8; contadorDerecha++)
    {
        
        Ficha casillaFinal = {contadorDerecha, jugadaHecha.y};

        if ((contadorDerecha == jugadaHecha.x + 1) && (ocupadaJugador(casillaFinal, jugadorTurno) == 1)) contadorDerecha = 9;
        else
        {
            if (ocupadaJugador(casillaFinal, jugadorCambiaFichas) == 0 && ocupadaJugador(casillaFinal, jugadorTurno) == 0) contadorDerecha = 9;
            
            if (ocupadaJugador(casillaFinal, jugadorTurno) == 1)
            {
                aniadirFicha(jugadaHecha, jugadorTurno); // Añade la ficha jugada.

                for (int i = jugadaHecha.x + 1; i < contadorDerecha; i++) // Añade las fichas que encierra hacia la derecha 
                {
                    Ficha casillaCambiar = {i, jugadaHecha.y};
                    
                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);
                }
                
            }
        
        }

    }
    
    for (int contadorIzquierda = jugadaHecha.x - 1; contadorIzquierda >= 1; contadorIzquierda--)
    {
        
        Ficha casillaFinal = {contadorIzquierda, jugadaHecha.y};

        if ((contadorIzquierda == jugadaHecha.x + 1) && (ocupadaJugador(casillaFinal, jugadorTurno) == 1)) contadorIzquierda = 0;
        else
        {
            if (ocupadaJugador(casillaFinal, jugadorCambiaFichas) == 0 && ocupadaJugador(casillaFinal, jugadorTurno) == 0) contadorIzquierda = 0;
            
            if (ocupadaJugador(casillaFinal, jugadorTurno) == 1)
            {
                aniadirFicha(jugadaHecha, jugadorTurno); // Añade la ficha jugada.

                for (int i = jugadaHecha.x + 1; i < contadorIzquierda; i++)
                {
                    Ficha casillaCambiar = {i, jugadaHecha.y};
                    
                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);
                }
                
            }
        
        }

    }

}

void modificaFichas (Ficha jugada, Jugador * jugador1, Jugador * jugador2, char turno)
{

    if (jugador1->color == turno) // Si la jugada es del jugador 1, cambia fichas del jugador 2
    {
        modificaHorizontal(jugada, jugador2, jugador1);
        modificaVertical(jugada, jugador2, jugador1);
        modificaDiagonalDer(jugada, jugador2, jugador1);
        modificaDiagonalIzq(jugada, jugador2, jugador1);
    }
    
    else
    {
        modificaHorizontal(jugada, jugador1, jugador2);
        modificaVertical(jugada, jugador1, jugador2);
        modificaDiagonalDer(jugada, jugador1, jugador2);
        modificaDiagonalIzq(jugada, jugador1, jugador2);
    }

}

int jugadaCorrecta(char * jugada, Jugador * jugador1, Jugador * jugador2, Ficha * jugadasPosibles, int cantJugadasPosibles, char turno)
{

    // jugadaCorrecta :: char *, Jugador *, Jugador *, Ficha * -> int
    // La funcion recibe una jugada y devuelve 0 si la jugada ingresada fue correcta, evaluando que
    // LA JUGADA ESTE DENTRO DE LAS JUGADAS POSIBLES. Si no lo esta, devuelve 1, pero antes pasando por 
    // otras funciones que dan a saber mas del error cometido.

    if (transformaFicha(jugada).x == -1)
    {
        return 1; //! ERROR DE TIPEO DE JUGADA
    }

    Ficha jugadaFicha = transformaFicha(jugada);
    
    if (jugadaFicha.x == 0 && cantJugadasPosibles == 0)
    {
        return 0; //! TURNO SALTEADO CORRECTAMENTE
    }

    for (int ficha = 0; ficha < cantJugadasPosibles ; ficha++)
    {    
        if (jugadasPosibles[ficha].x == jugadaFicha.x && jugadasPosibles[ficha].y == jugadaFicha.y)
        {
            return 0; //! LA JUGADA ESTA DENTRO DE LAS POSIBILIDADES
        }
    }
    
    mensajeError(jugadaFicha, jugada, jugador1, jugador2, jugadasPosibles, turno); 
    return 1;
}

Ficha * actualizarJugadasPosibles(char turno, Jugador * jugador1, Jugador * jugador2, int * cantJugadasPosibles, Ficha * jugadasPosibles)
{
    // actualizarJugadasPosibles :: char, Jugador*, Jugador*, Ficha*, int, char -> Ficha*
    // La funcion devuelve las jugadas posibles que puede realizar el jugador con el 
    // color que indique el turno.
    
    jugadasPosibles = vecinasColorOpuesto(turno, jugador1, jugador2, cantJugadasPosibles, jugadasPosibles);
    
}

int generaVertical(Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2, char turno)
{

    if (jugador1->color == turno) 
    {
        for (int contadorArriba = fichaTangente.y - 1; contadorArriba >= 1; contadorArriba--)
        {
            
            Ficha casilla = {fichaTangente.x, contadorArriba};

            if ((contadorArriba == fichaTangente.y - 1) && (ocupadaJugador(casilla, jugador1) == 1)) contadorArriba = 0;
            else
            {
                if (ocupadaJugador(casilla, jugador2) == 0 && ocupadaJugador(casilla, jugador1) == 0) contadorArriba = 0;
                
                if (ocupadaJugador(casilla, jugador1) == 1) return 0;
            }
            
        }
        
        for (int contadorAbajo = fichaTangente.y + 1; contadorAbajo <= 8; contadorAbajo++)
        {
            
            Ficha casilla = {fichaTangente.x, contadorAbajo};

            if ((contadorAbajo == fichaTangente.x + 1) && (ocupadaJugador(casilla, jugador1) == 1)) contadorAbajo = 9;
            else
            {
                if ((ocupadaJugador(casilla, jugador2) == 0) && (ocupadaJugador(casilla, jugador1) == 0)) contadorAbajo = 9;

                if (ocupadaJugador(casilla, jugador1) == 1) return 0;
            }

        }
        
        return 1;
    }

    else 
    {
        for (int contadorArriba = fichaTangente.y - 1; contadorArriba >= 1; contadorArriba--)
        {
            
            Ficha casilla = {fichaTangente.x, contadorArriba};

            //printf("\n--- Casilla ---\nColumna: %d\nFila: %d\n", casilla.x, casilla.y);
            
            if ((contadorArriba == fichaTangente.y - 1) && (ocupadaJugador(casilla, jugador2) == 1)) contadorArriba = 0;
            else
            {
                if (ocupadaJugador(casilla, jugador1) == 0 && ocupadaJugador(casilla, jugador2) == 0) contadorArriba = 0;
                
                if (ocupadaJugador(casilla, jugador2) == 1) return 0;
            }
            
        }
        
        for (int contadorAbajo = fichaTangente.y + 1; contadorAbajo <= 8; contadorAbajo++)
        {
            
            Ficha casilla = {fichaTangente.x, contadorAbajo};

            //printf("\n--- Casilla ---\nColumna: %d\nFila: %d\n", casilla.x, casilla.y);

            if ((contadorAbajo == fichaTangente.y + 1) && (ocupadaJugador(casilla, jugador2) == 1)) contadorAbajo = 9;
            else
            {
                if ((ocupadaJugador(casilla, jugador1) == 0) && (ocupadaJugador(casilla, jugador2) == 0)) contadorAbajo = 9;

                if (ocupadaJugador(casilla, jugador2) == 1) return 0;
            }

        }
        
    return 1;
    }
}

int generaHorizontal(Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2, char turno)
{

    if (jugador1->color == turno) 
    {
        for (int contadorDerecha = fichaTangente.x + 1; contadorDerecha <= 8; contadorDerecha++)
        {
            
            Ficha casilla = {contadorDerecha, fichaTangente.y};

            if ((contadorDerecha == fichaTangente.x + 1) && (ocupadaJugador(casilla, jugador1) == 1)) contadorDerecha = 9;
            else
            {
                if (ocupadaJugador(casilla, jugador2) == 0 && ocupadaJugador(casilla, jugador1) == 0) contadorDerecha = 9;
                
                if (ocupadaJugador(casilla, jugador1) == 1) return 0;
            }
            
        }
        
        for (int contadorIzquierda = fichaTangente.x - 1; contadorIzquierda >= 1; contadorIzquierda--)
        {
            
            Ficha casilla = {contadorIzquierda, fichaTangente.y};

            if ((contadorIzquierda == fichaTangente.x + 1) && (ocupadaJugador(casilla, jugador1) == 1)) contadorIzquierda = 0;
            else
            {
                if ((ocupadaJugador(casilla, jugador2) == 0) && (ocupadaJugador(casilla, jugador1) == 0)) contadorIzquierda = 0;

                if (ocupadaJugador(casilla, jugador1) == 1) return 0;
            }

        }
        return 1;
    }

    else
    {

        for (int contadorDerecha = fichaTangente.x + 1; contadorDerecha <= 8; contadorDerecha++)
        {
            
            Ficha casilla = {contadorDerecha, fichaTangente.y};

            if ((contadorDerecha == fichaTangente.x + 1) && (ocupadaJugador(casilla, jugador2) == 1)) contadorDerecha = 9;
            else
            {
                if (ocupadaJugador(casilla, jugador1) == 0 && ocupadaJugador(casilla, jugador2) == 0) contadorDerecha = 9;
                
                if (ocupadaJugador(casilla, jugador2) == 1) return 0;
            }
            
        }
        
        for (int contadorIzquierda = fichaTangente.x - 1; contadorIzquierda >= 1; contadorIzquierda--)
        {
            
            Ficha casilla = {contadorIzquierda, fichaTangente.y};

            if ((contadorIzquierda == fichaTangente.x - 1) && (ocupadaJugador(casilla, jugador2) == 1)) contadorIzquierda = 0;
            else
            {
                if ((ocupadaJugador(casilla, jugador1) == 0) && (ocupadaJugador(casilla, jugador2) == 0)) contadorIzquierda = 0;

                if (ocupadaJugador(casilla, jugador2) == 1) return 0;
            }

        }

    }

    return 1;
}

int generaDiagonalDer(Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2, char turno)
{

    if (jugador1->color == turno) 
    {
        int contadorFila = fichaTangente.y - 1;
        int contadorColumna = fichaTangente.x + 1;

        for (; contadorColumna <= 8 && contadorFila >= 1; contadorColumna++, contadorFila--)
        {
            
            Ficha casilla = {contadorColumna, contadorFila};

            if ((contadorColumna == fichaTangente.x + 1) && (contadorFila == fichaTangente.y - 1) && (ocupadaJugador(casilla, jugador1) == 1)) contadorColumna = 9;
            else
            {    
                if (ocupadaJugador(casilla, jugador2) == 0 && ocupadaJugador(casilla, jugador1) == 0) contadorColumna = 9;
                
                if (ocupadaJugador(casilla, jugador1) == 1) return 0;
            }
            
        }

        contadorFila = fichaTangente.y + 1;
        contadorColumna = fichaTangente.x - 1;
        
        for (; contadorColumna >= 1 && contadorFila <= 8; contadorColumna--, contadorFila++)
        {
            
            Ficha casilla = {contadorColumna, contadorFila};

            if ((contadorColumna == fichaTangente.x - 1) && (contadorFila == fichaTangente.y + 1) && (ocupadaJugador(casilla, jugador1) == 1)) contadorColumna = 0;
            else
            {
                if ((ocupadaJugador(casilla, jugador2) == 0) && (ocupadaJugador(casilla, jugador1) == 0)) contadorColumna = 0;

                if (ocupadaJugador(casilla, jugador1) == 1) return 0;
            }

        }
        return 1;
    }

    int contadorFila = fichaTangente.y - 1;
    int contadorColumna = fichaTangente.x + 1;

    for (; contadorColumna <= 8 && contadorFila >= 1; contadorColumna++, contadorFila--)
        {
            
            Ficha casilla = {contadorColumna, contadorFila};

            if ((contadorColumna == fichaTangente.x + 1) && (contadorFila == fichaTangente.y - 1) && (ocupadaJugador(casilla, jugador2) == 1)) contadorColumna = 9;
            else{
                if (ocupadaJugador(casilla, jugador1) == 0 && ocupadaJugador(casilla, jugador2) == 0) contadorColumna = 9;
                
                if (ocupadaJugador(casilla, jugador2) == 1) return 0;
            }
            
        }

    contadorFila = fichaTangente.y + 1;
    contadorColumna = fichaTangente.x - 1;
        
    for (; contadorColumna >= 1 && contadorFila <= 8; contadorColumna--, contadorFila++)
    {
        
        Ficha casilla = {contadorColumna, contadorFila};

        if ((contadorColumna == fichaTangente.x - 1) && (contadorFila == fichaTangente.y + 1) && (ocupadaJugador(casilla, jugador2) == 1)) contadorColumna = 0;
        else{
            if ((ocupadaJugador(casilla, jugador1) == 0) && (ocupadaJugador(casilla, jugador2) == 0)) contadorColumna = 0;

            if (ocupadaJugador(casilla, jugador2) == 1) return 0;
        }

    }

    return 1;

}

int generaDiagonalIzq(Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2, char turno)
{

    if (jugador1->color == turno) 
    {
        int contadorFila = fichaTangente.y - 1;
        int contadorColumna = fichaTangente.x - 1;

        for (; contadorColumna >= 1 && contadorFila >= 1; contadorColumna--, contadorFila--)
        {
            
            Ficha casilla = {contadorColumna, contadorFila};

            if ((contadorColumna == fichaTangente.x - 1) && (contadorFila == fichaTangente.y - 1) && (ocupadaJugador(casilla, jugador1) == 1)) contadorColumna = 0;
            else
            {
                if (ocupadaJugador(casilla, jugador2) == 0 && ocupadaJugador(casilla, jugador1) == 0) contadorColumna = 0;
                
                if (ocupadaJugador(casilla, jugador1) == 1) return 0;
            }
            
        }

        contadorFila = fichaTangente.y + 1;
        contadorColumna = fichaTangente.x + 1;
        
        for (; contadorColumna <= 8 && contadorFila <= 8; contadorColumna++, contadorFila++)
        {
            
            Ficha casilla = {contadorColumna, contadorFila};

            if ((contadorColumna == fichaTangente.x + 1) && (contadorFila == fichaTangente.y + 1) && (ocupadaJugador(casilla, jugador1) == 1)) contadorColumna = 9;
            else 
            {
                if ((ocupadaJugador(casilla, jugador2) == 0) && (ocupadaJugador(casilla, jugador1) == 0)) contadorColumna = 9;

                if (ocupadaJugador(casilla, jugador1) == 1) return 0;
            }

        }
        return 1;
    }
    else
    {
        int contadorColumna = fichaTangente.x - 1;
        int contadorFila = fichaTangente.y - 1;

        for (; contadorColumna >= 1 && contadorFila >= 1; contadorColumna--, contadorFila--)
            {
                
                Ficha casilla = {contadorColumna, contadorFila};

                if ((contadorColumna == fichaTangente.x - 1) && (contadorFila == fichaTangente.y - 1) && (ocupadaJugador(casilla, jugador2) == 1)) contadorColumna = 0;
                else
                {
                    if (ocupadaJugador(casilla, jugador1) == 0 && ocupadaJugador(casilla, jugador2) == 0) contadorColumna = 0;
                
                    if (ocupadaJugador(casilla, jugador2) == 1) return 0;
                }
                
            }

        contadorColumna = fichaTangente.x + 1;
        contadorFila = fichaTangente.y + 1;
            
        for (; contadorColumna <= 8 && contadorFila <= 8; contadorColumna++, contadorFila++)
        {
            
            Ficha casilla = {contadorColumna, contadorFila};

            if ((contadorColumna == fichaTangente.x + 1) && (contadorFila == fichaTangente.y + 1) && (ocupadaJugador(casilla, jugador2) == 1)) contadorColumna = 9;
            else{

                if ((ocupadaJugador(casilla, jugador1) == 0) && (ocupadaJugador(casilla, jugador2) == 0)) contadorColumna = 9;

                if (ocupadaJugador(casilla, jugador2) == 1) return 0;
            }

        }

        return 1;
    }
}

int generaCambios(char turno, Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2)
{

    if (generaHorizontal(fichaTangente, jugador1, jugador2, turno) == 0 || generaVertical(fichaTangente, jugador1, jugador2, turno) == 0 || generaDiagonalDer(fichaTangente, jugador1, jugador2, turno) == 0 || generaDiagonalIzq(fichaTangente, jugador1, jugador2, turno) == 0) return 0;
    
    return 1;

}

int repetida(Ficha fichaTangente, Ficha * jugadasPosibles, int cantFichasTangentes)
{

    for (int i = 0; i < cantFichasTangentes; i++) if (jugadasPosibles[i].x == fichaTangente.x && jugadasPosibles[i].y == fichaTangente.y) return 1;   
    return 0;
}

Ficha * vecinasColorOpuesto(char turno, Jugador * jugador1, Jugador * jugador2, int * cantJugadasPosibles, Ficha * jugadasPosibles)
{
    // vecinasColorOpuesto :: char, Jugador*, Jugador*, int*, Ficha* -> Ficha*
    // La funcion recibe el turno, los jugadores, la cantidad de jugadas posibles y las jugadas posibles, y devuelve
    // un espacio de memoria con todas las fichas que se pueden jugar en el turno.

    int cantFichasVecinas = 0;

    if (jugador1->color == turno) // Si es el turno del color del jugador 1, analiza todas las fichas tangentes del color contrario
    { 
        jugadasPosibles = malloc(sizeof(Ficha) * (jugador2->cantFichas * 8));
        // Nota: cada ficha tiene 8 tangentes, entonces el maximo del malloc debe ser 8 x cantFichas.

        for (int ficha = 0; ficha < jugador2->cantFichas; ficha++)
        {
            for (int columna = jugador2->fichasJugadas[ficha].x - 1; columna <= jugador2->fichasJugadas[ficha].x + 1; columna++)
            {
                for (int fila = jugador2->fichasJugadas[ficha].y - 1 ; fila <= jugador2->fichasJugadas[ficha].y + 1; fila++)
                {
                    //printf("\nColumna: %d \nFila: %d", columna, fila);
                    //printf("Cantidad de jugadas del jugador 1: %d", jugador1->cantFichas);
                    Ficha fichaTangente = {columna, fila};

                    /* printf("\nocupada jugador 1: %d\n", ocupadaJugador(fichaTangente, jugador1));
                    printf("ocupada jugador 2: %d\n", ocupadaJugador(fichaTangente, jugador2));
                    printf("repetida: %d\n", repetida(fichaTangente, jugadasPosibles, cantFichasVecinas));
                    printf("genera cambios diagonal derecha: %d\n", generaDiagonalDer(fichaTangente, jugador1, jugador2, turno));
                    printf("genera cambios diagonal izquierda: %d\n", generaDiagonalIzq(fichaTangente, jugador1, jugador2, turno));
                    printf("genera cambios horizontal: %d\n", generaHorizontal(fichaTangente, jugador1, jugador2, turno));
                    printf("genera cambios vertical: %d\n", generaVertical(fichaTangente, jugador1, jugador2, turno)); */

                    if ((1 <= columna <= 8) && (1 <= fila <= 8) && (ocupadaJugador(fichaTangente, jugador1) == 0) && (ocupadaJugador(fichaTangente, jugador2) == 0) && (repetida(fichaTangente, jugadasPosibles, cantFichasVecinas) == 0) && (generaCambios(turno, fichaTangente, jugador1, jugador2) == 0))
                    {
                        //printf("\n===LA FICHA ES VALIDA===\n");
                        jugadasPosibles[cantFichasVecinas] = fichaTangente;
                        cantFichasVecinas++;
                    }
                    else 
                    {
                        //printf("\n===LA FICHA ES INVALIDA===\n");
                    }
                }
            }
        }

        *cantJugadasPosibles = cantFichasVecinas;
        jugadasPosibles = realloc(jugadasPosibles, sizeof(Ficha) * cantFichasVecinas);    
        // Nota: Si el malloc no llegase a ocupar todos sus espacios, lo achica con la cantidad de fichas tangentes obtenidas.
        // Si no hay fichas jugables, el apuntador devuelve NULL, ya que cantFichasVecinas seria 0.
    }

    else
    {

        jugadasPosibles = malloc(sizeof(Ficha) * (jugador1->cantFichas * 8));
        // Nota: cada ficha tiene 8 tangentes, entonces el maximo del malloc debe ser 8 x cantFichas.

        for (int ficha = 0; ficha < jugador1->cantFichas; ficha++)
        {
            for (int columna = jugador1->fichasJugadas[ficha].x - 1; columna <= jugador1->fichasJugadas[ficha].x + 1; columna++)
            {
                for (int fila = jugador1->fichasJugadas[ficha].y - 1 ; fila <= jugador1->fichasJugadas[ficha].y + 1; fila++)
                {
                    //printf("\nColumna: %d \nFila: %d", columna, fila);
                    //printf("Cantidad de jugadas del jugador 1: %d", jugador1->cantFichas);
                    Ficha fichaTangente = {columna, fila};

                    /* printf("\nocupada jugador 1: %d\n", ocupadaJugador(fichaTangente, jugador1));
                    printf("ocupada jugador 2: %d\n", ocupadaJugador(fichaTangente, jugador2));
                    printf("repetida: %d\n", repetida(fichaTangente, jugadasPosibles, cantFichasVecinas));
                    printf("genera cambios diagonal derecha: %d\n", generaDiagonalDer(fichaTangente, jugador1, jugador2, turno));
                    printf("genera cambios diagonal izquierda: %d\n", generaDiagonalIzq(fichaTangente, jugador1, jugador2, turno));
                    printf("genera cambios horizontal: %d\n", generaHorizontal(fichaTangente, jugador1, jugador2, turno));
                    printf("genera cambios vertical: %d\n", generaVertical(fichaTangente, jugador1, jugador2, turno)); */

                    if ((1 <= columna <= 8) && (1 <= fila <= 8) && (ocupadaJugador(fichaTangente, jugador1) == 0) && (ocupadaJugador(fichaTangente, jugador2) == 0) && (repetida(fichaTangente, jugadasPosibles, cantFichasVecinas) == 0) && (generaCambios(turno, fichaTangente, jugador1, jugador2) == 0))
                    {
                        //printf("\n===LA FICHA ES VALIDA===\n");
                        jugadasPosibles[cantFichasVecinas] = fichaTangente;
                        cantFichasVecinas++;
                    }
                    else 
                    {
                        //printf("\n===LA FICHA ES INVALIDA===\n");
                    }
                }
            }
        }
        *cantJugadasPosibles = cantFichasVecinas;
        jugadasPosibles = realloc(jugadasPosibles, sizeof(Ficha) * cantFichasVecinas);    
        // Nota: Si el malloc no llegase a ocupar todos sus espacios, lo achica con la cantidad de fichas tangentes obtenidas.
        // Si no hay fichas jugables, el apuntador devuelve NULL, ya que cantFichasVecinas seria 0.
    }
}

