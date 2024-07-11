#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "funciones.h"

int main()
{
   char opcion;
   char pathSocios[51] = "../GenerarIndice/socios.dat";
   char pathInd[51] = "../GenerarIndice/socios.idx";
   int flag = 1;
   t_indice ind;

   time_t t = time(NULL);
   struct tm *tm = localtime(&t);

   Fecha fechaActual;
   fechaActual.dia = tm->tm_mday;
   fechaActual.mes = tm->tm_mon + 1;  // tm_mon es el mes desde enero (0-11), por eso se suma 1
   fechaActual.anio = tm->tm_year + 1900;  // tm_year es el número de años desde 1900


   ind_crear(&ind,sizeof(long),cmpLong);

   ind_cargar(&ind,pathInd);

//   ind_recorrer(&ind,mostrar_clave,&ind.tam_clave);

    FILE* archSocios = fopen(pathSocios,"r+b");

    if(!archSocios)
      return ERROR;

    do {
        if (flag) {
            printf("Bienvenido al sistema de Socios!\n\n");
            flag = 0;
        }
        printf("Que desea hacer?\n\n");
        printf("(A) Dar de alta un nuevo socio.\n");
        printf("(M) Modificar el campos del Socio a partir del DNI.\n");
        printf("(B) Dar de baja un socio cargando el Nro. Socio a eliminar.\n");
        printf("(L) Listar todos los socios ordenados (sin mostrar los dados de baja) por DNI \n");
        printf("(P) Listar los 10 socios con mayor retraso en la fecha de pago de la cuota.\n");
        printf("(S) Salir\n");
        printf("(I) (EXTRA) Mostrar Arbol de Indice en Memoria \n");

        printf("Ingrese la opcion: ");
        fflush(stdin);
        scanf("%c", &opcion);
        printf("\n");

        switch (tolower(opcion)) {
            case 'a':
                altaSocio(archSocios,&ind);
                break;
            case 'm':
                modificarSocio(archSocios,&ind);
                break;
            case 'b':
                bajaSocio(archSocios,&ind,fechaActual);
                break;
            case 'l':
                leerSociosAlta(archSocios,&ind);
                break;
            case 'i':
                recorrerEnOrdenInversoArbolBinBusq(&ind.arbol,0,NULL,imprimirConForma);
                break;
            case 'p':
                mostrarDeudores(archSocios,cmpSocioFecha);
                break;
            case 's':
                printf("\nSaliendo del sistema, que tenga un excelente dia!\n");
                fclose(archSocios);
                ind_grabar(&ind,pathInd);
                ind_vaciar(&ind);
                break;
            default:
                printf("Opcion no valida. Por favor, ingrese una opción valida.\n");
        }
    } while (opcion != 'S' && opcion != 's');
}
