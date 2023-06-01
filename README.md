# Programación Orientada a Objetos 
## Proyecto Integrador

### Modelado de servicio de streaming

En los últimos años, han proliferado los servicios de streaming de video bajo demanda por ejemplo Netflix, Disney Plus, HBO Max, entre otros. Algunos de ellos se especializan por el volumen de videos que proporcionan a sus usuarios mientras que otros se han puesto el reto de mostrar solamente videos de su propia marca. Una versión limitada para apoyar a un futuro proveedor de este tipo de servicios es la que se describe a continuación:

Se quiere trabajar con dos tipos de videos: películas y episodios de series.

Todo video tiene:
- ID.
- Nombre de la película o nombre del episodio de una serie.
- Género (Pueden ser varios separados por el caracter **&**).
- Calificación en escala de **1 a 7**.
- Duración en minutos.
- Fecha de estreno en formato ***mm/dd/aaaa***.

Las series tienen episodios y cada episodio tiene:

- ID.
- Nombre.
- Temporada a la que pertenece.
- Número de episodio.

Nos interesa construir un sistema de consulta para esta información que se encuentra en un archivo de texto.

El sistema debe ser capaz de mostrar el siguiente menu de manera iterativa, termina hasta que el usuario selecciona Salir:

1. Cargar el archivo de datos en formato **csv**.
2. Mostrar los videos en general con:
   - Una calificación mayor o igual a un valor tecleado por el usuario. 
   - Un género tecleado por el usuario.
3. Mostrar todos los episodios de una determinada serie que teclea el usuario.
4. Mostrar las películas con una calificacion mayor a un número tecleado por el usuario.
5. Calificar un video.
   - Pedir titulo de película o nombre del capítulo de la serie a calificar.
   - Pedir valor otorgado y asignarlo (reemplaza la calificación anterior).
6. Calcular el promedio de la calificación de una serie (promedio de todos los episodios).
7. Salir.

### **Estos requerimientos podrían cambiar hasta una semana antes de la entrega final. Asegúrate de construir tu aplicación de tal manera que sea fácil hacer modificaciones.**


## Entrega

Se entregará a través de **GitHub**, todos los archivos .h y .cpp  junto al **diagrama de clases** en jpg, png o pdf.

Entregar también en Canvas un archivo **ZIP** que contenga dos carpetas con el contenido indicado:

- **doc** (20 pts)

   Un documento PDF con:
   - Portada.
   - índice de contenido.
   - Introducción (planteamiento del problema).
   - Diagrama de clases explicando el diseño.
   - Ejemplos de ejecución de todas las opciones (capturas de  mostrando resultados exitos y mensajes de error cuando aplique).
   - Identificación de casos que harían que el proyecto deje de funcionar.
   - Conclusión personal. Partes difíciles de implementar, importancia del diagrama de clases, codificación, aprendizaje, problemas presentados, etc.
   - Referencias consultadas en formato APA.


- **src** (80 pts)

   Todos los archivos fuente necesarios para ejecutar la solución propuesta en el ambiente establecido al inicio del curso. No olvides incluir tu archivo csv y  ***considera que para probar tu código puedo reemplazarlo por otro.***
