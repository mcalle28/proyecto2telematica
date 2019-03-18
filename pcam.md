#Diseño bajo metodología PCAM

Problema:

Algoritmo de compresión de imagenes MPEG-2 en el cual se tienen que comparar distintos macrobloques del tamaño de 16x16 pixeles. Este problema puede escalar en grandes cantidades de macrobloques y muchos ciclos segun la cantidad de pixeles que tenga una imagen, por lo cual es necesario paralelizarlo en multiples procesadores.

Particiones:

Se dará a cada procesador un macrobloque distinto de la imagen 1 para que este pueda buscar la similutud en todo el arreglo de macrobloques de la imagen 2.
Para ello se utiliza un broadcast del arreglo de macrobloques de la imagen 2, y un scatter en el arreglo de macrobloques de la imagen 1,el cual, a diferencia del broadcast, envia partes del arreglo a los distintos procesadores para analizarla.

Comunicación:

Solo se recibira el resultado del analisis de los distintos procesadores en el maestro, ningun procesador se comunicara con los otros.

Aglomeración:

Para particionar correctamente se necesita crear una estructura propia que mande una clase que no existe en los tipos de MPI,
esto se realiza con el create_struct, definido en la libreria de c/c++ de MPI. Esta estructura hara una copia de la clase macrobloque para poder enviarla en un scatter. Esto significan pasos adicionales pero necesarios en el problema.

Broadcast puede llevar tiempo de procesamiento adicional, en especial tratandose del segundo arreglo de macrobloques, el cual siempre sera más extenso, pero es necesario para esta visión de la solución ya que se analizaran distintas partes de la imagen en toda la segunda, así que cada proceso necesita su propia versión de la imagen para funcionar correctamente.

Dentro de la misma paralelización por procesos existe una paralelización por hilos explicada en el archivo openmp.md

Mapeo:

Como se menciono anteriormente,cada parte de la primera imagen se enviara a N procesos para que recorran toda la imagen 2 y busquen las coincidencias.
La decisión de cuantas partes de la imagen 1 se enviaran a cada procesador, depende de cuantos procesadores se tienen, esto se logra gracias al método MPI_SCATTER.