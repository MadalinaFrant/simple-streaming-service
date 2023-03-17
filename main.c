/* FRANT Madalina - 315CB */

#include "serial.h"


int main(int argc, char *argv[])
{
    FILE *input, *output;
    size_t len = 0;
    char *line = NULL;

    input = fopen(argv[1], "r");
    if (input == NULL)
        return 0;
    output = fopen(argv[2], "w");
    if (output == NULL)
        return 0;


    Lista Tendinte = NULL;
    Lista Documentare = NULL;
    Lista Tutoriale = NULL;
    Lista Top10 = NULL;

    P_Coada watch_later = (P_Coada)(InitQ(sizeof(serial)));
    P_Stiva currently_watching = (P_Stiva)(InitS(sizeof(serial)));
    P_Stiva history = (P_Stiva)(InitS(sizeof(serial)));


    // citeste fiecare linie din fisier
    while (getline(&line, &len, input) != -1)
    {
        if (line[0] == '\n') // daca linia contine doar '\n'
            continue;

        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        char *comanda = strtok(line, " ");

        /* Adaugare serial in baza de date */
        if (strcmp(comanda, "add") == 0)
        {
            int ID = atoi(strtok(NULL, " "));

            switch (ID) // adauga in lista corespunzatoare ID-ului
            {
                case 1:
                    Add_Serial(&Tendinte, 1, output);
                    break;
                
                case 2:
                    Add_Serial(&Documentare, 2, output);
                    break;

                case 3:
                    Add_Serial(&Tutoriale, 3, output);
                    break;
                
                default:
                    break;
            }

        }

        /* Adaugare sezon integral */
        if (strcmp(comanda, "add_sez") == 0)
        {
            char* nume = strtok(NULL, " ");

            /* Adauga sezon serialului din lista in care exista */

            if (ExistaInLista(Tendinte, nume, comp))
                Add_Sez(Tendinte, nume);

            if (ExistaInLista(Documentare, nume, comp))
                Add_Sez(Documentare, nume);

            if (ExistaInLista(Tutoriale, nume, comp))
                Add_Sez(Tutoriale, nume);

            if (ExistaInLista(Top10, nume, comp))
                Add_Sez(Top10, nume);

            if (ExistaInLista(watch_later->ic, nume, comp))
                Add_Sez(watch_later->ic, nume);

            if (ExistaInLista(currently_watching->vf, nume, comp))
                Add_Sez(currently_watching->vf, nume);

            fprintf(output, "Serialul %s are un sezon nou.\n", nume);
        }

        /* Adaugare serial in Top10 */
        if (strcmp(comanda, "add_top") == 0)
        {
            Add_Top(&Top10);
            fprintf(output, "Categoria top10: ");
            AfisareLista(Top10, AfiSerial, output);
        }

        /* Adaugare serial in watch_later */
        if (strcmp(comanda, "later") == 0)
        {
            char* nume = strtok(NULL, " ");

            /* Muta serialul din lista in care exista in coada watch_later */

            if (ExistaInLista(Tendinte, nume, comp))
                Add_Later(&Tendinte, watch_later, nume);

            if (ExistaInLista(Documentare, nume, comp))
                Add_Later(&Documentare, watch_later, nume);

            if (ExistaInLista(Tutoriale, nume, comp))
                Add_Later(&Tutoriale, watch_later, nume);

            if (ExistaInLista(Top10, nume, comp))
                Add_Later(&Top10, watch_later, nume);

            fprintf(output, 
             "Serialul %s se afla in coada de asteptare pe pozitia %d.\n",
             nume, LungimeLista(watch_later->ic));
        }

        /* Vizionare serial */
        if (strcmp(comanda, "watch") == 0)
        {
            char* nume = strtok(NULL, " ");

            /* In cazul vizionarii unui serial din coada watch_later
            se apeleaza functia WatchFromWatchLater, deoarece trebuie
            eliminat un element din coada (se poate schimba sfarsitul
            cozii) */

            if (ExistaInLista(currently_watching->vf, nume, comp))
                Watch(&(currently_watching->vf), currently_watching,
                 history, nume, output);

            if (ExistaInLista(watch_later->ic, nume, comp))
                WatchFromWatchLater(&watch_later, currently_watching,
                 history, nume, output);

            if (ExistaInLista(Tendinte, nume, comp))
                Watch(&Tendinte, currently_watching, history, nume, output);

            if (ExistaInLista(Documentare, nume, comp))
                Watch(&Documentare, currently_watching, history, nume, output);

            if (ExistaInLista(Tutoriale, nume, comp))
                Watch(&Tutoriale, currently_watching, history, nume, output);

            if (ExistaInLista(Top10, nume, comp))
                Watch(&Top10, currently_watching, history, nume, output);

        }

        /* Afisare seriale */
        if (strcmp(comanda, "show") == 0)
        {
            char *x = strtok(NULL, " ");

            if (strcmp(x, "1") == 0)
            {
                fprintf(output, "Categoria 1: ");
                AfisareLista(Tendinte, AfiSerial, output);
            }
            if (strcmp(x, "2") == 0)
            {
                fprintf(output, "Categoria 2: ");
                AfisareLista(Documentare, AfiSerial, output);
            }
            if (strcmp(x, "3") == 0)
            {
                fprintf(output, "Categoria 3: ");
                AfisareLista(Tutoriale, AfiSerial, output);
            }
            if (strcmp(x, "top10") == 0)
            {
                fprintf(output, "Categoria top10: ");
                AfisareLista(Top10, AfiSerial, output);
            }
            if (strcmp(x, "later") == 0)
            {
                fprintf(output, "Categoria later: ");
                AfiCoada(watch_later, AfiSerial, output);
            }
            if (strcmp(x, "watching") == 0)
            {
                fprintf(output, "Categoria watching: ");
                AfiStiva(currently_watching, AfiSerial, output);
            }
            if (strcmp(x, "history") == 0)
            {
                fprintf(output, "Categoria history: ");
                AfiStiva(history, AfiSerial, output);
            }
        }
    }
    free(line);

    fclose(input);
    fclose(output);

    /* eliberare memorie ocupata de liste, stive, cozi */

    DistrugeLista(&Tendinte, ElibSerial);
    DistrugeLista(&Documentare, ElibSerial);
    DistrugeLista(&Tutoriale, ElibSerial);
    DistrugeLista(&Top10, ElibSerial);
    DistrQ((void *)(&watch_later), ElibSerial);
    DistrS((void *)(&currently_watching), ElibSerial);
    DistrS((void *)(&history), ElibSerial);

    return 0;
}