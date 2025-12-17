#include "head.h"
#include "histo.h"

int main(int argc, char *argv[]) 
{
/*On utilise ce qui est passe en parametre argv pour identifier la commande*/
    if (strcmp(argv[2], "histo") == 0)
    {
        if(argc < 3)
        {
            printf("Il n'y a pas d'instruction pour histo");
            return 3;
        }
        else
        {
            printf("Commande histo entrée!\n");
            if (strcmp(argv[3], "src") == 0)
            {
                FILE *fUsine  = fopen(argv[4], "r");
                if (!fUsine)
                {
                    fclose(fUsine); 
                    return 2;                   
                }
                FILE *fSource = fopen(argv[5], "r");
                if (!fSource)
                {
                    fclose(fSource); 
                    return 2;                   
                }
                VolumeCapte(fUsine,fSource);
                fclose(fUsine);
                fclose(fSource);
            }
            else if (strcmp(argv[3], "real") == 0)
            {
                FILE * fUsine   = fopen(argv[4], "r");
                if (!fUsine)
                {
                    fclose(fUsine); 
                    return 2;                   
                }
                FILE * fSourceL = fopen(argv[5], "r");
                if (!fSourceL)
                {
                    fclose(fSourceL); 
                    return 2;                   
                }
                VolumeTraite(fUsine,fSourceL);
                fclose(fUsine);
                fclose(fSourceL);                
            }
        }   
    }
    else if (strcmp(argv[2], "leaks") == 0)
    {
        if (argc < 3)
        {
            printf(ROUGE"Il n'y a pas assez d'argement pour leaks\n");
            return 3;
        }
        /*
        Pour leak la commande attendu du shell sera 
            ./wildwater    script.sh    leaks    File.txt    ID_usine
            argv[0]        argv[1]      argv[2]  argv[3]     argv[4]
        */
        FILE * fUsine = fopen(argv[3], "r");
        if (!fUsine)
        {
            fclose(fUsine); 
            return 2;                   
        }


    }
    else 
    {
        printf(ROUGE"Commande non reconnu!\n"RESET);
        return 1;
    }
    return 0;
}
