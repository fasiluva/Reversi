
def actualizaJugadasPosiblesJugador (fichasJugador, fichasMaquina):

    for ficha in fichasMaquina:

        for columna in range(ficha[0] - 1, ficha[0] + 2):

            if columna < 1: 
                columna += 1
            
            for fila in range(ficha[1] - 1, ficha[1] + 2):

                if fila < 1:
                    fila += 1
                
                if fichaValidaJugador((columna, fila), fichasJugador, fichasMaquina):
                    return True
                
    return False


def fichaValidaJugador(fichaVerifica, fichasJugador, fichasMaquina):

    if not ocupada(fichaVerifica, fichasJugador) and not ocupada(fichaVerifica, fichasMaquina) and generaCambiosJugador(fichaVerifica, fichasJugador, fichasMaquina):

        return True
    
    return False


def ocupada(fichaVerifica, jugador):

    return fichaVerifica in jugador
    

def generaCambiosJugador(fichaVerifica, fichasJugador, fichasMaquina):

    if generaVerticalJugador(fichaVerifica, fichasJugador, fichasMaquina) or generaHorizontalJugador(fichaVerifica, fichasJugador, fichasMaquina) or generaDiagonalSupJugador(fichaVerifica, fichasJugador, fichasMaquina) or generaDiagonalInfJugador(fichaVerifica, fichasJugador, fichasMaquina):

        return True
    
    return False


def generaVerticalJugador(fichaVerifica, fichasJugador, fichasMaquina):

    



def partidaFinaliza(fichasJugador, fichasMaquina, cantFichasJugadas, ultimasJugadas):

    if ultimasJugadas[0] == ultimasJugadas[1]:
        
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

        print("EL jugador se quedo sin fichas.")
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

    if not fichaOcupada(jugada, fichasJugador, fichasMaquina):

        mensajeError("ocupada") 
        return False

    if not generaCambios(jugada, fichasJugador, fichasMaquina):

        mensajeError("imposible")
        return False

    return True
    