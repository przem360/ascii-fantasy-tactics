#define SCREEN_HEIGHT 14
#define SCREEN_WIDTH  22
#define RANGE_CHAR '+'
#define BASE_CHAR '.'
#define TARGET_CHAR 'x'
#define DEAD_BODY_CHAR '~'
const char av_commands[7][6] = {"move", "attack", "use", "end", "cast", "skip", "quit"};
/* First letters of commands should be also legal aliases.
Need to convert input to lower case before checking. */
