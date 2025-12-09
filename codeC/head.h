#ifndef _HEAD
#define _HEAD


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>


//Importation des couleurs 

#define ROUGE "\033[31m"
#define VERT "\033[32m"
#define JAUNE "\033[33m"
#define BLEU "\033[34m"
#define RESET "\033[0m"
#define ROSE "\x1b[38;5;201m"
#define VIOLET "\x1b[38;5;135m"
#define ORANGE "\x1b[38;5;208m"
#define BLEUC "\x1b[38;5;117m"
#define BLEUF "\x1b[38;5;19m"


//Couleur pour le dégrade
#define ORANGE_CLAIR      "\x1b[38;5;214m"
#define ORANGE_TRES_CLAIR "\x1b[38;5;220m"
#define BLEU_CLAIR         "\x1b[38;5;123m"
#define BLEU_CLAIR2        "\x1b[38;5;147m"
#define VIOLET_CLAIR       "\x1b[38;5;177m"
#define VIOLET_CLAIR2      "\x1b[38;5;141m"
#define VIOLET_TRES_CLAIR    "\x1b[38;5;183m"


//On defini les macro utiles au rotations

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

//Partie arbre AVL 

typedef struct AVL
{
    char *ID;
    double Capacity_Max;
    double Total_Source_Vol;
    double Total_Real_Vol;

    struct AVL *fg;
    struct AVL *fd;

    int equi;
}AVL, *pAVL;




pAVL creerAVL(char *e/*Identifiant*/)
{
    pAVL nouveau = malloc(sizeof(AVL));
    if (nouveau)
    {
        nouveau->ID = strdup(e); //https://koor.fr/C/cstring/strdup.wp pour copier une chaine de caractère, il faut penser a la free mais je le ferais en mm temps que l'avl entier

        nouveau->Capacity_Max = nouveau->Total_Source_Vol = nouveau->Total_Real_Vol = 0;

        nouveau->fg = nouveau->fd = NULL;

        nouveau->equi = 0; //on assigne à 0 puisque pour le moment les fg et fd sont null.
        return nouveau;        
    }
    else return NULL;
}

pAVL recherche(pAVL a, char * e) //On cherche une usine
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

pAVL insertionAVL(pAVL a, char * e/*identifiant*/, int *h /*Facteur d'equi*/) //On insere en fonction de l'identifiant "e"
{

    //Insertion brute
    if(!a)
    {
        return creerAVL(e);
    }
    else if((strcmp(a->ID,e)) < 0 ) //On va à gauche
    {
        a->fg = insertionAVL(a->fg,e,h);
    }
    else if ((strcmp(a->ID,e)) > 0) //On va à droite
    {
        a->fd = insertionAVL(a->fd,e,h);
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
            a = equilibre(a);

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
    if(!a) return NULL;
    else 
    {
        if(a->equi >= 2)
        {
            if(a->fd->equi >= 0) a = rotation_gauche(a);
            else a = rotation_double_gauche(a); 
        }
        else if (a->equi <= -2)
        {
            if(a->fg->equi <= 0) a = rotation_droite(a);
            else a = rotation_double_droite(a);
        }
        else printf(ROUGE"Mauvais appel de fonction"RESET);
    }
    return a;
}

    //Partie supression

pAVL sup_min()
{
    
}

pAVL suppression_AVL()
{

}

//Partie ARBRE CLASSIQUE pour le calcul des fuites

typedef struct ArbreClassique
{
    int valeur;
    struct ABR *fg;
    struct ABR *fd;
}ArbreClassique, *pArbreClassique;

pAVL creerArbreClassique(int e/*Identifiant*/, int valeur /*Valeur en litre*/)
{
    pArbreClassique nouveau = malloc(sizeof(ArbreClassique));
    if (nouveau)
    {
        nouveau->valeur = valeur;
        nouveau->fg = nouveau->fd = NULL;
        return nouveau;        
    }
    else return NULL;
}
#endif 