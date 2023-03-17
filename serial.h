/* FRANT Madalina - 315CB */

#include "stiva.h"
#include "coada.h"


typedef struct
{
	int nr_ep;
	P_Coada episoade;    // cu elemente de tip int -> durata
} sezon;

typedef struct
{
	int ID;
	char* nume;
	float rating;
	int nr_sez;
	P_Coada sezoane;     // cu elemente de tip sezon
} serial;


/* initializeaza o structura de tip sezon */
sezon* InitSezon();

/* initializeaza o structura de tip serial */
serial* InitSerial();

/* 1 - trebuie inserat mai intai e1, respectiv 2 - e2;
functie necesara inserarii ordonate */
int cmpIns(void *e1, void *e2);

/* 0 - elemente egale, 1 - altfel */
int cmpName(void *e1, void* e2);

/* 0 - elementul x are campul nume egal cu numele s, 1 - altfel */
int comp(char *s, void* x);

/* afiseaza campurile nume si rating ale unui serial */
void AfiSerial(void *x, FILE* f);

/* elibereaza spatiul alocat pentru o strcutura de tip sezon */
void ElibSezon(void *x);

/* elibereaza spatiul alocat pentru o strcutura de tip serial */
void ElibSerial(void *x);

/* returneaza o copie a serialului primit ca parametru */
serial* copieSerial(serial* s);

/* adauga serialul in lista */
void Add_Serial(Lista* L, int ID, FILE* f);

/* adauga serialul in lista (functie specifica serialelor din top10) */
void Add_Top(Lista* L);

/* muta serialul din lista in coada */
void Add_Later(Lista* L, P_Coada c, char* nume);

/* adauga un sezon in coada sezoane ale serialului cu numele nume */
void Add_Sez(Lista L, char* nume);

/* vizioneaza serialul din lista */
void Watch(Lista* L, P_Stiva s, P_Stiva h, char* nume, FILE* f);

/* vizioneaza serialul din coada watch_later */
void WatchFromWatchLater(P_Coada* c, P_Stiva s, P_Stiva h, char* nume, FILE* f);