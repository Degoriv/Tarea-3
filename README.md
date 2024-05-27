## Programa solucionador de puzzle 8
Este codigo lo que hace es resolver un "Puzzle 8", es una variacion del "Juego del 15" donde hay unas 16 casillas donde solo 15 estan disponibles, el objetivo del juego consiste en ordenar las fichas en orden numerico, usando la casilla vacia para moverlas.
La diferencia con esta variante es simplemente que en lugar de tener 16 casillas tiene 9.<br>
Para poder resolver el puzzle lo que hace es usar dos metodos de busqueda, el por anchura y el por profundidad.

## Compilacion 
Si se desea compilar el programa, se debe crear una ventana tipo "shell" e ingresar el siguiente comando
````
gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea3
````

Luego ejecutar:
````
./tarea3
````

## Menu de funcionalidades
Al ejecutarlo se deberia de abrir el siguiente menu:

````
========================================

     Escoge método de búsqueda

========================================

1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero (No disponible)
4) Salir

Ingrese su opción: 
````

## 1) Búsqueda en Profundidad
El algoritmo de busqueda por profundidad lo que hace primero es recorrer el arbol hasta lo mas profundo posible, para despues retroceder hasta un nodo que le permita recorrer mas ramas. <br>
Al ejecutar el programa muestra el estado inicial, las iteraciones y cuantos pasos le toma llegar desde el puzzle solucion al puzzle inicial.<br>
````
Estado Inicial:

x 2 8 
1 3 4 
6 5 7 

Puzzle Resuelto

Iteraciones: 119550

Estado:

x 1 2 
3 4 5 
6 7 8 

Paso 1:

1 x 2 
3 4 5 
6 7 8 

...

Paso 14:

x 2 8 
1 3 4 
6 5 7 
````
## 2) Búsqueda en Anchura

El algoritmo de busqueda por anchura recorre el arbol nivel por nivel, de forma que explora los nodos vecinos y una vez termina, avanza al siguiente nivel de nodos.<br>
Al ejecutar el programa muestra el estado inicial, las iteraciones y cuantos pasos le toma llegar desde el puzzle solucion al puzzle inicial.<br>
````
Estado Inicial:

x 2 8 
1 3 4 
6 5 7 

Puzzle Resuelto 
Iteraciones: 221143

Paso 4206945:

x 2 8 
1 3 4 
6 5 7 

Paso 1:

1 2 8 
x 3 4 
6 5 7 

...

Paso 12:

x 1 2 
3 4 5 
6 7 8 
````