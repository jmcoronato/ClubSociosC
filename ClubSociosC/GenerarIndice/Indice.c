#include "Indice.h"

void ind_crear (t_indice* ind, size_t tam_clave, Cmp cmp)
{
    crearArbolBinBusq(&(ind->arbol));
    ind->tam_clave = tam_clave;
    ind->cmp = cmp;
    ind->reg_ind = malloc(ind->tam_clave+sizeof(unsigned));
}

int ind_insertar (t_indice* ind, void *clave, unsigned nro_reg)
{
    int r;

    memcpy(ind->reg_ind,clave,ind->tam_clave);
    memcpy(ind->reg_ind+ind->tam_clave,&nro_reg,sizeof(unsigned));

    r = insertarArbolBinBusq(&ind->arbol,ind->reg_ind,(ind->tam_clave+sizeof(unsigned)),ind->cmp);

    return r==1 ? OK : ERROR;
}

int ind_eliminar (t_indice* ind, void *clave, unsigned* nro_reg)
{
    int r;

    memcpy(ind->reg_ind,clave,ind->tam_clave);

    r = eliminarElemArbolBinBusq(&ind->arbol,ind->reg_ind,(ind->tam_clave+sizeof(unsigned)),ind->cmp);

    if(r==NO_EXISTE)
        return ERROR;

    memcpy(nro_reg,ind->reg_ind+ind->tam_clave,sizeof(unsigned));

    return OK;
}

int ind_buscar (const t_indice* ind, void *clave, unsigned* nro_reg)
{
    int r;

    memcpy(ind->reg_ind,clave,ind->tam_clave);

    r = buscarElemArbolBinBusq(&ind->arbol,ind->reg_ind,(ind->tam_clave+sizeof(unsigned)),ind->cmp);

    if(r==NO_EXISTE)
        return ERROR;

    memcpy(nro_reg,ind->reg_ind+ind->tam_clave,sizeof(unsigned));

    return OK;
}

void ind_vaciar (t_indice* ind)
{
    vaciarArbolBin(&(ind->arbol));
    free(ind->reg_ind);
    ind = NULL;
}

int ind_grabar (const t_indice* ind, const char* path)
{
   int r;
   r = grabarEnArchivoOrdenadoArbolBin(&(ind->arbol),path);
   return r == 1 ? OK : ERROR;
}

int ind_cargar(t_indice* ind, const char* path)
{
   int r;
   r = cargarArchivoBinOrdenadoArbolBinBusq(&ind->arbol,path,ind->tam_clave+sizeof(unsigned));
   return r == 1 ? OK : ERROR;
}

int ind_recorrer (const t_indice* ind, void (*accion)(const void *, unsigned, void *),void* param)
{
   recorrerEnOrdenSimpleArbolBinBusq(&ind->arbol,param,accion);
   return OK;
}



void mostrar_clave(const void* dato, unsigned tam, void* param)
{
   int clave = *(int*)dato;
   unsigned tamClave = *(unsigned*)param;
   unsigned reg = *(unsigned*)(dato+tamClave);
   printf("Clave: %d Registro: %d\n",clave,reg);
}
