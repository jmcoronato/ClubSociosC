#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "Indice.h"

int cmpLong(const void* a, const void* b);
int archTxtABin(const char* nombreArchBin, const char* nombreArchTxt);
void leer_socios(const char* nombre_archivo);
int binAindice(t_indice *ind, const char *path);
int generarIndice(t_indice *ind);

#endif // FUNCIONES_H_INCLUDED
