#include <stdio.h>
#include <string.h>
#include "resources.h"
#include "helpers.c"

int killed = 0; /* how many monsters were killed by fighters */
int died = 0;   /* how many fighters were killed by monsters */
char command[5];
char command_code; /* what analyse_command things about user input?*/



int main (int argc, char *argv[]){
    while(killed<amount_of_monsters && died<amount_of_fighters && command_code !='q'){
        printf("ASCII FANTASY TACTICS");
        memcpy(screen, lvl1,sizeof(lvl1));
        place_figures();
        draw_interface();
        clear_screen();
        draw_range("J6",4);
        printip("AVAILABLE FIGHTERS...",1);
        draw_interface();
        // printf("Monsters to kill: %d \n",amount_of_monsters);
        int d20;
        d20 = dice(20);
        printf("\n D20 throw: %d\n",d20);
        printf("Select fighters \n > ");
        scanf("%s",command);
        command_code = analyse_command(command);
    }
}