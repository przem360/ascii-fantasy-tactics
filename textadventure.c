#include <stdio.h>
#include <string.h>
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

// int invisible;
int current_location;
int attackers[MAX_MONSTERS_ATTACKING];
int qresult;
char command[12];

void get_attackers(void){
    int i;
    for (i=0; i<MAX_MONSTERS_ATTACKING;i++){}
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
    int amount_of_locations = sizeof(rooms) / sizeof(rooms[0]);
    int i;

    // open the file for writing
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    fprintf(fp, "CL:%d\n", current_location);
    for (i=0; i<amount_of_locations; i++) {
        fprintf(fp, "%d:%d\n", rooms[i].id, rooms[i].is_enemy);
    }
    fclose(fp);
    return 0;
}

int load_state(void){
    char *filename = SAVE_FILE;
    char ch;
    int lines = 0;

    // opening the file for reading
    FILE *fp = fopen(filename, "r");

    char state[100];

    if(fp != NULL) {
        while(!feof(fp)) {
            ch = fgetc(fp);
            if(ch == '\n') {
                lines++;
                }
        }
        printf ("State file loaded, %d lines found. \n",lines);
        while(fgets(state, 100, fp)) {
            // printf("%s", state);
            char * token = strtok(state, ":");
        }
    }
    else {
        printf("Error opening the file %s", filename);
        return -1;
    }
    fclose(fp);
    return 0;
}

int compareST(char a[],char b[])  
{  
    int flag=0,i=0;  // integer variables declaration  
    while(a[i]!='\0' &&b[i]!='\0')  // do until the end of one string 
    {  
       if(a[i]!=b[i])  
       {  
           flag=1;  
           break;  
       }  
       i++;  
    } 
    if(a[i]!='\0'||b[i]!='\0')
       return 1;
    if(flag==0)  
    return 0;  
    else  
    return 1;  
}

int get_location_by_id(int lid){
    int amount_of_locations = sizeof(rooms)/sizeof(rooms[0]);
    int i;
    for (i=0;i<amount_of_locations;i++){
        if(rooms[i].id == lid) return i;
    }
    return 99;
}

void show_intro(void){
    if (COLOURS_ON == 1) {
        printf(DSC "%s" reset,intro_text);
        printf("Y/N? > ");
    } else {
        printf("%s", intro_text);
        printf("Y/N? > ");
    }
}

int display_current_location(int loc){
    int cloc = get_location_by_id(loc);
    printf("\t\tASCII FANTASY TACTICS\n\t\t---------------------\nLocation: %s\n\n",rooms[cloc].name);
    if (COLOURS_ON == 1){
        printf(DSC "%s \n\n" reset,rooms[cloc].description);
    }
    else {
        printf("%s \n\n",rooms[cloc].description);
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
        printf("  game_mode: %d\n", game_mode);
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
    clear_screen();
    while((strstr(command, "n") == NULL) && (strstr(command, "y") == NULL)){
        show_intro();
        while( (command[0] = getchar() != '\n') && (command[0] != EOF)); 
        read_command();
        // getcomm(int_sel,2);
        if (command[0] == 'n') { qresult = 0; game_mode = 0; }
        if (command[0] == 'y') { qresult = 1; game_mode = 2; }
        if (DBG_MODE == 1) {printf("Command: %c\ngame_mode: %d\nqresult: %d\n",command[0],game_mode,qresult);}
    }
    while (qresult != 0 && game_mode == 2) {
        if (DBG_MODE == 1) {printf("game_mode: %d\nqresult: %d\n",game_mode,qresult);}
        clear_screen();
        if(rooms[cloc].is_enemy == 1 && invisible == 0){
            selected_arena = rooms[cloc].arena;
            battle_result = play_battle(current_location);
            if (game_mode != 2) {break;} /* re-checking: play_battle(); can change game_mode */
            if (battle_result == 1) rooms[cloc].is_enemy = 0;
            if (battle_result == 2) {
                current_location = previous_location;
                }
        }
        display_current_location(current_location);
        if (current_location == FINAL_LOCATION) {
            read_command();
            game_mode = 0;
            break;
        }
        read_command();
        qresult = compareST(command, "quit");
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
        game_mode = 0;
    }

    return 0;
}