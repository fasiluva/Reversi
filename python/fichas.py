
def fichaFormato(jugada):

    if len(jugada) != 2: # No verifica que tenga dos coordenadas 
        return False
    
    columna, fila = jugada[0], jugada[1]
        
    if not columna.isalpha(): # No verifica que la columna sea una letra
        return False

    if not fila.isdigit(): # No verifica que la fila sea un número
        return False

    return True


def transformaAFicha(jugada):

    columnas = ['A','B','C','D','E','F','G','H']

    columna = jugada[0].upper()
    fila = int(jugada[1])

    columnaEquivalente = columnas.index(columna) + 1
    filaEquivalente = fila 

    return (columnaEquivalente,filaEquivalente)


def fichaRango(jugada):

    columnas = ['A','B','C','D','E','F','G','H']

    columna = jugada[0].upper()
    fila = int(jugada[1])

    return (columna in columnas) and (1 <= fila <= 8)

