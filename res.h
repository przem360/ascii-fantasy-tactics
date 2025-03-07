char screen[SCREEN_HEIGHT][SCREEN_WIDTH];

char info_panel[2][22] = {
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
};

char side_panel[12][32] = {
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};


char lvls[4][14][22] = {
    {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    },
    {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','#','#','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','#'},
        {'#','.','.','#','#','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','#','#','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','#'},
        {'#','.','.','#','#','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    },
    {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','#','#','.','.','.','.','.','.','#','#','.','.','.','.','.','#'},
        {'#','~','~','~','~','~','~','#','.','.','.','.','.','.','#','~','~','~','~','~','~','#'},
        {'#','~','~','~','~','~','~','#','.','.','.','.','.','.','#','~','~','~','~','~','~','#'},
        {'#','~','~','~','~','~','~','#','.','.','.','.','.','.','#','~','~','~','~','~','~','#'},
        {'#','.','.','.','.','.','#','#','.','.','.','.','.','.','#','#','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    },
    {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','#','#','#','#','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','#','~','~','~','~','#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','#','~','~','~','~','#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','#','~','~','~','~','#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','#','#','#','#','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    }
};

/*PARTY - PLAYABLE CHARACTERS*/

struct character_pc {
    char letter;
    int id;         // id is must be unique, since we could have multiple figures with the same letter.
    int initiative;
    char name[10];
    char pc_class[10];
    char pc_description[24];
    int lvl;
    int xp;
    int max_xp;
    int mov; /*how many squares player can move*/
    int hp;
    int max_hp;
    int ac; /*Armor Class*/
    int bonus; /*Attack Bonus*/
    int chain_mail;
    char weapon[2];
    char spells[4][2];
    int start_x_position;
    int start_y_position;
    int x_position;
    int y_position;
};


struct character_pc pcs[4] = {
    {'A',1,2,"Avery", "Fighter","This one is protagonist.",1,0,2000,40,8,8,15,1,1,{'b','s'},{{'n','n'},{'n','n'},{'n','n'},{'n','n'}},12,3,12,3},
    {'K',2,4,"Koko",  "Bl__Mage","I will eradicate them.",  1,0,2500,40,6,6,13,1,0,{'m','r'},{{'l','b'},{'f','b'},{'n','n'},{'n','n'}},12,4,12,4},
    {'M',3,6,"Marsh", "Archer","You can\'t escape!",1,0,2500,30,6,6,13,1,0,{'b','w'},{{'n','n'},{'n','n'},{'n','n'},{'n','n'}},12,5,12,5},
    {'Z',4,8,"Zok",   "Wh__Mage","Need help?",1,0,1500,30,8,8,13,1,0,{'m','r'},{{'l','b'},{'r','e'},{'n','n'},{'n','n'}},12,6,12,6}
};
int amount_of_fighters = sizeof(pcs) / sizeof(pcs[0]);
// struct character_pc character1 = {"A",1,"Avery", "Fighter","This one is protagonist.",1,0,2000,40,8,15,1,1,{"Big Sword",8},{"","",0,0,0},{"","",0,0,0},{"","",0,0,0},{"","",0,0,0},12,3};
// struct character_pc character2 = {"K",2,"Koko",  "Black Mage", "I will eradicate them.",  1,0,2500,40,6,13,1,0,{"Magic Rod",3},{"Light.Bolt","Range 50 + 10 per lvl. DMG 1d6 in 10x40.",50,5,0},{"Fireball","Rnge 100 + 10 per lvl. DMG 1d6 rad 20.",100,6,0},{"","",0,0,0},{"","",0,0,0},12,4};

struct enemy { 
    char letter;
    int id;         // id is must be unique, since we could have multiple figures with the same letter.
    int initiative;
    char name[10];
    char race[15];
    char attack_description[40];
    int hp;
    int ac; /*Armor Class*/
    int mov; /*how many squares player can move*/
    int dmg;
    int morale;
    int saves; /*"SAVES AS target, BFT, p. 89"*/
    int target_index;
    int x_position;
    int y_position;
    int location;
};

/*
Saving throw - d20 against number. 1 is always failure, 20 alway success.
If number + modifier equals or exceeds target number, the roll is success,
otherwise faild.
*/

struct enemy beasts[40] = {
    {'b',1,1,"Bill","Bat","Bat attacks!",4,14,30,4,7,18,0,1,4,2},
    {'s',2,3,"Steve","Bat","Bat attacks!",4,14,30,4,7,18,0,1,3,2},
    {'g',3,1,"Benny","Red_Goblin","Goblin attacks!",4,14,30,4,7,18,0,1,3,4},
    {'g',4,3,"Mitch","Blue_Goblin","Goblin attacks!",4,14,30,4,7,18,0,1,3,4},
    {'g',5,5,"Jim","Red_Goblin","Goblin attacks!",4,14,30,4,7,18,0,1,3,4},
    {'g',6,7,"Phil","Blue_Goblin","Goblin attacks!",4,14,30,4,7,18,0,1,3,4},
    {'f',7,1,"Kool","Floating_Eye","Eye attacks!",8,14,30,4,7,18,0,1,3,5},
    {'p',8,3,"Spotty","Vampire_Cat","Cat attacks!",6,14,40,4,7,18,0,3,5,5},
    {'z',9,1,"Corpse", "Zombie","Zombie attacks!",4,14,40,6,9,20,0,1,6,7},
    {'z',10,3,"Rotter", "Zombie","Zombie attacks!",4,14,40,6,9,20,0,1,6,7},
    {'p',11,1,"Purr","Vampire_Cat","Cat attacks!",6,14,40,4,7,18,0,3,5,8},
    {'b',12,3,"Bob","Squidrakin","Squidrakin attacks",5,13,40,4,7,18,0,1,4,8},
    {'t',13,5,"Skinny",  "Skeleton","Whooa!",4,13,30,8,7,18,0,2,5,8},
    {'g',14,7,"George", "Ghoul","Fire breed attack!",5,14,40,6,9,20,0,1,6,8},
    {'m',15,1,"Max","Minotaur","Minotaur attacks!",8,14,30,4,7,18,0,3,8,9},
    {'b',16,3,"Badok","Malboro","Malboro attacks",8,13,30,4,7,18,0,1,4,9},
    {'t',17,5,"Ted",  "Tentacle_Worm","Squeezed you hard!",14,13,30,8,7,18,0,1,5,9},
    {'h',18,7,"BadBoy", "Hell_Hound","Fire breed attack!",18,14,40,6,9,20,0,1,6,9},
    {'g',19,1,"Peek","Blue_Goblin","Goblin attacks!",4,14,30,4,7,18,0,1,3,11},
    {'m',20,3,"Noom","Big Rat","Rat attacks!",4,14,30,4,7,18,0,1,3,11},
    {'g',21,5,"Poke","Red_Goblin","Goblin attacks!",4,14,30,4,7,18,0,1,3,11},
    {'d',22,7,"Leel","Dryad","Dryad attacks",4,13,40,4,7,18,0,1,4,11},
    {'g',23,1,"Fred","Goblin","Goblin attacks!",4,14,30,4,7,18,0,1,3,12},
    {'r',24,3,"Rogue","Human","Rogue attacks",5,13,40,4,7,18,0,1,4,12},
    {'t',25,5,"Ted",  "Tentacle_Worm","Squeezed you hard!",14,13,30,8,7,18,0,1,5,12},
    {'h',26,7,"BadBoy", "Hell_Hound","Fire breed attack!",18,14,40,6,9,20,0,1,6,12},
    {'m',27,1,"Max","Minotaur","Minotaur attacks!",8,14,30,4,7,18,0,3,8,13},
    {'b',28,3,"Badok","Malboro","Malboro attacks",8,13,30,4,7,18,0,1,4,13},
    {'c',29,5,"Baghun",  "Cúchulainn","Cúchulainn attacks!",14,13,30,8,7,18,0,2,10,13},
    {'z',30,7,"Ziggy", "Zombie_Vampire","Vampire attacks!",4,14,40,6,9,20,0,1,6,13},
    {'m',31,1,"Mini","Big Rat","Rat attacks!",4,14,30,4,7,18,0,1,4,16},
    {'m',32,3,"Moe","Big Rat","Rat attacks!",4,14,30,4,7,18,0,1,3,16},
    {'f',33,1,"Pixie","Floating_Eye","Eye attacks!",8,14,30,4,7,18,0,1,3,17},
    {'n',34,3,"Nina","Dryad","Dryad attacks",4,13,40,4,7,18,0,1,4,17},
    {'d',35,5,"Danny",  "Red_Dragon","eat you alive!",10,13,30,8,7,18,0,1,5,17},
    {'z',36,7,"ZooZoo", "Zalera","Zalera attacks!",6,14,40,6,9,20,0,1,6,17},
    {'g',37,1,"Red","Red_Goblin","Goblin attacks!",4,14,30,4,7,18,0,1,3,21},
    {'b',38,3,"Boby","Bomb","Bomb attacks!",5,13,40,4,7,18,0,2,4,21},
    {'t',39,5,"Tipy",  "Treant","Treant attacks!",14,13,30,8,7,18,0,1,5,21},
    {'h',40,7,"Bixy", "Behemoth","Fire breed attack!",18,14,40,6,9,20,0,1,6,21},
};


struct enemy monsters[4];

int amount_of_monsters = sizeof(monsters) / sizeof(monsters[0]);

struct spell {
    char id[2];
    char name[12];
    char desc[40];
    int range;
    int dmg;
    int recov;
    int inc_mov;
    int dec_mov;
    int always;
};

struct spell spells[3] = {
    {"lb","Light_Bolt","Light bolt the strikes target",50,5,0,0,0},
    {"fb","Fire_Ball ","Ball of fire hits the target",60,6,0,0,0},
    {"re","Recovery  ","Targets HP points has been recovered",10,0,4,0,0}
};

int amount_of_spells = sizeof(spells) / sizeof(spells[0]);

struct weapon {
    char id[2];
    char name[12];
    int ranged; /*0 if sword or dagger, 1 if i.e. bow*/
    int range;
    int inc_dmg;
    int inc_ac;
    int inc_mov;
    int dec_mov;
};

struct weapon weapons[3] = {
    {"bs","Big_Sword",0,0,2,0,0,0},
    {"mr","Magic_Rod",0,0,1,0,0,0},
    {"bw","Bow",1,60,2,0,0,0}
};

int amount_of_weapon = sizeof(weapons) / sizeof(weapons[0]);