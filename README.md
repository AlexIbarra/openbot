# ROBOT BUSCADOR DE MANCHAS POR VISIÓN

## Introducción
La idea para el desarrollo de este trabajo, surge del concurso organizado por MathWorks, "Mission on Mars Robot Challenge". Los robots Rover tienen una misión que llevan a cabo cumpliendo 2 objetivos: Explorar el planeta Marte mientras identifican ciertos elementos (manchas) y además debe hacerlo evitando ciertos obstáculos del terreno.

## Objetivos
El objetivo del proyecto es realizar un robot mediante herramientas libres y abiertas, tanto de software como de hardware, este debe ser lo más asequible posible, y además se ha de emplear un lenguaje de programación común y extendido.

Este robot, ha de cumplir con las especificaciones del concurso MathWorks y realizar la tarea establecida que dicho concurso exige, todo ello, sin depender de la herramienta y lenguaje no libres que se emplean, ni de su hardware.

## Estructura del Software

La idea en cuanto a la estructura del software, es la de que se modularice lo máximo posible. Por un lado se ha de tener un módulo para el control de cada dispositivo, en este caso para la cámara, mediante el uso de la librería de [OpenCV] [cv] y los motores, mediante el uso de la librería [WiringPI] [wpi]. El módulo de la cámara será el encargado de obtener los datos de entrada del sistema, mientras que el módulo de los motores desarrollarán la salida ya que la finalidad del robot es la de que se mueva hacia los objetivos que se encuentren en el mundo que percibe.

















[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [cv]: <http://opencv.org/>
   [wpi]: <http://wiringpi.com/>
