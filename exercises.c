#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");
}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

List* crea_lista() {
   List* L = create_list();
   for (int i = 1; i <= 10; i++) {
      int* dato = (int*)malloc(sizeof(int)); // Reservar memoria para un entero
      *dato = i; // Asignar el valor i al contenido de dato
      pushBack(L, dato); // Agregar el dato a la lista
   }
   return L;
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) {
   if (L == NULL) return 0;

   int contador = 0;
   int *elemento = first(L);
   while (elemento != NULL) {
      contador += *elemento;
      elemento = next(L);
   }
   return contador;
}

/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/
void eliminaElementos(List* L, int elem) {
   int *posicion = first(L);
   while (posicion != NULL) {
      if (*posicion == elem) {
         popCurrent(L);
      } else {
         posicion = next(L);
      }
   }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/
void copia_pila(Stack* P1, Stack* P2) {
   Stack* pAux = create_stack();
   while (top(P1) != NULL) {
      void* dato = pop(P1);
      push(pAux, dato);
   }
   while (top(pAux) != NULL) {
      void* dato = pop(pAux);
      push(P1, dato);
      push(P2, dato);
   }
}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

int parentesisBalanceados(char *cadena) {
   Stack* pila = create_stack();
   for (char *c = cadena; *c != '\0'; c++) {
      if (*c == '(' || *c == '{' || *c == '[') {
         char* dato = (char*)malloc(sizeof(char));
         *dato = *c;
         push(pila, dato);
      } else if (*c == ')' || *c == '}' || *c == ']') {
         if (top(pila) == NULL) return 0; // No hay apertura para este cierre
         char* apertura = (char*)pop(pila);
         if ((*apertura == '(' && *c != ')') ||
             (*apertura == '{' && *c != '}') ||
             (*apertura == '[' && *c != ']')) {
            return 0;
         }
         free(apertura);
      }
   }
   return top(pila) == NULL; // La pila debe estar vacía si todo está balanceado
}