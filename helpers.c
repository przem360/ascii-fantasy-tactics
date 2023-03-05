#include<stdio.h>

void print_screen(void);
void place_figures(void);
void draw_range(char id[4],int radius);

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
}