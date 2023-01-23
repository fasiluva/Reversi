/*

# En este archivo presento el diseño de los datos y como lo
# modelo dentro del programa. También hablare sobre las decisiones
# que tome en cuanto a el manejo de datos y como enfoco la 
# resolución del problema.
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
#   fueron jugadas. Al final del archivo se visualiza el tablero por consola,
#   viendo en cada casilla si hay una ficha.
#
#   # Jugadores:
#           Los jugadores lo representamos con una estructura definida con typedef
#   llamada Jugador. Dicha estructura tambien almacena el color como un char, la cantidad
#   de fichas jugadas por dicho jugador como un int y las fichas jugadas como un espacio 
#   de la memoria que almacena datos de tipo Ficha (mas adelante se explica que es).
#
#   # Fichas:
#            Cada ficha singular la representamos con una estructura definida con typedef
#   llamada Ficha. Dicha estructura aloja la columna como una coordenada x de tipo int
#   y la fila como una coordenada de tipo int.
#
#   "A1" -> {1, 1};
#   "H8" -> {8, 8};
#   "B3" -> {2, 3};
#
# PLANTEAMIENTO DE RESOLUCIÓN_______________
# 
#   # División en archivos:
#                          Dividimos la totalidad del programa en varios 
#   archivos para trabajar de manera más cómoda y ordenada. Los distinos 
#   archivos son:
#
#       # documentacion.c
#       # main.c - Archivo de juego donde agrupamos todas las funciones.
#       # tests.c - Archivo de tests de las funciones.
#       # tablero.c - Archivo con funciones relacionadas con el tablero.
#       # archivos.c - Archivo que contiene funciones que se encargan de la lectura del archivo.
#       # fichas.c - Archivo con funciones que leen y transforman las jugadas.
#       # jugadores.c - Archivo con funciones que verifican los colores.
#       # jugadas.c - Archivo con funciones que realizan las jugadas y los cambios en el tablero.
#  
#           # juego1.txt: Ficha colocada en un lugar ocupado.
#           # juego2.txt: Ficha colocada en un lugar no que no genera cambios.
#           # juego3.txt: Ficha colocada en un lugar ocupado.
#           # juego4.txt: Ficha fuera del tablero.
#           # juego5.txt: Turno mal salteado.
#           # juego6.txt: Turno mal salteado.
#           # juego7.txt: Partida incompleta, por lo que no se puede determinar un ganador.
#           # juego8.txt: Gana el jugador de las fichas negras porque el blanco se queda sin fichas en el tablero 
#           # juego9.txt: Gana el jugador de las fichas blancas
#           # juego10.txt: ?
#           # juegoC1.txt: Partida de ejemplo no terminada para el programa de Python
#           # juegoC2.txt: Partida de ejemplo no terminada para el programa de Python   
#           # juegoContinuacion.txt: Archivo donde se escribe una partida no termina en el programa de C, para analizar con Python
#
#
#   # Inicio del programa:
#                         Ejecutamos el programa por consola, indicando el archivo de jugadas a iniciar
#   en caso de ingresar uno erroneo, lo pedira de nuevo. Luego, chequea que el archivo este en condiciones
#   de iniciar (los colores son validos, los colores de los jugadores son diferentes, etc). Una vez listo, 
#   posiciona las primeras fichas de los jugadores, toma la primera jugada del archivo (cuarta linea del archivo),
#   y analiza si existen jugadas posibles para el jugador de turno. Chequea que la cantidad de fichas jugadas sea 
#   menor a 64 y que la jugada sea correcta. De ser asi, realiza los cambios en el tablero, cambia de turno y analiza
#   nuevamentea las jugadas posibles del jugador de turno, y repite el procedimiento hasta que una jugada sea erronea,
#   sea hayan colocado todas las fichas o se haya llegado al final del archivo.
#                       
#       # Errores en información de jugador:
#           # Colores inválidos de los jugadores.
#           # Colores repetidos en los jugadores.
#           # Color de inicio incorrecto.
#
#       # No existen errores en las jugadas:
#           # Se colocaron todas las fichas del juego.
#           # No se colocaron todas las fichas. La partida queda a medio
#             terminar.
#           # No se colocaron todas las fichas, pero un jugador se quedo sin.
#
#       # Existen errores en las jugadas:
#           # Se colocó una ficha en una casilla ya ocupada.
#           # Coordenada fuera del rango del tablero.
#           # Formato de jugada erróneo.
#           # Se colocó una ficha en un lugar donde no puede ir. En términos
#             del juego, dicha ficha no realiza cambios en el número de fichas.
#           # Se saltea cuando no se debe saltar.
#       
#   # Análisis de información de jugadores:
#                                           Antes de comenzar con la lectura
#   de las jugadas, nos encargaremos de verificar que toda la información de
#   los jugadores sea correcta. En caso de que no se cumpla alguna de las
#   verificaciones, se termina la partida sin leer las jugadas.
#
#   # Análisis de fichas válidas:
#                                 En cuanto al análisis de fichas, lo comenzaremos
#   a realizar una vez que hayamos verificado todos los datos de los jugadores. 
#
#   Para cada uno de los turnos, verifica si EXISTE AL MENOS UNA jugada posible para 
#   el jugador de turno. En caso de haberla y la jugada no es un salto de turno, verifica 
#   su formato, si el rango esta dentro del tablero, si esta en una casilla ocupada y si 
#   la jugada genera cambios. Si la jugada es un salto de turno, debe cumplirse que no 
#   existen jugadas posibles para el jugador.
#
#   Relacionado con la representación de las fichas, cuando nos encontremos con un
#   salto de turno, la asociaremos con la Ficha = {0, 0}, ya que estas coordenadas no hacen
#   referencia a ninguna posición del tablero.
#   

Tablero: 

|    | A  | B  | C  | D  | E  | F  | G  | H  |
----------------------------------------------
| 1  | 11 | 21 | 31 | 41 | 51 | 61 | 71 | 81 |
---------------------------------------------- 
| 2  | 12 | 22 | 32 | 42 | 52 | 62 | 72 | 82 |
----------------------------------------------
| 3  | 13 | 23 | 33 | 43 | 53 | 63 | 73 | 83 |
---------------------------------------------- 
| 4  | 14 | 24 | 34 | 44 | 54 | 64 | 74 | 84 |
----------------------------------------------
| 5  | 15 | 25 | 35 | 45 | 55 | 65 | 75 | 85 |
----------------------------------------------
| 6  | 16 | 26 | 36 | 46 | 56 | 66 | 76 | 86 |
----------------------------------------------
| 7  | 17 | 27 | 37 | 47 | 57 | 67 | 77 | 87 |
----------------------------------------------
| 8  | 18 | 28 | 38 | 48 | 58 | 68 | 78 | 88 |
----------------------------------------------

*/