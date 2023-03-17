/* FRANT Madalina - 315CB */

#include "coada.h"


void* InitQ(size_t d)
{
	P_Coada c = (P_Coada)malloc(sizeof(Coada));
	if (c == NULL)	
        return NULL;
	
	c->dim_elem = d;
	c->ic = NULL;
    c->sc = NULL;

	return (void *) c;
}

void InsQ(void* c, void* x)
{
    Lista aux = AlocCelula(x); // creeaza celula
    if (aux == NULL)
        return;

    if (COADA_VIDA(c)) // coada vida => inceput = sfarsit = celula creata
    {
        IC(c) = aux;
        SC(c) = aux;
    }
    else
    {
        SC(c)->urm = aux;   // adauga dupa sfarsit
        SC(c) = aux;        // noul sfarsit
    }  
}

void ElimCoada(P_Coada* c, void* x, TFElib elib_elem, TFCmp cmp)
{
    if (COADA_VIDA(c))
        return;

    Lista p = (*c)->ic;
    Lista ant = NULL;
	while (p != NULL)
	{
		if (cmp(p->info, x) == 0)
        {
            if (ant == NULL) // eliminare de la inceput
                (*c)->ic = ((*c)->ic)->urm;
            else
                ant->urm = p->urm;

            Lista aux = p;
            p = p->urm;

            /* daca a fost eliminat ultimul element trebuie
            actualizat sfarsitul cozii */
            if (p == NULL)
                (*c)->sc = ant;

            elib_elem(aux->info);
            free(aux);
            return;
        }
        
        ant = p;
        p = p->urm;
	}
}

void ResetQ(void* c, TFElib elib_elem)
{
	Lista aux = IC(c);
    /* elimina toate elementele */
	while (aux != NULL)
	{
		Lista p = aux;
		aux = aux->urm;
        elib_elem(p->info);
		free(p);
	}
	IC(c) = SC(c) = NULL;
}

void DistrQ(void** c, TFElib elib_elem)
{
	ResetQ(*c, elib_elem); // elimina toate elementele din coada
	free(*c);
	*c = NULL;
}

void AfiCoada(void* c, TFAfi afi_elem, FILE* f)
{
    Lista aux = IC(c);
    AfisareLista(aux, afi_elem, f);
}