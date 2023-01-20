from archivos import *
from mensajes import *
from jugadores import *
from jugadas import *
import sys

def main(nombreArchivo, colorJugador, dificultad):

    if not verificaArgumentos(nombreArchivo, colorJugador, dificultad):
        
        return
    
    colorMaquina = colorContrario(colorJugador)

    fichasJugador, fichasMaquina, turno = datosArchivo(nombreArchivo, colorJugador, colorMaquina)

    cantFichasJugadas = len(fichasJugador) + len(fichasMaquina)

    print(f"------------ DIFICULTAD {dificultad}---------------")
    print("Color de jugador: ", colorJugador)
    print("Color de adversario: ", colorMaquina)
    print("Turno del color ", turno)

    ultimasDosJugadas = []

    while partidaFinaliza(fichasJugador, fichasMaquina, cantFichasJugadas, ultimasDosJugadas):

        if turno == colorJugador:

            cantJugadasPosibles = actualizaJugadasPosiblesJugador(fichasJugador, fichasMaquina)

            muestraTablero(fichasJugador, fichasMaquina)

            if cantJugadasPosibles != 0:
                
                jugada = input("Ingrese una jugada: ")

                while not jugadaPosible(jugada, fichasJugador, fichasMaquina):
                    #escriba otra ficha.
                    jugada = input("Ingrese una jugada: ")

                actualizaFichas(turno, jugada, fichasJugador, fichasMaquina)

                cantFichasJugadas += 1
            
            else:

                print("Usted no tenia jugadas posibles, por lo que su turno fue salteado automaticamente.")

            ultimasDosJugadas[0] = jugada


        else:

            print("Turno de la maquina: ")

            jugadasPosiblesMaquina = actualizaJugadasPosiblesMaquina(fichasJugador, fichasMaquina) # DICCIONARIO

            if jugadasPosiblesMaquina != set():

                jugada = eligeFicha(jugadasPosiblesMaquina, dificultad)

                actualizaFichas(turno, jugada, fichasJugador, fichasMaquina)

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

        print("ERROR: Ha ingresado la cantidad incorrecta de argumentos. Finalizando programa...")
