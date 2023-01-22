
def colorContrario(color):

    # colorContrario :: string -> string
    # Devuelve el color contrario al que se ingreso.

    return 'B' if color == 'N' else 'N'

def datosArchivo(nombreArchivo, colorJugador, colorMaquina):

    # datosArchivo :: string string string -> set((int, int)) set((int, int)) string
    # Recibe el nombre del archivo, lo abre y analiza casilla por casilla a que jugador
    # le pertenece, asignando cada una a conjuntos de tuplas diferentes. La ultima linea 
    # es devuelta indicando que color inicia.

    archivo = open(nombreArchivo, 'r')

    fichasJugador = set()
    fichasMaquina = set()

    fila = 1

    while fila <= 8:

        linea = archivo.readline() # Lee la linea

        columna = 1

        while columna <= 8:

            if linea[columna-1] == colorJugador:

                fichasJugador.update({(columna, fila)}) # Aniade la ficha al jugador
            
            elif linea[columna-1] == colorMaquina:

                fichasMaquina.update({(columna, fila)}) # Aniade la ficha a la maquina
            
            columna += 1
        
        fila += 1

    colorInicia = archivo.readline() # Ultima linea: color que inicia

    archivo.close()

    return fichasJugador,fichasMaquina,colorInicia