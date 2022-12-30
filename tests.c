#include <assert.h>
#include "archivos.c"
// #include "main.c"

int main(int argc, char const *argv[])
{
    
    assert(reingresaArchivo("hola.txt") == NULL);
    assert(reingresaArchivo("counterstrike.dll") == NULL);
    assert(reingresaArchivo("hola como estan?") == NULL);

    return 0;
}
