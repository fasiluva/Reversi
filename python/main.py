from archivos import *
from mensajes import *
from jugadores import *
from jugadas import *
import sys


def main(nombreArchivo, colorJugador, dificultad):

    nombreExtension = "../archivosGenerados/" + nombreArchivo + '.txt'

    if not verificaArgumentos(nombreExtension, colorJugador, dificultad):
        
        return
    
    colorMaquina = colorContrario(colorJugador)

    fichasJugador, fichasMaquina, turno = datosArchivo(nombreExtension, colorJugador, colorMaquina)

    cantFichasJugadas = len(fichasJugador) + len(fichasMaquina)

    print(f"\n------------ DIFICULTAD {dificultad}---------------\n")
    print("Color de jugador: ", colorJugador)
    print("Color de adversario: ", colorMaquina)
    print("Turno del color ", turno)

    ultimasDosJugadas = [(-1, -1), (-2, -2)]

    while partidaFinaliza(fichasJugador, fichasMaquina, cantFichasJugadas, ultimasDosJugadas):

        if turno == colorJugador:

            jugadasPosibles = actualizaJugadasPosiblesJugador(fichasJugador, fichasMaquina, "jugador")

            muestraTablero(fichasJugador, fichasMaquina, colorJugador)

            if jugadasPosibles == True:
                
                jugada = input("Ingrese una jugada: ")

                while not jugadaPosible(jugada, fichasJugador, fichasMaquina):
                    
                    muestraTablero(fichasJugador, fichasMaquina, colorJugador)
                    jugada = input("\nIngrese una jugada: ")
                
                jugadaFicha = transformaAFicha(jugada)

                actualizaFichasJugador(jugadaFicha, fichasJugador, fichasMaquina)

                cantFichasJugadas += 1
            
            else:

                print("Usted no tenia jugadas posibles, por lo que su turno fue salteado automaticamente.")

            ultimasDosJugadas[0] = jugadaFicha

            muestraTablero(fichasJugador, fichasMaquina, colorJugador)

        else:

            print("Turno de la maquina: ")

            jugadasPosiblesMaquina = actualizaJugadasPosiblesMaquina(fichasJugador, fichasMaquina, "maquina") # DICCIONARIO

            if jugadasPosiblesMaquina != set():

                jugadaFicha = eligeFicha(jugadasPosiblesMaquina, dificultad)

                actualizaFichasMaquina(jugadaFicha, fichasJugador, fichasMaquina)

                cantFichasJugadas += 1
            
            else:

                print("La maquina no tiene jugadas posibles, por lo que ha salteado de turno.")

            ultimasDosJugadas[1] = jugada


        turno = colorContrario(turno)


if __name__ == "__main__":

    if len(sys.argv) == 4:

        nombreArchivoJuego = sys.argv[1]
        colorJugador = sys.argv[2]
        nivelDificultad = sys.argv[3]
        
        main(nombreArchivoJuego, colorJugador, nivelDificultad)
    
    else:

        print("ERROR: La cantidad de argumentos de la funcion es incorrecto.")
