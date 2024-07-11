#ifndef FECHA_H
#define FECHA_H

#define esBisiesto(a) (((a) % 4 == 0 && (a) %100 != 0) || (a) % 400 == 0)

typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;

Fecha ingresarFecha();
int esFechaValida(Fecha fecha);
int cantDiasMes(int mes, int anio);

#endif // FECHA_H
