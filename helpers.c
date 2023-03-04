#include<stdio.h>

void print_screen(void);

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