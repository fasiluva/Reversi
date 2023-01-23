from jugadas import *

# archivos.py

def test_verificaArgumentos():
    
    assert verificaArgumentos("../archivosGenerados/juegoC1.txt", 'B', '1')
    assert not verificaArgumentos("../archivosGenerados/messi.txt", 'B', '1')
    assert not verificaArgumentos("../archivosGenerados/juegoC1.txt", 'K', '1')
    assert not verificaArgumentos("../archivosGenerados/juegoC1.txt", 'B', '23')


def test_colorCorrecto():

    assert colorCorrecto('B')
    assert colorCorrecto('N')
    assert not colorCorrecto('Python')


def test_dificultadCorrecta():

    assert dificultadCorrecta('0')
    assert dificultadCorrecta('1')
    assert not dificultadCorrecta('2')


def test_archivoExiste():

    assert archivoExiste("../archivosGenerados/juegoC1.txt")
    assert archivoExiste("../archivosGenerados/juegoContinuacion.txt")
    assert not archivoExiste("../archivosGenerados/argentina.txt")
    assert not archivoExiste("linux.txt")


# jugadores.py


def test_colorContrario():

    assert colorContrario('B') == 'N'
    assert colorContrario('N') == 'B'
    

def test_datosArchivo():

    assert datosArchivo("../archivosGenerados/juegoC1.txt", 'N', 'B') == ({(3, 2), (3, 4), (5, 4), (4, 5)}, {(2, 2), (3, 3), (4, 4), (5, 5)}, 'N')
    assert datosArchivo("../archivosGenerados/juegoC1.txt", 'B', 'N') == ({(2, 2), (3, 3), (4, 4), (5, 5)}, {(3, 2), (3, 4), (5, 4), (4, 5)}, 'N')
    assert datosArchivo("../archivosGenerados/juegoC3.txt", 'B', 'N') == ({(4, 4), (5, 5)}, {(4, 5), (5, 4)}, 'N')


# fichas.py


def test_fichaFormato():

    assert fichaFormato("C4")
    assert fichaFormato("f5")
    assert not fichaFormato("42")
    assert not fichaFormato('hola')


def test_stringAFicha():

    assert stringAFicha("c4") == (3, 4)
    assert stringAFicha("a1") == (1, 1)
    assert stringAFicha("H5") == (8, 5)


def test_fichaAString():

    assert fichaAString((3, 4)) == "C4"
    assert fichaAString((1, 1)) == "A1"
    assert fichaAString((8, 5)) == "H5"


def test_fichaRango():

    assert fichaRango("c4")
    assert fichaRango("d5")
    assert not fichaRango("k1")
    assert not fichaRango("z3")


# jugadas.py


fichasJugador1 = {(4, 5), (4, 4), (4, 3)}
fichasMaquina1 = {(5, 5), (5, 4), (5, 3)}
fichasPosiblesMaquina1 = {(3, 2), (3, 3), (3, 4), (3, 5), (3, 6)}

fichasJugador2 = {(4, 3), (5, 5), (4, 5), (6, 6)}
fichasMaquina2 = {(5, 3), (5, 4), (4, 4), (3, 4)}
fichasPosiblesMaquina2 = {(3, 3), (3, 2), (4, 2), (4, 6), (3, 6), (7, 7), (5, 6), (5, 2)}

fichasJugador3 = {(4, 4), (5, 5), (6, 6)}
fichasMaquina3 = {(2, 3), (3, 3), (4, 3), (5, 3), (5, 4), (3, 4)}
fichasPosiblesMaquina3 = {(3, 6), (4, 6), (5, 6), (7, 7)}


def test_eligeFicha():

    # SOLO ANALIZAREMOS LAS ELECCIONES CON DIFICULTAD 1, YA QUE CON 0 ES ALEATORIO.
    assert eligeFicha(fichasPosiblesMaquina1, '1', fichasJugador1, fichasMaquina1) == (3, 3)
    assert eligeFicha(fichasPosiblesMaquina2, '1', fichasJugador2, fichasMaquina2) == (7, 7)
    assert eligeFicha(fichasPosiblesMaquina3, '1', fichasJugador3, fichasMaquina3) == (7, 7)


def test_cantVolteadas():

    assert cantVolteadas((3, 3), fichasJugador1, fichasMaquina1) == 2
    assert cantVolteadas((7, 7), fichasJugador2, fichasMaquina2) == 2
    assert cantVolteadas((7, 7), fichasJugador3, fichasMaquina3) == 3


def test_cantVolteosVertical():

    assert cantVolteosVertical((5, 3), fichasJugador1, fichasMaquina1) == 0
    assert cantVolteosVertical((3, 4), fichasJugador2, fichasMaquina2) == 0
    assert cantVolteosVertical((2, 3), fichasJugador3, fichasMaquina3) == 0


def test_cantVolteosHorizontal():

    assert cantVolteosHorizontal((6, 3), fichasJugador1, fichasMaquina1) == 0
    assert cantVolteosHorizontal((3, 4), fichasJugador2, fichasMaquina2) == 0
    assert cantVolteosHorizontal((2, 3), fichasJugador3, fichasMaquina3) == 0


def test_cantVolteosDiagonalInf():

    assert cantVolteosDiagonalInf((5, 3), fichasJugador1, fichasMaquina1) == 0
    assert cantVolteosDiagonalInf((3, 4), fichasJugador2, fichasMaquina2) == 0
    assert cantVolteosDiagonalInf((2, 3), fichasJugador3, fichasMaquina3) == 0


def test_cantVolteosDiagonalSup():

    assert cantVolteosDiagonalSup((5, 3), fichasJugador1, fichasMaquina1) == 0
    assert cantVolteosDiagonalSup((3, 4), fichasJugador2, fichasMaquina2) == 0
    assert cantVolteosDiagonalSup((2, 3), fichasJugador3, fichasMaquina3) == 0


def test_actualizaJugadasPosiblesJugador():

    assert actualizaJugadasPosiblesJugador(fichasJugador1, fichasMaquina1)
    assert actualizaJugadasPosiblesJugador(fichasJugador2, fichasMaquina2)
    assert actualizaJugadasPosiblesJugador(fichasJugador3, fichasMaquina3)


def test_actualizaJugadasPosiblesMaquina():

    assert actualizaJugadasPosiblesMaquina(fichasJugador1, fichasMaquina1) == fichasPosiblesMaquina1
    assert actualizaJugadasPosiblesMaquina(fichasJugador2, fichasMaquina2) == fichasPosiblesMaquina2


def test_fichaValida():

    assert fichaValida((4, 3), {(4, 5), (5, 4)}, {(4, 4), (5, 5)}, "jugador")
    assert fichaValida((3, 3), fichasJugador2, fichasMaquina2, "maquina")
    assert not fichaValida((3, 8), fichasJugador2, fichasMaquina2, "maquina")
    assert not fichaValida((1, 1), {(4, 5), (5, 4)}, {(4, 4), (5, 5)}, "jugador")


def test_ocupada():

    assert not ocupada((1, 1), fichasJugador1, fichasMaquina1)
    assert ocupada((3, 3), fichasJugador3, fichasMaquina3)
    assert ocupada((5, 5), fichasJugador1, fichasMaquina1)


def test_generaCambios():

    assert generaCambios((5, 3), {(4, 5), (5, 4)}, {(4, 4), (5, 5)}, "maquina")
    assert not generaCambios((1, 1), fichasJugador1, fichasJugador2, "maquina")
    assert generaCambios((4, 3), {(4, 5), (5, 4)}, {(4, 4), (5, 5)}, "jugador")
    assert not generaCambios((7, 2), fichasJugador2, fichasMaquina2, "jugador")


def test_generaDiagonalInf():

    assert not generaDiagonalInf((4, 3), fichasJugador1, fichasMaquina1, "jugador")
    assert generaDiagonalInf((3, 3), fichasJugador2, fichasMaquina2, "jugador")
    assert generaDiagonalInf((3, 2), fichasJugador2, fichasMaquina2, "maquina")
    assert not generaDiagonalInf((1, 1), fichasJugador2, fichasMaquina2, "maquina")


def test_generaDiagonalSup():

    assert generaDiagonalSup((3, 6), fichasJugador1, fichasMaquina1, "maquina")
    assert not generaDiagonalSup((3, 4), fichasJugador1, fichasMaquina1, "maquina")
    assert generaDiagonalSup((6, 2), fichasJugador1, fichasMaquina1, "jugador")
    assert not generaDiagonalSup((6, 4), fichasJugador1, fichasMaquina1, "jugador")


def test_generaVertical():

    assert not generaVertical((5, 2), fichasJugador1, fichasMaquina1, "maquina")
    assert not generaVertical((4, 2), fichasJugador1, fichasMaquina1, "jugador")
    assert generaVertical((5, 2), fichasJugador2, fichasMaquina2, "jugador")
    assert generaVertical((4, 2), fichasJugador2, fichasMaquina2, "maquina")


def test_generaHorizontal():

    assert not generaHorizontal((2, 4), fichasJugador2, fichasMaquina2, "jugador")
    assert not generaHorizontal((4, 6), fichasJugador2, fichasMaquina2, "maquina")
    assert generaHorizontal((3, 3), fichasJugador2, fichasMaquina2, "maquina")
    assert generaHorizontal((6, 3), fichasJugador2, fichasMaquina2, "jugador")


def test_partidaFinaliza():

    assert not partidaFinaliza(fichasJugador2, fichasMaquina2, 8, [(6, 6), (3, 3)], 'N')
    assert not partidaFinaliza(fichasJugador1, fichasMaquina1, 6, [(1, 2), (5, 2)], 'N')
    assert partidaFinaliza(fichasJugador1, fichasMaquina1, 6, [(0, 0), (0, 0)], 'N')
    assert partidaFinaliza(fichasJugador1, {}, 6, [(1, 2), (5, 2)], 'N')
    assert partidaFinaliza(fichasJugador3, fichasMaquina3, 64, [(1, 2), (5, 2)], 'B')
    assert partidaFinaliza({}, fichasMaquina2, 48, [(1, 2), (5, 2)], 'N')


def test_jugadaPosible():

    assert not jugadaPosible('C3', fichasJugador1, fichasMaquina1) # imposible
    assert not jugadaPosible('D3', fichasJugador1, fichasMaquina1) # ocupada
    assert not jugadaPosible('A1', fichasJugador1, fichasMaquina1) # imposible
    assert not jugadaPosible('AA', fichasJugador1, fichasMaquina1) # formato
    assert not jugadaPosible('A9', fichasJugador1, fichasMaquina1) # rango
    assert jugadaPosible('b3', fichasJugador2, fichasMaquina2)
    assert jugadaPosible('F6', fichasJugador1, fichasMaquina1)


def test_modificaHorizontal():

    assert modificaHorizontal((6, 3), fichasJugador1, fichasMaquina1) == {(5, 3)}
    assert modificaHorizontal((4, 6), fichasJugador1, fichasMaquina1) == set()
    assert modificaHorizontal((3, 3), fichasMaquina1, fichasJugador1) == {(4, 3)}
    assert modificaHorizontal((4, 2), fichasMaquina1, fichasJugador1) == set()


def test_modificaVertical():

    assert modificaVertical((6, 3), fichasJugador1, fichasMaquina1) == set()
    assert modificaVertical((3, 3), fichasMaquina1, fichasJugador1) == set()
    assert modificaVertical((5, 2), fichasJugador2, fichasMaquina2) == {(5, 3), (5,4)}
    assert modificaVertical((4, 2), fichasMaquina2, fichasJugador2) == {(4, 3)}


def test_modificaDiagonalSup():

    assert modificaDiagonalSup((6, 3), fichasJugador2, fichasMaquina2) == {(5, 4)}
    assert modificaDiagonalSup((5, 2), fichasMaquina2, fichasJugador2) == {(4, 3)}
    assert modificaDiagonalSup((1, 1), fichasJugador2, fichasMaquina2) == set()
    assert modificaDiagonalSup((1, 8), fichasMaquina2, fichasJugador2) == set()


def test_modificaDiagonalInf():

    assert modificaDiagonalInf((6, 5), fichasJugador2, fichasMaquina2) == {(5, 4)}
    assert modificaDiagonalInf((7, 7), fichasMaquina2, fichasJugador2) == {(5, 5), (6, 6)}
    assert modificaDiagonalInf((8, 8), fichasJugador2, fichasMaquina2) == set()
    assert modificaDiagonalInf((1, 1), fichasMaquina2, fichasJugador2) == set()