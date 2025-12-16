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
        }
        else
        {
            printf("Commande histo entrée!\n");
            if (strcmp(argv[3], "src") == 0)
            {
                FILE *fUsine  = fopen(argv[4], "r");
                FILE *fSource = fopen(argv[5], "r");
                VolumeCapte(fUsine,fSource);
                fclose(fUsine);
                fclose(fSource);
            }
            else if (strcmp(argv[3], "real") == 0)
            {
                FILE * fUsine   = fopen(argv[4], "r");
                FILE * fSourceL = fopen(argv[5], "r");
                VolumeTraite(fUsine,fSourceL);
                fclose(fUsine);
                fclose(fSourceL);                
            }
        }   
    }
    else if (strcmp(argv[1], "leak") == 0)
    {

    }
    else 
    {
        printf(ROUGE"Commande non reconnu!\n"RESET);
    }




    return 0;


}
