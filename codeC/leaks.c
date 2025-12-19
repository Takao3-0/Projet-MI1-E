#include "leaks.h"


/*

Cahier des charges 

On va mettre dans un arbre avec comme racine notre usine



Format fichier Enfant

Usine;Unite_actuelle;Unite_Suivante;Volume_Max;Fuite


-;Facility complex #RH400057F;Storage #13178;-;3.777  Ligne Usine->Stockage


Facility complex #RH400057F;Storage #13178;Junction #TM12995S;-;3.308  Ligne Stockage->Jonction


Facility complex #RH400057F;Junction #TM12995S;Service #LD204279R;-;3.735 Ligne Jonction->Raccordement


Facility complex #RH400057F;Service #LD204279R;Cust #TJ8256677Z;-;7.273  Ligne Raccordement->Usager


*/










int leaks(char *IDUsine, FILE *fSourceL, FILE * fEnfant)
{
    printf("On entre bien dans le fichier leaks\n");
    printf("On cherche l'usine %s\n", IDUsine);
    if(!fSourceL || !fEnfant) return 2; //Fichier vide 

    char line[128];

    char ID[128];
    //char Aval[128];
    bool usine_true = false;
    //float leak;
    double volume;

    float leak;
    char tiret[128];
    char ActualID[128];
    char Next[128];

    
    VolumeTraite(fSourceL);
    FILE * VT = fopen("returnreal.txt", "r");
    if(!VT) return 3; 
    while(fgets(line, sizeof(line),VT) && !usine_true)
    {
        sscanf(line, "%[^;];%lf", ID, &volume);
        printf("ID : %s, IDUsine : %s\n", ID,IDUsine);
        if(strcmp(ID,IDUsine) == 0) usine_true = true;
    }
    printf("%s\n", usine_true ? VERT"L'usine existe"RESET : ROUGE"L'usine n'existe pas"RESET);
    if (!usine_true) return -1;

    pAVL Index = creerAVL(IDUsine,AVL_LEAKS); //AVL index
    

    pAC Reseau = creerArbreClassique(Index->data.LeaksPart); //0 pour fuite l'usine ne fuit pas et le volume vient grace à real

    int h = 0;
    while(fgets(line,sizeof(line), fEnfant))
    {
        sscanf(line,"%[^;];%[^;];%[^;];%[^;];%f",ID,ActualID,Next,tiret,&leak);

        if(strcmp(tiret, "-") != 0) return 4; //Erreur de formatage;
        if(strcmp(ID, IDUsine) != 0) return 4; //Idem
        if(leak < 0) return 4; //Idem, une fuite ne peux pas être négative;

        //On a passé la batterie de test!

        //pAVL parent = insertionAVL(Index,ActualID,&h,AVL_LEAKS);

        pAVL tamp = NULL;
        pAVL parent = NULL;
        if (!(tamp = recherche(Index,Next)))
        {
            Index = insertionAVL(Index,Next,&h,AVL_LEAKS);
            parent = recherche(Index,ActualID);//On cherche le parent dans l'AVL
            Reseau = InsertionAC(Reseau);
        }
        else 
        {

        }
    }
    




    //return 

    FILE * returnleaks = fopen("returnleaks" , "w");
    fprintf(returnleaks,"%s\n",IDUsine);


    fclose(VT);
    return 0;

}



/*while(fgets(line, sizeof(line), fEnfant)) {
    // Lecture (Votre code corrigé)
    int nb = sscanf(line, "%[^;];%[^;];%[^;];%[^;];%f", 
                    PlantID, NodeAmont, NodeAval, VolumeStr, &leak);
    if (nb != 5) continue;

    // CAS 1 : C'est une source qui alimente NOTRE usine
    // (L'usine est en "Aval" (col 3) et le volume n'est pas "-")
    if (strcmp(NodeAval, targetFactoryID) == 0 && strcmp(VolumeStr, "-") != 0) {
        float vol = atof(VolumeStr);
        // On ajoute ce volume (en enlevant la fuite entre source et usine)
        initialWaterVolume += vol * (1.0 - (leak / 100.0));
        continue; // On passe à la ligne suivante
    }

    // CAS 2 : C'est un tuyau du réseau de NOTRE usine
    // (L'usine est indiquée en col 1, donc c'est bien son réseau)
    if (strcmp(PlantID, targetFactoryID) == 0) {
        
        // On cherche le Parent dans l'annuaire AVL
        Node* parentFunc = searchAVL(myIndex, NodeAmont);

        if (parentFunc != NULL) {
            // Le parent existe, on crée l'enfant
            Node* child = createNode(NodeAval);
            child->percentageLeak = leak;

            // Liaison dans l'arbre (Ajout en tête de liste des enfants)
            child->nextSibling = parentFunc->firstChild;
            parentFunc->firstChild = child;

            // Ajout du nouveau nœud dans l'annuaire AVL pour la suite
            myIndex = insertAVL(myIndex, NodeAval, child);
        }
    }
}*/