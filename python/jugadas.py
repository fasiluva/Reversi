from random import randint, choice
from mensajes import *
from fichas import *

def eligeFicha(jugadasPosibles, dificultad, fichasJugador, fichasMaquina):

    if dificultad == 0:

        fichas = list(jugadasPosibles)
        
        return fichas[randint(0, len(fichas))]

    else:

        fichas = list(jugadasPosibles)
        cantVolteosFicha = []

        for ficha in fichas:

            cantVolteosFicha += [cantVolteadas(ficha, fichasJugador, fichasMaquina)]

        return fichas[index(max(cantVolteosFicha))]


def cantVolteadas(ficha, fichasJugador, fichasMaquina):
    
    return cantVolteosVertical(ficha, fichasJugador, fichasMaquina) + cantVolteosHorizontal(ficha, fichasJugador, fichasMaquina) + cantVolteosDiagonalSup(ficha, fichasJugador, fichasMaquina) + cantVolteosDiagonalInf(ficha, fichasJugador, fichasMaquina)


def cantVolteosVertical(ficha, fichasJugador, fichasMaquina):

    contadorFila = ficha[1] - 1
    contadorVolteosSuperior = 0
    contadorVolteosInferior = 0

    while contadorFila >= 1 and (ficha[0], contadorFila) in fichasJugador:

        contadorVolteosSuperior += 1
        contadorFila -= 1

    contadorFila = ficha[1] + 1

    while contadorFila <= 8 and (ficha[0], contadorFila) in fichasJugador:

        contadorVolteosInferior += 1
        contadorFila += 1
    
    return contadorVolteosInferior + contadorVolteosSuperior


def cantVolteosHorizontal(ficha, fichasJugador, fichasMaquina):

    contadorColumna = ficha[0] - 1
    contadorVolteosDer = 0
    contadorVolteosIzq = 0

    while contadorColumna >= 1 and (contadorColumna, ficha[1]) in fichasJugador:

        contadorVolteosIzq += 1
        contadorColumna -= 1

    contadorColumna = ficha[0] + 1

    while contadorColumna <= 8 and (contadorColumna, ficha[1]) in fichasJugador:
        
        contadorVolteosDer += 1        
        contadorColumna += 1

    return contadorVolteosDer + contadorVolteosIzq


def cantVolteosDiagonalInf(ficha, fichasJugador, fichasMaquina):

    contadorColumna = ficha[0] + 1
    contadorFila = ficha[1] + 1
    contadorVolteosIzq = 0
    contadorVolteosDer = 0

    while contadorColumna <= 8 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasJugador:

        contadorVolteosDer += 1
        contadorColumna += 1
        contadorFila += 1
    
    contadorColumna = ficha[0] - 1
    contadorFila = ficha[1] - 1

    while contadorColumna >= 1 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasJugador:

        contadorVolteosIzq += 1        
        contadorColumna -= 1
        contadorFila -= 1


    return contadorVolteosDer + contadorVolteosIzq


def cantVolteosDiagonalSup(ficha, fichasJugador, fichasMaquina):

    contadorColumna = fichaVerifica[0] + 1
    contadorFila = fichaVerifica[1] - 1
    contadorVolteosDer = 0
    contadorVolteosIzq = 0

    while contadorColumna <= 8 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasJugador:

        contadorVolteosDer += 1
        contadorColumna += 1
        contadorFila -= 1
    

    contadorColumna = fichaVerifica[0] - 1
    contadorFila = fichaVerifica[1] + 1

    while contadorColumna >= 1 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasJugador:

        contadorVolteosIzq += 1        
        contadorColumna -= 1
        contadorFila += 1

    return contadorVolteosDer + contadorVolteosIzq


def actualizaJugadasPosiblesJugador(fichasJugador, fichasMaquina, turno):

    for ficha in fichasMaquina:

        for columna in range(ficha[0] - 1, ficha[0] + 2):

            if columna < 1: 
                columna += 1
            
            for fila in range(ficha[1] - 1, ficha[1] + 2):

                if fila < 1:
                    fila += 1
                
                if fichaValida((columna, fila), fichasJugador, fichasMaquina, turno):
                    return True
                
    return False


def actualizaJugadasPosiblesMaquina(fichasJugador, fichasMaquina, turno):

    fichasPosibles = set()

    for ficha in fichasJugador:

        for columna in range(ficha[0] - 1, ficha[0] + 2):

            if columna < 1: 
                columna += 1
            
            for fila in range(ficha[1] - 1, ficha[1] + 2):

                if fila < 1:
                    fila += 1
                
                if fichaValida((columna, fila), fichasJugador, fichasMaquina, turno):
                    
                    fichasPosibles.add(ficha)
                
    return fichasPosibles


def fichaValida(fichaVerifica, fichasJugador, fichasMaquina, turno):

    if not ocupada(fichaVerifica, fichasJugador) and not ocupada(fichaVerifica, fichasMaquina) and generaCambios(fichaVerifica, fichasJugador, fichasMaquina, turno):

        return True
    
    return False


def ocupada(fichaVerifica, jugador):
    
    return (fichaVerifica in jugador)
    

def generaCambios(fichaVerifica, fichasJugador, fichasMaquina, turno):

    if generaVertical(fichaVerifica, fichasJugador, fichasMaquina, turno) or generaHorizontal(fichaVerifica, fichasJugador, fichasMaquina, turno) or generaDiagonalSup(fichaVerifica, fichasJugador, fichasMaquina, turno) or generaDiagonalInf(fichaVerifica, fichasJugador, fichasMaquina, turno):

        return True
    
    return False


def generaDiagonalInf(fichaVerifica, fichasJugador, fichasMaquina, turno):

    if turno == "jugador":

        contadorColumna = fichaVerifica[0] + 1
        contadorFila = fichaVerifica[1] + 1

        while contadorColumna <= 8 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasMaquina:

            if ocupada((contadorColumna + 1, contadorFila + 1), fichasJugador):

                return True
            
            contadorColumna += 1
            contadorFila += 1
        

        contadorColumna = fichaVerifica[0] - 1
        contadorFila = fichaVerifica[1] - 1

        while contadorColumna >= 1 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasMaquina:

            if ocupada((contadorColumna - 1, contadorFila - 1), fichasJugador):

                return True
            
            contadorColumna -= 1
            contadorFila -= 1


        return False

    else: 

        contadorColumna = fichaVerifica[0] + 1
        contadorFila = fichaVerifica[1] + 1

        while contadorColumna <= 8 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasJugador:

            if ocupada((contadorColumna + 1, contadorFila + 1), fichasMaquina):

                return True
            
            contadorColumna += 1
            contadorFila += 1
        

        contadorColumna = fichaVerifica[0] - 1
        contadorFila = fichaVerifica[1] - 1

        while contadorColumna >= 1 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasJugador:

            if ocupada((contadorColumna - 1, contadorFila - 1), fichasMaquina):

                return True
            
            contadorColumna -= 1
            contadorFila -= 1


        return False



def generaDiagonalSup(fichaVerifica, fichasJugador, fichasMaquina, turno):

    if turno == "jugador":

        contadorColumna = fichaVerifica[0] + 1
        contadorFila = fichaVerifica[1] - 1

        while contadorColumna <= 8 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasMaquina:

            if ocupada((contadorColumna + 1, contadorFila - 1), fichasJugador):

                return True
            
            contadorColumna += 1
            contadorFila -= 1
        

        contadorColumna = fichaVerifica[0] - 1
        contadorFila = fichaVerifica[1] + 1

        while contadorColumna >= 1 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasMaquina:

            if ocupada((contadorColumna - 1, contadorFila + 1), fichasJugador):

                return True
            
            contadorColumna -= 1
            contadorFila += 1


        return False

    else: 

        contadorColumna = fichaVerifica[0] + 1
        contadorFila = fichaVerifica[1] - 1

        while contadorColumna <= 8 and contadorFila >= 1 and (contadorColumna, contadorFila) in fichasJugador:

            if ocupada((contadorColumna + 1, contadorFila - 1), fichasMaquina):

                return True
            
            contadorColumna += 1
            contadorFila -= 1
        

        contadorColumna = fichaVerifica[0] - 1
        contadorFila = fichaVerifica[1] + 1

        while contadorColumna >= 1 and contadorFila <= 8 and (contadorColumna, contadorFila) in fichasJugador:

            if ocupada((contadorColumna - 1, contadorFila + 1), fichasMaquina):

                return True
            
            contadorColumna -= 1
            contadorFila += 1


        return False



def generaVertical(fichaVerifica, fichasJugador, fichasMaquina, turno):

    if turno == "jugador":

        contadorFila = fichaVerifica[1] - 1

        while contadorFila >= 1 and (fichaVerifica[0], contadorFila) in fichasMaquina:

            if ocupada((fichaVerifica[0], contadorFila - 1), fichasJugador):

                return True
            
            contadorFila -= 1


        contadorFila = fichaVerifica[1] + 1

        while contadorFila <= 8 and (fichaVerifica[0], contadorFila) in fichasMaquina:

            if ocupada((fichaVerifica[0], contadorFila + 1), fichasJugador):

                return True
            
            contadorFila += 1
        
        return False

    else:

        contadorFila = fichaVerifica[1] - 1

        while contadorFila >= 1 and (fichaVerifica[0], contadorFila) in fichasJugador:

            if ocupada((fichaVerifica[0], contadorFila - 1), fichasMaquina):

                return True
            
            contadorFila -= 1


        contadorFila = fichaVerifica[1] + 1

        while contadorFila <= 8 and (fichaVerifica[0], contadorFila) in fichasJugador:

            if ocupada((fichaVerifica[0], contadorFila + 1), fichasMaquina):

                return True
            
            contadorFila += 1
        
        return False


def generaHorizontal(fichaVerifica, fichasJugador, fichasMaquina, turno):

    if turno == "jugador":

        contadorColumna = fichaVerifica[0] - 1

        while contadorColumna >= 1 and (contadorColumna, fichaVerifica[1]) in fichasMaquina:

            if ocupada((contadorColumna - 1, fichaVerifica[1]), fichasJugador):

                return True
            
            contadorColumna -= 1


        contadorColumna = fichaVerifica[0] + 1

        while contadorColumna <= 8 and (contadorColumna, fichaVerifica[1]) in fichasMaquina:

            if ocupada((contadorColumna + 1, fichaVerifica[1]), fichasJugador):

                return True
            
            contadorColumna += 1
        
        return False

    else:

        contadorColumna = fichaVerifica[0] - 1

        while contadorColumna >= 1 and (contadorColumna, fichaVerifica[1]) in fichasJugador:

            if ocupada((contadorColumna - 1, fichaVerifica[1]), fichasMaquina):

                return True
            
            contadorColumna -= 1


        contadorColumna = fichaVerifica[0] + 1

        while contadorColumna <= 8 and (contadorColumna, fichaVerifica[1]) in fichasJugador:

            if ocupada((contadorColumna + 1, fichaVerifica[1]), fichasMaquina):

                return True
            
            contadorColumna += 1
        
        return False



def partidaFinaliza(fichasJugador, fichasMaquina, cantFichasJugadas, ultimasJugadas):

    if ultimasJugadas[0] == ultimasJugadas[-1]:
        
        mensajeFinal("doble salteo")
        return False
    
    cantFichasJugador = len(fichasJugador)
    cantFichasMaquina = len(fichasMaquina)

    if cantFichasJugadas == 64:

        if cantFichasJugador > cantFichasMaquina:

            mensajeFinal("jugador")
            return False
        
        if cantFichasMaquina > cantFichasJugador:

            mensajeFinal("maquina")
            return False
        
    elif cantFichasJugador == 0:

        print("El jugador se quedo sin fichas.")
        mensajeFinal("maquina")
        return False

    elif cantFichasMaquina == 0:

        print("La maquina se quedo sin fichas. ")
        mensajeFinal("maquina")
        return False
    
    return True


def jugadaPosible(jugada, fichasJugador, fichasMaquina):

    if not fichaFormato(jugada):

        mensajeError("formato")
        return False
    
    if not fichaRango(jugada):

        mensajeError("rango")
        return False

    jugadaFicha = transformaAFicha(jugada)

    if ocupada(jugadaFicha, fichasJugador) and ocupada(jugadaFicha, fichasMaquina):

        mensajeError("ocupada") 
        return False

    if not generaCambiosJugador(jugadaFicha, fichasJugador, fichasMaquina):

        mensajeError("imposible")
        return False

    return True
    

def actualizaFichasMaquina(jugadaHecha, fichasJugador, fichasMaquina):
    
    horizontal = modificaHorizontal(jugadaHecha, fichasMaquina, fichasJugador)
    vertical = modificaVertical(jugadaHecha, fichasMaquina, fichasJugador)
    diagonalSup = modificaDiagonalSup(jugadaHecha, fichasMaquina, fichasJugador)
    diagonalInf = modificaDiagonalInf(jugadaHecha, fichasMaquina, fichaJugador)

    for ficha in (horizontal | vertical | diagonalSup | diagonalInf):

        fichasMaquina.add(ficha)
        fichasJugador.discard(ficha)

    fichasMaquina.add(jugadaHecha)


def actualizaFichasJugador(jugadaHecha, fichasJugador, fichasMaquina):

    horizontal = modificaHorizontal(jugadaHecha, fichasJugador, fichasMaquina)
    vertical = modificaVertical(jugadaHecha, fichasJugador, fichasMaquina)
    diagonalSup = modificaDiagonalSup(jugadaHecha, fichasJugador, fichasMaquina)
    diagonalInf = modificaDiagonalInf(jugadaHecha, fichasJugador, fichasMaquina)

    for ficha in (horizontal | vertical | diagonalSup | diagonalInf):

        fichasJugador.add(ficha)
        fichasMaquina.discard(ficha)
    
    fichasJugador.add(jugadaHecha)

    
def modificaHorizontal(jugadaHecha, ganaFichas, pierdeFichas):

    columna,fila = jugadaHecha

    volteadasDerecha = set()
    volteadasIzquierda = set()
    
    # Recorremos hacia la derecha
    fichasOpuestas = []
    indice = columna + 1

    while indice <= 8 and (indice,fila) in pierdeFichas:    
        
        fichasOpuestas += [(indice,fila)]

        if (indice + 1, fila) in ganaFichas:
            volteadasDerecha.update(fichasOpuestas)

        indice += 1

    # Recorremos hacia la izquierda
    fichasOpuestas = []
    indice = columna - 1

    while indice >= 1 and (indice,fila) in pierdeFichas:    

        fichasOpuestas += [(indice,fila)]

        if (indice - 1,fila) in ganaFichas:
            volteadasIzquierda.update(fichasOpuestas)

        indice -= 1
        
    return (volteadasDerecha | volteadasIzquierda) 


def modificaVertical(jugadaHecha, ganaFichas, pierdeFichas):

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

