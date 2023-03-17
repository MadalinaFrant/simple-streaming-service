/* FRANT Madalina - 315CB */

#include "serial.h"

#define L_MAX_NUME 32


sezon* InitSezon()
{
    sezon* Sezon = malloc(sizeof(sezon));
    if (Sezon == NULL)
        return NULL;

    /* initializeaza coada cu elemente de tip int */
    Sezon->episoade = InitQ(sizeof(int));
    if (Sezon->episoade == NULL)
        return NULL;

    return Sezon;
}

serial* InitSerial()
{
    serial* Serial = malloc(sizeof(serial));
    if (Serial == NULL)
        return NULL;

    Serial->nume = malloc(L_MAX_NUME * sizeof(char) + 1);
    if (Serial->nume == NULL)
        return NULL;

    /* initializeaza coada cu elemente de tip sezon */
    Serial->sezoane = InitQ(sizeof(sezon));
    if (Serial->sezoane == NULL)
        return NULL;

    return Serial;
}

int cmpIns(void *e1, void *e2)
{
    serial* s1 = (serial* )e1;
    serial* s2 = (serial* )e2;

    if (s1->rating > s2->rating)
    {
        return 1;
    }

    if (s1->rating < s2->rating)
    {
        return 2;
    }

    if (s1->rating == s2->rating) // rating egal
    {
        if (strcmp(s1->nume, s2->nume) > 0)
            return 2;
        else
            return 1;
    }

    return 0;
}

int cmpName(void *e1, void* e2)
{
    serial* s1 = (serial* )e1;
    serial* s2 = (serial* )e2;

    if (strcmp(s1->nume, s2->nume) == 0) // nume egale
        return 0;
    else
        return 1;
}

int comp(char *s, void* x)
{
    serial* el = (serial* )x;

    if (strcmp(s, el->nume) == 0) // x are numele s
        return 0;
    else
        return 1;
}

void AfiSerial(void *x, FILE* f)
{
    serial* S = (serial *)x;
    fprintf(f, "(%s, %.1f)", S->nume, S->rating);
}

void ElibSezon(void *x)
{
    sezon* S = (sezon* )x;
    DistrQ((void *)(&(S->episoade)), free);
    free(S);
}

void ElibSerial(void *x)
{
    serial* S = (serial* )x;
    free((S->nume));
    DistrQ((void *)(&(S->sezoane)), ElibSezon);
    free(S);
}

serial* copieSerial(serial* s)
{
    serial* Serial = InitSerial();
    if (Serial == NULL)
        return NULL;

    Serial->ID = s->ID;
    strcpy(Serial->nume, s->nume);
    Serial->rating = s->rating;
    Serial->nr_sez = s->nr_sez;

    Lista sezoane = IC(s->sezoane);
	while (sezoane != NULL)
	{
        sezon* sez = sezoane->info;

        sezon* Sezon = InitSezon();
        if (Sezon == NULL)
            return NULL;

        Sezon->nr_ep = sez->nr_ep;

        Lista episoade = IC(sez->episoade);
	    while (episoade != NULL)
        {
            int* durata_episod = (int* )malloc(sizeof(int));
            *durata_episod = *(int* )episoade->info;

            InsQ(Sezon->episoade, durata_episod);

            episoade = episoade->urm;
        }

        InsQ(Serial->sezoane, Sezon);

		sezoane = sezoane->urm;
	}

    return Serial;
}

void Add_Serial(Lista* L, int ID, FILE* f)
{
    int i, j;

    char* nume = strtok(NULL, " ");
    float rating = atof(strtok(NULL, " "));
    int nr_sez = atoi(strtok(NULL, " "));

    serial* Serial = InitSerial();
    if (Serial == NULL)
        return;

    Serial->ID = ID;
    strcpy(Serial->nume, nume);
    Serial->rating = rating;
    Serial->nr_sez = nr_sez;

    for (i = 0; i < nr_sez; i++)
    {
        int nr_ep = atoi(strtok(NULL, " "));

        sezon* Sezon = InitSezon();
        if (Sezon == NULL)
            return;

        Sezon->nr_ep = nr_ep;

        for (j = 0; j < nr_ep; j++)
        {  
            int* durata_episod = (int* )malloc(sizeof(int));
            *durata_episod =  atoi(strtok(NULL, " "));

            InsQ(Sezon->episoade, durata_episod);
        }

        InsQ(Serial->sezoane, Sezon);
    }

    int poz = InsOrd(L, Serial, cmpIns);
    fprintf(f, "Serialul %s a fost adaugat la pozitia %d.\n",
    Serial->nume, poz);
}

void Add_Top(Lista* L)
{
    int i, j;

    int poz = atoi(strtok(NULL, " "));
    char* nume = strtok(NULL, " ");
    float rating = atof(strtok(NULL, " "));
    int nr_sez = atoi(strtok(NULL, " "));


    serial* Serial = InitSerial();
    if (Serial == NULL)
        return;

    Serial->ID = 4;
    strcpy(Serial->nume, nume);
    Serial->rating = rating;
    Serial->nr_sez = nr_sez;

    for (i = 0; i < nr_sez; i++)
    {
        int nr_ep = atoi(strtok(NULL, " "));

        sezon* Sezon = InitSezon();
        if (Sezon == NULL)
            return;

        Sezon->nr_ep = nr_ep;

        for (j = 0; j < nr_ep; j++)
        {
            int* durata_episod = (int* )malloc(sizeof(int));
            *durata_episod =  atoi(strtok(NULL, " "));

            InsQ(Sezon->episoade, durata_episod);
        }
        InsQ(Serial->sezoane, Sezon);
    }
    /* se insereaza la pozitia data */
    InsTop(L, Serial, poz);
    /* se elimina eventualele elemente de dupa pozitia 10 */
    ElimTop(L, ElibSerial);
}

void Add_Later(Lista* L, P_Coada c, char* nume)
{
    serial* S = (serial* )(GasesteInLista(*L, nume, comp));
    serial* Serial = copieSerial(S);
    InsQ(c, Serial); // adauga in coada copia creata
    Elim(L, S, ElibSerial, cmpName); // elimina din lista
}

void Add_Sez(Lista L, char* nume)
{
    int j;

    /* gaseste serialul cu numele nume in lista */
    serial* s = (serial* )(GasesteInLista(L, nume, comp));

    int nr_ep = atoi(strtok(NULL, " "));

    sezon* Sezon = InitSezon();
    if (Sezon == NULL)
        return;

    Sezon->nr_ep = nr_ep;

    for (j = 0; j < nr_ep; j++)
    {
        int* durata_episod = (int* )malloc(sizeof(int));
        *durata_episod =  atoi(strtok(NULL, " "));

        InsQ(Sezon->episoade, durata_episod);
    }

    InsQ(s->sezoane, Sezon);

}

void Watch(Lista* L, P_Stiva s, P_Stiva h, char* nume, FILE* f)
{
    int durata = atoi(strtok(NULL, " "));
    int total = 0, d = durata;

    /* gaseste serialul cu numele nume in lista */
    serial* S = (serial* )(GasesteInLista(*L, nume, comp));
    serial* Serial = copieSerial(S);
    /* elimina din lista */
    Elim(L, S, ElibSerial, cmpName);
    /* adauga in stiva currently_watching copia creata */
    Push(s, Serial);

    /* calculeaza numarul de minute ramase nevizionate din serial */
    Lista sezoane = IC(Serial->sezoane);
	while (sezoane != NULL)
	{
        sezon* sez = sezoane->info;

        Lista episoade = IC(sez->episoade);
	    while (episoade != NULL)
        {
            int durata_ep = *(int* )(episoade->info);
            total += durata_ep;

            episoade = episoade->urm;
        }

		sezoane = sezoane->urm;
	}

    /* vizioneaza durata minute din serial (decrementand numarul
    de minute din fiecare episod) */
    sezoane = IC(Serial->sezoane);
	while ((sezoane != NULL) && (durata > 0))
	{
        sezon* sez = sezoane->info;

        Lista episoade = IC(sez->episoade);
	    while (episoade != NULL)
        {
            int durata_ep = *(int* )(episoade->info);
            while ((durata_ep > 0) && (durata > 0))
            {
                (*(int* )(episoade->info))--;
                durata_ep--;
                durata--;
            }

            episoade = episoade->urm;
        }

		sezoane = sezoane->urm;
	}

    if (d >= total) // serial vizionat integral
    {
        fprintf(f, "Serialul %s a fost vizionat integral.\n", nume);
        serial* copie = copieSerial(Serial);
        /* adauga in stiva history */
        Push(h, copie);
        /* elimina din stiva currently_watching */
        Elim(&(s->vf), Serial, ElibSerial, cmpName);
    }
}

void WatchFromWatchLater(P_Coada* c, P_Stiva s, P_Stiva h, char* nume, FILE* f)
{
    int durata = atoi(strtok(NULL, " "));
    int total = 0, d = durata;

    /* gaseste serialul cu numele nume in lista */
    serial* S = (serial* )(GasesteInLista((*c)->ic, nume, comp));
    serial* Serial = copieSerial(S);
    /* elimina din coada */
    ElimCoada(c, S, ElibSerial, cmpName);
    /* adauga in stiva currently_watching copia creata */
    Push(s, Serial);

    /* calculeaza numarul de minute ramase nevizionate din serial */
    Lista sezoane = IC(Serial->sezoane);
	while (sezoane != NULL)
	{
        sezon* sez = sezoane->info;

        Lista episoade = IC(sez->episoade);
	    while (episoade != NULL)
        {
            int durata_ep = *(int* )(episoade->info);
            total += durata_ep;

            episoade = episoade->urm;
        }

		sezoane = sezoane->urm;
	}

    /* vizioneaza durata minute din serial (decrementand numarul
    de minute din fiecare episod) */
    sezoane = IC(Serial->sezoane);
	while ((sezoane != NULL) && (durata > 0))
	{
        sezon* sez = sezoane->info;

        Lista episoade = IC(sez->episoade);
	    while (episoade != NULL)
        {
            int durata_ep = *(int* )(episoade->info);
            while ((durata_ep > 0) && (durata > 0))
            {
                (*(int* )(episoade->info))--;
                durata_ep--;
                durata--;
            }

            episoade = episoade->urm;
        }

		sezoane = sezoane->urm;
	}

    if (d >= total) // serial vizionat integral
    {
        fprintf(f, "Serialul %s a fost vizionat integral.\n", nume);
        serial* copie = copieSerial(Serial);
        /* adauga in stiva history */
        Push(h, copie);
        /* elimina din stiva currently_watching */
        Elim(&(s->vf), Serial, ElibSerial, cmpName);
    }

}