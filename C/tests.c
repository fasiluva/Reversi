#include <assert.h>
#include "tablero.c"
#include "archivos.c"

#define cantFichasPosibles 5

int main(int argc, char const *argv[])
{
    Jugador * jugador1, * jugador2, * jugador3, * jugador4;

    int cantJugadasPosibles;

    char jugada1[] = "F5 ";
    char jugada2[] = "C4 ";
    char jugada3[] = "45 ";
    char jugada4[] = "AA";
    char jugada5[] = "K4 ";

    char caracterInt1 = '5';
    char caracterInt2 = '0';

    char colorB = 'B';
    char colorN = 'N';

    // =========================================================================== archivos.c
    
    assert(reingresaArchivo("hola.txt") == NULL);
    assert(reingresaArchivo("counterstrike.dll") == NULL);
    assert(reingresaArchivo("hola como estan?") == NULL);
    
    //============================================================================= fichas.c
    
    assert(charInt(caracterInt1) == 5);
    assert(charInt(caracterInt2) == 0);

    Ficha ficha1 = {3, 4};
    Ficha ficha2 = {6, 5};
    Ficha falloFormato = {-1, -1};
    Ficha falloRango = {-2, -2};
    
    assert(transformaFicha(jugada2).x == ficha1.x);
    assert(transformaFicha(jugada2).y == ficha1.y);

    assert(transformaFicha(jugada1).x == ficha2.x);
    assert(transformaFicha(jugada1).y == ficha2.y);

    assert(transformaFicha(jugada3).x == falloRango.x);
    assert(transformaFicha(jugada3).y == falloRango.y);
    
    assert(transformaFicha(jugada4).x == falloFormato.x);
    assert(transformaFicha(jugada4).y == falloFormato.y);
    
    assert(transformaFicha(jugada5).x == falloRango.x);
    assert(transformaFicha(jugada5).y == falloRango.y);

    // =========================================================================== jugadores.c
    
    assert(colorValido(colorB) == 0);
    assert(colorValido('t') == 1);

    assert(mismosColores(colorB, colorN) == 0);
    assert(mismosColores(colorN, colorN) == 1);
   
    // =========================================================================== jugadas.c

    jugador1->color = 'B';
    jugador2->color = 'N';

    fichasIniciales(jugador1);
    fichasIniciales(jugador2);

    Ficha ficha3 = {4, 4};
    Ficha ficha4 = {5, 4};

    assert(ocupadaJugador(ficha3, jugador1) == 1);
    assert(ocupadaJugador(ficha1, jugador1) == 0);
    assert(ocupadaJugador(ficha3, jugador2) == 0);
    assert(ocupadaJugador(ficha4, jugador2) == 1);

    Ficha ficha5 = {4, 3};
    Ficha ficha6 = {5, 3};
    Ficha ficha7 = {3, 3};

    assert(cambiaTurno('B') == 'N');
    assert(cambiaTurno('N') == 'B');

    assert(generaVertical(ficha5, jugador1, jugador2, jugador2->color) == 0);
    assert(generaVertical(ficha1, jugador1, jugador2, jugador2->color) == 1);
    assert(generaVertical(ficha6, jugador1, jugador2, jugador2->color) == 1);

    assert(generaHorizontal(ficha1, jugador1, jugador2, jugador2->color) == 0);
    assert(generaHorizontal(ficha1, jugador1, jugador2, jugador1->color) == 1);

    assert(generaDiagonalSup(ficha7, jugador1, jugador2, jugador2->color) == 1);
    assert(generaDiagonalInf(ficha2, jugador1, jugador2, jugador1->color) == 1);

    assert(generaCambios(jugador2->color, ficha5, jugador1, jugador2) == 0);
    assert(generaCambios(jugador2->color, ficha7, jugador1, jugador2) == 1);

    Ficha * jugadasPosibles = malloc(sizeof(Ficha) * cantFichasPosibles);

    for (int i = 0; i < cantFichasPosibles; i++)
    {
        Ficha jugadaPosible = {i+1, i+3}; 
        jugadasPosibles[i] = jugadaPosible;
    } // {1, 3} {2, 4} {3, 5} {4, 6} {5, 7} {6, 8}
    
    Ficha ficha8 = {1,3};

    assert(jugadaCorrecta(jugada1, jugador1, jugador2, 2, jugador1->color) == 1);
    assert(jugadaCorrecta(jugada3, jugador1, jugador2, 4, jugador1->color) == 1);
    assert(jugadaCorrecta(jugada5, jugador1, jugador2, 5, jugador2->color) == 1);

    fichasIniciales(jugador1);
    fichasIniciales(jugador2);

    assert(actualizarJugadasPosibles('N', jugador1, jugador2) == 1);
    assert(actualizarJugadasPosibles('B', jugador1, jugador2) == 1);

    return 0;
}
