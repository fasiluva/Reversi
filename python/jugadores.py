
def colorContrario(color):

    return 'B' if color == 'N' else 'N'

def datosArchivo(nombreArchivo, colorJugador, colorMaquina):

    archivo = open(nombreArchivo, 'r')

    fichasJugador = set()
    fichasMaquina = set()

    fila = 1

    while fila <= 8:

        linea = archivo.readline()

        columna = 1

        while columna <= 8:

            if linea[columna] == colorJugador:

                fichasJugador.update({(columna, fila)})
            
            elif linea[columna] == colorMaquina:

                fichasMaquina.update({(columna, fila)})
            
            columna += 1
        
        fila += 1

    colorInicia = archivo.readline()

    archivo.close()

    return fichasJugador,fichasMaquina,colorInicia