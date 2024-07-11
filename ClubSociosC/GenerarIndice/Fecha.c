#include <stdio.h>
#include "Fecha.h"

Fecha ingresarFecha()
{
    Fecha f;
    fflush(stdin);
    scanf("%d/%d/%d", &f.dia, &f.mes, &f.anio);
    return f;
}

int esFechaValida(Fecha fecha)
{
    if(fecha.anio >= 1601 && fecha.anio <= 9999)
        if(fecha.mes >= 1 && fecha.mes <= 12)
            if(fecha.dia >= 1 && fecha.dia <= cantDiasMes(fecha.mes, fecha.anio))
                return 1;

    return 0;
}

int cantDiasMes(int mes, int anio)
{
    static int cdm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && esBisiesto(anio))
        return 29;

    return cdm[mes];
}
