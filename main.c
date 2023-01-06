
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivos.c"
#include "jugadores.c"
#include "fichas.c"
#include "jugadas.c"

int main (int argc , char * argv [])
{

    if (argc == 2) {
        
        // =========================================================================== CONDICIONES PRELIMINARES DE ARCHIVO
        FILE * archivo = fopen(argv[1], "r"); // Intenta abrir el archivo ingresado como parametro.

        while (archivo == NULL) {

            printf("\nEl archivo no fue encontrado. Intente reescribirlo: ");
            scanf("%s", argv[1]);
            archivo = reingresaArchivo(argv[1]);

        }

        printf("\n=== Archivo encontrado correctamente. Chequeando condiciones preliminares... ===\n\n");

        // =========================================================================== CONDICIONES PRELIMINARES DE JUGADORES
        // --------------------------------------------------------------------------- LINEA 1
        char linea[25];
        fgets(linea, 25, archivo); // jugador1,color

        if (colorValido(linea[(strlen(linea) - 2)]) == 1)
        {
            printf("El color del jugador 1 es invalido.");
            return 1; // TERMINA
        }
        
        Jugador * jugador1 = malloc(sizeof(Jugador));
        
        jugador1->color = linea[(strlen(linea) - 2)];
        printf("El color del jugador 1 es %c\n", jugador1->color);

        // --------------------------------------------------------------------------- LINEA 2

        fgets(linea, 25, archivo); // jugador2,color

        if (colorValido(linea[(strlen(linea) - 2)]) == 1)
        {
            printf("El color del jugador 2 es invalido."); 
            return 1; // TERMINA
        }
        
        Jugador * jugador2 = malloc(sizeof(Jugador));
        
        jugador2->color = linea[(strlen(linea) - 2)];
        printf("El color del jugador 2 es %c\n\n", jugador2->color);

        // ----------------------------------------------------------------------------- CHEQUEO DE COLORES

        if (mismosColores(jugador1->color, jugador2->color) == 1)
        {
            printf("Los colores de los jugadores no pueden ser iguales.");
            return 1; // TERMINA
        }

        // --------------------------------------------------------------------------- LINEA 3

        fgets(linea, 25, archivo); // COLOR INICIAL
        // printf("Linea: %s", linea);
        if (colorValido(linea[0]) == 1) 
        {
            printf("El color inicial es invalido. ");
            return 1; // TERMINA
        }

        // =========================================================================== INICIO DEL JUEGO

        char turnoColor = linea[0]; 

        printf("Inicia el color: %c\n\n", turnoColor);

        int cantJugadasPosibles;

        fichasIniciales(jugador1);
        fichasIniciales(jugador2);

        printf("============================ INICIO DEL JUEGO =================================\n");

        Ficha * jugadasPosibles; 
        actualizarJugadasPosibles(turnoColor, jugador1, jugador2, &cantJugadasPosibles, jugadasPosibles); 
        
        for (int i = 0; i < 10; i++)
        {
            printf("\nJugada posible %i: %i\n", i+1, jugadasPosibles[i]); 
        }

        fclose(archivo);
    }

    else printf("El programa no puede iniciar porque debe ingresar UN archivo de jugadas.");

    return 0;
}
