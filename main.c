
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivos.c"
#include "jugadores.c"

int main (int argc , char * argv [])
{

    if (argc == 2) {
        
        FILE * archivo = fopen(argv[1], "r"); // Intenta abrir el archivo ingresado como parametro.

        while (archivo == NULL) {

            printf("\nEl archivo no fue encontrado. Intente reescribirlo: ");
            scanf("%s", argv[1]);
            archivo = reingresaArchivo(argv[1]);

        }

        printf("\n=== Archivo encontrado correctamente. Chequeando condiciones preliminares... ===\n");

        char linea[25];
        fgets(linea, 25, archivo);
        printf("Linea: %s\n", linea);

        if (colorValido(linea[(strlen(linea) - 2)]) == 1)
        {
            printf("El color del jugador 1 es invalido.");
            return 1; 
        }
        // printf("El color del jugador 1 es valido.");
        
        Jugador * jugador1;
        
        jugador1->color = linea[(strlen(linea) - 2)];
        printf("El color del jugador 1 es %c\n", jugador1->color);

        fgets(linea, 25, archivo); // Siguiente linea: jugador2, color
        printf("Linea: %s\n", linea);

        if (colorValido(linea[(strlen(linea) - 2)]) == 1)
        {
            printf("El color del jugador 2 es invalido."); 
            return 1;
        }
        
        Jugador * jugador2;
        
        jugador2->color = linea[(strlen(linea) - 2)];

        printf("El color del jugador 2 es %c\n", jugador2->color);
        
        if (mismosColores(jugador1->color, jugador2->color) == 1)
        {
            printf("Los colores de los jugadores no pueden ser iguales.");
            return 1;
        }
        else {printf("Todo correcto");}
        fclose(archivo);
    }

    else {
        printf("El programa no puede iniciar porque debe ingresar UN archivo de jugadas.");
    }


    return 0;
}

// scanf("%[^\n]", B_nombre); 