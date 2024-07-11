#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../GenerarIndice/Indice.h"
#include "../GenerarIndice/Socios.h"
#include "../GenerarIndice/Fecha.h"

void altaSocio(FILE *pf,t_indice *ind);
int buscarEnVec(char vec[][10],const char *categoria);

void bajaSocio(FILE *pf, t_indice *ind, Fecha fechaActual);

void modificarSocio(FILE *pf,t_indice *ind);

int esNombreValido(const char *cadena);
void normalizarCadena(char *cadena);
void mayusculaCadena(char *cadena);

void leerSociosAlta(FILE* archivo, t_indice* ind);
void mostrarSocioAlta(const void* reg,unsigned tam_clave, void* pf);

void mostrarDeudores(FILE* arch,Cmp cmp);

int cmpLong(const void* a, const void* b);
int cmpSocioFecha(const void* e1,const void* e2);

void imprimirConForma(void* info, unsigned tam, unsigned n, void* params);
#endif // FUNCIONES_H_INCLUDED
