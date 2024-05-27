#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include <string.h>



typedef struct {

		int square[3][3]; // Matriz 3x3 que representa el tablero
		int x;    				// Posición X del espacio vacío
		int y;    				// Posición Y del espacio vacío
		int nActions;

} State;

typedef struct Node {

		State state;
		struct Node* parent;

} Node;

// Prototipos de funciones
void mostrarMenuPrincipal(void);

int isValidMove(int x, int y);

void imprimirEstado(const State *estado);

int isFinal(const State* estado);

void copyState(State original, State* new);

void move(State* current, int caso);

State* transicion(State* oldState, int action);

List* getAdjNodes(Node* parentNode);

void dfs(State initialState, int cont);

void bfs(State initialState, int cont);

void mostrarMenuPrincipal() {

		limpiarPantalla();
		puts("========================================\n");
		puts("     Escoge método de búsqueda\n");
		puts("========================================\n");

		puts("1) Búsqueda en Profundidad");
		puts("2) Buscar en Anchura");
		puts("3) Buscar Mejor Primero (No disponible)");
		puts("4) Salir\n");

}

int isValidMove(int x, int y) { 
	return (x >= 0 && x < 3 && y >= 0 && y < 3); }

void imprimirEstado(const State *estado) {
		for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
						if (estado->square[i][j] == 0)
								printf("x ");
						else
								printf("%d ", estado->square[i][j]);
				}
				printf("\n");
		}
}

int isFinal(const State* estado) {
	State estadoFinal = {
		{{0, 1, 2},
		 {3, 4, 5},
		 {6, 7, 8}},
	0,0
	};

	for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
					if (estado->square[i][j] != estadoFinal.square[i][j]){
							return 0; }
				}
		}
	return 1;
}

void copyState(State original, State* new) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			new->square[i][j] = original.square[i][j];

	new->x = original.x;
	new->y = original.y;
	new->nActions = original.nActions;

}


void move(State* current, int caso) {
	int x = current->x;
	int y = current->y;
	int temp;

	if (caso == 1) { // Arriba
		if (isValidMove(x, y - 1)) {
			temp = current->square[x][y - 1];
			current->square[x][y - 1] = current->square[x][y];
			current->square[x][y] = temp;
			current->y = y - 1; } 
				}	
		
	 else if (caso == 2) { // Abajo
		if (isValidMove(x, y + 1)) {
			temp = current->square[x][y + 1];
			current->square[x][y + 1] = current->square[x][y];
			current->square[x][y] = temp;
			current->y = y + 1; }
				}
		 
	 else if (caso == 3) { // Izquierda
		if (isValidMove(x - 1, y)) {
			temp = current->square[x - 1][y];
			current->square[x - 1][y] = current->square[x][y];
			current->square[x][y] = temp;
			current->x = x - 1; }
				}
		 
	 else if (caso == 4) { // Derecha
		if (isValidMove(x + 1, y)) {
			temp = current->square[x + 1][y];
			current->square[x + 1][y] = current->square[x][y];
			current->square[x][y] = temp;
			current->x = x + 1; }
				}
}

State* transicion(State* antEstado, int action) {
	State *nuevoEstado = (State*) malloc(sizeof(State));
	copyState(*antEstado, nuevoEstado);
	move(nuevoEstado, action);
		nuevoEstado->nActions++;

	return nuevoEstado;
}

List *getAdjNodes(Node* parentNode) {
	List *adjList = list_create();  // Crear la lista de nodos adyacentes

	int x = parentNode->state.x;
	int y = parentNode->state.y;

	// Movimiento arriba
	State *newState1 = transicion(&parentNode->state, 1);
	if (newState1->x != x || newState1->y != y) {
		Node *newNode1 = (Node*) malloc(sizeof(Node));
		newNode1->state = *newState1;
		newNode1->parent = parentNode;
		list_pushBack(adjList, newNode1); }
	else free(newState1);

	// Movimiento abajo
	State *newState2 = transicion(&parentNode->state, 2);
	if (newState2->x != x || newState2->y != y) {
		Node *newNode2 = (Node*) malloc(sizeof(Node));
		newNode2->state = *newState2;
		newNode2->parent = parentNode;
		list_pushBack(adjList, newNode2); }
	else free(newState2);

	// Movimiento izquierda
	State *newState3 = transicion(&parentNode->state, 3);
	if (newState3->x != x || newState3->y != y) {
		Node *newNode3 = (Node*) malloc(sizeof(Node));
		newNode3->state = *newState3;
		newNode3->parent = parentNode;
		list_pushBack(adjList, newNode3);
	} else {
			free(newState3);
	}

	// Movimiento derecha
	State *newState4 = transicion(&parentNode->state, 4);
	if (newState4->x != x || newState4->y != y) {
		Node *newNode4 = (Node*) malloc(sizeof(Node));
		newNode4->state = *newState4;
		newNode4->parent = parentNode;
		list_pushBack(adjList, newNode4);
	} else {
		free(newState4);
	}

	return adjList;
}

void bfs(const State estadoInicial, int cont) {
	Queue* queue = queue_create(NULL);

	printf("\nEstado Inicial:\n\n");
	imprimirEstado(&estadoInicial);
	printf("\n");

	Node *root = (Node *) malloc(sizeof(Node));
	root->parent = NULL;
	root->state = estadoInicial;
	queue_insert(queue, root);

	while (list_size(queue) > 0) {
		Node *current = (Node *) queue_front(queue);
		queue_remove(queue);

		if (cont >= 10000000) {
			printf("Se llegó al límite de iteraciones\n");
			queue_clean(queue);
			return;
		}

		if (isFinal(&current->state)) {
			printf("Puzzle Resuelto \n");
			printf("Iteraciones: %d\n\n", cont);

			Stack *solution_stack = stack_create(NULL);
			for (Node *node = current; node != NULL; node = node->parent) {
				stack_push(solution_stack, node);
			}

			int steps = 0;
			while (list_size(solution_stack) > 0) {
				Node *solution_node = (Node *) stack_top(solution_stack);
				stack_pop(solution_stack);
				printf("Paso %d:\n\n", steps == 0 ? "Inicial" : steps);
				imprimirEstado(&solution_node->state);
				printf("\n");
				steps++;
			}

			stack_clean(solution_stack);
			queue_clean(queue);
			return;
		}

		List *adjacent_nodes = getAdjNodes(current);
		
		for (void *aux = list_first(adjacent_nodes); aux != NULL; aux = list_next(adjacent_nodes)) {
			queue_insert(queue, aux); }
		
		list_clean(adjacent_nodes);
		cont++;
	}

	printf("La solución no fue encontrada.\n");
	queue_clean(queue);
}

void dfs(const State estadoInicial, int cont) {
	Stack* stack = stack_create(NULL);
	printf("\nEstado Inicial:\n\n");
	imprimirEstado(&estadoInicial);
	printf("\n");

	Node *raiz = (Node *) malloc(sizeof(Node));
	raiz->parent = NULL;
	raiz->state = estadoInicial;
	stack_push(stack, raiz); 

	while (list_size(stack) > 0) {
		Node *actual = (Node *) stack_top(stack);
		stack_pop(stack);

		if (actual->state.nActions >= 15) {
			free(actual);
			continue; }

		if (isFinal(&actual->state)) {
			printf("Puzzle Resuelto\n\n");
			printf("Iteraciones: %d\n\n", cont);
			int pasos = 0;
			while (actual != NULL) {
				if (pasos == 0) 
					printf("Estado:\n\n");  
				else
					printf("Paso %d:\n\n", pasos);                  

				imprimirEstado(&actual->state);
				printf("\n");
				pasos++;

				Node *temp = actual;
				actual = actual->parent;
				free(temp); 
			}
			stack_clean(stack);
			return; 
		}

		List *adjNodes = getAdjNodes(actual);
		for (void *aux = list_first(adjNodes); aux != NULL; aux = list_next(adjNodes)) {
			stack_push(stack, aux); }
		list_clean(adjNodes);
		cont++;
	}

	printf("La solucion no fue encontrada \n");

	stack_clean(stack);
}

int main() {
		State estado_inicial = {
				{{0, 2, 8}, // Primera fila (0 representa espacio vacío)
				 {1, 3, 4}, // Segunda fila
				 {6, 5, 7}, // Tercera fila
				 },  
				0, 0   // Posición del espacio vacío (fila 0, columna 1)
		};

		estado_inicial.nActions = 0;

		int opcion;
		int cont = 0;

		do {

				mostrarMenuPrincipal();
				printf("Ingrese su opción: ");
				scanf(" %d", &opcion);

				switch (opcion) {
				case 1:
					dfs(estado_inicial, cont);
					break;
					
				case 2:
					bfs(estado_inicial, cont);
					break;

				case 3: // No se hace
					printf("Opcion no disponible\n");
					break;
					
				case 4:
						printf("Saliendo del programa...\n");
						break;
				}
				presioneTeclaParaContinuar();
				limpiarPantalla();

	} while (opcion != 4);

	return 0;
}
