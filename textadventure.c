#include <stdio.h>
#include <string.h>
#include "locations.h"

#include <unistd.h> /* for pausing on POSIX */
// #include <dos.h> /* for pausing on Windows */

int current_location = 1;
char command[12];
int qresult = 1;

int compareST(char a[],char b[])  
{  
    int flag=0,i=0;  // integer variables declaration  
    while(a[i]!='\0' &&b[i]!='\0')  // while loop  
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


int display_current_location(int loc){
    int cloc = get_location_by_id(loc);
    if (COLOURS_ON == 1){
        printf(GRN "%s \n\n\n\n" reset,rooms[cloc].description);
    }
    else {
        printf("%s \n\n\n\n",rooms[cloc].description);
    }
    printf("Available directions: ");
    if (rooms[cloc].go_north > 0) printf("NORTH ");
    if (rooms[cloc].go_east  > 0) printf("EAST ");
    if (rooms[cloc].go_south > 0) printf("SOUTH ");
    if (rooms[cloc].go_west  > 0) printf("WEST ");
    printf("\n\n");
    if (DBG_MODE == 1) {
        printf("\nroom number: %d\n",rooms[cloc].id);
        printf("  Invisible: %d\n\n",invisible);
    }
    return 0;
}

int read_command(){
    printf("What to do? \n\n > ");
    fgets(command,12,stdin);
    char *p = strchr(command, '\n');
    if (p) *p = 0;
    return 0;
}

int explore_dungeon(){
    int cloc = get_location_by_id(current_location);
    int battle_result = 0;
    int previous_location = 0;
    while (current_location != 22 && qresult != 0 && game_mode == 2) {
        clear_screen();
        if(rooms[cloc].is_enemy == 1 && invisible == 0){
            battle_result = play_battle(current_location);
            if (battle_result == 1) rooms[cloc].is_enemy = 0;
            if (battle_result == 2) {
                current_location = previous_location;
                }
        }
        display_current_location(current_location);
        read_command();
        qresult = compareST(command, "quit");
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