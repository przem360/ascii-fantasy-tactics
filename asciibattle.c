#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* for pausing on POSIX */
// #include <dos.h> /* for pausing on Windows */
#include "converters.c"
#include "defs.h"


void print_screen(void);
void place_figures(void);
void draw_range(int xpos, int ypos,int radius, char mode);
void clear_range(char mode);
void clear_screen(void);
void draw_info_panel(void);
void draw_interface(void);
void cleanip(void);
void printip(char txt[20], int line_number);
char analyse_command(char comm[6]);
void print_to_side_panel(void);
void ascii_battle_init(void);
int player_action_move(char pid[2]);
// void move_cursor(int cx, int cy);
int move_fighter(int number_in_array, char letter, int fx, int fy, char target[3]);
void let_move(void);
void monsters_action(void);


int  dice(int maxv);


int side_panel_size = sizeof(side_panel)/sizeof(side_panel[0]);
char current_command[8];
char selected_fighter[] = "nn";
char selected_monster[] = "nn";
char output[1];
int whoseturn = 1; /* Initiative selection */
int player_or_monster = 1; /* 1 = player, 2 = monster */

// int cursor_on = 1;
const char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


void clear_screen(void){
    system("clear"); //*nix
    // system("cls"); //windows
}

void print_screen() {
    int elems = sizeof(screen)/sizeof(screen[0]);
    int rows = sizeof(screen[0]); // this is not rows, it's collumns!
    int i,y,z,nums,spaces,l;
    nums = 1;
    /* print alphabet letters */
    for (spaces=0;spaces<4;spaces++){
                printf(" ");
            }
    for(l=0;l<rows-2;l++){
        printf("%c",alphabet[l]);
    }
    printf("\n");

    print_to_side_panel();
    for (i=0; i<elems; i++){
        if ((nums!=1)&&(nums!=elems)){
            printf("%2d ",nums-1);
        }
        else {
            for (spaces=0;spaces<3;spaces++){
                printf(" ");
            }
        }
        nums++;
        for (y=0;y<rows; y++){
            printf("%c",screen[i][y]);
        }
        if (i<side_panel_size){
            // printf(" test ");
            for(z=0;z<sizeof(side_panel[0]);z++){
                printf("%c",side_panel[i][z]);
            }
        }
        printf("\n");
    }
}
void draw_info_panel(){
    int elems = sizeof(info_panel)/sizeof(info_panel[0]);
    int cols = sizeof(info_panel[0]);
    int i,y,spaces;
    for (i=0; i<elems; i++){
        for (spaces=0;spaces<3;spaces++){
                printf(" ");
            }
        for (y=0;y<cols; y++){
            printf("%c",info_panel[i][y]);
        }
        printf("\n");
    }
}

void cleanip(){
    int info_panel_size = sizeof(info_panel) / sizeof(info_panel[0]);
    int ip_line_size = sizeof(info_panel[0]);
    int i,y;
    for (i=1;i<info_panel_size;i++) {
        for (y=1;y<ip_line_size-1;y++) {
            info_panel[i][y] = ' ';
        }
    }
}

void printip(char txt[20], int line_number){
    int letters = strlen(txt);
    int i;
    cleanip();
    for (i=0; i<letters; i++){
        info_panel[line_number][i+1] = txt[i];
    }
}

void draw_interface(){
    clear_screen();
    printf("\t\tASCII FANTASY TACTICS \n\n");
    print_screen();
    draw_info_panel();
}

void place_figures(){
    int i;
    for (i=0;i<4;i++){
        screen[pcs[i].x_position][pcs[i].y_position] = pcs[i].letter;
        screen[monsters[i].x_position][monsters[i].y_position] = *monsters[i].letter;
    }
}

void clear_range(char mode){
    int i,y;
    int lines = sizeof(screen)/sizeof(screen[0]);
    int chars = sizeof(screen[0]); 
    if (mode == 'm'){
        for(i=0;i<lines;i++){
            for(y=0;y<chars;y++){
                if (screen[i][y] == RANGE_CHAR){
                    screen[i][y] =  BASE_CHAR;
                }
            }
        }
    }
}

void draw_range(int xpos, int ypos, int radius, char mode){
    /* Function draws range for walking, shooting, spells.
       Arguments: id - adress of figure that needs range specification (center point of range),
                       in form of chess coordinates (i.e. F20),
                       or letter.
        Function will analyse id and decide if it is an adress or a single letter.
        If it is a letter needs to check if it is unique and find the adress.
    */
    /* First we'll convert adress command to coordinates */
    // adresstocoords(id);
    int address_x = xpos;
    int address_y = ypos;
    /* Let's try to draw on screen from coordinates */
    /* drawing straight front and back */
    int i, rad;
    // if (screen[address_y][address_x] == '.'){
    //         screen[address_y][address_x] = '@';
    //     }

    if (mode == 'm') {
    for (rad=radius;rad>=0;rad--){
    for(i=0;i<=radius;i++) {
        if (screen[address_y-i][address_x] == BASE_CHAR){
            screen[address_y-i][address_x] = RANGE_CHAR;
        }
        if (screen[address_y+i][address_x] == BASE_CHAR){
            screen[address_y+i][address_x] = RANGE_CHAR;
        }
    }
    /* drawing radius to the right side */
    /* up */
    for(i=0;i<=rad;i++) {
        if (screen[address_y-i][address_x-rad+radius] == BASE_CHAR){
            screen[address_y-i][address_x-rad+radius] = RANGE_CHAR;
        }
        /* down */
        if (screen[address_y-i+rad][address_x-rad+radius] == BASE_CHAR){
            screen[address_y-i+rad][address_x-rad+radius] = RANGE_CHAR;
        }
    }
    }
    /* drawing radius to the left side */
    // for (rad=0,side_step=0;rad<=radius,side_step<radius;rad++,side_step++){
    for (rad=0;rad<radius;rad++){
        /* down */
        for(i=radius;i>0;i--){
            if (screen[address_y+rad][address_x-i+rad] == BASE_CHAR){
                screen[address_y+rad][address_x-i+rad] = RANGE_CHAR;
            }
            /* up */
            if (screen[address_y-rad][address_x-i+rad] == BASE_CHAR){
                screen[address_y-rad][address_x-i+rad] = RANGE_CHAR;
            }
        }
    }
    } /* end if(mode=='m')*/

}

char analyse_command(char comm[12]) {
    int y;
    char *comml = strtolower(comm, 12);
    int amount_of_available_commands = sizeof(av_commands) / sizeof(av_commands[0]);
    // selected_fighter[0] = 'n'; /* lets remove what ever is left in select_fighter */
    // selected_fighter[1] = 'n'; /* to make sure that selection actually took place */
    if (startswith("knock knock",comml)) {
        cleanip();
        printip("Whos there?",1);
        return 'k';
    }
    if ((strlen(comml) < 3)&&(comml[0] == 'q')){
        return 'q';
    }
    for (y=0;y<amount_of_available_commands;y++){
        if(strcmp(av_commands[y], comml)){
            cleanip();
            printip("Command found!",1);
            /* make it return the letter of command*/
            return comml[0];
        }   
    }
    return 'k';
    }

int  dice(int maxv) {
    int lower = 1;
    int upper = maxv;
    int rnum;
    rnum = (rand() % (upper-lower+1))+lower;
    return rnum;
}

void print_to_side_panel(){
    int i, y, free_lines,word_lenght,in_line_position;
    char monster_hp_string[3];
    char fighter_hp_string[3];
    free_lines = (side_panel_size - amount_of_monsters) - amount_of_fighters;
    // for(i=0;i<amount_of_monsters;i++){
    //     cx = snprintf(mbuff[i],30,"[%c] [%s] %s (%s) HP: %d",monsters[i].letter,monsters[i].id,monsters[i].name,monsters[i].race,monsters[i].hp);
    // }
    for(i=0;i<amount_of_monsters;i++){
        snprintf(monster_hp_string,3,"%d",monsters[i].hp);
        in_line_position = 3;
        if((selected_monster[0] == monsters[i].id[0])&&(selected_monster[1] == monsters[i].id[1])){
            side_panel[i][1] = '>';
        } else {
            side_panel[i][1] = ' ';
        }
        side_panel[i][in_line_position] = '[';
        in_line_position++;
        side_panel[i][in_line_position] = *monsters[i].letter;
        in_line_position++;
        side_panel[i][in_line_position] = ']';
        in_line_position++;
        side_panel[i][in_line_position] = ' ';
        in_line_position++;
        // side_panel[i][in_line_position] = '[';
        // in_line_position++;
        // side_panel[i][in_line_position] = monsters[i].id[0];
        // in_line_position++;
        // side_panel[i][in_line_position] = monsters[i].id[1];
        // in_line_position++;
        // side_panel[i][in_line_position] = ']';
        // in_line_position++;
        // side_panel[i][in_line_position] = ' ';
        // in_line_position++;
        word_lenght = strlen(monsters[i].name);
        for(y=0;y<word_lenght;y++){
            side_panel[i][in_line_position+y] = monsters[i].name[y];
        }
        in_line_position = in_line_position + y;
        side_panel[i][in_line_position] = ' ';
        in_line_position++;
        side_panel[i][in_line_position] = '(';
        in_line_position++;
        word_lenght = strlen(monsters[i].race);
        for(y=0;y<word_lenght;y++){
            side_panel[i][in_line_position+y] = monsters[i].race[y];
        }
        in_line_position = in_line_position + y;
        side_panel[i][in_line_position] = ')';
        in_line_position++;
        side_panel[i][in_line_position] = ' ';
        in_line_position++;
        side_panel[i][in_line_position] = 'H';
        in_line_position++;
        side_panel[i][in_line_position] = 'P';
        in_line_position++;
        side_panel[i][in_line_position] = ':';
        in_line_position++;
        word_lenght = strlen(monster_hp_string);
        for(y=0;y<word_lenght;y++){
            side_panel[i][in_line_position+y] = monster_hp_string[y];
        }
    }
    for(i=0;i<amount_of_fighters;i++){
        snprintf(fighter_hp_string,3,"%d",pcs[i].hp);
        in_line_position = 3;
        if((selected_fighter[0] == pcs[i].id[0])&&(selected_fighter[1] == pcs[i].id[1])){
            side_panel[i+free_lines+amount_of_monsters][1] = '>';
        } else {
            side_panel[i+free_lines+amount_of_monsters][1] = ' ';
        }
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = '[';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = pcs[i].letter;
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ']';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ' ';
        in_line_position++;
        // side_panel[i+free_lines+amount_of_monsters][in_line_position] = '[';
        // in_line_position++;
        // side_panel[i+free_lines+amount_of_monsters][in_line_position] = pcs[i].id[0];
        // in_line_position++;
        // side_panel[i+free_lines+amount_of_monsters][in_line_position] = pcs[i].id[1];
        // in_line_position++;
        // side_panel[i+free_lines+amount_of_monsters][in_line_position] = ']';
        // in_line_position++;
        // side_panel[i+free_lines+amount_of_monsters][in_line_position] = ' ';
        // in_line_position++;
        word_lenght = strlen(pcs[i].name);
        for(y=0;y<word_lenght;y++){
            side_panel[i+free_lines+amount_of_monsters][in_line_position+y] = pcs[i].name[y];
        }
        in_line_position = in_line_position + y;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ' ';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = '(';
        in_line_position++;
        word_lenght = strlen(pcs[i].pc_class);
        for(y=0;y<word_lenght;y++){
            side_panel[i+free_lines+amount_of_monsters][in_line_position+y] = pcs[i].pc_class[y];
        }
        in_line_position = in_line_position + y;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ')';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ' ';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = 'H';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = 'P';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ':';
        in_line_position++;
        word_lenght = strlen(fighter_hp_string);
        for(y=0;y<word_lenght;y++){
            side_panel[i+free_lines+amount_of_monsters][in_line_position+y] = fighter_hp_string[y];
        }
    }
}
void ascii_battle_init() {
    memcpy(screen, lvl1,sizeof(lvl1));
    draw_interface();
}

// void move_cursor(int cx, int cy){
//     /* Let's forget about it, since imidiete getchar() response
//     (without the need to hit enter) is not really a standard and
//     it is not really portable.
//     We would have to use ncurses for that. */
//     printip("Move Cursor");
//     int keypress;
// }

int move_fighter(int number_in_array, char letter, int fx, int fy, char target[3]){
    adresstocoords(target);
    /* make move */
    screen[fx][fy] = BASE_CHAR;
    if (screen[coords[0]][coords[1]] == RANGE_CHAR){
        // screen[coords[0]][coords[1]] = letter;
        pcs[number_in_array].x_position = coords[0];
        pcs[number_in_array].y_position = coords[1];
        clear_range('m');
        printip("Moved.",1);
        return 1;
    }
    else{
        printip("Can\'t move",1);
        clear_range('m');
        pcs[number_in_array].x_position = fx;
        pcs[number_in_array].y_position = fy;
        draw_interface();
        return 0;
    }
}

int player_action_move(char pid[2]){
    int i, selected_x, selected_y, rad, arrnum, mv;
    mv = 0;
    char fighter_letter;
    char addr[3];
    for(i=0;i<amount_of_fighters;i++){
        if (pcs[i].id[0] == pid[0] && pcs[i].id[1] == pid[1]){
            selected_x = pcs[i].x_position;
            selected_y = pcs[i].y_position;
            fighter_letter = pcs[i].letter;
            rad = pcs[i].mov / 10;
            arrnum = i;
            printip("Specify adress...",1);
            draw_range(selected_y,selected_x,rad,'m');
        }
    }
    draw_interface();
    scanf("%s",addr);
    mv = move_fighter(arrnum,fighter_letter,selected_x,selected_y,addr);
    draw_interface();
    return mv;
}

void let_move(){
    int i;
    for (i=0;i<amount_of_fighters;i++){
        if (pcs[i].initiative == whoseturn){
            selected_fighter[0] = pcs[i].id[0];
            selected_fighter[1] = pcs[i].id[1]; 
            player_or_monster = 1;
            printip("Player\'s turn",1);
        }
    }
    for (i=0;i<amount_of_monsters;i++){
        if (monsters[i].initiative == whoseturn){
            selected_monster[0] = monsters[i].id[0];
            selected_monster[1] = monsters[i].id[1]; 
            player_or_monster = 2;
            printip("Monster\'s turn",1);
        }
    }
}

void monsters_action(){
    printip("I\'ll skip",1);
    whoseturn++;
}