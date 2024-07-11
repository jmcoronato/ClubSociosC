#include "Lista.h"

int poner_al_final_lista(t_lista *pl,const void *pd, size_t tam)    /// Si le saco el while, es igual al poner en pila dinamica!!!
{
    t_nodo* nue;

    while(!*pl)  /// Mientras exista la lista voy a recorrer
        pl = &(*pl)->sig; /// Quiero la direccion del siguiente nodo al que apunta la lista

     nue = (t_nodo*)malloc(sizeof(t_nodo));

     if(!nue)
        return LISTA_LLENA;

     nue->info = malloc(tam);

     if(!nue->info)
     {
         free(nue);
         return LISTA_LLENA;
     }


    nue->tam = tam;

    memcpy(nue->info,pd,tam);

    nue->sig = *pl; /// NULL
    *pl = nue;      /// Hago que la direccion que apuntaba el que antes era el ultimo nodo, ahora apunte al nuevo nodo (t_nodo*)
                    /// Hago el "ENGANCHE" de la lista

    return OK;
}

int insertar_en_lista(t_lista *pl,const void *pd, size_t tam, unsigned pos)    /// Si le saco el while, es igual al poner en pila dinamica!!!
{
    t_nodo* nue;

    while(*pl != NULL && pos != 0)
    {
        pl = &(*pl)->sig;
        pos--;
    }


     nue = (t_nodo*)malloc(sizeof(t_nodo));

     if(!nue)
        return LISTA_LLENA;

     nue->info = malloc(tam);

     if(!nue->info)
     {
         free(nue);
         return LISTA_LLENA;
     }


    nue->tam = tam;

    memcpy(nue->info,pd,tam);

    nue->sig = *pl; /// Pl apunta al  siguiente nodo al que quiero insertar

    *pl = nue;      /// Hago que la direccion que apuntaba el que antes era el ultimo nodo, ahora apunte al nuevo nodo (t_nodo*)

    return OK;
}

int insertar_en_orden_lista(t_lista *pl,const void *pd, size_t tam, Cmp cmp)
{
    t_nodo* nue;
    int comp;

    while(*pl != NULL && (comp = cmp(pd, (*pl)->info))>0)
    {
        pl = &(*pl)->sig;
        if(*pl && !comp)
            return DUPLICADO;   /// Si hay datos y la comparacion a 0 no inserta y retorna duplicado
    }


     nue = (t_nodo*)malloc(sizeof(t_nodo));

     if(!nue)
        return LISTA_LLENA;

     nue->info = malloc(tam);

     if(!nue->info)
     {
         free(nue);
         return LISTA_LLENA;
     }

    nue->tam = tam;

    memcpy(nue->info,pd,tam);

    nue->sig = *pl;
    *pl = nue;

    return OK;
}

int insertar_al_final_lista(t_lista *pl,const void *pd, size_t tam)
{
   t_nodo* nue;

    while(*pl)
        pl = &(*pl)->sig;

     nue = (t_nodo*)malloc(sizeof(t_nodo));

     if(!nue)
        return LISTA_LLENA;

     nue->info = malloc(tam);

     if(!nue->info)
     {
         free(nue);
         return LISTA_LLENA;
     }

    nue->tam = tam;

    memcpy(nue->info,pd,tam);

    nue->sig = *pl;  /// NULL
    *pl = nue;

    return OK;
}

int sacar_de_lista(t_lista *pl, void *pd, size_t tam, Cmp cmp)
{
    t_nodo* elim;

    while(*pl && cmp(pd,(*pl)->info) != 0 ) /// si ponemos > 0, saca de lista ordenada
        pl = &(*pl)->sig;

    if(!*pl)
        return NO_EXISTE;

   /// Desenganch
    elim = *pl;
    *pl = elim->sig;

    memcpy(pd,elim->info,min(tam,elim->tam));   /// Copio el dato a eliminar en el puntero del dato asi no perdemos la informacion

    free(elim->info);
    free(elim);

    return OK;
}

int sacar_de_lista_ordenada(t_lista *pl, void *pd, size_t tam, Cmp cmp)
{
    int comp;
    t_nodo* elim;

    while(*pl && (comp = cmp(pd,(*pl)->info) > 0 ))
        pl = &(*pl)->sig;

    if(!*pl || comp)
        return NO_EXISTE;

    elim = *pl;

    *pl = elim->sig;

    memcpy(pd,elim->info,min(tam,elim->tam));   /// Copio el dato a eliminar en el puntero del dato asi no perdemos la informacion

    free(elim->info);
    free(elim);

    return OK;
}

int buscar_en_lista(t_lista *pl, void *pd, size_t tam, Cmp cmp)
{
    t_nodo* busc;

    while(*pl && cmp(pd,(*pl)->info) != 0 )
        pl = &(*pl)->sig;

    if(!*pl)
        return NO_EXISTE;

    busc = *pl;

    memcpy(pd,busc->info,min(tam,busc->tam));

    return OK;
}

int devolver_posicion_de_lista(t_lista *pl, void *pd, size_t tam, Cmp cmp)
{
    int i = 0;

    while(*pl && cmp(pd,(*pl)->info) != 0 )
    {
        pl = &(*pl)->sig;
        i++;
    }


    if(!*pl)
        return NO_EXISTE;

    return i;
}

int lista_vacia(t_lista *pl)
{
    return !*pl;
}

void crear_lista(t_lista *pl)
{
    *pl = NULL;
}

void vaciar_lista(t_lista *pl)
{
    t_nodo* nae;

    while(*pl)
    {
        nae = *pl;      /// 1: Nodo a eliminar que apunte al tope que se va a eliminar
        *pl = nae->sig;  ///2: La lista apunta al nodo debajo del que se va a eliminar
        free(nae->info);
        free(nae);
    }
}

void ordenarLista(t_lista* pl, Cmp cmp, int sentido)
{
   t_lista listaOrd = NULL; /// Arranco con una lista vacia
   t_lista* plOrd;
   t_nodo* nodo;

   while(*pl) /// Mientras haya elementos en la lista desordenada desengancho de esa lista y lo inserto de manera ordenada en lista ordenada
   {
      /// Desenganchar
      nodo = *pl; // 1
      *pl = nodo->sig; // 2

      plOrd = &listaOrd; /// Se vuelve a apuntar al inicio

      /// Insertar en lista ordenada
      while(*plOrd && cmp(nodo->info, (*plOrd)->info) * sentido > 0)  /// Mientras la lista ordenada apunte a algo
         plOrd = &(*plOrd)->sig;

      /// Una vez que corte el ciclo, engancho

      /// Enganchar
      nodo->sig = *plOrd; // 1
      *plOrd = nodo;      // 2
   }

   *pl = listaOrd;   /// A la lista orig le asigno direc del primer nodo de la lista ordenada
}

void recorrerLista(t_lista* pl, Accion accion, void* extra)
{
   while(*pl)
   {
      accion((*pl)->info,extra);
      pl = &(*pl)->sig;
   }
}

void invertirLista(t_lista *pl,Cmp cmp)
{
    int num_elim;
    t_lista *pl_aux = pl;

    if(!*pl) return;

    while((*pl_aux)->sig)
      pl_aux = &(*pl_aux)->sig;

    num_elim = *(int*)(*pl_aux)->info;

    printf("%d ", num_elim);

    sacar_de_lista(pl,&num_elim,sizeof(num_elim),cmp);

    invertirLista(pl,cmp);
}

void crearListaInvertida(t_lista *pl,t_lista *pl2, Cmp cmp)
{
    int num_elim;
    t_lista *pl_aux = pl;

    if(!*pl) return;

    while((*pl_aux)->sig)
      pl_aux = &(*pl_aux)->sig;

    num_elim = *(int*)(*pl_aux)->info;

    sacar_de_lista(pl,&num_elim,sizeof(num_elim),cmp);

    insertar_al_final_lista(pl2,&num_elim,sizeof(num_elim));

    crearListaInvertida(pl,pl2,cmp);
}

void ordenarLista2(t_lista* pl, Cmp cmp)
{
   t_lista listaOrd = NULL;
   t_lista* plOrd;
   t_nodo* nodo;

   while(*pl)
   {
      nodo = *pl;
      *pl = nodo->sig;

      plOrd = &listaOrd;

      while(*plOrd && cmp(nodo->info,(*plOrd)->info) > 0)
         plOrd = &(*plOrd)->sig;

      nodo->sig = *plOrd;
      *plOrd = nodo;
   }

   *pl = listaOrd;
}

int insertar_al_final_lista2(t_lista *pl,const void *pd, size_t tam)
{
   t_nodo* nue = crearNodo(tam);

   if(nue == NULL)
      return LISTA_LLENA;

   while(*pl)
      pl = &(*pl)->sig;

   memcpy(nue->info,pd,tam);

   nue->sig = *pl;
   *pl = nue;

   return OK;
}

int sacar_de_lista2(t_lista *pl, void *pd, size_t tam, Cmp cmp)
{
   t_nodo* elim;

   while(*pl && cmp(pd,(*pl)->info) != 0)
      pl = &(*pl)->sig;

   if(!*pl)
      return NO_EXISTE;

   memcpy(pd,(*pl)->info,min(tam,(*pl)->tam));

   elim = *pl;
   *pl = elim->sig;

   free(elim->info);
   free(elim);

   return OK;
}

void vaciarLista(t_lista *pl)
{
   t_nodo* elim;
   while(*pl)
   {
      elim = *pl;
      *pl = elim->sig;
      free(elim->info);
      free(elim);

   }
}

t_nodo* crearNodo(size_t tamInfo)
{
   t_nodo* nodo = malloc(sizeof(t_nodo));
   if(!nodo)
      return NULL;
   nodo->info = malloc(sizeof(tamInfo));
   if(!nodo->info)
   {
      free(nodo);
      return NULL;
   }
   nodo->tam = tamInfo;
   return nodo;
}

void destruirNodo(t_nodo* nodo)
{
   free(nodo->info);
   free(nodo);
}

int insertar_en_orden_lista2(t_lista *pl,const void *pd, size_t tam, Cmp cmp)
{
   t_nodo* nue = crearNodo(tam);

   if(nue == NULL)
      return LISTA_LLENA;

   while(*pl && cmp((*pl)->info,pd) < 0)
      pl = &(*pl)->sig;

   memcpy(nue->info,pd,tam);

   nue->sig = *pl;
   *pl = nue;

   return OK;
}

int insertar_al_inicio_lista(t_lista *pl,const void *pd, size_t tam)
{
   t_nodo* nue;

   if(!(nue = malloc(sizeof(t_nodo))) || !(nue->info = malloc(tam)))
   {
      free(nue);
      return LISTA_LLENA;
   }

   memcpy(nue->info,pd,tam);
   nue->tam = tam;
   nue->sig = *pl;
   *pl = nue;

   return OK;
}

int sacar_primero_de_lista(t_lista *pl, void *pd, size_t tam)
{
   t_nodo* elim;

   memcpy(pd,(*pl)->info,min(tam,(*pl)->tam));

   elim = *pl;
   *pl = elim->sig;  /// Desengancho

   free(elim->info);
   free(elim);

   return OK;
}

void OrdenarSeleccionLista(t_lista* pl, Cmp cmp)
{
   if(!*pl)
      return;
   t_nodo** menor; /// t_lista*

   while((*pl)->sig)
   {
      menor = buscarMenorNodoLista(pl,cmp);
      if(pl != menor)
         intercambiarInfoNodoLista(pl,menor);
      pl = &(*pl)->sig;
   }
}

t_nodo** buscarMenorNodoLista(const t_lista* pl, Cmp cmp)
{
   const t_lista* men = pl; // t_nodo**
   if(!pl)
      return NULL;
   pl = &(*pl)->sig;
   while(*pl)
   {
      if(cmp((*pl)->info, (*men)->info)<0)
         men = pl;
      pl = &(*pl)->sig;
   }
   return (t_nodo**)men;
}

void intercambiarInfoNodoLista(t_lista* nodo1, t_lista* nodo2)
{
   unsigned auxTam;
   void* aux = (*nodo1)->info;
   (*nodo1)->info = (*nodo2)->info;
   (*nodo2)->info = aux;

   auxTam = (*nodo1)->tam;
   (*nodo1)->tam = (*nodo2)->tam;
   (*nodo2)->tam = auxTam;
}

int eliminarDeListaOrdDuplicados(t_lista* pl, Cmp cmp)
{
   t_lista* pl2;
   t_nodo* elim;
   int cantElim = 0;

   while(*pl)
   {
      pl2 = &(*pl)->sig;

      while(*pl2 && cmp((*pl)->info,(*pl2)->info) == 0)
      {

         elim = *pl2;
         *pl2 = elim->sig;

         free(elim->info);
         free(elim);
         cantElim++;
      }


      pl = &(*pl)->sig;
   }

   return cantElim;
}


/// TODO: hacer ordenar lista por buscarMenor e insertar ordenado -> Semejante a seleccion (al final del video de pan)
/// Hacer recorrer lista y guardar el archivo (con fwrite) con funcion GrabarArchivo -> usar el extra y castearlo a (FILE*)
