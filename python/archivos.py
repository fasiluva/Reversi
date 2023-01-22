import os 
from mensajes import *


def limpiaConsola():

    # limpiaConsola :: None -> None
    # La funcion cuando es llamada, limpia la consola analizando en que sistema operativo
    # se esta ejecutando el programa. Funcion estetica. 

    if os.name == "posix": # Linux
        os.system("clear")
    
    elif os.name == "ce" or "nt" or "dos": # Windows, MAC, etc
        os.system("cls")
    
    else: # Si no lo reconoce, no hace nada
        pass


def verificaArgumentos(nombreArchivo, color, dificultad):

    # verificaArgumentos :: string string string -> bool
    # La funcion recibe los datos preliminares y chequea si estan bien ingresados
    # Devuelve True si es correcto, False si no lo es.

    if archivoExiste(nombreArchivo) and dificultadCorrecta(dificultad) and colorCorrecto(color):
        return True

    else:
        return False


def colorCorrecto(color):

    # colorCorrecto :: string -> bool
    # Chequea que el color con el que el jugador quiere jugar sea correcto, pudiendo ser
    # solo 'B' o 'N'.

    if color != 'N' and color != 'B':

        print("El color ingresado es invalido. No puede iniciar el programa. ")
        return False
    
    return True


def dificultadCorrecta(dificultad):

    # dificultadCorrecta :: string -> bool
    # Chequea que la dificultad con la que el jugador quiere jugar sea correcta, pudiendo ser
    # solo '1' o '0'.

    if dificultad != '0' and dificultad != '1':

        print("El nivel de dificultad es invalido. No puede iniciar el programa. ")
        return False
    
    return True


def archivoExiste(nombreArchivo):

    # archivoExiste :: string -> bool
    # Chequea que el archivo con el que el jugador quiere iniciar fue enconcontrado.

    try:
        archivo = open(nombreArchivo)
        archivo.close()
    except:

        print("El archivo no fue encontrado. No puede iniciar el programa. ")
        return False
    
    else:
        
        return True