# Programación Orientada a Objetos 
## Proyecto Integrador

### **Modelado de servicio de streaming **

En los últimos años, han proliferado los servicios de streaming de video bajo demanda por ejemplo Netflix, Disney, DC, entre otros. Algunos de ellos se especializan por el volumen de videos que proporcionan a sus usuarios mientras que otros se han puesto el reto de mostrar solamente videos de su propia marca. Una versión limitada para apoyar a un futuro proveedor de este tipo de servicios es la que se describe a continuación:

Se quiere trabajar con dos tipos de videos: películas y series. 

Todo video tiene:

- ID
- Nombre de Película/Serie
- Género (Pueden ser varios)
- Calificación
- Duración 
- Fecha Estreno

Las series tienen capítulos y cada capítulo tiene:

- ID
- Nombre
- Temporada a la que pertenece.
- Número de capítulo

Nos interesa conocer la calificación promedio que ha recibido cada uno de los videos. Esta calificación está en escala de 1 a 7, donde 7 es la mejor calificación y 1 es la más baja.

El sistema debe ser capaz de mostrar el siguiente menu ciclado:

1. Cargar el archivo de datos con formato Excel.
2. Mostrar los videos en general con:
   1.  Una calificación mayor o igual a un valor tecleado por el usuario. 
   2.  Un género tecleado por el usuario.
3. Mostrar todos los capítulos de una determinada serie.
4. Mostrar las películas con una calificacion mayor a un número tecleado por el usuario.
5. Calificar un video.
   - Pedir titulo de película o nombre del capítulo de la serie a calificar.
   - Pedir valor otorgado y asignarlo.
6. Calcular el promedio de la calificación de una serie (promedio de los episodios).
7. Salir.


## Entrega

Se entregará a través de GitHub, todos los archivos .h y .cpp  junto al **diagrama de clases** en imagen jpg o png.

Entregar en el espacio en Canvas un archivo ZIP que contenga las siguientes carpetas con el siguiente contenido:

- doc       (20 pts)
      Un documento PDF con:
        hoja de presentación,
        índice de contenido,
        Introducción (planteamiento del problema).
        diagrama de clases UML con una argumentación del por qué del diseño,,
        ejemplo de ejecución (capturas de pantalla),
        argumentación de las partes del proyecto relacionadas con cada uno de los puntos a) a g) mencionados arriba, con una argumentación de el por qué se optó por esa solución y no por otras.
        identificación de casos que harían que el proyecto deje de funcionar,
        conclusión personal.
        referencias consultadas

- src       (80 pts)
         Todos los archivos fuente necesarios para ejecutar la solución propuesta en el ambiente establecido al inicio del curso.