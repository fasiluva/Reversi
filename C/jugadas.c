
char cambiaTurno(char turno);
int ocupadaJugador(Ficha, Jugador *);
int generaHorizontal(Ficha, Jugador *, Jugador *, char);
int generaVertical(Ficha, Jugador *, Jugador *, char);
int generaDiagonalSup(Ficha, Jugador *, Jugador *, char);
int generaDiagonalInf(Ficha, Jugador *, Jugador *, char);
int actualizarJugadasPosibles(char, Jugador *, Jugador *);
int generaCambios(char, Ficha, Jugador *, Jugador *);
int jugadaCorrecta (char *, Jugador *, Jugador *, int, char);
void modificaFichas (Ficha, Jugador *, Jugador *, char);
void modificaHorizontal(Ficha, Jugador *, Jugador *);
void modificaVertical(Ficha, Jugador *, Jugador *);
void modificaDiagonalSup(Ficha, Jugador *, Jugador *);
void modificaDiagonalInf(Ficha, Jugador *, Jugador *);
void removerFicha(Ficha, Jugador *);
void aniadirFicha(Ficha, Jugador *);
void mensajeError(Ficha, char *, char, char *);


void mensajeError(Ficha jugadaFicha, char * jugadaString, char turno, char * error)
{
    // mensajeError :: Ficha, char *, char, char * -> None
    // Dado una jugada hecha (en su formato Ficha y String), el turno, y el tipo de error, 
    // imprime por consola el error cometido por el jugador y en que ficha se cometio.

    printf("\n============================ ERROR ============================\n\n");
    printf("Error cometido por el jugador de fichas: %c, en la jugada: %s", turno, jugadaString);

    if (error == "rango")
    {
        printf("\n !!! LA JUGADA SE SALE DEL RANGO DEL TABLERO !!!\n");
    }
    
    else if (error == "formato")
    {
        printf("\n !!! EL FORMATO DE LA JUGADA ES INCORRECTO !!!\n");
    }

    else if (error == "salteo")
    {
        printf("\n !!! EL TURNO FUE SALTEADO HABIENDO JUGADAS POSIBLES !!!\n");
    }

    else if (error == "ocupada")
    {
        printf("\n !!! LA JUGADA ESTA EN UNA POSICION OCUPADA !!!\n");
    }
    
    else if (error == "imposible")
    {
        printf("\n !!! LA JUGADA NO ESTA DENTRO DE LAS JUGADAS POSIBLES !!!\n");
    }

    printf("\n============================ ERROR ============================\n\n");

}


char cambiaTurno(char turno)
{
    // cambiaTurno :: char -> char
    // Recibe un turno en forma de char y devuelve el contrario
    return (turno == 'B') ? 'N' : 'B';
}


void aniadirFicha(Ficha casillaAniadir, Jugador * jugadorTurno)
{
    // aniadirFicha :: Ficha, Jugador * -> None
    // Recibe una ficha y el jugador de turno y añade dicha ficha a sus jugadas hechas,
    // aumenta la cantidad de fichas jugadas y expande el espacio del espacio de memoria que aloja
    // las jugadas. 

    jugadorTurno->cantFichas++;
    jugadorTurno->fichasJugadas = realloc(jugadorTurno->fichasJugadas, sizeof(Ficha) * (jugadorTurno->cantFichas));
    jugadorTurno->fichasJugadas[jugadorTurno->cantFichas - 1] = casillaAniadir; 

}


void removerFicha(Ficha casillaCambiar, Jugador * jugadorCambiaFichas)
{
    // removerFicha :: Ficha, Jugador * -> None
    // Dada una ficha y el jugador que no es de turno, elimina dicha ficha de sus jugadas. Para ello,
    // busca dicha ficha entre sus jugadas y cuando la encuentra, sobreescribe las siguientes fichas
    // con la posicion siguiente a las mismas, de modo que su tamanio disminuye en 1, asi como sus
    // fichas jugadas

    for (int i = 0; i < jugadorCambiaFichas->cantFichas; i++)
    {
        if (jugadorCambiaFichas->fichasJugadas[i].x == casillaCambiar.x && jugadorCambiaFichas->fichasJugadas[i].y == casillaCambiar.y)
        {
            for (int j = i; j < jugadorCambiaFichas->cantFichas - 1; j++)
            {
                jugadorCambiaFichas->fichasJugadas[j] = jugadorCambiaFichas->fichasJugadas[j + 1]; 
            }
            
            jugadorCambiaFichas->cantFichas--;
            jugadorCambiaFichas->fichasJugadas = realloc(jugadorCambiaFichas->fichasJugadas, sizeof(Ficha) * jugadorCambiaFichas->cantFichas);

        }
        
    }

}


int ocupadaJugador(Ficha casilla, Jugador * jugadorX)
{
    // ocupadaJugador :: Ficha, Jugador * -> int
    // Dada una ficha y un jugador, chequea si la ficha esta dentro de las fichas 
    // jugadas por el jugador. En caso de estarlo, devuelve 1, sino un 0 es devuelto

    for (int i = 0; i < jugadorX->cantFichas; i++) if ((jugadorX->fichasJugadas[i].x == casilla.x) && (jugadorX->fichasJugadas[i].y == casilla.y)) return 1;
    return 0;

}


void modificaDiagonalSup(Ficha jugadaHecha, Jugador * jugadorCambiaFichas, Jugador * jugadorTurno)
{
    // modificaDiagonalSup :: Ficha, Jugador *, Jugador * -> None 
    // Recibe una ficha, el jugador de turno y el jugador contrario y analiza si la ficha realiza
    // cambios en el tablero en la diagonal superior trazada desde dicha ficha. En caso de 
    // hacerlo, aniade las fichas al jugador de turno y las elimina del jugador contrario.

    int contadorFila = jugadaHecha.y - 1;
    int contadorColumna = jugadaHecha.x + 1;

    for (; contadorFila >= 1 && contadorColumna <= 8; contadorColumna++, contadorFila--)
    {
        
        Ficha casillaActual = {contadorColumna, contadorFila};

        if ((contadorColumna == jugadaHecha.x + 1) && (contadorFila = jugadaHecha.y - 1) && (ocupadaJugador(casillaActual, jugadorTurno) == 1)) contadorColumna = 9;
        else
        {

            if ((ocupadaJugador(casillaActual, jugadorCambiaFichas) == 0) && (ocupadaJugador(casillaActual, jugadorTurno) == 0)) contadorColumna = 9;

            if (ocupadaJugador(casillaActual, jugadorTurno) == 1)
            {

                int filaJugada = jugadaHecha.y - 1;
                int columnaJugada = jugadaHecha.x + 1;

                for (; columnaJugada < contadorColumna && filaJugada > contadorFila; columnaJugada++, filaJugada--) // Añade las fichas que encierra hacia la derecha 
                {
                    Ficha casillaCambiar = {columnaJugada, filaJugada};
                    
                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);
                }

                contadorColumna = 9;

            }

        }

    }

    contadorFila = jugadaHecha.y + 1;
    contadorColumna = jugadaHecha.x - 1;

    for (; contadorFila <= 8 && contadorColumna >= 1; contadorColumna--, contadorFila++)
    {
        
        Ficha casillaActual = {contadorColumna, contadorFila};

        if ((contadorColumna == jugadaHecha.x - 1) && (contadorFila = jugadaHecha.y + 1) && (ocupadaJugador(casillaActual, jugadorTurno) == 1)) contadorColumna = 0;
        else
        {

            if ((ocupadaJugador(casillaActual, jugadorCambiaFichas) == 0) && (ocupadaJugador(casillaActual, jugadorTurno) == 0)) contadorColumna = 0;

            if (ocupadaJugador(casillaActual, jugadorTurno) == 1)
            {

                int filaJugada = jugadaHecha.y + 1;
                int columnaJugada = jugadaHecha.x - 1;

                for (; columnaJugada > contadorColumna && filaJugada < contadorFila; columnaJugada--, filaJugada++) // Añade las fichas que encierra hacia la derecha 
                {
                    Ficha casillaCambiar = {columnaJugada, filaJugada};
                    
                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);
                }

                contadorColumna = 0;

            }

        }

    }

}


void modificaDiagonalInf(Ficha jugadaHecha, Jugador * jugadorCambiaFichas, Jugador * jugadorTurno)
{
    // modificaDiagonalSup :: Ficha, Jugador *, Jugador * -> None 
    // Recibe una ficha, el jugador de turno y el jugador contrario y analiza si la ficha realiza
    // cambios en el tablero en la diagonal inferior trazada desde dicha ficha. En caso de 
    // hacerlo, aniade las fichas al jugador de turno y las elimina del jugador contrario.

    int contadorFila = jugadaHecha.y + 1;
    int contadorColumna = jugadaHecha.x + 1;

    for (; contadorFila <= 8 && contadorColumna <= 8; contadorColumna++, contadorFila++)
    {
        
        Ficha casillaActual = {contadorColumna, contadorFila};

        if ((contadorColumna == jugadaHecha.x + 1) && (contadorFila = jugadaHecha.y + 1) && (ocupadaJugador(casillaActual, jugadorTurno) == 1)) contadorColumna = 9;
        else
        {

            if ((ocupadaJugador(casillaActual, jugadorCambiaFichas) == 0) && (ocupadaJugador(casillaActual, jugadorTurno) == 0)) contadorColumna = 9;

            else if (ocupadaJugador(casillaActual, jugadorTurno) == 1)
            {

                int filaJugada = jugadaHecha.y + 1;
                int columnaJugada = jugadaHecha.x + 1;

                for (; columnaJugada < contadorColumna && filaJugada < contadorFila; columnaJugada++, filaJugada++) // Añade las fichas que encierra hacia la derecha 
                {
                    Ficha casillaCambiar = {columnaJugada, filaJugada};
                    
                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);
                }

                contadorColumna = 9;

            }

        }

    }

    contadorFila = jugadaHecha.y - 1;
    contadorColumna = jugadaHecha.x - 1;

    for (; contadorFila >= 1 && contadorColumna >= 1; contadorColumna--, contadorFila--)
    {
        
        Ficha casillaActual = {contadorColumna, contadorFila};

        if ((contadorColumna == jugadaHecha.x - 1) && (contadorFila = jugadaHecha.y - 1) && (ocupadaJugador(casillaActual, jugadorTurno) == 1)) contadorColumna = 0;
        else
        {

            if ((ocupadaJugador(casillaActual, jugadorCambiaFichas) == 0) && (ocupadaJugador(casillaActual, jugadorTurno) == 0)) contadorColumna = 0;

            if (ocupadaJugador(casillaActual, jugadorTurno) == 1)
            {

                int filaJugada = jugadaHecha.y - 1;
                int columnaJugada = jugadaHecha.x - 1;

                for (; columnaJugada > contadorColumna && filaJugada > contadorFila; columnaJugada--, filaJugada--) // Añade las fichas que encierra hacia la derecha 
                {
                    Ficha casillaCambiar = {columnaJugada, filaJugada};

                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);
                }

                contadorColumna = 0;

            }

        }

    }

}


void modificaVertical (Ficha jugadaHecha, Jugador * jugadorCambiaFichas, Jugador * jugadorTurno)
{
    // modificaDiagonalSup :: Ficha, Jugador *, Jugador * -> None 
    // Recibe una ficha, el jugador de turno y el jugador contrario y analiza si la ficha realiza
    // cambios en el tablero verticalmente. En caso de hacerlo, aniade las fichas al jugador de 
    // turno y las elimina del jugador contrario.

    for (int contadorArriba = jugadaHecha.y - 1; contadorArriba >= 1; contadorArriba--)
    {

        Ficha casillaActual = {jugadaHecha.x, contadorArriba};

        if ((contadorArriba == jugadaHecha.y - 1) && (ocupadaJugador(casillaActual, jugadorTurno) == 1)) contadorArriba = 0;
        else
        {
            
            if (ocupadaJugador(casillaActual, jugadorCambiaFichas) == 0 && ocupadaJugador(casillaActual, jugadorTurno) == 0) contadorArriba = 0;
            
            if (ocupadaJugador(casillaActual, jugadorTurno) == 1)
            {

                for (int i = jugadaHecha.y - 1; i > contadorArriba; i--) // Añade las fichas que encierra hacia la derecha 
                {
                    Ficha casillaCambiar = {jugadaHecha.x, i};
                    
                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);
                }
                
                contadorArriba = 0;

            }

        }

    }
    
    for (int contadorAbajo = jugadaHecha.y + 1; contadorAbajo <= 8; contadorAbajo++)
    {
        
        Ficha casillaActual = {jugadaHecha.x, contadorAbajo};

        if ((contadorAbajo == jugadaHecha.y + 1) && (ocupadaJugador(casillaActual, jugadorTurno) == 1)) contadorAbajo = 9;
        else
        {
            
            if (ocupadaJugador(casillaActual, jugadorCambiaFichas) == 0 && ocupadaJugador(casillaActual, jugadorTurno) == 0) contadorAbajo = 9;
            
            if (ocupadaJugador(casillaActual, jugadorTurno) == 1)
            {

                for (int i = jugadaHecha.y + 1; i < contadorAbajo; i++) // Añade las fichas que encierra hacia la derecha 
                {
                    Ficha casillaCambiar = {jugadaHecha.x, i};
                    
                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);
                }
                
                contadorAbajo = 9;

            }

        }

    }
    

}


void modificaHorizontal(Ficha jugadaHecha, Jugador * jugadorCambiaFichas, Jugador * jugadorTurno)
{
    // modificaDiagonalSup :: Ficha, Jugador *, Jugador * -> None 
    // Recibe una ficha, el jugador de turno y el jugador contrario y analiza si la ficha realiza
    // cambios en el tablero horizontalmente. En caso de hacerlo, aniade las fichas al jugador de 
    // turno y las elimina del jugador contrario.

    for (int contadorDerecha = jugadaHecha.x + 1; contadorDerecha <= 8; contadorDerecha++)
    {
        
        Ficha casillaActual = {contadorDerecha, jugadaHecha.y};

        if ((contadorDerecha == jugadaHecha.x + 1) && (ocupadaJugador(casillaActual, jugadorTurno) == 1)) contadorDerecha = 9;
        else
        {
            if (ocupadaJugador(casillaActual, jugadorCambiaFichas) == 0 && ocupadaJugador(casillaActual, jugadorTurno) == 0) contadorDerecha = 9;
            
            if (ocupadaJugador(casillaActual, jugadorTurno) == 1)
            {

                for (int i = jugadaHecha.x + 1; i < contadorDerecha; i++) // Añade las fichas que encierra hacia la derecha 
                {
                    Ficha casillaCambiar = {i, jugadaHecha.y};
                    
                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);
                }

                contadorDerecha = 9;
                
            }
        
        }

    }
    
    for (int contadorIzquierda = jugadaHecha.x - 1; contadorIzquierda >= 1; contadorIzquierda--)
    {
        
        Ficha casillaActual = {contadorIzquierda, jugadaHecha.y};

        if ((contadorIzquierda == jugadaHecha.x - 1) && (ocupadaJugador(casillaActual, jugadorTurno) == 1)) contadorIzquierda = 0;
        else
        {
            if (ocupadaJugador(casillaActual, jugadorCambiaFichas) == 0 && ocupadaJugador(casillaActual, jugadorTurno) == 0) contadorIzquierda = 0;
            
            if (ocupadaJugador(casillaActual, jugadorTurno) == 1)
            {
                
                for (int i = jugadaHecha.x - 1; i > contadorIzquierda; i--)
                {
                    Ficha casillaCambiar = {i, jugadaHecha.y};
                    removerFicha(casillaCambiar, jugadorCambiaFichas);
                    aniadirFicha(casillaCambiar, jugadorTurno);

                }

                contadorIzquierda = 0; 
            }
        
        }

    }

}


void modificaFichas(Ficha jugada, Jugador * jugador1, Jugador * jugador2, char turno)
{
    // modificaFichas :: Ficha, Jugador *, Jugador *, char -> None
    // Recibe la ficha, los jugadores y el turno, y segun el turno realiza los cambios en el tablero 
    // horizontal, vertical y digonalmente del jugador de turno. 

    if (jugador1->color == turno) // Si la jugada es del jugador 1, cambia las fichas del jugador 2, volviendolas del jugador 1
    {
        modificaHorizontal(jugada, jugador2, jugador1);
        modificaVertical(jugada, jugador2, jugador1);
        modificaDiagonalSup(jugada, jugador2, jugador1);
        modificaDiagonalInf(jugada, jugador2, jugador1);

        aniadirFicha(jugada, jugador1); // Aniade la ficha jugada
    }
    
    else // Si la jugada es del jugador 2, cambia las fichas del jugador 1, volviendolas del jugador 2
    {
        modificaHorizontal(jugada, jugador1, jugador2);
        modificaVertical(jugada, jugador1, jugador2);
        modificaDiagonalSup(jugada, jugador1, jugador2);
        modificaDiagonalInf(jugada, jugador1, jugador2);

        aniadirFicha(jugada, jugador2); // Aniade la ficha jugada
    }

}


int jugadaCorrecta(char * jugada, Jugador * jugador1, Jugador * jugador2, int cantJugadasPosibles, char turno)
{

    // jugadaCorrecta :: char *, Jugador *, Jugador *, int, char -> int
    // La funcion recibe la jugada en forma de string, los jugadores, las cantidad de jugadas posibles, y el turno
    // y en base a ello analiza si la jugada es correcta, siendo los errores posibles de la jugada: fuera de rango,
    // formato incorrecto, turno mal salteado, casilla ocupada y jugada no posible. En caso de uno de ellos, devuelve
    // 1. Si ningun error es cometido, devuelve 0.

    Ficha jugadaFicha = transformaFicha(jugada);

    switch (jugadaFicha.x)
    {
    
    case -2:
        mensajeError(jugadaFicha, jugada, turno, "rango");
        return 1;
        break;
    
    case -1:
        mensajeError(jugadaFicha, jugada, turno, "formato");
        return 1; 
        break;
   
    case 0:

        if (cantJugadasPosibles != 0)
        {    
        mensajeError(jugadaFicha, jugada, turno, "salteo");
        return 1; 
        }
        break;

    default:
       
        if (ocupadaJugador(jugadaFicha, jugador1) == 1 || ocupadaJugador(jugadaFicha, jugador2) == 1)
        {
            mensajeError(jugadaFicha, jugada, turno, "ocupada");
            return 1;
        }

        else if (generaCambios(turno, jugadaFicha, jugador1, jugador2) == 1)
        {
            mensajeError(jugadaFicha, jugada, turno, "imposible");
            return 1;
        }
        break;
        
    }
    
    return 0;
}


int actualizarJugadasPosibles(char turno, Jugador * jugador1, Jugador * jugador2)
{
    // actualizarJugadasPosibles :: char, Jugador *, Jugador * -> int
    // La funcion recibe el turno y los jugadores y devuelve 0 si no hay jugadas posibles para el jugador de turno,
    // sino devuelve 1

    if (jugador1->color == turno) // Si es el turno del color del jugador 1, analiza todas las fichas tangentes del color contrario
    { 

        for (int ficha = 0; ficha < jugador2->cantFichas; ficha++)
        {
            
            for (int columna = jugador2->fichasJugadas[ficha].x - 1; columna <= jugador2->fichasJugadas[ficha].x + 1; columna++)
            {
            
                for (int fila = jugador2->fichasJugadas[ficha].y - 1 ; fila <= jugador2->fichasJugadas[ficha].y + 1; fila++)
                {

                    Ficha fichaTangente = {columna, fila};

                    if ((1 <= columna <= 8) && (1 <= fila <= 8) && (ocupadaJugador(fichaTangente, jugador1) == 0) && (ocupadaJugador(fichaTangente, jugador2) == 0) && (generaCambios(turno, fichaTangente, jugador1, jugador2) == 0))
                    {
                        return 1; // Hay al menos una jugada posible
                    }
            
                }
            
            }
        
        }

    }

    else
    {

        for (int ficha = 0; ficha < jugador1->cantFichas; ficha++)
        {
            for (int columna = jugador1->fichasJugadas[ficha].x - 1; columna <= jugador1->fichasJugadas[ficha].x + 1; columna++)
            {
                for (int fila = jugador1->fichasJugadas[ficha].y - 1 ; fila <= jugador1->fichasJugadas[ficha].y + 1; fila++)
                {

                    Ficha fichaTangente = {columna, fila};

                    if ((1 <= columna <= 8) && (1 <= fila <= 8) && (ocupadaJugador(fichaTangente, jugador1) == 0) && (ocupadaJugador(fichaTangente, jugador2) == 0) && (generaCambios(turno, fichaTangente, jugador1, jugador2) == 0))
                    {
                        return 1; // Hay al menos una jugada posible
                    }
        
                }
        
            }
        
        }
        
    }

    return 0; // No hay jugadas posibles

}


int generaVertical(Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2, char turno)
{
    // generaVertical :: Ficha, Jugador *, Jugador *, char -> int
    // Reciba la ficha, los jugadores y el turno, analiza si la jugada genera cambios en el tablero
    // de manera vertical a la ficha. Si genera cambios, devuelve 0, sino devuelve 1.
    
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

            if ((contadorAbajo == fichaTangente.y + 1) && (ocupadaJugador(casilla, jugador1) == 1)) contadorAbajo = 9;
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
    // generaHorizontal :: Ficha, Jugador *, Jugador *, char -> int
    // Reciba la ficha, los jugadores y el turno, analiza si la jugada genera cambios en el tablero
    // de manera horizontal a la ficha. Si genera cambios, devuelve 0, sino devuelve 1.

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


int generaDiagonalSup(Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2, char turno)
{
    // generaDiagonalSup :: Ficha, Jugador *, Jugador *, char -> int
    // Reciba la ficha, los jugadores y el turno, analiza si la jugada genera cambios en el tablero
    // de manera diagonal superiormente a la ficha. Si genera cambios, devuelve 0, sino devuelve 1.

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


int generaDiagonalInf(Ficha fichaTangente, Jugador * jugador1, Jugador * jugador2, char turno)
{
    // generaDiagonalInf :: Ficha, Jugador *, Jugador *, char -> int
    // Reciba la ficha, los jugadores y el turno, analiza si la jugada genera cambios en el tablero
    // de manera diagonal inferiormente a la ficha. Si genera cambios, devuelve 0, sino devuelve 1.

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
    // generaCambios :: char, Ficha, Jugador *, Jugador * -> int
    // Recibe el turno, la ficha y los jugadores y devuelve 0 si la ficha genera algun cambio
    // en el tablero en cualquier sentido sea. Sino, devuelve 1.

    if (generaHorizontal(fichaTangente, jugador1, jugador2, turno) == 0 || generaVertical(fichaTangente, jugador1, jugador2, turno) == 0 || generaDiagonalSup(fichaTangente, jugador1, jugador2, turno) == 0 || generaDiagonalInf(fichaTangente, jugador1, jugador2, turno) == 0) return 0;
    
    return 1;

}

