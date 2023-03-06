#include <stdio.h>
#include <string.h>
#include "converters.c"
#include <stdlib.h>

void print_screen(void);
void place_figures(void);
void draw_range(char id[4],int radius);
void clear_screen(void);

void clear_screen(void){
    system("clear"); //*nix
    // system("cls"); //windows
}

void print_screen() {
    int elems = sizeof(screen)/sizeof(screen[0]);
    int rows= sizeof(screen[0]);
    printf("\n > Screen has %d elements in %d rows. \n",elems,rows);
    int i,y;
    for (i=0; i<elems; i++){
        for (y=0;y<rows; y++){
            printf("%c",screen[i][y]);
        }
        printf("\n");
    }
    printf("i: %d, y: %d \n",i,y);
}

void place_figures(){
    int i;
    for (i=0;i<2;i++){
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
    if (screen[address_y][address_x] == '.'){
            screen[address_y][address_x] = '@';
        }
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