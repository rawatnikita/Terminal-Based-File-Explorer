#include <stdlib.h>
#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string>
#include <grp.h>
#include <cstdio>
#include <stack>
#include <vector>
#include <stdio.h>
#include <sys/ioctl.h>
#include <cstring>
#include <fcntl.h>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <signal.h>
using namespace std;
extern struct termios orig;
extern stack<char*> bkd;
extern string apphome;
extern string home;
extern vector<char*> path;
void listFiles(const char*);
void clearTerminal();
void listDirectory();
void openEditor(const char*);
void positionCursor(int x,int y);
void noncanonicalMode();
void canonicalMode();
void cmdMode();
void navigate();
void display(int,int);
void windowSize(int*,int*);
