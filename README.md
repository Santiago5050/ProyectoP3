# Proyecto en C++ para la asignatura "Programacion 3"

#### Descripcion del Proyecto
El proyecto fue realizado en solitario para la materia "Programacion 3" impartida por la "Facultad de Ingenieria - UDELAR".

#### Objetivo
El objetivo de este proyecto es el modelado y posterior implementación de un problema utilizando las técnicas Greedy, Programación Dinámica y Divide and Conquer. Se espera que la implementación realizada haga un buen uso de la memoria.

#### Problema
Se considera un conjunto de n pedidos {1, . . . , n}, de los cuales se conoce su tiempo de inicio, su tiempo de fin y su volumen. Dado un pedido i, se denota su tiempo de inicio como `inicio(i)`, su tiempo de fin como `fin(i)` y su volumen como `volumen(i)`. Se considera que dos pedidos i, j ∈ {1, . . . , n} son compatibles si y solo si no se superponen en el tiempo, es decir:

 ![Definicion compatibles en el tiempo](https://raw.githubusercontent.com/Santiago5050/ProyectoP3/master/imagenes_readme/001.png)

#### Que se pide?
 - a) Una solución, basada en la técnica Greedy, al problema de obtener el conjunto de pedidos compatibles de cantidad máxima. Esta solución deberá implementarse en la función max_cantidad que deberá ejecutarse en `O(n log n)`.
 - b) Una solución, basada en la técnica Programación Dinámica, al problema de obtener el conjunto de pedidos compatibles que maximice la suma de sus volúmenes. Esta solución deberá implementarse en la función `max_volumen` que deberá ejecutarse en `O(n log n)`.

#### Materiales
Se obtienen los siguientes archivos:
 - El intérprete de comandos principal.cpp utilizado para testear la implementación (ver sección 8.1 LetraTarea.pdf).
 - El archivo Makefile con reglas para la compilación y testing (ver sección 8.2 LetraTarea.pdf).
 - En el subdirectorio include el archivo de definición: intervalos.h.
 - En el subdirectorio test los casos de prueba para principal.cpp.
