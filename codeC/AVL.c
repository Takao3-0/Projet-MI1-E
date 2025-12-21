#include "AVL.h"

//Partie arbre AVL 

pAVL creerAVL(char *e/*Identifiant*/, AVLKey fkey)
{
    pAVL nouveau = malloc(sizeof(AVL));
    if (nouveau)
    {
        nouveau->ID = strdup(e); //https://koor.fr/C/cstring/strdup.wp pour copier une chaine de caractère, il faut penser a la free mais je le ferais en mm temps que l'avl entier
        CHECK_MALLOC(nouveau->ID, free(nouveau));

        //On assigne notre clé fourni pour l'utilisation de l'union
        nouveau->key = fkey;


        if(nouveau->key == AVL_HISTO)
        {
            nouveau->data.HistoPart = malloc(sizeof(NodeH));
            CHECK_MALLOC(nouveau->data.HistoPart,free(nouveau->ID); free(nouveau));

            nouveau->data.HistoPart->ID = strdup(e);
            CHECK_MALLOC(nouveau->data.HistoPart->ID, free(nouveau->data.HistoPart); free(nouveau->ID); free(nouveau));

            nouveau->data.HistoPart->Capacity_Max = nouveau->data.HistoPart->Total_Source_Vol = nouveau->data.HistoPart->Total_Real_Vol = 0;
        }
        else if(nouveau->key == AVL_LEAKS)
        {
            nouveau->data.LeaksPart = malloc(sizeof(NodeL));
            CHECK_MALLOC(nouveau->data.LeaksPart,free(nouveau->ID); free(nouveau));

            nouveau->data.LeaksPart->ID = strdup(e);
            CHECK_MALLOC(nouveau->data.LeaksPart->ID, free(nouveau->data.LeaksPart); free(nouveau->ID); free(nouveau));

            nouveau->data.LeaksPart->leak = nouveau->data.LeaksPart->volume_recu = 0;
            nouveau->data.LeaksPart->ac = NULL;
        }
        nouveau->fg = nouveau->fd = NULL;

        nouveau->equi = 0; //on assigne à 0 puisque pour le moment les fg et fd sont null.
        return nouveau;        
    }
    else return NULL;
}

pAVL recherche(pAVL a, char * e) //On fait la recherche en fonction de l'identifiant
{
    //https://koor.fr/C/cstring/strcmp.wp
    if(!a)
    {
        return NULL;
    }
    else if ((strcmp(a->ID,e)) == 0) //si les 2 chaine sont égales alors strcmp return null
    {
        return a; //trouvé
    }
    else if((strcmp(a->ID,e)) < 0) //strcmp <0 alors a->ID est avant "e" dans l'alphabet 
    {
        return recherche(a->fg,e);
    }
    else
    {
        return recherche(a->fd,e);
    } 
}

pAVL insertionAVL(pAVL a, char * e/*identifiant*/, int *h, AVLKey fkey) //On insere en fonction de l'identifiant "e"
{

    //Insertion brute
    if(!a)
    {
        return creerAVL(e,fkey);
    }
    else if((strcmp(a->ID,e)) < 0 ) //On va à gauche
    {
        a->fg = insertionAVL(a->fg,e,h,fkey);
    }
    else if ((strcmp(a->ID,e)) > 0) //On va à droite
    {
        a->fd = insertionAVL(a->fd,e,h,fkey);
    }
    else //L'element est déjà présent
    {
        *h = 0;
        return a;
    }
    
    //Mise a jour facteur d'equilibre
    if(*h != 0)
    {
        a->equi = a->equi + *h;

        if (a->equi == 0)
        {
            *h = 0;
        }
        else if (a->equi == 1 || a->equi == -1)
        {
            *h = 1;
        }
        else if (a->equi >= 2 || a->equi <= -2)
        {
            a = equilibreAVL(a);

            if (a->equi != 0) *h = 1;
            else *h = 0;
        }
    }

    return a;


}

pAVL rotation_droite(pAVL a)
{
    if(!a) return NULL;
    else 
    {
        pAVL pivot = a->fg;
        a->fg = pivot->fd;
        pivot->fd = a;

        int a_eq = a->equi;
        int p_eq = pivot->equi;

        a->equi = a_eq + MIN(p_eq,0) +1 ;
        pivot->equi=MAX(a_eq + 2,MAX(a_eq + p_eq +2, p_eq +1));
    }
    return a;
}

pAVL rotation_gauche(pAVL a)
{
    if(!a) return NULL;
    else 
    {
        pAVL pivot = a->fd;
        a->fd = pivot->fg;
        pivot->fg = a;

        int a_eq = a->equi;
        int p_eq = pivot->equi;

        a->equi = a_eq + MAX(p_eq,0) -1 ;
        pivot->equi=MIN(a_eq - 2,MIN(a_eq + p_eq -2, p_eq -1));
    }
    return a;
}

pAVL rotation_double_gauche(pAVL a)
{
    if(!a) return NULL;
    else
    {
        a->fg = rotation_droite(a->fg);
        return rotation_gauche(a);
    }
}
pAVL rotation_double_droite(pAVL a)
{
    if(!a) return NULL;
    else
    {
        a->fd = rotation_gauche(a->fd);
        return rotation_droite(a);
    }
}


pAVL equilibreAVL(pAVL a)
{
    if (!a) return NULL;

    if (a->equi >= 2 && a->fd)
    {
        if (a->fd->equi >= 0)
            a = rotation_gauche(a);
        else
            a = rotation_double_gauche(a);
    }
    else if (a->equi <= -2 && a->fg)
    {
        if (a->fg->equi <= 0)
            a = rotation_droite(a);
        else
            a = rotation_double_droite(a);
    }
    return a;
}

//Debug 

void traiter(pAVL a, FILE * returnfile, HistoMode mode)
{
    
    //printf(BLEU"Identifiant de l'usine : "ROUGE"%s\n"RESET, a->ID);
    //printf(VERT"Volume recu de l'usine :%lf\n"RESET, (mode == SRC) ? a->data.HistoPart->Total_Source_Vol : a->data.HistoPart->Total_Real_Vol);
    fprintf(returnfile,"%s;%lf\n",a->ID,(mode == SRC) ? a->data.HistoPart->Total_Source_Vol : a->data.HistoPart->Total_Real_Vol);
}

void parcoursprefixe(pAVL racine, FILE * returnfile, HistoMode mode)
{
    pAVL a = racine;
    if(a)
    {
        traiter(a, returnfile,mode);
        parcoursprefixe(a->fg, returnfile,mode);
        parcoursprefixe(a->fd, returnfile,mode);        
    }
}


void freeAVL(pAVL a)
{
    if (!a) return;

    freeAVL(a->fg);
    freeAVL(a->fd);

    if (a->key == AVL_HISTO) {
        if (a->data.HistoPart) {
            free(a->data.HistoPart->ID);
            free(a->data.HistoPart);
            a->data.HistoPart = NULL;
        }
    } 
    else if (a->key == AVL_LEAKS) {
        if (a->data.LeaksPart) {
            a->data.LeaksPart->ac = NULL;   // surtout pas free ici
            free(a->data.LeaksPart->ID);
            free(a->data.LeaksPart);
            a->data.LeaksPart = NULL;
        }
    }

    free(a->ID);
    free(a);
}


