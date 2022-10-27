#include "header.h"
struct termios orig;
void canonicalMode()
{
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig);
}
void clearTerminal()
{
 write(STDOUT_FILENO,"\x1b[2J",4);
}
void noncanonicalMode()
{
    char pw[200];
   listFiles(getcwd(pw,200));
    tcgetattr(STDIN_FILENO,&orig);
    struct termios raw=orig;
    raw.c_lflag&=~(ICANON|ECHO);//to enter noncanonical mode
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
    navigate();   
}
