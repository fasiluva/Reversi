
from jugadores import *
from time import sleep

def muestraTablero(fichasJugador, fichasMaquina, colorJugador):

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


def mensajeFinal(condicion):

    if condicion == "doble salteo":

        print("La partida finalizo porque ambos jugadores saltaron de turno. No hay mas jugadas posibles.")

    else: 
        print("\nHa ganado: ", condicion)


def mensajeError(error):

    print("\n\n----------- ERROR -----------\n")

    if error == "formato":

        print("El formato de la jugada es incorrecto. Reintente: ")

    elif error == "rango":

        print("La jugada esta fuera de rango. Reintente: ")

    elif error == "ocupada":
        
        print("La jugada esta en una casilla ya ocupada. Reintente: ")
    
    else:

        print("La jugada no genera cambios en el tablero. Reintente: ")