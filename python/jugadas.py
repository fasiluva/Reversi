from random import randint, choice
from archivos import *
from fichas import *


def eligeFicha(jugadasPosibles, dificultad, fichasJugador, fichasMaquina):

    # eligeFicha :: set((int, int)) string set((int, int)) set((int, int)) -> (int, int)
    # La funcion recibe las jugadas posibles, las jugadas hechas por el jugador y la maquina y 
    # la dificultad del juego y elige una ficha a realizar. Si la dificultad es 0, la elige 
    # aleatoriamente. Si la dificultad es 1, evalua la cantidad de cambios que realizan todas las fichas
    # y elige la que mas cambios haga (o una de la que mas cambios haga, si hay mas de una).

    print("FICHAS POSIBLES: ", jugadasPosibles)
    print("FICHAS JUGADOR: ", fichasJugador)
    print("FICHAS MAQUINA: ", fichasMaquina)

    fichas = list(jugadasPosibles)

    if dificultad == '0':

        return fichas[randint(0, len(fichas) - 1)]

    else:

        cantVolteosFichas = []

        for ficha in fichas:

            cantVolteosFichas += [cantVolteadas(ficha, fichasJugador, fichasMaquina)]
            # Nota: con cada ficha que evalua de las jugadas posibles, añade la cantidad de fichas que cambia a una lista.

        print("VOLTEOS DE LAS FICHAS: ", cantVolteosFichas)
        print("FICHA ELEGIDA: ", fichas[cantVolteosFichas.index(max(cantVolteosFichas))])
        return fichas[cantVolteosFichas.index(max(cantVolteosFichas))]


def cantVolteadas(ficha, fichasJugador, fichasMaquina):
    
    # cantVolteadas :: (int, int) set((int, int)) set((int, int)) -> int
    # Recibe la jugada posible y devuelve la cantidad de volteos que hace en cada sentido 
    # posible.

    return cantVolteosVertical(ficha, fichasJugador, fichasMaquina) + cantVolteosHorizontal(ficha, fichasJugador, fichasMaquina) + cantVolteosDiagonalSup(ficha, fichasJugador, fichasMaquina) + cantVolteosDiagonalInf(ficha, fichasJugador, fichasMaquina)


def cantVolteosVertical(ficha, fichasJugador, fichasMaquina):

    # cantVolteosDiagonalSup :: (int, int) set((int, int)) set((int, int)) -> int
    # Recibe la ficha ingresada, las fichas del jugador y de la maquina y devuelve la cantidad
    # de fichas que voltea verticalmente del jugador.

    contadorFila = ficha[1] - 1
    contadorVolteosSuperior = 0
    contadorVolteosInferior = 0

    while contadorFila >= 1 and (ficha[0], contadorFila) in fichasJugador: # Cuenta hacia arriba
        
        contadorVolteosSuperior += 1
    
        if not ocupada((ficha[0], contadorFila - 1), fichasJugador, fichasMaquina):
            # Si la ficha siguiente a la que se esta evaluando esta vacia, no realiza ningun cambio.
            contadorVolteosSuperior = 0
        
        contadorFila -= 1


    contadorFila = ficha[1] + 1

    while contadorFila <= 8 and (ficha[0], contadorFila) in fichasJugador: # Cuenta hacia abajo
        
        contadorVolteosInferior += 1
    
        if not ocupada((ficha[0], contadorFila + 1), fichasJugador, fichasMaquina):
            # Si la ficha siguiente a la que se esta evaluando esta vacia, no realiza ningun cambio.
            contadorVolteosInferior = 0
        
        contadorFila += 1


    return contadorVolteosInferior + contadorVolteosSuperior


def cantVolteosHorizontal(ficha, fichasJugador, fichasMaquina):

    # cantVolteosDiagonalSup :: (int, int) set((int, int)) set((int, int)) -> int
    # Recibe la ficha ingresada, las fichas del jugador y de la maquina y devuelve la cantidad
    # de fichas que voltea horizontalmente del jugador.

    contadorColumna = ficha[0] - 1
    contadorVolteosDer = 0
    contadorVolteosIzq = 0

    while contadorColumna >= 1 and (contadorColumna, ficha[1]) in fichasJugador: # Cuenta hacia la izquierda

        contadorVolteosIzq += 1

        if not ocupada((contadorColumna - 1, ficha[1]), fichasJugador, fichasMaquina):
            # Si la ficha siguiente a la que se esta evaluando esta vacia, no realiza ningun cambio.
            contadorVolteosIzq = 0

        contadorColumna -= 1


    contadorColumna = ficha[0] + 1

    while contadorColumna <= 8 and (contadorColumna, ficha[1]) in fichasJugador: # Cuenta hacia la derecha
        
        contadorVolteosDer += 1        

        if not ocupada((contadorColumna + 1, ficha[1]), fichasJugador, fichasMaquina):
            # Si la ficha siguiente a la que se esta evaluando esta vacia, no realiza ningun cambio.
            contadorVolteosDer = 0

        contadorColumna += 1


    return contadorVolteosDer + contadorVolteosIzq


def cantVolteosDiagonalInf(ficha, fichasJugador, fichasMaquina):

    # cantVolteosDiagonalSup :: (int, int) set((int, int)) set((int, int)) -> int
    # Recibe la ficha ingresada, las fichas del jugador y de la maquina y devuelve la cantidad
    # de fichas que voltea diagonalemente (inferior) del jugador.

    contadorColumna = ficha[0] + 1
    contadorFila = ficha[1] + 1
    contadorVolteosIzq = 0
    contadorVolteosDer = 0

    while contadorColumna <= 8 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasJugador: # Cuenta hacia la derecha

        contadorVolteosDer += 1

        if not ocupada((contadorColumna + 1, contadorFila + 1), fichasJugador, fichasMaquina):
            # Si la ficha siguiente a la que se esta evaluando esta vacia, no realiza ningun cambio.
            contadorVolteosDer = 0
        
        contadorColumna += 1
        contadorFila += 1

    
    contadorColumna = ficha[0] - 1
    contadorFila = ficha[1] - 1

    while contadorColumna >= 1 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasJugador: # Cuenta hacia la izquierda

        contadorVolteosIzq += 1        

        if not ocupada((contadorColumna - 1, contadorFila - 1), fichasJugador, fichasMaquina):
            # Si la ficha siguiente a la que se esta evaluando esta vacia, no realiza ningun cambio.
            contadorVolteosIzq = 0

        contadorColumna -= 1
        contadorFila -= 1


    return contadorVolteosDer + contadorVolteosIzq


def cantVolteosDiagonalSup(ficha, fichasJugador, fichasMaquina):

    # cantVolteosDiagonalSup :: (int, int) set((int, int)) set((int, int)) -> int
    # Recibe la ficha ingresada, las fichas del jugador y de la maquina y devuelve la cantidad
    # de fichas que voltea diagonalemente (superior) del jugador.

    contadorColumna = ficha[0] + 1
    contadorFila = ficha[1] - 1
    contadorVolteosDer = 0
    contadorVolteosIzq = 0

    while contadorColumna <= 8 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasJugador: # Cuenta hacia la derecha

        contadorVolteosDer += 1
    
        if not ocupada((contadorColumna + 1, contadorFila - 1), fichasJugador, fichasMaquina):
            # Si la ficha siguiente a la que se esta evaluando esta vacia, no realiza ningun cambio.
            contadorVolteosDer = 0

        contadorColumna += 1
        contadorFila -= 1


    contadorColumna = ficha[0] - 1
    contadorFila = ficha[1] + 1

    while contadorColumna >= 1 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasJugador: # Cuenta hacia la izquierda

        contadorVolteosIzq += 1        

        if not ocupada((contadorColumna - 1, contadorFila + 1), fichasJugador, fichasMaquina):
            # Si la ficha siguiente a la que se esta evaluando esta vacia, no realiza ningun cambio.
            contadorVolteosIzq = 0

        contadorColumna -= 1
        contadorFila += 1


    return contadorVolteosDer + contadorVolteosIzq


def actualizaJugadasPosiblesJugador(fichasJugador, fichasMaquina):

    # actualizaJugadasPosiblesJugador :: set((int, int)) set((int, int)) -> bool
    # Analiza si existen jugadas posibles para el jugador. Si se encuentra MINIMO UNA
    # la funcion termina y devuelve True. Si no encuentra ninguna jugada posible devuelve 
    # False. El conteo lo hace de columna a columna (de izquierda a derecha) y de fila por fila
    # (de arriba a abajo).

    for ficha in fichasMaquina:

        columna = ficha[0] - 1 

        if columna < 1:
            columna += 1

        while columna <= 8 and columna <= ficha[0] + 1:

            fila = ficha[1] - 1

            if fila < 1:
                fila += 1

            while fila <= 8 and fila <= ficha[1] + 1:

                if fichaValida((columna, fila), fichasJugador, fichasMaquina, "jugador"):
                    
                    return True # Entonces (columna, fila) es una jugada valida.

                fila += 1
            
            columna += 1
                
    return False 


def actualizaJugadasPosiblesMaquina(fichasJugador, fichasMaquina):

    # actualizaJugadasPosiblesMaquina :: set((int, int)) set((int, int)) -> set((int, int))
    # Toma las fichas del jugador y de la maquina y devuelve las jugadas posibles de la maquina.

    fichasPosibles = set()

    for ficha in fichasJugador:

        columna = ficha[0] - 1

        if columna < 1:
            columna += 1

        while columna <= 8 and columna <= ficha[0] + 1:

            fila = ficha[1] - 1

            if fila < 1:
                fila += 1

            while fila <= 8 and fila <= ficha[1] + 1:

                if fichaValida((columna, fila), fichasJugador, fichasMaquina, "maquina"):

                    fichasPosibles.add((columna, fila))

                fila += 1
            
            columna += 1
    
    return fichasPosibles


def fichaValida(fichaVerifica, fichasJugador, fichasMaquina, turno):

    # fichaValida :: (int, int) set((int, int)) set((int, int)) string -> bool
    # Chequea que la ficha recibida sea valida para ser ingresada por el turno en cuestion.
    # Chequea que no este ocupada y genere cambios en el tablero.

    if not ocupada(fichaVerifica, fichasJugador, fichasMaquina) and generaCambios(fichaVerifica, fichasJugador, fichasMaquina, turno):

        return True
    
    return False


def ocupada(fichaVerifica, jugador, maquina):
    
    # ocupada :: (int, int) set((int, int)) set((int, int)) -> bool
    # Chequea que la ficha no este ocupada por ninguno de los 2 jugadores.

    return (fichaVerifica in jugador) or (fichaVerifica in maquina)
    

def generaCambios(fichaVerifica, fichasJugador, fichasMaquina, turno):

    # generaCambios :: (int, int) set((int, int)) set((int, int)) string -> bool
    # Analiza si la ficha genera cambios en el tablero. Con que genere en uno de los 
    # sentidos devuelve True, si no genera en ningun sentido devuelve False.

    if generaVertical(fichaVerifica, fichasJugador, fichasMaquina, turno) or generaHorizontal(fichaVerifica, fichasJugador, fichasMaquina, turno) or generaDiagonalSup(fichaVerifica, fichasJugador, fichasMaquina, turno) or generaDiagonalInf(fichaVerifica, fichasJugador, fichasMaquina, turno):

        return True
    
    return False


def generaDiagonalInf(fichaVerifica, fichasJugador, fichasMaquina, turno):

    # generaDiagonalSup :: (int, int) set((int, int)) set((int, int)) string -> bool
    # Analiza si la ficha genera cambios diagonalmente, hacia la derecha o hacia la izquierda. 
    # En caso de hacerlo en algun sentido, devuelve True.

    if turno == "jugador":

        contadorColumna = fichaVerifica[0] + 1
        contadorFila = fichaVerifica[1] + 1

        while contadorColumna <= 8 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasMaquina:

            if (contadorColumna + 1, contadorFila + 1) in fichasJugador:

                return True
            
            contadorColumna += 1
            contadorFila += 1
        

        contadorColumna = fichaVerifica[0] - 1
        contadorFila = fichaVerifica[1] - 1

        while contadorColumna >= 1 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasMaquina:

            if (contadorColumna - 1, contadorFila - 1) in fichasJugador:

                return True
            
            contadorColumna -= 1
            contadorFila -= 1


        return False

    else: 

        contadorColumna = fichaVerifica[0] + 1
        contadorFila = fichaVerifica[1] + 1

        while contadorColumna <= 8 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasJugador:

            if (contadorColumna + 1, contadorFila + 1) in fichasMaquina:

                return True
            
            contadorColumna += 1
            contadorFila += 1
        

        contadorColumna = fichaVerifica[0] - 1
        contadorFila = fichaVerifica[1] - 1

        while contadorColumna >= 1 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasJugador:

            if (contadorColumna - 1, contadorFila - 1) in fichasMaquina:

                return True
            
            contadorColumna -= 1
            contadorFila -= 1


        return False


def generaDiagonalSup(fichaVerifica, fichasJugador, fichasMaquina, turno):

    # generaDiagonalSup :: (int, int) set((int, int)) set((int, int)) string -> bool
    # Analiza si la ficha genera cambios diagonalmente, hacia la derecha o hacia la izquierda. 
    # En caso de hacerlo en algun sentido, devuelve True.

    if turno == "jugador":

        contadorColumna = fichaVerifica[0] + 1
        contadorFila = fichaVerifica[1] - 1

        while contadorColumna <= 8 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasMaquina:

            if (contadorColumna + 1, contadorFila - 1) in fichasJugador:

                return True
            
            contadorColumna += 1
            contadorFila -= 1
        

        contadorColumna = fichaVerifica[0] - 1
        contadorFila = fichaVerifica[1] + 1

        while contadorColumna >= 1 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasMaquina:

            if (contadorColumna - 1, contadorFila + 1) in fichasJugador:

                return True
            
            contadorColumna -= 1
            contadorFila += 1


        return False

    else: 

        contadorColumna = fichaVerifica[0] + 1
        contadorFila = fichaVerifica[1] - 1

        while contadorColumna <= 8 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasJugador:

            if (contadorColumna + 1, contadorFila - 1) in fichasMaquina:

                return True
            
            contadorColumna += 1
            contadorFila -= 1
        

        contadorColumna = fichaVerifica[0] - 1
        contadorFila = fichaVerifica[1] + 1

        while contadorColumna >= 1 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasJugador:

            if (contadorColumna - 1, contadorFila + 1) in fichasMaquina:

                return True
            
            contadorColumna -= 1
            contadorFila += 1


        return False


def generaVertical(fichaVerifica, fichasJugador, fichasMaquina, turno):

    # generaVertical :: (int, int) set((int, int)) set((int, int)) string -> bool
    # Analiza si la ficha genera cambios verticalmente, hacia arriba o hacia abajo. 
    # En caso de hacerlo en algun sentido, devuelve True.

    if turno == "jugador":

        contadorFila = fichaVerifica[1] - 1

        while contadorFila >= 1 and (fichaVerifica[0], contadorFila) in fichasMaquina:

            if (fichaVerifica[0], contadorFila - 1) in fichasJugador:

                return True
            
            contadorFila -= 1


        contadorFila = fichaVerifica[1] + 1

        while contadorFila <= 8 and (fichaVerifica[0], contadorFila) in fichasMaquina:

            if (fichaVerifica[0], contadorFila + 1) in fichasJugador:

                return True
            
            contadorFila += 1
        
        return False

    else:

        contadorFila = fichaVerifica[1] - 1

        while contadorFila >= 1 and (fichaVerifica[0], contadorFila) in fichasJugador:

            if (fichaVerifica[0], contadorFila - 1) in fichasMaquina:

                return True
            
            contadorFila -= 1


        contadorFila = fichaVerifica[1] + 1

        while contadorFila <= 8 and (fichaVerifica[0], contadorFila) in fichasJugador:

            if (fichaVerifica[0], contadorFila + 1) in fichasMaquina:

                return True
            
            contadorFila += 1
        
        return False


def generaHorizontal(fichaVerifica, fichasJugador, fichasMaquina, turno):

    # generaHorizontal :: (int, int) set((int, int)) set((int, int)) string -> bool
    # Analiza si la ficha genera cambios horizontal, hacia la derecha o hacia la izquierda. 
    # En caso de hacerlo en algun sentido, devuelve True.

    if turno == "jugador":

        contadorColumna = fichaVerifica[0] - 1

        while contadorColumna >= 1 and (contadorColumna, fichaVerifica[1]) in fichasMaquina:

            if (contadorColumna - 1, fichaVerifica[1]) in fichasJugador:

                return True
            
            contadorColumna -= 1


        contadorColumna = fichaVerifica[0] + 1

        while contadorColumna <= 8 and (contadorColumna, fichaVerifica[1]) in fichasMaquina:

            if (contadorColumna + 1, fichaVerifica[1]) in fichasJugador:

                return True
            
            contadorColumna += 1
        
        return False

    else:

        contadorColumna = fichaVerifica[0] - 1

        while contadorColumna >= 1 and (contadorColumna, fichaVerifica[1]) in fichasJugador:

            if (contadorColumna - 1, fichaVerifica[1]) in fichasMaquina:

                return True
            
            contadorColumna -= 1


        contadorColumna = fichaVerifica[0] + 1

        while contadorColumna <= 8 and (contadorColumna, fichaVerifica[1]) in fichasJugador:

            if (contadorColumna + 1, fichaVerifica[1]) in fichasMaquina:

                return True
            
            contadorColumna += 1
        
        return False


def partidaFinaliza(fichasJugador, fichasMaquina, cantFichasJugadas, ultimasJugadas, colorJugador):

    # partidaFinaliza :: set((int, int)) set((int, int)) int list -> bool
    # Analiza si la partida debe finalizar, analizando si los jugadores han hecho un 
    # doble salteo, si se ingresaron todas las fichas del tablero o si un jugador se quedo
    # sin fichas. Si no se cumple ninguna de dichas condiciones, devuelve False

    if ultimasJugadas[0] == ultimasJugadas[-1]:
        
        mensajeFinal("doble salteo", fichasJugador, fichasMaquina, colorJugador)
        return True
    
    cantFichasJugador = len(fichasJugador)
    cantFichasMaquina = len(fichasMaquina)

    if cantFichasJugadas == 64:

        if cantFichasJugador > cantFichasMaquina:

            mensajeFinal("jugador", fichasJugador, fichasMaquina, colorJugador)
            return True
        
        if cantFichasMaquina > cantFichasJugador:

            mensajeFinal("maquina", fichasJugador, fichasMaquina, colorJugador)
            return True
        
    elif cantFichasJugador == 0:

        print("El jugador se quedo sin fichas.")
        mensajeFinal("maquina", fichasJugador, fichasMaquina, colorJugador)
        return True

    elif cantFichasMaquina == 0:

        print("La maquina se quedo sin fichas. ")
        mensajeFinal("maquina", fichasJugador, fichasMaquina, colorJugador)
        return True
    
    return False


def jugadaPosible(jugada, fichasJugador, fichasMaquina):

    # jugadaPosible :: string set((int, int)) set((int, int))
    # Recibe la jugada ingresada y analiza si el formato es correcto,
    # si esta dentro del tablero, si esta ocupada por algun jugador y si 
    # genera cambios en el tablero.

    limpiaConsola()

    if not fichaFormato(jugada):

        mensajeError("formato")
        return False
    
    if not fichaRango(jugada):

        mensajeError("rango")
        return False

    jugadaFicha = stringAFicha(jugada)

    if ocupada(jugadaFicha, fichasJugador, fichasMaquina):

        mensajeError("ocupada") 
        return False

    if not generaCambios(jugadaFicha, fichasJugador, fichasMaquina, "jugador"):

        mensajeError("imposible")
        return False

    return True
    

def actualizaFichasMaquina(jugadaHecha, fichasJugador, fichasMaquina):
    
    # actualizaFichasMaquina :: (int, int) set((int, int)) set((int, int)) -> None
    # La funcion recibe las fichas del jugador, de la maquina y la jugada hecha y añade las fichas
    # volteadas a la maquina y las descarta del jugador.

    horizontal = modificaHorizontal(jugadaHecha, fichasMaquina, fichasJugador)
    vertical = modificaVertical(jugadaHecha, fichasMaquina, fichasJugador)
    diagonalSup = modificaDiagonalSup(jugadaHecha, fichasMaquina, fichasJugador)
    diagonalInf = modificaDiagonalInf(jugadaHecha, fichasMaquina, fichasJugador)

    for ficha in (horizontal | vertical | diagonalSup | diagonalInf):
        # Recorre cada ficha a modificar

        fichasMaquina.add(ficha)
        fichasJugador.discard(ficha)

    fichasMaquina.add(jugadaHecha) # Añade la ficha jugada al final


def actualizaFichasJugador(jugadaHecha, fichasJugador, fichasMaquina):

    # actualizaFichasJugador :: (int, int) set((int, int)) set((int, int)) -> None
    # La funcion recibe las fichas del jugador, de la maquina y la jugada hecha y añade las fichas
    # volteadas al jugador y las descarta de la maquina.

    horizontal = modificaHorizontal(jugadaHecha, fichasJugador, fichasMaquina)
    vertical = modificaVertical(jugadaHecha, fichasJugador, fichasMaquina)
    diagonalSup = modificaDiagonalSup(jugadaHecha, fichasJugador, fichasMaquina)
    diagonalInf = modificaDiagonalInf(jugadaHecha, fichasJugador, fichasMaquina)

    for ficha in (horizontal | vertical | diagonalSup | diagonalInf): 
        # Recorre cada ficha a modificar

        fichasJugador.add(ficha)
        fichasMaquina.discard(ficha)
    
    fichasJugador.add(jugadaHecha) # Añade la ficha jugada al final

    
def modificaHorizontal(jugadaHecha, ganaFichas, pierdeFichas):

    # modificaHorizontal :: (int, int) set((int, int)) set((int, int)) -> set((int, int))
    # La funcion recibe la ficha y las jugadas hechas y devuelve las fichas que se cambiaran 
    # horizontalmente. ganaFichas es el jugador de turno y pierdeFichas el adversario del turno.

    columna,fila = jugadaHecha

    volteadasDerecha = set()
    volteadasIzquierda = set()
    
    fichasOpuestas = []
    indice = columna + 1

    while indice <= 8 and (indice,fila) in pierdeFichas:    
        
        fichasOpuestas += [(indice,fila)]

        if (indice + 1, fila) in ganaFichas:
            volteadasDerecha.update(fichasOpuestas)

        indice += 1

    fichasOpuestas = []
    indice = columna - 1

    while indice >= 1 and (indice,fila) in pierdeFichas:    

        fichasOpuestas += [(indice,fila)]

        if (indice - 1,fila) in ganaFichas:
            volteadasIzquierda.update(fichasOpuestas)

        indice -= 1
        
    return (volteadasDerecha | volteadasIzquierda) 


def modificaVertical(jugadaHecha, ganaFichas, pierdeFichas):

    # modificaHorizontal :: (int, int) set((int, int)) set((int, int)) -> set((int, int))
    # La funcion recibe la ficha y las jugadas hechas y devuelve las fichas que se cambiaran 
    # verticalmente. ganaFichas es el jugador de turno y pierdeFichas el adversario del turno.

    columna,fila = jugadaHecha

    volteadasArriba = set()
    volteadasAbajo = set()
    
    # Recorremos hacia arriba
    fichasOpuestas = []
    indice = fila + 1

    while indice <= 8 and (columna,indice) in pierdeFichas:    
        
        fichasOpuestas += [(columna,indice)]

        if (columna,indice + 1) in ganaFichas:
            volteadasArriba.update(fichasOpuestas)

        indice += 1

    # Recorremos hacia abajo
    fichasOpuestas = []
    indice = fila - 1

    while indice >= 1 and (columna,indice) in pierdeFichas:    

        fichasOpuestas += [(columna,indice)]

        if (columna,indice - 1) in ganaFichas:
            volteadasAbajo.update(fichasOpuestas)

        indice -= 1

    return (volteadasArriba | volteadasAbajo)


def modificaDiagonalSup(jugadaHecha, ganaFichas, pierdeFichas):

    # modificaHorizontal :: (int, int) set((int, int)) set((int, int)) -> set((int, int))
    # La funcion recibe la ficha y las jugadas hechas y devuelve las fichas que se cambiaran 
    # digonalmente (superior). ganaFichas es el jugador de turno y pierdeFichas el adversario del turno.

    columna,fila = jugadaHecha

    volteadasMitad1 = set()
    volteadasMitad2 = set()
    
    # Recorremos hacia una mitad
    fichasOpuestas = []
    indiceX = columna + 1
    indiceY = fila - 1

    while indiceX <= 8 and indiceY >= 1 and (indiceX,indiceY) in pierdeFichas:    
        
        fichasOpuestas += [(indiceX,indiceY)]

        if (indiceX + 1,indiceY - 1) in ganaFichas:
            volteadasMitad1.update(fichasOpuestas)

        indiceX += 1
        indiceY -= 1

    # Recorremos hacia la otra mitad
    fichasOpuestas = []
    indiceX = columna - 1
    indiceY = fila + 1

    while indiceX >= 1 and indiceY <= 8 and (indiceX,indiceY) in pierdeFichas:    

        fichasOpuestas += [(indiceX,indiceY)]

        if (indiceX - 1,indiceY + 1) in ganaFichas:
            volteadasMitad2.update(fichasOpuestas)
        
        indiceX -= 1
        indiceY += 1

    return (volteadasMitad1 | volteadasMitad2)


def modificaDiagonalInf(jugadaHecha, ganaFichas, pierdeFichas):
    
    # modificaHorizontal :: (int, int) set((int, int)) set((int, int)) -> set((int, int))
    # La funcion recibe la ficha y las jugadas hechas y devuelve las fichas que se cambiaran 
    # digonalmente (inferior). ganaFichas es el jugador de turno y pierdeFichas el adversario del turno.

    columna, fila = jugadaHecha

    volteadasMitad1 = set()
    volteadasMitad2 = set()
    
    # Recorremos hacia una mitad
    fichasOpuestas = []
    indiceX = columna + 1
    indiceY = fila + 1

    while indiceX <= 8 and indiceY <= 8 and (indiceX,indiceY) in pierdeFichas:    
        
        fichasOpuestas += [(indiceX,indiceY)]

        if (indiceX + 1,indiceY + 1) in ganaFichas:
            volteadasMitad1.update(fichasOpuestas)

        indiceX += 1
        indiceY += 1

    # Recorremos hacia la otra mitad
    fichasOpuestas = []
    indiceX = columna - 1
    indiceY = fila - 1

    while indiceX >= 1 and indiceY >= 1 and (indiceX,indiceY) in pierdeFichas:    

        fichasOpuestas += [(indiceX,indiceY)]

        if (indiceX - 1,indiceY - 1) in ganaFichas:
            volteadasMitad2.update(fichasOpuestas)

        indiceX -= 1
        indiceY -= 1

    return (volteadasMitad1 | volteadasMitad2)

