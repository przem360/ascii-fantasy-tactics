#include <stdio.h>
#include <string.h>
#include "resources.h"
#include "asciibattle.c"

int killed = 0; /* how many monsters were killed by fighters */
int died = 0;   /* how many fighters were killed by monsters */
char command[12];
char command_code; /* what analyse_command things about user input?*/



int main (int argc, char *argv[]){
    printf("ASCII FANTASY TACTICS");
    ascii_battle_init();
    while(killed<amount_of_monsters && died<amount_of_fighters && command_code !='q'){
        clear_screen();
        draw_interface();
        printf("Command > \n");
        scanf("%s",command);
        command_code = analyse_command(command);
    }
}