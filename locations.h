char intro_text[] = "Welcome to the Mines of Yaradow!\nSomewhere in these dark corridors the old demon Agth is keeping his soul.\nA undead demon terrorizes the inhabitants of the town of Yaradow,\nthe only way to get rid of the demon is to find and destroy its soul.\n\nWill you be brave enough to go deep into the Mines of Yaradow and find the soul of Agth?\n\n";

struct locations {
    int id; // number of room on map
    int size[2]; // width west to east, lenght north to south
    char name[18];
    char description[210];
    char action_description[110];
    int is_enemy; // 0 - no enemy, 1 - look in enemy_array_index
    int enemy_array_index;
    int found; /* 0 - nothing found, 1 - look in search_array_index*/
    int search_array_index;
    /* conections */
    int go_north;
    int go_east;
    int go_south;
    int go_west;
};


struct locations rooms[36] = {
    {1,{4,6},"Large hall","This large room has a row of heavy, cobweb-laden columns down each side. \n The floor is dusty, and you can clearly see a beaten path to \n the door on the far side of the room.", "Nothing to do here.",0,0,0,0,/* c */102,0,2,0},
    {2,{4,4},"Secret room","Description yet to come...",  "Also yet to come",1,0,0,0,/* c */1,0,0,0},
    {3,{6,5},"Room","A row of pegs such as one might hang a cloak \n from run along the wall to your left. The floor is \n littered with scraps of gray and brown fabric.", "Nothing here",0,0,0,0,/* c */101,1,103,5},
    {4,{4,3},"Storage room","This is obviously a storeroom. The walls to the left \n and right are lined with shelves containing what \n appear to be many bottles of wine. The far wall \n is lined with large barrels.", "Nothing here",0,0,0,0,/* c */103,0,0,0},
    {5,{12,6},"Temple","Beyond the double doors you see a colonnaded \n temple with an altar at far end of the room.", "Additional description yet to come",0,0,0,0,/* c */105,3,0,0},
    {6,{4,2},"Study","This room appears to be a study. There is a desk \n on the left and several dilapidated chairs and a \n bookshelf on the right.", "Search reveals passage hidden behind the bookshelf",0,0,0,0,/* c */7,0,105,0},
    {7,{4,3},"Giant ants","You see a group of huge ants as big as ponies.", "Giant Ants attacks!",1,0,0,0,/* c */0,0,6,0},
    {8,{4,4},"Giant spider","Debris, mostly bits of rock and dirt with a few \n bones, is scattered on the floor. The high ceiling \n of this room is covered in a mass of spiderweb.", "Giant Ants attacks!",0,0,0,0,/* c */108,101,0,0},
    {9,{6,4},"Empty room","This room appears to be empty",  "The pits!",0,0,1,0,/* c */0,109,101,0}, // traps!
    {10,{3,3},"Bedroom","This room contains a bed, wardrobe, table and chair. \n On the table you see a ring of keys. \n A thick layer of dust covers everything.",  "Found gold!",0,0,1,0,/* c */0,108,0,0},
    {11,{4,5},"Empty room","This room appears to be empty", "You hear a strange noises.",0,0,0,0,/* c */0,0,108,0},
    {12,{4,4},"Bugbears","You see a group of hairy goblin-like humanoids as big as large men. \n They appear to be camping in this room",  "5 Bugbears attacks",1,0,0,0,/* c */0,112,113,109},
    {13,{4,3},"Empty room","This room appears to be empty.", "Found 500 GP",0,1,0,0,/* c */0,113,0,0},
    {14,{3,3},"Treasure room","There are ten bags piled in the corner of this room. \n They appear to be full.", "Found 1000 GP",0,1,0,0,/* c */0,0,116,113},
    {15,{3,3},"Room","This room appears empty save for a large chest centered against the far wall.", "Additional description yet to come",0,0,0,0,/* c */113,0,115,0},
    {16,{4,4},"Cristals","The walls of this room are covered with large lumps of crystals.", "You are surrounded by white, blue and pink light.",0,0,0,0,/* c */116,0,0,0},
    {17,{7,5},"Statue gallery","This room is illuminated by magic. \n There are six finely crafted statues in two ranks across the room; they \n appear to be elven warriors in chainmail with swords upraised toward you.", "6 living statues attacks",0,0,0,0,/* c */120,0,118,117},
    {18,{4,3},"Sarcophagus","A large sarcophagus rests in the center of this room. \n A chill comes over you as the musty air of the room flows over you.", "You hear a moaning sound, faint and distant. \n It seems to be emanating from the sarcophagus.",0,0,0,0,/* c */118,0,0,0},
    {19,{4,5},"Mystery room","Cobwebs hang thickly from the ceiling in the far left corner of this room, partially covering the \n doorway there.\n A trail of blood leads from the center \n of the room to the door on the right.", "Nothing here!",0,0,0,0,/* c */0,117,0,0},
    {20,{5,4},"Midden","A faint odor of ancient foulness fills the air of this room. \n The top and part of the sides of the piles are covered in mushrooms, \n from the size of your hand up to the size of your head.",  "This room was used as a midden, an area for waste disposal.",0,0,0,0,/* c */0,21,120,0}, // traps!
    {21,{5,4},"Dread altar","There is an altar against the left wall of this room and an unusual blue flame \n burns in a small brazier in the center.",  "Nothing here...",0,0,0,0,/* c */0,121,0,20},
    {22,{2,3},"Stairs","You see stone stairs leading up and above the gate through which the rays of the sun fall. You found a way out.",  "Nothing here...",0,0,0,0,/* c */0,0,0,121},
    /* corridors */
    {101,{10,1},"Corridor","This corridor crossing leads east, west and north, there are doors on the southern wall.", "Nothing to do here.",0,0,0,0,/* c */9,102,3,8},
    {102,{10,1},"Corridor","This corridor is turning. You can go  west or south.", "Nothing to do here.",0,0,0,0,/* c */0,0,1,101},
    {103,{1,2},"Corridor","Short corridor leads north and south.", "Nothing to do here.",0,0,0,0,/* c */3,0,4,0},
    {105,{1,2},"Corridor","Short corridor leads north and south.", "Nothing to do here.",0,0,0,0,/* c */6,0,5,0},
    {108,{10,1},"Corridor","This corridor leads north and south, with a east tunnel in the middle.", "Nothing to do here.",0,0,0,0,/* c */11,0,8,10},
    {109,{5,1},"Corridor","This corridor leads east and west.", "Nothing to do here.",0,0,0,0,/* c */0,12,0,9},
    {112,{6,1},"Corridor","This corridor turns west and north.", "Nothing to do here.",0,0,0,0,/* c */117,0,0,12},
    {113,{3,6},"Corridor","This is a crossing, leads east, west, north and south.", "Nothing to do here.",0,0,0,0,/* c */12,14,15,13},
    {115,{1,3},"Corridor","Short corridor leads north and south but south looks like a dead end.", "Nothing to do here.",0,0,0,0,/* c */15,0,0,0},
    {116,{1,4},"Corridor","This is a crossing, leads north and south.", "Nothing to do here.",0,0,0,0,/* c */14,0,16,0},
    {117,{5,1},"Corridor","This corridor leads east and west.", "Nothing to do here.",0,0,0,0,/* c */0,17,112,19},
    {118,{1,2},"Corridor","Short corridor leads north and south.", "Nothing to do here.",0,0,0,0,/* c */17,0,18,0},
    {120,{1,2},"Corridor","Short corridor leads north and south.", "Nothing to do here.",0,0,0,0,/* c */20,0,17,0},
    {121,{5,1},"Corridor","This corridor leads east and west.", "Nothing to do here.",0,0,0,0,/* c */0,22,0,21},
};

