#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define LISTA_LLENA 0
#define DUPLICADO 4
#define NO_EXISTE 5
#define ASCENDENTE 1
#define DESCENDENTE -1

#define min(x,y) ((x) <= (y) ? (x) : (y))

typedef int(*Cmp)(const void*, const void*);
typedef void(*Accion)(void*,void*);

typedef struct s_nodo
{
    void* info;
    size_t tam;
    struct s_nodo* sig;
} t_nodo;

typedef t_nodo* t_lista;

int poner_al_final_lista(t_lista *pl,const void *pd, size_t tam);
int insertar_en_lista(t_lista *pl,const void *pd, size_t tam, unsigned pos);
int insertar_en_orden_lista(t_lista *pl,const void *pd, size_t tam, Cmp cmp);
int insertar_al_final_lista(t_lista *pl,const void *pd, size_t tam);
int sacar_de_lista(t_lista *pl, void *pd, size_t tam, Cmp cmp);
int sacar_primero_de_lista(t_lista *pl, void *pd, size_t tam);
int insertar_al_inicio_lista(t_lista *pl,const void *pd, size_t tam);

int sacar_de_lista_ordenada(t_lista *pl, void *pd, size_t tam, Cmp cmp);

int buscar_en_lista(t_lista *pl, void *pd, size_t tam, Cmp cmp);
int devolver_posicion_de_lista(t_lista *pl, void *pd, size_t tam, Cmp cmp);

int lista_vacia(t_lista *pl);
void crear_lista(t_lista *pl);
void vaciar_lista(t_lista *pl);

void ordenarLista(t_lista* pl, Cmp cmp, int sentido);
void ordenarLista2(t_lista* pl, Cmp cmp);

void OrdenarSeleccionLista(t_lista* pl, Cmp cmp);
t_nodo** buscarMenorNodoLista(const t_lista* pl, Cmp cmp);
void intercambiarInfoNodoLista(t_lista* nodo1, t_lista* nodo2);

int eliminarDeListaOrdDuplicados(t_lista* pl, Cmp cmp); /// Revisar esta funcion

void recorrerLista(t_lista* pl, Accion accion, void* extra);

void invertirLista(t_lista *pl, Cmp cmp);
void crearListaInvertida(t_lista *pl,t_lista *pl2, Cmp cmp);

t_nodo* crearNodo(size_t tamInfo);
void destruirNodo(t_nodo* nodo);

int sacar_de_lista2(t_lista *pl, void *pd, size_t tam, Cmp cmp);
void vaciarLista(t_lista *pl);
int insertar_al_final_lista2(t_lista *pl,const void *pd, size_t tam);
int insertar_en_orden_lista2(t_lista *pl,const void *pd, size_t tam, Cmp cmp);

#endif // LISTA_H_INCLUDED
