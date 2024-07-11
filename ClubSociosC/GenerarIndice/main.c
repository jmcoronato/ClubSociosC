#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Indice.h"
#include "Fecha.h"
#include "Socios.h"
#include "funciones.h"

/// Trabajo Practico
/// Algoritmos y Estructuras de Datos
/// Profesor: Federico Pezzola y Paola Ghigo
/// Alumno: Coronato, Juan
/// DNI: 44713835

int main() {

      t_indice ind;

      ind_crear(&ind,sizeof(long),cmpLong);

      generarIndice(&ind);


      ind_cargar(&ind,"socios.idx");

      // Descomentar para ver archivo completo e indice cargado en memoria
      printf("\n\n **ARCHIVO CSV PASADO A BINARIO** \n\n");
      leer_socios("socios.dat");
      printf("\n\n **INDICE EN MEMORIA** \n\n");
      ind_recorrer(&ind,mostrar_clave,&ind.tam_clave);

      ind_vaciar(&ind);


    return 0;
}

