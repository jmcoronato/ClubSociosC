#include "TDAArbol.h"
#define min(x,y) x<y ? x : y
#define max(x,y) x>y ? x : y
void vaciarArbolBin(tArbolBinBusq *p)
{
   if(!*p)
      return;

   vaciarArbolBin(&(*p)->izq);
   vaciarArbolBin(&(*p)->der);

   free((*p)->info);
   free((*p));
   *p = NULL;
}

int eliminarElemArbolBinBusq(tArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *))
{
   int comp;
   while(*p && (comp =cmp(d,(*p)->info))!= 0)
   {
      if(comp<0)
         p = &(*p)->izq;
      else
         p = &(*p)->der;
   }
   if(comp != 0)
      return NO_EXISTE;
   memcpy(d,(*p)->info,min(tam,(*p)->tamInfo));
   return eliminarRaizArbolBinBusq(p);

}

int buscarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *))
{
   int comp;
   while(*p && (comp =cmp(d,(*p)->info))!= 0)
   {
      if(comp<0)
         p = &(*p)->izq;
      else
         p = &(*p)->der;
   }
   if(comp != 0)
      return NO_EXISTE;
   memcpy(d,(*p)->info,min(tam,(*p)->tamInfo));
   return TODO_OK;
}

int eliminarRaizArbolBinBusq(tArbolBinBusq *p)
{
   int hi, hd;
   tArbolBinBusq* reemplazo;
   tNodoArbol* elim;

   if(!*p)
      return NO_EXISTE;

   if(!(*p)->izq && !(*p)->der)
   {
      free((*p)->info);
      free(*p);
      *p = NULL;
      return TODO_OK;
   }

   hi = alturaArbolBin(&(*p)->izq);
   hd = alturaArbolBin(&(*p)->der);

   reemplazo = (hi>hd ? mayorNodo(&(*p)->izq) : menorNodo(&(*p)->der));

   elim = *reemplazo;

   (*p)->info = elim->info;
   (*p)->tamInfo = elim->tamInfo;

   *reemplazo = elim->izq ? elim->izq : elim->der;

   free(elim);

   return TODO_OK;

}

unsigned alturaArbolBin(const tArbolBinBusq *p)
{
   unsigned hi, hd;
   if(!*p)
      return 0;

   hi = alturaArbolBin(&(*p)->izq);
   hd = alturaArbolBin(&(*p)->der);

   return max(hi,hd)+1;
}

tArbolBinBusq* mayorNodo(tArbolBinBusq *p)
{
   while((*p)->der)
      p = &(*p)->der;
   return p;
}
tArbolBinBusq* menorNodo(tArbolBinBusq *p)
{
   while((*p)->izq)
      p = &(*p)->izq;
   return p;
}

int grabarEnArchivoOrdenadoArbolBin(const tArbolBinBusq *p, const char * path)
{

   FILE* pf = fopen(path,"wb");
   if(!pf)
      return ERROR_ARCHIVO;
   if(!*p)
   {
      fclose(pf);
      return 0; /// Arbol vacio
   }
   recorrerEnOrdenSimpleArbolBinBusq(p,pf,grabarBin);
   fclose(pf);
   return TODO_OK;
}

void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params,
                                       void (*accion)(const void *, unsigned, void *))
{
   if(!*p)
      return;
   recorrerEnOrdenSimpleArbolBinBusq(&(*p)->izq,params,accion);
   accion((*p)->info,(*p)->tamInfo,params);
   recorrerEnOrdenSimpleArbolBinBusq(&(*p)->der,params,accion);
}

void grabarBin(const void* pd, unsigned tam, void* arch)
{
   fwrite(pd,tam,1,(FILE*)arch);
}

void crearArbolBinBusq(tArbolBinBusq *p)
{
   *p = NULL;
}

int cargarArchivoBinOrdenadoArbolBinBusq(tArbolBinBusq * p, const char * path,
                                         unsigned tamInfo)
{
   unsigned cantReg;
   if(*p)
      return SIN_INICIALIZAR;
   FILE* pf = fopen(path,"rb");
   if(!pf)
      return ERROR_ARCHIVO;
   fseek(pf,0,SEEK_END);
   cantReg = ftell(pf)/tamInfo;
   cargarDesdeDatosOrdenadosArbol(p,pf,leerBin,0,cantReg-1,&tamInfo);

   fclose(pf);
   return TODO_OK;
}

unsigned leerBin(void** d, void* pf,unsigned pos, void* params)
{
   unsigned tam = *((int*)params);
   *d = malloc(tam);
   if(!*d)
      return 0;
   fseek((FILE*)pf,tam*pos,SEEK_SET);
//   return fread(*d,tam,1,(FILE*)pf);
   if(fread(*d,tam,1,(FILE*)pf))
      return tam;
   return 0;

}

int cargarDesdeDatosOrdenadosArbol(tArbolBinBusq *p,
                        void *ds,
                        unsigned (*leer)(void **, void *, unsigned, void *params), int li, int ls,
                        void * params)
{
   if(li>ls)
      return TODO_OK;
   int m = (li + ls)/2, r;
   *p = (tNodoArbol*)malloc(sizeof(tNodoArbol));
   if(!*p || !((*p)->tamInfo = leer(&(*p)->info,ds,m,params)))
   {
      free(*p);
      return 0;
   }
   (*p)->izq = (*p)->der = NULL;
   if((r = cargarDesdeDatosOrdenadosArbol(&(*p)->izq,ds,leer,li,m-1,params))!= TODO_OK)
      return r;
   return cargarDesdeDatosOrdenadosArbol(&(*p)->der,ds,leer,m+1,ls,params);
}

int insertarArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam,
                         int (*cmp)(const void *, const void *))
{
   int comp;
   tNodoArbol* nue;
   while(*p)
   {
      if( (comp = cmp(d,(*p)->info)) < 0)
         p = &(*p)->izq;
      else if(comp > 0)
          p = &(*p)->der;
      else
         return DUPLICADO;
   }
   if(!(nue = malloc(sizeof(tNodoArbol))) || !(nue->info = malloc(tam)))
   {
      free(nue);
      return SIN_MEM;
   }
   memcpy(nue->info,d,tam);
   nue->tamInfo = tam;
   nue->izq = nue->der = NULL;
   *p = nue;
   return TODO_OK;
}

int arbolVacio(tArbolBinBusq *p)
{
   return !*p;
}

void recorrerEnOrdenInversoArbolBinBusq(const tArbolBinBusq * p, unsigned n, void * params,
                                        void (*accion)(void *, unsigned, unsigned, void *))
{
   if(!*p)
      return;
   recorrerEnOrdenInversoArbolBinBusq(&(*p)->der, n+1, params,accion);
   accion((*p)->info,(*p)->tamInfo,n,params);
   recorrerEnOrdenInversoArbolBinBusq(&(*p)->izq,n+1,params,accion);
}

