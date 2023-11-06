#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "settings.h"

void clear_screen(void){
    if (DBG_MODE == 0){
        system("clear"); //*nix
        // system("cls"); //windows
    }
    else {
        // dummy:
        int i,l;
        l = 50;
        for (i=0;i<l;i++){
             printf("\n");
        }
    }
}
