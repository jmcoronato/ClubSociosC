#ifndef SOCIOS_H_INCLUDED
#define SOCIOS_H_INCLUDED

#include "Fecha.h"

typedef struct
{
    long dni;
    char ap[61];
    char nom[61];
    Fecha fecha_nac;
    char sexo;
    Fecha fecha_afiliacion;
    char categoria[11];
    Fecha fecha_pago;
    char estado;
    Fecha fecha_baja;
} Socio;

#endif // SOCIOS_H_INCLUDED
