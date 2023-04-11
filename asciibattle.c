#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* for pausing on POSIX */
// #include <dos.h> /* for pausing on Windows */
#include <time.h> /* for seeding rand() with time */
#include "converters.c"

int get_array_index(char type, char id[2]);
void print_screen(void);
void place_figures(void);
void draw_range(int xpos, int ypos,int radius, char mode);
void draw_monster_range(int xpos, int ypos,int radius);
// void draw_white_magic_range(int xpos, int ypos,int radius);
void chase_figters(int mnstr, int fightr);
void clear_range();
void clear_screen(void);
void draw_info_panel(void);
void draw_interface(void);
void cleanip(void);
void printip(char txt[20], int line_number);
char analyse_command(char comm[6]);
void clean_side_panel(void);
void print_to_side_panel(void);
int ask_spells(char pid[2]);
void ascii_battle_init(void);
int player_action_move(char pid[2]);
int player_action_cast(char pid[2]);
int player_action_attack(char pid[2]);
// void move_cursor(int cx, int cy);
int resolve_spell(char pid[2],char taddr[3],char sid[2]);
int resolve_attack(char pid[2],char taddr[3]);
int resolve_monster_attack(int mnst,int figh);
int move_fighter(int number_in_array, char letter, int fx, int fy, char target[3]);
int let_move(void);
void monsters_action(void);
int ai_choose_action(char mid[2]);
int dice(int maxv);
void info_screen(void);


int side_panel_size = sizeof(side_panel)/sizeof(side_panel[0]);
char current_command[8];
char selected_fighter[] = "nn";
char selected_monster[] = "nn";
char output[1];
int whoseturn = 1; /* Initiative selection */
int player_or_monster = 1; /* 1 = player, 2 = monster */
int targets[] = {0,1,2,3};

// int cursor_on = 1;
const char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int killed = 0; /* how many monsters were killed by fighters */
int died = 0;   /* how many fighters were killed by monsters */

int get_array_index(char type, char id[2]){
    int i;
    if (type == 'm') {
        for (i=0;i<amount_of_monsters;i++){
            if ((monsters[i].id[0]==id[0])&&(monsters[i].id[1]==id[1])) {
                return i;
            }
        }
    }
    if (type == 'f') {
        for (i=0;i<amount_of_fighters;i++){
            if ((pcs[i].id[0]==id[0])&&(pcs[i].id[1]==id[1])){
                return i;
            }
        }
    }
    return 0;
}

void clear_screen(void){
    // system("clear"); //*nix
    // system("cls"); //windows
    // dummy:
    int i,l;
    l = 50;
    for (i=0;i<l;i++){
        printf("\n");
    }
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
    for (i=0;i<info_panel_size;i++) {
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
    int i, pxp, pyp, mxp, myp;
    pxp = 0;
    pyp = 0;
    mxp = 0;
    myp = 0;
    for (i=0;i<amount_of_fighters;i++){
        pxp = pcs[i].x_position;
        pyp = pcs[i].y_position;
        printf("pxp: %d pyp: %d \n",pxp,pyp);
        // if ((pxp>=0)&&(pyp>=0)) {
            if (screen[pxp][pyp] != TARGET_CHAR){
                screen[pxp][pyp] = pcs[i].letter;
            }
        // }
    }
    for (i=0; i<amount_of_monsters;i++) {
        mxp = monsters[i].x_position;
        myp = monsters[i].y_position;
        printf("mxp: %d myp: %d \n",mxp,myp);
        if ((mxp>=0)&&(myp>=0)&&(mxp<14)&&(myp<22)) {
            if(screen[mxp][myp] != TARGET_CHAR){
            screen[mxp][myp] = monsters[i].letter;
            }
        }
    }
}

void clear_range(){
    int i,y;
    int lines = sizeof(screen)/sizeof(screen[0]);
    int chars = sizeof(screen[0]); 
    for(i=0;i<lines;i++){
        for(y=0;y<chars;y++){
            if (screen[i][y] == RANGE_CHAR){
                screen[i][y] =  BASE_CHAR;
            }
            /* have to remove target marks before placing figures */
            if (screen[i][y] == TARGET_CHAR){
                screen[i][y] =  BASE_CHAR;
            }
        }
    }
    place_figures();
}

void draw_range(int xpos, int ypos, int radius, char mode){
    // adresstocoords(id);
    int address_x = xpos;
    int address_y = ypos;
    int i, rad, m;
    clear_range();
    if (mode == 'm') {
    for (rad=radius;rad>=0;rad--){
    for(i=0;i<=radius;i++) {
        if((address_y-i)>=0){
            if (screen[address_y-i][address_x] == BASE_CHAR){
                screen[address_y-i][address_x] = RANGE_CHAR;
            }
        }
        if((address_y+i)<=SCREEN_HEIGHT){
            if (screen[address_y+i][address_x] == BASE_CHAR){
                screen[address_y+i][address_x] = RANGE_CHAR;
            }
        }
    }
    /* drawing radius to the right side */
    /* up */
    for(i=0;i<=rad;i++) {
        if((address_y-i)>=0 && (address_x-rad+radius)>=0 && (address_x-rad+radius)<=SCREEN_WIDTH){
            if (screen[address_y-i][address_x-rad+radius] == BASE_CHAR){
                screen[address_y-i][address_x-rad+radius] = RANGE_CHAR;
            }
        }
        if((address_y-i)>=0 && (address_y-i)<=SCREEN_HEIGHT && (address_x-rad+radius)>=0 && (address_x-rad+radius)<=SCREEN_WIDTH){
            /* down */
            if (screen[address_y-i+rad][address_x-rad+radius] == BASE_CHAR){
                screen[address_y-i+rad][address_x-rad+radius] = RANGE_CHAR;
            }
        }
    }
    }
    /* drawing radius to the left side */
    // for (rad=0,side_step=0;rad<=radius,side_step<radius;rad++,side_step++){
    for (rad=0;rad<radius;rad++){
        /* down */
        for(i=radius;i>0;i--){
            if((address_x-i+rad)>=0){
                if (screen[address_y+rad][address_x-i+rad] == BASE_CHAR && (rad-i<0)){
                    screen[address_y+rad][address_x-i+rad] = RANGE_CHAR;
                }
            }
                /* up */
            if((address_x-i+rad)>=0){
                if (screen[address_y-rad][address_x-i+rad] == BASE_CHAR && (rad-i<0)){
                    screen[address_y-rad][address_x-i+rad] = RANGE_CHAR;
                }
            }
        }
    }
    } /* end if(mode=='m')*/
    if (mode == 'c') {
    for (rad=radius;rad>=0;rad--){
    for(i=0;i<=radius;i++) {
        if (screen[address_y-i][address_x] == BASE_CHAR){
            screen[address_y-i][address_x] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_monsters;m++){
                if ((screen[address_y-i][address_x] == monsters[m].letter)&&(monsters[m].letter != DEAD_BODY_CHAR)){
                    screen[address_y-i][address_x] = TARGET_CHAR;
                }
            }
        }
        if (screen[address_y+i][address_x] == BASE_CHAR){
            screen[address_y+i][address_x] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_monsters;m++){
                if ((screen[address_y+i][address_x] == monsters[m].letter)&&(monsters[m].letter != DEAD_BODY_CHAR)){
                    screen[address_y+i][address_x] = TARGET_CHAR;
                }
            }
        }
    }
    /* drawing radius to the right side */
    /* up */
    for(i=0;i<=rad;i++) {
        if (screen[address_y-i][address_x-rad+radius] == BASE_CHAR){
            screen[address_y-i][address_x-rad+radius] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_monsters;m++){
                if ((screen[address_y-i][address_x-rad+radius] == monsters[m].letter)&&(monsters[m].letter != DEAD_BODY_CHAR)){
                    screen[address_y-i][address_x-rad+radius] = TARGET_CHAR;
                }
            }
        }
        /* down */
        if (screen[address_y-i+rad][address_x-rad+radius] == BASE_CHAR){
            screen[address_y-i+rad][address_x-rad+radius] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_monsters;m++){
                if ((screen[address_y-i+rad][address_x-rad+radius] == monsters[m].letter)&&(monsters[m].letter != DEAD_BODY_CHAR)){
                    screen[address_y-i+rad][address_x-rad+radius] = TARGET_CHAR;
                }
            }
        }
    }
    }
    /* drawing radius to the left side */
    // for (rad=0,side_step=0;rad<=radius,side_step<radius;rad++,side_step++){
    for (rad=0;rad<radius;rad++){
        /* down */
        for(i=radius;i>0;i--){
            if((address_x-i+rad)>=0){
                if (screen[address_y+rad][address_x-i+rad] == BASE_CHAR && (rad-i<0)){
                    screen[address_y+rad][address_x-i+rad] = RANGE_CHAR;
                }
                else {
                for (m=0;m<amount_of_monsters;m++){
                    if (screen[address_y+rad][address_x-i+rad] == monsters[m].letter && (monsters[m].letter != DEAD_BODY_CHAR) && (rad-i<0)){
                        screen[address_y+rad][address_x-i+rad] = TARGET_CHAR;
                    }
                }
                }
            }
            /* up */
            if((address_x-i+rad)>=0){
                if (screen[address_y-rad][address_x-i+rad] == BASE_CHAR && (rad-i<0)){
                    screen[address_y-rad][address_x-i+rad] = RANGE_CHAR;
                } else {
                for (m=0;m<amount_of_monsters;m++){
                    if (screen[address_y-rad][address_x-i+rad] == monsters[m].letter && (monsters[m].letter != DEAD_BODY_CHAR) && (rad-i<0)){
                        screen[address_y-rad][address_x-i+rad] = TARGET_CHAR;
                    }
                }
                }
            }
        }
    }
    } /* end if((mode=='a')||(mode=='c'))*/
}

void draw_monster_range(int xpos, int ypos,int radius) {
    int i, rad, m;
    /* lest flip x and y values just for test */
    clear_range();
    for (rad=radius;rad>=0;rad--){
    for(i=0;i<=radius;i++) {
        printf("ypos-i: %d",ypos-i);
        if (screen[ypos-i][xpos] == BASE_CHAR){
            screen[ypos-i][xpos] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_fighters;m++){
                if ((screen[ypos-i][xpos] == pcs[m].letter)&&(pcs[m].letter != DEAD_BODY_CHAR)){
                    screen[ypos-i][xpos] = TARGET_CHAR;
                }
            }
        }
        if (screen[ypos+i][xpos] == BASE_CHAR){
            screen[ypos+i][xpos] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_monsters;m++){
                if ((screen[ypos+i][xpos] == pcs[m].letter)&&(pcs[m].letter != DEAD_BODY_CHAR)){
                    screen[ypos+i][xpos] = TARGET_CHAR;
                }
            }
        }
    }
    /* drawing radius to the right side */
    /* up */
    for(i=0;i<=rad;i++) {
        if (screen[ypos-i][xpos-rad+radius] == BASE_CHAR){
            screen[ypos-i][xpos-rad+radius] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_monsters;m++){
                if ((screen[ypos-i][xpos-rad+radius] == pcs[m].letter)&&(pcs[m].letter != DEAD_BODY_CHAR)){
                    screen[ypos-i][xpos-rad+radius] = TARGET_CHAR;
                }
            }
        }
        /* down */
        if (screen[ypos-i+rad][xpos-rad+radius] == BASE_CHAR){
            screen[ypos-i+rad][xpos-rad+radius] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_monsters;m++){
                if ((screen[ypos-i+rad][xpos-rad+radius] == pcs[m].letter)&&(pcs[m].letter != DEAD_BODY_CHAR)){
                    screen[ypos-i+rad][xpos-rad+radius] = TARGET_CHAR;
                }
            }
        }
    }
    }
    /* drawing radius to the left side */
    // for (rad=0,side_step=0;rad<=radius,side_step<radius;rad++,side_step++){
    for (rad=0;rad<radius;rad++){
        /* down */
        for(i=radius;i>0;i--){
            if((xpos-i+rad)>=0){
                if (screen[ypos+rad][xpos-i+rad] == BASE_CHAR && (rad-i<0)){
                    screen[ypos+rad][xpos-i+rad] = RANGE_CHAR;
                }
                else {
                for (m=0;m<amount_of_monsters;m++){
                    if (screen[ypos+rad][xpos-i+rad] == pcs[m].letter && (pcs[m].letter != DEAD_BODY_CHAR) && (rad-i<0)){
                        screen[ypos+rad][xpos-i+rad] = TARGET_CHAR;
                    }
                }
                }
            }
            /* up */
            if((xpos-i+rad)>=0){
                if (screen[ypos-rad][xpos-i+rad] == BASE_CHAR && (rad-i<0)){
                    screen[ypos-rad][xpos-i+rad] = RANGE_CHAR;
                } else {
                for (m=0;m<amount_of_monsters;m++){
                    if (screen[ypos-rad][xpos-i+rad] == pcs[m].letter && (pcs[m].letter != DEAD_BODY_CHAR) && (rad-i<0)){
                        screen[ypos-rad][xpos-i+rad] = TARGET_CHAR;
                    }
                }
                }
            }
        }
    }
}

void chase_figters(int mnstr, int fightr){
    int fx, fy, finalx, finaly;
    int current_x_dist, current_y_dist, current_distance;
    int i, j;
    i = 0;
    j = 0;
    finalx = 0;
    finaly = 0;
    fx = pcs[fightr].x_position;
    fy = pcs[fightr].y_position;
    current_distance = 1000; /* just some high value */
    for (i=0; i<SCREEN_HEIGHT; i++) {
        for (j=0; j<SCREEN_WIDTH; j++) {
            if (screen[i][j] == RANGE_CHAR) {
                /* i is y, j is x */
                if (j>fx) {
                    current_x_dist = j - fx;
                }
                if (j<fx) {
                    current_x_dist = fx - j;
                }
                if (j==fx) {
                    current_x_dist = j;
                }
                if (i>fy) {
                    current_y_dist = i - fy;
                }
                if (i<fy) {
                    current_y_dist = fy - i;
                }
                if (i==fy) {
                    current_y_dist = i;
                }
                if (current_distance>(current_x_dist+current_y_dist)) {
                    current_distance = (current_x_dist+current_y_dist);
                    // finalx = j;
                    // finaly = i;
                    finalx = i;
                    finaly = j;
                }
            }
        }
    }
    // printf("finalx: %d \n",finalx);
    if ((finalx>0)&&(finaly>0)) {
        screen[monsters[mnstr].x_position][monsters[mnstr].y_position] = BASE_CHAR;
        monsters[mnstr].x_position = finalx;
        monsters[mnstr].y_position = finaly;
    }
}

char analyse_command(char comm[12]) {
    int y;
    char *comml = strtolower(comm, 12);
    int amount_of_available_commands = sizeof(av_commands) / sizeof(av_commands[0]);
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
    srand(time(0));
    rnum = (rand() % (upper-lower+1))+lower;
    return rnum;
}

void clean_side_panel(){
    int i,y, sp_lines, line_chars;
    line_chars = sizeof(side_panel[0]);
    sp_lines = sizeof(side_panel) / sizeof(side_panel[0]);
    for(i=0;i<sp_lines;i++){
        for(y=0;y<line_chars;y++){
            side_panel[i][y] = ' ';
        }
    }
}

int ask_spells(char pid[2]){
    /* print fields id and name, from array spells[3],
       based on spells[4][2] from array pcs */
    int i,y,z,amount_of_fighters_spells,sp_counter;
    amount_of_fighters_spells = 4;
    char av_spells[4][2];
    char av_spells_names[4][12];
    char chspell[2];
    /* cleaning av_spells*/
    for(i=0;i<4;i++){
        for(y=0;y<2;y++){
            av_spells[i][y] = ' ';
        }
    }
    /* Getting spells from fighter */
    for (i=0;i<amount_of_fighters;i++){
        if((pcs[i].id[0] == pid[0])&&(pcs[i].id[1] == pid[1])) {
            amount_of_fighters_spells = sizeof(pcs[i].spells);
            for(y=0;y<amount_of_fighters_spells;y++){
                av_spells[y][0] = pcs[i].spells[y][0];
                av_spells[y][1] = pcs[i].spells[y][1];
            }
        }
    }
    sp_counter = 0;
    for(i=0;i<4;i++){
        if (av_spells[i][0] != 'n' && av_spells[i][1] != 'n'){
            sp_counter++;
            for (z=0;z<amount_of_spells;z++) {
                if((spells[z].id[0] == av_spells[i][0]) && (spells[z].id[1] == av_spells[i][1])){
                    // av_spells_names[i] = spells[z].name;
                    memcpy(av_spells_names[i], spells[z].name,sizeof(spells[z].name));
                }
            }
            printf(" [%c%c] %s |",av_spells[i][0],av_spells[i][1],av_spells_names[i]);
        }
    }
    printf("\n");
    if (sp_counter>0) {
        // printf("hint av1: %c%c \n",av_spells[0][0],av_spells[0][1]);
        // printf("Spell counter: %d \n",sp_counter);
        printf("Select spell > ");
        scanf("%s",chspell);
        // for (i=0;i<amount_of_fighters_spells;i++){
        //     if(av_spells[i][0]==chspell[0] && av_spells[i][1]==chspell[1]){
        //         // printf("Casting %c%c",spells[i].id[0],spells[i].id[1]);
        //         return i+1;
        //     }
        // }
        for (i=0;i<amount_of_spells;i++) {
            if (spells[i].id[0]==chspell[0] && spells[i].id[1]==chspell[1]) {
                printip("Found spell",0);
                return i+1;
            }
        }
    } else {
        printf("No spells to cast \n");
        return 0;
    }
    // int amount_of_fighters_spells = sizeof(av_spells) / sizeof(av_spells[0]);
    return i+1;
}

void print_to_side_panel(){
    int i, y, free_lines,word_lenght,in_line_position;
    char monster_hp_string[3];
    char fighter_hp_string[3];
    free_lines = (side_panel_size - amount_of_monsters) - amount_of_fighters;
    clean_side_panel();
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
        side_panel[i][in_line_position] = monsters[i].letter;
        in_line_position++;
        side_panel[i][in_line_position] = ']';
        in_line_position++;
        side_panel[i][in_line_position] = ' ';
        in_line_position++;
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
        // side_panel[i+free_lines+amount_of_monsters][1] = ' ';
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
    int i,j;
    for (i=0;i<SCREEN_HEIGHT;i++){
        for(j=0;j<SCREEN_WIDTH;j++){
            screen[i][j] = ' ';
        }
    }
    memcpy(screen, lvl1,sizeof(lvl1));
    shuffle(targets,4);
    for (i=0;i<amount_of_monsters;i++) {
        monsters[i].target_index = i;
    }
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

int resolve_spell(char pid[2],char taddr[3],char sid[2]){
    /* player id, target coords, spell id */
    /* 1) Attack throw: D20+bonuses vs. target's AC.
        If result is higher or equal to target's AC - success, proceed to 2).
       2) Saving throw. If d20 is bigger that targets .saves, than target is saved,
        otherwise deal DMG.*/
    int dca, dcs, spell_in_array, target_in_array, foundm;
    int i, attack_success, monster_hp, fighter_hp;
    foundm = 0;
    attack_success = 0;
    monster_hp = 0;
    printip("Resolving spell",0);
    adresstocoords(taddr);
    /*target address is in coords[0] and coords[1] */

    /* Let's find spell index */
    for(i=0;i<amount_of_spells;i++){
        if((spells[i].id[0]==sid[0])&&(spells[i].id[1]==sid[1])){
            spell_in_array = i;
        }
    }
    /* check if spells[spell_in_array].recov is greater than 0, 
    if so, it is white magic, targetting fighter. */

    if (spells[spell_in_array].recov > 0) {
        /* Let's find target in monsters array */
        for (i=0; i<amount_of_fighters;i++){
            if((pcs[i].x_position == coords[0])&&(pcs[i].y_position == coords[1])){
                foundm = 1;
                target_in_array = i;
            }
        }
        if (foundm == 0) {
            printip("Nothing there!",0);
            draw_interface();
            return 0;
        }
        fighter_hp = pcs[target_in_array].hp + spells[spell_in_array].recov;
        pcs[target_in_array].hp = fighter_hp;
        printip("HP recovered!",0);
        draw_interface();
        return 1;
    }

    dca = dice(20);
    dcs = dice(20);
    if (dca == 1) {
        printip("MISS!",0);
        draw_interface();
        return 0;
    }
    if (dcs == 1) {
        printip("MISS!",0);
        draw_interface();
        return 0;
    }
    /* Let's find target in monsters array */
    for (i=0; i<amount_of_monsters;i++){
        if((monsters[i].x_position == coords[0])&&(monsters[i].y_position == coords[1])){
            foundm = 1;
            target_in_array = i;
        }
    }
    if (foundm == 0) {
        printip("Nothing there!",1);
        draw_interface();
        return 0;
    }
    monster_hp = monsters[target_in_array].hp;

    if (dca == 20){ attack_success = 1; }
    if (dca >= monsters[target_in_array].ac) {
        attack_success = 1;
    } else {
        attack_success = 0;
    }
    if (dcs >= monsters[target_in_array].saves) {
        printip("MISS!",0);
        return 0;
    }

    if (attack_success == 1){
        printip("HIT!",0);
        monsters[target_in_array].hp = monster_hp - spells[spell_in_array].dmg;
        if (monsters[target_in_array].hp <= 0) {killed++;}
    }
    draw_interface();
    return 0;
}

int resolve_attack(char pid[2],char taddr[3]){
    /*  player id, target coords */
    /*  Attack throw: D20+bonuses vs. target's AC.
        If result is higher or equal to target's AC - success, proceed to 2).
    */
    int dca, target_in_array;
    int i, attack_success, monster_hp, damage, foundm;
    attack_success = 0;
    foundm=0;
    monster_hp = 0;
    printip("Resolving attack",1);
    draw_interface();
    adresstocoords(taddr);
    // printf("Read coords: %c %c resulting addr: %d %d \n",taddr[0],taddr[1],coords[0],coords[1]);
    // sleep(3);
    for (i=0; i<amount_of_monsters;i++){
        // clear_screen();
        // printf("I: %d ",i);
        // sleep(5);
        if((monsters[i].x_position == coords[0])&&(monsters[i].y_position == coords[1])){
            target_in_array = i;
            foundm = 1;
            // printf("Found in position %d \n",target_in_array);
            // sleep(3);
        }
    }
    if (foundm == 0) {
        printip("Nothing there!",1);
        draw_interface();
        return 0;
    }
    monster_hp = monsters[target_in_array].hp;
    dca = dice(20);
    damage = dice(6);
    if (dca == 1) {
        attack_success = 0;
    }
    if (dca == 20) {
        attack_success = 1;
    }
    if (dca >= monsters[target_in_array].ac) {
        attack_success = 1;
    } else {
        attack_success = 0;
    }

    if (attack_success == 1){
        printip("HIT!",1);
        monsters[target_in_array].hp = monster_hp - damage;
        if (monsters[target_in_array].hp<=0) { killed++; }
    } else {
        printip("MISS",1);
    }
    return 0;
}

int resolve_monster_attack(int mnst,int figh){
    int dca, fighter_hp, damage;
    damage = dice(6);
    dca = dice(20);
    fighter_hp = pcs[figh].hp;
    if ((dca>=pcs[figh].ac)||(dca==20)) {
        printip("HIT!",1);
        draw_interface();
        pcs[figh].hp = fighter_hp - damage;
        if (pcs[figh].hp<=0) { died++;}
    }
    else {
        printip("MISS!",1);
        draw_interface();
    }
    return 0;
}

int move_fighter(int number_in_array, char letter, int fx, int fy, char target[3]){
    adresstocoords(target);
    /* make move */
    screen[fx][fy] = BASE_CHAR;
    if (screen[coords[0]][coords[1]] == RANGE_CHAR){
        // screen[coords[0]][coords[1]] = letter;
        pcs[number_in_array].x_position = coords[0];
        pcs[number_in_array].y_position = coords[1];
        clear_range();
        printip("Moved.",1);
        return 1;
    }
    else{
        printip("Can\'t move",1);
        clear_range();
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

int player_action_cast(char pid[2]){
    int i, s, selected_x, selected_y, rad, done;
    done = 0;
    char targetaddr[3];
    printip("Choose spell",1);
    // clean_side_panel();
    // draw_interface();
    s = ask_spells(pid);
    // printf("Casted spell no.: %d",s);
    if (s>0){
        s--;
        rad = spells[s].range / 10;
        for(i=0;i<amount_of_fighters;i++){
            if (pcs[i].id[0] == pid[0] && pcs[i].id[1] == pid[1] && rad>0){
                selected_x = pcs[i].x_position;
                selected_y = pcs[i].y_position;
                if (spells[s].recov > 0) {
                    /* using monster range for white magic spells */
                    printf("White spell: %s, s: %d",spells[s].id,s);
                    draw_monster_range(selected_y,selected_x,rad);
                }
                else {
                    printf("Black spell: %s, s: %d",spells[s].id,s);
                    draw_range(selected_y,selected_x,rad,'c');
                }
                printip("Spell target",1);
                /* Spell target selection here */
                draw_interface();
                // printip("Spell target",1);
                scanf("%s",targetaddr);
                // clear_range();
                /* check if target in range before resolving spell */
                adresstocoords(targetaddr);
                // printf("Checking %d,%d \n",coords[0],coords[1]);
                // printf("Found char: %c \n",screen[coords[0]][coords[1]]);
                if (screen[coords[0]][coords[1]]!=TARGET_CHAR) {
                    printip("NOT IN RANGE!",0);
                    done = 0;
                    clear_range();
                    return done;
                }
                clear_range();
                resolve_spell(pid,targetaddr,spells[s].id);
                done = 1;
            }
        }
    }
    else {
        done = 0;
    }
    return done;
}

int player_action_attack(char pid[2]){
    int i, j, selected_x, selected_y, rad, done;
    char targetaddr[3];
    rad = 1;
    done = 0;
    for(i=0;i<amount_of_fighters;i++){
        if (pcs[i].id[0] == pid[0] && pcs[i].id[1] == pid[1]){
            selected_x = pcs[i].x_position;
            selected_y = pcs[i].y_position;
            if ((pcs[i].weapon[0] == 'b')&&(pcs[i].weapon[1] == 'w')) {
                for(j=0;j<amount_of_weapon;j++){
                    if ((weapons[j].id[0]=='b')&&(weapons[j].id[1]=='w')) {
                        rad = weapons[j].range/10;
                    }
                }
            }
            draw_range(selected_y,selected_x,rad,'c');
            printip("Choose target",1);
            draw_interface();
            scanf("%s",targetaddr);
            // clear_range();
            if (targetaddr[0]=='q') {done = 0;}
            /* resolve_attack(); */
            adresstocoords(targetaddr);
            // printf("Attacking %d,%d",coords[0],coords[1]);
            // printf("Found char: %c",screen[coords[0]][coords[1]]);
            if (screen[coords[0]][coords[1]]!=TARGET_CHAR) {
                    printip("NOT IN RANGE!",0);
                    done = 0;
                    clear_range();
                    return done;
                }
            clear_range();
            resolve_attack(pid,targetaddr);
            draw_interface();
            done = 1;
        }
    }
    return done;
}

int let_move(){
    int i;
    for (i=0;i<amount_of_fighters;i++){
        if (pcs[i].hp<=0) {
            pcs[i].letter = DEAD_BODY_CHAR;
            pcs[i].hp = 0;
            }
        if (pcs[i].initiative == whoseturn){
            if (pcs[i].hp>0) {
                selected_fighter[0] = pcs[i].id[0];
                selected_fighter[1] = pcs[i].id[1]; 
                player_or_monster = 1;
                printip("Player\'s turn",1);
            }
        }
    }
    for (i=0;i<amount_of_monsters;i++){
        if (monsters[i].hp<=0) {
            monsters[i].letter = DEAD_BODY_CHAR;
            monsters[i].hp = 0;
            // monsters[i].initiative = 0;
            // whoseturn++; <- utter nonsense
            }
        if (monsters[i].initiative == whoseturn){
            // if (monsters[i].hp>0) {
                selected_monster[0] = monsters[i].id[0];
                selected_monster[1] = monsters[i].id[1]; 
                player_or_monster = 2;
                printip("Monster\'s turn",1);
            // }
        }
    }
    return 0;
}

/* AI */

void monsters_action(){
    int i;
    for (i=0;i<amount_of_monsters;i++) {
        if ((monsters[i].id[0] == selected_monster[0])&&(monsters[i].id[1] == selected_monster[1])){
            if (monsters[i].hp<=0) {
                printip("DEAD ONE :(",1);
                draw_interface();
                // whoseturn++;
            }
            else {
                printip("I\'ll skip",1);
                draw_interface();
                // whoseturn++;
            }
        }
    }
}

int ai_choose_action(char mid[2]) {
    printip("Choosing action",1);
    int i,j,my_range,enemy_is_close, me_in_array, fighter_found_in_array;
    my_range = 0;
    enemy_is_close = 0;
    fighter_found_in_array = 0;
    int my_addr[2];
    // int current_field_to_check[2];
    for (i=0;i<amount_of_monsters;i++) {
        if((monsters[i].id[0] == mid[0])&&(monsters[i].id[1] == mid[1])){
            my_addr[0] = monsters[i].x_position;
            my_addr[1] = monsters[i].y_position;
            me_in_array = i;
            my_range = monsters[i].mov/10;
        }
    }
    /* check if have a target */
    /* calculate distances */
    /* decide about movement */

    /* check neighbour areas for enemies */
    // proper monster range drawing:
    // draw_monster_range(my_addr[1],my_addr[0],1);
    // draw_interface();
    // sleep(10);
    for(i=0;i<4;i++){
        for(j=0;j<amount_of_fighters;j++){
            /* back */
            if(screen[(my_addr[0]-1)][my_addr[1]] == pcs[i].letter){
                enemy_is_close = 1;
                fighter_found_in_array = i;
                // found_enemy_at[0] = (my_addr[0])-1;
                // found_enemy_at[1] = my_addr[1];
            }
            /* front */
            if(screen[(my_addr[0]+1)][my_addr[1]] == pcs[i].letter){
                enemy_is_close = 1;
                fighter_found_in_array = i;
            }
            /* left */
            if(screen[my_addr[0]][(my_addr[1]-1)] == pcs[i].letter){
                enemy_is_close = 1;
                fighter_found_in_array = i;
            }
            /* right */
            if(screen[my_addr[0]][(my_addr[1]+1)] == pcs[i].letter){
                enemy_is_close = 1;
                fighter_found_in_array = i;
            }
        }
    }
    if(enemy_is_close>0){
        /* attack the first fighter who is close */
        draw_monster_range(my_addr[1],my_addr[0],my_range);
        draw_interface();
        sleep(2);
        resolve_monster_attack(me_in_array,fighter_found_in_array);
        clear_range();
        draw_interface();
        return 1;
    }
    else {
        draw_monster_range(my_addr[1],my_addr[0],my_range);
        draw_interface();
        sleep(2);
        chase_figters(me_in_array, monsters[me_in_array].target_index);
        clear_range();
        return 2;
    }
}

void info_screen(void){
    int i,j;
    char key[1];
    clear_screen();
    printf("-------- FIGHTERS --------\n");
    printf("\n");
    for (i=0;i<amount_of_fighters;i++) {
        if ((pcs[i].id[0] == selected_fighter[0])&&(pcs[i].id[1] == selected_fighter[1])){
            printf(" > [%c] %6s  HP:%d/40\n",pcs[i].letter,pcs[i].name,pcs[i].hp);
        }
        else {
            printf("   [%c] %6s  HP:%d/40\n",pcs[i].letter,pcs[i].name,pcs[i].hp);
        }
    }
    printf("\n\n-------- MONSTERS --------\n");
    printf("\n");
    for (j=0;j<amount_of_monsters;j++) {
        printf(" [%c] %6s %14s  HP:%d\n",monsters[j].letter,monsters[j].name,monsters[j].race, monsters[j].hp);
    }
    printf("\n\n--------------------------\n");
    printf("\n");
    printf("Press any key... ");
    scanf("%c",key);
}