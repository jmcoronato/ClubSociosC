#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "funciones.h"
#include "../GenerarIndice/Indice.h"
#include "../GenerarIndice/Socios.h"
#include "../GenerarIndice/Fecha.h"
#include "Lista.h"

void altaSocio(FILE *pf,t_indice *ind)
{
    Socio reg;
    char catValidas[6][10]={"MENOR", "CADETE", "ADULTO", "VITALICIO","HONORARIO", "JUBILADO"};
    int flag = 1;
    unsigned nro_reg;

    do{
        if(flag)
            flag=0;
        else
            printf("DNI invalido\n");
        printf("Ingrese DNI socio: ");
        scanf("%ld",&reg.dni);
    }while(10000>=reg.dni||reg.dni>=100000000);

    flag=1;
    if(ind_buscar(ind,&reg.dni,&nro_reg))
    {
       fseek(pf,sizeof(Socio)*nro_reg,SEEK_SET);
       fread(&reg,sizeof(Socio),1,pf);
       if((reg.estado) == 'A')   ///Socio activo
       {
         printf("Socio ya activo!\n");
         fseek(pf,0,SEEK_SET);
         return;
       }

    }

    do
   {
      if(flag)
         flag = 0;
      else
         printf("Nombre invalido\n");

      puts("Ingrese el o los nombres del Socio:");
      fflush(stdin);
      gets(reg.nom);
      normalizarCadena(reg.nom);
   }while(!(esNombreValido(reg.nom)));
   flag = 1;
    do
   {
      if(flag)
         flag = 0;
      else
         printf("Apellido invalido\n");

      puts("Ingrese el Apellido del Socio:");
      fflush(stdin);
      gets(reg.ap);
      normalizarCadena(reg.ap);
   }while(!(esNombreValido(reg.ap)));

   flag = 1;
    do
       {
         if(flag)
            flag = 0;
         else
            printf("\nFormato de fecha incorrecto\n\n");

         printf("\nIngrese la fecha de nacimiento (DD/MM/AAAA)\n\n");

         reg.fecha_nac = ingresarFecha();

       }while(!(esFechaValida(reg.fecha_nac)));

    printf("Ingrese Sexo (M: Masculino/F: Femenino/O: Otro): ");
    fflush(stdin);
    scanf("%c",&reg.sexo);
    reg.sexo=toupper(reg.sexo);
    while(reg.sexo != 'M' && reg.sexo != 'F' && reg.sexo != 'O')
    {
      printf("Letra Incorrecta. Ingrese uno de los siguientes valores (M: Masculino/F: Femenino/O: Otro): ");
      fflush(stdin);
      scanf("%c",&reg.sexo);
      reg.sexo=toupper(reg.sexo);
    }

    flag = 1;

    do
       {
         if(flag)
            flag = 0;
         else
            printf("\nFormato de fecha incorrecto\n\n");

         printf("\nIngrese la fecha Afiliacion (DD/MM/AAAA)\n\n");

         reg.fecha_afiliacion = ingresarFecha();

       }while(!(esFechaValida(reg.fecha_afiliacion)));

       reg.fecha_pago = reg.fecha_afiliacion;

    printf("Ingrese categoria ('MENOR', 'CADETE', 'ADULTO', 'VITALICIO','HONORARIO', 'JUBILADO'): ");
    fflush(stdin);
    scanf("%s",reg.categoria);

    while(!buscarEnVec(catValidas,reg.categoria))
    {
        printf("Categoria invalida, ingrese nuevamenete ('MENOR', 'CADETE', 'ADULTO', 'VITALICIO','HONORARIO', 'JUBILADO'):");
        fflush(stdin);
        scanf("%s",reg.categoria);
    }
    mayusculaCadena(reg.categoria);

    reg.fecha_baja.anio = 0;
    reg.fecha_baja.mes = 0;
    reg.fecha_baja.dia = 0;

   reg.estado = 'A';
   fseek(pf,0,SEEK_END);
   nro_reg = (ftell(pf)/sizeof(Socio));
   ind_insertar(ind,&reg.dni,nro_reg);
   fwrite(&reg,sizeof(Socio),1,pf);

    fseek(pf,0,SEEK_SET);
    printf("\nSocio dado de Alta Exitosamente!\n");
}

int buscarEnVec(char vec[][10],const char *categoria)
{
    int cmp,i=0;

    while((cmp=strcmpi(vec[i],categoria)) && i<6)
    {
       i++;
    }

    if(cmp==0)
        return 1;

    return 0;
}

void bajaSocio(FILE *pf, t_indice *ind, Fecha fechaActual)
{
    long int dniSocio;
    unsigned nroReg;
    Socio reg;

    printf("Ingrese DNI de Socio que desea dar de baja:");

    scanf("%ld",&dniSocio);

    if( (ind_eliminar(ind,&dniSocio,&nroReg))== ERROR)
    {
        printf("Socio no encontrado\n");
        return;
    }

    fseek(pf,nroReg*(sizeof(Socio)),SEEK_SET);
    fread(&reg,sizeof(Socio),1,pf);
    reg.fecha_baja = fechaActual;
    reg.estado='I';
    fseek(pf,nroReg*(sizeof(Socio)),SEEK_SET);
    fwrite(&reg,sizeof(Socio),1,pf);
    fseek(pf,0,SEEK_SET);
    printf("\nSocio dado de baja exitosamente.\n");
}

void leerSociosAlta(FILE* archivo, t_indice* ind)
{
   ind_recorrer(ind,mostrarSocioAlta,archivo);
   fseek(archivo,0,SEEK_SET);
}

void mostrarSocioAlta(const void* reg,unsigned tam, void* pf)
{
   FILE* archivo = (FILE*)pf;
   Socio socio;
   unsigned nroReg = *(int*)(reg+sizeof(unsigned));

   fseek(archivo,nroReg*sizeof(Socio),SEEK_SET);
   fread(&socio,sizeof(Socio),1,archivo);
   printf("DNI: %ld\n", socio.dni);
   printf("Apellido/s: %s\n", socio.ap);
   printf("Nombre/s: %s\n", socio.nom);
   printf("Fecha de Nacimiento: %d/%d/%d\n", socio.fecha_nac.dia, socio.fecha_nac.mes, socio.fecha_nac.anio);
   printf("Sexo: %c\n", socio.sexo);
   printf("Fecha de Afiliacion: %d/%d/%d\n", socio.fecha_afiliacion.dia, socio.fecha_afiliacion.mes, socio.fecha_afiliacion.anio);
   printf("Categoria: %s\n", socio.categoria);
   printf("Fecha de Pago: %d/%d/%d\n", socio.fecha_pago.dia, socio.fecha_pago.mes, socio.fecha_pago.anio);
   printf("Estado: %c\n\n", socio.estado);
}

void modificarSocio(FILE *pf,t_indice *ind)
{
   long int dniSocio;
   unsigned nroReg;
   int flag = 1;
   Socio reg;
   char opcion;
   char catValidas[6][10]={"MENOR", "CADETE", "ADULTO", "VITALICIO","HONORARIO", "JUBILADO"};

    printf("Ingrese DNI del socio a modificar:");

    scanf("%ld",&dniSocio);

    if((ind_buscar(ind,&dniSocio,&nroReg))== ERROR)
    {
        printf("Socio no encontrado\n");
        return;
    }

   fseek(pf,nroReg*(sizeof(Socio)),SEEK_SET);
   fread(&reg,sizeof(Socio),1,pf);

    do {
        printf("Que desea Modificar?\n\n");
        printf("(A) Modificar Apellido.\n");
        printf("(N) Modificar Nombre.\n");
        printf("(C) Modificar Categoria.\n");
        printf("(E) Modificar Sexo \n");
        printf("(F) Modificar Fecha de Ultima Cuota Paga.\n");
        printf("(S) Salir de la modificacion de Socio\n");

        printf("Ingrese la opcion: ");
        fflush(stdin);
        scanf("%c", &opcion);
        printf("\n");

        switch (tolower(opcion)) {
            case 'a':
                 do
                     {
                        if(flag)
                           flag = 0;
                        else
                           printf("Apellido invalido\n");

                        puts("Ingrese el Apellido del Socio:");
                        fflush(stdin);
                        gets(reg.ap);
                        normalizarCadena(reg.ap);
                     }while(!(esNombreValido(reg.ap)));
                     flag = 1;
                     printf("\nApellido de Socio modificado exitosamente.\n");
                  break;
            case 'n':
                  do
                     {
                        if(flag)
                           flag = 0;
                        else
                           printf("Nombre invalido\n");

                        puts("Ingrese el Nombre del Socio:");
                        fflush(stdin);
                        gets(reg.nom);
                        normalizarCadena(reg.nom);
                     }while(!(esNombreValido(reg.nom)));
                     flag = 1;
                     printf("\nNombre de Socio modificado exitosamente.\n");
                break;
            case 'c':
                   printf("Ingrese categoria ('MENOR', 'CADETE', 'ADULTO', 'VITALICIO','HONORARIO', 'JUBILADO'): ");
                   fflush(stdin);
                   scanf("%s",reg.categoria);

                   while(!buscarEnVec(catValidas,reg.categoria))
                   {
                       printf("Categoria invalida, ingrese nuevamenete ('MENOR', 'CADETE', 'ADULTO', 'VITALICIO','HONORARIO', 'JUBILADO'):");
                       fflush(stdin);
                       scanf("%s",reg.categoria);
                   }
                   mayusculaCadena(reg.categoria);
                   printf("\nCategoria de Socio modificada exitosamente.\n");
                break;
            case 'e':
                printf("Ingrese Sexo (M: Masculino/F: Femenino/O: Otro): ");
                fflush(stdin);
                scanf("%c",&reg.sexo);
                reg.sexo=toupper(reg.sexo);
                while(reg.sexo != 'M' && reg.sexo != 'F' && reg.sexo != 'O')
                {
                  printf("Letra Incorrecta. Ingrese uno de los siguientes valores (M: Masculino/F: Femenino/O: Otro): ");
                  fflush(stdin);
                  scanf("%c",&reg.sexo);
                  reg.sexo=toupper(reg.sexo);
                }
                printf("\nSexo de Socio/a modificado exitosamente.\n");
                break;
            case 'f':
               do
                {
                  if(flag)
                     flag = 0;
                  else
                     printf("\nFormato de fecha incorrecto\n\n");

                  printf("\nIngrese la Ultima Fecha de Pago del Socio (DD/MM/AAAA)\n\n");

                  reg.fecha_pago = ingresarFecha();

                }while(!(esFechaValida(reg.fecha_pago)));
                printf("\nFecha de Pago del Socio modificada exitosamente.\n");
                break;
            case 's':
                printf("\nSaliendo de la modificacion del socio...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, ingrese una opción valida.\n");
        }
    } while (opcion != 'S' && opcion != 's');


   fseek(pf,nroReg*(sizeof(Socio)),SEEK_SET);
   fwrite(&reg,sizeof(Socio),1,pf);
   fseek(pf,0,SEEK_SET);
}

int esNombreValido(const char *cadena) {
    /// Verificar si la cadena está vacía
    if (cadena == NULL || *cadena == '\0') {
        return 0;  /// No es un nombre válido
    }

    /// Recorrer la cadena para verificar cada carácter
    while (*cadena != '\0') {
        /// Verificar si el carácter no es una letra
        if ((!isalpha(*cadena)) && *cadena != ' ') {
            return 0;  /// No es un nombre válido
        }
        cadena++;  /// Mover al siguiente carácter
    }

    return 1;  /// Es un nombre válido
}

void normalizarCadena(char *cadena) {
    /// Verificar si la cadena está vacía
    if (cadena == NULL || *cadena == '\0') {
        return;  /// No hay nada que normalizar
    }

    /// Convertir la primera letra a mayúscula
    *cadena = toupper(*cadena);

    /// Recorrer la cadena para convertir las demás letras a minúsculas
    while (*(++cadena) != '\0') {
        *cadena = tolower(*cadena);
        if(*cadena == ' ')
        {
           cadena++;
           *cadena = toupper(*cadena);
        }
    }
}

void mayusculaCadena(char *cadena) {
    /// Verificar si la cadena está vacía
    if (cadena == NULL || *cadena == '\0') {
        return;  // No hay nada que normalizar
    }

    /// Recorrer la cadena para convertir las letras a minusculas
    while (*(cadena) != '\0')
    {
       *cadena = toupper(*cadena);
       cadena++;
    }

}

void mostrarDeudores(FILE* arch,Cmp cmp)
{
   t_lista lista;
   crear_lista(&lista);
   Socio socio;
   int i = 0;
   fseek(arch,0L,SEEK_SET);
   fread(&socio,sizeof(Socio),1,arch);

   while(!feof(arch))
   {
      insertar_en_orden_lista(&lista,&socio,sizeof(Socio),cmp);
      fread(&socio,sizeof(Socio),1,arch);
   }

   while(i<10 && !lista_vacia(&lista))
   {
      sacar_primero_de_lista(&lista,&socio,sizeof(Socio));
      if(socio.estado=='A')
        {
            i++;
            printf("DNI: %ld\n", socio.dni);
            printf("Apellido/s: %s\n", socio.ap);
            printf("Nombre/s: %s\n", socio.nom);
            printf("Fecha de Nacimiento: %d/%d/%d\n", socio.fecha_nac.dia, socio.fecha_nac.mes, socio.fecha_nac.anio);
            printf("Sexo: %c\n", socio.sexo);
            printf("Fecha de Afiliacion: %d/%d/%d\n", socio.fecha_afiliacion.dia, socio.fecha_afiliacion.mes, socio.fecha_afiliacion.anio);
            printf("Categoria: %s\n", socio.categoria);
            printf("Fecha de Pago: %d/%d/%d\n", socio.fecha_pago.dia, socio.fecha_pago.mes, socio.fecha_pago.anio);
            printf("Estado: %c\n\n", socio.estado);
        }
   }
   vaciar_lista(&lista);
}

int cmpSocioFecha(const void* e1,const void* e2)
{
   Socio f1 = *(Socio*)e1;
   Socio f2 = *(Socio*)e2;

   if(f1.fecha_pago.anio!=f2.fecha_pago.anio)
      return f1.fecha_pago.anio-f2.fecha_pago.anio;

   if(f1.fecha_pago.mes!=f2.fecha_pago.mes)
      return f1.fecha_pago.mes-f2.fecha_pago.mes;

   return f1.fecha_pago.dia-f2.fecha_pago.dia;
}

int cmpLong(const void* a, const void* b)
{
   return *(long*)a - *(long*)b;
}

void imprimirConForma(void* info, unsigned tam, unsigned n, void* params)
{
   printf("%*s-%3d-\n",n*3,"",*(int*)info);
}
