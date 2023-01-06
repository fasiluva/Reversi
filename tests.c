#include <assert.h>
#include "archivos.c"
#include "jugadores.c"
#include "jugadas.c"
#include "fichas.c"

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
    
    assert(transformaFicha(jugada2) == 34);
    assert(transformaFicha(jugada1) == 65);
    assert(transformaFicha(jugada3) == "La jugada esta fuera del rango.");
    assert(transformaFicha(jugada4) == "La jugada debe tener un tamanio de 2 caracteres.");
    assert(transformaFicha(jugada5) == "El formato de la jugada es incorrecto.");
    
    // =========================================================================== jugadores.c
    
    assert(colorValido(colorB) == 0);
    assert(colorValido('t') == 1);

    assert(mismosColores(colorB, colorN) == 0);
    assert(mismosColores(colorN, colorN) == 1);
   
    // =========================================================================== jugadas.c

    jugador1->fichasJugadas = fichasIniciales(colorB);
    jugador2->fichasJugadas = fichasIniciales(colorN);

    assert(actualizarJugadasPosibles(colorN, jugador1, jugador2, &cantJugadasPosibles));
    assert(actualizarJugadasPosibles(colorB, jugador1, jugador2, &cantJugadasPosibles));

    return 0;
}
