#include "leaks.h"


//static equivaut a private en C#
//quand on met rien -> public en C#
static int count_children_ac(pAC n) {
    int c = 0;
    for (pAC ch = (n ? n->enfant : NULL); ch; ch = ch->frere) c++;
    return c;
}

static pAC child_at_ac(pAC n, int idx) {
    int i = 0;
    for (pAC ch = (n ? n->enfant : NULL); ch; ch = ch->frere) 
    {
        if (i == idx) return ch;
        i++;
    }
    return NULL;
}

static void print_children_ac(pAC n) {
    if (!n)
    { 
        puts("(null)"); 
        return; 
    }
    int i = 0;
    for (pAC ch = n->enfant; ch; ch = ch->frere) 
    {
        pNodeL info = ch->node;
        printf("  [%d] "VIOLET"%s"RESET" | leak=%.3f | vol=%.3f | #kids=%d\n",
               i,
               (info && info->ID) ? info->ID : "(noID)",
               info ? info->leak : 0.0f,
               info ? info->volume_recu : 0.0,
               count_children_ac(ch));
        i++;
    }
    if (i == 0) puts("  (no children)");
}

/*
Commandes:
  p                : afficher noeud courant
  ls               : lister enfants
  cd <i>           : aller à l'enfant index i
  up               : remonter au parent (via pile)
  root             : revenir à la racine
  path             : afficher chemin
  find <substr>    : recherche DFS (substring sur ID) depuis courant, puis se positionne dessus si trouvé
  q                : quitter

  show             : Voir le volume reçu par ce tronçont
  cdf              : Aller au frere suivant
  cde              : Aller au premier enfant
*/
void debug_arbre_leaks(pAC root)
{
    if (!root) 
    {
        puts("debug_arbre_leaks: root NULL"); 
        return; 
    }

    int cap = 64, top = 0;
    pAC *stack = malloc((size_t)cap * sizeof(pAC));
    if (!stack) 
    {
        puts("malloc stack failed");
        return; 
    }
    pAC cur = root;
    char cmd[256];

    puts("=== DEBUG ARBRE (leaks reseau) ===");
    puts(BLEU_CLAIR"Liste des commandes"RESET);
    puts(BLEU_CLAIR"cmd: p | ls | cd <i> | up | root | path | q | show | cdf | cde | review"RESET);
    for (;;)
    {

        printf("\n[%s] > ", (cur->node && cur->node->ID) ? cur->node->ID : "(noID)");
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        cmd[strcspn(cmd, "\r\n")] = 0;

        if (strcmp(cmd, "q") == 0) break;

        if (strcmp(cmd, "review") == 0)
        {
            puts(BLEU_CLAIR"Liste des commandes"RESET);
            puts(BLEU_CLAIR"cmd: p | ls | cd <i> | up | root | path | q | show | cdf | cde"RESET);  
            continue;          
        }

        if (strcmp(cmd, "p") == 0)
        {
            pNodeL info = cur->node;
            printf("ID=%s | leak=%.3f | vol=%.3f | #kids=%d\n",(info && info->ID) ? info->ID : "(noID)",info ? info->leak : 0.0f,info ? info->volume_recu : 0.0,count_children_ac(cur));
            continue;
        }
        
        if(strcmp(cmd, "cdf") == 0)
        {
            cur = cur->frere;
            continue;
        }

        if(strcmp(cmd, "cde") == 0)
        {
            cur = cur->enfant;
            continue;
        }

        if(strcmp(cmd, "show") == 0)
        {
            printf("Le volume recu de : %s est de "VIOLET"%lf\n"RESET, cur->node->ID , cur->node->volume_recu);
            continue;
        }

        if (strcmp(cmd, "ls") == 0)
        {
            print_children_ac(cur);
            continue;
        }

        if (strcmp(cmd, "up") == 0)
        {
            if (top == 0) puts("(On est deja a la racine)");
            else cur = stack[--top];
            continue;
        }

        if (strcmp(cmd, "root") == 0)
        {
            cur = root;
            top = 0;
            continue;
        }

        if (strcmp(cmd, "path") == 0)
        {
            printf("PATH: ");
            for (int i = 0; i < top; i++) 
            {
                pNodeL info = stack[i]->node;
                printf("%s -> ", (info && info->ID) ? info->ID : "(noID)");
            }
            printf("%s\n", (cur->node && cur->node->ID) ? cur->node->ID : "(noID)");
            continue;
        }

        if (strncmp(cmd, "cd ", 3) == 0)
        {
            char *arg = cmd + 3;
            while (*arg == ' ') arg++;
            int idx = atoi(arg);

            pAC nxt = child_at_ac(cur, idx);
            if (!nxt) 
            { 
                puts("invalid index"); 
                continue; 
            }

            if (top >= cap) 
            {
                cap *= 2;
                pAC *tmp = realloc(stack, (size_t)cap * sizeof(pAC));
                if(!tmp) { puts("realloc failed"); break; }
                stack = tmp;
            }

            stack[top++] = cur;
            cur = nxt;
            continue;
        }

        puts("Commande inconnu");
    }

    free(stack);
}

void calculVolume(pAC Reseau, double *perte, double *perteMax, pAC *TPerteMax)//PerteMax est initialement nulle (= 0)
{
    if(Reseau)
    {
        int Nb_Child = count_children_ac(Reseau);
        //printf("Le volume de %s : %lf sera divisé en %d\n",Reseau->node->ID, Reseau->node->volume_recu,Nb_Child);

        if(Nb_Child == 0)
        {
            return;
        }

        double VolperChild = Reseau->node->volume_recu / Nb_Child;
        pAC child = Reseau->enfant;
        while(Nb_Child > 0 && child)
        {
            child->node->volume_recu = VolperChild * (1.0 - child->node->leak / 100.0);
            double p = VolperChild - child->node->volume_recu;
            if(*(perteMax) < p)
            {
                *perteMax = p;
                *TPerteMax = Reseau;
            }
            *perte += p;
            child = child->frere;
            Nb_Child--;
        }
        calculVolume(Reseau->frere,perte,perteMax, TPerteMax);
        calculVolume(Reseau->enfant,perte,perteMax, TPerteMax);
    }
    else return;
}


void free_leaks_all(pAC reseau, pAVL indexInfo)
{
    if (reseau) freeAC(reseau);       // libère uniquement les AC*
    if (indexInfo) freeAVL(indexInfo); // libère NodeL/ID + AVL*
}

int leaks(char *IDUsine, FILE *fSourceL, FILE *fEnfant)
{
    int rturn = 0;
    if (!IDUsine || !fSourceL || !fEnfant) return 2;

    char line[128];
    char ID[128];
    double volume;
    bool usine_true = false;

    char ActualID[128], Next[128], tiret[128];
    float leakVal;

    printf(BLEU"On travaille sur le réseau de l'usine %s\n"RESET, IDUsine);

    VolumeTraite(fSourceL);

    FILE *VT = fopen("returnreal.txt", "r");
    if (!VT) return 3;

    while (fgets(line, sizeof(line), VT) && !usine_true) {
        if (sscanf(line, "%127[^;];%lf", ID, &volume) != 2) continue;
        if (strcmp(ID, IDUsine) == 0) usine_true = true;
    }
    fclose(VT);
    printf("%s\n", usine_true ? VERT"L'usine existe"RESET : ROUGE"L'usine n'existe pas"RESET);
    if (!usine_true)
    {
        FILE *returnleaks = fopen("returnleaks.dat", "w");
        if (returnleaks) 
        {
            fprintf(returnleaks,"-1");
            fclose(returnleaks);
        }
        return -1;
    }

    // Index infos : ID -> NodeL* (NodeL contient aussi ac) 
    pAVL IndexInfo = creerAVL(IDUsine, AVL_LEAKS);
    if (!IndexInfo) return 7;

    // Racine topo = ac de l'usine
    pNodeL infoRoot = IndexInfo->data.LeaksPart;      // déjà cree par creerAVL
    if (!infoRoot) return 7;
    else infoRoot->volume_recu = volume;
    //printf("Volume partant de l'usine : %lf\n",infoRoot->volume_recu);

    if (!infoRoot->ac) 
    {
        infoRoot->ac = creerAC(infoRoot);
        if (!infoRoot->ac) return 7;
    }
    pAC Reseau = infoRoot->ac; //Notre reseau final avec comme racine l'usine

    int h = 0;

    // Build de reseau
    while (fgets(line, sizeof(line), fEnfant))
    {
        char poubelle[128];
        if(sscanf(line, "%127[^;];%127[^;];%127[^;];%127[^;];%f",poubelle,ActualID, Next, tiret, &leakVal) != 5) continue;

        if (strcmp(tiret, "-") != 0) return 4;
        if (leakVal < 0.0f) return 4;

        pAVL avlP = recherche(IndexInfo, ActualID);
        if (!avlP) {
            h = 0;
            IndexInfo = insertionAVL(IndexInfo, ActualID, &h, AVL_LEAKS);
            avlP = recherche(IndexInfo, ActualID);
            if (!avlP) return 5;
        }

        pAVL avlC = recherche(IndexInfo, Next);
        if (!avlC) {
            h = 0;
            IndexInfo = insertionAVL(IndexInfo, Next, &h, AVL_LEAKS);
            avlC = recherche(IndexInfo, Next);
            if (!avlC) return 5;
        }

        pNodeL infoParent = avlP->data.LeaksPart;
        pNodeL infoChild  = avlC->data.LeaksPart;
        if (!infoParent || !infoChild) return 7;

        // fuite sur l'enfant
        infoChild->leak = leakVal;

        if (!infoParent->ac) {
            if (strcmp(infoParent->ID, IDUsine) == 0) infoParent->ac = Reseau;
            else {
                infoParent->ac = creerAC(infoParent);
                if (!infoParent->ac) return 7;
            }
        }

        if (!infoChild->ac) {
            infoChild->ac = creerAC(infoChild);
            if (!infoChild->ac) return 7;
        }
        InsertionAC(infoParent->ac, infoChild->ac);
    }

    //puts("Volume sortant de l'usine");
    //printf(ROUGE"%lf\n"RESET, infoRoot->volume_recu);//volume_reçu pour roots est le volume sortant;

    double perte = 0.0;
    double perteMax = 0.0;
    pAC TPM = NULL;
    calculVolume(Reseau,&perte,&perteMax,&TPM);

    printf("Le tronçon qui pert le plus est : %s -> %s avec un volume de %lf perdu!\n",TPM->node->ID,TPM->enfant->node->ID,perteMax);

    //debug_arbre_leaks(Reseau);
    //rturn
    FILE *returnleaks = fopen("returnleaks.dat", "w");
    if (returnleaks) {
;
        fprintf(returnleaks, "%s;%lf\n", IDUsine,perte/1000); //On divise par 1000 pour avoir des millions de m^3
        fprintf(returnleaks,"Le tronçon qui pert le plus est : %s -> %s avec un volume de %lf perdu!\n",TPM->node->ID,TPM->enfant->node->ID,perteMax);
        fclose(returnleaks);
    }
    free_leaks_all(Reseau, IndexInfo);
    IndexInfo = NULL;
    return 0;
}



