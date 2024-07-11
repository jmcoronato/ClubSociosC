#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Indice.h"
#include "Fecha.h"
#include "Socios.h"
#include "funciones.h"

int cmpLong(const void* a, const void* b)
{
   return *(long*)a - *(long*)b;
}

int archTxtABin(const char* nombreArchBin, const char* nombreArchTxt)
{
    FILE* archBin = fopen(nombreArchBin, "wb");

    if(!archBin)
        return ERROR;

    FILE* archTxt = fopen(nombreArchTxt, "rt");

    if(!archTxt)
        return ERROR;

    char* formatoTxt = "%ld,%[^,],%[^,],%d/%d/%d,%c,%d/%d/%d,%[^,],%d/%d/%d,%c,%d/%d/%d\n";

    Socio socio;

    while
    (
        fscanf
        (
            archTxt,formatoTxt,
            &socio.dni, socio.ap, socio.nom,
                    &socio.fecha_nac.dia, &socio.fecha_nac.mes, &socio.fecha_nac.anio,
                    &socio.sexo,
                    &socio.fecha_afiliacion.dia, &socio.fecha_afiliacion.mes, &socio.fecha_afiliacion.anio,
                    socio.categoria,
                    &socio.fecha_pago.dia, &socio.fecha_pago.mes, &socio.fecha_pago.anio,
                    &socio.estado,
                    &socio.fecha_baja.dia, &socio.fecha_baja.mes, &socio.fecha_baja.anio
        ) != EOF
    )
    {
		fwrite(&socio, sizeof(Socio), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return OK;
}

void leer_socios(const char* nombre_archivo)
{
    FILE* archivo = fopen(nombre_archivo, "rb");

    if (archivo != NULL)
    {
        Socio socio;

        while (fread(&socio, sizeof(Socio), 1, archivo) == 1)
        {
            printf("DNI: %ld\n", socio.dni);
            printf("Apellido/s: %s\n", socio.ap);
            printf("Nombre/s: %s\n", socio.nom);
            printf("Fecha de Nacimiento: %d/%d/%d\n", socio.fecha_nac.dia, socio.fecha_nac.mes, socio.fecha_nac.anio);
            printf("Sexo: %c\n", socio.sexo);
            printf("Fecha de Afiliacion: %d/%d/%d\n", socio.fecha_afiliacion.dia, socio.fecha_afiliacion.mes, socio.fecha_afiliacion.anio);
            printf("Categoria: %s\n", socio.categoria);
            printf("Fecha de Pago: %d/%d/%d\n", socio.fecha_pago.dia, socio.fecha_pago.mes, socio.fecha_pago.anio);
            printf("Estado: %c\n", socio.estado);
            printf("Fecha de Baja: %d/%d/%d\n\n", socio.fecha_baja.dia, socio.fecha_baja.mes, socio.fecha_baja.anio);
        }

        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

int binAindice(t_indice *ind, const char *path)
{
    FILE *pf;
    Socio reg;
    int nroReg=0;

    if(!(pf=fopen(path,"rb")))
        return ERROR;

    fread(&reg,sizeof(Socio),1,pf);
    while(!feof(pf))
    {
      if(reg.estado == 'A')
         ind_insertar(ind,&reg.dni,nroReg);
      fread(&reg,sizeof(Socio),1,pf);
      nroReg++;
    }

    fclose(pf);
    return OK;
}

int generarIndice(t_indice *ind)
{
   char pathTxt[200];
   char pathBin[200];
   char pathIdx[200];
   char* act;

   printf("Escriba la ruta del archivo de texto de Socios: ");

   gets(pathTxt);

   strcpy(pathBin,pathTxt);

   act = strchr(pathBin,'.');

   strcpy(act,".dat");

   strcpy(pathIdx,pathTxt);

   act = strchr(pathIdx,'.');

   strcpy(act,".idx");

   if( archTxtABin(pathBin,pathTxt) && binAindice(ind,pathBin) && ind_grabar(ind,pathIdx))
      return OK;
   return ERROR;
}
