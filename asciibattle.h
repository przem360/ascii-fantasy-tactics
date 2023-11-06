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
void print_stats_horisontal(char mode);
void print_to_side_panel(void);
int ask_spells(char pid[2]);
void ascii_battle_init(int location);
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
int get_fighter_by_position(int x, int y);
void restore_fighters_hp(void);
void cheat_max_hp(void);
int play_battle(int enemy_location);
void cheat_max_hp(void);

const char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

char current_command[8];
char selected_fighter[] = "nn";
char selected_monster[] = "nn";
char output[1];
int whoseturn = 1; /* Initiative selection */
int player_or_monster = 1; /* 1 = player, 2 = monster */
int targets[] = {0,1,2,3};

// int cursor_on = 1;

int killed = 0; /* how many monsters were killed by fighters */
int died = 0;   /* how many fighters were killed by monsters */