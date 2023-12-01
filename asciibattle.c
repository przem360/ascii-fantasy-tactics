#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* for pausing on POSIX */
// #include <dos.h> /* for pausing on Windows */
#include <time.h> /* for seeding rand() with time */
#include "settings.h"
#include "colors.h"
#include "converters.h"
#include "asciibattle.h"
#include "helpers.h"
#include "globals.h"
#include "resources.h"

const char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

// int game_mode;

char current_command[8];
int selected_fighter;
int selected_monster;
char output[1];
int whoseturn = 1; /* Initiative selection */
int player_or_monster = 1; /* 1 = player, 2 = monster */
int targets[] = {0,1,2,3};

// int cursor_on = 1;

int killed = 0; /* how many monsters were killed by fighters */
int died = 0;   /* how many fighters were killed by monsters */

const char av_commands[6][6] = {"move", "attack", "cast", "skip", "quit","info"};
int max_mov_fields = MAX_MOV * MAX_MOV;
char command_code[2]; /* what analyse_command things about user input?*/
int wasmoved = 0;
int tookaction = 0;
char tb_command[12] = {'c','o','d','e','e','\0'};
int aiaction;
int fid, mid; /* fighter id, monster id*/
// int max_power;

int legal_moves[MAX_MOV * MAX_MOV][3];
int the_move[2];


int side_panel_size = sizeof(side_panel)/sizeof(side_panel[0]);


int tb_read_command(void){
    // while( (tb_command[0] = getchar() != '\n') && (tb_command[0] != EOF));
    printf("Command > ");
    fgets(tb_command,12,stdin);
    char *p = strchr(tb_command, '\n');
    if (p) *p = 0;
    return 0;
}

int get_array_index(char type, int id){
    int i;
    if (type == 'm') {
        for (i=0;i<amount_of_monsters;i++){
            if (monsters[i].id==id) {
                return i;
            }
        }
    }
    if (type == 'f') {
        for (i=0;i<amount_of_fighters;i++){
            if (pcs[i].id==id){
                return i;
            }
        }
    }
    return 0;
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
    if (!NO_SIDEPANEL) { print_to_side_panel(); }
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
            if (COLOURS_ON == 1) {
                if (screen[i][y] == DEAD_BODY_CHAR)  {printf(RED  "%c" reset,screen[i][y]);}
                else if (screen[i][y] == WATER_CHAR) {printf(BLUB "%c" reset,screen[i][y]);}
                else if (screen[i][y] == RANGE_CHAR) {printf(BLUB "%c" reset,screen[i][y]);}
                else printf(GRNB "%c" reset,screen[i][y]);
                }
            else {printf("%c",screen[i][y]); }
        }
        if (i<side_panel_size){ 
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
    if (NO_SIDEPANEL) {
        print_stats_horisontal('m');
        printf("\n");
    }
    print_screen();
    if (NO_SIDEPANEL) {
        print_stats_horisontal('f');
    }
    draw_info_panel();
}

void place_figures(){
    if (DBG_MODE) printf("\nPlacing figures\n");
    int i, pxp, pyp, mxp, myp;
    pxp = 0;
    pyp = 0;
    mxp = 0;
    myp = 0;
    for (i=0;i<amount_of_fighters;i++){
        pxp = pcs[i].x_position;
        pyp = pcs[i].y_position;
        // printf("pxp: %d pyp: %d \n",pxp,pyp);
        // if ((pxp>=0)&&(pyp>=0)) {
            if (screen[pxp][pyp] != TARGET_CHAR){
                screen[pxp][pyp] = pcs[i].letter;
            }
        // }
    }
    for (i=0; i<amount_of_monsters;i++) {
        mxp = monsters[i].x_position;
        myp = monsters[i].y_position;
        // printf("mxp: %d myp: %d \n",mxp,myp);
        if ((mxp>=0)&&(myp>=0)&&(mxp<14)&&(myp<22)) {
            if(screen[mxp][myp] != TARGET_CHAR){
            screen[mxp][myp] = monsters[i].letter;
            }
        }
    }
    if (screen[0][0] == DEAD_BODY_CHAR) screen[0][0] = WALL_CHAR;
}

void clear_range(){
    if (DBG_MODE) printf("\nClearing range\n");
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

void draw_range(char actor, int xpos, int ypos, int radius, char mode){
    /* 
        actor: f - fighter/player; m - monster;
        mode: m - move, c (or a) - cast, attack
       in the move mode range is drawn only on BASE_CHAR
       in c or a enemy letters are replaced with TARGET_CHAR*/
    // adresstocoords(id);
    int i, j, ofst;
    int t; /* for counting targets */
    clear_range();
    if (mode == 'm') {
        if (DBG_MODE) {printf("\nDrawing movement for %c, from position X:%d Y:%d with range: %d\n",actor,xpos,ypos,radius);}
        for (i = ypos - radius; i <= ypos + radius; i++) {
            ofst = (i - ypos) > 0 ? (i - ypos) : (ypos - i);
            for (j = xpos - radius + ofst; j <= xpos + radius - ofst; j++) {
                if ((i<(SCREEN_HEIGHT))&&(j<(SCREEN_WIDTH))&&(j>0)){ if (screen[i][j] == BASE_CHAR) { screen[i][j] = RANGE_CHAR; } }
            }
        }
    } /* end if(mode=='m')*/
    if ((mode == 'c')||(mode == 'a')) {
        for (i = ypos - radius; i <= ypos + radius; i++) {
            ofst = (i - ypos) > 0 ? (i - ypos) : (ypos - i);
            for (j = xpos - radius + ofst; j <= xpos + radius - ofst; j++) {
                if ((i<(SCREEN_HEIGHT))&&(j<(SCREEN_WIDTH))&&(j>0)){
                    if (screen[i][j] == BASE_CHAR) { screen[i][j] = RANGE_CHAR; }
                    if (actor == 'f'){
                        for(t=0;t<amount_of_monsters;t++){
                            if ((screen[i][j] == monsters[t].letter)&&(monsters[t].letter != DEAD_BODY_CHAR)){
                                screen[i][j] = TARGET_CHAR;
                            }
                    }
                    }
                    else if (actor == 'm'){
                        for(t=0;t<amount_of_fighters;t++){
                            if ((screen[i][j] == pcs[t].letter)&&(pcs[t].letter != DEAD_BODY_CHAR)){
                                screen[i][j] = TARGET_CHAR;
                            }
                    }
                    }
                }
            }
        }
    } /* end if((mode=='a')||(mode=='c'))*/
}

void chase_figters(int mnstr, int fightr){
    int fx, fy;
    int current_distance;
    int i, j, k;
    // int legal_moves[max_mov_fields][3];
    // int the_move[2];
    for (i=0;i<max_mov_fields;i++){
        legal_moves[i][0] = 0;
        legal_moves[i][1] = 0;
        legal_moves[i][2] = 0;
    }
    the_move[0] = 0;
    the_move[1] = 0;
    k = 0;
    fx = pcs[fightr].x_position;
    fy = pcs[fightr].y_position;
    current_distance = 1000;/* just some high value */
    for (i=0; i<SCREEN_HEIGHT; i++) {
        for (j=0; j<SCREEN_WIDTH; j++) {
            if (screen[i][j] == RANGE_CHAR) {
                legal_moves[k][0] = i;
                legal_moves[k][1] = j;
                legal_moves[k][2] = (abs(i - fx)+abs(j - fy));
                // legal_moves[k][2] = 2;
                k++;
            }
        }
    }
    if(DBG_MODE==1) printf("Found %d legal moves \n",k);
    // screen[mxp][myp] = monsters[i].letter;
    for (i=0;i<k;i++){
        if ((legal_moves[i][0]>0)&&(legal_moves[i][1]>0)) {
            if (legal_moves[i][2]<current_distance) { 
                if(DBG_MODE==1) printf("Current shortest is x: %d y: %d with distance: %d \n",legal_moves[i][0],legal_moves[i][1],legal_moves[i][2]);
                current_distance = legal_moves[i][2];
                the_move[0] = legal_moves[i][0];
                the_move[1] = legal_moves[i][1];
            }
    
        }
    }
    
    // test legal_moves
    if(DBG_MODE==1) {
        // for (i=0;i<100;i++) {
        //     if ((legal_moves[i][0]>0)&&(legal_moves[i][1]>0)) printf("Legal v: %d          legal h: %d          distance: %d\n",legal_moves[i][0],legal_moves[i][1],legal_moves[i][2]);
        // }
        for (i=0;i<MAX_MOV*MAX_MOV;i++){
            for (j=0;j<3;j++){
                printf(" :: legal_moves[%d][%d] =  %d :: ",i,j,legal_moves[i][j]);
            }
            printf("\n");
        }
        printf("My target is: %c at [%d %d] \n",pcs[fightr].letter,fx,fy);
        printf("I decide to move to: [%d %d] \n",the_move[0],the_move[1]);
    }

    screen[monsters[mnstr].x_position][monsters[mnstr].y_position] = BASE_CHAR;
    monsters[mnstr].x_position = the_move[0];
    monsters[mnstr].y_position = the_move[1];
    if(DBG_MODE==1) printf("Now I am at: [%d %d] \n",monsters[mnstr].x_position,monsters[mnstr].y_position);
}

char analyse_command(char comm[6]) {
    int y;
    char *comml = strtolower(comm, 12);
    int amount_of_available_commands = sizeof(av_commands) / sizeof(av_commands[0]);
    if (startswith("knock knock",comml)) {
        cleanip();
        printip("Whos there?        ",1);
        return 'k';
    }
    if ((strlen(comml) < 3)&&(comml[0] == 'q')){
        return 'q';
    }
    for (y=0;y<=amount_of_available_commands;y++){
        if(strcmp(av_commands[y], comml)){
            cleanip();
            printip("Command found!     ",1);
            /* make it return the letter of command*/
            return comml[0];
        }   
        // printf("Command %s does not math available command %s",comml,av_commands[y]);
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

int ask_spells(int pid){
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
        if(pcs[i].id == pid) {
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
        for (i=0;i<amount_of_spells;i++) {
            if (spells[i].id[0]==chspell[0] && spells[i].id[1]==chspell[1]) {
                printip("Found spell        ",0);
                if (DBG_MODE == 1) {printf("Found spell: %s", spells[i].name);}
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

void print_stats_horisontal(char mode){
    int i;
    if (mode == 'm'){
        for(i=0;i<amount_of_monsters;i++){
            if (monsters[i].name[0]) {
                if(selected_monster == monsters[i].id){ printf(">[%c] HP:%d  ",monsters[i].letter,monsters[i].hp); }
                else {printf("[%c] HP:%d  ",monsters[i].letter,monsters[i].hp);}
            }
        }
        printf("\n");
    }
    else if (mode == 'f'){
        for(i=0;i<amount_of_fighters;i++){
            if(selected_fighter == pcs[i].id){ printf(">[%c] HP:%d  ",pcs[i].letter,pcs[i].hp); }
            else { printf("[%c] HP:%d  ",pcs[i].letter,pcs[i].hp); }
        }
        printf("\n");
    }
    else {
        printf("! Error in print_stats_horisontal - use only m or f modes!");
    }
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
        if(selected_monster == monsters[i].id){
            side_panel[i][1] = '>';
        } else {
            side_panel[i][1] = ' ';
        }
        if (monsters[i].name[0]) {
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
    }
    for(i=0;i<amount_of_fighters;i++){
        snprintf(fighter_hp_string,3,"%d",pcs[i].hp);
        in_line_position = 3;
        // side_panel[i+free_lines+amount_of_monsters][1] = ' ';
        if(selected_fighter == pcs[i].id){
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

void ascii_battle_init(int current_location, int arena_id) {
    killed = 0;
    died = 0;
    int amount_of_beasts = sizeof(beasts) / sizeof(beasts[0]);
    int i,j;
    for (i=0;i<amount_of_fighters;i++){
        pcs[i].x_position = pcs[i].start_x_position;
        pcs[i].y_position = pcs[i].start_y_position;
    }
    if (current_location > 0){
        j = 0;
        for (i=0;i<amount_of_beasts;i++){
            if (beasts[i].location == current_location){
                monsters[j] = beasts[i];
                printf("Copying %s to index %d\n",beasts[i].name,j);
                j++;
            }
        }
    }
    for (i=0;i<SCREEN_HEIGHT;i++){
        for(j=0;j<SCREEN_WIDTH;j++){
            screen[i][j] = ' ';
        }
    }
    // memcpy(screen, lvl1,sizeof(lvl1));
    memcpy(screen, lvls[arena_id],sizeof(lvls[arena_id]));
    shuffle(targets,4);
    for (i=0;i<amount_of_monsters;i++) {
        monsters[i].target_index = i;
    }
    if(DBG_MODE==1) {
        printf("current_location: %d\n",current_location);
        printf("amount_of_monsters: %d\nfirst monster: %c\n",amount_of_monsters,monsters[0].letter);
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

int resolve_spell(int pid,char taddr[3],char sid[2]){
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
    printip("Resolving spell    ",0);
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
            printip("Nothing there!     ",0);
            draw_interface();
            return 0;
        }
        fighter_hp = pcs[target_in_array].hp + spells[spell_in_array].recov;
        if (fighter_hp>pcs[target_in_array].max_hp){
            fighter_hp = pcs[target_in_array].max_hp;
        }
        pcs[target_in_array].hp = fighter_hp;
        printip("HP recovered!      ",0);
        if (DBG_MODE == 1) {printf("HP recovered!\n");}
        draw_interface();
        return 1;
    }

    dca = dice(20);
    dcs = dice(20);
    if (dca == 1) {
        printip("MISS!              ",0);
        if (DBG_MODE == 1) {printf("MISS! DCA == 1\n");}
        draw_interface();
        return 0;
    }
    if (dcs == 1) {
        printip("MISS!              ",0);
        if (DBG_MODE == 1) {printf("MISS! DCS == 1\n");}
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
        printip("Nothing there!     ",1);
        if (DBG_MODE == 1) {printf("Nothing at this address.\n");}
        draw_interface();
        return 0;
    }
    monster_hp = monsters[target_in_array].hp;

    if (dca == 20){ if (DBG_MODE == 1) {printf("HIT! DCA == 20\n");} attack_success = 1; }
    if (dca >= monsters[target_in_array].ac) {
        attack_success = 1;
        if (DBG_MODE == 1) {printf("HIT! DCA >= AC\n");}
    } else {
        attack_success = 0;
        if (DBG_MODE == 1) {printf("MISS! DCA < AC\n");}
    }
    if (dcs >= monsters[target_in_array].saves) {
        printip("MISS!              ",0);
        if (DBG_MODE == 1) {printf("MISS! DCS >= Monster saving throw\n");}
        return 0;
    }

    if (attack_success == 1){
        printip("HIT!               ",0);
        monsters[target_in_array].hp = monster_hp - spells[spell_in_array].dmg;
        if (monsters[target_in_array].hp <= 0) {killed++;}
    }
    draw_interface();
    return 0;
}

int resolve_attack(int pid,char taddr[3]){
    /*  player id, target coords */
    /*  Attack throw: D20+bonuses vs. target's AC.
        If result is higher or equal to target's AC - success, proceed to 2).
    */
    int dca, target_in_array;
    int i, attack_success, monster_hp, damage, foundm;
    attack_success = 0;
    foundm=0;
    monster_hp = 0;
    printip("Resolving attack...",1);
    // draw_interface();
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
        printip("Nothing there!     ",1);
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
        printip("HIT!               ",1);
        monsters[target_in_array].hp = monster_hp - damage;
        if (monsters[target_in_array].hp<=0) { killed++; }
    } else {
        printip("MISS!              ",1);
    }
    return 0;
}

int resolve_monster_attack(int mnst,int figh){
    int dca, fighter_hp, damage;
    damage = dice(6);
    dca = dice(20);
    fighter_hp = pcs[figh].hp;
    if ((dca>=pcs[figh].ac)||(dca==20)) {
        printip("HIT!               ",1);
        draw_interface();
        sleep(1);
        pcs[figh].hp = fighter_hp - damage;
        if (pcs[figh].hp<=0) { 
            pcs[figh].letter = DEAD_BODY_CHAR;
            died++;
            draw_interface();
            }
    }
    else {
        printip("MISS!              ",1);
        draw_interface();
        sleep(1);
    }
    if(DBG_MODE==1) printf("Clearing range after attack\n");
    clear_range();
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
        printip("Moved...           ",1);
        return 1;
    }
    else{
        printip("Can\'t move...      ",1);
        clear_range();
        pcs[number_in_array].x_position = fx;
        pcs[number_in_array].y_position = fy;
        draw_interface();
        return 0;
    }
}

int player_action_move(int pid){
    int i, selected_x, selected_y, rad, arrnum, mv, addr_test;
    mv = 0;
    addr_test = 0;
    char fighter_letter;
    char addr[3];
    for(i=0;i<amount_of_fighters;i++){
        if (pcs[i].id == pid){
            selected_x = pcs[i].x_position;
            selected_y = pcs[i].y_position;
            fighter_letter = pcs[i].letter;
            rad = pcs[i].mov / 10;
            arrnum = i;
            printip("Specify address... ",1);
            draw_range('f',selected_y,selected_x,rad,'m');
        }
    }
    draw_interface();
    /* need to validate if addr is an address, not some random stuff */
    while (addr_test == 0) {
        addr[0] = '\0';
        scanf("%3s",addr);
        addr_test = validate_coords(addr);
    }
    mv = move_fighter(arrnum,fighter_letter,selected_x,selected_y,addr);
    draw_interface();
    return mv;
}

int player_action_cast(int pid){
    int i, s, selected_x, selected_y, rad, done;
    done = 0;
    char targetaddr[3];
    printip("Choose spell       ",1);
    // clean_side_panel();
    // draw_interface();
    s = ask_spells(pid);
    // printf("Casted spell no.: %d",s);
    if (s>0){
        s--;
        rad = spells[s].range / 10;
        for(i=0;i<amount_of_fighters;i++){
            if (pcs[i].id == pid && rad>0){
                selected_x = pcs[i].x_position;
                selected_y = pcs[i].y_position;
                if (spells[s].recov > 0) {
                    /* using monster range for white magic spells */
                    // printf("White spell: %s, s: %d",spells[s].id,s);
                    if (DBG_MODE == 1) {printf("\nDrawing call at: 931\n");}
                    draw_range('m',selected_x,selected_y,rad,'c');
                }
                else {
                    // printf("Black spell: %s, s: %d",spells[s].id,s);
                    draw_range('f',selected_x,selected_y,rad,'c');
                }
                printip("Spell target       ",1);
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
                    printip("NOT IN RANGE!      ",0);
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

int player_action_attack(int pid){
    int i, j, selected_x, selected_y, rad, done;
    char targetaddr[3];
    rad = 1;
    done = 0;
    for(i=0;i<amount_of_fighters;i++){
        if (pcs[i].id == pid){
            selected_x = pcs[i].x_position;
            selected_y = pcs[i].y_position;
            if ((pcs[i].weapon[0] == 'b')&&(pcs[i].weapon[1] == 'w')) {
                for(j=0;j<amount_of_weapon;j++){
                    if ((weapons[j].id[0]=='b')&&(weapons[j].id[1]=='w')) {
                        rad = weapons[j].range/10;
                    }
                }
            }
            draw_range('f',selected_y,selected_x,rad,'c');
            printip("Choose target      ",1);
            draw_interface();
            scanf("%s",targetaddr);
            // clear_range();
            if (targetaddr[0]=='q') {done = 0;}
            /* resolve_attack(); */
            adresstocoords(targetaddr);
            // printf("Attacking %d,%d",coords[0],coords[1]);
            // printf("Found char: %c",screen[coords[0]][coords[1]]);
            if (screen[coords[0]][coords[1]]!=TARGET_CHAR) {
                    printip("NOT IN RANGE!      ",0);
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
                selected_fighter = pcs[i].id;
                player_or_monster = 1;
                printip("Player\'s turn      ",1);
                // return 0;
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
                selected_monster = monsters[i].id;
                player_or_monster = 2;
                printip("Monster\'s turn     ",1);
            // }
        }
    }
    return 0;
}

/* AI */

void monsters_action(){
    int i;
    for (i=0;i<amount_of_monsters;i++) {
        if (monsters[i].id == selected_monster){
            if (monsters[i].hp<=0) {
                printip("DEAD ONE :(        ",1);
                draw_interface();
                // whoseturn++;
            }
            else {
                printip("I\'ll skip          ",1);
                draw_interface();
                // whoseturn++;
            }
        }
    }
}

int ai_choose_action(int ai_mid) {
    printip("Choosing action    ",1);
    int i,j, my_range,enemy_is_close, me_in_array, fighter_found_in_array;
    // int fighter_in_range,coin;
    //fighter_in_range = 99;
    my_range = 0;
    enemy_is_close = 0;
    fighter_found_in_array = 0;
    int my_addr[2];
    // int current_field_to_check[2];
    for (i=0;i<amount_of_monsters;i++) {
        if(monsters[i].id == ai_mid){
            my_addr[0] = monsters[i].x_position;
            my_addr[1] = monsters[i].y_position;
            me_in_array = i;
            my_range = monsters[i].mov/10;
        }
    }
    /* retargetting if current monster's target is already dead */
    if (pcs[monsters[me_in_array].target_index].hp <=0) {
        if (monsters[me_in_array].target_index+1 < amount_of_monsters) {
            monsters[me_in_array].target_index = monsters[me_in_array].target_index+1;
        }
        else {
            monsters[me_in_array].target_index = monsters[me_in_array].target_index-1;
        }
        printip("Retargetting       ",1);
        draw_interface();
        sleep(1);
    }
    /* check if have a target */
    /* calculate distances */
    /* decide about movement */

    /* check neighbour areas for enemies */
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
        if(DBG_MODE==1) printf("Found enemy very close, I will stay and attack \n");
        if (DBG_MODE == 1) {printf("\nDrawing call at: 1125\n");}
        draw_range('m',my_addr[1],my_addr[0],my_range,'c');
        draw_interface();
        sleep(2);
        resolve_monster_attack(me_in_array,fighter_found_in_array);
        // tookaction = 1;
        // clear_range();
        // if(DBG_MODE==1) printf("Cleaned range because enemy is close \n");
        draw_interface();
        return 1;
    }
    else {
        // coin = dice(10);
        if(DBG_MODE==1) printf("No enemy nowhere near \n");
        if (DBG_MODE == 1) {printf("\nDrawing call at: 1140\n");}
        draw_range('m',my_addr[1],my_addr[0],my_range,'m');
        draw_interface();
        sleep(2);
        // if (coin<5) {
        //     for (i=0;i<SCREEN_HEIGHT;i++){
        //         for (j=0;j<SCREEN_WIDTH;j++){
        //             if (screen[i][j]==TARGET_CHAR) {
        //                 fighter_in_range = get_fighter_by_position(i,j);
        //                 chase_figters(me_in_array,fighter_in_range);
        //                 clear_range();
        //                 return 2;
        //             }
        //         }
        //     }
        // }
        chase_figters(me_in_array, monsters[me_in_array].target_index);
        // wasmoved = 1;
        clear_range();
        return 2;
    }
}

void info_screen(void){
    int i,j;
    char key[1];
    clear_screen();
    getchar();
    printf("------------ FIGHTERS ------------\n");
    printf("\n");
    for (i=0;i<amount_of_fighters;i++) {
        if (pcs[i].id == selected_fighter){
            printf(" > [%c] %6s  HP:%d/%d\n",pcs[i].letter,pcs[i].name,pcs[i].hp,pcs[i].max_hp);
        }
        else {
            printf("   [%c] %6s  HP:%d/%d\n",pcs[i].letter,pcs[i].name,pcs[i].hp,pcs[i].max_hp);
        }
    }
    printf("\n\n------------ MONSTERS ------------\n");
    printf("\n");
    for (j=0;j<amount_of_monsters;j++) {
        printf(" [%c] %6s %14s  HP:%d\n",monsters[j].letter,monsters[j].name,monsters[j].race, monsters[j].hp);
    }
    printf("\n\n----------------------------------\n");
    printf("\n");
    printf("Press any key... ");
    scanf("%c",key);
}

int get_fighter_by_position(int x, int y){
    int i;
    for (i=0;i<amount_of_fighters;i++){
        if ((pcs[i].x_position == x)&&(pcs[i].y_position == y)){
            return i;
        }
    }
    return 99;
}

void restore_fighters_hp(void) {
    int i = 0;
    for (i=0; i<amount_of_fighters; i++){
        pcs[i].hp = pcs[i].max_xp;
    }
}

// void fix_monster_letters(){
//     int monsters_on_board;
//     monsters_on_board = 0;
//     int i;
//     for (i=0;i<amount_of_monsters;i++){
//         if (monsters[i].letter == TARGET_CHAR){}
//     }
// }

int play_battle(int enemy_location, int selected_arena, int mode){
    // problem: po wygranej w adventure wyrzuca do ekranu głównego
    int amount_of_beasts = sizeof(beasts) / sizeof(beasts[0]);
    int amount_of_monsters_in_room = 0;
    int i = 0;
    for (i=0;i<amount_of_beasts;i++){
        if (beasts[i].location == enemy_location) amount_of_monsters_in_room++;
    }
    // current_location = enemy_location;
    ascii_battle_init(enemy_location, selected_arena);
    while(killed<amount_of_monsters_in_room && died<amount_of_fighters && command_code[0] != 'q'){
        if ((wasmoved > 0)&&(tookaction > 0)){
            wasmoved = 0;
            tookaction = 0;
            whoseturn++;
        }
        // check if fighter of monster with geaven whoseturn (initiative) egzists, if not increase whoseturn
        int found;
        found = 0;
        for (i=0;i<amount_of_monsters;i++){
            if ((monsters[i].initiative == whoseturn) || (pcs[i].initiative == whoseturn)) {
                // printf("\nNo turn number: %d ",whoseturn);
                // whoseturn++;
                // printf(" turn increased to: %d \n",whoseturn);
                found = 1;
            }
        }
        if (found == 0) whoseturn++;

        if (whoseturn>(amount_of_fighters+amount_of_monsters)){
            wasmoved = 0;
            tookaction = 0;
            whoseturn = 1;
        }
        /* check here if selected pcs hp <=0 */
        clear_screen();
        printf("ASCII FANTASY TACTICS \n");
        // place_figures();
        let_move();
        draw_interface();
        // printf("\nPOM value 1: %d TURN: %d\n",player_or_monster,whoseturn);
        if (player_or_monster == 1){
            /* Player's move */
            clear_range();
            // printf("Command > ");
            // fgets(command,COMMAND_LENGHT,stdin);
            // scanf("%s", tb_command);
            tb_read_command();
            command_code[0] = analyse_command(tb_command);
            if (command_code[0] == 'm'){
                if (wasmoved == 0) {
                    printip("MOVING             ",1);
                    wasmoved = player_action_move(selected_fighter);
                }
            }
            if (command_code[0] == 'a'){
                if (tookaction == 0) {
                    printip("ATTACKING          ",1);
                    tookaction = player_action_attack(selected_fighter);
                    // sleep(1);
                    // draw_interface();
                }
            }
            if (command_code[0] == 'c'){
                if (tookaction == 0) {
                    printip("CAST SPELL         ",1);
                    tookaction = player_action_cast(selected_fighter);
                    // draw_interface();
                }
            }
            if (command_code[0] == 's'){
                // player_action_move(selected_fighter);
                printip("SKIPPING           ",1);
                wasmoved = 1;
                tookaction = 1;
                // whoseturn++;
            }
            if (command_code[0] == 'i'){
                info_screen();
            }
        }
        if (player_or_monster == 2){
            /* monster's move */
            // draw_interface();
            if (DBG_MODE == 1) {printf("Selected monster: %d", selected_monster);}
            mid = get_array_index('m',selected_monster);
            if (monsters[mid].hp > 0) {
                aiaction = ai_choose_action(selected_monster);
                if (aiaction == 1) {
                    tookaction = 1;
                    wasmoved = 0;
                }
                if (aiaction == 2) {
                    tookaction = 0;
                    wasmoved = 1;
                }
                if (wasmoved == 0) {
                    // fid = get_array_index('f',);
                    if (DBG_MODE == 1) {printf("\nDrawing call at: 1310\n");}
                    draw_range('m',monsters[mid].y_position,monsters[mid].x_position,monsters[mid].mov/10,'m');
                    chase_figters(mid,monsters[mid].target_index);
                    clear_range();
                    // chase_figters(me_in_array, monsters[me_in_array].target_index)
                    wasmoved = 1;
                    // printf("fid: %d",fid);
                }
                if (tookaction == 0) {
                    tookaction = 1; /* for now */
                }
                // monsters_action();
                // wasmoved = 1;
                // tookaction = 1;
                draw_interface();
                // sleep(1);
            }
            else {
                monsters_action();
                wasmoved = 1;
                tookaction = 1;
                draw_interface();
            }
        }
        }

        if (command_code[0] == 'q') {
            // game_mode = 0;
            // if (DBG_MODE == 1) {printf("[q] pressed, quitting...\ngame_mode: %d\n", game_mode);}
            return 0;
        }
        
        if (died >= amount_of_fighters){
            // game_mode = 3;
            restore_fighters_hp();
            clear_screen();
            printf("You lost! \n");
            sleep(2);
            // if (game_mode == 1) { game_mode = 0; }
            if (mode == 1) return 0;
            else return 2;
        }
        if (killed >= amount_of_monsters || killed >= amount_of_monsters_in_room){
            // game_mode = 2;
            clear_screen();
            printf("You won! \n");
            sleep(2);
            if (mode == 1) return 0;
            else return 4;
        }
    return 0;
}
void cheat_max_hp(void) {
    int i = 0;
    for (i=0; i<amount_of_fighters; i++){
        pcs[i].hp = MAX_POW;
    }
}