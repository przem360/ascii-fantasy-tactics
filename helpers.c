#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "helpers.h"
#include "settings.h"
#include "colors.h"
#define LOGFILE "aft.log"
#if !defined(SYSTEM)
#define SYSTEM "LIN" 
#endif

int var_log(const char *format, ...) {
    if (log_on == 0) { return 0; }
    va_list valist;
    char *filename = LOGFILE;

    va_start(valist, format);
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }

    fprintf(fp,"\n");

    while (*format != '\0') {
        switch (*format++){
            case 's':
                fprintf(fp, "%s ", va_arg(valist, const char *));
                break;
            case 'd':
                fprintf(fp, "%d ", va_arg(valist, int));
                break;
            case 'f':
                fprintf(fp, "%f ", va_arg(valist, double));
                break;
        }
    }
    fclose(fp);
    va_end(valist);
    return 0;
}


int clean_log(void) {
    return remove(LOGFILE);
}

void clear_screen(void){
    if (DBG_MODE == 0){
        if ((strcmp("DOS",SYSTEM) != 0)&&(strcmp("WIN",SYSTEM) != 0)) { /* clear screen for non-M$ systems */
            printf("\033[1;1H\033[2J");
            system("clear");
        } // 0 when strings are equal
        else {
            printf("\033[1;1H\033[2J");
            system("cls");
        }
    }
    else {
        // dummy:
        int i,l;
        l = 50;
        for (i=0;i<l;i++){
             printf("\n");
        }
    }
}
void wprint(char desc[], int width, int use_colors){
    int i = 0;
    int total_lenght = strlen(desc);
    if (width > 0) {
        desc[strcspn(desc, "\r\n")] = 0;
        while (i < total_lenght){
            if (use_colors>0){
                printf(DSC "%c" reset, desc[i++]);
                if (i % width == 0) {printf("\n");}
            }
            else {
                printf("%c", desc[i++]);
                if (i % width == 0) {printf("\n");}
            }
        }
        printf("\n\n");
    }
    else {
        if (use_colors>0) printf(DSC "%s \n\n" reset,desc);
        else printf("%s \n\n",desc);
    }
}
