#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  /* for seeding rand() with time */
#include <ctype.h> /* for checking if char is a letter or a number */
#include <string.h>
#include "converters.h"

int coords[2];

void adresstocoords(char addr[3]){
    int command_size = strlen(addr);
    if (command_size>1){
        coords[1] = letters_to_numbers(addr[0]);
        char* substr = addr + 1;
        coords[0] = string_to_number(substr);
    }
}

int letters_to_numbers(char letter) {
    int number;
    number = 0;
    switch(letter) {
            case 'A' :
            case 'a' :
                number = 1;
            break;
            case 'B' :
            case 'b' :
                number = 2;
            break;
            case 'C' :
            case 'c' :
                number = 3;
            break;
            case 'D' :
            case 'd' :
                number = 4;
            break;
            case 'E' :
            case 'e' :
                number = 5;
            break;
            case 'F' :
            case 'f' :
                number = 6;
            break;
            case 'G' :
            case 'g' :
                number = 7;
            break;
            case 'H' :
            case 'h' :
                number = 8;
            break;
            case 'I' :
            case 'i' :
                number = 9;
            break;
            case 'J' :
            case 'j' :
                number = 10;
            break;
            case 'K' :
            case 'k' :
                number = 11;
            break;
            case 'L' :
            case 'l' :
                number = 12;
            break;
            case 'M' :
            case 'm' :
                number = 13;
            break;
            case 'N' :
            case 'n' :
                number = 14;
            break;
            case 'O' :
            case 'o' :
                number = 15;
            break;
            case 'P' :
            case 'p' :
                number = 16;
            break;
            case 'Q' :
            case 'q' :
                number = 17;
            break;
            case 'R' :
            case 'r' :
                number = 18;
            break;
            case 'S' :
            case 's' :
                number = 19;
            break;
            case 'T' :
            case 't' :
                number = 20;
            break;
            case 'U' :
            case 'u' :
                number = 21;
            break;
            case 'V' :
            case 'v' :
                number = 22;
            break;
            case 'W' :
            case 'w' :
                number = 23;
            break;
            case 'X' :
            case 'x' :
                number = 24;
            break;
            case 'Y' :
            case 'y' :
                number = 25;
            break;
            case 'Z' :
            case 'z' :
                number = 26;
            break;
        }
    return number;
}

int string_to_number(char* str){
    int num = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        num = num * 10 + (str[i] - 48);
    }
    return num;
}

// const char* strtolower(char *str) {
//   for(int i = 0; str[i]; i++){
//       str[i] = tolower(str[i]);
//   }
//   return str;
// }

char *strtolower(char *str, int len)
{
    char *str_l = calloc(len+1, sizeof(char));
    for (size_t i = 0; i < len; ++i) {
        str_l[i] = tolower((unsigned char)str[i]);
    }
    return str_l;
}

int startswith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

void shuffle(int *array, int n) {
    srand(time(0));
    int i;
    for (i=0;i<n-1;i++) {
        int j = i+rand() / (RAND_MAX/(n-1)+1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

int numcmp(int i, int j) {
    int diff = 0;
    if (i>j) diff = i - j;
    if (i<j) diff = j - i;
    if (i==j) diff = i;
    return diff;
}

int validate_coords(char coords[3]) {

    int is_1st_position_a_letter = 0;
    int is_2nd_position_a_number = 0;

    if (isalpha(coords[0])) {
        is_1st_position_a_letter = 1;
    } else {
        is_1st_position_a_letter = 0;
    }

    if (isdigit(coords[1])) {
        is_2nd_position_a_number = 1;
    } else {
        is_2nd_position_a_number = 0;
    }

    if ((is_1st_position_a_letter == 1)&&(is_2nd_position_a_number == 1)) {
        return 1;
    }
    else {
        printf("\nERROR: type coords in correct format: letter followed by number, i.e.: A1\n");
        return 0;   
    }
}