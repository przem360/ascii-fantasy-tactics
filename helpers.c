#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "settings.h"
#include "colors.h"

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
void wprint(char desc[], int width, int use_colors){
    int i = 0;
    int total_lenght = strlen(desc);
    if (width > 0) {
        desc[strcspn(desc, "\r\n")] = 0;
        while (i < total_lenght){
            if (use_colors>0){
                printf(DSC "%c" reset, desc[i++]);
                if (i % width == 0) {printf("\n");}
            }
            else {
                printf("%c", desc[i++]);
                if (i % width == 0) {printf("\n");}
            }
        }
        printf("\n\n");
    }
    else {
        if (use_colors>0) printf(DSC "%s \n\n" reset,desc);
        else printf("%s \n\n",desc);
    }
}
