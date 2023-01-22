from archivos import *
from mensajes import *
from jugadores import *
from jugadas import *
import sys


def main(nombreArchivo, colorJugador, dificultad):

    nombreExtension = "../archivosGenerados/" + nombreArchivo + '.txt'

    if not verificaArgumentos(nombreExtension, colorJugador, dificultad):
        # Si no verifican los datos ingresados, no inicia
        return
    
    colorMaquina = colorContrario(colorJugador)

    fichasJugador, fichasMaquina, turno = datosArchivo(nombreExtension, colorJugador, colorMaquina)

    cantFichasJugadas = len(fichasJugador) + len(fichasMaquina)

    limpiaConsola() 

    print(f"\n------------ DIFICULTAD {dificultad} ---------------\n")
    print("Color de jugador: ", colorJugador)
    print("Color de adversario: ", colorMaquina)
    print("Turno del color ", turno)

    ultimasDosJugadas = [(-1, -1), (-2, -2)]
    # Nota: si las ultimas 2 jugadas son saltos de turno, la partida termina.

    while not partidaFinaliza(fichasJugador, fichasMaquina, cantFichasJugadas, ultimasDosJugadas, colorJugador):

        muestraTablero(fichasJugador, fichasMaquina, colorJugador)

        if turno == colorJugador: # Si es el turno del jugador

            jugadasPosibles = actualizaJugadasPosiblesJugador(fichasJugador, fichasMaquina)
            # Nota: a diferencia de actualizaJugadasPosiblesMaquina, esta funcion devuelve True si existe
            # al menos una jugada posible.

            if jugadasPosibles == True: # Si existen jugadas posibles a realizar 
                
                jugada = input("Ingrese una jugada: ")

                while not jugadaPosible(jugada, fichasJugador, fichasMaquina):
                    
                    muestraTablero(fichasJugador, fichasMaquina, colorJugador)
                    jugada = input("\nIngrese una jugada: ")
                
                limpiaConsola()

                jugadaFicha = stringAFicha(jugada) # Transforma la jugada de string a tupla

                actualizaFichasJugador(jugadaFicha, fichasJugador, fichasMaquina)

                cantFichasJugadas += 1
            
            else: # Si la unica opcion es el salto de turno

                jugadaFicha = (0, 0) # Salto de linea
                print("Usted no tenia jugadas posibles, por lo que su turno fue salteado automaticamente.")

            ultimasDosJugadas[0] = jugadaFicha # Aniade la ficha jugada o el salto de turno a la ultimas 2 jugadas hechas


        else:

            print("Turno de la maquina: ")

            sleep(1)  

            jugadasPosiblesMaquina = actualizaJugadasPosiblesMaquina(fichasJugador, fichasMaquina) 
            # Nota: a diferencia de actualizaJugadasPosiblesJugador, esta funcion devuelve todas las jugadas
            # posibles para la maquina en un conjunto. Si no existe niguna jugada, devuelve un conjunto vacio.

            limpiaConsola()

            if jugadasPosiblesMaquina != set(): # Si hay jugadas posibles

                jugadaFicha = eligeFicha(jugadasPosiblesMaquina, dificultad, fichasJugador, fichasMaquina)

                actualizaFichasMaquina(jugadaFicha, fichasJugador, fichasMaquina)

                cantFichasJugadas += 1
                
                print("La maquina hizo la jugada", fichaAString(jugadaFicha))

            else: # Si no existen jugadas posibles

                jugadaFicha = (0, 0) # Salto de linea
                print("La maquina no tiene jugadas posibles, por lo que ha salteado de turno.")

            ultimasDosJugadas[1] = jugadaFicha # Aniade la ficha jugada o el salto de turno a la ultimas 2 jugadas hechas


        turno = colorContrario(turno) # Cambia el turno


if __name__ == "__main__":

    if len(sys.argv) == 4: # Si la cantidad de datos ingresados es correcta

        nombreArchivoJuego = sys.argv[1]
        colorJugador = sys.argv[2]
        nivelDificultad = sys.argv[3]
        
        main(nombreArchivoJuego, colorJugador, nivelDificultad)
    
    else:

        print("ERROR: La cantidad de argumentos de la funcion es incorrecto.")
