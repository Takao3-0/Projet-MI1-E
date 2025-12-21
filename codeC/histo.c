#include "histo.h"

/*

Cahier des charges 

    Ici on doit pouvoir comparer les données des usines.
        -On recupere les donnes des sources et usines.
            -On place ça dans un AVL.
                -AVL;
                -Sommer les capacités de captage/traitement pour chaque usine;
                    -Il faut identifier chaque source relié a une usine particuliere et sommer tout les volumes en direction de cette usine. 
                -Trier les usine par identifiant inverse????;
            -Le programme doit nous retourner un fichier CSV
                -Il servira à GnuPlot? via le script Shell.









    -Pour l'AVL
    Chaque noeud correcpond à une usine, pour obtenir la capacite max d'une usine il faut sommer tout les volumes provenant des sources.
    Dans un noeud on stocke 3 arg : max, src, real 
        Capacite max de l'usine, une valeur fixe qu'on trouve sur la ligne de l'usine
        Le volume capté, soit la somme des volumes de toutes les sources reliées à cette usine.
        La somme des volumes captés multipliée par le rendement   ???? mais les fuites sont au niveau de l'usine ou entre les sources et l'usine???
*/


void Max(FILE * Usine) //max
{
    char line[128];
    int h = 0;
    char IDUsine[128];
    double Vol;
    

    pAVL AVL_MAX = NULL;
    if (Usine)
    {
        while(fgets(line,sizeof(line), Usine))
        {
            if (sscanf(line, "%[^;];%lf", IDUsine, &Vol) != 2) continue;
            pAVL elmt = recherche(AVL_MAX, IDUsine);
            if (!elmt)
            {
                h = 0;
                AVL_MAX = insertionAVL(AVL_MAX,IDUsine, &h ,AVL_HISTO);
                elmt = recherche(AVL_MAX,IDUsine);
            }
            elmt->data.HistoPart->Capacity_Max = Vol;
        }
    }
    else printf("Le fichier reçu est vide\n");

    FILE *returnMAX = fopen("returnmax.txt", "w");
    if (returnMAX) {
        parcoursInfixe(AVL_MAX, returnMAX, MAX);
        fclose(returnMAX);
    } else {
        printf("returnMAX n'existe pas!\n");
    }
    freeAVL(AVL_MAX);
    AVL_MAX = NULL;
}


void VolumeCapte(FILE * filesource) //src
{
    char line[128]; 
    int h = 0;
    char IDUsine[128];
    char IDSource[128];
    double volumeSource;
    pAVL AVL_VC = NULL;
    if(filesource)
    {
        //printf(VERT"On fait la partie src\n"RESET);
        while (fgets(line, sizeof(line), filesource))
        {
            if (sscanf(line, "%[^;];%[^;];%lf", IDSource, IDUsine, &volumeSource) != 3) continue;
            pAVL elmt = recherche(AVL_VC, IDUsine);
            if (!elmt)
            {
                //printf(VIOLET"L'usine %s n'est pas dans l'AVL, on l'ajoute\n"RESET,IDUsine);
                h = 0;
                AVL_VC = insertionAVL(AVL_VC, IDUsine, &h,AVL_HISTO);
                elmt = recherche(AVL_VC, IDUsine);
            }
            elmt->data.HistoPart->Total_Source_Vol += volumeSource;
        }        

    }
    else 
    {
        printf("Le fichier reçu est vide!\n");
    }
    
    /*On cree le fichier return*/

    FILE *returnSRC = fopen("returnsrc.txt", "w");
    if (returnSRC) {
        parcoursInfixe(AVL_VC, returnSRC, SRC);
        fclose(returnSRC);
    } else {
        printf("returnSRC n'existe pas!\n");
    }
    freeAVL(AVL_VC);
    AVL_VC = NULL;
}

void VolumeTraite(FILE * filesourceL) //real
{
    char line[128]; 
    int h;
    char IDUsine[128];
    char IDSource[128];
    int volumeSource;
    float leaks;
    pAVL elmt;
    pAVL AVL_VT = NULL;
    if(filesourceL)
    {
        //printf(VERT"On fait la partie real\n"RESET);
        while (fgets(line, sizeof(line), filesourceL))
        {
            if (sscanf(line, "%[^;];%[^;];%d;%f", IDSource, IDUsine, &volumeSource, &leaks) != 4) continue;
            elmt = recherche(AVL_VT, IDUsine);
            if (!elmt)
            {
                //printf(VIOLET"L'usine %s n'est pas dans l'AVL, on l'ajoute\n"RESET,IDUsine);
                h = 0;
                AVL_VT = insertionAVL(AVL_VT, IDUsine, &h,AVL_HISTO);
                elmt = recherche(AVL_VT, IDUsine);
            }
            elmt->data.HistoPart->Total_Real_Vol += volumeSource - (volumeSource * (leaks / 100));
        }        

    }
    else 
    {
        printf("Le fichier reçu est vide!\n");
    }    

    //On cree le fichier return
    FILE * returnREAL = fopen("returnreal.txt", "w");
    if (returnREAL) parcoursInfixe(AVL_VT, returnREAL,REAL);
    else printf(ROUGE"returnREAL n'existe pas!\n"RESET);

    freeAVL(AVL_VT);
    AVL_VT = NULL; 
    fclose(returnREAL); 
}






void HistoALL()
{
    char line[128], dassault[128], line2[128];
    char id1[128], id2[128], id3[128];
    double vsrc, vreal, vmax;

    FILE * src = fopen("returnsrc.txt", "r");
    FILEOPEN(src, "returnsrc.txt");

    FILE * real = fopen("returnreal.txt", "r");   
    FILEOPEN(real, "returnreal.txt");

    FILE * max = fopen("returnmax.txt", "r");   
    FILEOPEN(max, "returnmax.txt");

    FILE * returnall = fopen("returnall.txt", "w");
    FILEOPEN(returnall, "returnall.txt");    
    
    while(fgets(line, sizeof(line),src) && fgets(dassault, sizeof (dassault), real) && fgets(line2, sizeof (line2), max))
    {
        if (sscanf(line,  "%[^;];%lf", id1, &vsrc)  != 2) continue;
        if (sscanf(dassault, "%[^;];%lf", id2, &vreal) != 2) continue;
        if (sscanf(line2,  "%[^;];%lf", id3, &vmax)  != 2) continue;
        
        if ((strcmp(id1,id2) == 0) && (strcmp(id2, id3) == 0))
        {
            fprintf(returnall,"%s;%lf;%lf;%lf\n",id1,vmax,vsrc,vreal);
        }
        else continue;
    }

    fclose(src);
    fclose(real);
    fclose(max);
    fclose(returnall);
}


