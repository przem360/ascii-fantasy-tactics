#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "helpers.h"
#include "settings.h"
#include "globals.h"
#include "asciibattle.h"
#include "textadventure.h"

int invisible;
int max_power;
// int current_location = 1;
int selected_arena = 0;
int game_mode = 0;
int game_loaded;
// char selected_fighter[] = "nn"; /* asciibattle.c is storing id of selected fighter here */
// char command[COMMAND_LENGHT];
// char command_code[2]; /* what analyse_command things about user input?*/


void welcome_screen(){
    char mode_sel;
    char ch;
    // *command_code = 'z';
    printf("\n");
    clear_screen();
    printf(" > ASCII FANTASY TACTICS <\n\n");
    printf("     [s] single  battle     \n");
    printf("     [a] adventure mode     \n");
    printf("     [l] load adventure     \n");
    printf("     [q] quit game        \n\n");
    printf(" > ");
    // getcomm(mode_sel,2);
    // fgets(mode_sel,2,stdin);
    // char *q = strchr(mode_sel, '\n');
    // if (q) *q = 0;
    mode_sel = getchar();
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    if (mode_sel == 's') game_mode = 1;
    if (mode_sel == 'a') game_mode = 2;
    if (mode_sel == 'q') game_mode = 4;
    if (mode_sel == 'i') invisible = 1;
    if (mode_sel == 'l') {game_loaded = 1; load_state();}
    if (mode_sel == 'p') cheat_max_hp();
    if (DBG_MODE == 1) {printf("selection: %c, game_mode: %d \n",mode_sel, game_mode);}
}

int main (int argc, char *argv[]){
    game_loaded = 0;
    while(game_mode<3){
        if (game_mode == 0) welcome_screen();
        if (game_mode == 1) {invisible = 0; play_battle(2);}
        if (game_mode == 2) {
            if (game_loaded == 0) {current_location = 1; show_intro();}
            explore_dungeon();
        }
    }
    if (game_mode == 3) {
        clear_screen();
        printf("\n bye... \n");
        return 0;
    }
    }


