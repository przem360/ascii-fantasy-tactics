#include <stdio.h>
#include <string.h>
#include "resources.h"
#include "asciibattle.c"

int killed = 0; /* how many monsters were killed by fighters */
int died = 0;   /* how many fighters were killed by monsters */
// char selected_fighter[] = "nn"; /* asciibattle.c is storing id of selected fighter here */
char command[12];
char command_code[1]; /* what analyse_command things about user input?*/
int wasmoved = 0;
int tookaction = 0;

char selected_spell[] = "lb";


int main (int argc, char *argv[]){
    ascii_battle_init();
    while(killed<amount_of_monsters && died<amount_of_fighters && *command_code != 'q'){
        if (whoseturn>(amount_of_fighters+amount_of_monsters)){
            whoseturn = 1;
        }
        clear_screen();
        printf("ASCII FANTASY TACTICS \n");
        if (command_code[0]!='c'){
            place_figures();
        }
        let_move();
        draw_interface();
        if (player_or_monster == 1){
            printf("Command > ");
            fgets(command,12,stdin);
            command_code[0] = analyse_command(command);
            if (command_code[0] == 'm'){
                // player_action_move(selected_fighter);
                printip("MOVING",1);
                wasmoved = player_action_move(selected_fighter);
                if (wasmoved == 1){
                    whoseturn++;
                }
            }
            if (command_code[0] == 'c'){
                // player_action_move(selected_fighter);
                tookaction = player_action_cast(selected_fighter,selected_spell);
                printip("CASTED SPELL",1);
                if (tookaction == 1){
                    whoseturn++;
                }
                draw_interface();
            }
            if (command_code[0] == 's'){
                // player_action_move(selected_fighter);
                printip("SKIPPING",1);
                whoseturn++;
            }
        }
        if (player_or_monster == 2){
            monsters_action();
            // draw_interface();
            sleep(1);
        }
        }
        // scanf("%s",command);
        printf("POM: %d \n",player_or_monster);
        printf("Turn: %d \n",whoseturn);
        printf("Command: %c \n",command_code[0]);
    }
