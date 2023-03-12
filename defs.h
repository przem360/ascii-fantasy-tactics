#define RANGE_CHAR '+'
#define BASE_CHAR '.'
const char av_commands[6][6] = {"move", "attack", "use", "end", "spell", "quit"};
/* First letters of commands should be also legal aliases.
Need to convert input to lower case before checking. */
