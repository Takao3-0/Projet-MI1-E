#include "head.h"
#include "histo.h"

int main(int argc, char *argv[]) 
{
/*On utilise ce qui est passe en parametre argv pour identifier la commande*/
    if (strcmp(argv[1], "histo") == 0)
    {
        if(argc < 3)
        {
            printf("Il n'y a pas d'instruction pour histo");
        }
        else 
        {
            
        }    
    }
    else if (strcmp(argv[1], "leak") == 0)
    {

    }
    else 
    {
        printf(ROUGE"Commande non reconnu!\n"RESET);
    }


}
