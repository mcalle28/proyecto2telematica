#Diseño multihilos de OpenMP

Gracias a que el proyecto se compone de varios ciclos paralelizables, existen muchas opciones con las cuales se puede realizar la misma para mejorar la efectividad y rapidez del código.

En este caso se decidió paralelizar la clase que realiza la comparación entre los macrobloques: compresión.

Dentro de ella existe un ciclo que recorre los dos arreglos de macrobloques referentes a las dos imagenes que se comparan en este archivo. Esto se realiza muchas veces internamente ya que pueden existir miles de macrobloques dependiendo del tamaño de una imagen, y más en la segunda ya que su división de macrobloques es mas extensa.

Cada hilo de los que se decidan tomara su parte en el ciclo for, y la realizara para luego enviar su resultado e imprimir el vector, esto puede dar resultados desordenados, pero correctos.

Aprovechando OpenMP, se utilizaron las librerias "omp.h" de c++ en esta clase, y con ella facilmente se diseño un pragma for dinámico, el cual facilita la distribución de trabajos mas eficazmente por su partición del loop en tareas, que, cuando estas se terminan, asignan otras.

Además de eso , se verifico que la variable que hace la operación de igualdad, la cual se encuentra en macrobloque, estuviera protegida por un atomic para no ser modificada por hilos que no deberian hacerlo en ese momento y dar resultados erroneos.
