
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivos.c"

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
        
        

    }
    else {
        printf("El programa no puede iniciar porque debe ingresar UN archivo de jugadas.");
    }

    fclose(archivo);
    return 0;
}

// scanf("%[^\n]", B_nombre); 