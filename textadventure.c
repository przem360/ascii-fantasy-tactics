#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* for atoi(); */
// #include "locations.h"

#include <unistd.h> /* for pausing on POSIX */
// #include <dos.h> /* for pausing on Windows */
#include "settings.h"
#include "colors.h"
#include "helpers.h"
#include "globals.h"
#include "locations.h"
#include "textadventure.h"
#include "asciibattle.h"

#define AMOUNT_OF_LOCATIONS 36

extern int invisible;


int current_location;
int attackers[MAX_MONSTERS_ATTACKING];
int qresult;
char command[12];
int was_i_here;
// int amount_of_locations = sizeof(rooms) / sizeof(rooms[0]);

int location_history[AMOUNT_OF_LOCATIONS];

int check_location_in_history(int loc){
    // if loaction is found in location_history[amount_of_locations] return index
    // else return -1
    int i;
    for (i=0;i<AMOUNT_OF_LOCATIONS;i++){
        if (location_history[i] == loc) return i;
    }
    return -1;
}
void add_location_to_history(int loc){
    // if (loc==0) printf("ERROR in textadventure.c add_location_to_history(): int loc zero value.");
    int i;
    for (i=0;i<AMOUNT_OF_LOCATIONS;i++){
        if (location_history[i]==0) {
            location_history[i] = loc;
            break;
        }
    }
}


char *getcomm(char *inpstr,int inpsiz) {
    char    *seachr;                    /* Result of search via strchr()     */

    if (inpstr==NULL) {
        return(NULL);
    }
    if (fgets(inpstr,inpsiz,stdin)==NULL) {
        return(NULL);
    }
    seachr=strchr(inpstr,'\n');
    if (seachr!=NULL) *seachr=0;

    return(inpstr);
}

int save_state(void){
    char *filename = SAVE_FILE;
    int i;

    // open the file for writing
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    fprintf(fp, "%d\n", current_location);
    for (i=0; i<AMOUNT_OF_LOCATIONS; i++) {
        fprintf(fp, "%d\n", rooms[i].is_enemy);
    }
    fclose(fp);
    return 0;
}

int load_state(void){
    char *filename = SAVE_FILE;
    char info[4];
    int i;
    int is_monster;
    int room_id;
    if (DBG_MODE == 1) {printf("Loading game...\n");sleep(2);}

    // opening the file for reading
    FILE *fp = fopen(filename, "r");

    if(fp != NULL) {
        i=0;
        while (fgets(info, sizeof(info), fp)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        if (i==0) {
            current_location = atoi(info);
            if (DBG_MODE == 1) {printf("current_location: %d\n",current_location);sleep(2);}
            }
        else if (i>1 && ((info[0]=='0')||(info[0]=='1'))){
            room_id = i-1;
            is_monster = atoi(info);
            if (DBG_MODE == 1) {printf("Room: %d monster: %d\n",room_id,is_monster);sleep(1);}
            rooms[room_id].is_enemy = is_monster;
        }
        i++; 
    }
    }
    else {
        printf("Error opening the file %s", filename);
        return -1;
    }
    fclose(fp);
    printf("\nGame loaded.\n");
    sleep(1);
    return 0;
}


int get_location_by_id(int lid){
    int i;
    for (i=0;i<AMOUNT_OF_LOCATIONS;i++){
        if(rooms[i].id == lid) return i;
    }
    return 99;
}

void show_intro(void){
    char ch;
    clear_screen();
    current_location = 1;
    if (COLOURS_ON == 1) {
        printf(DSC "%s" reset,intro_text);
        printf("Press any key to continue > ");
    } else {
        printf("%s", intro_text);
        printf("Press any key to continue > ");
    }
    ch = getchar();
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

int display_current_location(int loc){
    int cloc = get_location_by_id(loc);
    was_i_here = check_location_in_history(loc);
        if (was_i_here<0){
            add_location_to_history(loc);
        }
    printf("\t\tASCII FANTASY TACTICS\n\t\t---------------------\nLocation: %s\n\n",rooms[cloc].name);
    if (COLOURS_ON == 1){
        // printf(DSC "%s \n\n" reset,rooms[cloc].description);
        wprint(rooms[cloc].description,LIMIT_TXT_WIDH,1);
        if (was_i_here>=0){
            wprint("\nYou know, you have been here before.\n",LIMIT_TXT_WIDH,1);
        }
    }
    else {
        // printf("%s \n\n",rooms[cloc].description);
        wprint(rooms[cloc].description,LIMIT_TXT_WIDH,0);
        if (was_i_here>0){
            wprint("\nYou know, you have been here before.\n",LIMIT_TXT_WIDH,0);
        }
    }
    if (loc == FINAL_LOCATION) {
        printf("\t Press [ENTER] to quit...");
    }
    else {
        printf("Available directions: ");
        if (rooms[cloc].go_north > 0) printf("NORTH ");
        if (rooms[cloc].go_east  > 0) printf("EAST ");
        if (rooms[cloc].go_south > 0) printf("SOUTH ");
        if (rooms[cloc].go_west  > 0) printf("WEST ");
        printf("\n\n");
    }
    if (DBG_MODE == 1) {
        printf("\nroom number: %d\n",rooms[cloc].id);
        printf("  Invisible: %d\n",invisible);
    }
    return 0;
}

int read_command(void){
    printf("\n\nWhat to do?  > ");
    fgets(command,12,stdin);
    char *p = strchr(command, '\n');
    if (p) *p = 0;
    return 0;
}

int explore_dungeon(void){
    int cloc = get_location_by_id(current_location);
    int battle_result = 0;
    int previous_location = 0;
    qresult = 1;
    was_i_here = 0;
    // clear_screen();
    while (1) {
        clear_screen();
        if(rooms[cloc].is_enemy == 1 && invisible == 0){
            battle_result = play_battle(current_location, rooms[cloc].arena, 2);
            // if (game_mode != 2) {break;} /* re-checking: play_battle(); can change game_mode */
            if (battle_result == 4) rooms[cloc].is_enemy = 0;
            if (battle_result == 2) {
                current_location = previous_location;
                }
        }
        display_current_location(current_location);
        if (current_location == FINAL_LOCATION) {
            read_command();
            return 0;
        }
        read_command();
        if (strstr(command,"quit") !=NULL) {return 0;}
        if (strstr(command, "save") != NULL) { save_state(); }
        if (command[0]=='g'&&command[1]=='o'){
            if (strstr(command, "north") != NULL) {
                if (rooms[cloc].go_north > 0) {
                    printf("\n Going north... \n");
                    previous_location = current_location;
                    current_location = rooms[cloc].go_north;
                    cloc = get_location_by_id(current_location);
                    }
                else printf("\n Can\'t go there... \n");
            }
            else if (strstr(command, "east") != NULL) {
                if (rooms[cloc].go_east > 0) {
                    printf("\n Going east... \n");
                    previous_location = current_location;
                    current_location = rooms[cloc].go_east;
                    cloc = get_location_by_id(current_location);
                    }
                else printf("\n Can\'t go there... \n");
            }
            else if (strstr(command, "south") != NULL) {
                if (rooms[cloc].go_south > 0) {
                    printf("\n Going south... \n");
                    previous_location = current_location;
                    current_location = rooms[cloc].go_south;
                    cloc = get_location_by_id(current_location);
                    }
                else printf("\n Can\'t go there... \n");
            }
            else if (strstr(command, "west") != NULL) {
                if (rooms[cloc].go_west > 0) {
                    printf("\n Going west... \n");
                    previous_location = current_location;
                    current_location = rooms[cloc].go_west;
                    cloc = get_location_by_id(current_location);
                    }
                else printf("\n Can\'t go there... \n");
            }
            else printf("\n Command [go] needs direction. \n");
            sleep(2);
        }
    }
    clear_screen();

    if (qresult == 0){
        printf("\nQuitting exploration mode\n");
        return 0;
    }

    return 0;
}