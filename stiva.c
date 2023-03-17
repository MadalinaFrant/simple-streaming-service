/* FRANT Madalina - 315CB */

#include "stiva.h"


void* InitS(size_t d)
{
	P_Stiva s = (P_Stiva)malloc(sizeof(Stiva));
	if (s == NULL)	
        return NULL;
	
	s->dim_elem = d;
	s->vf = NULL;

	return (void*) s;
}

void Push(void *s, void* x)
{
	Lista aux = AlocCelula(x); // creeaza celula
	if (aux == NULL) 
        return;

	aux->urm = VF(s);   // adauga inainte de varf
	VF(s) = aux;        // noul varf
}

void ResetS(void* s, TFElib elib_elem)
{
	Lista aux = VF(s);
    /* elimina toate elementele */
	while (aux != NULL)
	{
		Lista p = aux;
		aux = aux->urm;
        elib_elem(p->info);
		free(p);
	}
	VF(s) = NULL;
}

void DistrS(void **s, TFElib elib_elem)
{
	ResetS(*s, elib_elem); // elimina toate elementele din stiva
	free(*s);
	*s = NULL;
}

void AfiStiva(void* s, TFAfi afi_elem, FILE* f)
{
    Lista aux = VF(s);
    AfisareLista(aux, afi_elem, f);
}