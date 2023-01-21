import os 
from mensajes import *


def limpiaConsola():

    if os.name == "posix":
        os.system("clear")
    
    elif os.name == "ce" or "nt" or "dos":
        os.system("cls")
    
    else:
        pass

def verificaArgumentos(nombreArchivo, color, dificultad):

    if archivoExiste(nombreArchivo) and dificultadCorrecta(dificultad) and colorCorrecto(color):
        return True

    else:
        return False


def colorCorrecto(color):

    if color != 'N' and color != 'B':

        print("El color ingresado es invalido. No puede iniciar el programa. ")
        return False
    
    return True


def dificultadCorrecta(dificultad):

    if dificultad != '0' and dificultad != '1':

        print("El nivel de dificultad es invalido. No puede iniciar el programa. ")
        return False
    
    return True

def archivoExiste(nombreArchivo):

    try:
        archivo = open(nombreArchivo)
        archivo.close()
    except:

        print("El archivo no fue encontrado. No puede iniciar el programa. ")
        return False
    
    else:
        
        return True