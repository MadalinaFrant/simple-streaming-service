/* FRANT Madalina - 315CB */

#include "lista.h"


Lista AlocCelula(void* x)
{
    Lista aux = (Lista)malloc(sizeof(Celula)); // incearca alocare
    if (aux == NULL) // alocare nereusita
        return NULL;

    aux->info = x; // completeaza campul info cu valoarea x primita ca parametru
    aux->urm = NULL;

    return aux;
}

void AfisareLista(Lista L, TFAfi afi_elem, FILE* f)
{
    if (L == NULL) // lista vida
    {
        fprintf(f, "[].\n");
        return;
    }

    fprintf(f, "[");
    for (; L->urm != NULL; L = L->urm)
    {
        afi_elem(L->info, f);
        fprintf(f, ", ");
    }
    afi_elem(L->info, f);
    fprintf(f, "].\n");
}

void DistrugeLista(Lista* L, TFElib elib_elem)
{
    Lista aux;
    while (*L != NULL) // cat timp exista elemente in lista
    {
        aux = *L;
        *L = (*L)->urm;
        elib_elem(aux->info); // elibereaza spatiul ocupat de element
        free(aux); // elibereaza spatiul ocupat de celula
    }
}

int LungimeLista(Lista L)
{ 
	int lg = 0;
	for ( ; L != NULL; L = L->urm)
		lg++;
	return lg;
}

int InsOrd(Lista* L, void* x, TFCmp cmp)
{
    Lista aux = AlocCelula(x);
    if (aux == NULL)
        return 0;

    if (*L == NULL) // lista vida => inserare la inceput
    {
        aux->urm = *L;
        *L = aux;
        return 1;
    }
    else
    {
        Lista p = *L;

        if (cmp((*L)->info, x) == 2)
        { // inserare inainte de primul element
            aux->urm = *L;
            *L = aux;
            return 1;
        }

        int pos = 2;

        for (; p->urm != NULL; p = p->urm, pos++)
        {
            if ((cmp(p->info, x) == 1) && (cmp(p->urm->info, x) == 2))
            { // inserare dupa p (elementul curent)
                aux->urm = p->urm;
                p->urm = aux;
                return pos;
            }
        }

        if (cmp(p->info, x) == 1)
        { // inserare dupa ultimul element
            aux->urm = p->urm;
            p->urm = aux;
            return pos;
        }
    }

    return 0;
}

void InsTop(Lista* L, void *x, int poz)
{
    Lista aux = AlocCelula(x);
    if (aux == NULL)
        return;

    int p = 1; // pozitia curenta

    while (p <= poz)
    {
        if (p == poz) // s-a ajuns la pozitia de inserat
        {
            aux->urm = *L;
            *L = aux;
        }
        else
        {
            L = &(*L)->urm; // avans fara pointeri
        }
        p++;
    }
}

void ElimTop(Lista* L, TFElib elib_elem)
{
    if (LungimeLista(*L) > 10) // daca lista are mai mult de 10 elemente
    {
        Lista l = *L, ant, aux;
        int i;
        for (i = 0; i < 10; i++) // parcurgere lista pana la elementul 11
        {
            ant = l;
            l = l->urm;
        }

        while (l != NULL) // se elimina toate elementele incepand cu pozitia 11
        {
            ant->urm = l->urm;
            aux = l;
            ant = l;
            l = l->urm;
            elib_elem(aux->info); // elibereaza spatiul ocupat de element
            free(aux); // elibereaza spatiul ocupat de celula

        }
    }
}

void Elim(Lista* L, void* x, TFElib elib_elem, TFCmp cmp)
{
    Lista p, ant, aux;
    p = *L;
    ant = NULL;

    while (p != NULL)
    {
        if (cmp(p->info, x) == 0) // gasire element de eliminat
        {
            if (ant == NULL) // eliminare de la inceput
                *L = (*L)->urm;
            else
                ant->urm = p->urm;

            aux = p;
            p = p->urm;
            elib_elem(aux->info); // elibereaza spatiul ocupat de element
            free(aux); // elibereaza spatiul ocupat de celula
            return;
        }
        
        ant = p;
        p = p->urm;
        
    }
}

void* GasesteInLista(Lista L, char *x, FCmp f)
{
    if (L == NULL)
        return NULL;

    for (; L != NULL; L = L->urm)
    {
        if (f(x, L->info) == 0) // gasire element
            return L->info;
    }
    
    return NULL; // element negasit
}

int ExistaInLista(Lista L, char *x, FCmp f)
{
    if (GasesteInLista(L, x, f) != NULL)
        return 1;

    return 0;
}