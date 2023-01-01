from fichas import normalizarLectura

def verificaDatos(archivo):
    """
    verificaDatos :: file -> bool

    Recibe el archivo y devuelve true si los colores de ambos no son los mismos y si son B O N, 
    y si el color de inicio es B o N. Sino, devuelve false, indicando que el juego no puede iniciar.
    """

    linea = normalizarLectura(archivo.readline()) # linea 1 (jugador 1)

    jugador1 = jugador(linea)
 
    linea = normalizarLectura(archivo.readline()) # linea 2 (jugador 2)

    jugador2 = jugador(linea)
    
    linea = normalizarLectura(archivo.readline()) # linea 3 (color que inicia)
   
    if not coloresCorrectos(jugador1, jugador2): 
        return False

    if linea != 'N' and linea != 'B': 
        print('El color que inicia es invalido.')
        return False
    
    return True 



def jugador(linea):
    """
    jugador :: str -> (string, string)

    Dado un string, lo divide y devuelve una tupla (nombre, color).
    """

    nombre,color = linea.split(',')

    return nombre,color    



def coloresCorrectos(jugador1, jugador2):
    """
    coloresCorrectos :: (str, str), (str, str) -> bool

    La función toma dos jugadores, y si los colores son diferentes, y son N o B, 
    entonces devuelve True, que significa que los colores son validos, sino devuelve False.
    """
    
    # Verificamos colores del primer jugador
    if jugador1[1] != 'N' and jugador1[1] != 'B':
        print("El color del primer jugador no es válido.")
        return False

    # Verificamos colores del segundo jugador
    if jugador2[1] != 'N' and jugador2[1] != 'B':
        print("El color del segundo jugador no es válido.")
        return False
    
    if jugador1[1] == jugador2[1]:
        print("Los colores de los jugadores son iguales.")
        return False

    return True
