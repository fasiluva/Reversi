from time import sleep

def mensajeProcesamientoArchivo(nombreArchivo):
    """
    mensajeProcesamientoArchivo :: str -> None

    Nos muestra un mensaje indicando que se está procesando el archivo.
    """

    print(f'\nEl archivo {nombreArchivo}.txt se está procesando ...')
    sleep(1)



def errorJugada(jugada,error):
    """
    errorJugada :: str -> None

    Nos indica en que jugada se produjo un error y nos proporciona
    información sobre el error.
    """
    if jugada == "\n":
        print("Se encontro un error en una jugada.")
    else:
        print(f'Se encontro un error en la jugada {jugada[:-1]}.')


    if error == "salteo":
        print("Se salteó el turno cuando había jugadas posibles.")

    if error == "formato":
        print("La jugada no cumple con el formato estipulado.")

    if error == "rango":
        print("La jugada se sale fuera del rango del tablero.")

    if error == "ocupada":
        print("La jugada cae sobre una casilla ya ocupada.")

    if error == "imposible":
        print("La jugada no se encuentra dentro de las jugadas posibles.")



def informacionJugadores(jugador1,jugador2,turno):
    """
    informacionJugadores :: (str,str) (str,str) str -> None

    Dada la información inicial, nos la muestra antes de comenzar la partida.
    """

    print('\nEl jugador 1 es', jugador1[0], 'con el color', jugador1[1].upper())
    print('El jugador 2 es', jugador2[0], 'con el color', jugador2[1].upper())
    print('Inicia el color', turno)  
    print('________________________________________________')
    sleep(1)



def mensajeFinalJuego(jugadaFinal,fichasJugadas,turnoActual):
    """
    mensajeFinalJuego :: str dict(str:set((int,int))) str -> None

    Dada las condiciones de la última jugada, las fichas jugadas, y el turno
    nos muestra un mensaje adecuado relacionado a la terminación del juego.
    """
    
    cantidadFichasBlancas = len(fichasJugadas["B"])
    cantidadFichasNegras = len(fichasJugadas["N"])
    cantidadFichasJugadas = cantidadFichasBlancas + cantidadFichasNegras
    
    # Vemos si se colocaron todas las fichas
    if cantidadFichasJugadas == 64:
        print("La partida terminó satisfactoriamente.")

        if cantidadFichasBlancas > cantidadFichasNegras:
            print("Ganó el jugador de las fichas blancas!")

        elif cantidadFichasBlancas < cantidadFichasNegras:
            print("Ganó el jugador de las fichas negras!")

        else:
            print("Los dos jugadores empataron!")

    else:
        # Vemos si alguno de los jugadores se quedaron sin fichas.
        if cantidadFichasBlancas == 0:
            print("El jugador blanco se quedó sin fichas.")
            print("Gano el jugador de las fichas negras!")

        elif cantidadFichasNegras == 0:
            print("El jugador negro se quedó sin fichas.")
            print("Gano el jugador de las fichas blancas!")

        # Vemos si la partida termina a medias.
        elif jugadaFinal == "":
            print("La partida no se finalizó. No podemos determinar un ganador.")

        # Vemos si la partida terminó debido a un error.
        else:
            print(f"El error fue cometido por el jugador de las fichas {turnoActual}.")
