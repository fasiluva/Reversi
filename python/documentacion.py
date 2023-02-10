# 
#	En este archivo presento el diseño de los datos y como los 
# 	modelo dentro del programa de Python. También hablare sobre las decisiones
# 	que tome en cuanto a el manejo de datos y como enfoco la resolución del problema.
# 
#	INGRESO DE ARCHIVOS EN LA CONSOLA:
#
#   python3 main.py archivo.txt colorJugador dificultad
#
#
# DISEÑO DE DATOS___________________________ 
# 
#   # Tablero:
#             El tablero tiene un tamaño de 8 columnas por 8 filas, 
#   representadas por los números del 1 al 8, y con las letras de la A a la
#   H, respectivamente.
#           
#   El tablero en si no posee un tipo de dato especifico, ya que a lo largo 
#   de la ejecucion del programa solo almacenamos la posicion de las fichas que 
#   fueron jugadas. Con cada jugada de los integrantes se visualiza el tablero 
#   en la consola. 
# 
#
#   # Jugadores:
#           Los datos relevantes de los jugadores son sus colores y sus fichas jugadas,
#   por lo que almaceno sus fichas jugadas en conjuntos diferentes de tuplas (int, int) y sus colores como strings,
#   donde el color del jugador es el ingresado en la consola y el de la maquina es el contrario a dicho
#   color.
#
#   # Fichas:
#            Cada ficha singular la represento como una tupla (int, int), donde el primer componente
#   es la columna y la segunda es la fila. Las componentes pueden ser numeros del 1 al 8 inclusive. Por
#   ejemplo: 
#
#   "A1" -> (1, 1);
#   "H8" -> (8, 8);
#   "B3" -> (2, 3);
#
# PLANTEAMIENTO DE RESOLUCIÓN_______________
# 
#   # DIVISION DE ARCHIVOS:
#                          Dividi la totalidad del programa en varios 
#   archivos para trabajar de manera más cómoda y ordenada. Los distinos 
#   archivos son:
#
#       # documentacion.py
#       # main.py - Archivo de juego donde agrupa todas las funciones.
#       # tests.py - Archivo de tests de las funciones.
#       # archivos.py - Archivo que contiene funciones que se encargan de la lectura del archivo.
#       # mensajes.py - Archivo encargado de mostrar los mensajes de errores y finales por consola.
#       # fichas.py - Archivo con funciones que leen y transforman las jugadas.
#       # jugadores.py - Archivo con funciones que verifican los colores.
#       # jugadas.py - Archivo con funciones que realizan las jugadas y los cambios en el tablero.
#  
#       #! LOS ARCHIVOS DEL PROGRAMA DE PYTHON ESTAN EN archivosGenerados
#
#       # juegoC1.txt, juegoC2.txt - Jugadas aleatorias.
#       # juegoC3.txt - Jugada en posiciones iniciales.
#       # juegoC4.txt - Jugada a punto de finalizar.
#       # juegoContinuacion.txt - Archivo que es sobreescripto por el programa de C.
#
#
#   # Inicio del programa:
#                         Ejecutamos el programa por consola, indicando el archivo de jugadas, el color y la dificultad.
#   En caso de que uno de dichos datos no sea valido, no inicia el programa. Luego, abre el archivo una unica vez y extrae
#   las jugadas del jugador y de la maquina, almacenandolo en conjuntos diferentes de fichas, junto con el turno que inicia.
#   El bucle que da funcionamiento al juego funciona de la siguiente manera: 
#
#       #? Verifica que:
#           #? No se hayan ingresado todas las fichas. Sino, termina la partida.
#           #? Los jugadores no hayan saltado su turno. Sino, termina la partida.
#           #? Los jugadores se hayan quedado sin fichas. Sino, termina la partida.
#       #? Muestra el tablero
#       #* Si es el turno del jugador:
#           #? Analiza si existen jugadas posibles (min 1).
#           #? Si existen jugadas posibles para el jugador:
#               #? Pide que ingrese una jugada y verifica:
#                   #? La jugada tiene formato correcto.
#                   #? La jugada esta dentro del tablero
#                   #? La jugada no esta en una casilla ocupada.
#                   #? La jugada genera cambios en el tablero.
#                   #! Sino, pide denuevo la jugada.
#               #? Limpia la consola.
#               #? Transforma la jugada a ficha (tupla).
#               #? Actualiza las fichas volteadas por la ficha
#               #? Aumenta la cantidad de fichas jugadas en 1.
#           #? Si no existen jugadas posibles para el jugador:
#               #? La 'jugada' hecha es una tupla de ceros.
#           #? Guarda la jugada hecha en la lista de ultimas 2 jugadas.
#        #* Si es el turno de la maquina:
#           #? Actualiza todas las jugadas posibles y las guarda.
#           #? Si la maquina tiene jugadas posibles:
#               #? Elige una ficha, segun la dificultad.
#               #? Actualiza las fichas volteadas por la ficha.
#               #? Aumenta la cantidad de fichas jugadas en 1.
#           #? Si no existen jugadas posibles:
#               #? La 'jugada' hecha es una tupla de ceros.
#           #? Guarda la jugada hecha en la lista de ultimas 2 jugadas.
#       #? Cambia de turno
#                       
#
#
#   Relacionado con la representación de las fichas, cuando nos encontremos con un
#   salto de turno, la asociaremos con la tupla (0, 0), ya que estas coordenadas no hacen
#   referencia a ninguna posición del tablero.
#   
#
#   Importacion de archivos en el main:
#
#       jugadas.py
#         |  random
#         |  archivos.py
#         |    |  mensajes.py
#         |    |    |  jugadores.py
#         |    |    |  time
#         |    |  os
#         |  fichas.py
#       sys
#
#   (main importa jugadas y sys, jugadas importa rangom arhivos y fichas, y asi)
#
#  Tablero: 
#
#	. El primer numero representa la columna, y el segundo la fila. La primera columna y fila
#     son indicativos de las filas y columnas, respectivamente. 
#
#
# |    | A  | B  | C  | D  | E  | F  | G  | H  |
# ----------------------------------------------
# | 1  | 11 | 21 | 31 | 41 | 51 | 61 | 71 | 81 |
# ---------------------------------------------- 
# | 2  | 12 | 22 | 32 | 42 | 52 | 62 | 72 | 82 |
# ----------------------------------------------
# | 3  | 13 | 23 | 33 | 43 | 53 | 63 | 73 | 83 |
# ---------------------------------------------- 
# | 4  | 14 | 24 | 34 | 44 | 54 | 64 | 74 | 84 |
# ----------------------------------------------
# | 5  | 15 | 25 | 35 | 45 | 55 | 65 | 75 | 85 |
# ----------------------------------------------
# | 6  | 16 | 26 | 36 | 46 | 56 | 66 | 76 | 86 |
# ----------------------------------------------
# | 7  | 17 | 27 | 37 | 47 | 57 | 67 | 77 | 87 |
# ----------------------------------------------
# | 8  | 18 | 28 | 38 | 48 | 58 | 68 | 78 | 88 |
# ----------------------------------------------
#
#
#