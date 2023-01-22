
def fichaFormato(jugada):

    # fichaFormato :: string -> bool
    # Analiza si la jugada contiene 2 caracteres, si el segundo caracter
    # es una letra y si el primer caracter es un numero.

    if len(jugada) != 2: 
        return False
    
    columna, fila = jugada[0], jugada[1]
        
    if not columna.isalpha(): 
        return False

    if not fila.isdigit(): 
        return False

    return True


def stringAFicha(jugada):

    # stringAFicha :: string -> (int, int)
    # Recibe una jugada ingresada y devuelve su version en forma de tupla

    columnas = ['A','B','C','D','E','F','G','H']

    columna = jugada[0].upper()
    fila = int(jugada[1])

    columnaEquivalente = columnas.index(columna) + 1
    filaEquivalente = fila 

    return (columnaEquivalente,filaEquivalente)


def fichaAString(jugada):

    # fichaAString :: tupla -> string
    # Recibe una jugada y devuelve su version en forma de string.

    columnas = ['A','B','C','D','E','F','G','H']

    columna = columnas[jugada[0] - 1]
    fila = (str)(jugada[1])

    return columna + fila


def fichaRango(jugada):

    # fichaRango :: string -> bool
    # Recibe una jugada y devuelve True si esta dentro del tablero.

    columnas = ['A','B','C','D','E','F','G','H']

    columna = jugada[0].upper()
    fila = int(jugada[1])

    return (columna in columnas) and (1 <= fila <= 8)

