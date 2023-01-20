
def actualizaJugadasPosiblesJugador (fichasJugador, fichasMaquina):

    for ficha in fichasMaquina:

        contadorColumna = ficha[0]
        contadorFila = ficha[1] 

        while contadorColumna - 1 < contadorColumna + 1:

            
    

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
    