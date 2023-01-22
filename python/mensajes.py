
from jugadores import *
from time import sleep


def muestraTablero(fichasJugador, fichasMaquina, colorJugador):

    # muestraTablero :: set((int, int)) set((int, int)) string -> None
    # La funcion toma las fichas del jugador, las fichas de la maquina y el color
    # del jugador, e imprime el tablero analizando casilla por casilla si le
    # pertenece a uno u otro

    print("\n----- Tablero -----\n")

    print("|    | A  | B  | C  | D  | E  | F  | G  | H  |",end = "")

    for fila in range(1, 9):
        
        print("\n----------------------------------------------")

        print(f'| {fila}  |',end = "")

        for columna in range(1, 9):

            if (columna, fila) in fichasJugador:

                print(f' {colorJugador}  |', end = "")

            elif (columna,fila) in fichasMaquina:
                print(f' {colorContrario(colorJugador)}  |', end = "")
             
            else:
                print('    |',end = "")

    print("\n----------------------------------------------\n")


def mensajeFinal(condicion, fichasJugador, fichasMaquina, colorJugador):

    # mensajeFinal :: string -> None
    # Dependiendo la condicion final, devuelve un mensaje indicando como termino la partida.

    if condicion == "doble salteo":

        print("La partida finalizo porque ambos jugadores saltaron de turno. No hay mas jugadas posibles.")
        print("Cantidad de fichas del jugador: ", len(fichasJugador))
        print("Cantidad de fichas de la maquina: ", len(fichasMaquina))

    else: 
        print("\nHa ganado: ", condicion)
        print("Cantidad de fichas del jugador: ", len(fichasJugador))
        print("Cantidad de fichas de la maquina: ", len(fichasMaquina))
    
    muestraTablero(fichasJugador, fichasMaquina, colorJugador)


def mensajeError(error):

    # mensajeError: string -> None
    # Dependiendo del error cometido, devuelve un mensaje indicando dicho error.

    print("\n\n----------- ERROR -----------\n")

    if error == "formato":

        print("El formato de la jugada es incorrecto. Reintente: ")

    elif error == "rango":

        print("La jugada esta fuera de rango. Reintente: ")

    elif error == "ocupada":
        
        print("La jugada esta en una casilla ya ocupada. Reintente: ")
    
    else:

        print("La jugada no genera cambios en el tablero. Reintente: ")