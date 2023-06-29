#include <stdio.h>
#include <string.h>
#include "settings.h"
#include "colors.h"
#include "resources.h"
#include "asciibattle.c"
int play_battle(int enemy_array);
int game_mode = 0;
#include "textadventure.c"

// char selected_fighter[] = "nn"; /* asciibattle.c is storing id of selected fighter here */
// char command[COMMAND_LENGHT];
char command[12] = {'c','o','d','e','e','\0'};
char command_code[2]; /* what analyse_command things about user input?*/
int wasmoved = 0;
int tookaction = 0;
int aiaction;
int fid, mid;

void welcome_screen(){
    char mode_sel[2];
    *command_code = 'z';
    current_location = 1;
    printf("\n");
    clear_screen();
    printf(" > ASCII FANTASY TACTICS <\n\n");
    printf("     [s] single  battle     \n");
    printf("     [a] adventure mode     \n");
    printf("     [q] quit game        \n\n");
    printf(" > ");
    fgets(mode_sel,2,stdin);
    if (mode_sel[0] == 's') game_mode = 1;
    if (mode_sel[0] == 'a') game_mode = 2;
    if (mode_sel[0] == 'q') game_mode = 3;
}

int main (int argc, char *argv[]){
    while(game_mode<3){
        if (game_mode == 0) welcome_screen();
        if (game_mode == 1) play_battle(2);
        if (game_mode == 2) {
            explore_dungeon();
            qresult = 1;
        }
    }
    if (game_mode == 3) {
        clear_screen();
        printf("\n bye... \n");
        return 0;
    }
    }

int play_battle(int enemy_location){
    int amount_of_beasts = sizeof(beasts) / sizeof(beasts[0]);
    int amount_of_monsters_in_room = 0;
    int i = 0;
    for (i=0;i<amount_of_beasts;i++){
        if (beasts[i].location == enemy_location) amount_of_monsters_in_room++;
    }
    ascii_battle_init(enemy_location);
    while(killed<amount_of_monsters_in_room && died<amount_of_fighters && *command_code != 'q'){
        if ((wasmoved > 0)&&(tookaction > 0)){
            wasmoved = 0;
            tookaction = 0;
            whoseturn++;
        }
        // check if fighter of monster with geaven whoseturn (initiative) egzists, if not increase whoseturn
        int found;
        found = 0;
        for (i=0;i<amount_of_monsters;i++){
            if ((monsters[i].initiative == whoseturn) || (pcs[i].initiative == whoseturn)) {
                // printf("\nNo turn number: %d ",whoseturn);
                // whoseturn++;
                // printf(" turn increased to: %d \n",whoseturn);
                found = 1;
            }
        }
        if (found == 0) whoseturn++;

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
        // printf("\nPOM value 1: %d TURN: %d\n",player_or_monster,whoseturn);
        if (player_or_monster == 1){
            /* Player's move */
            clear_range();
            printf("Command > ");
            // fgets(command,COMMAND_LENGHT,stdin);
            scanf("%s", command);
            command_code[0] = analyse_command(command);
            if (command_code[0] == 'm'){
                if (wasmoved == 0) {
                    printip("MOVING             ",1);
                    wasmoved = player_action_move(selected_fighter);
                }
            }
            if (command_code[0] == 'a'){
                if (tookaction == 0) {
                    printip("ATTACKING          ",1);
                    tookaction = player_action_attack(selected_fighter);
                    // draw_interface();
                }
            }
            if (command_code[0] == 'c'){
                if (tookaction == 0) {
                    printip("CAST SPELL         ",1);
                    tookaction = player_action_cast(selected_fighter);
                    // draw_interface();
                }
            }
            if (command_code[0] == 's'){
                // player_action_move(selected_fighter);
                printip("SKIPPING           ",1);
                wasmoved = 1;
                tookaction = 1;
                // whoseturn++;
            }
            if (command_code[0] == 'i'){
                info_screen();
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
                    draw_monster_range(monsters[mid].y_position,monsters[mid].y_position,monsters[mid].mov/10);
                    chase_figters(mid,monsters[mid].target_index);
                    clear_range();
                    // chase_figters(me_in_array, monsters[me_in_array].target_index)
                    wasmoved = 1;
                    // printf("fid: %d",fid);
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

        if (*command_code == 'q') {
            game_mode = 0;
            qresult = 0;
        }
        
        if (died >= amount_of_fighters){
            game_mode = 3;
            restore_fighters_hp();
            clear_screen();
            printf("You lost! \n");
            sleep(2);
            return 2;
        }
        if (killed >= amount_of_monsters || killed >= amount_of_monsters_in_room){
            game_mode = 2;
            clear_screen();
            printf("You won! \n");
            sleep(2);
            return 1;
        }
    return 0;
}
