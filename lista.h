/* FRANT Madalina - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LISTA
#define LISTA

/* Lista generica simplu inlantuita */

typedef struct celula
{
    void* info;
    struct celula *urm;
} Celula, *Lista;


typedef int (*FCmp)(char*, void*);      /* functie de comparare doua elemente */
typedef int (*TFCmp)(void*, void*);     /* functie de comparare doua elemente */
typedef void (*TFAfi)(void*, FILE*);    /* functie de afisare un element */
typedef void (*TFElib)(void*);          /* functie de eliberare un element */


/* aloca celula si completeaza campul info cu x */
Lista AlocCelula(void* x);

/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void AfisareLista(Lista L, TFAfi afi_elem, FILE* f);

/* distrugere lista - elimina toate celulele din lista */
void DistrugeLista(Lista* L, TFElib elib_elem);

/* calculeaza si returneaza lungimea listei */
int LungimeLista(Lista L);

/* insereaza ordonat in lista si returneaza pozitia la care a inserat */
int InsOrd(Lista* L, void* x, TFCmp cmp);

/* insereaza in lista la pozitia poz */
void InsTop(Lista* L, void *x, int poz);

/* daca lista are mai mult de 10 elemente elimina toate elementele
de dupa poztitia 10 */
void ElimTop(Lista* L, TFElib elib_elem);

/* elimina un element din lista */
void Elim(Lista* L, void* x, TFElib elib_elem, TFCmp cmp);

/* returneaza elementul din lista cu numele x, respectiv
NULL daca nu exista */
void* GasesteInLista(Lista L, char* x, FCmp f);

/* returneaza 1 daca exista in lista elementul cu numele x,
respectiv 0 daca nu exista */
int ExistaInLista(Lista L, char* x, FCmp f);

#endif