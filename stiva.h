/* FRANT Madalina - 315CB */

#include "lista.h"

/* Stiva implementata folosind lista generica simplu inlantuita */

typedef struct 
{
    size_t dim_elem;
    Lista vf;
} Stiva, *P_Stiva;


#define VF(a) (((P_Stiva)(a))->vf)

#define DIM_EL_S(a) (((P_Stiva)(a))->dim_elem)

#define STIVA_VIDA(a) (VF(a) == NULL)


/* initializeaza stiva cu elemente de dimensiune d */
void* InitS(size_t d);

/* adauga elementul x in varful stivei */
void Push(void *s, void* x);

/* transforma stiva in stiva vida */
void ResetS(void* s, TFElib elib_elem);

/* elibereaza intregul spatiu ocupat de stiva */
void DistrS(void **s, TFElib elib_elem);

/* afiseaza elementele din stiva, folosind o functie de tip TFAfi */
void AfiStiva(void* s, TFAfi afi_elem, FILE* f);