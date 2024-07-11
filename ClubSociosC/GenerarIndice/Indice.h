#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAArbol.h"

#define min(x,y) ((x) <= (y) ? (x) : (y))
#define max(x,y) ((x) <= (y) ? (y) : (x))
#define OK 1
#define ERROR 0

typedef struct
{
    size_t tam_clave;
    Cmp cmp;
    tArbolBinBusq arbol;
    void* reg_ind;
} t_indice;

void ind_crear (t_indice* ind, size_t tam_clave, Cmp cp);
int ind_insertar (t_indice* ind, void *clave, unsigned nro_reg);
int ind_eliminar (t_indice* ind, void *clave, unsigned* nro_reg);
int ind_buscar (const t_indice* ind, void *clave, unsigned* nro_reg);
void ind_vaciar (t_indice* ind);
int ind_grabar (const t_indice* ind, const char* path);
int ind_cargar(t_indice* ind, const char* path);
int ind_recorrer (const t_indice* ind, void (*accion)(const void *, unsigned, void *),void* param);

void mostrar_clave(const void* dato, unsigned tam, void* param);


#endif // INDICE_H_INCLUDED
