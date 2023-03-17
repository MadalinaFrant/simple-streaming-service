/* FRANT Madalina - 315CB */

#include "lista.h"

/* Coada implementata folosind lista generica simplu inlantuita */

typedef struct 
{
    size_t dim_elem;
    Lista ic, sc;
} Coada, *P_Coada;


#define IC(a) (((P_Coada)(a))->ic)

#define SC(a) (((P_Coada)(a))->sc)

#define DIM_EL_C(a) (((P_Coada)(a))->dim_elem)

#define COADA_VIDA(a) ((IC(a) == NULL) && (SC(a) == NULL))


/* initializeaza coada cu elemente de dimensiune d */
void* InitQ(size_t d);

/* adauga elementul x la sfarsitul cozii */
void InsQ(void* c, void* x);

/* elimina un element din coada */
void ElimCoada(P_Coada* c, void* x, TFElib elib_elem, TFCmp cmp);

/* transforma coada in coada vida */
void ResetQ(void* c, TFElib elib_elem);

/* elibereaza intregul spatiu ocupat de coada */
void DistrQ(void** c, TFElib elib_elem);

/* afiseaza elementele din coada, folosind o functie de tip TFAfi */
void AfiCoada(void* c, TFAfi afi_elem, FILE* f);