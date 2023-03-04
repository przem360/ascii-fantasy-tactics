#include<stdio.h>

void print_screen(void);
void place_figures(void);

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
    screen[character1.x_position][character1.y_position] = *character1.letter;
    screen[character2.x_position][character2.y_position] = *character2.letter;
    screen[enemy1.x_position][enemy1.y_position] = *enemy1.letter;
    screen[enemy2.x_position][enemy2.y_position] = *enemy2.letter;
}