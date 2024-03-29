#define FINAL_LOCATION 22

char intro_text[] = "These are the ruins of Yaradow Castle,\nwhere Lord Agth ruled long ago.\nMany years after the sorcerer's death,\nnature is taking over what was left of his castle.\nThe brick walls have become overgrown with moss\nand the cracked remains of the floors are now covered\nwith a carpet of grass.\n\nRumors circulating among locals say that old Agth\nhas trapped a fragment of his soul somewhere here\nand now, as an undead demon, he drains the energy\nof unlucky people who wander into the area.\n\nYou are the only hope for restoring peace to this area...\n\n";

struct locations {
    int id; // number of room on map
    int size[2]; // width west to east, lenght north to south
    char name[33];
    char description[321];
    char action_description[111];
    int is_enemy; // 0 - no enemy, 1 - look in enemy_array_index
    int enemy_array_index;
    int found; /* 0 - nothing found, 1 - look in search_array_index*/
    int search_array_index;
    int arena;
    /* conections */
    int go_north;
    int go_east;
    int go_south;
    int go_west;
};


struct locations rooms[36] = {
    {1,{4,6},"Entry hall","You entered between gray brick walls, old and torn,\nprotruding from the ground like the teeth of an ancient beast.\n\nIn the northern wall there is a passage leading to the corridor, in the southern wall there is a heavy door.\n\nThere are sounds of giggling and wild growling.", "These sounds are coming from the south.",0,0,0,0,/* a */0,/* c */102,0,2,0},
    {2,{4,4},"The bat chamber","This small chamber is empty.\nBats hang from the rotting ceiling beams.\nYou see that there are deep grooves in the walls.",  "Whatever was clawing at the walls was a big beast.",1,0,0,0,/* a */0,/* c */1,0,0,0},
    {3,{6,5},"Old library","This is the sorcerer\'s library.\nThe shelves stretching along the walls to the ceiling\nare bending under the weight of thousands of books.", "The collection is impressive.",0,0,0,0,/* a */0,/* c */101,1,103,5},
    {4,{4,3},"Sorcerer\'s collection","In this small room there are cabinets with dozens of small drawers.\nThere are jars with strange things and a collection of magic wands.", "These items may be cursed.",0,0,0,0,/* a */0,/* c */103,0,0,0},
    {5,{12,6},"The Creek of Nixx","This was once a sorcerer's workshop,\na branch of the Nixx River flows through here, who knows what may be swimming in these waters\nthat were once used for the practice of black magic.", "If you remain silent, you can listen to the sound of the slowly flowing river.",1,0,0,0,/* a */2,/* c */105,3,0,0},
    {6,{4,2},"Room with paintings","There is no furniture in this room.\nThere are portraits and landscapes depicting\ncemeteries hanging on the walls.\nOpposite the entrance, in the northern wall, there is a door.", "You hear the sounds of footsteps.",0,0,0,0,/* a */0,/* c */7,0,105,0},
    {7,{4,3},"The Chapel of Solitude","Visibility is poor.\nThere are no windows in this room and the only\nsource of light is the door through which you entered.\nOn the opposite wall there is an armchair and a black mirror.", "You sense the gloomy aura of this room.",1,0,0,0,/* a */0,/* c */0,0,6,0},
    {8,{4,4},"The Chamber of fungus","Here the walls have vibrant colors, you become light, you seem to be floating. Would you like to stay here?", "You hear the beautiful sound of the cello.",0,0,0,0,/* a */0,/* c */108,101,0,0},
    {9,{6,4},"Temple of forgotten gods","Even though the vault collapsed long ago,\nthe columns that once supported it are still standing.\nUnder the western wall you can see the remains of a wooden altar.",  "This place will be haunted forever.",1,0,1,0,/* a */1,/* c */0,109,101,0},
    {10,{3,3},"The mosaics chamber","A small room with one window. The walls are lined with ceramic mosaics depicting old magical rites.",  "There\'s nothing else here.",0,0,1,0,/* a */0,/* c */0,108,0,0},
    {11,{4,5},"The Tower","There used to be a tower here but it collapsed a long time ago.\nThe remains of a staircase leading to nowhere stick out of the ground.", "You hear a strange noises.",1,0,0,0,/* a */0,/* c */0,0,108,0},
    {12,{4,4},"Crossing","More or less in the middle of the room, from the floor to the ceiling, there is a huge spider's web.\n\nYou hear quiet scratching and rustling.",  "You can\'t see anything else, maybe it\'s better.",1,0,0,0,/* a */0,/* c */0,112,113,109},
    {13,{4,3},"Chamber of the mist","There is fog in this room.\n\nYou can't see the floor you're walking on at all.\nYou can't see walls or doors.\nEach party member appears only as a barely noticeable shape.", "Maybe it's safer to retreat.",0,1,0,0,/* a */0,/* c */0,113,0,0},
    {14,{3,3},"Chamber of wandering souls","The room is empty.\n On the walls you see moving shadows in human shapes.\nThey walk silently along the surfaces of the walls.", "Do they know about our presence?",0,1,0,0,/* a */0,/* c */0,0,116,113},
    {15,{3,3},"Meat storage room","There are steel hooks hanging on the chains with dried blood on them.\nYou notice the smell of death in the air.", "There\'s a screech of metal in the distance.",0,0,0,0,/* a */0,/* c */113,0,115,0},
    {16,{4,4},"Ritual Chamber","You entered through the only door in this room.\nTorch holders stick out from the walls.\nOn the remains of the floor you can see symbols of ancient magic.", "Looks like there\'s nothing here.",0,0,0,0,/* a */0,/* c */116,0,0,0},
    {17,{7,5},"Well of voices","This room is a large hall with a stone well in the center.\nA soft singing comes from inside the well.", "When you look into the well, you see a surface of clean water.",0,0,0,0,/* a */3,/* c */120,0,118,117},
    {18,{4,3},"Decaying room","The walls of this empty room are bent inwards, as if they wanted to crush anyone who dares to stay here.", "You hear a creaking sound coming from the walls, as if old bricks were slowly moving.",0,0,0,0,/* a */0,/* c */118,0,0,0},
    {19,{4,5},"The chamber of eyes","The eyes carved in the walls seem to be watching you.\nYou even feel like they\'re moving.", "They are watching...",0,0,0,0,/* a */0,/* c */0,117,0,0},
    {20,{5,4},"Cocoons","Human-sized cocoons hang from the burnt beams of the ceiling.\nThey vibrate and crackle, you feel like something is trying to get out of them.",  "It\'s better to leave this place",0,0,0,0,/* a */0,/* c */0,21,120,0}, // traps!
    {21,{5,4},"Empty hall","Looks like there\'s nothing here.\nYou feel a gentle breeze of fresh air.",  "Nothing here...",0,0,0,0,/* a */0,/* c */0,121,0,20},
    {22,{2,3},"The Chamber of immortality","\t\t CONGRATULATIONS !\n\nYou entered a small, dark room.\nIt's empty here, except for the decorated plinth in the middle.\nOn the pedestal there is a glass vessel with opalescent contents.\nHere you have found the soul of a demon.\n\nBy breaking the vessel, you bring death to Agth.\n\nYour mission has been completed.",  "The nightmare is over.",0,0,0,0,/* a */0,/* c */0,0,0,121},
    /* corridors */
    {101,{10,1},"Corridor","This corridor crossing leads east, west and north, there are doors on the southern wall.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */9,102,3,8},
    {102,{10,1},"Corridor","This corridor is turning. You can go  west or south.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */0,0,1,101},
    {103,{1,2},"Corridor","Short corridor leads north and south.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */3,0,4,0},
    {105,{1,2},"Corridor","Short corridor leads north and south.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */6,0,5,0},
    {108,{10,1},"Corridor","This corridor leads north and south, with a east tunnel in the middle.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */11,0,8,10},
    {109,{5,1},"Corridor","This corridor leads east and west.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */0,12,0,9},
    {112,{6,1},"Corridor","This corridor turns west and north.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */117,0,0,12},
    {113,{3,6},"Corridor","This is a crossing, leads east, west, north and south.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */12,14,15,13},
    {115,{1,3},"Corridor","Short corridor leads north and south but south looks like a dead end.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */15,0,0,0},
    {116,{1,4},"Corridor","This is a crossing, leads north and south.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */14,0,16,0},
    {117,{5,1},"Corridor","This corridor leads east and west.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */0,17,112,19},
    {118,{1,2},"Corridor","Short corridor leads north and south.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */17,0,18,0},
    {120,{1,2},"Corridor","Short corridor leads north and south.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */20,0,17,0},
    {121,{5,1},"Corridor","This corridor leads east and west.", "Nothing to do here.",0,0,0,0,/* a */0,/* c */0,22,0,21},
};
