#include <stdio.h>
#include <string.h>
#include "resources.h"
#include "asciibattle.c"

int killed = 0; /* how many monsters were killed by fighters */
int died = 0;   /* how many fighters were killed by monsters */
char command[12];
char command_code[1]; /* what analyse_command things about user input?*/



int main (int argc, char *argv[]){
    ascii_battle_init();
    while(killed<amount_of_monsters && died<amount_of_fighters && *command_code != 'q'){
        clear_screen();
        printf("ASCII FANTASY TACTICS \n");
        draw_interface();
        printf("Command > ");
        // scanf("%s",command);
        fgets(command,12,stdin);
        command_code[0] = analyse_command(command);
        if (command_code[0] == 'm'){
            player_action_move("av");
        }
        // printf("Main Command code: %c",command_code[0]);
        // printf("Main comml 3: %c",test_comml[0]);
    }
}