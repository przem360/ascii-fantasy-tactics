#define SCREEN_HEIGHT 14
#define SCREEN_WIDTH  22
#define COMMAND_LENGHT 12
#define WALL_CHAR '#'
#define RANGE_CHAR ' '
//#define RANGE_CHAR '■'
#define BASE_CHAR '.'
#define TARGET_CHAR 'x'
#define DEAD_BODY_CHAR '~'
#define COLOURS_ON 1
#define MAX_MOV 10
#define NO_SIDEPANEL 1
const char av_commands[6][6] = {"move", "attack", "cast", "skip", "quit","info"};
int max_mov_fields = MAX_MOV * MAX_MOV;

#define DBG_MODE 0

int invisible = 0;

