#include "head.h"
#include "histo.h"
#include "leaks.h"
#include "type.h"


int main(int argc, char *argv[]) 
{
    int rturn = 0;
/*On utilise ce qui est passe en parametre argv pour identifier la commande*/
    puts(ROUGE"Debut d'execution du C"RESET);
    if (strcmp(argv[2], "histo") == 0)
    {
        if(argc < 3)
        {
            printf("Il n'y a pas d'instruction pour histo");
            return ERREUR_ARG;
        }
        else
        {
            if (strcmp(argv[3], "src") == 0)
            {
                puts(VIOLET"Commande histo SRC entrée!"RESET);
                FILE *fSource = fopen(argv[4], "r");
                FILEOPEN(fSource, argv[4]);
                rturn = VolumeCapte(fSource);
                fclose(fSource);
            }
            else if (strcmp(argv[3], "real") == 0)
            {
                puts(VIOLET"Commande histo REAL entrée!"RESET);
                FILE * fSourceL = fopen(argv[4], "r");
                FILEOPEN(fSourceL, argv[4]);

                rturn = VolumeTraite(fSourceL);
                fclose(fSourceL);                
            }
            else if (strcmp(argv[3], "max") == 0)
            {
                puts(VIOLET"Commande histo MAX entrée!"RESET);
                FILE * Usine = fopen(argv[4], "r");
                FILEOPEN(Usine, argv[4]);

                rturn = Max(Usine);
                fclose(Usine);                    

            }
            else if (strcmp(argv[3], "all") == 0)
            {
                puts(VIOLET"Commande histo ALL entrée!"RESET);    
                FILE * Usine = fopen(argv[4], "r");
                FILEOPEN(Usine, argv[4]);
                FILE * fSourceL = fopen(argv[5], "r");
                FILEOPEN(fSourceL, argv[5]);
                FILE * fSource = fopen(argv[6], "r");
                FILEOPEN(fSource, argv[6]);
                rturn = Max(Usine);
                if (rturn != 0)
                {
                    puts(ROUGE"Fin d'execution du C"RESET);
                    return rturn;
                }
                rturn = VolumeCapte(fSource);
                if (rturn != 0)
                {
                    puts(ROUGE"Fin d'execution du C"RESET);
                    return rturn;
                }
                rturn = VolumeTraite(fSourceL);
                if (rturn != 0)
                {
                    puts(ROUGE"Fin d'execution du C"RESET);
                    return rturn;
                }
                fclose(fSourceL);  
                fclose(Usine); 
                fclose(fSource); 
                rturn = HistoALL(); 

            }     
        }   
    }
    else if (strcmp(argv[2], "leaks") == 0)
    {
        if (argc < 3)
        {
            printf(ROUGE"Il n'y a pas assez d'argement pour leaks\n");
            return ERREUR_ARG;
        }
        else printf(BLEU"Fonction leaks\n"RESET);
        /*
        Pour leak la commande attendu du shell sera 
            ./wildwater    script.sh    leaks    ID_Usine    File1      File2
            argv[0]        argv[1]      argv[2]  argv[3]     argv[4]    argv[5]
        */
        FILE * fEnfant = fopen(argv[4], "r");
        if (!fEnfant)
        {
            return ERREUR_FOPEN;                   
        }
        FILE * fSourceL = fopen(argv[5], "r");
        if (!fSourceL)
        {
            return ERREUR_FOPEN;                   
        }
        rturn = leaks(argv[3],fSourceL, fEnfant);
        fclose(fSourceL);
        fclose(fEnfant);
    }
    else 
    {
        printf(ROUGE"Commande non reconnu!\n"RESET);
        return ERREUR_ARG;
    }
    puts(ROUGE"Fin d'execution du C"RESET);
    printf(VERT"%d\n"RESET, rturn);
    return rturn;
}
