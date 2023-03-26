#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "resources.h"
#include "asciibattle.c"

int killed = 0; /* how many monsters were killed by fighters */
int died = 0;   /* how many fighters were killed by monsters */
// char selected_fighter[] = "nn"; /* asciibattle.c is storing id of selected fighter here */
char command[12];
char command_code[1]; /* what analyse_command things about user input?*/
int wasmoved = 0;
int tookaction = 0;
int aiaction;
int fid, mid;


int main (int argc, char *argv[]){
    ascii_battle_init();
    while(killed<amount_of_monsters && died<amount_of_fighters && *command_code != 'q'){
        if ((wasmoved > 0)&&(tookaction > 0)){
            wasmoved = 0;
            tookaction = 0;
            whoseturn++;
        }
        if (whoseturn>(amount_of_fighters+amount_of_monsters)){
            wasmoved = 0;
            tookaction = 0;
            whoseturn = 1;
        }
        /* check here if selected pcs hp <=0 */
        clear_screen();
        printf("ASCII FANTASY TACTICS \n");
        place_figures();
        let_move();
        draw_interface();
        if (player_or_monster == 1){
            printf("Command > ");
            fgets(command,12,stdin);
            command_code[0] = analyse_command(command);
            if (command_code[0] == 'm'){
                printip("MOVING",1);
                wasmoved = player_action_move(selected_fighter);
            }
            if (command_code[0] == 'a'){
                tookaction = player_action_attack(selected_fighter);
                printip("ATTACKING",1);
                draw_interface();
            }
            if (command_code[0] == 'c'){
                tookaction = player_action_cast(selected_fighter);
                printip("CASTED SPELL",1);
                draw_interface();
            }
            if (command_code[0] == 's'){
                // player_action_move(selected_fighter);
                printip("SKIPPING",1);
                wasmoved = 1;
                tookaction = 1;
                // whoseturn++;
            }
        }
        if (player_or_monster == 2){
            /* monster's move */
            // draw_interface();
            mid = get_array_index('m',selected_monster);
            if (monsters[mid].hp > 0) {
                aiaction = ai_choose_action(selected_monster);
                if (aiaction == 1) {
                    tookaction = 1;
                    wasmoved = 0;
                }
                if (aiaction == 2) {
                    tookaction = 0;
                    wasmoved = 1;
                }
                if (wasmoved == 0) {
                    // fid = get_array_index('f',);
                    chase_figters(mid,monsters[mid].target_index);
                    // chase_figters(me_in_array, monsters[me_in_array].target_index)
                    wasmoved = 1;
                    printf("fid: %d",fid);
                }
                if (tookaction == 0) {
                    tookaction = 1; /* for now */
                }
                // monsters_action();
                // wasmoved = 1;
                // tookaction = 1;
                draw_interface();
                // sleep(1);
            }
            else {
                monsters_action();
                wasmoved = 1;
                tookaction = 1;
                draw_interface();
            }
        }
        }
        printf("Dice: %d",dice(20));
        printf("POM: %d \n",player_or_monster);
        printf("Turn: %d \n",whoseturn);
        // printf("Command: %c \n",command_code[0]);
        printf("Selected fighter: %s \n",selected_fighter);
        printf("whoseturn: %d, selected monster: %s \n",whoseturn,selected_monster);
    }
