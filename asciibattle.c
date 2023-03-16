#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> /* for pausing on POSIX */
// #include <dos.h> /* for pausing on Windows */
#include "converters.c"


void print_screen(void);
void place_figures(void);
void draw_range(int xpos, int ypos,int radius, char mode);
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
// void move_cursor(int cx, int cy);
int resolve_spell(char pid[2],char taddr[3],char sid[2]);
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
    for (i=0;i<amount_of_fighters;i++){
        if (screen[pcs[i].x_position][pcs[i].y_position] != TARGET_CHAR){
            screen[pcs[i].x_position][pcs[i].y_position] = pcs[i].letter;
        }
        if(screen[monsters[i].x_position][monsters[i].y_position] != TARGET_CHAR){
            screen[monsters[i].x_position][monsters[i].y_position] = monsters[i].letter;
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
                if (screen[address_y-i][address_x] == monsters[m].letter){
                    screen[address_y-i][address_x] = TARGET_CHAR;
                }
            }
        }
        if (screen[address_y+i][address_x] == BASE_CHAR){
            screen[address_y+i][address_x] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_monsters;m++){
                if (screen[address_y+i][address_x] == monsters[m].letter){
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
                if (screen[address_y-i][address_x-rad+radius] == monsters[m].letter){
                    screen[address_y-i][address_x-rad+radius] = TARGET_CHAR;
                }
            }
        }
        /* down */
        if (screen[address_y-i+rad][address_x-rad+radius] == BASE_CHAR){
            screen[address_y-i+rad][address_x-rad+radius] = RANGE_CHAR;
        } else {
            for (m=0;m<amount_of_monsters;m++){
                if (screen[address_y-i+rad][address_x-rad+radius] == monsters[m].letter){
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
                    if (screen[address_y+rad][address_x-i+rad] == monsters[m].letter && (rad-i<0)){
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
                    if (screen[address_y-rad][address_x-i+rad] == monsters[m].letter && (rad-i<0)){
                        screen[address_y-rad][address_x-i+rad] = TARGET_CHAR;
                    }
                }
                }
            }
        }
    }
    } /* end if((mode=='a')||(mode=='c'))*/
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
    int i,y,amount_of_fighters_spells;
    amount_of_fighters_spells = 4;
    char av_spells[4][2];
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
    for(i=0;i<4;i++){
        if (av_spells[i][0] != 'n' && av_spells[i][1] != 'n'){
            printf(" [%c%c] Spell name |",av_spells[i][0],av_spells[i][1]);
        }
    }
    scanf("%s",chspell);
    for (i=0;i<amount_of_spells;i++){
        if(spells[i].id[0]==chspell[0] && spells[i].id[1]==chspell[1]){
            // printf("Casting %c%c",spells[i].id[0],spells[i].id[1]);
            return i;
        }
    }
    return 0;
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
    int dca, dcs, spell_in_array, target_in_array;
    int i, attack_success, save_success, monster_hp;
    attack_success = 0;
    save_success = 0;
    monster_hp = 0;
    printip("Resolving spell",0);
    adresstocoords(taddr);
    /*target address is in coords[0] and coords[1] */
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
            target_in_array = i;
        }
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
    
    /* Let's find target in monsters array */
    for(i=0;i<amount_of_spells;i++){
        if((spells[i].id[0]==sid[0])&&(spells[i].id[1]==sid[1])){
            spell_in_array = i;
        }
    }

    if (attack_success == 1){
        printip("HIT!",0);
        monsters[target_in_array].hp = monster_hp - spells[spell_in_array].dmg;
    }
    draw_interface();
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
    // scanf("%s",chspell);
    rad = spells[s].range / 10;
    for(i=0;i<amount_of_fighters;i++){
        if (pcs[i].id[0] == pid[0] && pcs[i].id[1] == pid[1] && rad>0){
            selected_x = pcs[i].x_position;
            selected_y = pcs[i].y_position;
            // fighter_letter = pcs[i].letter;
            // rad = pcs[i].mov / 10;
            // arrnum = i;
            // printip("Specify adress...",1);
            draw_range(selected_y,selected_x,rad,'c');
            printip("Spell target",1);
        }
    }
    /* Spell target selection here */
    draw_interface();
    printip("Spell target",1);
    scanf("%s",targetaddr);
    clear_range();
    resolve_spell(pid,targetaddr,spells[s].id);
    // draw_interface();
    return done;
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