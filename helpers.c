#include <stdio.h>
#include <string.h>
#include "converters.c"
#include <stdlib.h>

char selected_fighter[] = "kk";

void print_screen(void);
void place_figures(void);
void draw_range(char id[4],int radius);
void clear_screen(void);
void draw_info_panel(void);
void draw_interface(void);
void cleanip(void);
void printip(char txt[20], int line_number);
char analyse_command(char comm[6]);
int  dice(int maxv);
void print_to_side_panel(void);

int side_panel_size = sizeof(side_panel)/sizeof(side_panel[0]);


void clear_screen(void){
    system("clear"); //*nix
    // system("cls"); //windows
}

void print_screen() {
    int elems = sizeof(screen)/sizeof(screen[0]);
    int rows = sizeof(screen[0]); // this is not rows, it's collumns!
    int i,y,z;
    print_to_side_panel();
    for (i=0; i<elems; i++){
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
    int i,y;
    for (i=0; i<elems; i++){
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
    for (i=0; i<letters; i++){
        info_panel[line_number][i+1] = txt[i];
    }
}

void draw_interface(){
    print_screen();
    draw_info_panel();
}

void place_figures(){
    int i;
    for (i=0;i<4;i++){
        screen[pcs[i].x_position][pcs[i].y_position] = *pcs[i].letter;
        screen[monsters[i].x_position][monsters[i].y_position] = *monsters[i].letter;
    }
}

void draw_range(char id[3],int radius){
    /* Function draws range for walking, shooting, spells.
       Arguments: id - adress of figure that needs range specification (center point of range),
                       in form of chess coordinates (i.e. F20),
                       or letter.
        Function will analyse id and decide if it is an adress or a single letter.
        If it is a letter needs to check if it is unique and find the adress.
    */
    /* First we'll convert adress command to coordinates */
    int command_size = strlen(id);
    int address_x;
    int address_y;
    if (command_size>1){
        address_x = letters_to_numbers(id[0]);
        char* substr = id + 1;
        address_y = string_to_number(substr);
        // printf("ADDRESS X: %d \n", address_x);
        // printf("ADDRESS Y: %d \n", address_y);
    }
    /* Let's try to draw on screen from coordinates */
    /* drawing straight front and back */
    int i, rad;
    // if (screen[address_y][address_x] == '.'){
    //         screen[address_y][address_x] = '@';
    //     }
    for (rad=radius;rad>=0;rad--){
    for(i=0;i<=radius;i++) {
        if (screen[address_y-i][address_x] == '.'){
            screen[address_y-i][address_x] = '+';
        }
        if (screen[address_y+i][address_x] == '.'){
            screen[address_y+i][address_x] = '+';
        }
    }
    /* drawing radius to the right side */
    /* up */
    for(i=0;i<=rad;i++) {
        if (screen[address_y-i][address_x-rad+radius] == '.'){
            screen[address_y-i][address_x-rad+radius] = '+';
        }
        /* down */
        if (screen[address_y-i+rad][address_x-rad+radius] == '.'){
            screen[address_y-i+rad][address_x-rad+radius] = '+';
        }
    }
    }
    /* drawing radius to the left side */
    // for (rad=0,side_step=0;rad<=radius,side_step<radius;rad++,side_step++){
    for (rad=0;rad<radius;rad++){
        /* down */
        for(i=radius;i>0;i--){
            if (screen[address_y+rad][address_x-i+rad] == '.'){
                screen[address_y+rad][address_x-i+rad] = '+';
            }
            /* up */
            if (screen[address_y-rad][address_x-i+rad] == '.'){
                screen[address_y-rad][address_x-i+rad] = '+';
            }
        }
    }
}

char analyse_command(char comm[12]) {
    int i;
    char *comml = strtolower(comm, 12);
    if (startswith("knock knock",comml)) {
        cleanip();
        printip("Whos there?",1);
    }
    if ((strlen(comml) == 1)&&(comml[0] == 'q')){
        return 'q';
    }
    for (i=0;i<amount_of_fighters;i++){
        if(startswith(pcs[i].id,comml) != 0){
            cleanip();
            printip("Selected new",1);
            selected_fighter[0] = comml[0];
            selected_fighter[1] = comml[1];
        }
    }
    return 'K';
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
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = *pcs[i].letter;
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ']';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ' ';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = '[';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = pcs[i].id[0];
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = pcs[i].id[1];
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ']';
        in_line_position++;
        side_panel[i+free_lines+amount_of_monsters][in_line_position] = ' ';
        in_line_position++;
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