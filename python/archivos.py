
def verificaArgumentos(nombreArchivo, color, dificultad):

    if archivoExiste(nombreArchivo) and dificultadCorrecta(dificultad) and colorCorrecto(color):
        return True
    else:
        return False


def colorCorrecto(color):

    if color != 'N' and color != 'B':

        mensajeError("color")
        return False
    
    return True


def dificultadCorrecta(dificultad):

    if dificultad != '0' and dificultad != '1':

        mensajeError("dificultad")
        return False
    
    return True

def archivoExiste(nombreArchivo):

    try:

        open(nombreArchivo, 'r')
    
    except:

        mensajeError("archivo")
        return False
    
    else:

        return True