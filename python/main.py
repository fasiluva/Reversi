from archivos import *
from mensajes import *
from jugadores import *

def main():

    nombreArchivo = input("\nIntroduzca el archivo de jugadas (sin extension .txt): ")

    while not ingresaArchivo(nombreArchivo): # Seguimos pidiendo el archivo si no se encuentra.
        nombreArchivo = input("\nIntroduzca nuevamente el archivo de jugadas: ")
    
    rutaArchivo = '../' + nombreArchivo + '.txt'
    archivo = open(rutaArchivo, 'r') #Abre el archivo encontrado en formato lectura

    mensajeProcesamientoArchivo(nombreArchivo)

    if not verificaDatos(archivo): # Si alguno de los datos preliminares es incorrecto no ejecutamos nada.
        print("El archivo tiene fallos. No se podra jugar la partida.")
        return
    

if __name__ == "__main__":
    main()
