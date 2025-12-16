#include "AVL.h"
#include "head.h"

//Partie arbre AVL 

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


//Partie supression

pAVL sup_min(pAVL a, pAVL *minNode, int *h)
{
    if (!a) { *minNode = NULL; *h = 0; return NULL; }

    if (a->fg == NULL) {
        *minNode = a;
        *h = 1;
        return a->fd;
    }

    a->fg = sup_min(a->fg, minNode, h);

    if (*h) {
        a->equi += 1;
        if (a->equi >= 2 || a->equi <= -2) a = equilibreAVL(a);
    }
    return a;
}

pAVL suppression_AVL(pAVL a, const char *key, int *h)
{
    if (!a) { *h = 0; return NULL; }

    int cmp = strcmp(key, a->ID);

    if (cmp < 0) {
        a->fg = suppression_AVL(a->fg, key, h);
        if (*h) { a->equi += 1; if (a->equi >= 2 || a->equi <= -2) a = equilibreAVL(a); }
        return a;
    }
    if (cmp > 0) {
        a->fd = suppression_AVL(a->fd, key, h);
        if (*h) { a->equi -= 1; if (a->equi >= 2 || a->equi <= -2) a = equilibreAVL(a); }
        return a;
    }

    /* cmp == 0 */
    pAVL toFree = a;

    if (a->fg == NULL) {
        a = a->fd;
        free(toFree->ID); free(toFree);
        *h = 1;
        return a;
    }
    if (a->fd == NULL) {
        a = a->fg;
        free(toFree->ID); free(toFree);
        *h = 1;
        return a;
    }

    pAVL minNode = NULL;
    int h2 = 0;
    a->fd = sup_min(a->fd, &minNode, &h2);

    free(a->ID);
    a->ID = strdup(minNode->ID);
    a->Capacity_Max     = minNode->Capacity_Max;
    a->Total_Source_Vol = minNode->Total_Source_Vol;
    a->Total_Real_Vol   = minNode->Total_Real_Vol;

    free(minNode->ID);
    free(minNode);

    if (h2) {
        a->equi -= 1;
        if (a->equi >= 2 || a->equi <= -2) a = equilibreAVL(a);
        *h = 1;
    } else {
        *h = 0;
    }
    return a;
}


//Partie ARBRE CLASSIQUE pour le calcul des fuites

typedef struct ArbreClassique
{
    int valeur;
    struct ArbreClassique *fg;
    struct ArbreClassique *fd;
} ArbreClassique, *pArbreClassique;

pArbreClassique creerArbreClassique(int valeur)
{
    pArbreClassique nouveau = malloc(sizeof(ArbreClassique));
    if (nouveau)
    {
        nouveau->valeur = valeur;
        nouveau->fg = NULL;
        nouveau->fd = NULL;
        return nouveau;
    }
    return NULL;
}





//Debug 

void traiter(pAVL a, FILE * returnfile)
{
    printf(BLEU"Identifiant de l'usine : "ROUGE"%s\n"RESET, a->ID);
    printf(VERT"Volume recu de l'usine :%lf\n"RESET, a->Total_Source_Vol);
    fprintf(returnfile,"%s;%lf\n",a->ID,a->Total_Source_Vol);
}


void parcoursprefixe(pAVL racine, FILE * returnfile)
{
    pAVL a = racine;
    if(a)
    {
        traiter(a, returnfile);
        parcoursprefixe(a->fg, returnfile);
        parcoursprefixe(a->fd, returnfile);        
    }
}


void suppressionAVL(pAVL a)
{
    if(a)
    {
        suppressionAVL(a->fg);
        suppressionAVL(a->fd);
        free(a->ID);
        free(a);
    }
}
