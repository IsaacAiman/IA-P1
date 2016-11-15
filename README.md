# PRACTICA IA

## Coche autonomo

Miembros

* Isaac Manuel Aiman Salas
* Cristian Gonzalez Alonso
* Pablo Pastor Martín

## Descripción de funcionamiento

El funcionamiento de nuestro programa consiste en implementar una estrategia de búsqueda heurística determinada, en este caso la búsqueda A estrella,  con el objetivo de dar la posibilidad a un vehículo de llegar de un punto a otro escogiendo siempre el camino más óptimo.

## Herramientas de desarrollo

Para la realización de esta práctica hemos escogido un lenguaje de programación orientado a objetos, en este caso C++. Lo hemos acompañado de la librería Allegro para elaborar la interfaz gráfica del programa.
Elementos del sistema basado en agentes
Percepciones. El coche dispone de sensores delanteros y laterales, capaces de detectar obstáculos en cuatro direcciones (norte, sur, este y oeste). 
Acciones. Cambios de dirección (4 posibles), además de acelerar y frenar.
Objetivos. Llegar a un punto determinado por la ruta más corta.
Entorno. Un tablero representado con una interfaz gráfica, en la que existen una serie de obstáculos  a esquivar y personas a las que recoger durante el trayecto.

## Propuesta de toma de decisiones.

Ante cualquier fallo del coche, que suponga poner en riesgo la vida de sus ocupantes o de los peatones, hemos decidido que el coche autónomo priorice la vida de estos últimos, siempre y cuando estuvieran cruzando correctamente.  No obstante, si la diferencia entre el número de pasajeros y el número de peatones resulta muy grande, no aplicaremos esta norma. 


